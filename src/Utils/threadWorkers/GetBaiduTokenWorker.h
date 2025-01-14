/**
* @file GetBaiduTokenWorker.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/14
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QThread>

extern inline QString API_KEY;
extern inline QString SECRET_KEY;

static QString baseUrl = "https://aip.baidubce.com/oauth/2.0/token";

class GetBaiduTokenWorker final : public QThread {
  Q_OBJECT

public:
  explicit GetBaiduTokenWorker(QObject* parent = nullptr) : QThread(parent)
  {
    // 此处不能放 manager 的实例化，构造函数由主线程调用
    // 而 run 会自动的分配另一个线程去调用 即在另一个线程中使用主线程的manager不对！！！
  }

  void run() override
  {
    manager = std::make_unique<QNetworkAccessManager>();

    connect(manager.get(), &QNetworkAccessManager::finished,
            [this](QNetworkReply* reply) {
              if (reply->error() == QNetworkReply::NoError) {
                if (const QString replyText = reply->readAll();
                  !replyText.contains("error")) {
                  // 得到回复后释放内存并发出信号
                  reply->deleteLater();
                  QJsonObject obj = QJsonDocument::fromJson(replyText.toUtf8())
                    .object();
                  emit baiduTokenReady(obj["access_token"].toString());
                }
              }
            });

    const QString url = baseUrl + "?grant_type=client_credentials&client_id=" +
      API_KEY + "&client_secret=" + SECRET_KEY;

    manager->get(QNetworkRequest(QUrl(url)));

    this->exec(); ///< 事件循环等待 finished 的响应，否则线程直接退出
  }

signals:
  void baiduTokenReady(const QString& token);

private:
  std::unique_ptr<QNetworkAccessManager> manager;
  GetBaiduTokenWorker() = default;
};
