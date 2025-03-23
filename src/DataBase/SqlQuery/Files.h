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
#include <QHeaderView>
#include <QMap>
#include <QTableView>

#include "../../Utils/Tools/CalculateHash.h"
#include "../../Utils/Tools/IconTextDelegate.h"
#include "../../Utils/Tools/LogOut.h"
#include "../../Utils/Tools/MyQueryModel.h"
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

class FilesDB final: public  QObject{
  Q_OBJECT
public:
  static FilesDB& getInstance() {
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
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      sLog.log("无法打开数据库-Files.h");
      return false;
    }

    // 准备三种语句
    QSqlQuery insertQuery(*db);
    QSqlQuery findQuery(*db);
    QSqlQuery updateQuery(*db);

    // 优化SQLite配置提高写入性能
    insertQuery.exec("PRAGMA journal_mode=WAL");
    insertQuery.exec("PRAGMA synchronous=NORMAL");
    insertQuery.exec("PRAGMA cache_size=10000"); // 可以自己配置大小
    insertQuery.exec("PRAGMA temp_store=MEMORY");

    // 准备查找语句（通过MD5和文件大小查找）
    findQuery.prepare(
      "SELECT file_absFilePath, file_name FROM Files WHERE md5_hash = ? AND file_size = ?");

    // 准备更新语句
    updateQuery.prepare(
      "UPDATE Files SET "
      "file_name = ?, file_path = ?, file_absFilePath = ?, directory_id = ?, "
      "file_type = ?, modification_date = ?, last_access_date = ?, "
      "icon_path = ?, op_time = ? "
      "WHERE md5_hash = ? AND file_size = ?"
    );

    // 准备插入语句
    insertQuery.prepare(
      "INSERT INTO Files ("
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
          //sLog.logf("处理文件：%s",filePath.toStdString().c_str());
          FileInfo info = createFileInfo(filePath);

          // 通过MD5和文件大小检查文件是否已存在
          findQuery.bindValue(0, info.md5Value);
          findQuery.bindValue(1, info.fileSize);

          if (findQuery.exec() && findQuery.next()) {
            // 文件内容已存在，但路径可能不同，更新记录
            QString existingPath = findQuery.value(0).toString();
            QString existingName = findQuery.value(1).toString();

            // 更新现有记录
            updateQuery.bindValue(0, info.fileName);
            updateQuery.bindValue(1, info.filePath);
            updateQuery.bindValue(2, info.fileAbsFilePath);
            updateQuery.bindValue(3, -1);
            updateQuery.bindValue(4, info.fileType);
            updateQuery.bindValue(5, info.modificationDate);
            updateQuery.bindValue(6, info.lastAccessDate);
            updateQuery.bindValue(7, info.iconPath);
            updateQuery.bindValue(8, QDateTime::currentDateTime());
            updateQuery.bindValue(9, info.md5Value);
            updateQuery.bindValue(10, info.fileSize);

            if (!updateQuery.exec()) {
              throw std::runtime_error("Failed to update file");
            }
          }
          else {
            // 文件不存在，插入新记录
            if (!insertFile(insertQuery, info)) {
              throw std::runtime_error("Failed to insert file");
            }
          }

          processedRecords++;

          // 中途提交事务处理
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
        FileInfo info = createFileInfo(filesPath.toString());

        // 通过MD5和文件大小检查文件是否已存在
        findQuery.bindValue(0, info.md5Value);
        findQuery.bindValue(1, info.fileSize);

        if (findQuery.exec() && findQuery.next()) {
          // 文件内容已存在，但路径可能不同，更新记录
          QString existingPath = findQuery.value(0).toString();
          QString existingName = findQuery.value(1).toString();

          // 更新现有记录
          updateQuery.bindValue(0, info.fileName);
          updateQuery.bindValue(1, info.filePath);
          updateQuery.bindValue(2, info.fileAbsFilePath);
          updateQuery.bindValue(3, -1);
          updateQuery.bindValue(4, info.fileType);
          updateQuery.bindValue(5, info.modificationDate);
          updateQuery.bindValue(6, info.lastAccessDate);
          updateQuery.bindValue(7, info.iconPath);
          updateQuery.bindValue(8, QDateTime::currentDateTime());
          updateQuery.bindValue(9, info.md5Value);
          updateQuery.bindValue(10, info.fileSize);

          if (!updateQuery.exec()) { throw std::runtime_error("Failed to update file"); }
        }
        else {
          // 文件不存在，插入新记录
          if (!insertFile(insertQuery, info)) {
            throw std::runtime_error("Failed to insert file");
          }
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
    return success;
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

   qint32 getAllFilesShowView(const QString& dirPath, QTableView* view,
                                    const quint8& filterMode)
  {
    if (!view) {
      qWarning() << "Invalid view pointer";
      return 0;
    }

    if (auto* oldModel = view->model()) {
      view->setModel(nullptr);
      oldModel->deleteLater();
    }

    // 设置新模型
    MyQueryModel* queryModel = getAllFilesInDir(dirPath, filterMode);
    view->setModel(queryModel);
    // 表头右键菜单
    QObject::connect(view->horizontalHeader(),
                     &QHeaderView::sortIndicatorChanged,
                     queryModel, &MyQueryModel::sort);
    // 给第0列自定义委托用于绘制图标
    view->setItemDelegateForColumn(0, new IconTextDelegate(view));

    // 假设第9列是计数列，需要获取第一行的第9列的值
    // 检查是否有数据
    if (queryModel->rowCount() > 0) {
      // 创建第一行第9列的模型索引
      const QModelIndex countIndex = queryModel->index(0, 9);
      // 获取该单元格的数据并转换为整数
      return queryModel->data(countIndex).toInt();
    }

    // 如果没有数据，返回0
    return 0;
  }

  /**
   * @brief 获取所有文件信息
   * @param dirPath 目录路径
   * @param filterMode 文件过滤
   */
   MyQueryModel* getAllFilesInDir(const QString& dirPath,
                                        const quint8 filterMode)
  {
    const auto myQueryModel = new MyQueryModel();

    // 检查路径是否为空
    if (dirPath.isEmpty()) {
      qWarning() << "Directory path is empty";
      return myQueryModel;
    }

    // 获取数据库连接
    const auto db = SqlManager::instance().getDatabase().data();
    if (!db->isValid() || !db->isOpen()) {
      qWarning() << "Database is not open. Trying to reconnect...";
      if (!db->open()) {
        qWarning() << "Failed to reopen database!";
        return myQueryModel;
      }
    }

    // 构造 SQL 查询
    QString queryString =
      "SELECT file_name AS '名称', file_path AS '路径', file_size AS '大小', "
      "file_type AS '类型', creation_date AS '创建时间', modification_date AS '修改时间', "
      "last_access_date AS '最近修改时间', md5_hash AS '哈希值', icon_path AS '图标路径', "
      "CASE WHEN is_encrypted = 0 THEN '否' ELSE '是' END AS '是否加密'"
      "FROM Files WHERE file_path LIKE :path";

    // 只有当filterMode不为0时，才添加文件类型过滤条件
    if (filterMode > 0) {
      QString filterCondition;
      switch (filterMode) {
      case 1: ///< 音频
        filterCondition = "file_type IN ('mp3', 'wav', 'flac', 'aac', 'ogg')";
        break;
      case 2: ///< 压缩文件
        filterCondition = "file_type IN ('zip', 'rar', '7z', 'tar', 'gz')";
        break;
      case 3: ///< 文档
        filterCondition =
          "file_type IN ('pdf', 'doc', 'docx', 'xls', 'xlsx', 'ppt', 'pptx', 'txt')";
        break;
      case 4: ///< 可执行文件
        filterCondition = "file_type IN ('exe', 'dll', 'bin', 'sh')";
        break;
      case 5: ///< 文件夹
        filterCondition = "file_type = 'folder'";
        break;
      case 6: ///< 图片
        filterCondition =
          "file_type IN ('jpg', 'jpeg', 'png', 'gif', 'bmp', 'svg')";
        break;
      case 7: ///< 视频
        filterCondition = "file_type IN ('mp4', 'avi', 'mkv', 'mov', 'flv')";
        break;
      default:
        // 如果不是已知的filterMode，就不添加过滤条件
        break;
      }

      if (!filterCondition.isEmpty()) { queryString += " AND (" + filterCondition + ")"; }
    }

    // 打印调试信息，帮助排查问题
    // qDebug() << "SQL Query: " << queryString;
    // qDebug() << "Filter Mode: " << filterMode;

    QSqlQuery query(*db);
    query.prepare(queryString);
    query.bindValue(":path", dirPath + "%");

    if (!query.exec()) {
      qWarning() << "Failed to get files in directory: " << dirPath <<
        " Error: "
        << query.lastError().text();
      return myQueryModel;
    }

    myQueryModel->setQuery(std::move(query));

    return myQueryModel;
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

  // 创建新方法，支持将搜索和过滤模式结合使用 isRegexSearch其实用不到...
   qint32 searchFilesShowView(const QString& searchTerm,
                                    const QString& dirPath,
                                    QTableView* view, const bool isRegexSearch,
                                    const quint8& filterMode)
  {
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
    if (filterMode > 0) {
      switch (filterMode) {
      case 1: // 音频
        filterCondition = "file_type IN ('mp3', 'wav', 'flac', 'aac', 'ogg')";
        break;
      case 2: // 压缩文件
        filterCondition = "file_type IN ('zip', 'rar', '7z', 'tar', 'gz')";
        break;
      case 3: // 文档
        filterCondition =
          "file_type IN ('pdf', 'doc', 'docx', 'xls', 'xlsx', 'ppt', 'pptx', 'txt')";
        break;
      case 4: // 可执行文件
        filterCondition = "file_type IN ('exe', 'dll', 'bin', 'sh')";
        break;
      case 5: // 文件夹
        filterCondition = "file_type = 'folder'";
        break;
      case 6: // 图片
        filterCondition =
          "file_type IN ('jpg', 'jpeg', 'png', 'gif', 'bmp', 'svg')";
        break;
      case 7: // 视频
        filterCondition = "file_type IN ('mp4', 'avi', 'mkv', 'mov', 'flv')";
        break;
      default: ;
      // 分支0会跳过这个switch，不添加任何筛选条件
      }
    }

    // 构造 SQL 查询
    QString queryString =
      "SELECT file_name AS '名称', file_path AS '路径', file_size AS '大小', "
      "file_type AS '类型', creation_date AS '创建时间', modification_date AS '修改时间', "
      "last_access_date AS '最近修改时间', md5_hash AS '哈希值', icon_path AS '图标路径', "
      "CASE WHEN is_encrypted = 0 THEN '否' ELSE '是' END AS '是否加密' "
      "FROM Files WHERE file_path LIKE :path";

    // 使用LIKE进行普通搜索
    queryString += " AND file_name LIKE :search";

    // 添加文件类型过滤条件
    if (!filterCondition.isEmpty()) { queryString += " AND (" + filterCondition + ")"; }

    QSqlQuery query(*db);
    query.prepare(queryString);
    query.bindValue(":path", dirPath + "%");

    // if (isRegexSearch) { query.bindValue(":search", searchTerm); }
    query.bindValue(":search", "%" + searchTerm + "%");

    if (!query.exec()) {
      qWarning() << "Failed to search files: " << query.lastError().text();
      return 0;
    }

    auto* queryModel = new MyQueryModel();
    queryModel->setQuery(std::move(query));
    view->setModel(queryModel);

    // 表头右键菜单
    QObject::connect(view->horizontalHeader(),
                     &QHeaderView::sortIndicatorChanged,
                     queryModel, &MyQueryModel::sort);
    // 给第0列自定义委托用于绘制图标
    view->setItemDelegateForColumn(0, new IconTextDelegate(view));

    return queryModel->rowCount();
  }

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

  //////////////////////////////////////////////////////////////////////////////
  /////////////////////////         推荐算法         ////////////////////////////
  //////////////////////////////////////////////////////////////////////////////
  // 用于推荐相关文件依据哈希值  使用汉明距离（适用于二进制哈希） similarityThreshold相似度阈值
   QMap<QString, QString> RecFileByHash(const QString& hashValue,
                                              const int similarityThreshold =
                                                68)
  {
    QMap<QString, QString> recommendedFiles;

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

      // 先查找完全匹配的文件
      query.prepare(
        "SELECT file_name, file_absFilePath FROM Files WHERE md5_hash = :hash");
      query.bindValue(":hash", hashValue);
      if (query.exec()) {
        while (query.next()) {
          recommendedFiles.insert(query.value(0).toString(),
                                  query.value(1).toString());
        }
      }
      else {
        qWarning() << "Failed to query files by hash: " << query.lastError().
          text();
      }

      // 查找所有哈希值
      query.prepare("SELECT file_name, md5_hash, file_absFilePath FROM Files");
      if (!query.exec()) {
        qWarning() << "Failed to query all hashes: " << query.lastError().
          text();
        return recommendedFiles;
      }

      while (query.next()) {
        QString filePath = query.value(0).toString();
        QString dbHash = query.value(1).toString();

        const int distance = CalculateHammingDistance(hashValue, dbHash);
        const int similarity = 100 - (distance * 100 / 128); ///< MD5 是 128-bit

        if (similarity >= similarityThreshold) {
          recommendedFiles.insert(filePath, query.value(2).toString());
        }
      }
    }

    return recommendedFiles;
  }

   void deleteFileFormAbsPath(const QString& absFilePath)
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
      query.prepare("DELETE FROM Files WHERE file_absFilePath = :filePath");
      query.bindValue(":filePath", absFilePath);

      if (!query.exec()) {
        qWarning() << "Failed to delete file: " << query.lastError().text();
      }
    }
  }

private:
  // 解析文件信息并返回 FileInfo 结构体
   FileInfo createFileInfo(const QString& fileAbsPath)
  {
    const QFileInfo fileInfo(fileAbsPath);
    QString hashValue = getHashByAbsPath(fileAbsPath);
    if (hashValue.isEmpty()) {
      // 计算文件哈希值
      hashValue = calculateHash(fileAbsPath, QCryptographicHash::Md5);
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

   int CalculateHammingDistance(const QString& hash1,
                                      const QString& hash2)
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

signals:
  void progressUpdated(int progress);
};


#define sFileDB FilesDB::getInstance()