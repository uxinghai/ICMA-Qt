// /**
// * @file FileTransfer.h
//  * @brief 文件传输助手界面的头文件
//  *
//  * 该头文件定义了 `FileTrans` 类，用于程序中的文件传输助手界面。
//  * 提供用户选择是否作为服务器或客户端启动的功能，并启动相应的传输模式。
//  *
//  * @version 0.2
//  * @date 2024.11.1
//  *
//  * @author uxinghai
//  * @copyright Copyright (c) 2024
//  */
//
// #ifndef FILETRANSFER_H
// #define FILETRANSFER_H
//
// #include <QSharedPointer>
// #include <QWidget>
//
// class AServer;
// class AClient;
// namespace Ui {
//   class FileTrans;
// }
//
// class FileTrans : public QWidget {
//   Q_OBJECT
//
// public:
//   explicit FileTrans(QWidget *parent = nullptr);
//   ~FileTrans();
//
//   private slots:
//       /**
//        * @brief 处理用户点击“发送方”按钮的槽函数
//        *
//        * 该槽函数连接到“发送方”按钮，用户点击后，
//        * 程序将启动客户端模式，以便进行文件发送操作。
//        */
//       void on_btnSender_clicked();
//
//   /**
//    * @brief 处理用户点击“接收方”按钮的槽函数
//    *
//    * 该槽函数连接到“接收方”按钮，用户点击后，
//    * 程序将启动服务器模式，以便接收文件。
//    */
//   void on_btnReciver_clicked();
//
// private:
//   Ui::FileTrans *ui;
//   QSharedPointer<AServer> aServer; // 管理服务器实例的智能指针
//   QSharedPointer<AClient> aClient; // 管理客户端实例的智能指针
// };
//
// #endif // FILETRANSFER_H