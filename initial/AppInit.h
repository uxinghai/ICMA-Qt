/**
 * @file AppInit.h
 *
 * @Breife 应用程序初始化器的头文件
 * 该头文件定义了 AppInit 类，这个类负责处理应用程序的初始化过程
 * 它包括加载配置、初始化数据库、设置语言、处理文件安全性的功能
 * 该头文件创建的数据库文件和基本配置文件都存放在用户本地应用数据目录
 * (C:\Users\uxinghai\AppData\Local\)
 * 并在程序启动前检查是否存在，如果不存在则创建
 *
 * @version 1.0
 * @date 2024.8.4
 *
 * @author uxinghai
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <QWidget>

class SqlManager;
class JsonManager;
class iniManager;
class SplashScreen;
class MainWindow;

static QString icmaRootDirPath; ///< icma根路径

class AppInit final {
public:
  AppInit();

  // 初始化应用程序(程序启动时)
  bool init(MainWindow& w);

  // 确保配置文件存在 并初始化
  bool configureDirAndFiles();

  // 界面配置信息写入 Json 配置文件(程序被关闭时)
  //void WriteInJsonConfig(MainWindow& w);

  // 设置系统配置(在MainWindow.cpp)中调用
  // void setSystemSettings(MainWindow& w, SplashScreen& splash);

  // 设置应用程序语言
  QString getLangPath();

signals:
  // void initMainWindowUI(); ///< 让Mainwindow初始化

private:
  // // 定义配置项映射
  // struct ConfigMapping {
  //   QAction* action;
  //   QString jsonKey;
  //   // 关联的额外UI组件 例如过滤器组件关联一个过滤器的combox等
  //   QWidget* otherWidget = nullptr;
  // };
  //
  // struct ConfigGroup {
  //   QString groupName;
  //   QVector<ConfigMapping> mappings;
  // };
  //
  // QVector<ConfigGroup> getConfigMappings(MainWindow& w);

  QSharedPointer<SplashScreen> splash;
  std::unique_ptr<iniManager> ini;
  std::unique_ptr<JsonManager> json;
};
