/**
 * @file SqlManager.h
 *
 * @brief 线程安全的数据库管理器
 *
 * 该类使用单例模式和线程局部存储来确保在多线程环境下安全运行
 * 通过 QThreadStorage 让每个线程都管理自己的数据库连接实例
 *
 * @author uxinghai
 * @version 1.0
 *
 * @date 2024/10/21
 */

#pragma once

#include <QMutex>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>
#include <QThreadStorage>

#include "Config/iniManager.h"

// 数据库文件路径亦即数据库名，在程序启动时调用的 initSqlConfig 中被赋值，后续全局可用
inline QString dbFilePath; ///< 数据库文件路径
class SqlManager {
public:
  // 删除拷贝构造和赋值操作符
  SqlManager(const SqlManager&) = delete;
  SqlManager& operator=(const SqlManager&) = delete;

  /**
   * @brief 获取唯一实例
   * @return SqlManager的静态引用
   */
  static SqlManager& instance()
  {
    static SqlManager _instance;
    return _instance;
  }

  ///////////////////////////////////////////////////////////////////
  /////////////  通过 instance 调用 //////////////////////////////////
  /**
   * @brief 初始化SQL配置
   * @thread 线程安全
   */
  void initSqlConfig() const
  {
    QMutexLocker locker(&mutex);
    dbFilePath = icmaRootDirPath + "/ICMA.db";
    // 如果文件不存在则创建文件并初始化数据库
    if (!QFile::exists(dbFilePath)) { initDatabase(); }
  }

  /**
   * @brief 获取当前线程的数据库连接(打开的数据库)
   * @return 数据库连接的共享指针
   * @thread 线程安全，每个线程获取独立的连接
   */
  QSharedPointer<QSqlDatabase> getDatabase()
  {
    // 检查当前线程内是否有数据库
    if (!threadLocalDb.hasLocalData()) {
      const auto db = QSharedPointer<QSqlDatabase>::create
      (QSqlDatabase::addDatabase(
        "QSQLITE",
        QString("Connection-%1").arg(
          reinterpret_cast<quintptr>(QThread::currentThread()))));
      db->setDatabaseName(dbFilePath);
      if (!db->open()) {
        qWarning() << "Failed to open database for thread:" <<
          QThread::currentThread()
          << "Error:" << db->lastError().text();
        return nullptr;
      }
      threadLocalDb.setLocalData(db);
    }
    return threadLocalDb.localData();
  }

  /**
   * @brief 获取数据库名称
   * @return 数据库文件路径
   * @thread 线程安全
   */
  [[nodiscard]] QString getDatabaseName() const
  {
    QMutexLocker locker(&mutex);
    return dbFilePath;
  }

  /**
   * @brief 关闭当前线程的数据库连接
   * @thread 线程安全
   */
  void closeDatabase()
  {
    if (threadLocalDb.hasLocalData()) {
      if (const auto db = threadLocalDb.localData();
        db && db->isOpen()) {
        {
          QMutexLocker locker(&mutex);
          db->close();
        }
        QSqlDatabase::removeDatabase(db->connectionName());
      }
      threadLocalDb.setLocalData(nullptr);
    }
  }

  /**
   * @brief 获取数据库文件路径
   * @return 数据库文件路径
   * @thread 线程安全
   */
  [[nodiscard]] QString DbFilePath() const
  {
    QMutexLocker locker(&mutex);
    return dbFilePath;
  }

private:
  SqlManager() = default;

  ~SqlManager()
  {
    // 确保所有线程的连接都被正确关闭
    threadLocalDb.setLocalData(nullptr);
  }

  /**
   * @brief 初始化数据库文件和表结构，只被 initSqlConfig 调用
   * 不使用QMutexLocker locker(&mutex);因为这个函数只被 initSqlConfig调用而initSqlConfig
   * 中已经上锁确保线程安全，此处再次上锁会导致死锁问题!!!
   * @note 私有的辅助函数不上锁！！！
   */
  static void initDatabase()
  {
    if (QFile::exists(dbFilePath)) { return; }

    // 创建数据库文件
    QFile file(dbFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
      qWarning() << "Failed to create database file:" << dbFilePath;
      return;
    }
    file.close();

    // 创建数据库连接
    const auto db = QSharedPointer<QSqlDatabase>::create(
      QSqlDatabase::addDatabase("QSQLITE", "init-connection"));
    db->setDatabaseName(dbFilePath);
    if (!db->open()) {
      qWarning() << "Failed to open database:" << dbFilePath;
      return;
    }

    QSqlQuery query(*db);

    // SQL文件路径列表
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

    // 开启事务
    if (!db->transaction()) {
      qWarning() << "Failed to start transaction:" << db->lastError().text();
      db->close();
      QSqlDatabase::removeDatabase(db->connectionName());
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

      QString sqlContent = QString::fromUtf8(sqlFile.readAll());
      sqlFile.close();

      QStringList statements = sqlContent.split(';', Qt::SkipEmptyParts);
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
      if (!db->commit()) {
        qWarning() << "Failed to commit transaction:" << db->lastError().text();
        db->rollback();
      }
    }
    else {
      db->rollback();
      qWarning() << "Rolling back transaction due to errors";
    }

    db->close();
    QSqlDatabase::removeDatabase(db->connectionName());
  }

  mutable QMutex mutex;                                       ///< 用于保护共享资源
  QThreadStorage<QSharedPointer<QSqlDatabase>> threadLocalDb; ///< 线程局部存储的数据库连接
};
