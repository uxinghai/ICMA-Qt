// /**
//  * @file AClient.h
//  * @brief 文件传输的客户端头文件
//  *
//  * 该头文件是程序中的文件传输助手的客户端界面和实现
//  * 单独使用一个头文件设计利用后期拓展优化
//  *
//  * 自定义了标识头传输协议
//  * 格式为<文件名>??<文件大小>??
//  * 使用??分隔，是因为不会和文件名重名
//  *
//  * 先发送标识头 等待对方接收标识头回应信号
//  * 然后发送文件数据 再次等待对方全部接收完成的回应
//  * 最后发送下一个文件 直到全部发送完成（并发出所有文件全部发送信号）
//  *
//  * @author uxinghai
//  * @date 2024.9.19
//  */
//
// #ifndef ACLIENT_H
// #define ACLIENT_H
//
// #include <QFile>
// #include <QMainWindow>
// #include <QSet>
// #include <QTimer>
//
// class QLabel;
// class QLineEdit;
// class QTcpSocket;
//
// namespace Ui {
// class AClient;
// }
//
// class AClient : public QMainWindow {
//     Q_OBJECT
//
// public:
//     explicit AClient(QWidget *parent = nullptr);
//     ~AClient();
//
// private slots:
//     void on_FileListWidget_customContextMenuRequested(const QPoint &pos);
//     void on_actionConnect_triggered();    // 点击连接
//     void on_actionDisConnect_triggered(); // 点击断开
//     void on_actionSend_triggered();       // 点击发送
//     void on_actionAdd_triggered();        // 点击添加文件
//     void on_actionHelp_triggered();       // 点击帮助
//     void on_actionClearList_triggered();  // 点击清空列表(菜单项)
//     void on_actionRemove_triggered();     // 点击移除项(菜单项)
//
//     void doSocketConnected();    // 处理tcp连接
//     void doSocketError();        // 处理socket错误
//     void handleServerResponse(); // 处理aserver端发来的回应
//
// private:
//     void initUI();           // 初始化界面
//     void setupConnections(); // 建立相关信号槽链接
//
//     void updateUIStatus(const QString &isConnect); // 连接或者断开之后的UI更新
//
//     void sendData();                        // 发送文件数据
//     void sendNextFile();                    // 发送下一个文件
//     void sendFile(const QString &filePath); // 发送文件
//     void updateProgress(qint64 curBytes, qint64 allBytes, const QString &fileName, qint64 startTime);
//
//     Ui::AClient *ui;
//
//     QLabel *statusLabel;  // 状态标签
//     QLabel *fileCntLabel; // 文件数标签
//     QLineEdit *ipInput;   // Ip输入框
//
//     QTcpSocket *serverSocket;
//     QTimer sendTimer;
//
//     QSet<QString> filePaths; // 所有待传输文件
//     QFile curFile;           // 当前传输文件（工作文件） ps:不要用指针
//     QString curFileName;
//     qint64 curBytes, totalBytes;
//     qint64 transStartTime;
// };
//
// #endif // ACLIENT_H