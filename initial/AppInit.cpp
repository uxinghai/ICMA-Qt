#include "AppInit.h"

#include <QStandardPaths>

#include "../manager/Config/iniManager.h"
#include "../manager/Config/JsonManager.h"
#include "../manager/SqlManager.h"
#include "../Widgets/mainWindow/MainWindow.h"
#include "./SplashScreen.h"

//SplashScreen* AppInit::splash;

AppInit::AppInit()
  : splash(QSharedPointer<SplashScreen>::create())
{
  // 创建 ICMA 配置文件根目录
  icmaRootDirPath = QStandardPaths::writableLocation(
    QStandardPaths::ConfigLocation);
  if (const QDir dir; !dir.mkpath(icmaRootDirPath)) {
    qDebug() << "Failed to create file ob: " << icmaRootDirPath;
    return;
  }

  ini = std::make_unique<iniManager>();
  json = std::make_unique<JsonManager>();
  SqlManager::instance().initSqlConfig();
}

bool AppInit::init(MainWindow& w)
{
  // configureDirAndFiles()函数在main中调用了，这里不需要

  //  emit initMainWindowUI();

  return true;
}

// void AppInit::initMainWindowUI(MainWindow& w)
// {
// Ui_MainWindow* ui = w.ui; // 使用传入的MainWindow对象的UI实例
// // 辅助函数：创建互斥的Action组
// auto createExclusiveActionGroup = [&w](QList<QAction*> actions) {
//   QActionGroup* group = new QActionGroup(&w);
//   for (auto& action : actions) { group->addAction(action); }
//   group->setExclusive(true);
//   return group;
// };
//
// createExclusiveActionGroup({
//   ui->actionlistView, ui->actioniconView,
//   ui->actiondetaileview
// });
//
// createExclusiveActionGroup({
//   ui->actionname, ui->actiondate,
//   ui->actionsize, ui->actionpath,
//   ui->actionsufix, ui->actiontype,
//   ui->actioncreatDate, ui->actionmodifyDate
// });
//
// createExclusiveActionGroup({ui->actionasc, ui->actiondesc});
// createExclusiveActionGroup({ui->actionlight, ui->actiondark, ui->actionauto});
// createExclusiveActionGroup({ui->actionCN, ui->actionEN, ui->actionJP});
// }

// 一开始错误 是因为jsonFilePath没有被赋值
// 所以重构了Appinit代码，把configureDirAndFiles提取出来
// 在这个函数里先检查所有文件和目录是否存在
bool AppInit::configureDirAndFiles()
{
  // AppInit::splash = new SplashScreen(QPixmap(":/splash.png")); // 换个图片
  // splash->show();
  // QApplication::processEvents();
  // splash->setProgress(0);
  // // writableLocation返回指定类型应该写入的路径 各个系统不相同
  // auto configPath = QStandardPaths::writableLocation(
  //   QStandardPaths::ConfigLocation);
  // QString configDir = configPath + "/ICMA_App"; // 名为ICMA_App的文件夹
  // QDir dir(configDir);
  // // mkpath会创建路径上的所有目录 C:/user/uxinghai/demo 确保这样的每级目录存在
  // if (!dir.exists()) { dir.mkpath(configDir); }
  //
  // AppInit::jsonFilePath = configDir + "/config.json";
  // if (!checkJsonFilePath(AppInit::jsonFilePath)) // 确保Json文件存在并正确配置
  //   return false;
  //
  // // 获取json根对象
  // QJsonObject obj = getJsonObject();
  // if (obj.isEmpty())
  //   return false; // 如果没有正常配置
  //
  // splash->setProgress(10);
  //
  // // 设置应用程序基本信息
  // QJsonObject appInfo = obj["application"].toObject();
  // QApplication::setOrganizationName(appInfo["organization"].toString());
  // QApplication::setApplicationName(appInfo["name"].toString());
  // qDebug() << "OrganizationName: " << QApplication::organizationName();
  // qDebug() << "ApplicationName: " << QApplication::applicationName();
  // splash->setProgress(30);
  //
  // // 设置数据库路径
  // QString dbFilePath = configDir + "/ICMA.db";
  // DataBasePath = QDir::toNativeSeparators(dbFilePath);
  // // 确保存在并初始化数据库
  // if (!initDatabase(obj, *splash))
  //   return false;
  //
  return true;
}

// 设置系统语言
QString AppInit::getLangPath()
{
  // QJsonObject langObj = getJsonObject()["settings"].toObject()["language"].
  //   toObject();
  // QString curLang = "CN"; // 默认中文
  // if (langObj["EN"].toBool()) { curLang = "EN"; } else if (langObj["JP"].
  //   toBool()) { curLang = "JP"; }
  //
  // // 语言及所对应的文件路径映射
  // QMap<QString, QString> langMap{
  //   {"CN", ":/translations/res/translations/icmaLang_CN.qm"},
  //   {"EN", ":/translations/res/translations/icmaLang_EN.qm"},
  //   {"JP", ":/translations/res/translations/icmaLang_JP.qm"}
  // };
  // return langMap.value(curLang); // 获取路径
  return "";
}

// 所有配置文件映射项
// QVector<AppInit::ConfigGroup> AppInit::getConfigMappings(MainWindow& w)
// {
// Ui_MainWindow* ui = w.ui;
// return {
//   {
//     "general", { // 常规项
//       {ui->actionautoRun, "autoRun"},
//       {ui->actionenableFileLog, "enableFileLogging"},
//       {ui->actionfilter, "filter", ui->comBoxFilter},
//       {ui->actionpreview, "preview", ui->lbPreview},
//       {ui->actionstatusbar, "statusBar", ui->statusbar}
//     }
//   },
//   {
//     "language", { // 语言项
//       {ui->actionCN, "CN"},
//       {ui->actionEN, "EN"},
//       {ui->actionJP, "JP"}
//     }
//   },
//   {
//     "sort", { // 排序项
//       {ui->actioncreatDate, "birth"},
//       {ui->actionmodifyDate, "modify"},
//       {ui->actiondate, "date"},
//       {ui->actionname, "name"},
//       {ui->actionpath, "path"},
//       {ui->actionsize, "size"},
//       {ui->actiontype, "type"},
//       {ui->actionsufix, "suffix"},
//       {ui->actionasc, "ascending"},
//       {ui->actiondesc, "descending"}
//     }
//   },
//   {
//     "theme", { // 主题项
//       {ui->actionlight, "light"},
//       {ui->actiondark, "dark"},
//       {ui->actionauto, "auto"}
//     }
//   },
//   {
//     "view", { // 视图项
//       {ui->actionlistView, "list"},
//       {ui->actioniconView, "icon"},
//       {ui->actiondetaileview, "detail"}
//     }
//   }
// };
//   return {};
// }

// 只是界面组件的变化(注意所有组件应该是 checkable 属性!)
// void AppInit::setSystemSettings(MainWindow& w, SplashScreen& splash)
// {
// QJsonObject obj = getJsonObject()["settings"].toObject();
//
// // 处理所有配置组
// const auto groups = getConfigMappings(w);
// int progress = 70;
// const int progressStep = 20 / groups.size();
//
// for (const auto& group : groups) {
//   QJsonObject groupObj = group.groupName == "settings"
//                            ? obj
//                            : obj[group.groupName].toObject();
//
//   // 处理组内每个配置项
//   for (const auto& config : group.mappings) {
//     bool checked = groupObj[config.jsonKey].toBool();
//     config.action->setChecked(checked);
//
//     // 处理关联的UI组件
//     if (config.otherWidget) { config.otherWidget->setVisible(checked); }
//   }
//
//   progress += progressStep;
//   splash.setProgress(progress);
// }
// }

// void AppInit::WriteInJsonConfig(MainWindow& w)
// {
// QJsonObject obj = getJsonObject()["settings"].toObject();
//
// // 处理所有配置组
// const auto groups = getConfigMappings(w);
// for (const auto& group : groups) {
//   QJsonObject groupObj = obj[group.groupName].toObject(); // 临时object
//
//   // 处理组内每个配置项
//   for (const auto& config : group.mappings) {
//     groupObj[config.jsonKey] = config.action->isChecked();
//   }
//
//   // 更新到根设置对象
//   obj[group.groupName] = groupObj;
// }
//
// // 保存更新后的settings对象
// QJsonObject root = getJsonObject();
// root["settings"] = obj;
//
// // 写入json文件
// QFile configFile(jsonFilePath);
// if (configFile.open(QIODevice::WriteOnly)) {
//   configFile.write(QJsonDocument(root).toJson());
//   configFile.close();
// }
// }
