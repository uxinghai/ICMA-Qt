/**
 * This software uses the Qt framework, licensed under the GNU
 * Lesser General Public License (LGPL) version 2.1 (or later).
 * You can obtain a copy of the LGPL license at https://www.gnu.org/licenses/lgpl.html.
 */

#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

#include "../src/Initial/AppInit.h"
#include "../src/Manager/Config/iniManager.h"
#include "../src/Widgets/mainWindow/MainWindow.h"
#include "src/Utils/Tools/LogOut.h"

QtMessageHandler IcmaMessageHandler; ///< 安装自定义的日志处理器时返回这个指针
QTranslator tran;                    ///< 全局翻译器
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  LogOut::initializeLog();
  IcmaMessageHandler = qInstallMessageHandler(LogOut::messageOutput);

  const auto appInit = new AppInit();
  if (!appInit->init()) {
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                          QObject::tr("Failed to initialize the application."
                            " The application will now exit."));
    exit(-1);
  }

  // 初始化界面,为界面设置主题和语言
  // 语言设置必须在窗口构建之前
  const auto Settings = iniManager::getIniSetting();
  if (QStringList lang = Settings.value("Settings/language").toStringList();
    tran.load(lang[1])) { QApplication::installTranslator(&tran); }

  MainWindow w;
  QObject::connect(appInit, &AppInit::initMainWindowUI,
                   &w, &MainWindow::doInit);
  appInit->initMainwindow();

  // 为系统设置主题
  const QString style = Settings.value("Settings/theme-style").toString();
  if (QFile qss(style); qss.open(QFile::ReadOnly)) {
    qApp->setStyleSheet(qss.readAll());
    qss.close();
  }

  w.show();

  return QApplication::exec();
}
