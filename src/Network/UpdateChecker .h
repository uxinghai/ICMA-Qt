/**
 * @file UpdateChecker.h
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

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVersionNumber>

class UpdateChecker final : public QObject {
  Q_OBJECT

public:
  explicit UpdateChecker(QObject* parent = nullptr)
  {
    networkManager = new QNetworkAccessManager(this);
    // 默认使用 GitHub 上的版本文件
    updateUrl =
      "https://github.com/uxinghai/ICMA-Qt/blob/main/version.json";
    currentVersion = "1.0.0"; // 默认当前版本
  }

  ~UpdateChecker() override {}

  // 开始检查更新
  void checkForUpdates()
  {
    QNetworkRequest request{QUrl(updateUrl)};

    // Qt 6 兼容方式
#if QT_VERSION >= QT_VERSION_CHECK(5, 9, 0)
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                         QNetworkRequest::NoLessSafeRedirectPolicy);
#endif

    QNetworkReply* reply = networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
      this->onNetworkReply(reply);
    });
  }

  // 设置当前版本和更新服务器URL
  void setCurrentVersion(const QString& version) { currentVersion = version; }
  void setUpdateUrl(const QString& url) { updateUrl = url; }

signals:
  void updateAvailable(const QString& newVersion, const QString& downloadUrl,
                       const QString& releaseNotes);
  void noUpdateAvailable();
  void checkFailed(const QString& errorMessage);

private slots:
  void onNetworkReply(QNetworkReply* reply)
  {
    if (reply->error() != QNetworkReply::NoError) {
      emit checkFailed(tr("网络错误: %1").arg(reply->errorString()));
      reply->deleteLater();
      return;
    }

    const QByteArray data = reply->readAll();

  qDebug() << data.toStdString();

    reply->deleteLater();

    QJsonParseError parseError;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
      emit checkFailed(tr("JSON解析错误: %1").arg(parseError.errorString()));
      return;
    }

    if (!doc.isObject()) {
      emit checkFailed(tr("无效的JSON格式"));
      return;
    }

    QJsonObject obj = doc.object();

    if (!obj.contains("version")) {
      emit checkFailed(tr("版本信息缺失"));
      return;
    }

    const QString newVersion = obj["version"].toString();
    const QString downloadUrl = obj.contains("downloadUrl")
                                  ? obj["downloadUrl"].toString()
                                  : "";
    const QString releaseNotes = obj.contains("releaseNotes")
                                   ? obj["releaseNotes"].toString()
                                   : "";

    if (isVersionNewer(currentVersion, newVersion)) {
      emit updateAvailable(newVersion, downloadUrl, releaseNotes);
    }
    else { emit noUpdateAvailable(); }
  }

private:
  QNetworkAccessManager* networkManager;
  QString currentVersion;
  QString updateUrl;

  // 比较版本号
  static bool isVersionNewer(const QString& currentVersion, const QString& newVersion)
  {
    // 使用Qt的版本号比较功能
    const QVersionNumber current = QVersionNumber::fromString(currentVersion);
    const QVersionNumber newer = QVersionNumber::fromString(newVersion);

    return (QVersionNumber::compare(newer, current) > 0);
  }
};
