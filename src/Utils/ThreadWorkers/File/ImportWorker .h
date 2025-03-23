/**
 * @file ImportWorker
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

#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QThread>

// 导入工作线程类
class ImportWorker final : public QThread {
  Q_OBJECT

public:
  ImportWorker(const QVector<QVariantList>& data, const QString& connectionName,
               QObject* parent = nullptr)
    : QThread(parent), data(data), connectionName(connectionName) {}

signals:
  void progressUpdated(int percentage);
  void importFinished(bool success);

protected:
  void run() override
  {
    // 在新线程中创建数据库连接
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", connectionName + "_thread");
    db.setDatabaseName(QSqlDatabase::database(connectionName).databaseName());

    if (!db.open()) {
      emit importFinished(false);
      return;
    }

    QSqlQuery query(db);

    // 优化SQLite配置提高写入性能
    query.exec("PRAGMA journal_mode=WAL");
    query.exec("PRAGMA synchronous=NORMAL");
    query.exec("PRAGMA cache_size=10000");
    query.exec("PRAGMA temp_store=MEMORY");

    // 准备插入语句 - 根据你的表结构调整
    query.prepare(
      "INSERT INTO your_table_name (column1, column2, column3) VALUES (?, ?, ?)");

    const int totalRecords = data.size();
    int processedRecords = 0;

    // 开始事务
    db.transaction();

    for (const QVariantList& record : data) {
      // 绑定参数 - 根据你的表结构调整参数的数量
      query.bindValue(0, record.at(0));
      query.bindValue(1, record.at(1));
      query.bindValue(2, record.at(2));

      if (!query.exec()) {
        qDebug() << "Insert error:" << query.lastError().text();
        db.rollback();
        emit importFinished(false);
        db.close();
        return;
      }

      processedRecords++;

      // 每批次提交一次事务
      if (constexpr int batchSize = 1000; processedRecords % batchSize == 0) {
        db.commit();
        db.transaction();

        // 发送进度信号
        const int progress = (processedRecords * 100) / totalRecords;
        emit progressUpdated(progress);
      }
    }

    // 提交最后的事务
    db.commit();
    db.close();

    emit progressUpdated(100);
    emit importFinished(true);
  }

private:
  QVector<QVariantList> data;
  QString connectionName;
};
