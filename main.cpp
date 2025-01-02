#include <iostream>
#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

#include "./initial/AppInit.h"
#include "./Widgets/mainWindow/MainWindow.h"

QTranslator tran; ///< 全局翻译器
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  const auto appInit = new AppInit();
  // if (appInit->configureDirAndFiles()) {
  //   QMessageBox::critical(nullptr, QObject::tr("Error"),
  //                         QObject::tr("Failed to initialize the application."
  //                           " The application will now exit."));
  //   exit(-1);
  // }

  // if (tran.load(AppInit::getLangPath())) {
  //   QApplication::installTranslator(&tran);
  // }

  // MainWindow w;
  //初始化应用程序 如果失败就退出
  // if (!AppInit::init(w)) {
  //   QMessageBox::critical(nullptr, "Error",
  //                         "Failed to initialize the application."
  //                         " The application will now exit.");
  //   exit(-1);
  // }

  //w.show();

  QApplication::processEvents(QEventLoop::AllEvents); ///< 不阻塞UI线程
  qDebug() <<
    R"((♥◠‿◠)ﾉﾞ  ICMA启动成功   ლ(´ڡ`ლ)ﾞ
  ___ ____ __  __    _      ____  _             _
 |_ _/ ___|  \/  |  / \    / ___|| |_ __ _ _ __| |_
  | | |   | |\/| | / _ \   \___ \| __/ _` | '__| __|
  | | |___| |  | |/ ___ \   ___) | || (_| | |  | |_
 |___\____|_|  |_/_/   \_\ |____/ \__\__,_|_|   \__|
                                                    )";

  return QApplication::exec();
}
