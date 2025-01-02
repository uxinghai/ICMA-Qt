// #include "aclient.h"
//
// #include <synchapi.h>
//
// #include <QMenu>
// #include <QMessageBox>
//
// #include "lib/FileTransTool.h"
// #include "ui_aclient.h"
//
// AClient::AClient(QWidget *parent)
//     : QMainWindow(parent), ui(new Ui::AClient) {
//     ui->setupUi(this);
//     initUI();
//     setupConnections();
// }
//
// AClient::~AClient() {
//     delete ui;
// }
//
// void AClient::initUI() {
//     setContextMenuPolicy(Qt::CustomContextMenu);
//
//     // 工具栏
//     ui->toolBar->addSeparator();
//     ipInput = new QLineEdit(this);
//     ipInput->setPlaceholderText(tr("请输入接收方IP地址"));
//     ui->toolBar->addWidget(ipInput);
//
//     // 状态栏
//     statusLabel = new QLabel(tr("就绪"), this);
//     ui->statusbar->addWidget(statusLabel);
//
//     fileCntLabel = new QLabel(tr("待传输文件个数: 0"), this);
//     ui->statusbar->addWidget(fileCntLabel);
//     ui->statusbar->addPermanentWidget(new QLabel(tr("传输模式：发送"), this));
// }
//
// void AClient::setupConnections() {
//     /**
//      * 实例化serverSocket(与server(接收方)的socket连接)并且监听相应信号
//      * 1、处理连接; 2、处理错误; 3、处理回馈
//      */
//     serverSocket = new QTcpSocket(this);
//     connect(serverSocket, &QTcpSocket::connected, this, &AClient::doSocketConnected);
//     connect(serverSocket, &QTcpSocket::errorOccurred, this, &AClient::doSocketError);
//     connect(serverSocket, &QTcpSocket::readyRead, this, &AClient::handleServerResponse);
//
//     // 计时器30ms触发一次 (作用：流量控制 避免拥塞堵塞) 确保了每一次Write之后能正常写入并被接收
//     connect(&sendTimer, &QTimer::timeout, this, &AClient::sendData);
// }
//
// void AClient::on_actionAdd_triggered() {
//     auto addItemsToView = [=]() { // 把所有待传输文件显示在界面列表上
//         ui->FileListWidget->clear();
//         for (auto it = filePaths.constBegin(); it != filePaths.constEnd(); ++it) {
//             QFileInfo info(*it);
//             QString suffix = info.suffix().toLower(); // 因为资源文件名都是小写
//             QString iconPath = ":/suffix/res/suffix/" + suffix + ".png";
//             ui->FileListWidget->addItem(new QListWidgetItem(QIcon(iconPath), info.fileName()));
//         }
//         fileCntLabel->setText(tr("待传输文件个数: %1").arg(filePaths.size()));
//     };
//
//     QStringList files = FileTransTool::getOpenFilesName();
//     filePaths.unite(QSet<QString>(files.begin(), files.end()));
//     addItemsToView();
// }
//
// void AClient::on_FileListWidget_customContextMenuRequested(const QPoint &pos) {
//     if (!ui->FileListWidget->count()) {
//         return; // 没有待传输的项 不处理右键
//     }
//
//     // 获取右键的项
//     auto *item = ui->FileListWidget->itemAt(pos);
//     QMenu menu;
//     if (item) { // 右键位置不是空白(确保移除操作正确)
//         menu.addAction(ui->actionRemove);
//     }
//     menu.addAction(ui->actionClearList);
//     menu.exec(QCursor::pos());
//     menu.deleteLater();
// }
//
// void AClient::on_actionClearList_triggered() {
//     ui->FileListWidget->clear();
//     filePaths.clear();
//     fileCntLabel->setText(tr("待传输文件个数: 0"));
// }
//
// void AClient::on_actionRemove_triggered() {
//     // 获取当前鼠标选中的项
//     QListWidgetItem *item = ui->FileListWidget->currentItem();
//     if (!item) {
//         return;
//     }
//
//     // 获取选中项下标并移除
//     int index = ui->FileListWidget->row(item);
//     delete ui->FileListWidget->takeItem(index);
//
//     if (filePaths.isEmpty()) {
//         return; // 文件列表为空 不操作filePaths
//     }
//     auto it = filePaths.constBegin();
//     // 序列容器 如vector、list 可以使用 重载+号运算符来进行指针位移
//     std::advance(it, index); // set容器使用advance指针前移
//     filePaths.erase(it);
//
//     fileCntLabel->setText(tr("待传输文件个数: %1").arg(filePaths.size()));
// }
//
// void AClient::on_actionConnect_triggered() {
//     QString ip = ipInput->text();
//     if (!FileTransTool::IPIsVaild(ip)) {
//         QMessageBox::critical(this, tr("错误"), tr("接收方IP地址无效."));
//         return;
//     }
//
//     serverSocket->connectToHost(QHostAddress(ip), FileTransTool::default_port);
//     if (!serverSocket->waitForConnected(3000)) { // 最多等待3秒
//         QMessageBox::critical(this, tr("错误"), tr("连接错误: %1").arg(serverSocket->errorString()));
//         return;
//     }
//     updateUIStatus("Connect");
// }
//
// void AClient::on_actionDisConnect_triggered() {
//     serverSocket->disconnectFromHost();
//     updateUIStatus("disConnect");
// }
//
// /**
//  * TCP文件传输发送核心代码
//  * 自定义了协议、发送顺序
//  */
// void AClient::on_actionSend_triggered() {
//     ui->lbStatus->setText(tr("准备传输"));
//     if (filePaths.isEmpty()) {
//         QMessageBox::information(this, tr("提示"), tr("请先添加文件。"));
//         return;
//     }
//     sendNextFile();
// }
//
// void AClient::sendNextFile() {
//     if (filePaths.isEmpty()) { // 全部发送
//         statusLabel->setText(tr("传输完成!"));
//         ui->lbStatus->setText(tr("传输完成"));
//         fileCntLabel->setText(tr("待传输文件个数: 0"));
//         serverSocket->write("TRANSFER_COMPLETE\n"); // 最后发出一个传输完成的信号
//     } else {
//         QString currentFile = *filePaths.begin();
//         filePaths.erase(filePaths.constBegin());
//         sendFile(currentFile);
//     }
// }
//
// void AClient::sendFile(const QString &filePath) {
//     // 初始化工作文件并打开
//     curFile.setFileName(filePath);
//     if (!curFile.open(QIODevice::ReadOnly)) {
//         qWarning() << "无法打开文件:" << filePath;
//         sendNextFile();
//         return;
//     }
//
//     // 获取文件元数据
//     QFileInfo info(filePath);
//     QString header = QString("FILE_HEADER??%1??%2\n").arg(info.fileName()).arg(info.size());
//     qint64 written = serverSocket->write(header.toUtf8());
//
//     if (written > 0) {
//         qDebug() << "客户端发送标识头:" << header;
//         curFileName = info.fileName();
//         curBytes = 0;
//         totalBytes = info.size();
//         transStartTime = QDateTime::currentMSecsSinceEpoch();
//         sendTimer.start(30); // 间隔30ms发送一段 一般20ms~50ms
//     } else {
//         qDebug("标识头没有正确被发出，尝试发送下一个文件。");
//         curFile.close();
//         sendNextFile();
//     }
// }
//
// void AClient::sendData() {
//     QByteArray buffer;
//     while (curBytes < totalBytes) {
//         // 从工作文件中读取最大长度为perBytesToSend的数据
//         QByteArray chunk = curFile.read(FileTransTool::perBytesToSend);
//         if (chunk.isEmpty()) {
//             break; // 没有正常读取
//         }
//
//         // 在每个数据块后添加 \n
//        buffer = chunk + '\n';
//         qDebug() << "数据块发送 " << chunk;
//         // tcp write 不一定一次性发出，所以循环等待，确保全部发出
//         qint64 bytesWritten = 0;             // 已经写入数据量
//         qint64 bytesToWrite = buffer.size(); // 要写入的总数据量
//         while (bytesWritten < bytesToWrite) {
//             // 参数1给是要传输的数据，从buffer中偏移到了正确位置。参数2是写入的数据量
//             qint64 written = serverSocket->write(buffer.data() + bytesWritten, bytesToWrite - bytesWritten);
//             if (written < 0) {
//                 qDebug() << "写入 socket 错误:" << serverSocket->errorString();
//                 curFile.close();
//                 sendNextFile(); // 尝试发送下一个文件
//                 return;
//             }
//             bytesWritten += written;
//         }
//
//         curBytes += chunk.size(); // 注意这里使用chunk.size()而不是bytesWritten
//         updateProgress(curBytes, totalBytes, curFileName, transStartTime);
//         QCoreApplication::processEvents(); // 保持界面流畅 不卡顿冻结
//     }
//
//     if (curBytes == totalBytes) {
//         serverSocket->flush();
//         curFile.close();
//         sendTimer.stop();
//         serverSocket->write("FILE_COMPLETE\n"); // 发出当前文件传输完成的信号
//         // 等待一小段时间确保 FILE_COMPLETE 被发送，然后继续下一个文件
//         QTimer::singleShot(100, this, &AClient::sendNextFile);
//     } else {
//         curFile.close();
//         sendNextFile(); // 尝试发送下一个文件
//     }
// }
//
// /**
//  * @brief AClient::handleServerResponse
//  * 只对接收方发回的FILE_RECEIVED信号做操作
//  */
// void AClient::handleServerResponse() {
//     if (serverSocket->readAll() == "FILE_RECEIVED") {
//         sendNextFile();
//     }
// }
//
// // 成功建立连接
// void AClient::doSocketConnected() {
//     statusLabel->setText(tr("成功与接收方连接."));
// }
//
// // 后期改成使用中文提示
// void AClient::doSocketError() {
//     QMessageBox::critical(this, tr("错误"), tr("套接字错误: %1").arg(serverSocket->errorString()));
// }
//
// void AClient::updateProgress(qint64 curBytes, qint64 allBytes, const QString &fileName, qint64 startTime) {
//     FileTransTool::TransferStats stats = FileTransTool::calculateStats(curBytes, allBytes, startTime);
//
//     ui->lbCurFile->setText(fileName);
//     ui->lbSize->setText(QString("%1 %2 / %3 %4")
//                             .arg(stats.curDisplay)
//                             .arg(stats.curUnit)
//                             .arg(stats.totalDisplay)
//                             .arg(stats.totalUnit));
//     ui->lbSpeed->setText(QString("%1 KB/s").arg(stats.speed));
//     ui->lbRemaingTime->setText(tr("%1 秒").arg(stats.remainingTime));
//
//     for (int i = 0; i < ui->FileListWidget->count(); ++i) {
//         QListWidgetItem *item = ui->FileListWidget->item(i);
//         if (item->text() == fileName) {
//             item->setBackground(Qt::green);
//             item->setForeground(Qt::black);
//             break;
//         }
//     }
// }
//
// void AClient::updateUIStatus(const QString &isConnect) {
//     bool _isConnect = false;
//     if (isConnect == "Connect") {
//         _isConnect = true;
//     }
//     ui->actionConnect->setEnabled(!_isConnect);
//     ui->actionDisConnect->setEnabled(_isConnect);
//     ui->actionSend->setEnabled(_isConnect);
//     ui->actionAdd->setEnabled(_isConnect);
// }
//
// void AClient::on_actionHelp_triggered() {
//     QString helpText = tr(
//         "<h2>文件传输工具（发送方）使用说明</h2>"
//         "<p>欢迎使用本文件传输工具。以下是基本使用步骤：</p>"
//         "<ol>"
//         "<li><b>添加文件：</b> 点击工具栏的'添加文件'选项来选择要传输的文件。</li>"
//         "<li><b>设置接收方IP：</b> 在工具栏的输入框中输入接收方的IP地址。</li>"
//         "<li><b>连接：</b> 点击'连接'按钮与接收方建立连接。</li>"
//         "<li><b>发送文件：</b> 连接成功后，点击'发送'按钮开始传输文件。</li>"
//         "</ol>"
//         "<h3>其他功能：</h3>"
//         "<ul>"
//         "<li><b>移除文件：</b> 右键点击文件列表中的文件，选择'移除'选项。</li>"
//         "<li><b>清空列表：</b> 使用右键菜单中的'清空列表'选项可以清除所有待传输文件。</li>"
//         "<li><b>断开连接：</b> 传输完成后，可以点击'断开连接'按钮终止与接收方的连接。</li>"
//         "</ul>"
//         "<p>状态栏会显示当前的连接状态、待传输文件数量和传输模式。</p>"
//         "<p>如果遇到任何问题，请检查网络连接或联系技术支持。</p>"
//         "<p>致信开发者：uxinghaiwyi@163.com</p>");
//
//     QMessageBox::information(this, tr("使用帮助"), helpText);
// }