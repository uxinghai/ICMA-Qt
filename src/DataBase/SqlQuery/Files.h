/**
 * @file Files.h
 * @brief 线程安全的文件数据库操作接口
 *
 * @version 2.0
 * @date 2025/1/12
 *
 * @author uxinghai
 */

#pragma once

#include <QDateTime>
#include <QFileInfo>
#include <QMap>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariant>

#include "Directory.h"

class FilesDB {
public:
  /**
   * @brief 插入单个文件记录
   * @param query 预处理的查询对象
   * @param filePath 文件路径
   * @return 是否成功
   */
  static bool insertFile(QSqlQuery& query, const QString& filePath)
  {
    const QFileInfo fileInfo(filePath);

    query.addBindValue(fileInfo.fileName());
    query.addBindValue(fileInfo.absolutePath());
    query.addBindValue(fileInfo.absoluteFilePath());

    // 获取目录ID (使用新的线程安全的DirectoryDB)
    const auto id = DirectoryDB::getDirectoryId(fileInfo.absolutePath());
    query.addBindValue(id);
    query.addBindValue(fileInfo.size());
    query.addBindValue(fileInfo.suffix());
    query.addBindValue(fileInfo.birthTime().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(fileInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(fileInfo.lastRead().toString("yyyy/MM/dd hh:mm"));
    const QString suffixIcon = fileInfo.suffix().toLower();
    query.addBindValue(":/suffixes/res/suffix/" + suffixIcon + ".png");

    if (!query.exec()) {
      /// 这里报错database is locked Unable to fetch row被上锁
      qWarning() << "Failed to insert file:" << filePath
        << "Error:" << query.lastError().text();
      return false;
    }
    return true;
  }

  /**
   * @brief 自动插入文件记录
   * @param filesPath 单个文件路径或文件路径列表
   * @return 是否成功
   * @thread-safety 线程安全
   */
  static bool autoInsert(const QVariant& filesPath)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    QSqlQuery query(*db);

    query.prepare(
      "INSERT INTO Files ("
      "file_name, file_path, file_absFilePath, directory_id, file_size, "
      "file_type, creation_date, modification_date, last_access_date, icon_path"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    );

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool success = true;
    try {
      if (filesPath.typeId() == QVariant::StringList) {
        for (const QString& filePath : filesPath.toStringList()) {
          if (!insertFile(query, filePath)) {
            throw std::runtime_error("Failed to insert file");
          }
        }
      }
      else if (filesPath.typeId() == QVariant::String) {
        if (!insertFile(query, filesPath.toString())) {
          throw std::runtime_error("Failed to insert file");
        }
      }
      else { throw std::runtime_error("Unsupported input type"); }

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
    } catch (const std::exception& e) {
      qWarning() << "Error during file insertion:" << e.what();
      db->rollback();
      success = false;
    }

    return success;
  }

  /**
   * @brief 获取所有文件路径及其修改时间
   * @return 文件路径到修改时间的映射
   * @thread-safety 线程安全
   */
  static QMap<QString, QDateTime> getAllFilesWithModTime()
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return {};
    }

    QMap<QString, QDateTime> fileMap;
    QSqlQuery query(*db);

    if (!query.exec("SELECT file_absFilePath, modification_date FROM Files")) {
      qWarning() << "Failed to get files:" << query.lastError().text();
      return {};
    }

    while (query.next()) {
      const QString filePath = query.value(0).toString();
      const QDateTime modTime = QDateTime::fromString(
        query.value(1).toString(), "yyyy/MM/dd hh:mm");
      fileMap.insert(filePath, modTime);
    }

    return fileMap;
  }

  /**
   * @brief 更新文件记录
   * @param path 单个文件路径或文件路径列表
   * @return 是否成功
   * @thread-safety 线程安全
   */
  static bool updateFile(const QVariant& path)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool success = true;
    try {
      QSqlQuery query(*db);
      query.prepare(
        "UPDATE Files SET file_size = ?, modification_date = ? "
        "WHERE file_absFilePath = ?"
      );

      if (path.typeId() == QVariant::StringList) {
        for (const QString& filePath : path.toStringList()) {
          const QFileInfo fileInfo(filePath);
          query.bindValue(0, fileInfo.size());
          query.bindValue(
            1, fileInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
          query.bindValue(2, filePath);

          if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
          }
        }
      }
      else if (path.typeId() == QVariant::String) {
        const QFileInfo fileInfo(path.toString());
        query.bindValue(0, fileInfo.size());
        query.bindValue(
          1, fileInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
        query.bindValue(2, path.toString());

        if (!query.exec()) {
          throw std::runtime_error(query.lastError().text().toStdString());
        }
      }
      else { throw std::runtime_error("Unsupported input type"); }

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
    } catch (const std::exception& e) {
      qWarning() << "Error during file update:" << e.what();
      db->rollback();
      success = false;
    }

    return success;
  }

  /**
   * @brief 删除文件记录
   * @param path 单个文件路径或文件路径列表
   * @return 是否成功
   * @thread-safety 线程安全
   */
  static bool removeFile(const QVariant& path)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool success = true;
    try {
      QSqlQuery query(*db);
      query.prepare("DELETE FROM Files WHERE file_absFilePath = ?");

      if (path.typeId() == QVariant::StringList) {
        for (const QString& filePath : path.toStringList()) {
          query.bindValue(0, filePath);
          if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
          }
        }
      }
      else if (path.typeId() == QVariant::String) {
        query.bindValue(0, path.toString());
        if (!query.exec()) {
          throw std::runtime_error(query.lastError().text().toStdString());
        }
      }
      else { throw std::runtime_error("Unsupported input type"); }

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
    } catch (const std::exception& e) {
      qWarning() << "Error during file removal:" << e.what();
      db->rollback();
      success = false;
    }

    return success;
  }
};
