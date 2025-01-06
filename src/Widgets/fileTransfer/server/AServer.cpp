// #include <QClipboard>       // 使用剪贴板
// #include <QDesktopServices> // 使用桌面服务
// #include <QDir>
// #include <QMenu>
// #include <QMessageBox>
//
// #include "../../../UI/ui_AServer.h"
// #include "../FileTransTool.h"
// #include "aserver.h"
//
//
// AServer::AServer(QWidget* parent)
//   : QMainWindow(parent), ui(new Ui::AServer), server(new QTcpServer(this)),
//     clientSocket(nullptr)
// {
//   ui->setupUi(this);
//   initUI();
//   setupConnections();
//
//   isHeader = true; // 初始时默认是标识头
// }
//
// AServer::~AServer()
// {
//   delete ui;
//   delete server;
//   delete clientSocket;
// }
//
// void AServer::initUI()
// {
//   setContextMenuPolicy(Qt::CustomContextMenu);
//   // 工具栏
//   ui->toolBar->addSeparator();
//   ui->toolBar->addWidget(new QLabel(tr("IP地址：") + FileTransTool::getLocalIp(),
//                                     this));
//
//   // 状态栏
//   ui->statusbar->addPermanentWidget(new QLabel(tr("传输模式：接收"), this));
//   statusLabel = new QLabel(tr("就绪"), this);
//   ui->statusbar->addWidget(statusLabel);
//
//   savePathLabel = new QLabel(tr("保存路径: %1").arg(QDir::currentPath()), this);
//   savePathLabel->setFixedWidth(300); // 设置显示宽度
//   savePathLabel->setWordWrap(true);  // 允许文字换行
//   ui->statusbar->addWidget(savePathLabel);
// }
//
// void AServer::setupConnections()
// {
//   server = new QTcpServer(this);
//   connect(server, &QTcpServer::newConnection, this, &AServer::doNewConnection);
//   connect(server, &QTcpServer::acceptError, this, &AServer::doServerError);
// }
//
// void AServer::on_actionListen_triggered()
// {
//   server->listen(QHostAddress::Any, FileTransTool::default_port);
//   statusLabel->setText(tr("等待发送方连接。"));
//   updateUI();
// }
//
// void AServer::on_actionDisConnect_triggered()
// {
//   if (server->isListening()) { server->close(); }
//   statusLabel->setText(tr("就绪"));
//   updateUI();
// }
//
// void AServer::updateUI()
// {
//   bool isListening = server->isListening();
//   ui->actionListen->setEnabled(!isListening);
//   ui->actionDisConnect->setEnabled(isListening);
//   ui->actionSetSavePath->setEnabled(!isListening);
// }
//
// void AServer::doNewConnection()
// {
//   statusLabel->setText(tr("成功与发送方连接."));
//   if (server->hasPendingConnections()) {
//     clientSocket = server->nextPendingConnection();
//     // 降低延迟选项会优化套接字并禁用Nagle's算法 设置为1表示启用
//     clientSocket->setSocketOption(QTcpSocket::LowDelayOption, 1);
//     connect(clientSocket, &QTcpSocket::readyRead, this,
//             &AServer::doSocketReadyRead);
//     connect(clientSocket, &QTcpSocket::errorOccurred, this,
//             &AServer::doSocketError);
//   }
// }
//
// // 处理接收到的数据
// void AServer::doSocketReadyRead()
// {
//   buffer += clientSocket->readAll();
//   processBuffer();
// }
//
// void AServer::processBuffer()
// {
//   while (!buffer.isEmpty()) {
//     int eof = buffer.indexOf("\n"); // 查找'\n'位置
//     if (eof == -1) {
//       return; // 等待更多数据
//     }
//     if (isHeader) {
//       // 使用 mid 来避免过多的拷贝
//       handleHeader(buffer.mid(0, eof));
//     } else { handleFileData(buffer.mid(0, eof + 1)); }
//     buffer.remove(0, eof + 1);
//   }
// }
//
// void AServer::handleHeader(const QByteArray& data)
// {
//   qDebug() << "标识头处理" << data;
//   auto createFile = [=](const QString& fileName) {
//     // 如果用户设定了路径，则使用用户设定的路径，否则按默认
//     QString filePath = fileSavePath.isEmpty()
//                          ? QDir::currentPath()
//                          : fileSavePath;
//     filePath = QDir(filePath).filePath(fileName);
//
//     curFile.setFileName(filePath); // 直接初始化 curFile，不用指针对象
//     if (!curFile.open(QIODevice::WriteOnly)) {
//       qWarning() << "无法打开文件进行写入:" << filePath;
//       QMessageBox::warning(this, tr("警告"), tr("无法创建文件: %1").arg(filePath));
//       return;
//     }
//     qDebug() << "新文件创建于:" << filePath;
//   };
//   auto addFileToListWidget = [=](const QString& fileName) {
//     auto* item = new QListWidgetItem(fileName);
//     item->setBackground(Qt::white);
//     item->setForeground(Qt::black);
//     ui->FileListView->addItem(item);
//   };
//
//   QString headerStr = QString::fromUtf8(data); // trimmed()会删除所有空白。哪怕是\n产生的
//   if (headerStr.startsWith("FILE_HEADER??")) {
//     QStringList header = headerStr.split("??");
//     if (header.size() == 3) {
//       curFileName = header[1];
//       totalBytes = header[2].toLongLong();
//       receivedBytes = 0;
//       transStartTime = QDateTime::currentMSecsSinceEpoch();
//       createFile(curFileName);
//       addFileToListWidget(curFileName);
//       isHeader = false;
//     }
//   } else if (headerStr == "FILE_COMPLETE") {
//     finalizeFileReceiving();
//     isHeader = true;
//     clientSocket->write("FILE_RECEIVED");
//   } else if (headerStr == "TRANSFER_COMPLETE") {
//     statusLabel->setText(tr("所有文件接收完成!"));
//     ui->lbStatus->setText(tr("接收完成"));
//   } else { qDebug() << "未知标识头:" << headerStr; }
// }
//
// void AServer::handleFileData(const QByteArray& data)
// {
//   qDebug() << "数据快处理" << data;
//   if (writeDataToFile(data)) {
//     receivedBytes += data.size(); // 已接收数据量
//     updateProgress(receivedBytes, totalBytes, curFileName, transStartTime);
//
//     if (receivedBytes >= totalBytes) {
//       isHeader = true;
//       finalizeFileReceiving();
//       clientSocket->write("FILE_RECEIVED");
//     }
//   } else {
//     qDebug("数据写入文件失败");
//     QMessageBox::critical(this, tr("错误"), tr("数据写入文件失败。"));
//   }
// }
//
// bool AServer::writeDataToFile(const QByteArray& data)
// {
//   if (!curFile.isOpen()) {
//     qWarning() << "尝试写入到未打开的文件";
//     return false;
//   }
//
//   // 传入多少写多少
//   qint64 written = curFile.write(data);
//   if (written != data.size()) {
//     qWarning() << "写入文件失败. 预期:" << data.size() << "实际:" << written;
//     return false;
//   }
//   return true;
// }
//
// void AServer::finalizeFileReceiving()
// {
//   if (curFile.isOpen()) {
//     curFile.flush();
//     curFile.close();
//     qDebug() << "文件已关闭:" << curFile.fileName();
//   }
// }
//
// void AServer::on_actionSetSavePath_triggered()
// {
//   fileSavePath = FileTransTool::getExistingDirectory();
//   savePathLabel->setText(tr("保存路径: %1").arg(fileSavePath));
// }
//
// void AServer::updateProgress(qint64 curBytes, qint64 allBytes,
//                              const QString& fileName, qint64 startTime)
// {
//   FileTransTool::TransferStats stats = FileTransTool::calculateStats(
//     curBytes, allBytes, startTime);
//
//   ui->lbStatus->setText(tr("接收中"));
//   ui->lbCurFile->setText(fileName);
//   ui->lbSize->setText(QString("%1 %2 / %3 %4")
//                       .arg(stats.curDisplay)
//                       .arg(stats.curUnit)
//                       .arg(stats.totalDisplay)
//                       .arg(stats.totalUnit));
//   ui->lbSpeed->setText(QString("%1 KB/s").arg(stats.speed));
//   ui->lbRemaingTime->setText(tr("%1 秒").arg(stats.remainingTime));
// }
//
// // 错误后续都改为中文显示
// void AServer::doServerError()
// {
//   QString errorMessage = tr("服务器错误: %1").arg(server->errorString());
//   QMessageBox::critical(this, tr("服务器错误"), errorMessage);
// }
//
// void AServer::doSocketError()
// {
//   QString errorMessage = tr("套接字错误: %1").arg(clientSocket->errorString());
//   QMessageBox::critical(this, tr("套接字错误"), errorMessage);
// }
//
// // 右键菜单
// void AServer::on_FileListView_customContextMenuRequested(const QPoint& pos)
// {
//   auto* item = ui->FileListView->itemAt(pos);
//   if (!item) { // 点击空白处不作处理
//     return;
//   }
//
//   // 显示菜单
//   auto* menu = new QMenu();
//
//   // 此处添加菜单项
//   menu->addAction(ui->actionOpenFile);
//   menu->addAction(ui->actionOpenPath);
//   menu->addAction(ui->actionCopyAbsoultPath);
//
//   menu->exec(QCursor::pos());
//   menu->deleteLater();
// }
//
// void AServer::on_actionOpenFile_triggered()
// {
//   int currentRow = ui->FileListView->currentRow();
//   if (currentRow < 0)
//     return;
//
//   QString fileName = ui->FileListView->currentItem()->text();
//   auto newpPath = QDir(fileSavePath).filePath(fileName);
//   openFileOrPath(newpPath);
// }
//
// void AServer::on_actionOpenPath_triggered() { openFileOrPath(fileSavePath); }
//
// void AServer::on_actionCopyAbsoultPath_triggered()
// {
//   int currentRow = ui->FileListView->currentRow();
//   if (currentRow < 0)
//     return;
//
//   QString fileName = ui->FileListView->currentItem()->text();
//   auto newpPath = QDir(fileSavePath).filePath(fileName);
//   // 验证文件是否存在
//   if (!fileIsExist(newpPath)) {
//     QMessageBox::critical(this, tr("错误"), tr("文件被移动或被删除."));
//   }
//   QString nativeFilePath = QDir::toNativeSeparators(newpPath);
//   QApplication::clipboard()->setText(nativeFilePath);
// }
//
// void AServer::openFileOrPath(const QString& filePath)
// {
//   // 验证文件是否存在
//   if (!fileIsExist(filePath)) {
//     QMessageBox::critical(this, tr("错误"), tr("文件被移动或被删除."));
//   }
//   // 自动识别路径打开
//   QString nativeFilePath = QDir::toNativeSeparators(filePath);
//   if (!QDesktopServices::openUrl(QUrl::fromLocalFile(nativeFilePath))) {
//     qDebug("Failed to open file or path.");
//   }
// }
//
// void AServer::on_FileListView_itemDoubleClicked(QListWidgetItem* item)
// {
//   if (!item)
//     return;
//
//   on_actionOpenFile_triggered();
// }
//
// bool AServer::fileIsExist(const QString& fileAbsoultPath)
// {
//   return QFile::exists(fileAbsoultPath);
// }
//
// void AServer::on_actionHelp_triggered()
// {
//   QString helpText = tr(
//     "<h2>文件传输工具（接收方）使用说明</h2>"
//     "<p>欢迎使用本文件传输工具。以下是基本使用步骤：</p>"
//     "<ol>"
//     "<li><b>开始监听：</b> 点击工具栏的'开始监听'按钮来等待发送方的连接。</li>"
//     "<li><b>设置保存路径：</b> 点击'设置保存路径'按钮选择接收文件的保存位置。</li>"
//     "<li><b>接收文件：</b> 连接建立后，文件将自动开始接收。</li>"
//     "</ol>"
//     "<h3>其他功能：</h3>"
//     "<ul>"
//     "<li><b>查看IP地址：</b> 您的IP地址显示在工具栏上，可以提供给发送方。</li>"
//     "<li><b>断开连接：</b> 点击'断开连接'按钮可以停止监听或断开当前连接。</li>"
//     "<li><b>文件列表：</b> 接收的文件会显示在主窗口的列表中。</li>"
//     "</ul>"
//     "<p>状态栏会显示当前的连接状态、保存路径和传输模式。</p>"
//     "<p>传输进度、当前文件名、文件大小、传输速度和剩余时间会在主窗口中实时更新。</p>"
//     "<p>如果遇到任何问题，请检查网络连接或联系技术支持。</p>"
//     "<p>致信开发者：uxinghaiwyi@163.com</p>");
//
//   QMessageBox::information(this, tr("使用帮助"), helpText);
// }
