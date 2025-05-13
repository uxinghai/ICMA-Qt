/**
 * @file GetQuickStartGuide.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/5/13
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */
 
 #pragma once

class GetQuickStartGuide final {
public:
 static QString getDocBrief()
 {
  const auto accessManager = std::make_unique<QNetworkAccessManager>();
  // 构建网络请求
  const QString url =
    "http://127.0.0.1:4523/m1/5738159-5420866-default/getQuickStartGuide";
  auto* reply = accessManager->get(QNetworkRequest(QUrl(url)));
  NetworkTool::waitForFinished(reply);

  const QString replyStr = reply->readAll();
  if (auto obj = QJsonDocument::fromJson(replyStr.toUtf8())
    .object(); obj["code"].toInt() == 200) { return obj["brief"].toString(); }
  else { return obj["msg"].toString(); }
 }
};