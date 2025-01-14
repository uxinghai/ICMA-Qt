/**
 * @file Directory.h
 * @brief 线程安全的目录数据库操作接口
 *
 * @version 2.0
 * @date 2025/1/12
 *
 * @author uxinghai
 */

#pragma once

#include <QFileInfo>
#include <QVariant>

#include "../../Manager/SqlManager.h"

class DirectoryDB {
public:
  /**
   * @brief 获取目录ID
   * @param path 目录路径
   * @return 目录ID，失败返回-1
   * @thread 线程安全
   */
  static int getDirectoryId(const QString& path)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return -1;
    }

    QSqlQuery query(*db);
    query.prepare(
      "SELECT directory_id FROM Directory WHERE directory_absFilePath = ?");
    query.addBindValue(path);

    if (!query.exec() || !query.next()) {
      qWarning() << "Failed to get directory id for path:" << path
        << "Error:" << query.lastError().text();
      return -1;
    }

    return query.value(0).toInt();
  }

  /**
   * @brief 插入单个目录记录
   * @param dirPath 目录路径
   * @param query 已准备好的查询对象
   * @return 是否成功
   */
  static bool insertDirectory(QSqlQuery& query, const QString& dirPath)
  {
    const QFileInfo dirInfo(dirPath);

    // 处理根目录和普通目录
    const QString name =
      dirInfo.isRoot() ? dirPath.left(2) : dirInfo.fileName();
    const QString icon = dirInfo.isRoot()
                           ? ":/icons/res/icons/disk.png"
                           : ":/icons/res/icons/directory.png";
    const QString path = dirInfo.isRoot() ? "" : dirInfo.absolutePath();

    query.addBindValue(name);
    query.addBindValue(path);
    query.addBindValue(dirInfo.absoluteFilePath());
    query.addBindValue(QVariant()); // parent_directory_id
    query.addBindValue(dirInfo.birthTime().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(dirInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(dirInfo.lastRead().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(icon);

    if (!query.exec()) {
      qWarning() << "Failed to insert directory:" << dirPath
        << "Error:" << query.lastError().text();
      return false;
    }

    return true;
  }

  /**
   * @brief 自动插入目录记录
   * @param dirsPath 单个目录路径或目录路径列表
   * @return 是否成功
   * @thread 线程安全
   */
  static bool autoInsert(const QVariant& dirsPath)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    QSqlQuery query(*db);
    query.prepare(
      "INSERT INTO Directory ("
      "directory_name, directory_path, directory_absFilePath, "
      "parent_directory_id, creation_date, "
      "modification_date, last_access_date, icon_path"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?)"
    );

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool success = true;
    try {
      if (dirsPath.typeId() == QVariant::StringList) {
        for (const QString& dirPath : dirsPath.toStringList()) {
          if (!insertDirectory(query, dirPath)) {
            throw std::runtime_error("Failed to insert directory");
          }
        }
      }
      else if (dirsPath.typeId() == QVariant::String) {
        if (!insertDirectory(query, dirsPath.toString())) {
          throw std::runtime_error("Failed to insert directory");
        }
      }
      else { throw std::runtime_error("Unsupported input type"); }

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
    } catch (const std::exception& e) {
      qWarning() << "Error during directory insertion:" << e.what();
      db->rollback();
      success = false;
    }

    return success;
  }

  /**
   * @brief 获取所有目录路径
   * @return 目录路径列表
   * @thread 线程安全
   */
  static QStringList getAllPaths()
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return {};
    }

    QSqlQuery query(*db);
    if (!query.exec("SELECT directory_path FROM Directory")) {
      qWarning() << "Failed to get directory paths:"
        << query.lastError().text();
      return {};
    }

    QStringList paths;
    while (query.next()) {
      if (const QString path = query.value(0).toString(); !path.isEmpty()) {
        paths.append(path);
      }
    }

    return paths;
  }

  /**
   * @brief 删除目录记录
   * @param dirPath 要删除的目录路径
   * @return 是否成功
   * @thread 线程安全
   */
  static bool remove(const QString& dirPath)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    QSqlQuery query(*db);
    query.prepare("DELETE FROM Directory WHERE directory_path = ?");
    query.bindValue(0, dirPath);

    if (!query.exec()) {
      qWarning() << "Failed to remove directory:" << dirPath
        << "Error:" << query.lastError().text();
      return false;
    }
    return true;
  }
};
