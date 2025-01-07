#include "AppInit.h"

#include <QApplication>
#include <QStandardPaths>

#include "../Manager/Config/iniManager.h"
#include "../Manager/Config/JsonManager.h"
#include "../Manager/SqlManager.h"
#include "../Widgets/mainWindow/MainWindow.h"
#include "SplashScreen.h"

AppInit::AppInit()
  : splash(QSharedPointer<SplashScreen>::create()),
    ini(nullptr), json(nullptr)
{
  qDebug() << R"(
////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                              //
//                      ____/`---'\____                           //
//                    .'  \\|     |//  `.                         //
//                   /  \\|||  :  |||//  \                        //
//                  /  _||||| -:- |||||-  \                       //
//                  |   | \\\  -  /// |   |                       //
//                  | \_|  ''\---/''  |   |                       //
//                  \  .-\__  `-`  ___/-. /                       //
//                ___`. .'  /--.--\  `. . ___                     //
//              ."" '<  `.___\_<|>_/___.'  >'"".                  //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //
//      ========`-.____`-.___\_____/___.-`____.-'========         //
//                           `=---='                              //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//             佛祖保佑       永不宕机      永无BUG                   //
////////////////////////////////////////////////////////////////////)";
  splash->setProgress(0);
}

bool AppInit::init()
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
  json = new JsonManager(this);
  splash->setProgress(40);
  SqlManager::instance().initSqlConfig();
  splash->setProgress(80);

  QApplication::processEvents(QEventLoop::AllEvents); ///< 不阻塞UI线程
  printSysInfo();

  return true;
}

void AppInit::initMainwindow()
{
  emit initMainWindowUI();
  splash->setProgress(100);
  splash.reset(); ///< 释放
}

void AppInit::printSysInfo()
{
  qDebug() <<
    "(♥◠‿◠)ﾉﾞ  ICMA启动成功   ლ(´ڡ`ლ)ﾞ\n"
    "  ___ ____ __  __    _      ____  _             _\n"
    " |_ _/ ___|  \\/  |  / \\    / ___|| |_ __ _ _ __| |_\n"
    "  | | |   | |\\/| | / _ \\   \\___ \\| __/ _` | '__| __|\n"
    "  | | |___| |  | |/ ___ \\   ___) | || (_| | |  | |_\n |___\\____|_|  |_/_/   "
    "\\_\\ |____/ \\__\\__,_|_|   \\__|\n                                                    ";

  const auto iniSetting = iniManager::getIniSetting(); ///< 用来控制（读写）它
  qDebug() << tr("版本：") << iniSetting.value("ICMA/version").toString();
  qDebug() << tr("作者：") << iniSetting.value("ICMA/author").toString();
  qDebug() << tr("联系方式：") << iniSetting.value("ICMA/contact").toString();
  qDebug() << tr("开源地址：") << iniSetting.value("ICMA/git").toString();
  qDebug() << tr("协议：") << iniSetting.value("ICMA/license").toString();
  qDebug() << tr("描述：") << iniSetting.value("ICMA/description")
                                     .toString();
  qDebug() << tr("依赖：") << iniSetting.value("ICMA/dependencies")
                                     .toStringList().join(",");
  qDebug() << tr("发布日期：") << iniSetting.value("ICMA/releaseDate")
                                       .toString();
}
