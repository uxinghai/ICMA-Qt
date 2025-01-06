#include "MainWindow.h"

#include <QActionGroup>
#include <QKeyEvent>
#include <QTimer>
#include <QTranslator>

#include "../../../UI/ui_MainWindow.h"
#include "../../controls/messagebox/MyMesgBox.h"
#include "../../dataBase/worker/FilesDBWorker.h"
#include "../fileTransfer/FileTransfer.h"
#include "../photoShop/PS.h"
//#include "../../initial/AppInit.h"

extern QTranslator tran;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow),
    lbStatus(new QLabel(this))
   // appInit(std::make_unique<AppInit>())
{
  ui->setupUi(this);

  setupConnections();
}

// 初始化界面
void MainWindow::doInit()
{

  qDebug() << "收到信号，准备初始化界面";
}

void MainWindow::setupConnections()
{
  connect(ui->actionNewWindow, &QAction::triggered,
          this, &MainWindow::doCreateANewWindow);
  connect(ui->actionFilter, &QAction::triggered,
          this, &MainWindow::doComBoxVisible);
  connect(ui->actionPreview, &QAction::triggered,
          this, &MainWindow::doPreviewVisible);
  connect(ui->actionStatusBar, &QAction::triggered,
          this, &MainWindow::doStatusBarVisible);

  // connect(appInit.get(), &AppInit::initMainWindowUI,
  //         this, &MainWindow::doInit);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  // // 如果不再询问为True 直接关闭并退出
  // QJsonObject obj = JsonManager::loadConfig()["settings"].toObject();
  // if (obj["general"].toObject()["closeNoRequire"].toBool()) {
  //   event->accept();
  //   return;
  // }
  //
  // auto* mesgBox = new MyMesgBox(this);
  // if (mesgBox->exec() == QDialog::Accepted) {
  //   AppInit::writeInJsonConfig(*this); // 接受引用所以指针
  //   // 如果勾选了不再询问 则写入Json
  //   if (mesgBox->isCloseNoRequirChecked()) {
  //     // 找到修改的根
  //     QJsonObject root = JsonManager::loadConfig();
  //     auto settingsObj = root["settings"].toObject();
  //     auto generalObj = settingsObj["general"].toObject();
  //
  //     // 修改值
  //     generalObj["closeNoRequire"] = true;
  //
  //     // 写回
  //     settingsObj["general"] = generalObj;
  //     root["settings"] = settingsObj;
  //
  //     JsonManager::JsonObjWriteInFile(root);
  //   }
  //   event->accept();
  // }
  // else { event->ignore(); }
}

// 打开一个新的窗口
void MainWindow::doCreateANewWindow() const
{
  const auto w = new MainWindow();                 ///< 创建一个自身对象
  w->move(QPoint(this->x() + 15, this->y() + 20)); ///< 突出新增
  w->show();
}

// 过滤器 Combox 显示/隐藏
void MainWindow::doComBoxVisible(const bool& checked) const
{
  ui->comBoxFilter->setVisible(checked);
}

// 预览窗口显示/隐藏
void MainWindow::doPreviewVisible(const bool& checked) const
{
  ui->lbPreview->setVisible(checked);
}

// 状态栏显示/隐藏
void MainWindow::doStatusBarVisible(const bool& checked) const
{
  ui->statusbar->setVisible(checked);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) {
    this->close(); // 关闭窗口
    return;
  }
  QMainWindow::keyPressEvent(event); // 调用父类的默认处理
}

// // 导入文件(支持多选)
// void MainWindow::on_actiondaori_triggered()
// {
//   ui->actiondaori->setEnabled(false);
//   // 导入的多个文件
//   QString filter = tr(
//     "所有(*);;图片(*.png *.xpm *.jpg);;"
//     "文本文件(*.txt);;C++(*.cpp;*.cc;*.c;*cxx;*.c++;*.h)");
//   auto temp = QFileDialog::getOpenFileNames(this, tr("选择文件"),
//                                             QDir::currentPath(), filter);
//   decltype(temp) files; // 过滤无后缀文件
//   for (const auto& file : temp) {
//     QFileInfo fileInfo(file);
//     if (!fileInfo.suffix().isEmpty()) { files << file; }
//   }
//
//   // 处理选中的文件或文件夹
//   if (!files.isEmpty()) {
//     QProgressBar* progress = new QProgressBar();
//     progress->setFixedSize(200, 10);
//     progress->setRange(0, 0); // 形成加载中的样式
//     lbStatus->setText(tr("正在导入文件."));
//     ui->statusbar->addWidget(lbStatus);
//     ui->statusbar->addWidget(progress);
//
//     // 使用文件数据库工具来导入到数据库
//     FilesDBWorker* dbWorker = new FilesDBWorker(files, this); // 处理文件列表
//     connect(dbWorker, &FilesDBWorker::resultReady,
//             this, [this, progress](const qint32& nums) {
//               lbStatus->setText(tr("已导入%1个对象").arg(nums));
//               displayOnView(progress);
//             });
//     dbWorker->start();
//   }
//   else { ui->actiondaori->setEnabled(true); }
// }
//
// void MainWindow::displayOnView(QProgressBar* progress)
// {
//   auto show = [](QTableView* view) {
//     extern QString DataBasePath;
//     if (SqlManager::instance().openDatabase(DataBasePath)) {
//       qCritical("Failed to open database in displayOnView function!");
//       return;
//     }
//
//     auto* model = new QSqlQueryModel();
//     QString selectAll = QStringLiteral(
//       "SELECT file_name,file_path,file_size,"
//       "file_type,creation_date,modification_date,"
//       "last_access_date,md5_hash,CASE is_encrypted "
//       "WHEN 1 THEN '是' ELSE '否' END FROM Files");
//
//     model->setQuery(selectAll);
//     view->setModel(model);
//   };
//
//   // 显示在对应视图上
//   if (ui->actioniconView->isChecked()) {
//     // show(ui->IconView);
//   }
//   else if (ui->actionlistView->isChecked()) {
//     // show(ui->listView);
//   }
//   else { show(ui->tableView); }
//   progress->setRange(0, 100);
//   progress->setValue(100);
//   ui->actiondaori->setEnabled(true);
// }
//
// // 文件传输助手
// void MainWindow::on_actiontransmission_triggered()
// {
//   FileTrans* fileTransferUi = new FileTrans;          // 不设parent
//   fileTransferUi->setAttribute(Qt::WA_DeleteOnClose); // 自动清理内存
//   fileTransferUi->show();
// }
//
// // PS 图像处理
// void MainWindow::on_actionPS_triggered()
// {
//   PS* psUi = new PS;
//   psUi->setAttribute(Qt::WA_DeleteOnClose);
//   psUi->show();
// }
//
// ///////////////////////////////////////////////////////////////////////////
// /////////////////////////// 修改系统语言 后续拓展往下写  //////////////////////
// ///////////////////////////////////////////////////////////////////////////
// void MainWindow::retranslate(const QString& lang, const QString& path)
// {
//   if (tran.load(path)) {
//     ui->retranslateUi(this);
//     QSettings settings;
//     settings.setValue("Language", lang);
//   }
//   else { qCritical() << "Failed to load translation file:" << path; }
// }
//
// void MainWindow::on_actionCN_triggered()
// {
//   retranslate("CN", ":/translations/res/translations/icmaLang_CN.qm");
// }
//
// void MainWindow::on_actionEN_triggered()
// {
//   retranslate("EN", ":/translations/res/translations/icmaLang_EN.qm");
// }
//
// void MainWindow::on_actionJP_triggered()
// {
//   retranslate("JP", ":/translations/res/translations/icmaLang_JP.qm");
// }
//
// // 关于ICMA简介
// void MainWindow::on_actionabout_triggered()
// {
//   QMessageBox aboutBox(this);
//   aboutBox.setWindowTitle(tr("关于 ICMA"));
//   aboutBox.setIconPixmap(QPixmap(":/icons/res/icons/logo/logo1024.ico")
//     .scaledToWidth(128, Qt::SmoothTransformation));
//
//   QString aboutText = tr(
//     "<h3>ICMA 智能内容管理助手</h3>"
//     "<p>版本 1.0</p>"
//     "<p>ICMA 是一款功能强大的个人文件管理工具，专为需要高效组织和访问数字内容的用户设计。"
//     "这款应用程序集成了先进的文件管理、智能搜索、内容推荐和数据安全功能，"
//     "旨在提升用户的工作效率和数据管理体验。</p>"
//     "<p><b>主要特点：</b></p>"
//     "<ul>"
//     "<li>智能文件组织：自动分类和标签系统，帮助用户轻松整理各类文件</li>"
//     "<li>高效搜索：支持基本和高级搜索功能，快速定位所需文件</li>"
//     "<li>个性化推荐：基于用户行为，智能推荐相关文件和内容</li>"
//     "<li>数据安全：提供文件加密和MD5完整性校验，保护用户重要数据</li>"
//     "<li>可视化分析：通过图表和报告，直观展示文件使用情况和存储状态</li>"
//     "<li>用户友好界面：直观的布局设计，支持多种视图模式和主题切换</li>"
//     "</ul>"
//     "<p>ICMA 不仅是一个文件管理器，更是您的智能内容助手，"
//     "致力于为用户提供一个更智能、更安全、更高效的数字内容管理解决方案。"
//     "无论是日常文件整理，还是专业内容管理，ICMA 都能满足您的需求。</p>"
//     "<p>Copyright &copy; 2024 UxhQt. All rights reserved.</p>");
//
//   aboutBox.setText(aboutText);
//   aboutBox.setTextFormat(Qt::RichText);
//   aboutBox.setStandardButtons(QMessageBox::Ok);
//
//   aboutBox.exec();
// }
//
// // 退出应用
// void MainWindow::on_actiontuichu_triggered() { this->close(); }
//
// // 开机自启动
// void MainWindow::on_actionautoRun_triggered(bool checked)
// {
//   MainWindow::autoRunSystem(checked, QCoreApplication::applicationName(),
//                             QCoreApplication::applicationFilePath());
// }

MainWindow::~MainWindow()
{
  qDebug() << "\nICMA正常退出";
  delete ui;
}
