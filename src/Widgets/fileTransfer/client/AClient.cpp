#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QTcpSocket>
#include <synchapi.h>

#include "../../../../UI/ui_AClient.h"
#include "../../../Utils/Tools/LogOut.h"
#include "../FileTransTool.h"
#include "../ShareSrc.h"
#include "aclient.h"

AClient::AClient(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::AClient)
{
  ui->setupUi(this);
  initUI();
  setupConnections();
}

void AClient::initUI()
{
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  // 工具栏
  ui->toolBar->addSeparator();
  ipInput = new QLineEdit(this);
  ipInput->setPlaceholderText(tr("请输入接收方IP地址"));
  ui->toolBar->addWidget(ipInput);

  // 状态栏
  statusLabel = new QLabel(tr("就绪"), this);
  ui->statusBar->addWidget(statusLabel);

  fileCntLabel = new QLabel(tr("待传输文件个数: 0"), this);
  ui->statusBar->addWidget(fileCntLabel);
  ui->statusBar->addPermanentWidget(new QLabel(tr("传输模式：发送"), this));
}

void AClient::setupConnections()
{
  // 工具栏 Action 的信号槽连接
  connect(ui->actionConnect, &QAction::triggered, this, &AClient::doConnect);
  connect(ui->actionDisconnect, &QAction::triggered, this,
          &AClient::doDisConnect);
  connect(ui->actionAddFiles, &QAction::triggered, this, &AClient::doAddFiles);
  connect(ui->fileListWidget, &QListWidget::customContextMenuRequested, this,
          &AClient::doContextMenuRequested);
  connect(ui->actionSend, &QAction::triggered, this, &AClient::doSend);
  connect(ui->actionHelp, &QAction::triggered, this, &AClient::doHelp);

  // 通信连接
  serverSocket = new QTcpSocket(this);
  connect(serverSocket, &QTcpSocket::connected, this,
          &AClient::doSocketConnected);
  connect(serverSocket, &QTcpSocket::errorOccurred, this,
          &AClient::doSocketError);
  connect(serverSocket, &QTcpSocket::bytesWritten, this, &AClient::onBytesWritten);

  // 传输控制
  connect(&transferTimer, &QTimer::timeout, this, &AClient::continueTransfer);
}

void AClient::doAddFiles()
{
  QStringList files = QFileDialog::getOpenFileNames(this, tr("选择文件"),
                                                    QDir::currentPath(),
                                                    tr("所有文件 (*)"));
  filePaths.unite(QSet(files.begin(), files.end()));
  addItemsToView(ui->fileListWidget, filePaths);
  fileCntLabel->setText(tr("待传输文件个数: %1").arg(filePaths.size()));
}

void AClient::doConnect()
{
  const QString ip = ipInput->text();
  if (!FileTransTool::IPIsValid(ip)) {
    QMessageBox::critical(this, tr("错误"), tr("接收方IP地址无效."));
    return;
  }

  serverSocket->connectToHost(QHostAddress(ip), default_port);
  if (!serverSocket->waitForConnected(300)) { return; }
  updateUIStatus(true);
}

void AClient::doDisConnect() const
{
  serverSocket->disconnectFromHost();
  updateUIStatus(false);
}

void AClient::doSend()
{
  // 无待传输文件
  if (filePaths.isEmpty()) {
    sLog.log("没有添加待发送的文件");
    QMessageBox::information(this, tr("提示"), tr("请先添加文件。"));
    return;
  }

  ui->statusValue->setText(tr("准备传输"));
  isTransferring = false;
  transferNextFile();
}

// 新的文件传输实现
void AClient::transferNextFile()
{
  if (filePaths.isEmpty()) { // 全部发送完成
    statusLabel->setText(tr("传输完成"));
    ui->statusValue->setText(tr("传输完成"));
    fileCntLabel->setText(tr("待传输文件个数: 0"));

    if (curFile.isOpen()) { curFile.close(); }

    transferTimer.stop();
    isTransferring = false;

    // 发送传输完成标记
    QByteArray endMarker;
    QDataStream endStream(&endMarker, QIODevice::WriteOnly);
    endStream << 0xFFFFFFFF; // 特殊标记，表示所有文件传输完成
    serverSocket->write(endMarker);

    return;
  }

  // 从文件列表中获取一个待传输文件
  const QString curFilePath = *filePaths.begin();
  sLog.logf("传输文件:%s", curFilePath);

  filePaths.erase(filePaths.constBegin());
  sendFile(curFilePath);
}

void AClient::sendFile(const QString& filePath)
{
  // 初始化工作文件并打开
  if (curFile.isOpen()) { curFile.close(); }
  curFile.setFileName(filePath);
  if (!curFile.open(QIODevice::ReadOnly)) {
    sLog.logf("无法打开文件: %s，尝试发出下一个", filePath);
    transferNextFile();
    return;
  }

  // 获取文件元数据
  const QFileInfo info(filePath);
  curFileName = info.fileName();
  curBytes = 0;
  totalBytes = info.size();
  transStartTime = QDateTime::currentMSecsSinceEpoch();

  // 发送文件头信息
  QByteArray headerData;
  QDataStream headerStream(&headerData, QIODevice::WriteOnly);
  headerStream.setVersion(QDataStream::Qt_5_15);

  // 命令标识 (1: 新文件)
  headerStream << static_cast<quint8>(1);
  // 文件名长度和内容
  headerStream << curFileName;
  // 文件大小
  headerStream << static_cast<quint64>(totalBytes);

  sLog.logf("发送方正在发出文件：%s, 大小：%d 字节", curFileName.toLocal8Bit(), totalBytes);
  // 发送头信息
  serverSocket->write(headerData);
  // 等待头信息写入完成后再开始传输文件内容
  isTransferring = false;
  waitingForHeader = true;
}

void AClient::onBytesWritten(qint64 bytes)
{
  Q_UNUSED(bytes);

  // 如果正在等待头信息写入完成
  if (waitingForHeader) {
    waitingForHeader = false;
    // 开始文件传输
    isTransferring = true;
    transferTimer.start(10); // 10ms间隔控制传输速度
    return;
  }

  // 普通数据块写入完成，可以继续传输
  if (isWaitingForWrite) {
    isWaitingForWrite = false;
    if (isTransferring) { continueTransfer(); }
  }
}

void AClient::continueTransfer()
{
  if (!isTransferring || isWaitingForWrite) { return; }

  // 如果当前文件已经传输完毕
  if (curBytes >= totalBytes) {
    completeCurrentFile();
    return;
  }

  // 读取下一块数据
  QByteArray dataBlock;
  QDataStream dataStream(&dataBlock, QIODevice::WriteOnly);
  dataStream.setVersion(QDataStream::Qt_5_15);

  // 命令标识 (2: 文件数据)
  dataStream << (quint8)2;

  // 读取文件数据
  QByteArray fileData = curFile.read(qMin((qint64)perBytesToSend, totalBytes - curBytes));

  // 写入数据大小和内容
  dataStream << (quint32)fileData.size();
  dataBlock.append(fileData);

  // 发送数据
  qint64 written = serverSocket->write(dataBlock);
  if (written <= 0) {
    QMessageBox::critical(this, tr("传输错误"), tr("无法发送数据块"));
    transferTimer.stop();
    isTransferring = false;
    return;
  }

  // 更新进度
  curBytes += fileData.size();
  updateProgress(curBytes, totalBytes,
                 curFileName, transStartTime, true,
                 {
                   ui->statusValue, ui->currentFileValue,
                   ui->sizeValue, ui->speedValue, ui->remainingTimeValue
                 });

  // 更新文件列表中的显示
  for (int i = 0; i < ui->fileListWidget->count(); ++i) {
    QListWidgetItem* item = ui->fileListWidget->item(i);
    if (item && item->text() == curFileName) {
      item->setBackground(Qt::green);
      item->setForeground(Qt::black);
      break;
    }
  }

  // 流量控制 - 等待写入完成
  isWaitingForWrite = true;
}

void AClient::completeCurrentFile()
{
  if (curFile.isOpen()) { curFile.close(); }

  // 发送文件结束标记
  QByteArray endFileMarker;
  QDataStream endStream(&endFileMarker, QIODevice::WriteOnly);
  endStream.setVersion(QDataStream::Qt_5_15);

  // 命令标识 (3: 文件结束)
  endStream << (quint8)3;
  endStream << curFileName;

  serverSocket->write(endFileMarker);

  // 停止当前文件传输
  isTransferring = false;
  transferTimer.stop();

  // 等待一小段时间后继续传输下一个文件
  QTimer::singleShot(200, this, &AClient::transferNextFile);
}

// 成功建立连接
void AClient::doSocketConnected() const { statusLabel->setText(tr("成功与接收方连接.")); }

void AClient::doSocketError()
{
  QMessageBox::critical(this, tr("错误"),
                        tr("套接字错误: %1").arg(serverSocket->errorString()));
}

void AClient::updateUIStatus(const bool& isConnect) const
{
  ui->actionConnect->setEnabled(!isConnect);
  ui->actionDisconnect->setEnabled(isConnect);
  ui->actionSend->setEnabled(isConnect);
  ui->actionAddFiles->setEnabled(isConnect);
}

// 右键菜单项操作
void AClient::doContextMenuRequested(const QPoint& pos) const
{
  // 没有待传输的项则不处理右键
  if (!ui->fileListWidget->count()) { return; }

  // 获取右键的项
  const auto* item = ui->fileListWidget->itemAt(pos);
  const auto menu = std::make_unique<QMenu>();

  connect(ui->actionClearList, &QAction::triggered,
          this, &AClient::doClearList, Qt::SingleShotConnection);
  connect(ui->actionRemoveFile, &QAction::triggered,
          this, &AClient::doRemove, Qt::SingleShotConnection);

  if (item) { // 右键位置不是空白(确保移除操作正确)
    menu->addAction(ui->actionRemoveFile);
  }
  menu->addAction(ui->actionClearList);

  menu->exec(QCursor::pos());
}

void AClient::doClearList()
{
  ui->fileListWidget->clear();
  filePaths.clear();
  fileCntLabel->setText(tr("待传输文件个数: 0"));
}

void AClient::doRemove()
{
  // 获取所有选中的项
  const auto selectItems = ui->fileListWidget->selectedItems();
  for (auto it = selectItems.constBegin(); it != selectItems.constEnd(); ++it) {
    // 获取当前选中项
    const QListWidgetItem* item = *it;
    if (!item) { continue; }

    // 获取选中项下标并移除
    const int index = ui->fileListWidget->row(item);
    delete ui->fileListWidget->takeItem(index);

    auto filePathsIt = filePaths.constBegin();
    // 序列容器 如vector、list 可以使用 重载+号运算符来进行指针位移
    std::advance(filePathsIt, index); ///< set容器使用advance指针前移
    filePaths.erase(filePathsIt);
  }

  fileCntLabel->setText(tr("待传输文件个数: %1").arg(filePaths.size()));
}

void AClient::doHelp()
{
  QMessageBox::information(this, tr("使用帮助"), getHelpContext(false));
}

void AClient::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
  QMainWindow::closeEvent(event);
}

AClient::~AClient()
{
  qDebug() << "文件传输发送方被正常关闭";
  delete ui;
}
