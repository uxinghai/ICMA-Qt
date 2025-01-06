// /**
//  * @file AServer.h
//  * @brief 文件传输的服务器端头文件
//  *
//  * 该头文件是程序中的文件传输助手的服务器端界面和实现
//  * 单独使用一个头文件设计利用后期拓展优化
//  *
//  * @author uxinghai
//  * @date 2024.9.19
//  */
//
// #ifndef ASERVER_H
// #define ASERVER_H
//
// #include <QFile>
// #include <QListWidgetItem>
// #include <QMainWindow>
//
// class QTcpServer;
// class QTcpSocket;
// class QLabel;
// namespace Ui {
// class AServer;
// }
//
// class AServer : public QMainWindow {
//     Q_OBJECT
//
// public:
//     explicit AServer(QWidget *parent = nullptr);
//     ~AServer();
//
// private slots:
//     void on_actionListen_triggered();      // 点击监听
//     void on_actionDisConnect_triggered();  // 点击断开
//     void on_actionSetSavePath_triggered(); // 点击设置保存路径
//     void on_actionHelp_triggered();        // 点击帮助
//
//     void doNewConnection();   // 处理新连接
//     void doServerError();     // 处理服务器错误
//     void doSocketError();     // 处理套接字错误
//     void doSocketReadyRead(); // 处理数据读取
//
//     void on_FileListView_customContextMenuRequested(const QPoint &pos);
//     void openFileOrPath(const QString &filePath); // 辅助函数
//     void on_actionOpenFile_triggered();           // 点击打开文件
//     void on_actionOpenPath_triggered();           // 点击打开路径
//     void on_actionCopyAbsoultPath_triggered();    // 点击复制路径
//     void on_FileListView_itemDoubleClicked(QListWidgetItem *item);
//     bool fileIsExist(const QString &fileAbsoultPath);
//
// private:
//     void initUI();           // 初始化界面
//     void setupConnections(); // 建立相关信号槽链接
//     void updateUI();         // 根据客户端监听状态更新界面
//
//     void updateProgress(qint64 curBytes, qint64 allBytes, const QString &fileName, qint64 startTime);
//     void finalizeFileReceiving();
//     bool writeDataToFile(const QByteArray &data);
//
//     void handleHeader(const QByteArray &data);
//     void handleFileData(const QByteArray &data);
//     void processBuffer();
//
//     Ui::AServer *ui;
//     bool isHeader;         // 是否接收到标识头的标记
//     QLabel *statusLabel;   // 状态标签
//     QLabel *savePathLabel; // 保存路径标签
//
//     QTcpServer *server;
//     QTcpSocket *clientSocket; // 与客户端（发送方）进行通信
//     QByteArray buffer;        // 用于存储未完全处理的数据
//     QFile curFile;            // 当前接收文件（工作文件）
//     QString curFileName;
//     qint64 totalBytes;
//     qint64 receivedBytes;
//     QString fileSavePath;
//
//     qint64 transStartTime; // 记录每次传输开始时间以便更新进度
// };
//
// #endif // ASERVER_H