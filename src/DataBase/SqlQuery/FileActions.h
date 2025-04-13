/**
 * @file FileActions.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/3/23
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QSqlQuery>
#include <QString>

#include "../../Manager/SqlManager.h"

class FileActionsDB {
public:
  static FileActionsDB& getInstance()
  {
    static FileActionsDB instance;
    return instance;
  }

  // 更新文件操作信息（最近操作类型）， 如果类型是打开则更新打开次数
  void updateFileAction(const QString& absFilePath, const QString& actionType)
  {
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return;
        }
      }

      QSqlQuery query(*db);
      // 优化SQLite配置提高写入性能
      query.exec("PRAGMA journal_mode=WAL");
      query.exec("PRAGMA synchronous=NORMAL");
      query.exec("PRAGMA cache_size=10000"); ///< 可以自己配置大小
      query.exec("PRAGMA temp_store=MEMORY");

      if (searchFileByAbsFilePath(absFilePath)) {
        // 更新现有记录
        query.prepare(
          "UPDATE FileActions SET action_type = :actionType, action_date = :actionDate "
          "WHERE absFilePath = :absFilePath");
      }
      else {
        // 插入新记录
        query.prepare(
          "INSERT INTO FileActions (absFilePath, action_type, action_date, openCount) "
          "VALUES (:absFilePath, :actionType, :actionDate, :openCount)");
        query.bindValue(":openCount", 0);
      }

      query.bindValue(":absFilePath", absFilePath);
      query.bindValue(":actionType", actionType);
      query.bindValue(":actionDate", QDateTime::currentDateTime().toString(Qt::ISODate));

      if (!query.exec()) {
        qWarning() << "Failed to update file action:" << query.lastError().text();
      }
    }

    // 如果是打开操作还要更新文件打开次数+1
    if (actionType == "打开") {
      if (const auto* db = SqlManager::instance().getDatabase().data()) {
        if (db->isValid() && db->isOpen()) {
          QSqlQuery countQuery(*db);

          countQuery.prepare(
            "UPDATE FileActions SET openCount = openCount + 1 "
            "WHERE absFilePath = :absFilePath");
          countQuery.bindValue(":absFilePath", absFilePath);

          if (!countQuery.exec()) {
            qWarning() << "Failed to update open count:" << countQuery.lastError().text();
          }
        }
      }
    }
  }

  bool searchFileByAbsFilePath(const QString& absFilePath)
  {
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return false;
        }
      }

      QSqlQuery query(*db);

      query.prepare(
        "select FileActions.action_id from FileActions where absFilePath = :absFilePath");
      query.bindValue(":absFilePath", absFilePath);

      if (query.exec()) { while (query.next()) { return true; } }
    }
    return false;
  }

  quint16 getFileOpenCntByAbsPath(const QString& fileAbsPath)
  {
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return 0;
        }
      }

      QSqlQuery query(*db);

      query.prepare(
        "select openCount from FileActions where absFilePath = ?");
      query.addBindValue(fileAbsPath);
      if (query.exec() && query.next()) { return query.value(0).toUInt(); }
    }
    return 0;
  }
};

#define sFileActionsDB FileActionsDB::getInstance()
