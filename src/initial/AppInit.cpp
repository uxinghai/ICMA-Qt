#include "AppInit.h"

#include <QApplication>
#include <QStandardPaths>

#include "../manager/Config/iniManager.h"
#include "../manager/Config/JsonManager.h"
#include "../manager/SqlManager.h"
#include "../Widgets/mainWindow/MainWindow.h"
#include "SplashScreen.h"

AppInit::AppInit()
  : splash(QSharedPointer<SplashScreen>::create())
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
  // 初始化配置文件，让其自动创建文件
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
    R"((♥◠‿◠)ﾉﾞ  ICMA启动成功   ლ(´ڡ`ლ)ﾞ
  ___ ____ __  __    _      ____  _             _
 |_ _/ ___|  \/  |  / \    / ___|| |_ __ _ _ __| |_
  | | |   | |\/| | / _ \   \___ \| __/ _` | '__| __|
  | | |___| |  | |/ ___ \   ___) | || (_| | |  | |_
 |___\____|_|  |_/_/   \_\ |____/ \__\__,_|_|   \__|
                                                    )";
  const auto ini = std::make_unique<iniManager>();
  qDebug() << "version" << ini->getSysInfo(Version);
  qDebug() << "author" << ini->getSysInfo(Author);
  qDebug() << "contact" << ini->getSysInfo(Contact);
  qDebug() << "git" << ini->getSysInfo(Git);
  qDebug() << "license" << ini->getSysInfo(License);
  qDebug() << "description" << ini->getSysInfo(Description);
  qDebug() << "dependencies" << ini->getSysInfo(Dependencies);
  qDebug() << "releaseDate" << ini->getSysInfo(ReleaseDate);
}
