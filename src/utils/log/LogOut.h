/**
 * @file LogOut
 * @brief 日志输出的头文件
 *
 * 该头文件用于实现重定向了debug等输出信息的日志输出
 * 产生的日志文件是以当天日期命名的.txt文件
 * 该文件只在Release模式下有效
 * 处理的类型是Debug、Warning、Critical、Fatal
 *
 * @author uxinghai
 * @date 2024.8.2
 */

#ifndef LOGOUT_H
#define LOGOUT_H

#include <QCoreApplication>
#include <QDir>
#include <QMutex>

// 获取日志目录路径
QString getLogDirPath() {
    auto logDir = QDir::currentPath();           // 获取exe文件所在路径
    logDir = QDir(logDir).filePath("../logDir"); // 上一级目录下的logDir
    logDir = QDir::toNativeSeparators(logDir);   // 转为系统原生路径格式
    return logDir;
}

// 初始化日志目录
void InitializeLog() {
    // 检查日志目录，不存在则创建
    QString logDir = getLogDirPath();
    QDir dir(logDir);
    if (!dir.exists()) {
        dir.mkdir(logDir); // mkdir会递归创建路径上一系列目录(如果没有)
    }

    // 删除超过7天的日志文件
    auto deadline = QDateTime::currentDateTime().addDays(-7); // 当前时间减7（7天前）
    auto fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);
    for (const auto &fileInfo : fileList) {
        if (fileInfo.birthTime() < deadline) {
            dir.remove(fileInfo.fileName());
        }
    }
}

// 自定义消息处理函数
void MyMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QMutex mutex;
    QMutexLocker locker(&mutex); // 保证多线程环境下安全访问

    // 根据消息类型选择前缀
    QString msgType;
    switch (type) {
    case QtWarningMsg:
        msgType = "Warning";
        break;
    case QtCriticalMsg:
        msgType = "Critical";
        break;
    case QtFatalMsg:
        msgType = "Fatal";
        break;
    case QtInfoMsg:
        msgType = "Info";
        break;
    case QtDebugMsg: // qDebug()信息不记入日志
        break;
    }

    // 格式化日志消息
    QString logMessage = QString("[%1] [file: %2] [line: %3] [datetime: %4] %5")
                             .arg(msgType)      // 消息类型
                             .arg(context.file) // 文件名
                             .arg(context.line) // 行号
                             .arg(QDateTime::currentDateTime()
                                      .toString("yyyy-MM-dd hh:mm:ss")) // 时间戳
                             .arg(msg);                                 // 消息内容

    // 获取日志文件路径（每天一个文件）
    QString logDir = getLogDirPath();
    QString logFileName = QString("%1.txt").arg(QDate::currentDate()
                                                    .toString("yyyy-MM-dd"));
    QString logFilePath = QDir(logDir).filePath(logFileName);

    // 追加日志到文件
    QFile file(logFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logMessage << "\n";
        file.close();
    }
}

#endif // LOGOUT_H