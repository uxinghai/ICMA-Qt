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

#include <QApplication>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QMutex>

#define ICMALogDir "ICMALogDir"

extern QtMessageHandler IcmaMessageHandler;

static QMutex mutex;
inline QString TodayDate;

class LogOut final {
public:
  // 获取单例
  static LogOut& getInstance()
  {
    static auto instance = new LogOut();
    return *instance;
  }

  // 初始化日志目录
  void init() const
  {
    // 创建存放日志的目录
    if (const QDir dir; !dir.exists(ICMALogDir)) {
      if (dir.mkdir(ICMALogDir)) { qDebug() << "创建日志文件:" << ICMALogDir; }
    }

    const QString curDate = QDate::currentDate().toString("yyyy-MM-dd");
    TodayDate = curDate;
    if (QFile file(QString("%1/%2.txt").arg(ICMALogDir, TodayDate));
      file.open(QIODeviceBase::Append)) { file.close(); }

    if (clearLog7DaysAgo) {
      // 清理超出7天的日志（应用每次重启时清理日志）
      for (const auto& fileInfo : QDir(ICMALogDir).entryInfoList(
             QDir::Files | QDir::NoDotAndDotDot)) {
        if (QDate logFileDate = QDate::fromString(fileInfo.baseName(),
                                                  "yyyy-MM-dd");
          logFileDate.addDays(days) < QDate::currentDate()) {
          QFile::remove(fileInfo.filePath());
        }
      }
    }
  }

  // 自定义消息处理函数(处理QT日志)
  static void messageOutput(const QtMsgType type,
                            const QMessageLogContext& context,
                            const QString& msg)
  {
    const QString message = qFormatLogMessage(type, context, msg); ///< 格式化信息

    QMutexLocker locker(&mutex); ///< 确保线程安全
    // 创建当天日志文件
    if (type != QtDebugMsg) {
      writeLog(message);
    }
    else {
      qInstallMessageHandler(nullptr); ///< qDebug()日志让系统处理
    }
  }

  // 处理其他用户自定义日志 格式为当前日期加日志内容
  void log(const QString& message) const { writeLog(message); }

  // string 只支持 c_str()
  template <typename... Args>
  void logf(const char* format, const Args&... args) const
  {
    char buffer[8192];
    if (const int result = snprintf(buffer, sizeof(buffer), format, args...);
      result >= 0) {
      if (result < static_cast<int>(sizeof(buffer))) { log(QString::fromUtf8(buffer)); }
      else {
        QByteArray largeBuffer(result + 1, '\0');
        snprintf(largeBuffer.data(), largeBuffer.size(), format, args...);
        log(QString::fromUtf8(largeBuffer));
      }
    }
    else { log(QString("格式化日志消息错误: ") + QString::fromUtf8(format)); }
  }

  template <typename... Args>
  void logf(const QString& format, const Args&... args) const
  {
    logf(format.toUtf8().constData(), args...);
  }

  // TODO: 这个时间可配置
  void setClear7DaysAgo(const bool& enable) { clearLog7DaysAgo = enable; }

  ~LogOut()
  {
    //qInstallMessageHandler(IcmaMessageHandler); ///< 恢复系统日志处理
  }

private:
  static void writeLog(const QString& message)
  {
    const QString timeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    const QString formattedMessage = QString("[%1]: %2\n").arg(timeStr, message);

    const QString fileName = QString("./%1/%2.txt").arg(ICMALogDir, TodayDate);

    if (QFile file(fileName); file.open(QIODevice::Append | QIODevice::Text)) {
      file.write(formattedMessage.toUtf8());
      file.close();
    }
    else { qWarning() << "Failed to open log file:" << fileName; }
  }

  LogOut() = default;
  // 禁用构造方法
  Q_DISABLE_COPY_MOVE(LogOut);

  bool clearLog7DaysAgo = false; ///< 是否清理7天前的日志文件标志
  quint8 days = 7;               ///< 默认清理7天的日志文本(启动 clearLog7DaysAgo 的话)
};

// 宏定义局部 方便外部直接调用创建单例
#define sLog LogOut::getInstance()
