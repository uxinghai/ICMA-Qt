/**
 * @file LogOut.h
 *
 * @Breife 该头文件用于实现重定向了日志输出到文件系统
 * 产生的日志文件是以当天日期命名的.txt文件
 * 处理的类型是 Warning、Critical、Fatal
 *
 * 不记录用户操作，即与historyAction不同
 *
 * @version 1.0
 * @date 2025/1/9
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <mutex>
#include <QCoreApplication>
#include <QDir>
#include <QMutex>

extern QtMessageHandler IcmaMessageHandler;

static QMutex mutex;
static QString logDir;

class LogOut final {
public:
  // 初始化日志目录
  static void initializeLog()
  {
    // 创建存放日志的目录
    const QDir dir;
    if (logDir = QApplication::applicationDirPath() + "/ICMALogDir";
      !dir.exists(logDir)) {
      if (dir.mkdir(logDir)) { qDebug() << "created log dir in:" << logDir; }
    }

    // 清理超出7天的日志（应用每次重启时清理日志）
    for (const auto& fileInfo : QDir(logDir).entryInfoList(
           QDir::Files | QDir::NoDotAndDotDot)) {
      if (QDate logFileDate = QDate::fromString(fileInfo.baseName(),
                                                "yyyy-MM-dd");
        logFileDate.addDays(7) < QDate::currentDate()) {
        QFile::remove(fileInfo.filePath());
      }
    }
  }

  // 自定义消息处理函数
  static void messageOutput(const QtMsgType type,
                            const QMessageLogContext& context,
                            const QString& msg)
  {
    const QString message = qFormatLogMessage(type, context, msg); ///< 格式化信息

    QMutexLocker locker(&mutex); ///< 确保线程安全
    // 创建当天日志文件
    if (type != QtDebugMsg) {
      const QString curDate = QDate::currentDate().toString("yyyy-MM-dd");
      if (QFile file(logDir + "/" + curDate + ".txt");
        file.open(QIODeviceBase::Append)) {
        file.write(message.toUtf8());
        file.close();
      }
    }
    else {
      qInstallMessageHandler(nullptr); ///< qDebug()日志让系统处理
    }
  }
};
