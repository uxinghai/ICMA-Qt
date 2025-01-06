/**
 * @file SysConfig.h
 *
 * @Breife 系统配置，主题色，字体等中英文
 *
 * @version 1.0
 * @date 2025/1/2 20:18
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include "../../manager/Config/JsonManager.h"

static auto* jsonManager = new JsonManager();

class SysConfig final {
public:
  static QString setSysLang()
  {
    // 按当前配置文件json表来设置。每次修改语言就是修改配置表
    auto langObj = jsonManager->jsonObject()["settings"]
      .toObject()["language"].toObject();

    QString curLang = "CN"; ///< 默认中文
    if (langObj["EN"].toBool()) { curLang = "EN"; }
    else if (langObj["JP"].toBool()) { curLang = "JP"; }
    // 语言及所对应的翻译资源文件的路径映射
    const QMap<QString, QString> langMap{
      {"CN", ":/translations/res/translations/icmaLang_CN.qm"},
      {"EN", ":/translations/res/translations/icmaLang_EN.qm"},
      {"JP", ":/translations/res/translations/icmaLang_JP.qm"}
    };
    return langMap.value(curLang);
  }
};
