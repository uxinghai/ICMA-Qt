#pragma once

#include <QFile>
#include <QMainWindow>
#include <QSet>
#include <QTimer>

QT_BEGIN_NAMESPACE

class QLabel;
class QLineEdit;
class QTcpSocket;

namespace Ui
{
  class AClient;
}

QT_END_NAMESPACE

class AClient final : public QMainWindow {
  Q_OBJECT

public:
  explicit AClient(QWidget* parent = nullptr);
  ~AClient() override;

signals:
  void WindowClose();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void doContextMenuRequested(const QPoint& pos) const;
  void doConnect();          ///< 点击连接
  void doDisConnect() const; ///< 点击断开
  void doSend();             ///< 点击发送
  void doAddFiles();         ///< 点击添加文件
  void doHelp();             ///< 点击帮助
  void doClearList();        ///< 点击清空列表(菜单项)
  void doRemove();           ///< 点击移除项(菜单项)

  void doSocketConnected() const; ///< 处理tcp连接
  void doSocketError();           ///< 处理socket错误

private:
  void initUI();           ///< 初始化界面
  void setupConnections(); ///< 建立相关信号槽链接

  void updateUIStatus(const bool& isConnect) const; ///< 连接或者断开之后的UI更新

  void sendData();                        ///< 发送文件数据
  void sendNextFile();                    ///< 发送下一个文件
  void sendFile(const QString& filePath); ///< 发送文件

  Ui::AClient* ui;

  QLabel* statusLabel;      ///< 状态标签
  QLabel* fileCntLabel;     ///< 文件数标签
  QLineEdit* ipInput;       ///< 嵌入工具栏的 IP 地址输入框
  QTcpSocket* serverSocket; /// 用于与 AServer 端通信的 Socket
  QTimer sendTimer;
  QSet<QString> filePaths; ///< 所有待传输文件
  QFile curFile;           ///< 当前传输文件（工作文件） ps:不要用指针
  QString curFileName;
  qint64 curBytes, totalBytes;
  qint64 transStartTime;
};
