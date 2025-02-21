#include "MainWindow.h"

#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QStandardItemModel>

#include "../../../UI/ui_MainWindow.h"
#include "../../DataBase/SqlQuery/Files.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Manager/JsonManager.h"
#include "../../Network/GetICMABrief.h"
#include "../../Utils/ThreadWorkers/File/FilesDBWorker.h"
#include "../../Utils/Tools/CloseWindowMsgBox.h"
#include "../../Utils/Tools/SystemTrayIcon.h"
#include "../fileDeduplicate/FileDeduplicate.h"
#include "../fileTransfer/FileTransfer.h"
#include "../photoShop/PS.h"

extern QTranslator tran;
extern QtMessageHandler IcmaMessageHandler;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow),
    lbStatus(new QLabel(this)),
    icmaTrayIcon(std::make_unique<SystemTrayIcon>(
      QIcon(":/icons/res/icons/logo/logo64.ico"), this, "ICMA")),
    progress(new QProgressBar(this))
{
  ui->setupUi(this);
  ui->statusbar->addWidget(lbStatus);
  ui->statusbar->addWidget(progress);
  progress->setRange(0, 100);
  progress->setMaximumHeight(25);
  progress->setMaximumWidth(this->width());
  progress->setVisible(false);
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

  connect(ui->actionDaori, &QAction::triggered, this, &MainWindow::doDaoRu);

  // 日志文件
  connect(ui->actionEnableFileLog, &QAction::triggered,
          this, &MainWindow::doEnableLogOut);

  // 关于QT
  connect(ui->actionAboutQT, &QAction::triggered, [this] {
    QMessageBox::aboutQt(this, tr("关于QT"));
  });

  // ICMA简介
  connect(ui->actionAbout, &QAction::triggered,
          this, &MainWindow::doShowICMABrief);

  // 退出程序
  connect(ui->actionExit, &QAction::triggered,
          this, &MainWindow::close);

  // 启动图像处理窗口
  connect(ui->actionPS, &QAction::triggered,
          [this] {
            auto* psWidget = PS::getInstance();
            connect(psWidget, &PS::WindowClose, this, &MainWindow::show);
            this->hide();
            psWidget->show();
          });

  // 启动文件传输
  connect(ui->actionTransmission, &QAction::triggered,
          [this] {
            auto* fileTransWidget = new FileTrans();
            connect(fileTransWidget, &FileTrans::WindowClose,
                    this, &MainWindow::show);
            this->hide();
            fileTransWidget->show();
          });

  // 启动文件去重
  connect(ui->actionFileDuplication, &QAction::triggered,
          [this] {
            auto* fileDepWidget = new FileDeduplicate();
            connect(fileDepWidget, &FileDeduplicate::WindowClose,
                    this, &MainWindow::show);
            this->hide();
            fileDepWidget->show();
          });

  // 自定义的 TableView 右键菜单
  connect(ui->tableView, &QTableView::customContextMenuRequested,
          [this](const QPoint& pos) {
            // 如果 pos 不位于名称列（第0列）
            if (ui->tableView->indexAt(pos).column() != 0) {
              const auto menu = std::make_unique<QMenu>();
              // 视图 排序 刷新
              auto* viewMenu = new QMenu(tr("视图(&V)"));
              viewMenu->addActions({
                ui->actionListView, ui->actionIconView,
                ui->actionDetailView
              });
              auto* sortMenu = new QMenu(tr("排序(&S)"));
              sortMenu->addActions({
                ui->actionFileName, ui->actionFileDate, ui->actionFileSize,
                ui->actionFilePath, ui->actionFileType, ui->actionFileSuffix,
                ui->actionFileModifyDate, ui->actionFileCreateDate
              });
              sortMenu->addSeparator();
              sortMenu->addActions({ui->actionAsc, ui->actionDesc});
              menu->addMenu(viewMenu);
              menu->addMenu(sortMenu);
              menu->addAction(ui->actionRefresh);
              menu->exec(QCursor::pos());
            }
            else {
              showFileContextMenu(); ///< 显示名称列上下文菜单
            }
          });

  // 自定义的信号
  connect(ui->tableView, &MyTableView::lbStatusModify,
          [this](const QString& modText) {
            if (modText == "NULL") {
              lbStatus->setText(tr("%1 个对象").arg(filesCountResult));
            }
            else { lbStatus->setText(modText); }
          });

  connect(ui->actionAutoRun, &QAction::triggered, this,
          &MainWindow::autoRunSystem);

  connect(&watcher, &QFutureWatcher<qint32>::progressRangeChanged,
          progress, &QProgressBar::setRange); ///< 范围更新
  connect(&watcher, &QFutureWatcher<qint32>::progressValueChanged,
          progress, &QProgressBar::setValue); ///< 进度值更新
  connect(&watcher, &QFutureWatcher<qint32>::finished, [this] {
    filesCountResult = future.result();
    lbStatus->setText(tr("%1 个对象").arg(filesCountResult));
    progress->setVisible(false);

    // 检查界面当前的视图模式
    if (const int index = ui->stackedWidgetView->currentIndex();
      index == 0) {
      FilesDB::getAllFilesShowView(daoRuDirectoryFile, ui->tableView);
      qDebug() << "导入路径:" << daoRuDirectoryFile;
      ui->tableView->setColumnWidth(0, 500); ///< 让名称列显示的更宽一些
      ui->tableView->setTheSelectionModel(
        ui->tableView->selectionModel()); ///< 自定义存储到selectionModel用于监听
      ui->tableView->initHeaderCustomMenu(ui->actionAutoFit,
                                          ui->actionAutoFitColWidth,
                                          ui->actionShowNameCol,
                                          ui->actionShowPathCol,
                                          ui->actionShowSizeCol,
                                          ui->actionShowTypeCol,
                                          ui->actionShowCreateDateCol,
                                          ui->actionShowModifyDateCol,
                                          ui->actionShowLastModDateCol,
                                          ui->actionShowHashCol,
                                          ui->actionShowEncrCol);
    }
    else if (index == 1) {
      FilesDB::getAllFilesShowView(daoRuDirectoryFile, ui->listView);
    }
    else {
      FilesDB::getAllFilesShowView(daoRuDirectoryFile, ui->IconView,
                                   true);
    }

    this->setEnabled(true);
  });


  // 搜索文件
  connect(ui->lineEdit, &QLineEdit::textChanged,this,&MainWindow::doSearchFile);
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
    ui->actionListView, ui->actionDetailView, ui->actionIconView
  });
  createExclusiveGroup({
    ui->actionFileName, ui->actionFileDate, ui->actionFileSize,
    ui->actionFilePath, ui->actionFileType, ui->actionFileSuffix,
    ui->actionFileModifyDate, ui->actionFileCreateDate
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

void MainWindow::doSearchFile(const QString& term)
{
  // TODO: 搜索数据库 返回对应词条内容,支持正则表达式输入
}

void MainWindow::readIniConfig()
{
  QSettings Settings = iniManager::getIniSetting();

  // 程序启动时写入两个系统信息
  Settings.setValue("ICMA/applicationName",
                    QCoreApplication::applicationName());
  Settings.setValue("ICMA/applicationPath",
                    QCoreApplication::applicationFilePath());

  // 以下是读取 ini， 修改UI及Action的选中情况
  const QString settingsPrefix = "Settings/";
  QStringList pos = Settings.value(
    settingsPrefix + "window-size").toStringList();
  if (pos.length() == 2) { this->resize(pos[0].toInt(), pos[1].toInt()); }
  ui->actionAutoRun->setChecked(
    Settings.value(settingsPrefix + "auto-run").toBool());
  ui->actionEnableFileLog->setChecked(
    Settings.value(settingsPrefix + "enableFileLogging").toBool());
  ui->actionShowHideFile->setChecked(
    Settings.value(settingsPrefix + "showHideFile").toBool());

  ui->actionFilter->setChecked(
    Settings.value(settingsPrefix + "filter").toBool());
  ui->actionPreview->setChecked(
    Settings.value(settingsPrefix + "preview").toBool());
  ui->actionStatusBar->
      setChecked(Settings.value(settingsPrefix + "statusBar").toBool());
  ui->comBoxFilter->setVisible(ui->actionFilter->isChecked());
  ui->lbPreview->setVisible(ui->actionPreview->isChecked());
  ui->statusbar->setVisible(ui->actionStatusBar->isChecked());

  // 对于主题Action的选中
  const QString themeName = Settings.value(settingsPrefix + "theme-style").
                                     toString();
  const auto leftPos = themeName.lastIndexOf('/') + 1;
  const QString themeActionName = QString("action") +
    themeName.mid(leftPos, themeName.length() - leftPos - 4);
  if (auto* themeAction = findChild<QAction*>(themeActionName)) { ///< 确保存在
    themeAction->setChecked(true);
  }

  // 对于排序方式的Action的选中
  const auto sortValue = Settings.value(settingsPrefix + "sort-method").
                                  toList();
  if (auto* sortAction = findChild<QAction*>(QString("action") +
    sortValue[0].toString())) { sortAction->setChecked(true); }
  if (auto* sortAction2 = findChild<QAction*>(QString("action") +
    sortValue[1].toString())) { sortAction2->setChecked(true); }

  // 修改视图的Action的选中
  if (auto* viewAction = findChild<QAction*>(QString("action") +
    Settings.value(settingsPrefix + "view-method").toString())) {
    viewAction->setChecked(true);
  }

  // 修改语言Action的选中
  if (auto* langAction = findChild<QAction*>(QString("action") +
    Settings.value(settingsPrefix + "language").toList()[0].toString())) {
    langAction->setChecked(true);
  }

  // 修改系统字体
  auto font = Settings.value(settingsPrefix + "font").toList();
  this->setFont(QFont(font[0].toString(), font[1].toInt()));

  // 详细的列表视图中显示的列
  ui->actionShowNameCol->setChecked(Settings.value
    (settingsPrefix + "actionShowNameCol").toBool());
  ui->actionShowPathCol->setChecked(Settings.value
    (settingsPrefix + "actionShowPathCol").toBool());
  ui->actionShowTypeCol->setChecked(Settings.value
    (settingsPrefix + "actionShowTypeCol").toBool());
  ui->actionShowSizeCol->setChecked(Settings.value
    (settingsPrefix + "actionShowSizeCol").toBool());
  ui->actionShowCreateDateCol->setChecked(Settings.value
    (settingsPrefix + "actionShowCreateDateCol").toBool());
  ui->actionShowModifyDateCol->setChecked(Settings.value
    (settingsPrefix + "actionShowModifyDateCol").toBool());
  ui->actionShowLastModDateCol->setChecked(Settings.value
    (settingsPrefix + "actionShowLastModDateCol").toBool());
  ui->actionShowHashCol->setChecked(Settings.value
    (settingsPrefix + "actionShowHashCol").toBool());
  ui->actionShowEncrCol->setChecked(Settings.value
    (settingsPrefix + "actionShowEncrCol").toBool());
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
  if (event->key() == Qt::Key_Escape) {
    this->close(); ///< 关闭窗口
    return;
  }
  QMainWindow::keyPressEvent(event);
}

// ICMA简介
void MainWindow::doShowICMABrief()
{
  QDialog aboutBox(this);
  aboutBox.setWindowTitle(tr("关于 ICMA"));
  aboutBox.setMinimumSize(662, 563);

  // 主布局为水平布局
  auto* mainLayout = new QHBoxLayout(&aboutBox);

  // 图标部分
  auto* iconLabel = new QLabel();
  iconLabel->setPixmap(QPixmap(":/icons/res/icons/logo/logo1024.ico")
    .scaledToWidth(64, Qt::SmoothTransformation));
  iconLabel->setAlignment(Qt::AlignTop); ///< 图标靠上对齐
  mainLayout->addWidget(iconLabel);

  // 文本和按钮为垂直布局
  auto* subLayout = new QVBoxLayout();

  // 文本部分(后续添加更多语言支持)
  auto* textLabel = new QLabel();
  QString context;
  if (ui->actionCN->isChecked()) { context = GetIcmaBrief::getIcmaBrief("CN"); }
  else if (ui->actionEN->isChecked()) {
    context = GetIcmaBrief::getIcmaBrief("EN");
  }
  else if (ui->actionJP->isChecked()) {
    context = GetIcmaBrief::getIcmaBrief("JP");
  }

  textLabel->setText(context);
  textLabel->setTextFormat(Qt::RichText);
  textLabel->setWordWrap(true);
  textLabel->setAlignment(Qt::AlignTop | Qt::AlignLeft); ///< 文本靠左靠上
  subLayout->addWidget(textLabel);

  // 按钮部分
  auto* buttonLayout = new QHBoxLayout;
  auto* okButton = new QPushButton(tr("OK"));
  connect(okButton, &QPushButton::clicked, &aboutBox, &QDialog::accept);

  buttonLayout->addStretch();        ///< 左侧留空
  buttonLayout->addWidget(okButton); ///< 按钮靠右
  subLayout->addLayout(buttonLayout);
  mainLayout->addLayout(subLayout);
  // 设置对话框的主布局
  aboutBox.setLayout(mainLayout);
  aboutBox.exec();
}

void MainWindow::doEnableLogOut(const bool& checked)
{
  if (checked) { qInstallMessageHandler(IcmaMessageHandler); }
  else { qInstallMessageHandler(nullptr); }
}

qint32 MainWindow::doFilesInDirectory(const QString& path) const
{
  QDir::Filters filter = QDir::Files;
  if (ui->actionShowHideFile->isChecked()) { filter |= QDir::NoDotAndDotDot; }

  qsizetype count = 0; ///< 记录当前目录下的文件数
  QDirIterator it(path, filter, QDirIterator::Subdirectories);

  static QMutex mutex;
  QMutexLocker locker(&mutex); ///< 线程安全保护
  QStringList directoryFilesPath;
  while (it.hasNext()) {
    it.next();
    // 写入数据库
    directoryFilesPath << it.fileInfo().absoluteFilePath();
    ++count;
  }
  FilesDB::autoInsert(directoryFilesPath);
  return count;
}

void MainWindow::doDaoRu()
{
  daoRuDirectoryFile = QFileDialog::getExistingDirectory(
    this, tr("选择文件夹"));
  if (daoRuDirectoryFile.isEmpty()) return;

  QStringList tempListPath{daoRuDirectoryFile}; ///< 只有1个 用于 mappedReduced 首个参数
  future = mappedReduced(
    tempListPath,
    [this](const QString& path) { return this->doFilesInDirectory(path); },
    // 绑定 this
    [](qint32& result, const qint32& intermediateResult) {
      result += intermediateResult;
    },
    QtConcurrent::UnorderedReduce | QtConcurrent::SequentialReduce
  );

  progress->setVisible(true);
  watcher.setFuture(future);
  this->setEnabled(false); ///< 冻结窗口不可用
}

void MainWindow::showFileContextMenu()
{
  const auto menu = std::make_unique<QMenu>();
  // TODO: 加入更多动作项并监听信号
  menu->addAction(ui->actionRefresh);
  menu->exec(QCursor::pos());
}

void MainWindow::closeEvent(QCloseEvent* event)
{
  // 如果设置了不再询问，直接关闭应用
  if (const auto& settings = iniManager::getIniSetting();
    settings.value("Settings/closeNoRequire").toBool() &&
    settings.value("Settings/close-method").toString() == "directClose") {
    qApp->quit();
    event->accept();
    return;
  }

  // 询问用户
  auto* closeWindowMsgBox = new CloseWindowMsgBox(this);

  auto cancel = [&event, &closeWindowMsgBox, this](const bool& hide) {
    event->ignore();
    closeWindowMsgBox->deleteLater();
    if (hide) { this->hide(); }
  };

  // 结构体存储用户选择
  struct CloseOptions {
    QString method = "tray";
    bool noRequire = false;
  } options;

  connect(closeWindowMsgBox, &CloseWindowMsgBox::trayRadioClicked,
          [&options] { options.method = "tray"; });
  connect(closeWindowMsgBox,
          &CloseWindowMsgBox::directCloseRadioClicked,
          [&options] { options.method = "directClose"; });
  connect(closeWindowMsgBox, &CloseWindowMsgBox::checkBoxClicked,
          [&options](const bool checked) { options.noRequire = checked; });
  connect(closeWindowMsgBox, &CloseWindowMsgBox::okButtonClicked,
          [&options, this, cancel] {
            savaIniConfig(options.method, options.noRequire);
            if (options.method != "tray") { qApp->quit(); }
            else { cancel(true); }
          });
  connect(closeWindowMsgBox, &CloseWindowMsgBox::cancelButtonClicked,
          [cancel] { cancel(false); });

  closeWindowMsgBox->exec();
}

void MainWindow::savaIniConfig(const QString& closeMethod,
                               const bool noRequire) const
{
  auto settings = iniManager::getIniSetting();
  const QString settingsPrefix = "Settings/";

  // 窗口大小和位置保存
  settings.setValue(settingsPrefix + "window-size",
                    QStringList{
                      QString::number(this->width()),
                      QString::number(this->height())
                    });

  // 基础设置保存
  const QMap<QString, bool> boolSettings{
    {"closeNoRequire", noRequire},
    {"auto-run", ui->actionAutoRun->isChecked()},
    {"enableFileLogging", ui->actionEnableFileLog->isChecked()},
    {"showHideFile", ui->actionShowHideFile->isChecked()},
    {"filter", ui->actionFilter->isChecked()},
    {"preview", ui->actionPreview->isChecked()},
    {"statusBar", ui->actionStatusBar->isChecked()}
  };

  // 批量保存布尔值设置
  for (auto it = boolSettings.constBegin();
       it != boolSettings.constEnd(); ++it) {
    settings.setValue(settingsPrefix + it.key(), it.value());
  }

  settings.setValue(settingsPrefix + "close-method", closeMethod);

  // 保存字体设置
  settings.setValue(settingsPrefix + "font",
                    QStringList{
                      font().family(), QString::number(font().pointSize())
                    });

  // 语言设置保存
  const QString qmPath = ":/translations/res/translations/icmaLang_";
  QString lang;
  if (ui->actionCN->isChecked()) { lang = "CN"; }
  else if (ui->actionEN->isChecked()) { lang = "EN"; }
  else { lang = "JP"; }
  settings.setValue(settingsPrefix + "language",
                    QStringList{lang, qmPath + lang + ".qm"});

  // 排序方法保存
  const std::vector<std::pair<QAction*, QString>> sortActions = {
    {ui->actionFileCreateDate, "FileCreateDate"},
    {ui->actionFileDate, "FileDate"},
    {ui->actionFileModifyDate, "FileModifyDate"},
    {ui->actionFileName, "FileName"},
    {ui->actionFilePath, "FilePath"},
    {ui->actionFileSize, "FileSize"},
    {ui->actionFileType, "FileType"}
  };

  QString sortType = "FileSuffix";
  for (const auto& [action, value] : sortActions) {
    if (action->isChecked()) {
      sortType = value;
      break;
    }
  }

  const QString sortOrder = ui->actionAsc->isChecked() ? "Asc" : "Desc";
  settings.setValue(settingsPrefix + "sort-method",
                    QStringList{sortType, sortOrder});

  // 视图方法保存
  QString viewMethod = "ListView";
  if (ui->actionDetailView->isChecked()) { viewMethod = "DetailView"; }
  else if (ui->actionIconView->isChecked()) { viewMethod = "IconView"; }
  settings.setValue(settingsPrefix + "view-method", viewMethod);

  // 详细的列表视图中显示的列
  settings.setValue(settingsPrefix + "actionShowNameCol",
                    ui->actionShowNameCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowPathCol",
                    ui->actionShowPathCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowSizeCol",
                    ui->actionShowSizeCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowTypeCol",
                    ui->actionShowTypeCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowCreateDateCol",
                    ui->actionShowCreateDateCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowModifyDateCol",
                    ui->actionShowModifyDateCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowLastModDateCol",
                    ui->actionShowLastModDateCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowHashCol",
                    ui->actionShowHashCol->isChecked());
  settings.setValue(settingsPrefix + "actionShowEncrCol",
                    ui->actionShowEncrCol->isChecked());
}

MainWindow::~MainWindow()
{
  qDebug() << "\nICMA正常退出";
  delete ui;
}
