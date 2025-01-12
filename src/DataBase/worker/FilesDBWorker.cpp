#include "FilesDBWorker.h"

#include "../../Initial/SplashScreen.h"
#include "../../Manager/Config/iniManager.h"
#include "../SqlQuery/Directory.h"

bool FilesDBWorker::doFullWork(SplashScreen* splash)
{
  splash->showMessage(QObject::tr("首次加载需要较长时间"));
  QElapsedTimer timer;
  timer.start();

  // 快速收集所有顶级目录（各个磁盘下的目录）
  QStringList rootPaths;
  QStringList pendingDirs; ///< 保留所有要处理的目录
  for (const auto& drive : QDir::drives()) {
    QString rootPath = drive.absolutePath(); ///< "C:/", "D:/"...
    QDir rootDir(rootPath);
    rootPaths << rootPath;
    // 如果目录不可读或不可以根据名称打开文件，尝试下一个
    if (!rootDir.isReadable()) continue;

    auto entries = rootDir.entryInfoList(QDir::Dirs | QDir::Hidden |
      QDir::NoDotAndDotDot);
    for (const auto& dirInfo : entries) {
      pendingDirs << dirInfo.absoluteFilePath();
    }
  }
  // 先把目录全部写入 Directory 表
  Directory::autoInsert(pendingDirs + rootPaths);

  // 根据目录大小分配工作
  QList<QFuture<void>> futures; ///< QFuture<void>表示结果中不包含任何内容
  constexpr int batchSize = 15; ///< 每个线程处理15个目录
  for (int i = 0; i < pendingDirs.size(); i += batchSize) {
    QStringList batch = pendingDirs.mid(i, batchSize);
    auto future = QtConcurrent::run([this, batch]() {
      for (const QString& dir : batch) { processDirectory(dir); }
    });
    futures.append(future); ///< 放入每个线程得到的结果
  }

  // 等待所有扫描任务完成
  for (auto& future : futures) { future.waitForFinished(); }

  updateLastBuildSqlTime();
  return true;
}

bool FilesDBWorker::doIncrementalScan(SplashScreen* splash)
{
  splash->showMessage(QObject::tr("正在更新数据库"));

  updateLastBuildSqlTime();
}

inline void FilesDBWorker::processDirectory(const QString& dirPath)
{
  constexpr int BATCH_SIZE = 1000; ///< 批量处理文件
  QVector<QString> filesBatch;
  filesBatch.reserve(BATCH_SIZE);

  QDirIterator it(dirPath,
                  QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks,
                  QDirIterator::Subdirectories);

  while (it.hasNext()) {
    QString filePath = it.next();
    filesBatch.append(filePath);

    // 分批次交给 processBatch 处理
    if (filesBatch.size() >= BATCH_SIZE) {
      processBatch(filesBatch);
      filesBatch.clear();
      filesBatch.reserve(BATCH_SIZE);
    }
  }

  // 处理剩余的文件
  if (!filesBatch.isEmpty()) { processBatch(filesBatch); }
}

inline void FilesDBWorker::processBatch(const QVector<QString>& files)
{
  for (const QString& filePath : files) {
    QFileInfo fileInfo(filePath);
    const qint64 size = fileInfo.size();

    // TODO: 在这里添加实际的文件处理逻辑
  }
}

void FilesDBWorker::updateLastBuildSqlTime()
{
  auto ICMA = iniManager::getIniSetting();
  ICMA.setValue("Settings/lastBuildSqlTime",
                QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm"));
}
