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
    dbFilePath = icmaRootDirPath + "/ICMA.db";
    if (!QFile::exists(dbFilePath)) { initDatabase(); }
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
    // db 在打开时会确保正确
    if (db.isOpen()) { db.close(); }
    QSqlDatabase::removeDatabase(db.connectionName());
  }

  [[nodiscard]] QString DbFilePath() { return dbFilePath; }

private:
  // 把构造函数隐藏起来，并禁止一切拷贝方法
  SqlManager() {}
  ~SqlManager() { if (db.isOpen()) { db.close(); } }

  // 初始化数据库文件
  void initDatabase() const
  {
    if (QFile::exists(dbFilePath)) { return; }

    // ICMA.db文件不存在则新建
    QFile file(dbFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
      qWarning() << "Failed to create database file:" << dbFilePath;
      return;
    }
    file.close(); ///< 直接关闭，不需要这个file

    SqlManager& dbInstance = instance();
    if (!dbInstance.openDatabase(dbFilePath)) {
      qWarning() << "Failed to open database:" << dbFilePath;
      return;
    }

    QSqlDatabase db = dbInstance.getDatabase();
    QSqlQuery query(db);

    // 来自资源文件，因为资源文件不能被 QDir::entryList获取，所以写死
    const QVector<QString> sqlPaths{
      ":/sql/res/SQLite3_ICMA/Directory.sql",
      ":/sql/res/SQLite3_ICMA/FileActions.sql",
      ":/sql/res/SQLite3_ICMA/FileContent.sql",
      ":/sql/res/SQLite3_ICMA/FileMetadata.sql",
      ":/sql/res/SQLite3_ICMA/Files.sql",
      ":/sql/res/SQLite3_ICMA/FileSimilarity.sql",
      ":/sql/res/SQLite3_ICMA/FileTags.sql",
      ":/sql/res/SQLite3_ICMA/HistoryActions.sql",
      ":/sql/res/SQLite3_ICMA/Tags.sql"
    };

    // 开启事务 准备建表
    if (!db.transaction()) {
      qWarning() << "Failed to start transaction:" << db.lastError().text();
      dbInstance.closeDatabase();
      return;
    }

    bool success = true;
    for (const auto& sqlPath : sqlPaths) {
      QFile sqlFile(sqlPath);
      if (!sqlFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open SQL file:" << sqlPath;
        success = false;
        break;
      }

      // 读取 SQL 文件内容
      QString sqlContent = QString::fromUtf8(sqlFile.readAll());
      sqlFile.close();

      // 分割多条 SQL 语句, sqlite不能多条一起执行
      QStringList statements = sqlContent.split(';', Qt::SkipEmptyParts);

      // 逐条执行 SQL 语句
      for (const QString& statement : statements) {
        QString trimmedStmt = statement.trimmed();
        if (trimmedStmt.isEmpty()) { continue; }

        if (!query.exec(trimmedStmt)) {
          qWarning() << "Failed to execute SQL statement from" << sqlPath << ":"
            << query.lastError().text() << "\nStatement:" << trimmedStmt;
          success = false;
          break;
        }
      }

      if (!success) { break; }
    }

    if (success) {
      if (!db.commit()) {
        qWarning() << "Failed to commit transaction:" << db.lastError().text();
        db.rollback();
      }
    }
    else {
      db.rollback();
      qWarning() << "Rolling back transaction due to errors";
    }

    dbInstance.closeDatabase();
  }

  QSqlDatabase db;
  QString dbFilePath;
};
