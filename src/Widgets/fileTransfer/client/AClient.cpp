#include <QLineEdit>
#include <QMenu>
#include <QMessageBox>
#include <QTcpSocket>
#include <synchapi.h>

#include "../../../../UI/ui_AClient.h"
#include "../FileTransTool.h"
#include "../ShareSrc.h"
#include "aclient.h"

AClient::AClient(QWidget* parent)
  : QMainWindow(parent),
    ui(new Ui::AClient)
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

  connect(FileTransTool::getInstance(), &FileTransTool::HEADER_RECEIVED,
          [this] {
            sendTimer.start(30); ///< 间隔30ms发送一段 一般20ms~50ms
          });
  // 计时器30ms触发一次 (作用：流量控制 避免拥塞堵塞) 确保了每一次Write之后能正常写入并被接收
  connect(&sendTimer, &QTimer::timeout, this, &AClient::sendData);

  connect(FileTransTool::getInstance(), &FileTransTool::FILE_RECEIVED,
          [this] { sendNextFile(); });
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

  serverSocket->connectToHost(QHostAddress(ip), FileTransTool::default_port);
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
    QMessageBox::information(this, tr("提示"), tr("请先添加文件。"));
    return;
  }

  ui->statusValue->setText(tr("准备传输"));
  sendNextFile();
}

void AClient::sendNextFile()
{
  if (filePaths.isEmpty()) { ///< 全部发送完成
    statusLabel->setText(tr("传输完成"));
    ui->statusValue->setText(tr("传输完成"));
    fileCntLabel->setText(tr("待传输文件个数: 0"));
    // 最后发出一个传输完成的信号
    emit FileTransTool::getInstance()->TRANSFER_COMPLETE();

    // 整个文件数据全部发送
    if (curBytes == totalBytes) {
      serverSocket->flush();
      curFile.close();
      sendTimer.stop();
    }
    return;
  }

  // 从文件列表中获取一个待传输文件
  const QString curFilePath = *filePaths.begin();
  filePaths.erase(filePaths.constBegin());
  sendFile(curFilePath);
}

void AClient::sendFile(const QString& filePath)
{
  // 初始化工作文件并打开
  if (curFile.isOpen()) { curFile.close(); }
  curFile.setFileName(filePath);
  if (!curFile.open(QIODevice::ReadOnly)) {
    qWarning() << "无法打开文件:" << filePath;
    sendNextFile();
    return;
  }

  // 获取文件元数据
  const QFileInfo info(filePath);
  const quint32 byteArraySize = sizeof(quint8) + ///< MessageType
    sizeof(quint32) +                            ///< byteArraySize
    sizeof(quint32) +                            ///< QString length
    info.fileName().size() * sizeof(QChar) +     ///< QString content
    sizeof(quint32);                             ///< fileSize

  const auto data = FileTransTool::serializeHeader({
    byteArraySize, info.fileName(), static_cast<quint32>(info.size())
  });
  if (const qint64 written = serverSocket->write(data);
    written > 0) {
    curFileName = info.fileName();
    curBytes = 0;
    totalBytes = info.size();
    transStartTime = QDateTime::currentMSecsSinceEpoch();
    return;
  }

  // 没有正常发出文件，尝试下一个文件
  sendNextFile();
}

void AClient::sendData()
{
  QCoreApplication::processEvents();
  // 这个 while 控制整个文件的所有数据发送
  while (curBytes < totalBytes) {
    // 尝试从文件中读取数据
    QByteArray chunk = curFile.read(FileTransTool::perBytesToSend);
    if (chunk.isEmpty()) { break; }

    qint64 bytesWritten = 0;                  ///< 已经写入数据量
    const qint64 bytesToWrite = chunk.size(); ///< 应写入的总数据量
    // 这个 while 控制当前数据块所有数据的发送
    while (bytesWritten < bytesToWrite) {
      QByteArray chunkData = chunk.data() + bytesWritten;
      auto data = FileTransTool::serializeFileData(
        {
          static_cast<quint32>(chunkData.size() + sizeof(quint8) + sizeof
            (quint32) +
            sizeof
            (quint32)),
          chunkData
        });
      const qint64 written = serverSocket->write(data);
      if (written < 0) {
        qDebug() << "写入 socket 错误:" << serverSocket->errorString();
        sendNextFile(); ///< 尝试发送下一个文件
        return;
      }
      bytesWritten += written;
    }

    curBytes += bytesToWrite;
    updateProgress(curBytes, totalBytes,
                   curFileName, transStartTime, true,
                   {
                     ui->statusValue, ui->currentFileValue,
                     ui->sizeValue, ui->speedValue, ui->remainingTimeValue
                   });
    for (int i = 0; i < ui->fileListWidget->count(); ++i) {
      if (QListWidgetItem* item = ui->fileListWidget->item(i);
        item->text() == curFileName) {
        item->setBackground(Qt::green);
        item->setForeground(Qt::black);
        break;
      }
    }
  }
}

// 成功建立连接
void AClient::doSocketConnected() const
{
  statusLabel->setText(tr("成功与接收方连接."));
}

// 后期改成使用中文提示
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
