/**
 * @file AServer.h
 * @brief 文件传输的服务器端头文件
 *
 * 该头文件是程序中的文件传输助手的服务器端界面和实现
 * 单独使用一个头文件设计利用后期拓展优化
 *
 * @author uxinghai
 * @date 2024.9.19
 */
#pragma once

#include <QFile>
#include <QListWidgetItem>
#include <QMainWindow>

class QTcpServer;
class QTcpSocket;
class QLabel;

namespace Ui
{
  class AServer;
}

class AServer final : public QMainWindow {
  Q_OBJECT

public:
  explicit AServer(QWidget* parent = nullptr);
  ~AServer() override;

signals:
  void WindowClose();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  bool doListen();                ///< 点击监听
  void doDisConnect();            ///< 点击断开
  void doSetSavePath();           ///< 点击设置保存路径
  void doOpenSavePath() const;    ///< 打开保存位置
  void on_actionHelp_triggered(); ///< 点击帮助

  void doNewConnection();   ///< 处理新连接
  void doServerError();     ///< 处理服务器错误
  void doSocketError();     ///< 处理套接字错误
  void doSocketReadyRead(); ///< 处理数据读取

private:
  void initUI();           ///< 初始化界面
  void setupConnections(); ///< 建立相关信号槽链接
  void updateUI() const;   ///< 根据客户端监听状态更新界面


  void finalizeFileReceiving();
  bool writeDataToFile(const QByteArray& data);

  bool doHeader(const QString& fileName, qint64 fileSize, qint32 headerSize);
  bool doFileData(const QByteArray& data, quint32 dataSize, quint32 filedataSize);
  void doProcessBuffer();

  Ui::AServer* ui;

  QLabel* statusLabel;   //< 状态标签
  QLabel* savePathLabel; //< 保存路径标签

  QTcpServer* server;
  QTcpSocket* clientSocket; ///< 与客户端（发送方）进行通信
  QByteArray buffer;        ///< 用于存储未完全处理的数据
  QFile curFile;            ///< 当前接收文件（工作文件）
  QString curFileName;
  qint64 totalBytes;
  qint64 receivedBytes;
  QString fileSavePath;

  qint64 transStartTime; ///< 记录每次传输开始时间以便更新进度
};
