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

class JsonManager final {
public:
  JsonManager()
  {
    jsonFilePath = icmaRootDirPath + "/appConfig.json";
    if (!QFile::exists(jsonFilePath)) { initJsonConfig(); }
  }

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
    // 各项配置(最重要!)
    obj["settings"] = QJsonObject{
      {
        "general",
        QJsonObject{
          {"enableFileLogging", true}, ///< 是否启动文件日志
          {"filter", false},           ///< 是否显示过滤器
          {"preview", false},          ///< 是否显示预览窗口
          {"statusBar", true},         ///< 是否显示状态栏
          {"autoRun", false},          ///< 开机是否自启动
          {"closeNoRequire", false},   ///< 退出程序是否不再询问
          {"font", 10}                 ///< 字号记录
        }
      },
      {
        "theme", QJsonObject{
          {"light", true}, ///< 浅色主题
          {"dark", false}, ///< 深色主题
          {"auto", false}  ///< 自动主题
        }
      },
      {
        "language", QJsonObject{
          {"CN", true},  ///< 中文语言
          {"EN", false}, ///< 英文语言
          {"JP", false}  ///< 日文语言
        }
      },
      {
        "view", QJsonObject{
          {"list", false}, ///< 列表视图
          {"icon", false}, ///< 图标视图
          {"detail", true} ///< 详细信息视图
        }
      },
      {
        "sort", QJsonObject{
          {"name", false},      ///< 名称
          {"date", false},      ///< 日期
          {"size", false},      ///< 大小
          {"path", true},       ///< 路径
          {"suffix", false},    ///< 扩展名
          {"type", false},      ///< 类型
          {"birth", false},     ///< 创建日期
          {"modify", false},    ///< 修改日期
          {"ascending", true},  ///< 升序
          {"descending", false} ///< 降序
        }
      },

    };

    return obj;
  }

  QString jsonFilePath;
};
