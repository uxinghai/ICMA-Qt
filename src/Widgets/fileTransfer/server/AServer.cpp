/**
 * AClient 发送完全正确，但是 AServer 接收端会多收一部分内容，导致异常
 */

#include <QClipboard>       ///< 使用剪贴板
#include <QDesktopServices> ///< 使用桌面服务
#include <QMenu>
#include <QMessageBox>
#include <qstorageinfo.h>
#include <QTcpSocket>

#include "../../../../UI/ui_AServer.h"
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
  connect(FileTransTool::getInstance(), &FileTransTool::TRANSFER_COMPLETE,
          [this] { finalizeFileReceiving(); });

  server = new QTcpServer(this);
  connect(server, &QTcpServer::newConnection, this, &AServer::doNewConnection);
  connect(server, &QTcpServer::acceptError, this, &AServer::doServerError);
}

bool AServer::doListen()
{
  if (!server->listen(QHostAddress::Any, FileTransTool::default_port)) {
    QMessageBox::critical(this, tr("监听错误"),
                          tr("无法在端口 %1 上启动服务器: %2").arg(
                            FileTransTool::default_port).arg(
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

  buffer.clear();
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

  statusLabel->setText(tr("成功与发送方连接"));
}

// 处理接收到的数据
void AServer::doSocketReadyRead()
{
  // 如果没有可用字节则返回
  const qint64 bytesAvailable = clientSocket->bytesAvailable();
  if (bytesAvailable <= 0) { return; }

  // 设置最大缓冲区大小以防止内存溢出
  static constexpr qint64 maxBufferSize = 100 * 1024 * 1024; ///< 100MB
  if (buffer.size() + bytesAvailable > maxBufferSize) {
    QMessageBox::critical(this, tr("缓冲区错误"), tr("接收缓冲区超出限制"));
    doDisConnect();
    return;
  }

  buffer += clientSocket->readAll();
  doProcessBuffer();
}

void AServer::doProcessBuffer()
{
  while (!buffer.isEmpty()) {
    if (buffer.size() < sizeof(quint8)) { return; }

    MessageType type;
    mySizeType byteArraySize;
    QDataStream in(&buffer, QIODevice::ReadOnly);
    in >> type >> byteArraySize;

    switch (type) {
    case MessageType::Header:
      {
        const QByteArray headerInfo = buffer.left(byteArraySize);
        buffer.remove(0, byteArraySize);

        auto [_,fileName, fileSize] =
          FileTransTool::deserializeHeader(headerInfo);

        if (fileName.isEmpty() || fileSize <= 0) {
          doDisConnect();
          return;
        }

        if (!doHeader(fileName, fileSize, byteArraySize)) {
          doDisConnect();
          return;
        }

        break;
      }
    case MessageType::Data:
      {
        if (buffer.size() < static_cast<int>(byteArraySize)) { return; }

        const QByteArray fileData = buffer.left(byteArraySize);
        buffer.remove(0, byteArraySize);

        if (!curFile.isOpen()) { return; }

        if (auto [dataSize, data, _]
            = FileTransTool::deserializeFileData(fileData);
          !doFileData(data, data.size(), byteArraySize)) {
          doDisConnect();
          return;
        }
        break;
      }

    default:
      buffer.clear();
      break;
    }
  }
}

bool AServer::doHeader(const QString& fileName, const qint64 fileSize,
                       const qint32 headerSize)
{
  Q_UNUSED(headerSize);
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

  emit FileTransTool::getInstance()->HEADER_RECEIVED();
  return true;
}

bool AServer::doFileData(const QByteArray& data,
                         const quint32 dataSize,
                         const quint32 filedataSize)
{
  Q_UNUSED(filedataSize);
  if (!curFile.isOpen()) {
    QMessageBox::critical(this, tr("文件错误"), tr("尝试写入到未打开的文件"));
    return false;
  }

  if (dataSize > FileTransTool::perBytesToSend) {
    QMessageBox::critical(this, tr("数据错误"), tr("接收到超出限制的数据包"));
    return false;
  }

  if (!writeDataToFile(data)) { return false; }

  receivedBytes += dataSize;
  updateProgress(receivedBytes, totalBytes,
                 curFileName, transStartTime, false,
                 {
                   ui->statusValue, ui->currentFileValue,
                   ui->sizeValue, ui->speedValue, ui->remainingTimeValue
                 });

  if (receivedBytes >= totalBytes) {
    finalizeFileReceiving();
    emit FileTransTool::getInstance()->FILE_RECEIVED();
  }

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
    buffer.clear(); // Clear any remaining data in buffer

    statusLabel->setText(tr("传输完成"));
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

// 错误后续都改为中文显示
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
