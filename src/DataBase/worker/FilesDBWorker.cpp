#include "FilesDBWorker.h"

#include <QThread>

#include "../../Initial/SplashScreen.h"
#include "../../Manager/Config/iniManager.h"
#include "../SqlQuery/Directory.h"
#include "../SqlQuery/Files.h"

bool FilesDBWorker::doFullScan(SplashScreen* splash_pram)
{
  if (!splash_pram) {
    qWarning() << "Splash screen pointer is null";
    return false;
  }

  splash = splash_pram;
  splash->showMessage(QObject::tr("首次加载需要较长时间"));

  try {
    // 快速收集所有顶级目录（各个磁盘下的目录）
    QStringList rootDirs;    ///< 根目录（磁盘驱动）
    QStringList pendingDirs; ///< 收集到的要处理的目录

    // 通过获取所有磁盘驱动而得到顶层目录
    for (const auto& drive : QDir::drives()) {
      QString rootDirPath = drive.absolutePath(); ///< "C:/", "D:/"...
      QDir rootDir(rootDirPath);
      rootDirs << rootDirPath;

      // 如果目录不可读或不可以根据名称打开文件，尝试下一个
      if (!rootDir.isReadable()) {
        qWarning() << "Drive not readable:" << rootDirPath;
        continue;
      }

      // 获取驱动下的顶层目录 不递归子目录
      for (const auto& dirInfo :
           rootDir.entryInfoList(
             QDir::Dirs | QDir::Hidden | QDir::NoDotAndDotDot)) {
        pendingDirs << dirInfo.absoluteFilePath();
      }
    }

    // 先把目录全部写入 Directory 表
    if (!DirectoryDB::autoInsert(rootDirs + pendingDirs)) {
      qWarning() << "Failed to insert directories into database";
      return false;
    }

    // 进度条基础设置
    splash->setProgress(0);
    int totalDirs = static_cast<int>(pendingDirs.size());
    splash->setMaximum(totalDirs);

    // 根据CPU核心数确定线程数
    const int threadCount = QThread::idealThreadCount(); ///< 如4核8线程,则返返回8
    //threadCount = qMax(1, threadCount - 1);        ///< 保留一个线程给UI

    // 根据目录大小分配工作
    QList<QFuture<void>> futures;
    constexpr int batchSize = 10; ///< 每个线程处理15个目录

    int processedDirs = 0; ///< 已处理的目录数
    for (auto i = 0; i < pendingDirs.size(); i += batchSize) {
      QStringList batch = pendingDirs.mid(i, batchSize);

      // 多线程并发
      auto future = QtConcurrent::run([this, batch, &processedDirs, totalDirs] {
        for (const auto& dirPath : batch) {
          doDirectory(dirPath);
          // 原子操作增加已处理目录数
          processedDirs++;
          // 更新进度
          const int progress = (processedDirs * 100) / totalDirs;
          splash->setProgress(progress);
          splash->showMessage(QObject::tr("正在扫描: %1%").arg(progress));
        }
      });

      futures.append(future);

      // 限制同时运行的线程数
      while (futures.size() >= threadCount) {
        for (auto it = futures.begin(); it != futures.end();) {
          if (it->isFinished()) { it = futures.erase(it); }
          else { ++it; }
        }
        QThread::msleep(100); ///< 100ms检查一次
      }
    }

    // 等待所有扫描任务完成
    for (auto& future : futures) { future.waitForFinished(); }

    updateLastBuildSqlTime();
  } catch (const std::exception& e) {
    qCritical() << "Exception during full scan:" << e.what();
    splash->deleteLater();
    return false;
  }

  splash->deleteLater();
  return true;
}

inline void FilesDBWorker::doDirectory(const QString& dirPath)
{
  constexpr int BATCH_SIZE = 1000; ///< 批量处理文件
  QStringList filesBatch;
  filesBatch.reserve(BATCH_SIZE);

  try {
    QDirIterator it(dirPath,
                    QDir::AllEntries | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                    QDirIterator::Subdirectories);

    while (it.hasNext()) {
      QString path = it.next();

      // 如果是目录直接处理。如果是文件则收集等待批处理
      if (QFileInfo info(path); info.isDir()) { DirectoryDB::autoInsert(path); }
      else { filesBatch << path; }

      // 分批次处理文件
      if (filesBatch.size() >= BATCH_SIZE) {
        if (!FilesDB::autoInsert(filesBatch)) {
          qWarning() << "Failed to insert files batch";
        }
        filesBatch.clear();
        filesBatch.reserve(BATCH_SIZE);
      }
    }

    // 处理剩余的文件
    if (!filesBatch.isEmpty()) {
      if (!FilesDB::autoInsert(filesBatch)) {
        qWarning() << "Failed to insert remaining files";
      }
    }
  } catch (const std::exception& e) {
    qWarning() << "Exception in doDirectory:" << dirPath << e.what();
  }
}

bool FilesDBWorker::doIncrementalScan(SplashScreen* splash_pram)
{
  if (!splash_pram) {
    qWarning() << "Splash screen pointer is null";
    return false;
  }

  splash = splash_pram;
  splash->showMessage(QObject::tr("正在更新数据库"));

  try {
    // 获取上次扫描时间
    const auto ICMA = iniManager::getIniSetting();
    const QString lastScanTime = ICMA.value("Settings/lastBuildSqlTime")
                                     .toString();
    auto lastScan =
      QDateTime::fromString(lastScanTime, "yyyy/MM/dd hh:mm");

    // 获取所有已知目录
    QStringList knownDirs = DirectoryDB::getAllPaths();
    QStringList existingDirs; ///< 有效（存在）的目录(筛选knownDirs)
    QStringList newDirs;      ///< 保留新增目录(knownDirs中不存在的)

    splash->setMaximum(static_cast<int>(knownDirs.size()));
    int progress = 0;

    // 检查已知目录是否仍然存在，同时收集新目录
    for (const QString& dirPath : knownDirs) {
      if (QDir dir(dirPath); dir.exists()) {
        existingDirs << dirPath;

        // 检查这个目录下的新子目录
        QDirIterator it(dirPath,
                        QDir::Dirs | QDir::NoDotAndDotDot,
                        QDirIterator::Subdirectories);
        while (it.hasNext()) {
          if (QString newPath = it.next(); !knownDirs.contains(newPath)) {
            newDirs << newPath;
          }
        }
      }
      else {
        // 目录不存在了，从数据库中删除目录
        DirectoryDB::remove(dirPath);
      }

      progress++;
      splash->setProgress(static_cast<int>(progress * 100 / knownDirs.size()));
      splash->showMessage(
        QObject::tr("正在检查目录: %1%").arg(progress * 100 / knownDirs.size()));
    }

    // 将新发现的目录添加到数据库
    if (!newDirs.isEmpty()) {
      DirectoryDB::autoInsert(newDirs);
      existingDirs << newDirs;
    }

    // 检查新文件和修改过的文件
    QMap<QString, QDateTime> dbFiles = FilesDB::getAllFilesWithModTime();
    auto totalDirs = static_cast<int>(existingDirs.size());
    progress = 0;

    // 使用多线程处理目录
    QList<QFuture<void>> futures;
    constexpr int batchSize = 15;
    const int threadCount = QThread::idealThreadCount() - 1; ///< 保留一个线程给UI

    for (auto i = 0; i < existingDirs.size(); i += batchSize) {
      QStringList batch = existingDirs.mid(
        i, qMin(batchSize, existingDirs.size() - i));

      auto future = QtConcurrent::run(
        [this, batch, &dbFiles, &progress, totalDirs] {
          doIncrementalBatch(batch, dbFiles, progress, totalDirs);
        });

      futures.append(future);

      // 限制同时运行的线程数
      while (futures.size() >= threadCount) {
        for (auto it = futures.begin(); it != futures.end();) {
          if (it->isFinished()) { it = futures.erase(it); }
          else { ++it; }
        }
        QThread::msleep(100); ///< 让调用的线程阻塞
      }
    }

    // 等待所有扫描任务完成
    for (auto& future : futures) { future.waitForFinished(); }
  } catch (const std::exception& e) {
    qCritical() << "Exception during incremental scan:" << e.what();
    splash->deleteLater();
    return false;
  }
  updateLastBuildSqlTime();
  splash->deleteLater();
  return true;
}

// dbFiles是数据库中现有所有文件
void FilesDBWorker::doIncrementalBatch(const QStringList& dirs,
                                       const QMap<QString, QDateTime>& dbFiles,
                                       int& progress, const int totalDirs) const
{
  constexpr int BATCH_SIZE = 1000;
  QStringList newFilesBatch;
  QStringList updatedFilesBatch;
  QStringList removedFiles;
  newFilesBatch.reserve(BATCH_SIZE);
  updatedFilesBatch.reserve(BATCH_SIZE);

  for (const QString& dirPath : dirs) {
    QDirIterator it(dirPath,
                    QDir::Files | QDir::NoDotAndDotDot,
                    QDirIterator::Subdirectories);

    QSet<QString> curFiles; ///< 保留系统中当前存在的所有文件

    while (it.hasNext()) {
      QString filePath = it.next();
      QFileInfo fileInfo(filePath);

      curFiles.insert(filePath);

      if (!dbFiles.contains(filePath)) { ///< 新文件
        newFilesBatch << filePath;
      }
      else {
        if (auto dbModTime = dbFiles[filePath];
          fileInfo.lastModified() > dbModTime) { ///< 检查文件是否被修改
          updatedFilesBatch << filePath;
        }
      }

      // 批量处理新文件
      if (newFilesBatch.size() >= BATCH_SIZE) {
        FilesDB::autoInsert(newFilesBatch);
        newFilesBatch.clear();
        newFilesBatch.reserve(BATCH_SIZE);
      }

      // 批量处理更新的文件
      if (updatedFilesBatch.size() >= BATCH_SIZE) {
        FilesDB::updateFile(updatedFilesBatch);
        updatedFilesBatch.clear();
        updatedFilesBatch.reserve(BATCH_SIZE);
      }
    }

    // 查找已删除的文件
    for (auto iter = dbFiles.begin(); iter != dbFiles.end(); ++iter) {
      if (iter.key().startsWith(dirPath) &&
        !curFiles.contains(iter.key())) { removedFiles << iter.key(); }
    }

    progress++;
    if (splash) {
      splash->setProgress((progress * 100) / totalDirs);
      splash->showMessage(
        QObject::tr("正在扫描: %1%").arg((progress * 100) / totalDirs));
    }
  }

  // 处理剩余的批次
  if (!newFilesBatch.isEmpty()) { FilesDB::autoInsert(newFilesBatch); }
  if (!updatedFilesBatch.isEmpty()) { FilesDB::updateFile(updatedFilesBatch); }
  if (!removedFiles.isEmpty()) { FilesDB::removeFile(removedFiles); }
}

void FilesDBWorker::updateLastBuildSqlTime()
{
  auto ICMA = iniManager::getIniSetting();
  ICMA.setValue("Settings/lastBuildSqlTime",
                QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm"));
}
