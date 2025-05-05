/**
 * @file Files.h
 * @brief 线程安全的文件数据库操作接口
 *
 * 使用计数方法确保所有操作完成，即确保数据同步
 * 当前数据库使用样例如下：
 *  // 开始一个数据库操作
    sFileDB.startOperation();

    // 其他代码

    // 在操作结束时标记完成
    sFileDB.markOperationComplete();
 *
 * @version 2.0
 * @date 2025/1/12
 *
 * @author uxinghai
 */

#pragma once

#include <QDateTime>
#include <QFileInfo>
#include <QHeaderView>
#include <QMap>
#include <QTableView>
#include <qwaitcondition.h>

#include "../../Utils/Tools/CalculateHash.h"
#include "../../Utils/Tools/IconTextDelegate.h"
#include "../../Utils/Tools/LogOut.h"
#include "../../Utils/Tools/MyQueryModel.h"
#include "../../Widgets/mainWindow/RegexHelper.h"
#include "Directory.h"

class MyQueryModel;

struct FileInfo {
  QString fileName;
  QString filePath;
  QString fileAbsFilePath;
  qsizetype fileSize;
  QString fileType;
  QString creationDate;
  QString modificationDate;
  QString lastAccessDate;
  QString md5Value;
  bool isEncrypted;
  QString iconPath;

  FileInfo() = default;

  FileInfo(const QString& fileName, const QString& filePath,
           const QString& fileAbsFilePath, const qsizetype fileSize,
           const QString& fileType, const QString& creationDate,
           const QString& modificationDate, const QString& lastAccessDate,
           const QString& md5Value, const bool& isEncrypted,
           const QString& iconPath)
    : fileName(fileName), filePath(filePath), fileAbsFilePath(fileAbsFilePath),
      fileSize(fileSize), fileType(fileType), creationDate(creationDate),
      modificationDate(modificationDate), lastAccessDate(lastAccessDate),
      md5Value(md5Value), isEncrypted(isEncrypted), iconPath(iconPath) {}
};

class FilesDB final : public QObject {
  Q_OBJECT

public:
  // 等待所有数据库操作完成
  void waitForCompletion()
  {
    QMutexLocker locker(&m_syncMutex);

    // 如果还有未完成的操作，则等待
    while (m_pendingOperations > 0) { m_syncCondition.wait(&m_syncMutex); }
  }

  // 标记数据库操作已完成
  void markOperationComplete()
  {
    QMutexLocker locker(&m_syncMutex);

    m_pendingOperations--;
    if (m_pendingOperations <= 0) {
      // 所有操作已完成，通知等待的线程
      m_syncCondition.wakeAll();
    }
  }

  // 在开始数据库操作前，增加计数
  void startOperation()
  {
    QMutexLocker locker(&m_syncMutex);
    m_pendingOperations++;
  }

  static FilesDB& getInstance()
  {
    static FilesDB instance;
    return instance;
  }

  /**
   * @brief 插入单个文件记录
   * @param query 预处理的查询对象
   * @param fileInfo 文件信息
   * @return 是否成功
   */
  bool insertFile(QSqlQuery& query, const FileInfo& fileInfo)
  {
    query.addBindValue(fileInfo.fileName);
    query.addBindValue(fileInfo.filePath);
    query.addBindValue(fileInfo.fileAbsFilePath);
    query.addBindValue(DirectoryDB::getDirectoryId(fileInfo.filePath));
    query.addBindValue(fileInfo.fileSize);
    query.addBindValue(fileInfo.fileType);
    query.addBindValue(fileInfo.creationDate);
    query.addBindValue(fileInfo.modificationDate);
    query.addBindValue(fileInfo.lastAccessDate);
    query.addBindValue(fileInfo.md5Value);
    query.addBindValue(fileInfo.iconPath);
    query.addBindValue(
      QDateTime::currentDateTime().toString("yyyy/MM/dd hh:mm"));

    if (!query.exec()) {
      /// 这里报错 database is locked Unable to fetch row被上锁
      return false;
    }

    //sLog.logf("处理文件：%s",fileInfo.fileAbsFilePath.toStdString().c_str());
    return true;
  }

  /**
   * @brief 自动插入文件记录
   * @param filesPath 单个文件路径或文件路径列表(完整路径)
   * @return 是否成功
   * @thread-safety 线程安全
   */
  bool autoInsert(const QVariant& filesPath)
  {
    startOperation();
    // 删除旧数据库内容
    if (!clearDBContext("TempFiles")) {
      sLog.log("系统自动删除了数据库[TempFiles]中的所有内容，为了添加新内容。");
      return false;
    }
    waitForCompletion();
    // 删除成功插入新数据
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      sLog.log("无法打开数据库，并插入新内容。 -Files.h");
      return false;
    }

    // 准备插入语句
    QSqlQuery insertQuery(*db);

    // 优化SQLite配置提高写入性能
    insertQuery.exec("PRAGMA journal_mode=WAL");
    insertQuery.exec("PRAGMA synchronous=NORMAL");
    insertQuery.exec("PRAGMA cache_size=10000"); ///< 可以自己配置大小
    insertQuery.exec("PRAGMA temp_store=MEMORY");

    // 准备插入语句
    insertQuery.prepare(
      "INSERT INTO TempFiles ("
      "file_name, file_path, file_absFilePath, directory_id, file_size, "
      "file_type, creation_date, modification_date, last_access_date, "
      "md5_hash, icon_path, op_time) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
    );

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool success = true;
    try {
      if (filesPath.typeId() == QVariant::StringList) {
        int processedRecords = 0;
        // 如果是 list，循环处理
        QStringList pathLists = filesPath.toStringList();
        int totalRecords = pathLists.size();
        for (const QString& filePath : pathLists) {
          // 直接插入新记录，不检查是否存在
          if (FileInfo info = createFileInfo(filePath);
            !insertFile(insertQuery, info)) {
            throw std::runtime_error("Failed to insert file");
          }

          processedRecords++;

          // 中途提交事务处理 提高性能
          if (constexpr int batchSize = 1000; processedRecords % batchSize == 0) {
            db->commit();
            db->transaction();

            // 发送进度信号
            const int progress = (processedRecords * 100) / totalRecords;
            emit progressUpdated(progress);
          }
        }
      }
      else if (filesPath.typeId() == QVariant::String) {
        // 直接插入新记录，不检查是否存在
        if (FileInfo info = createFileInfo(filesPath.toString());
          !insertFile(insertQuery, info)) {
          throw std::runtime_error("Failed to insert file");
        }
      }
      else { throw std::runtime_error("Unsupported input type"); }

      if (!db->commit()) { throw std::runtime_error("Failed to commit transaction"); }
    } catch (const std::exception& e) {
      qWarning() << "Error during file insertion:" << e.what();
      sLog.logf("处理文件失败:%s-Files.h", e.what());
      db->rollback();
      success = false;
    }
    qDebug() << "删除成功,新插入,FileTmpNum:" << getDBContextNumber("TempFiles");
    waitForCompletion();
    markOperationComplete();
    return success;
  }

  /**
   * @brief 删除数据库内容
   * @param dbName 数据库名称
   */
  bool clearDBContext(const QString& dbName)
  {
    startOperation();

    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    QSqlQuery query(*db);

    // 优化 SQLite 的性能设置
    query.exec("PRAGMA synchronous = OFF;");
    query.exec("PRAGMA journal_mode = MEMORY;");
    query.exec("PRAGMA temp_store = MEMORY;");

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    if (const QString sql = QString("DELETE FROM %1;").arg(dbName);
      !query.exec(sql)) {
      qWarning() << "Failed to delete table data:" << query.lastError().text();
      db->rollback();
      return false;
    }

    if (!db->commit()) {
      qWarning() << "Failed to commit transaction:" << db->lastError().text();
      db->rollback();
      return false;
    }

    markOperationComplete();
    return true;
  }

  /**
   * @brief 获取所有文件路径及其修改时间
   * @return 文件路径到修改时间的映射
   * @thread-safety 线程安全
   */
  QMap<QString, QDateTime> getAllFilesWithModTime()
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
   * @brief 更新文件大小和文件修改时间记录
   * @param path 单个文件路径或文件路径列表
   * @return 是否成功
   * @thread-safety 线程安全
   */
  bool updateFile(const QVariant& path)
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
      // 优化SQLite配置提高写入性能
      query.exec("PRAGMA journal_mode=WAL");
      query.exec("PRAGMA synchronous=NORMAL");
      query.exec("PRAGMA cache_size=10000"); ///< 可以自己配置大小
      query.exec("PRAGMA temp_store=MEMORY");
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

      if (!db->commit()) { throw std::runtime_error("Failed to commit transaction"); }
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
  bool removeFile(const QVariant& path)
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
      // 优化SQLite配置提高写入性能
      query.exec("PRAGMA journal_mode=WAL");
      query.exec("PRAGMA synchronous=NORMAL");
      query.exec("PRAGMA cache_size=10000"); ///< 可以自己配置大小
      query.exec("PRAGMA temp_store=MEMORY");
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

      if (!db->commit()) { throw std::runtime_error("Failed to commit transaction"); }
    } catch (const std::exception& e) {
      qWarning() << "Error during file removal:" << e.what();
      db->rollback();
      success = false;
    }

    return success;
  }

  /**
   * @brief 获取所有哈希值一致的文件路径
   * @param directoryPath filePath
   * @param recursive 是否递归子目录
   * @return
   */
  QVector<FileInfo> getAllFilesWithSameHash(const QString& directoryPath,
                                            const bool recursive)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return {};
    }

    QSqlQuery query(*db);
    QString normalizedPath = QDir::fromNativeSeparators(directoryPath);

    // 确保路径以 / 结尾
    if (!normalizedPath.endsWith('/')) { normalizedPath += '/'; }

    // 构建SQL查询
    QString sql =
      "WITH DirectoryFiles AS ("
      "    SELECT md5_hash "
      "    FROM Files "
      "    WHERE ";

    if (recursive) {
      // 递归模式：匹配目录本身和所有子目录
      sql += "file_path LIKE ? OR file_path = ? ";
    }
    else {
      // 非递归模式：只匹配当前目录，不包括子目录
      sql += "(file_path LIKE ? AND "
        "file_path NOT LIKE ? AND "
        "LENGTH(REPLACE(file_path, ?, '')) - LENGTH(REPLACE(file_path, '/', '')) = "
        "LENGTH(REPLACE(?, ?, '')) - LENGTH(REPLACE(?, '/', '')) + 1) "
        "OR file_path = ? ";
    }

    sql +=
      "    GROUP BY md5_hash "
      "    HAVING COUNT(*) > 1"
      ") "
      "SELECT file_name, file_path, file_absFilePath, file_size, "
      "       file_type, creation_date, modification_date, last_access_date, "
      "       md5_hash, is_encrypted, icon_path "
      "FROM Files "
      "WHERE md5_hash IN (SELECT md5_hash FROM DirectoryFiles) "
      "ORDER BY md5_hash, file_path;";

    query.prepare(sql);

    // 绑定参数
    if (recursive) {
      query.addBindValue(normalizedPath + "%");      // 匹配所有子目录
      query.addBindValue(normalizedPath.chopped(1)); // 匹配目录本身
    }
    else {
      query.addBindValue(normalizedPath + "%");   // LIKE 匹配当前目录下的文件
      query.addBindValue(normalizedPath + "%/%"); // NOT LIKE 排除子目录
      query.addBindValue("/");                    // 用于计算路径深度
      query.addBindValue(normalizedPath);
      query.addBindValue("/");
      query.addBindValue(normalizedPath);
      query.addBindValue(normalizedPath.chopped(1)); // 匹配目录本身
    }

    if (!query.exec()) {
      qWarning() << "Failed to get files with same hash:"
        << query.lastError().text()
        << "\nQuery:" << query.lastQuery()
        << "\nPath:" << normalizedPath;
      return {};
    }

    QVector<FileInfo> res;
    while (query.next()) {
      res.push_back(FileInfo{
        query.value(0).toString(),
        query.value(1).toString(),
        query.value(2).toString(),
        query.value(3).toLongLong(),
        query.value(4).toString(),
        query.value(5).toString(),
        query.value(6).toString(),
        query.value(7).toString(),
        query.value(8).toString(),
        query.value(9).toBool(),
        query.value(10).toString()
      });
    }

    return res;
  }

  /**
   * @brief 根据文件绝对路径获取文件哈希值
   * @param fileAbsPath 文件绝对路径
   * @return 文件哈希值
   */
  QString getHashByAbsPath(const QString& fileAbsPath)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return {};
    }

    QSqlQuery query(*db);
    query.prepare("SELECT md5_hash FROM Files WHERE file_absFilePath = ?");
    query.addBindValue(fileAbsPath);
    if (!query.exec() || !query.next()) {
      // qWarning() << "Failed to get hash by absPath:"
      //   << query.lastError().text();
      return {};
    }
    return query.value(0).toString();
  }

  /**
   * @brief 判断文件是否存在
   * @param fileAbsPath 文件绝对路径
   * @return 是否存在
   */
  bool fileIsExistByAbsFile(const QString& fileAbsPath)
  {
    if (fileAbsPath.isEmpty()) { return false; }
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return {};
    }

    QSqlQuery query(*db);
    query.prepare("SELECT COUNT(*) FROM Files WHERE file_absFilePath = ?");
    query.addBindValue(fileAbsPath);
    if (!query.exec() || !query.next()) {
      qWarning() << "Failed to check file existence:"
        << query.lastError().text();
      return false;
    }
    if (query.value(0).toInt() == 0) { return false; }
    return true;
  }

  QSqlQueryModel* getAllTermFilesInDir(const QString& term,
                                       const QString& dirPath,
                                       const bool isRegex = false)
  {
    auto* model = new QSqlQueryModel();

    QString sql;
    QSqlQuery query;

    if (dirPath.isEmpty()) {
      // 全局搜索
      if (isRegex) {
        // 使用正则表达式搜索
        sql = "SELECT * FROM files WHERE name REGEXP ? OR path REGEXP ?";
      }
      else {
        // 使用模糊匹配搜索
        sql = "SELECT * FROM files WHERE name LIKE ? OR path LIKE ?";
      }

      query.prepare(sql);

      if (isRegex) {
        query.addBindValue(term);
        query.addBindValue(term);
      }
      else {
        query.addBindValue("%" + term + "%");
        query.addBindValue("%" + term + "%");
      }
    }
    else {
      // 在指定目录下搜索
      if (isRegex) {
        // 使用正则表达式搜索
        sql =
          "SELECT * FROM files WHERE (name REGEXP ? OR path REGEXP ?) AND path LIKE ?";
      }
      else {
        // 使用模糊匹配搜索
        sql =
          "SELECT * FROM files WHERE (name LIKE ? OR path LIKE ?) AND path LIKE ?";
      }

      query.prepare(sql);

      if (isRegex) {
        query.addBindValue(term);
        query.addBindValue(term);
      }
      else {
        query.addBindValue("%" + term + "%");
        query.addBindValue("%" + term + "%");
      }

      query.addBindValue(dirPath + "%");
    }

    if (!query.exec()) {
      qDebug() << "Search files error:" << query.lastError().text();
      return model;
    }

    model->setQuery(std::move(query));
    return model;
  }

  // 获取指定目录下的文件条数
  qint32 getFileCount(const QString& dirPath)
  {
    if (dirPath.isEmpty()) { return 0; }

    // 获取数据库连接
    const auto db = SqlManager::instance().getDatabase().data();
    if (!db->isValid() || !db->isOpen()) {
      qWarning() << "Database is not open.";
      if (!db->open()) {
        qWarning() << "Failed to reopen database!";
        return 0;
      }
    }

    QSqlQuery query(*db);
    query.prepare("SELECT COUNT(*) FROM Files WHERE file_path LIKE :path");
    query.bindValue(":path", dirPath + "%");

    if (!query.exec()) {
      qWarning() << "Failed to count files: " << query.lastError().text();
      return 0;
    }
    if (query.next()) { return query.value(0).toInt(); }
    return 0;
  }

  // 解析文件信息并返回 FileInfo 结构体
  FileInfo createFileInfo(const QString& fileAbsPath, const bool& getHash = false)
  {
    const QFileInfo fileInfo(fileAbsPath);
    QString hashValue = "-1";
    if (getHash) {
      hashValue = getHashByAbsPath(fileAbsPath);
      if (hashValue.isEmpty()) {
        // 计算文件哈希值 不计算了，在用户点击具体文件时后台计算然后返回推荐以及文件信息
        hashValue = calculateHash(fileAbsPath, QCryptographicHash::Md5);
      }
    }

    return FileInfo{
      fileInfo.fileName(),
      fileInfo.absolutePath(),
      fileAbsPath,
      fileInfo.size(),
      fileInfo.suffix(),
      fileInfo.birthTime().toString("yyyy/MM/dd hh:mm"),
      fileInfo.lastModified().toString("yyyy/MM/dd hh:mm"),
      fileInfo.lastRead().toString("yyyy/MM/dd hh:mm"),
      hashValue,
      false,
      ":/suffixes/res/suffix/" + fileInfo.suffix().toLower() + ".png"
    };
  }

  // 获取数据库内容的数量 即数据空中所有条数
  quint32 getDBContextNumber(const QString& dbName)
  {
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return 0;
        }
      }

      // 使用指定的数据库连接创建查询对象
      QSqlQuery query(*db);
      if (!query.exec(QString("SELECT COUNT(*) FROM %1").arg(dbName))) {
        qWarning() << "Failed to count files: " << query.lastError().text();
        return 0;
      }

      if (query.next()) { return query.value(0).toInt(); }
    }
    return 0;
  }

  /**
 * @brief 搜索数据库文件，支持全部搜索和条件搜索
 * @param view 表格视图指针
 * @param filterMode 文件类型筛选模式
 * @param dbName 数据库名称
 * @param searchTerm 搜索词（可选，为空时搜索全部）
 * @return 搜索结果的行数
 */
  quint32 searchFilesFromDB(QTableView* view, const quint8& filterMode,
                            const QString& dbName, const QString& searchTerm = QString())
  {
    startOperation();

    if (!view) {
      qWarning() << "Invalid view pointer";
      return 0;
    }

    if (auto* oldModel = view->model()) {
      view->setModel(nullptr);
      oldModel->deleteLater();
    }

    // 获取数据库连接
    const auto db = SqlManager::instance().getDatabase().data();
    if (!db->isValid() || !db->isOpen()) {
      qWarning() << "Database is not open. Trying to reconnect...";
      if (!db->open()) {
        qWarning() << "Failed to reopen database!";
        return 0;
      }
    }

    // 文件类型筛选
    QString filterCondition;
    if (RegexHelper::filterTypeMap.contains(filterMode)) {
      QString fileExtensions = RegexHelper::filterTypeMap[filterMode];

      if (filterMode == 5) { // 文件夹特殊处理
        filterCondition = "file_type = " + fileExtensions;
      }
      else {
        QStringList extensions = fileExtensions.replace("'", "").split(", ");
        QStringList conditions;
        for (const QString& ext : extensions) {
          conditions.append("file_name LIKE '%." + ext + "'");
        }
        filterCondition = conditions.join(" OR ");
      }
    }

    // 构造基本SQL查询
    QString queryString =
      "SELECT file_name AS '名称', file_path AS '路径', file_size AS '大小', "
      "file_type AS '类型', creation_date AS '创建时间', modification_date AS '修改时间', "
      "last_access_date AS '最近修改时间', md5_hash AS '哈希值', icon_path AS '图标路径', "
      "CASE WHEN is_encrypted = 0 THEN '否' ELSE '是' END AS '是否加密' "
      "FROM " + dbName;

    // 构建 WHERE 子句
    QStringList whereConditions;

    // 添加文件类型过滤条件
    if (!filterCondition.isEmpty()) {
      whereConditions.append("(" + filterCondition + ")");
    }

    // 仅搜索文件名
    if (!searchTerm.isEmpty()) { whereConditions.append("file_name LIKE :searchTerm"); }

    // 组合所有 WHERE 条件
    if (!whereConditions.isEmpty()) {
      queryString += " WHERE " + whereConditions.join(" AND ");
    }

    // 确保获取最新数据
    db->transaction();
    // 创建查询对象并执行
    QSqlQuery query(*db);
    query.prepare(queryString);

    if (!searchTerm.isEmpty()) { query.bindValue(":searchTerm", "%" + searchTerm + "%"); }

    if (!query.exec()) {
      qWarning() << "Failed to search files:" << query.lastError().text();
      sLog.logf("查询文件错误：%s--Files:762", query.lastError().text());
      return 0;
    }

    auto* queryModel = new MyQueryModel();
    queryModel->setQuery(std::move(query));
    view->setModel(queryModel);

    // 表头右键菜单
    // connect(view->horizontalHeader(), &QHeaderView::sortIndicatorChanged,
    //         queryModel, &MyQueryModel::sort);

    // 给第0列自定义委托用于绘制图标
    view->setItemDelegateForColumn(0, new IconTextDelegate(view));
    db->commit();
    markOperationComplete();
    return queryModel->rowCount();
  }

  QStringList getDBDisticntCol(const QString& dbName, const QString& col)
  {
    QStringList res;
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return {};
        }
      }

      QSqlQuery query(*db);
      if (!query.exec(QString("SELECT DISTINCT %1 FROM %2").arg(col).arg(dbName))) {
        qWarning() << "Failed to count files: " << query.lastError().text();
        return {};
      }

      while (query.next()) {
        if (QString value = query.value(0).toString(); !value.isEmpty()) {
          res.append(value);
        }
      }
    }

    return res;
  }

  /**
   * @brief 根据文件路径删除数据库中的行
   * @param file_path  文件路径
   */
  void delectRowByFilePath(const QString& file_path, const QString& dbName)
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
      query.prepare(QString("Delete from %1 where file_path = :file_path").arg(dbName));
      query.bindValue(":file_path", file_path);

      if (!query.exec()) {
        qWarning() << "Failed to delete row: " << query.lastError().text();
        sLog.logf("删除文件错误：%s--Files:851", query.lastError().text());
      }
    }
  }

  void delectRowByFileAbsPath(const QString& file_Abspath, const QString& dbName)
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
      query.prepare("Delete from :Table where file_absFilePath = :file_absFilePath");
      query.bindValue(":file_absFilePath", file_Abspath);
      query.bindValue(":Table", dbName);

      if (!query.exec()) {
        qWarning() << "Failed to delete row: " << query.lastError().text();
        sLog.logf("删除文件错误：%s--Files:874", query.lastError().text());
      }
    }
  }

  /**
   * @brief 获取所有文件的绝对路径
   * @param dbName
   */
  QStringList getAllFileAbsPath(const QString& dbName)
  {
    QStringList res;
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return {};
        }
      }

      QSqlQuery query(*db);
      if (!query.exec(QString("SELECT file_absFilePath FROM %1").arg(dbName))) {
        qWarning() << "Failed to count files: " << query.lastError().text();
        return {};
      }

      while (query.next()) {
        if (QString value = query.value(0).toString(); !value.isEmpty()) {
          res.append(value);
        }
      }
    }
    return res;
  }

  /**
   * @brief  插入文件信息
   * @param dbName
   * @param info
   */
  void insertFileInto(const QString& dbName, const FileInfo& info)
  {
    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return;
        }
      }

      // 准备插入语句
      QSqlQuery insertQuery(*db);

      // 优化SQLite配置提高写入性能
      insertQuery.exec("PRAGMA journal_mode=WAL");
      insertQuery.exec("PRAGMA synchronous=NORMAL");
      insertQuery.exec("PRAGMA cache_size=10000"); ///< 可以自己配置大小
      insertQuery.exec("PRAGMA temp_store=MEMORY");

      // 准备插入语句
      QString queryStr = QString(
        "INSERT INTO %1 ("
        "file_name, file_path, file_absFilePath, directory_id, file_size, "
        "file_type, creation_date, modification_date, last_access_date, "
        "md5_hash, icon_path, op_time) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
      ).arg(dbName);

      insertQuery.prepare(queryStr);

      insertQuery.addBindValue(info.fileName);
      insertQuery.addBindValue(info.filePath);
      insertQuery.addBindValue(info.fileAbsFilePath);
      insertQuery.addBindValue(QVariant());
      insertQuery.addBindValue(info.fileSize);
      insertQuery.addBindValue(info.fileType);
      insertQuery.addBindValue(info.creationDate);
      insertQuery.addBindValue(info.modificationDate);
      insertQuery.addBindValue(info.lastAccessDate);
      insertQuery.addBindValue(info.md5Value);
      insertQuery.addBindValue(info.iconPath);
      insertQuery.addBindValue(
        QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
      if (!insertQuery.exec()) {
        qWarning() << "Failed to insert file into database: "
          << insertQuery.lastError().text();
      }
    }
  }

  quint32 getFileIdByFileAbsPath(const QString& file_absPath, const QString& dbName)
  {
    startOperation();

    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return 0;
        }
      }

      QSqlQuery query(*db);
      if (!query.exec(
        QString("SELECT file_id FROM '%1' WHERE file_absFilePath = '%2'").
        arg(dbName, file_absPath))) {
        qWarning() << "Failed to count files: " << query.lastError().text();
        return 0;
      }
      while (query.next()) {
        if (QString value = query.value(0).toString(); !value.isEmpty()) {
          return value.toUInt();
        }
      }
    }

    markOperationComplete();

    return 0;
  }

  quint32 getAllContentFrom(QTableView* view, const QString& dbName)
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
      query.exec("SELECT 1");
      QString queryString =
        "SELECT file_name AS '名称', file_path AS '路径', file_size AS '大小', "
        "file_type AS '类型', creation_date AS '创建时间', modification_date AS '修改时间', "
        "last_access_date AS '最近修改时间', md5_hash AS '哈希值', icon_path AS '图标路径', "
        "CASE WHEN is_encrypted = 0 THEN '否' ELSE '是' END AS '是否加密' "
        "FROM " + dbName;

      query.prepare(queryString);

      if (!query.exec()) {
        qWarning() << "Failed to search files:" << query.lastError().text();
        sLog.logf("查询文件错误：%s--Files:762", query.lastError().text());
        return 0;
      }

      auto* queryModel = new MyQueryModel();
      queryModel->setQuery(std::move(query));
      view->setModel(queryModel);

      // 表头右键菜单
      connect(view->horizontalHeader(), &QHeaderView::sortIndicatorChanged,
              queryModel, &MyQueryModel::sort);

      // 给第0列自定义委托用于绘制图标
      view->setItemDelegateForColumn(0, new IconTextDelegate(view));

      return queryModel->rowCount();
    }
    return 0;
  }

  //////////////////////////////////////////////////////////////////////////////
 /////////////////////////         推荐算法         ////////////////////////////
 //////////////////////////////////////////////////////////////////////////////
  // 用于推荐相关文件依据哈希值  使用汉明距离（适用于二进制哈希） similarityThreshold相似度阈值
  struct FileRecommendation {
    QString filePath;             // 文件路径
    QStringList recommendReasons; // 推荐原因列表
  };

  // 用于排序的文件信息结构
  struct RecFileInfo {
    QString fileName;
    QString filePath;
    int openCount;
    QDateTime lastModified;
    int similarity;
  };

  QMap<QString, FileRecommendation> RecFileByHash(const QString& hashValue,
                                                  const int similarityThreshold = 68)
  {
    startOperation();
    // 结果列表
    QList<RecFileInfo> fileInfoList;
    QMap<QString, FileRecommendation> recommendedFiles;

    if (hashValue.isEmpty()) { return recommendedFiles; }

    if (auto* db = SqlManager::instance().getDatabase().data()) {
      if (!db->isValid() || !db->isOpen()) {
        qWarning() << "Database is not open.";
        if (!db->open()) {
          qWarning() << "Failed to reopen database!";
          return recommendedFiles;
        }
      }

      QSqlQuery query(*db);

      // 先查找完全匹配的文件（相似度设为100）
      query.prepare(
        "SELECT Files.file_name,Files.file_path,Files.modification_date,"
        "FileActions.openCount FROM Files LEFT JOIN FileActions ON "
        "Files.file_absFilePath=FileActions.absFilePath WHERE "
        "Files.md5_hash= :hash"
        " GROUP BY Files.file_name, Files.file_path, Files.modification_date");
      query.bindValue(":hash", hashValue);
      if (query.exec()) {
        while (query.next()) {
          RecFileInfo info;
          info.fileName = query.value(0).toString();
          info.filePath = query.value(1).toString();
          info.lastModified = query.value(2).toDateTime();
          info.openCount = query.value(3).toInt();
          info.similarity = 100; // 完全匹配

          fileInfoList.append(info);
        }
      }
      else {
        qWarning() << "Failed to query files by hash: " << query.lastError().text();
      }

      // 查找相似文件 首先获取文件信息以及被打开次数
      query.prepare(
        "SELECT f.file_name,f.md5_hash,f.file_absFilePath,COALESCE(o.openCount,0) "
        "as openCount,f.modification_date FROM Files f LEFT JOIN ("
        "SELECT absFilePath,openCount from FileActions) o ON f.file_absFilePath=o.absFilePath");

      if (!query.exec()) {
        qWarning() << "Failed to query all hashes: " << query.lastError().text();

        // 即使查询失败，也处理已获取的完全匹配结果
        processRecommendations(fileInfoList, recommendedFiles);
        return recommendedFiles;
      }

      // 当前日期，用于计算是否是最近3天修改的文件
      QDateTime currentDate = QDateTime::currentDateTime();

      while (query.next()) {
        const QString fileName = query.value(0).toString();
        QString dbHash = query.value(1).toString();
        const QString filePath = query.value(2).toString();
        const int openCount = query.value(3).toInt();
        const QDateTime modifiedDate = query.value(4).toDateTime();

        // 跳过完全匹配的，因为已经在前面查询中处理过了
        if (dbHash == hashValue) { continue; }

        RecFileInfo info;
        info.fileName = fileName;
        info.filePath = filePath;
        info.openCount = openCount;
        info.lastModified = modifiedDate;

        const int distance = CalculateHammingDistance(hashValue, dbHash);
        if (const int similarity = 100 - (distance * 100 / 128); // 相似文件
          similarity >= similarityThreshold) {
          info.similarity = similarity;
          fileInfoList.append(info);
        }
        else if (openCount >= 5) { // 常打开文件（超过5次）
          info.similarity = 0;     // 不是因相似度推荐
          fileInfoList.append(info);
        }
        else if (currentDate.daysTo(modifiedDate) >= -3) { // 最近3天修改的文件
          info.similarity = 0;                             // 不是因相似度推荐
          fileInfoList.append(info);
        }
      }
    }

    // 按优先级排序: 打开次数（降序） > 最近修改时间（降序）> 相似度（降序）
    std::sort(fileInfoList.begin(), fileInfoList.end(),
              [](const RecFileInfo& a, const RecFileInfo& b) {
                if (a.openCount != b.openCount) {
                  return a.openCount > b.openCount; // 打开次数降序
                }
                if (a.lastModified != b.lastModified) {
                  return a.lastModified > b.lastModified; // 修改时间降序
                }
                return a.similarity > b.similarity; // 相似度降序
              });

    // 处理排序后的结果，添加推荐原因
    processRecommendations(fileInfoList, recommendedFiles);

    markOperationComplete();
    return recommendedFiles;
  }

  // 处理排序后的结果，添加推荐原因
  void processRecommendations(const QList<RecFileInfo>& fileInfoList,
                              QMap<QString, FileRecommendation>& recommendedFiles)
  {
    const QDateTime now = QDateTime::currentDateTime();

    for (const auto& [fileName, filePath,
           openCount, lastModified, similarity] :
         fileInfoList) {
      FileRecommendation rec;
      rec.filePath = filePath;

      // 添加推荐原因
      if (constexpr int HIGH_USAGE_THRESHOLD = 5;
        openCount >= HIGH_USAGE_THRESHOLD) { rec.recommendReasons.append("常使用"); }

      if (constexpr int RECENT_DAYS_THRESHOLD = 3;
        lastModified.daysTo(now) <= RECENT_DAYS_THRESHOLD) {
        rec.recommendReasons.append("最近修改");
      }
      if (constexpr int HIGH_SIMILARITY_THRESHOLD = 85;
        similarity >= HIGH_SIMILARITY_THRESHOLD) { rec.recommendReasons.append("相似"); }
      else if (similarity >= 60) {
        // 相似度较低但仍在阈值之上
        rec.recommendReasons.append(QString("部分相似(%1%)").arg(similarity));
      }

      // 如果没有特定原因，但文件匹配，添加一个默认原因
      if (rec.recommendReasons.isEmpty()) { rec.recommendReasons.append("匹配"); }

      recommendedFiles.insert(fileName, rec);
    }
  }

private:
  int CalculateHammingDistance(const QString& hash1, const QString& hash2)
  {
    if (hash1.size() != hash2.size()) { return 128; } ///< MD5 是 128-bit

    int distance = 0;
    bool ok;
    const quint64 h1_part1 = hash1.left(16).toULongLong(&ok, 16);
    const quint64 h1_part2 = hash1.right(16).toULongLong(&ok, 16);
    const quint64 h2_part1 = hash2.left(16).toULongLong(&ok, 16);
    const quint64 h2_part2 = hash2.right(16).toULongLong(&ok, 16);

    quint64 xor1 = h1_part1 ^ h2_part1;
    quint64 xor2 = h1_part2 ^ h2_part2;

    while (xor1) {
      distance += xor1 & 1;
      xor1 >>= 1;
    }
    while (xor2) {
      distance += xor2 & 1;
      xor2 >>= 1;
    }

    return distance;
  }

  QMutex m_syncMutex;
  QWaitCondition m_syncCondition;
  int m_pendingOperations = 0;

signals:
  void progressUpdated(int progress);
};

#define sFileDB FilesDB::getInstance()
