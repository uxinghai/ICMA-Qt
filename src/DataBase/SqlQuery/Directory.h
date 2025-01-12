/**
 * @file Directory.h
 *
 * @Breife 存放一系列用于操作 Directory 表的 sql 语句
 *
 * @version 1.0
 * @date 2025/1/12
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <QDir>

#include "SqlQueryHelper.h"

namespace DirectoryHelper // 隐藏其可见性，尽量不被外部使用
{
  inline bool insertDirectory(QSqlQuery& query, const QString& dirPath)
  {
    const QFileInfo dirInfo(dirPath);
    QString name = dirInfo.fileName();
    QString icon = ":/icons/res/icons/directory.png";
    QString path = dirInfo.absolutePath();

    if (dirInfo.isRoot()) {
      name = dirPath.left(2);
      icon = ":/icons/res/icons/disk.png";
      path = "";
    }

    query.bindValue(0, name);
    query.bindValue(1, path);
    query.bindValue(2, dirInfo.birthTime().toString("yyyy/MM/dd hh:mm"));
    query.bindValue(3, dirInfo.lastModified().toString("yyyy/MM/dd hh:mm"));
    query.bindValue(4, dirInfo.lastRead().toString("yyyy/MM/dd hh:mm"));
    query.bindValue(5, icon);

    if (!query.exec()) {
      qWarning() << "Failed to insert directory:" << dirPath
        << "Error:" << query.lastError().text();
      return false;
    }
    return true;
  }
}

// 操作 Directory 表
namespace Directory
{
  inline bool autoInsert(const QVariant& dirsPath)
  {
    auto dataBase = SqlQueryHelper::ensureDatabaseIsOpen();
    if (!dataBase.isValid()) {
      qWarning() << "Failed to open database";
      return false;
    }

    QSqlQuery query(dataBase);
    query.prepare("INSERT INTO Directory("
      "directory_name, directory_path, creation_date, "
      "modification_date, last_access_date, icon_path) "
      "VALUES (?, ?, ?, ?, ?, ?)");

    // 开始事务
    if (!dataBase.transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool hasError = false;

    // 处理目录（单个或多个）
    if (dirsPath.typeId() == QVariant::StringList) {
      const QStringList dirList = dirsPath.toStringList();
      for (const auto& dirPath : dirList) {
        if (!DirectoryHelper::insertDirectory(query, dirPath)) {
          hasError = true;
          break;
        }
      }
    }
    else if (dirsPath.typeId() == QVariant::String) {
      if (!DirectoryHelper::insertDirectory(query, dirsPath.toString())) {
        hasError = true;
      }
    }
    else {
      qWarning() << "Unsupported input type for dirsPath";
      return false;
    }

    // 根据执行结果提交或回滚事务
    if (hasError) { dataBase.rollback(); }
    else { dataBase.commit(); }

    SqlQueryHelper::ensureDatabaseIsClose();
    return !hasError;
  }
}
