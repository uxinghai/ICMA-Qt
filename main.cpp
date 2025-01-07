#include <QApplication>
#include <QMessageBox>
#include <QTranslator>

#include "../src/Initial/AppInit.h"
#include "../src/Manager/Config/iniManager.h"
#include "../src/Widgets/mainWindow/MainWindow.h"

QTranslator tran; ///< 全局翻译器
int main(int argc, char* argv[])
{
  QApplication app(argc, argv);

  const auto appInit = new AppInit();
  if (!appInit->init()) {
    QMessageBox::critical(nullptr, QObject::tr("Error"),
                          QObject::tr("Failed to initialize the application."
                            " The application will now exit."));
    exit(-1);
  }

  // 初始化界面,为界面设置主题和语言
  // 语言设置必须在窗口构建之前
  const auto settings = iniManager::getIniSetting();
  if (QStringList lang = settings.value("Settings/language").toStringList();
    tran.load(lang[1])) { QApplication::installTranslator(&tran); }
  MainWindow w;
  QObject::connect(appInit, &AppInit::initMainWindowUI,
                   &w, &MainWindow::doInit);
  appInit->initMainwindow();

  const QString style = settings.value("Settings/theme-style").toString();
  if (QFile qss(style); qss.open(QFile::ReadOnly)) {
    qApp->setStyleSheet(qss.readAll());
    qss.close();
  }

  w.show();

  return QApplication::exec();
}
