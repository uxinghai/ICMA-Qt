/**
 * @file FileTransTool.h
 * @brief 中间件 给客户端和服务器提供方法
 *
 * 文件传输助手抽象出的工具类(中间件)
 * 提供给aClient.h、aServer.h调用
 *
 * @author uxinghai
 * @date 2024.11.2
 */

/**
 * 关于 bytearray 操作
 * 写入流时最好使用 writeRawData 方法
 * 读取时使用 readRawData
 */
#pragma once

#include <QFileDialog>
#include <QHostInfo>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTcpServer>

#include "../../Utils/Tools/DataUnitCalc.h"

using mySizeType = quint32;

/**
 * @brief 消息类型枚举
 */
enum class MessageType : quint8 {
  Header, ///< 头部信息
  Data,   ///< 文件数据
  Message ////< 回复消息
};

/**
 * @brief 文件信息结构体
 */
struct HeaderInfo {
  mySizeType byteArraySize; ///< 标识头结构信息大小
  QString fileName;         ///< 文件名
  mySizeType fileSize;      ///< 文件大小

  void print() const
  {
    qDebug() << "文件头信息：" << byteArraySize << fileName << fileSize;
  }
};

/**
 * @brief 文件数据结构体
 */
struct FileData {
  mySizeType dataSize;   ///< 数据大小
  QByteArray data;       ///< 数据块
  mySizeType structSize; ///< 文件数据结构大小
};

class FileTransTool;
static FileTransTool* instance = nullptr; ///< 共享的唯一实例

class FileTransTool final : public QObject {
  Q_OBJECT

public:
  /**
   * @brief 获取 FileTransTool 单例实例
   * @return FileTransTool 实例
   */
  static FileTransTool* getInstance()
  {
    if (instance == nullptr) { instance = new FileTransTool(); }
    return instance;
  }

  /**
   * @brief 传输状态结构体
   */
  struct TransferStats {
    qreal speed;                    ///< 传输速度 (KB/s)
    qreal remainingTime;            ///< 剩余时间 (秒)
    QString curUnit, totalUnit;     ///< 当前数据单位，总数据单位
    qreal curDisplay, totalDisplay; ///< 当前显示的数据量，总数据量
  };

  static constexpr quint16 default_port = 9811;        ///< 默认端口号
  static constexpr quint32 perBytesToSend = 32 * 1024; ///< 每次发送 32KB 数据

  /**
   * @brief 序列化文件头信息
   * @param headInfo 文件头信息
   * @return 序列化后的 QByteArray
   */
  static QByteArray serializeHeader(const HeaderInfo& headInfo)
  {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << static_cast<quint8>(MessageType::Header)
      << headInfo.byteArraySize
      << headInfo.fileName
      << headInfo.fileSize;
    headInfo.print();

    return block;
  }

  /**
   * @brief 反序列化文件头信息
   * @param headerData 序列化数据
   * @return 解析出的 HeaderInfo
   */
  static HeaderInfo deserializeHeader(QByteArray headerData)
  {
    HeaderInfo info;
    QDataStream in(&headerData, QIODevice::ReadOnly);

    quint8 messageType;
    in >> messageType;
    if (messageType != static_cast<quint8>(MessageType::Header)) {
      qWarning() << "Invalid message type in header";
      return {};
    }

    in >> info.byteArraySize >> info.fileName >> info.fileSize;
    info.print();
    return info;
  }

  /**
   * @brief 序列化文件数据
   * @param fileData 文件数据
   * @return 序列化后的 QByteArray
   */
  static QByteArray serializeFileData(const FileData& fileData)
  {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);

    out << static_cast<quint8>(MessageType::Data)
      << static_cast<mySizeType>(0) ///< 先占位 fileDataSize
      << fileData.dataSize;

    out.writeRawData(fileData.data.constData(), fileData.data.size());

    // 计算 fileDataSize 并回写
    const mySizeType fileDataSize = block.size();
    out.device()->seek(sizeof(quint8)); ///< 定位 fileDataSize 的写入位置
    out << fileDataSize;
    return block;
  }

  /**
   * @brief 反序列化文件数据
   * @param fileData 序列化后的数据
   * @return 解析出的 FileData
   */
  static FileData deserializeFileData(QByteArray fileData)
  {
    FileData info;
    QDataStream in(&fileData, QIODevice::ReadOnly);

    quint8 messageType;
    in >> messageType; // 读取消息类型
    if (messageType != static_cast<quint8>(MessageType::Data)) {
      qWarning() << "Invalid message type in file data";
      return {};
    }

    in >> info.structSize; // 读取 fileDataSize
    in >> info.dataSize;

    QByteArray fileContent;
    fileContent.resize(info.dataSize);
    in.readRawData(fileContent.data(), info.dataSize);
    info.data = fileContent;

    // 处理 `structSize`，确保读取完整
    if (fileData.size() >=
      static_cast<int>(sizeof(mySizeType) + in.device()->pos())) {
      in >> info.structSize;
    }
    else { info.structSize = 0; }
    return info;
  }

  /**
   * @brief 计算当前传输状态
   * @param curBytes 当前已传输字节数
   * @param allBytes 总字节数
   * @param startTime 传输开始时间戳 (毫秒)
   * @return 传输状态信息结构体
   */
  static TransferStats calculateStats(const qint64 curBytes, qint64 allBytes,
                                      const qint64 startTime)
  {
    const qint64 elapsedSeconds = (QDateTime::currentMSecsSinceEpoch() -
      startTime) / 1000;
    const double elapsedSecondsNonZero = std::max(
      1.0, static_cast<double>(elapsedSeconds));

    TransferStats stats;
    stats.speed = curBytes / 1024.0 / elapsedSecondsNonZero;
    stats.remainingTime = (allBytes - curBytes) / 1024.0 / stats.speed;

    stats.curUnit = stats.totalUnit = DataUnitCalc::getOnlyUnit(allBytes);
    const double divisor = DataUnitCalc::getDivisorByUnit(stats.curUnit);
    stats.curDisplay = curBytes / divisor;
    stats.totalDisplay = allBytes / divisor;

    return stats;
  }

  /**
   * @brief 获取本机 IP 地址
   * @return 返回 IPv4 地址 (若无非回环地址，则返回 127.0.0.1)
   */
  static QString getLocalIp()
  {
    for (const auto& addr : QHostInfo::fromName(QHostInfo::localHostName()).
         addresses()) {
      if (addr.toIPv4Address() && addr != QHostAddress::LocalHost)
        return addr.toString();
    }
    return "127.0.0.1";
  }

  /**
   * @brief 验证 IPv4 地址是否有效
   * @param ipAddr 需要验证的 IP 地址
   * @return 是否为有效的 IPv4 地址
   */
  static bool IPIsValid(const QString& ipAddr)
  {
    static QRegularExpression ipRegex(
      "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
      "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
      "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
      "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    return ipRegex.match(ipAddr).hasMatch();
  }

signals:
  void TRANSFER_COMPLETE(); ///< 传输完成信号 (由 AClient 发送)
  void FILE_RECEIVED();     ///< 文件接收完成信号 (由 AServer 发送)
  void HEADER_RECEIVED();   ///< 头部信息接收完成信号 (由 AServer 发送)

private:
  // 构造函数私有化，确保单例模式
  FileTransTool() {}
  FileTransTool(const FileTransTool&) = delete;
  FileTransTool& operator=(const FileTransTool&) = delete;
};
