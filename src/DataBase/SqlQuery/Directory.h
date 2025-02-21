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
   * @param absPath 目录路径
   * @return 目录ID，失败返回-1，正确返回ID号
   * @thread 线程安全
   */
  static int getDirectoryId(const QString& absPath)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return -1;
    }

    QSqlQuery query(*db);
    query.prepare(
      "SELECT directory_id FROM Directory WHERE "
      "directory_absFilePath = ?");
    query.addBindValue(absPath);

    if (!query.exec() || !query.next()) { return -1; }

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

    // 如果文件记录已经存在直接返回
    if (getDirectoryId(dirInfo.absolutePath()) != -1) { return true; }

    // 处理根目录和普通目录
    const QString name =
      dirInfo.isRoot() ? dirPath.left(2) : dirInfo.fileName();
    query.addBindValue(name);
    const QString path = dirInfo.isRoot() ? "" : dirInfo.absolutePath();
    query.addBindValue(path);
    query.addBindValue(dirInfo.absoluteFilePath());
    const int parentId = getDirectoryId(path);
    query.addBindValue(parentId == -1 ? QVariant() : parentId); ///< 父目录ID
    query.addBindValue(dirInfo.birthTime().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(dirInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
    query.addBindValue(dirInfo.lastRead().toString("yyyy/MM/dd hh:mm"));
    const QString iconPath = dirInfo.isRoot()
                               ? ":/icons/res/icons/disk.png"
                               : ":/icons/res/icons/directory.png";

    query.addBindValue(iconPath);

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

    // 插入的 SQL 语句，在 insertDirectory 中使用执行
    QSqlQuery query(*db);
    query.prepare(
      "INSERT INTO Directory ("
      "directory_name, directory_path, directory_absFilePath, "
      "parent_directory_id, creation_date, "
      "modification_date, last_access_date, icon_path"
      ") VALUES (?, ?, ?, ?, ?, ?, ?, ?) "
      "ON CONFLICT(directory_absFilePath) DO UPDATE SET "
      "directory_name = excluded.directory_name, "
      "directory_absFilePath = excluded.directory_absFilePath, "
      "parent_directory_id = excluded.parent_directory_id, "
      "creation_date = excluded.creation_date, "
      "modification_date = excluded.modification_date, "
      "last_access_date = excluded.last_access_date, "
      "icon_path = excluded.icon_path;"
    );

    if (!db->transaction()) { return false; } ///< 无法开启事务直接返回

    bool success = true;
    try {
      if (dirsPath.typeId() == QVariant::StringList) {
        // 如果是 list 循环处理
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
