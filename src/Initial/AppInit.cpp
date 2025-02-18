#include "AppInit.h"

#include <QApplication>

#include "../../icmaStart.h"
#include "../Manager/Config/iniManager.h"
#include "../Manager/JsonManager.h"
#include "../Manager/SqlManager.h"
#include "../Utils/ThreadWorkers/File/FilesDBWorker.h"
#include "../Widgets/mainWindow/MainWindow.h"
#include "SplashScreen.h"

AppInit::AppInit()
  : splash(QSharedPointer<SplashScreen>::create()),
    ini(nullptr), json(nullptr)
{
  icmaStart::printFZ();
  // 在系统文件写入数据库功能实现时show
  // splash->setProgress(0);
  // splash->show();
  // splash->showMessage(tr("正在加载资源，请您耐心等待..."));
}

bool AppInit::configInit()
{
  // 创建 ICMA 配置文件根目录
  icmaRootDirPath = QStandardPaths::writableLocation(
    QStandardPaths::ConfigLocation);
  if (const QDir dir; !dir.mkpath(icmaRootDirPath)) {
    qDebug() << "Failed to create file ob: " << icmaRootDirPath;
    return false;
  }
  // 初始化配置文件，让其自动创建文件(内部会判断是否需要初始化)
  ini = new iniManager(this);
  SqlManager::instance().initSqlConfig();

  printSysInfo();

  return true;
}

bool AppInit::sysFileDBInit() const
{
  // 以下多线程版本系统文件写入数据库还有些问题。数据库作为共享资源出现了被争抢
  // auto* fileDbWorker = new FilesDBWorker();
  // const auto ICMA = iniManager::getIniSetting();
  // const auto lastBuildSqlTime = ICMA.value("Settings/lastBuildSqlTime")
  //                                   .toString();
  // if (!lastBuildSqlTime.isEmpty()) {
  //   // 非首次加载
  //   return fileDbWorker->doIncrementalScan(splash.get());
  // }
  // return fileDbWorker->doFullScan(splash.get());

  return true;
}

void AppInit::initMainwindow()
{
  emit initMainWindowUI();
}

void AppInit::printSysInfo()
{
  icmaStart::printStart();

  const auto ICMA = iniManager::getIniSetting();
  qDebug() << tr("版本：") << ICMA.value("ICMA/version").toString();
  qDebug() << tr("作者：") << ICMA.value("ICMA/author").toString();
  qDebug() << tr("联系方式：") << ICMA.value("ICMA/contact").toString();
  qDebug() << tr("开源地址：") << ICMA.value("ICMA/git").toString();
  qDebug() << tr("协议：") << ICMA.value("ICMA/license").toString();
  qDebug() << tr("描述：") << ICMA.value("ICMA/description")
                               .toString();
  qDebug() << tr("依赖：") << ICMA.value("ICMA/dependencies")
                               .toStringList().join(",");
  qDebug() << tr("发布日期：") << ICMA.value("ICMA/releaseDate")
                                 .toString();
}
