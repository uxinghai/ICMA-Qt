/**
 * @file FilesDatabaseUpdater.h
 *
 * @Breife 后台更新 Files 表的任务类
 *
 * @version 1.0
 * @date 2025/4/5
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QObject>
#include <QRunnable>

#include "../../DataBase/SqlQuery/Files.h"

class FilesDatabaseUpdater final : public QObject, public QRunnable {
  Q_OBJECT

public:
  FilesDatabaseUpdater()
  {
    setAutoDelete(true); // 任务执行完后自己销毁
  }

  // 启动后台更新进程
  void run() override
  {
    // 删除 Files 中的旧数据
    for (auto path : sFileDB.getDBDisticntCol("TempFiles", "file_path")) {
      if (m_cancelled.loadRelaxed()) { return; }
      sFileDB.delectRowByFilePath(path, "Files");
    }

    // 删除完成后 插入新的内容 并且计算 hash 值
    for (auto absPath : sFileDB.getAllFileAbsPath("TempFiles")) {
      if (m_cancelled.loadRelaxed()) { return; }
      FileInfo info = sFileDB.createFileInfo(absPath, true);
      sFileDB.insertFileInto("Files", info);
    }
  }

  void cancel() { m_cancelled.storeRelaxed(true); }
signals:

private:
  QAtomicInt m_cancelled{false}; // 线程安全的布尔值
};
