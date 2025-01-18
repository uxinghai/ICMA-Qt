#include "MainWindow.h"

#include <QActionGroup>
#include <QMessageBox>

#include "../../../UI/ui_MainWindow.h"
#include "../../Network/GetICMABrief.h"
#include "../../DataBase/worker/FilesDBWorker.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Manager/JsonManager.h"
#include "../../Utils/Tools/CloseWindowMsgBox.h"
#include "../../Utils/Tools/SystemTrayIcon.h"
#include "../fileTransfer/FileTransfer.h"
#include "../photoShop/PS.h"

extern QTranslator tran;
extern QtMessageHandler IcmaMessageHandler;

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::MainWindow),
    lbStatus(new QLabel(this)),
    icmaTrayIcon(std::make_unique<SystemTrayIcon>(
      QIcon(":/icons/res/icons/logo/logo64.ico"), this, "ICMA"))
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
          [this]() {
            const auto psWidget = new PS();
            psWidget->setAttribute(Qt::WA_DeleteOnClose);
            psWidget->show();
          });
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

void MainWindow::readIniConfig()
{
  const QString settingsPrefix = "Settings/";
  // 修改UI及Action的选中情况
  const auto Settings = iniManager::getIniSetting();
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
    Settings.value("Settings/language").toList()[0].toString())) {
    langAction->setChecked(true);
  }

  // 修改系统字体
  auto font = Settings.value("Settings/font").toList();
  this->setFont(QFont(font[0].toString(), font[1].toInt()));
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
  QHBoxLayout* buttonLayout = new QHBoxLayout;
  QPushButton* okButton = new QPushButton(tr("OK"));
  connect(okButton, &QPushButton::clicked, &aboutBox, &QDialog::accept);

  buttonLayout->addStretch();        // 左侧留空
  buttonLayout->addWidget(okButton); // 按钮靠右
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
}

MainWindow::~MainWindow()
{
  qDebug() << "\nICMA正常退出";
  delete ui;
}
