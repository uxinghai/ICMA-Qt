#include "FilesDBWorker.h"

#include <QDirIterator>
#include <QThread>

#include "../../../DataBase/SqlQuery/Directory.h"
#include "../../../DataBase/SqlQuery/Files.h"
#include "../../../Initial/SplashScreen.h"
#include "../../../Manager/Config/iniManager.h"

namespace
{
  // 文件批处理的大小
  constexpr int BATCH_SIZE = 1000;
  // 每个线程处理的目录数
  constexpr int DIRS_PER_THREAD = 10;

  // 进度更新管理类
  class ProgressUpdater {
  public:
    explicit ProgressUpdater(SplashScreen* splash, const QString& message = "")
      : splash_(splash), message_(message) {}

    void update(const int current, const int total) const
    {
      if (!splash_) return;
      const int progress = (current * 100) / total;
      splash_->setProgress(progress);
      if (!message_.isEmpty()) {
        splash_->showMessage(QObject::tr(message_.arg(progress).toUtf8()));
      }
    }

  private:
    SplashScreen* splash_;
    QString message_;
  };

  // 批量处理文件的辅助函数
  void processBatch(QStringList& batch,
                    const std::function<void(const QStringList&)>& processor)
  {
    if (!batch.isEmpty()) {
      processor(batch);
      batch.clear();
      batch.reserve(BATCH_SIZE);
    }
  }
}

bool FilesDBWorker::doFullScan(SplashScreen* splash_pram) const
{
  if (!splash_pram) { return false; }

  splash_pram->showMessage(QObject::tr("首次加载需要较长时间"));

  try {
    // 收集根目录及其直接子目录
    QStringList pendingDirs;
    for (const auto& drive : QDir::drives()) {
      if (!drive.isReadable()) {
        qWarning() << "驱动器不可读:" << drive.absolutePath();
        continue;
      }

      QDirIterator it(drive.absolutePath(),
                      QDir::Dirs | QDir::Hidden,
                      QDirIterator::NoIteratorFlags); ///< 确保不会递归
      while (it.hasNext()) {
        QString dir = it.next();
        if (dir == "." || dir == "..") continue;
        pendingDirs << dir;
      }
    }

    // 初始化目录扫描
    if (!DirectoryDB::autoInsert(pendingDirs)) {
      qWarning() << "向数据库插入目录失败";
      return false;
    }

    // 设置进度跟踪
    ProgressUpdater progress(splash_pram, QObject::tr("正在扫描: %1%"));
    int totalDirs = pendingDirs.size();
    splash_pram->setMaximum(totalDirs);

    // 并行处理目录
    QList<QFuture<void>> futures;
    const int threadCount = QThread::idealThreadCount() - 1;

    for (int i = 0; i < pendingDirs.size(); i += DIRS_PER_THREAD) {
      auto batch = pendingDirs.mid(i, DIRS_PER_THREAD);
      futures << QtConcurrent::run([this, batch, &progress, i, totalDirs] {
        for (const auto& dir : batch) {
          doDirectory(dir);
          progress.update(i, totalDirs);
        }
      });

      // 管理活动线程
      while (futures.size() >= threadCount) {
        futures.removeIf([](const QFuture<void>& f) { return f.isFinished(); });
        QThread::msleep(100);
      }
    }

    for (auto& future : futures) { future.waitForFinished(); }

    updateLastBuildSqlTime();
    return true;
  } catch (const std::exception& e) {
    qCritical() << "全盘扫描期间发生异常:" << e.what();
    return false;
  }
}

void FilesDBWorker::doDirectory(const QString& dirPath)
{
  QStringList filesBatch;
  filesBatch.reserve(BATCH_SIZE);

  try {
    for (auto filePath : QDir(dirPath).entryList(
           QDir::Files | QDir::NoDotAndDotDot)) {
      filesBatch << QDir(dirPath).filePath(filePath); ///< 是绝对完整路径
      if (filesBatch.size() >= BATCH_SIZE) {
        processBatch(filesBatch, FilesDB::autoInsert);
      }
    }
  } catch (const std::exception& e) {
    qWarning() << "处理目录时发生异常:" << dirPath << e.what();
  }

  // 处理剩余未处理的文件
  if (!filesBatch.isEmpty()) { processBatch(filesBatch, FilesDB::autoInsert); }
}

bool FilesDBWorker::doIncrementalScan(SplashScreen* splash_pram) const
{
  if (!splash_pram) {
    qWarning() << "启动画面指针为空";
    return false;
  }

  try {
    // 获取上次扫描时间和已知目录
    const auto lastScan = iniManager::getIniSetting()
                          .value("Settings/lastBuildSqlTime").toString();
    QStringList knownDirs = DirectoryDB::getAllPaths();

    // 处理目录
    QStringList existingDirs, newDirs;
    ProgressUpdater progress(splash_pram, QObject::tr("正在检查目录: %1%"));

    for (const auto& dir : knownDirs) {
      if (QDir qdir(dir); qdir.exists()) {
        existingDirs << dir;
        // 查找新的子目录
        QDirIterator it(dir, QDir::Dirs | QDir::NoDotAndDotDot,
                        QDirIterator::Subdirectories);
        while (it.hasNext()) {
          if (QString newPath = it.next(); !knownDirs.contains(newPath)) {
            newDirs << newPath;
          }
        }
      }
      else { DirectoryDB::remove(dir); }
    }

    if (!newDirs.isEmpty()) {
      DirectoryDB::autoInsert(newDirs);
      existingDirs << newDirs;
    }

    // 处理文件
    auto dbFiles = FilesDB::getAllFilesWithModTime();
    const int threadCount = QThread::idealThreadCount() - 1;
    QList<QFuture<void>> futures;

    for (int i = 0; i < existingDirs.size(); i += DIRS_PER_THREAD) {
      auto batch = existingDirs.mid(i, DIRS_PER_THREAD);
      futures << QtConcurrent::run([this, batch, &dbFiles] {
        doIncrementalBatch(batch, dbFiles);
      });

      while (futures.size() >= threadCount) {
        futures.removeIf([](const QFuture<void>& f) { return f.isFinished(); });
        QThread::msleep(100);
      }
    }

    for (auto& future : futures) { future.waitForFinished(); }

    updateLastBuildSqlTime();
    return true;
  } catch (const std::exception& e) {
    qCritical() << "增量扫描期间发生异常:" << e.what();
    return false;
  }
}

void FilesDBWorker::doIncrementalBatch(
  const QStringList& dirs,
  const QMap<QString, QDateTime>& dbFiles)
{
  QStringList newFiles, updatedFiles, removedFiles;
  newFiles.reserve(BATCH_SIZE);
  updatedFiles.reserve(BATCH_SIZE);

  for (const auto& dir : dirs) {
    QSet<QString> currentFiles;
    QDirIterator it(dir, QDir::Files | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
      QString path = it.next();
      QFileInfo info(path);
      currentFiles.insert(path);

      if (!dbFiles.contains(path)) { newFiles << path; }
      else if (info.lastModified() > dbFiles[path]) { updatedFiles << path; }

      processBatch(newFiles, FilesDB::autoInsert);
      processBatch(updatedFiles, FilesDB::updateFile);
    }

    // 查找已删除的文件
    for (auto iterator = dbFiles.begin(); iterator != dbFiles.end(); ++
         iterator) {
      if (iterator.key().startsWith(dir) && !currentFiles.
        contains(iterator.key())) { removedFiles << iterator.key(); }
    }
  }

  // 处理剩余的批次
  processBatch(newFiles, FilesDB::autoInsert);
  processBatch(updatedFiles, FilesDB::updateFile);
  if (!removedFiles.isEmpty()) { FilesDB::removeFile(removedFiles); }
}

void FilesDBWorker::doScanDirectory(const QString& directoryPath,
                                    const bool recursive)
{
  // 收集要处理的目录列表
  QStringList pendingDirs = {directoryPath};
  if (recursive) { ///< 如果想要递归扫描子目录
    QDirIterator it(directoryPath, QDir::Dirs | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
      it.next();
      pendingDirs << it.filePath();
    }
  }

  // 将所有目录写入数据库
  for (const auto& dirPath : pendingDirs) { DirectoryDB::autoInsert(dirPath); }

  // 并行处理目录
  QList<QFuture<void>> futures;
  const int threadCount = QThread::idealThreadCount() - 1; ///< 保留一个线程给UI

  for (int i = 0; i < pendingDirs.size(); i += DIRS_PER_THREAD) {
    auto batch = pendingDirs.mid(i, DIRS_PER_THREAD);
    futures << QtConcurrent::run([batch] {
      // 处理单个目录下的所有文件
      for (const auto& dirPath : batch) { doDirectory(dirPath); }
    });

    // 管理活动线程数量
    while (futures.size() >= threadCount) {
      futures.removeIf([](const QFuture<void>& f) { return f.isFinished(); });
      QThread::msleep(100);
    }
  }

  // 等待所有任务完成
  for (auto& future : futures) { future.waitForFinished(); }
}

void FilesDBWorker::updateLastBuildSqlTime()
{
  iniManager::getIniSetting().setValue(
    "Settings/lastBuildSqlTime",
    QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm")
  );
}

QVariant FilesDBWorker::getFileHashValue(const QString& filePath)
{
  QFile file(filePath);
  if (!file.exists()) {
    qDebug() << "File does not exist:" << filePath;
    return {};
  }

  if (file.open(QIODevice::ReadOnly)) {
    QCryptographicHash hash(QCryptographicHash::Sha256);
    while (!file.atEnd()) {
      QByteArray data = file.read(1024 * 1024); ///< 1MB
      hash.addData(data);
    }
    file.close();
    return hash.result().toHex();
  }
  return {};
}
