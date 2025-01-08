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

#include <QEventLoop>

#include "./NetworkTool.h"

class GetIcmaBrief final : public QObject {
  Q_OBJECT

public:
  GetIcmaBrief() = default;
  ~GetIcmaBrief() override = default;

  static QString getIcmaBrief()
  {
    const auto accessManager = new QNetworkAccessManager();
    // 构建网络请求
    auto* reply = accessManager->get(QNetworkRequest(
      QUrl("http://127.0.0.1:4523/m1/5738159-5420866-default/getICMABrief")));
    // 阻塞网络请求直到完成
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); ///< 阻塞，直到事件循环退出

    accessManager->deleteLater(); ///< 完成之后析构
    const QString replyStr = reply->readAll();
    if (auto obj = QJsonDocument::fromJson(replyStr.toUtf8())
      .object(); obj["code"].toInt() == 200) { return obj["brief"].toString(); }
    else { return obj["msg"].toString(); }
  }
};
