/**
 * @file JsonManager.h
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

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

static QString staticFilePath;

class JsonManager final : public QObject {
public:
  // 返回json Object 用于控制操作
  static QJsonObject jsonObject(const QString& jsonFilePath)
  {
    QFile jsonFile(jsonFilePath);
    if (!QFile::exists(jsonFilePath) || !jsonFile.open(QIODevice::ReadOnly)) {
      qWarning() << jsonFilePath << ":" << jsonFile.errorString();
      return {}; ///< 返回空对象
    }

    const QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    // 解析JSON文档，确保是Json格式
    QJsonParseError jsonError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    // 检查解析是否成功
    if (jsonError.error != QJsonParseError::NoError) {
      qWarning() << "Failed to parse JSON configuration file:"
        << jsonError.errorString();
      return {};
    }

    return jsonDoc.object(); ///< 返回根对象
  }

  void writeIntoJson() {}
};
