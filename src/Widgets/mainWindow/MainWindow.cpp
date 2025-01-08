#include "MainWindow.h"

#include <QActionGroup>
#include <QKeyEvent>
#include <QMessageBox>
#include <QTimer>
#include <QTranslator>

#include "../../../UI/ui_MainWindow.h"
#include "../../Controls/Network/GetICMABrief.h"
#include "../../DataBase/worker/FilesDBWorker.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Manager/Config/JsonManager.h"
#include "../../Utils/Tools/CloseWindowMsgBox.h"
#include "../fileTransfer/FileTransfer.h"
#include "../photoShop/PS.h"

extern QTranslator tran;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow),
    lbStatus(new QLabel(this))
{
  ui->setupUi(this);

  setupConnections();
}

void MainWindow::setupConnections()
{
  // 为三个组件的可见性创建统一的槽函数
  auto createVisible = [this](const QAction* action) {
    connect(action, &QAction::triggered,
            this, &MainWindow::doSetActionVisible);
  };
  createVisible(ui->actionFilter);
  createVisible(ui->actionPreview);
  createVisible(ui->actionStatusBar);

  // 为主题切换创建统一的槽函数处理
  auto createLangChanged = [this](const QAction* action) {
    connect(action, &QAction::triggered,
            this, &MainWindow::doChangeTheme);
  };
  createLangChanged(ui->actionAMOLED);
  createLangChanged(ui->actionAqua);
  createLangChanged(ui->actionConsoleStyle);
  createLangChanged(ui->actionMacOS);
  createLangChanged(ui->actionManjaroMix);
  createLangChanged(ui->actionMaterialDark);
  createLangChanged(ui->actionNeonButtons);
  createLangChanged(ui->actionUbuntu);

  // ICMA简介
  connect(ui->actionAbout, &QAction::triggered,
          this, &MainWindow::doShowICMABrief);

  // 退出程序
  connect(ui->actionExit, &QAction::triggered,
          this, &MainWindow::close);
}

// 初始化界面
void MainWindow::doInit()
{
  // 创建互斥组的通用方法
  auto createExclusiveGroup = [this](const QVector<QAction*>& actions) {
    auto* group = new QActionGroup(this);
    for (const auto& action : actions) { group->addAction(action); }
    group->setExclusive(true);
  };

  // 定义各组的 QAction 列表并创建互斥组
  createExclusiveGroup({
    ui->actionAMOLED, ui->actionAqua, ui->actionConsoleStyle,
    ui->actionMacOS, ui->actionManjaroMix, ui->actionMaterialDark,
    ui->actionNeonButtons, ui->actionUbuntu
  });

  createExclusiveGroup({ui->actionCN, ui->actionEN, ui->actionJP});
  createExclusiveGroup({
    ui->actionListView, ui->actionDetaileView, ui->actionIconView
  });
  createExclusiveGroup({
    ui->actionFileName, ui->actionFileDate, ui->actionFileSize,
    ui->actionFilePath, ui->actionFileType, ui->actionFileSufix,
    ui->actionFileModifyDate, ui->actionFileCeateDate
  });
  createExclusiveGroup({ui->actionAsc, ui->actionDesc});

  // 读取配置文件修改UI
  readIniConfig();
}

void MainWindow::doSetActionVisible(const bool& checked) const
{
  if (const QString objectName = sender()->objectName();
    objectName == "actionFilter") { ui->comBoxFilter->setVisible(checked); }
  else if (objectName == "actionPreview") {
    ui->lbPreview->setVisible(checked);
  }
  else { ui->statusbar->setVisible(checked); }
}

void MainWindow::doChangeTheme() const
{
  // 获取到发送这个信号的 action
  const QString objectName = sender()->objectName();
  // 去掉 action 保留主题名称
  const auto themeName = objectName.mid(6, objectName.length() - 1);
  // 通过构建资源文件路径 优化了映射的额外内存占用
  const QString qssPath = ":/qss/res/QSS/" + themeName + ".qss"; ///< 本地资源
  if (QFile qss(qssPath); qss.open(QIODeviceBase::ReadOnly)) {
    qApp->setStyleSheet(qss.readAll());
    qss.close();
  }

  // 写回文件
  auto setting = iniManager::getIniSetting();
  setting.setValue("Settings/theme-style", qssPath);
}

void MainWindow::readIniConfig()
{
  // 修改UI及Action的选中情况
  const auto Settings = iniManager::getIniSetting();
  ui->actionAutoRun->setChecked(Settings.value("Settings/auto-run").toBool());
  ui->actionEnableFileLog->setChecked(
    Settings.value("Settings/enableFileLogging").toBool());
  ui->actionShowHideFile->setChecked(
    Settings.value("Settings/showHideFile").toBool());

  ui->actionFilter->setChecked(Settings.value("Settings/filter").toBool());
  ui->actionPreview->setChecked(Settings.value("Settings/preview").toBool());
  ui->actionStatusBar->
      setChecked(Settings.value("Settings/statusBar").toBool());
  ui->comBoxFilter->setVisible(ui->actionFilter->isChecked());
  ui->lbPreview->setVisible(ui->actionPreview->isChecked());
  ui->statusbar->setVisible(ui->actionStatusBar->isChecked());

  // 对于主题Action的选中
  const QString themeName = Settings.value("Settings/theme-style").toString();
  const auto leftPos = themeName.lastIndexOf('/') + 1;
  const QString themeActionName = QString("action") +
    themeName.mid(leftPos, themeName.length() - leftPos - 4);
  if (auto* themeAction = findChild<QAction*>(themeActionName)) { ///< 确保存在
    themeAction->setChecked(true);
  }

  // 对于排序方式的Action的选中
  const auto sortValue = Settings.value("Settings/sort-method").toList();
  if (auto* sortAction = findChild<QAction*>(QString("action") +
    sortValue[0].toString())) { sortAction->setChecked(true); }
  if (auto* sortAction2 = findChild<QAction*>(QString("action") +
    sortValue[1].toString())) { sortAction2->setChecked(true); }

  // 修改视图的Action的选中
  if (auto* viewAction = findChild<QAction*>(QString("action") +
    Settings.value("Settings/view-method").toString())) {
    viewAction->setChecked(true);
  }

  // 修改语言Action的选中
  if (auto* langAction = findChild<QAction*>(QString("action") +
    Settings.value("Settings/language").toList()[0].toString())) {
    langAction->setChecked(true);
  }

  // 修改系统字体
  updateAppFont(Settings.value("Settings/font").toList());
}

void MainWindow::updateAppFont(const QList<QVariant>& list)
{
  if (list.isEmpty()) { return; }
  QFont font;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) {
    this->close(); ///< 关闭窗口
    return;
  }
  QMainWindow::keyPressEvent(event);
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

// ICMA简介
void MainWindow::doShowICMABrief()
{
  QMessageBox aboutBox(this);
  aboutBox.setWindowTitle(tr("关于 ICMA"));
  aboutBox.setIconPixmap(QPixmap(":/icons/res/icons/logo/logo1024.ico")
    .scaledToWidth(128, Qt::SmoothTransformation));

  const QString aboutText = GetIcmaBrief::getIcmaBrief();
  aboutBox.setText(aboutText);
  aboutBox.setTextFormat(Qt::RichText);
  aboutBox.setStandardButtons(QMessageBox::Ok);
  aboutBox.exec();
}

//
//
// // 开机自启动
// void MainWindow::on_actionautoRun_triggered(bool checked)
// {
//   MainWindow::autoRunSystem(checked, QCoreApplication::applicationName(),
//                             QCoreApplication::applicationFilePath());
// }

void MainWindow::closeEvent(QCloseEvent* event)
{
  // 如果不再询问为True 直接关闭并退出
  auto setting = iniManager::getIniSetting();
  if (!setting.value("Settings/closeNoRequire").toBool()) {
    auto* closeWindowMsgBox = new CloseWindowMsgBox(this);
    closeWindowMsgBox->exec();
  }
  savaIniConfig();
  event->accept();
}

void MainWindow::savaIniConfig()
{
  qDebug() << "写u";
}

MainWindow::~MainWindow()
{
  qDebug() << "\nICMA正常退出";
  delete ui;
}
