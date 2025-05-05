/**
 * 接收端代码 - 重写以解决多收一部分内容导致异常的问题
 */

#include <QClipboard>       ///< 使用剪贴板
#include <QDesktopServices> ///< 使用桌面服务
#include <QMenu>
#include <QMessageBox>
#include <qstorageinfo.h>
#include <QTcpSocket>

#include "../../../../UI/ui_AServer.h"
#include "../../../Utils/Tools/LogOut.h"
#include "../FileTransTool.h"
#include "../ShareSrc.h"
#include "aserver.h"

AServer::AServer(QWidget* parent)
  : QMainWindow(parent),
    ui(new Ui::AServer),
    server(new QTcpServer(this)),
    clientSocket(nullptr)
{
  ui->setupUi(this);
  initUI();
  setupConnections();
}

void AServer::initUI()
{
  setContextMenuPolicy(Qt::CustomContextMenu);
  // 工具栏
  ui->toolBar->addSeparator();
  const auto lb = new QLabel(tr("IP地址：") + FileTransTool::getLocalIp(),
                             this);
  lb->setTextInteractionFlags(Qt::TextSelectableByMouse);
  ui->toolBar->addWidget(lb);

  // 状态栏
  ui->statusBar->addPermanentWidget(new QLabel(tr("传输模式：接收"), this));
  statusLabel = new QLabel(tr("就绪"), this);
  ui->statusBar->addWidget(statusLabel);

  savePathLabel = new QLabel(tr("保存路径: %1").arg(QDir::currentPath()), this);
  savePathLabel->setFixedWidth(300); ///< 设置显示宽度
  savePathLabel->setWordWrap(true);  ///< 允许文字换行
  ui->statusBar->addWidget(savePathLabel);
}

void AServer::setupConnections()
{
  connect(ui->actionListen, &QAction::triggered, this, &AServer::doListen);
  connect(ui->actionDisconnect, &QAction::triggered, this,
          &AServer::doDisConnect);
  connect(ui->actionSetSavePath, &QAction::triggered, this,
          &AServer::doSetSavePath);
  connect(ui->actionOpenSavePath, &QAction::triggered, this,
          &AServer::doOpenSavePath);

  server = new QTcpServer(this);
  connect(server, &QTcpServer::newConnection, this, &AServer::doNewConnection);
  connect(server, &QTcpServer::acceptError, this, &AServer::doServerError);
}

bool AServer::doListen()
{
  if (!server->listen(QHostAddress::Any, default_port)) {
    QMessageBox::critical(this, tr("监听错误"),
                          tr("无法在端口 %1 上启动服务器: %2").arg(
                            default_port).arg(
                            server->errorString()));
    return false;
  }
  statusLabel->setText(tr("等待发送方连接。"));
  updateUI();
  return true;
}

void AServer::doDisConnect()
{
  if (clientSocket) {
    clientSocket->disconnectFromHost();
    if (clientSocket->state() != QAbstractSocket::UnconnectedState) {
      clientSocket->waitForDisconnected();
    }
    delete clientSocket;
    clientSocket = nullptr;
  }

  if (server->isListening()) { server->close(); }

  if (curFile.isOpen()) { curFile.close(); }

  dataBuffer.clear();
  statusLabel->setText(tr("就绪"));
  updateUI();
}

void AServer::updateUI() const
{
  const bool isListening = server->isListening();
  ui->actionListen->setEnabled(!isListening);
  ui->actionDisconnect->setEnabled(isListening);
  ui->actionSetSavePath->setEnabled(!isListening);
}

void AServer::doNewConnection()
{
  if (!server->hasPendingConnections()) { return; }

  // 如果已经有连接，拒绝新的连接
  if (clientSocket) {
    QTcpSocket* newConnection = server->nextPendingConnection();
    newConnection->disconnectFromHost();
    newConnection->deleteLater();
    return;
  }

  clientSocket = server->nextPendingConnection();
  if (!clientSocket) { return; }

  clientSocket->setSocketOption(QTcpSocket::LowDelayOption, 1);
  connect(clientSocket, &QTcpSocket::readyRead, this,
          &AServer::doSocketReadyRead);
  connect(clientSocket, &QTcpSocket::errorOccurred, this,
          &AServer::doSocketError);
  connect(clientSocket, &QTcpSocket::disconnected, this, [this]() {
    statusLabel->setText(tr("发送方断开连接"));
    finalizeFileReceiving();
    clientSocket->deleteLater();
    clientSocket = nullptr;
  });

  dataBuffer.clear();
  statusLabel->setText(tr("成功与发送方连接"));
}

// 处理接收到的数据
void AServer::doSocketReadyRead()
{
  if (!clientSocket) { return; }

  dataBuffer.append(clientSocket->readAll());

  // 循环处理缓冲区中的所有完整消息
  while (processNextMessage()) {
    // 处理成功，继续处理下一个消息
  }
}

bool AServer::processNextMessage()
{
  // 确保缓冲区至少有一个字节用于消息类型
  if (dataBuffer.size() < 1) { return false; }

  // 读取命令类型
  switch (const quint8 commandType = static_cast<quint8>(dataBuffer.at(0))) {
  case 1: // 文件头信息
    return processFileHeader();

  case 2: // 文件数据块
    return processFileData();

  case 3: // 文件结束标记
    return processFileEnd();

  case 0xFF:                      // 特殊标记，所有文件传输完成
    if (dataBuffer.size() >= 5) { // 标记类型(1) + 32位值(4)
      QDataStream stream(dataBuffer);
      quint8 type;
      quint32 marker;
      stream >> type >> marker;

      if (marker == 0xFFFFFFFF) {
        // 所有文件传输完成
        dataBuffer.remove(0, 5);
        finalizeFileReceiving();
        return true;
      }
    }
    return false;

  default:
    // 未知命令类型，清空缓冲区避免死循环
    qWarning() << "接收到未知命令类型:" << commandType;
    dataBuffer.clear();
    return false;
  }
}

bool AServer::processFileHeader()
{
  // 确保缓冲区中有足够的数据
  QDataStream stream(dataBuffer);
  stream.setVersion(QDataStream::Qt_5_15);

  // 读取命令类型
  quint8 commandType;
  stream >> commandType;

  // 尝试读取文件名
  QString fileName;
  stream >> fileName;

  sLog.logf("接收方收到发送方传输的文件名称：%s", fileName);

  // 检查数据流状态
  if (stream.status() != QDataStream::Ok) {
    return false; // 数据不完整，等待更多数据
  }

  // 尝试读取文件大小
  quint64 fileSize;
  stream >> fileSize;

  sLog.logf("接收方收到发送方传输的文件名称：%s，大小：%d 字节", fileName.toLocal8Bit(), fileSize);

  // 再次检查数据流状态
  if (stream.status() != QDataStream::Ok) {
    return false; // 数据不完整，等待更多数据
  }

  // 计算已读取的字节数
  int bytesRead = stream.device()->pos();

  // 从缓冲区删除已处理的数据
  dataBuffer.remove(0, bytesRead);

  // 处理文件头信息
  return startReceivingFile(fileName, fileSize);
}

bool AServer::processFileData()
{
  if (!curFile.isOpen()) {
    // 当前没有文件处理
    dataBuffer.clear();
    return false;
  }

  // 确保缓冲区中至少有命令类型和数据大小信息
  if (dataBuffer.size() < 5) { // 1字节命令 + 4字节大小
    return false;
  }

  QDataStream stream(dataBuffer);
  stream.setVersion(QDataStream::Qt_5_15);

  // 跳过命令类型
  quint8 commandType;
  stream >> commandType;

  // 读取数据块大小
  quint32 dataSize;
  stream >> dataSize;

  // 检查是否有完整的数据块
  if (dataBuffer.size() < static_cast<int>(5 + dataSize)) {
    return false; // 等待更多数据
  }

  // 提取文件数据
  QByteArray fileData = dataBuffer.mid(5, dataSize);

  // 从缓冲区删除已处理的数据
  dataBuffer.remove(0, 5 + dataSize);

  // 写入文件
  if (!writeDataToFile(fileData)) { return false; }

  // 更新接收进度
  receivedBytes += dataSize;
  updateProgress(receivedBytes, totalBytes,
                 curFileName, transStartTime, false,
                 {
                   ui->statusValue, ui->currentFileValue,
                   ui->sizeValue, ui->speedValue, ui->remainingTimeValue
                 });

  return true;
}

bool AServer::processFileEnd()
{
  // 确保缓冲区中有足够的数据
  QDataStream stream(dataBuffer);
  stream.setVersion(QDataStream::Qt_5_15);

  // 读取命令类型
  quint8 commandType;
  stream >> commandType;

  // 尝试读取文件名
  QString fileName;
  stream >> fileName;

  // 检查数据流状态
  if (stream.status() != QDataStream::Ok) {
    return false; // 数据不完整，等待更多数据
  }

  // 计算已读取的字节数
  int bytesRead = stream.device()->pos();

  // 从缓冲区删除已处理的数据
  dataBuffer.remove(0, bytesRead);

  // 完成当前文件接收
  finalizeFileReceiving();
  return true;
}

bool AServer::startReceivingFile(const QString& fileName, const qint64 fileSize)
{
  if (fileSize <= 0) {
    QMessageBox::critical(this, tr("文件错误"), tr("接收到无效的文件大小"));
    return false;
  }

  if (fileName.isEmpty() || fileName.contains("..") || fileName.contains('/')) {
    QMessageBox::critical(this, tr("文件错误"), tr("接收到无效的文件名"));
    return false;
  }

  curFileName = fileName;
  totalBytes = fileSize;
  receivedBytes = 0;
  transStartTime = QDateTime::currentMSecsSinceEpoch();

  QString filePath = fileSavePath.isEmpty()
                       ? QDir::currentPath()
                       : fileSavePath;
  filePath = QDir(filePath).filePath(fileName);

  if (const QStorageInfo storage(QFileInfo(filePath).absolutePath());
    storage.bytesAvailable() < fileSize) {
    QMessageBox::critical(this, tr("存储空间错误"),
                          tr("磁盘空间不足，需要 %1 MB，但只有 %2 MB 可用")
                          .arg(fileSize / 1024.0 / 1024.0, 0, 'f', 2)
                          .arg(storage.bytesAvailable() / 1024.0 / 1024.0, 0,
                               'f', 2));
    return false;
  }

  if (curFile.isOpen()) { curFile.close(); }

  curFile.setFileName(filePath);
  if (!curFile.open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, tr("文件错误"),
                          tr("无法打开文件进行写入: %1\n错误: %2").arg(
                            filePath, curFile.errorString()));
    return false;
  }

  statusLabel->setText(tr("正在接收文件: %1").arg(fileName));
  return true;
}

bool AServer::writeDataToFile(const QByteArray& data)
{
  if (!curFile.isOpen()) { return false; }

  if (const qint64 written = curFile.write(data);
    written != data.size()) {
    QMessageBox::critical(this, tr("写入错误"),
                          tr("写入文件失败\n预期: %1 字节\n实际: %2 字节\n错误: %3")
                          .arg(data.size())
                          .arg(written)
                          .arg(curFile.errorString()));

    return false;
  }

  return true;
}

void AServer::finalizeFileReceiving()
{
  if (curFile.isOpen()) {
    curFile.flush();
    curFile.close();

    statusLabel->setText(tr("文件接收完成: %1").arg(curFileName));
    qDebug() << "传输完成 - 文件名:" << curFile.fileName()
      << "最终接收字节数:" << receivedBytes
      << "预期总字节数:" << totalBytes;
  }
}

void AServer::doSetSavePath()
{
  fileSavePath = QFileDialog::getExistingDirectory(this, tr("选择保存路径"));
  if (fileSavePath.isEmpty()) { return; }
  savePathLabel->setText(tr("保存路径: %1").arg(fileSavePath));
}

void AServer::doOpenSavePath() const
{
  if (fileSavePath.isEmpty()) {
    QDesktopServices::openUrl(QUrl::fromLocalFile(QDir::currentPath()));
    return;
  }
  QDesktopServices::openUrl(QUrl::fromLocalFile(fileSavePath));
}

void AServer::doServerError()
{
  QString errorMessage = tr("服务器错误: %1").arg(server->errorString());
  QMessageBox::critical(this, tr("服务器错误"), errorMessage);
}

void AServer::doSocketError()
{
  const QString errorMessage = tr("套接字错误: %1").arg(clientSocket->errorString());
  QMessageBox::critical(this, tr("套接字错误"), errorMessage);
}

void AServer::on_actionHelp_triggered()
{
  QMessageBox::information(this, tr("使用帮助"), getHelpContext(false));
}

void AServer::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
  QMainWindow::closeEvent(event);
}

AServer::~AServer()
{
  delete ui;
  delete clientSocket;
}
