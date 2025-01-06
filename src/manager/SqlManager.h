/**
* @file SqlManager.h
 * @brief 数据库管理器的头文件
 *
 * 该头文件用于管理本应用程序的数据库
 * 并使用单例设计模式来确保只有一个实例
 * 只能通过instance.getDatabase()函数获取db，然后使用db连接数据库

 *
 * @author uxinghai
 * @date 2024.10.21
 */

/** sqlite 与 sqlServer 的区别
 *  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

 *  db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName(...);
    db.setDatabaseName(dbName);

 * 因为sqlite是嵌入式数据库，不涉及网络通信，所以不应该设置主机名
*/

#pragma once

#include <QSqlError>
#include <QSqlQuery>

#include "./Config/JsonManager.h"

class SqlManager {
public:
  SqlManager(const SqlManager&) = delete;
  SqlManager& operator=(const SqlManager&) = delete;

  /**
   * @brief 获取唯一实例
   * @return 静态的SqlManager对象
   */
  static SqlManager& instance()
  {
    static SqlManager _instance;
    return _instance;
  }

  void initSqlConfig()
  {
    dbFilePath = icmaRootDirPath + "/dataBase.db";
    if (!QFile::exists(dbFilePath)) {
      json = std::make_unique<JsonManager>();
      initDatabase(json->jsonObject());
    }
  }

  /**
   * @brief 打开数据库
   * @param dbPath .db 文件完整路径
   * @return 是否成功打开数据库的布尔值
   */
  bool openDatabase(const QString& dbPath)
  {
    if (!db.isOpen()) {
      db = QSqlDatabase::addDatabase("QSQLITE");
      db.setDatabaseName(dbPath);
      if (!db.open())
        return false;
    }
    return true;
  }

  /**
   * @brief 获取数据库
   * @return SqlDatabase
   */
  QSqlDatabase getDatabase() { return db; }

  /**
   * @brief 获取数据库名称(由setDatabaseName设定)
   * @return 返回名称(本系统找中实际是指完整路径)
   */
  [[nodiscard]] QString getDatabaseName() const { return db.databaseName(); }

  /**
   * @brief 关闭数据库并移除它
   */
  void closeDatabase()
  {
    if (db.isOpen()) { db.close(); }
    QSqlDatabase::removeDatabase(db.connectionName());
  }

  [[nodiscard]] QString DbFilePath() { return dbFilePath; }

private:
  // 把构造函数隐藏起来，并禁止一切拷贝方法
  SqlManager() {}
  ~SqlManager() { if (db.isOpen()) { db.close(); } }

  // 初始化数据库文件
  void initDatabase(const QJsonObject& obj) const
  {
    if (QFile::exists(dbFilePath))
      return;

    // 不存在则 创建数据库文件并建表
    QFile file(dbFilePath);
    if (!file.open(QIODevice::WriteOnly))
      return;
    file.close(); ///< 直接关闭 数据库文件交给sqlManager控制

    // 打开数据库
    SqlManager& dbInstance = instance();
    if (!dbInstance.openDatabase(dbFilePath)) {
      qWarning() << "Failed to open database:" << dbFilePath;
      return;
    }

    // 建表
    QSqlDatabase db = dbInstance.getDatabase();
    QSqlQuery query(db);
    QJsonArray tables = obj["database"].toObject()["tables"].toArray();
    db.transaction(); ///< 启用事务
    for (const auto& table : tables) {
      if (!query.exec(table.toObject()["sql"].toString())) {
        qWarning() << "Failed to create table:" << query.lastError().text();
        db.rollback(); ///< 回退
        return;
      }
    }

    if (!db.commit()) { ///< 提交
      qWarning() << "Failed to commit transaction:" << db.lastError().text();
      return;
    }

    dbInstance.closeDatabase();
  }

  QSqlDatabase db;
  QString dbFilePath;
  std::unique_ptr<JsonManager> json;
};
