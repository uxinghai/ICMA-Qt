/**
 * @file GetICMABrief.h
 *
 * @Breife 通过API调用本地apifox里的接口
 *        修改的话需要去修改文档下的返回响应中brief内容
 *
 * @version 1.0
 * @date 2025/1/8 21:38
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "../../Utils/Tools/NetworkTool.h"

class GetIcmaBrief final {
public:
  static QString getIcmaBrief(const QString& lang)
  {
    const auto accessManager = std::make_unique<QNetworkAccessManager>();
    // 构建网络请求
    const QString url = "http://127.0.0.1:4523/m1/5738159-5420866-default/getICMA"
      + lang + "Brief";
    auto* reply = accessManager->get(QNetworkRequest(QUrl(url)));
    NetworkTool::waitForFinished(reply);

    const QString replyStr = reply->readAll();
    if (auto obj = QJsonDocument::fromJson(replyStr.toUtf8())
      .object(); obj["code"].toInt() == 200) { return obj["brief"].toString(); }
    else { return obj["msg"].toString(); }
  }
};
