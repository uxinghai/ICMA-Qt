// #include "FileManage.h"
//
// #include <QClipboard>
// #include <QDesktopServices>
// #include <QDir>
// #include <QDirIterator>
// #include <QFileDialog>
// #include <QMessageBox>
// #include <QMutexLocker>
// #include <QSettings>
// #include <QTextEdit>
//
// // 报错cpp未引用时前置声明
// QString MainWindow::term;
// QFileInfoList MainWindow::res;
// QFileInfoList MainWindow::filterRes;
// QMutex MainWindow::mutex;
//
// qint32 MainWindow::handleFilesInDirectory(const QString& path)
// {
//   QDirIterator it(path, QDir::Files | QDir::NoDotAndDotDot,
//                   QDirIterator::Subdirectories);
//   qint32 count = 0;
//   QFileInfoList tempRes;
//
//   while (it.hasNext()) {
//     it.next();
//     tempRes << it.fileInfo();
//     ++count;
//   }
//
//   QMutexLocker locker(&mutex);
//   res.append(tempRes);
//   return count;
// }
//
// bool MainWindow::filterFilesInfo(const QFileInfo& fileInfo)
// {
//   QString baseName = fileInfo.baseName();
//   if (baseName.contains(term.toUtf8().data(), Qt::CaseInsensitive)) {
//     QMutexLocker locker(&mutex);
//     filterRes.append(fileInfo);
//     return true;
//   }
//   return false;
// }
//
// MainWindow::MainWindow(QWidget* parent)
//   : QMainWindow(parent), ui(new Ui::MainWindow)
// {
//   ui->setupUi(this);
//
//   progress = new QProgressBar(this);
//   progress->setMaximumHeight(15);
//   progress->setValue(0);
//   ui->statusbar->addPermanentWidget(progress);
//
//   lbLoad = new QLabel(this);
//   ui->statusbar->addWidget(lbLoad);
//
//   connect(&watcher, &QFutureWatcher<qint32>::progressRangeChanged, progress,
//           &QProgressBar::setRange);
//   connect(&watcher, &QFutureWatcher<qint32>::progressValueChanged, progress,
//           &QProgressBar::setValue);
//   connect(&watcher, &QFutureWatcher<qint32>::finished, this, [this]() {
//     qint32 result = future.result();
//     lbLoad->setText(tr("Total: %1 files.").arg(result));
//     initializeTableData(res);
//     updateUIForSearching(false);
//   });
//
//   connect(&watcher2, &QFutureWatcher<void>::progressRangeChanged, progress,
//           &QProgressBar::setRange);
//   connect(&watcher2, &QFutureWatcher<void>::progressValueChanged, progress,
//           &QProgressBar::setValue);
//   connect(&watcher2, &QFutureWatcher<void>::finished, this, [this]() {
//     lbLoad->setText(tr("Total: %1 files.").arg(filterRes.size()));
//     initializeTableData(filterRes);
//     updateUIForSearching(false);
//   });
//
//   // 启用右键菜单
//   ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
// }
//
// void MainWindow::on_btnBrowse_clicked()
// {
//   path = QFileDialog::getExistingDirectory(this, tr("Select Directory"),
//                                            QDir::currentPath());
//   ui->lePath->setText(path);
// }
//
// void MainWindow::initializeTableData(const QFileInfoList& list)
// {
//   ui->tableWidget->setRowCount(0);           ///< 清空表格
//   ui->tableWidget->setSortingEnabled(false); ///< 暂时禁用排序以提高插入效率
//   const int batchSize = 1000;                ///< 减小批处理大小
//   int totalRows = list.size();
//   qDebug("List中总的条数为: %d", totalRows);
//
//   // 分段分批加载
//   int currentRow = 0;
//   QTimer* timer = new QTimer(this);
//   /* mutable可变，即允许在 lambda 内部修改这些捕获的值的副本
//   默认情况下，按值捕获的 lambda 是常量的，这意味着它不能修改捕获的变量。
//   使用 mutable 关键字可以解除这个限制，但不会影响原本的变量*/
//   connect(timer, &QTimer::timeout, this, [=]() mutable {
//     int endRow = qMin(currentRow + batchSize, totalRows);
//     for (int i = currentRow; i < endRow; ++i) { createItems(i, list); }
//     // qDebug("当前处理到: %d, 本批结束于: %d", currentRow, endRow);
//     currentRow = endRow;
//
//     if (currentRow >= totalRows) {
//       timer->stop();
//       ui->tableWidget->setSortingEnabled(true); ///< 重新启用排序
//       qDebug("已经插入了: %d", ui->tableWidget->rowCount());
//       delete timer;
//     }
//   });
//   timer->setInterval(100); ///< 给系统0.1的缓冲时间
//   timer->start(0);
// }
//
// void MainWindow::createItems(int index, const QFileInfoList& list)
// {
//   int row = ui->tableWidget->rowCount();
//   ui->tableWidget->insertRow(row); // 始终在最后一行插入
//   auto createItem = [this
//     ](int row, int column, const QString& text, Type type) {
//     QTableWidgetItem* item = new QTableWidgetItem(text);
//     item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
//     item->setData(Qt::UserRole, static_cast<int>(type));
//     ui->tableWidget->setItem(row, column, item);
//   };
//
//   createItem(row, 0, list[index].completeBaseName(), Type::BaseName);
//   createItem(row, 1, list[index].path(), Type::Path);
//   createItem(row, 2, "." + list[index].suffix(), Type::Suffix);
//   createItem(row, 3, QString::number(list[index].size() / 1024) + " KB",
//              Type::Size);
//   createItem(
//     row, 4, list[index].lastModified().toString("yyyy/MM/dd hh:mm:ss A"),
//     Type::DateTime);
// }
//
// void MainWindow::on_btnSearch_clicked()
// {
//   if (path.isEmpty()) {
//     showErrorMessage(tr("The file path is empty!"));
//     return;
//   }
//
//   updateUIForSearching(true);
//   lbLoad->setText(tr("Loading..."));
//   progress->setRange(0, 0);
//
//   QStringList paths;
//   paths << path;
//
//   res.clear();
//   filterRes.clear();
//   ui->tableWidget->setRowCount(0);
//
//   future = QtConcurrent::mappedReduced(
//     paths, handleFilesInDirectory,
//     [](qint32& result, const qint32& intermediateResult) {
//       result += intermediateResult;
//     },
//     QtConcurrent::UnorderedReduce | QtConcurrent::SequentialReduce);
//   watcher.setFuture(future);
// }
//
// // 右键菜单
// void MainWindow::on_tableWidget_customContextMenuRequested(const QPoint& pos)
// {
//   Q_UNUSED(pos);
//   QMenu menu(this);
//   menu.addAction(ui->actOpen);
//   menu.addAction(ui->actOpenPath);
//   menu.addAction(ui->actCopy);
//   menu.addSeparator();
//   menu.addAction(ui->actAbout);
//   menu.addSeparator();
//   menu.addAction(ui->actVersion);
//   menu.exec(QCursor::pos());
// }
//
// void copyFilePathToClipboard(const QString& filePath)
// {
//   QString nativeFilePath = QDir::toNativeSeparators(filePath);
//   QApplication::clipboard()->setText(nativeFilePath);
// }
//
// void MainWindow::on_actOpen_triggered()
// {
//   int currentRow = ui->tableWidget->currentRow();
//   if (currentRow < 0)
//     return;
//
//   QString path = ui->tableWidget->item(currentRow, 1)->text();
//   QString fileName = QString("/%1%2").arg(
//     ui->tableWidget->item(currentRow, 0)->text(),
//     ui->tableWidget->item(currentRow, 2)->text());
//   openFileOrPath(path + fileName);
//   QString all = path + fileName;
//   qDebug() << all;
// }
//
// void MainWindow::on_actOpenPath_triggered()
// {
//   int currentRow = ui->tableWidget->currentRow();
//   if (currentRow < 0)
//     return;
//
//   QString filePath = ui->tableWidget->item(currentRow, 1)->text();
//   openFileOrPath(filePath);
// }
//
// void MainWindow::on_actCopy_triggered()
// {
//   int currentRow = ui->tableWidget->currentRow();
//   if (currentRow < 0)
//     return;
//
//   QString path = ui->tableWidget->item(currentRow, 1)->text();
//   QString fileName = QString("/%1%2").arg(
//     ui->tableWidget->item(currentRow, 0)->text(),
//     ui->tableWidget->item(currentRow, 2)->text());
//   copyFilePathToClipboard(path + fileName);
// }
//
// void MainWindow::on_tableWidget_itemDoubleClicked(QTableWidgetItem* item)
// {
//   if (!item)
//     return;
//
//   auto type = static_cast<Type>(item->data(Qt::UserRole).toInt());
//   if (type == Type::BaseName) { on_actOpen_triggered(); }
//   else if (type == Type::Path) { on_actOpenPath_triggered(); }
// }
//
// void MainWindow::updateUIForSearching(bool isSearching)
// {
//   ui->btnSearch->setEnabled(!isSearching);
//   ui->btnBrowse->setEnabled(!isSearching);
//   ui->lePath->setEnabled(!isSearching);
//   ui->lbTerm->setEnabled(!isSearching);
// }
//
// void MainWindow::showErrorMessage(const QString& message)
// {
//   QMessageBox::warning(this, tr("Error"), message);
// }
//
// void MainWindow::openFileOrPath(const QString& filePath)
// {
//   QString nativeFilePath = QDir::toNativeSeparators(filePath);
//   if (!QDesktopServices::openUrl(QUrl::fromLocalFile(nativeFilePath))) {
//     showErrorMessage("Failed to open file or path.");
//   }
// }
//
// void MainWindow::showFile(const QString& path)
// {
//   QFile readFile(path);
//   if (readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//     QTextStream in(&readFile);
//     QString content = in.readAll();
//
//     QTextEdit* text = new QTextEdit();
//     text->setPlainText(content);
//     text->setReadOnly(true);
//     text->setWindowTitle(tr("关于"));
//     text->setAttribute(Qt::WA_DeleteOnClose);
//     text->show();
//     readFile.close();
//   }
//   else { showErrorMessage("Failed to open file or path."); }
// }
//
// // 右键菜单结束
//
// void MainWindow::on_leTerm_textEdited(const QString& term)
// {
//   this->term = term;
//   filterRes.clear();
//   if (path.isEmpty())
//     return;
//   // 启用多线程对已有的res进行过滤
//   future2 = QtConcurrent::filtered(res, filterFilesInfo);
//   watcher2.setFuture(future2);
// }
//
// MainWindow::~MainWindow() = default;
