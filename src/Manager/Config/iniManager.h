/**
 * @file iniManager.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2024/12/29 22:42
 *
 * @author uxinghai
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <QDir>
#include <QSettings>

extern QString icmaRootDirPath;
inline QString staticIniFilePath;

class iniManager final : public QObject {
public:
  explicit iniManager(QObject* parent = nullptr) : QObject(parent)
  {
    iniFilePath = icmaRootDirPath + "/ICMAInfo.ini";
    staticIniFilePath = iniFilePath;
    if (QFile::exists(iniFilePath)) { return; }
    initIniConfig();
  }

  ~iniManager() override = default;

  [[nodiscard]] QString IniFilePath() { return iniFilePath; }

  // 返回本身可控制读写的 Setting。与 json 提供object类似
  static QSettings getIniSetting()
  {
    return {staticIniFilePath, QSettings::IniFormat};
  }

private:
  // 初始化 ini 配置文件
  void initIniConfig() const
  {
    if (QFile::exists(iniFilePath)) { return; }
    QSettings settings(iniFilePath, QSettings::IniFormat); ///< 如果路径下没有文件会自动生成
    // 系统信息
    settings.setValue("ICMA/version", "1.0.1011");
    settings.setValue("ICMA/author", "uxinghai");
    settings.setValue("ICMA/description",
                      "为需要全面管理数字内容的高级用户或专业人士而创建");
    settings.setValue("ICMA/license", "LGPL");
    settings.setValue("ICMA/git", "https://github.com/uxinghai/ICMA-Qt");
    settings.setValue("ICMA/releaseDate", "2025-01-07");
    settings.setValue("ICMA/dependencies",
                      QStringList{"Qt 6.0", "CMake 3.16"});
    settings.setValue("ICMA/contact", "uxinghaiwyi@163.com");
    // UI配置
    settings.setValue("Settings/theme-style",
                      ":/qss/res/QSS/NeonButtons.qss");
    settings.setValue("Settings/auto-run", false);
    // directClose/tray
    settings.setValue("Settings/close-method", "tray");
    settings.setValue("Settings/closeNoRequire", false);
    settings.setValue("Settings/enableFileLogging", true);
    settings.setValue("Settings/showHideFile", false);
    settings.setValue("Settings/filter", false);
    settings.setValue("Settings/font",
                      QStringList{"Microsoft YaHei UI", "10"});
    settings.setValue("Settings/preview", false);
    settings.setValue("Settings/statusBar", true);
    settings.setValue("Settings/language",
                      QStringList{
                        "CN",
                        ":/translations/res/translations/icmaLang_CN.qm"
                      });
    settings.setValue("Settings/sort-method",
                      QStringList{"FilePath", "Asc"});
    settings.setValue("Settings/view-method", "DetailView");
    settings.setValue("Settings/lastBuildSqlTime", "");
  }

  QString iniFilePath;
};
