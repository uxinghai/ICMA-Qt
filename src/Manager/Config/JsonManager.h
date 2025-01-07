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
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

extern QString icmaRootDirPath;
static QString staticFilePath;

class JsonManager final : public QObject {
public:
  explicit JsonManager(QObject* parent = nullptr) : QObject(parent)
  {
    jsonFilePath = icmaRootDirPath + "/appConfig.json";
    staticFilePath = jsonFilePath;
    if (!QFile::exists(jsonFilePath)) { initJsonConfig(); }
  }

  ~JsonManager() override = default;

  [[nodiscard]] QString JsonFilePath() { return jsonFilePath; }

  // 返回json Object 用于控制操作
  [[nodiscard]] QJsonObject jsonObject() const
  {
    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
      qWarning() << jsonFilePath << ":" << jsonFile.errorString();
      return QJsonObject{}; ///< 返回空对象
    }

    const QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    // 解析JSON文档
    QJsonParseError jsonError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    // 检查解析是否成功
    if (jsonError.error != QJsonParseError::NoError) {
      qWarning() << "Failed to parse JSON configuration file:"
        << jsonError.errorString();
      return QJsonObject{};
    }

    return jsonDoc.object(); ///< 返回根对象
  }

  static QJsonObject getJsonObject()
  {
    QFile jsonFile(staticFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
      qWarning() << staticFilePath << ":" << jsonFile.errorString();
      return QJsonObject{}; ///< 返回空对象
    }

    const QByteArray jsonData = jsonFile.readAll();
    jsonFile.close();

    // 解析JSON文档
    QJsonParseError jsonError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &jsonError);
    // 检查解析是否成功
    if (jsonError.error != QJsonParseError::NoError) {
      qWarning() << "Failed to parse JSON configuration file:"
        << jsonError.errorString();
      return QJsonObject{};
    }

    return jsonDoc.object(); ///< 返回根对象
  }

private:
  // 初始化 json 配置文件
  void initJsonConfig() const
  {
    if (QFile::exists(jsonFilePath)) { return; }
    // 文件不存在则创建
    QFile configFile(jsonFilePath);
    if (!configFile.open(QIODevice::WriteOnly))
      return;

    const QJsonDocument jsonDoc(InitJsonContent()); ///< 初始JSON内容
    configFile.write(jsonDoc.toJson());             ///< 写入.json文件
    configFile.close();
  }

  static QJsonObject InitJsonContent()
  {
    QJsonObject obj; ///< 临时Json对象
    obj["application"] = QJsonObject{
      {"organization", "uxh-Qt"},
      {"name", "ICMA"}
    };

    obj["database"] = QJsonObject{
      {"path", "dataBase.db"},
      {
        "tables", QJsonArray{
          QJsonObject{
            {"name", "Files"},
            {
              "sql",
              "CREATE TABLE IF NOT EXISTS Files (file_id INTEGER PRIMARY KEY AUTOINCREMENT, file_name TEXT NOT NULL, file_path TEXT NOT NULL, file_size INTEGER, file_type TEXT, creation_date DATETIME, modification_date DATETIME, last_access_date DATETIME, md5_hash TEXT, is_encrypted BOOLEAN DEFAULT 0)"
            }
          },
          QJsonObject{
            {"name", "FileContent"},
            {
              "sql",
              "CREATE TABLE IF NOT EXISTS FileContent (file_id INTEGER PRIMARY KEY, content TEXT, FOREIGN KEY (file_id) REFERENCES Files(file_id))"
            }
          },
          QJsonObject{
            {"name", "FileTags"},
            {
              "sql",
              "CREATE TABLE IF NOT EXISTS FileTags (file_id INTEGER, tag_id INTEGER, PRIMARY KEY (file_id, tag_id))"
            }
          },
          QJsonObject{
            {"name", "Settings"},
            {
              "sql",
              "CREATE TABLE IF NOT EXISTS Settings (setting_key TEXT PRIMARY KEY, setting_value TEXT)"
            }
          },
          QJsonObject{
            {"name", "Tags"},
            {
              "sql",
              "CREATE TABLE IF NOT EXISTS Tags (tag_id INTEGER PRIMARY KEY AUTOINCREMENT, tag_name TEXT NOT NULL UNIQUE)"
            }
          },
          QJsonObject{
            {"name", "UserActions"},
            {
              "sql",
              "CREATE TABLE IF NOT EXISTS UserActions (action_id INTEGER PRIMARY KEY AUTOINCREMENT, file_id INTEGER, action_type INTEGER, action_date DATETIME, FOREIGN KEY (file_id) REFERENCES Files (file_id) ON DELETE NO ACTION ON UPDATE NO ACTION)"
            }
          }
        }
      }
    };

    return obj;
  }

  QString jsonFilePath;
};
