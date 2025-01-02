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

class iniManager final {
public:
  iniManager()
  {
    iniFilePath = icmaRootDirPath + "/appInfo.ini";
    if (QFile::exists(iniFilePath)) { return; }
    initIniConfig();
  }

  // getter还没写

  void SetVersion(const QVariant& version) const
  {
    upDateIniConfig("version", version);
  }

  void SetAuthor(const QVariant& author) const
  {
    upDateIniConfig("author", author);
  }

  void SetDescription(const QVariant& description) const
  {
    upDateIniConfig("description", description);
  }

  void SetLicense(const QVariant& license) const
  {
    upDateIniConfig("license", license);
  }

  void SetGit(const QVariant& git) const { upDateIniConfig("git", git); }

  void SetReleaseDate(const QVariant& releaseDate) const
  {
    upDateIniConfig("releaseDate", releaseDate);
  }

  void SetDependencies(const QVariant& dependencies) const
  {
    upDateIniConfig("dependencies", dependencies);
  }

  void SetContact(const QVariant& contact) const
  {
    upDateIniConfig("contact", contact);
  }

  [[nodiscard]] QString IniFilePath() { return iniFilePath; }

private:
  // 初始化 ini 配置文件
  void initIniConfig() const
  {
    if (QFile::exists(iniFilePath)) { return; }
    QSettings settings(iniFilePath, QSettings::IniFormat); ///< 如果路径下没有文件会自动生成
    settings.setValue("version", "1.0.0");
    settings.setValue("author", "uxinghai");
    settings.setValue("description", "");
    settings.setValue("license", "LGPL");
    settings.setValue("git", "https://github.com/uxinghai/ICMA");
    settings.setValue("releaseDate", "");
    settings.setValue("dependencies", "[Qt 6.0,CMake 3.16]");
    settings.setValue("contact", "uxinghaiwyi@163.com");
  }

  // 值更新时更新到文件
  void upDateIniConfig(const QAnyStringView key, const QVariant& value) const
  {
    QSettings settings(iniFilePath, QSettings::IniFormat);
    settings.setValue(key, value);
  }

  QString iniFilePath;
};
