// /**
//  * @file FileTransTool
//  * @brief 中间件 给客户端和服务器提供方法
//  *
//  * 文件传输助手抽象出的工具类(中间件)
//  * 提供给aClient.h、aServer.h调用
//  *
//  * @author uxinghai
//  * @date 2024.11.2
//  */
//
// // 对于把bytearry写入流时最好使用writeRawData方法！！！
// // 读取时使用readRawData
// // 否则出错！！！！！！！！！！！！！！！
//
// #ifndef FILETRANSTOOL_H
// #define FILETRANSTOOL_H
//
// #include <QFileDialog>
// #include <QHostInfo>
// #include <QRegularExpression>
// #include <QStandardPaths>
// #include <QTcpServer>
// #include <QTcpSocket>
//
// // 消息类型
// enum class MessageType : quint8 {
//     Header,
//     Data
// };
//
// // 文件信息结构
// struct HeaderInfo {
//     QString fileName; // 文件名
//     qint64 fileSize;  // 文件大小
// };
//
// // 文件数据信息结构
// struct FileData {
//     quint32 dataSize; // 数据大小
//     QByteArray data;  // 数据块
// };
//
// class FileTransTool : public QObject {
//     Q_OBJECT
//
// public:
//     // 单例模式 维护唯一实例 由它发出信号
//     static FileTransTool &instance() {
//         static FileTransTool instance;
//         return instance;
//     }
//
//     // 传输状态
//     struct TransferStats {
//         qreal speed;                // 传输速度
//         qreal remainingTime;        // 剩余传输时间
//         QString curUnit, totalUnit; // 当前数据量的单位 总数据量的单位
//         qreal curDisplay, totalDisplay;
//     };
//     static const quint16 default_port = 9811;        // 默认端口号
//     static const quint32 perBytesToSend = 32 * 1024; // 一次支持发送的数据量(32KB)
//
//     /**
//      * @brief 序列化文件信息
//      * @param headInfo 文件信息（文件名长度、文件名、文件大小）
//      * @return 返回序列化后的byteArray(以MessageType::Header为开头)
//      * @note 类型是 quint8(0)<<QString<<qint64
//      */
//     static QByteArray serializeHeader(const HeaderInfo &headInfo) {
//         QByteArray block;
//         QDataStream out(&block, QIODevice::WriteOnly);
//         out << static_cast<quint8>(MessageType::Header)
//             << headInfo.fileName
//             << headInfo.fileSize;
//         return block;
//     }
//
//     /**
//      * @brief 反序列化文件信息
//      * @param in 被序列化的文件信息
//      * @return 返回文件信息结构
//      */
//     static HeaderInfo deserializeHeader(QByteArray &headerData) {
//         QDataStream in(&headerData, QIODevice::ReadOnly);
//         in.skipRawData(sizeof(quint8)); // 跳过消息类型
//         HeaderInfo info;
//         in >> info.fileName >> info.fileSize;
//         return info;
//     }
//
//     /**
//      * @brief 序列化文件数据
//      * @param data 文件元数据
//      * @return 返回序列化后的byteArray
//      * @note 类型是 quint8(1)<<dataSize<<data
//      */
//     static QByteArray serializeFileData(const FileData &fileData) {
//         QByteArray block;
//         QDataStream out(&block, QIODevice::WriteOnly);
//         out << static_cast<quint8>(MessageType::Data)
//             << fileData.dataSize;
//         // 对于把bytearry写入流时最好使用writeRawData方法！！！
//         out.writeRawData(fileData.data.constData(), fileData.data.size());
//         return block;
//     }
//
//     /**
//      * @brief 反序列文件数据
//      * @param filedata 被序列化后的数据
//      * @return 返回FileData
//      */
//     static FileData deserializeFileData(QByteArray &filedata) {
//         QDataStream in(&filedata, QIODevice::ReadOnly);
//         in.skipRawData(sizeof(quint8)); // 跳过消息类型
//         FileData fileData;
//         in >> fileData.dataSize;
//
//         QByteArray fileContent;
//         fileContent.resize(fileData.dataSize);
//         in.readRawData(fileContent.data(), fileData.dataSize);
//
//         fileData.data = fileContent;
//         return fileData;
//     }
//
//     /**
//      * @brief 是一个工具类，用来计算当前状态
//      * @param curBytes  当前数据量
//      * @param allBytes  总的数据量
//      * @param startTime 开始时间
//      * @return 返回一个 TransferStats 结构体
//      */
//     static TransferStats calculateStats(qint64 curBytes, qint64 allBytes, qint64 startTime) {
//         const qint64 elapsedSeconds = (QDateTime::currentMSecsSinceEpoch() - startTime) / 1000;
//         const double elapsedSecondsNonZero = std::max(1.0, static_cast<double>(elapsedSeconds));
//
//         TransferStats stats;
//         stats.speed = curBytes / 1024.0 / elapsedSecondsNonZero;
//         stats.remainingTime = (allBytes - curBytes) / 1024.0 / stats.speed;
//
//         const std::array<std::pair<qint64, QString>, 3> units = {{{1024 * 1024, "MB"},
//                                                                   {1024, "KB"},
//                                                                   {0, "B"}}};
//
//         auto it = find_if(units.begin(), units.end(),
//                           [allBytes](const auto &unit) { return allBytes >= unit.first; });
//
//         double divisor = std::max(1.0, static_cast<double>(it->first));
//         stats.curDisplay = curBytes / divisor;
//         stats.totalDisplay = allBytes / divisor;
//         stats.curUnit = stats.totalUnit = it->second;
//
//         return stats;
//     }
//
//     /**
//      * @brief 获取本机的IP地址
//      * @return 如果获取到非回环地址，返回非回环地址，否则返回回环地址
//      */
//     static QString getLocalIp() {
//         for (const auto &addr : QHostInfo::fromName(QHostInfo::localHostName()).addresses()) {
//             if (addr.toIPv4Address() && addr != QHostAddress::LocalHost)
//                 return addr.toString();
//         }
//         return "127.0.0.1";
//     }
//
//     /**
//      * @brief 使用正则表达式验证IPv4地址有效性
//      * @param ipAddr IPV4地址
//      * @return 返回有效与否
//      */
//     static bool IPIsVaild(const QString &ipAddr) {
//         // 使用static 修饰，不会报don't create temporary object
//         static QRegularExpression ipRegex(
//             "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
//             "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
//             "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
//             "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
//         return ipRegex.match(ipAddr).hasMatch();
//     }
//
//     /**
//      * @brief 使用文件对话框获取打开获取多个文件
//      * @return 获取到的所有文件路径
//      */
//     static QStringList getOpenFilesName() {
//         return QFileDialog::getOpenFileNames(
//             nullptr, tr("选择文件"), QDir::currentPath());
//     }
//
//     /**
//      * @brief 获取现存的目录（文件夹）
//      * @return 返回目录路径
//      */
//     static QString getExistingDirectory() {
//         return QFileDialog::getExistingDirectory(
//             nullptr, tr("保存"),
//             QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
//     }
//
// signals:
//     void TRANSFER_COMPLETE(); // 传输完成由AClient发出
//     void FILE_RECEIVED();     // 文件接收完成由AServer发出
//     void HEADER_RECEIVED();   // 标识头接收完成由AServer发出
//
// private:
//     FileTransTool() {} // 构造函数私有化
//     FileTransTool(const FileTransTool &) = delete;
//     FileTransTool &operator=(const FileTransTool &) = delete;
// };
//
// #endif // FILETRANSTOOL_H