#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

#include "../src/initial/AppInit.h"
#include "../src/initial/sysConfig/SysConfig.h"
#include "../src/Widgets/mainWindow/MainWindow.h"

QTranslator tran; ///< 全局翻译器
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  if (const auto appInit = new AppInit(); !appInit->init()) {
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                          QObject::tr("Failed to initialize the application."
                            " The application will now exit."));
    exit(-1);
  }

  if (tran.load(SysConfig::setSysLang())) {
    QApplication::installTranslator(&tran);
  }

  MainWindow w;
  w.show();

  return QApplication::exec();
}
