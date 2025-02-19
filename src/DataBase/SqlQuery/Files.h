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
#include <QListView>
#include <QMap>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QListView>
#include <QTabWidget>

#include "../../Utils/ThreadWorkers/File/FilesDBWorker.h"
#include "../../Utils/Tools/CustomQueryModel.h"
#include "../../Utils/Tools/DataUnitCalc.h"
#include "../../Utils/Tools/IconTextDelegate.h"
#include "Directory.h"

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

class FilesDB {
public:
  /**
   * @brief 插入单个文件记录
   * @param query 预处理的查询对象
   * @param fileInfo 文件信息
   * @return 是否成功
   */
  static bool insertFile(QSqlQuery& query, const FileInfo& fileInfo)
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

    if (!query.exec()) {
      /// 这里报错 database is locked Unable to fetch row被上锁
      return false;
    }
    return true;
  }

  /**
   * @brief 自动插入文件记录
   * @param filesPath 单个文件路径或文件路径列表(完整路径)
   * @return 是否成功
   * @thread-safety 线程安全
   */
  static bool autoInsert(const QVariant& filesPath)
  {
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return false;
    }

    QSqlQuery query(*db);

    query.prepare(
      "INSERT INTO Files ("
      "file_name, file_path, file_absFilePath, directory_id, file_size, "
      "file_type, creation_date, modification_date, last_access_date, "
      "md5_hash, icon_path) "
      "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?) "
      "ON CONFLICT(file_absFilePath) DO UPDATE SET "
      "file_name = excluded.file_name, "
      "file_absFilePath = excluded.file_absFilePath, "
      "directory_id = excluded.directory_id, "
      "file_size = excluded.file_size, "
      "file_type = excluded.file_type, "
      "creation_date = excluded.creation_date, "
      "modification_date = excluded.modification_date, "
      "last_access_date = excluded.last_access_date, "
      "md5_hash = excluded.md5_hash, "
      "icon_path = excluded.icon_path;"
    );

    if (!db->transaction()) {
      qWarning() << "Failed to begin transaction";
      return false;
    }

    bool success = true;
    try {
      if (filesPath.typeId() == QVariant::StringList) {
        // 如果是 list，循环处理
        for (const QString& filePath : filesPath.toStringList()) {
          FileInfo info = createFileInfo(filePath);
          if (fileIsExistByAbsFile(filePath)) {
            throw std::runtime_error("File is Exist");
          }
          if (!insertFile(query, info)) {
            throw std::runtime_error("Failed to insert file");
          }
        }
      }
      else if (filesPath.typeId() == QVariant::String) {
        FileInfo info = createFileInfo(filesPath.toString());
        if (fileIsExistByAbsFile(filesPath.toString())) {
          throw std::runtime_error("File is Exist");
        }
        if (!insertFile(query, info)) {
          throw std::runtime_error("Failed to insert file");
        }
      }
      else { throw std::runtime_error("Unsupported input type"); }

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
    } catch (const std::exception& e) {
      qWarning() << "Error during file insertion:" << e.what();
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
  static QMap<QString, QDateTime> getAllFilesWithModTime()
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
  static bool updateFile(const QVariant& path)
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

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
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
  static bool removeFile(const QVariant& path)
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

      if (!db->commit()) {
        throw std::runtime_error("Failed to commit transaction");
      }
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
  static QVector<FileInfo> getAllFilesWithSameHash(const QString& directoryPath,
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
  static QString getHashByAbsPath(const QString& fileAbsPath)
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
      qWarning() << "Failed to get hash by absPath:"
        << query.lastError().text();
      return {};
    }
    return query.value(0).toString();
  }

  /**
   * @brief 判断文件是否存在
   * @param fileAbsPath 文件绝对路径
   * @return 是否存在
   */
  static bool fileIsExistByAbsFile(const QString& fileAbsPath)
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

  static void getAllFilesShowView(const QString& dirPath, QTableView* view)
  {
    if (!view) {
      qWarning() << "Invalid view pointer";
      return;
    }

    if (auto* oldModel = view->model()) {
      view->setModel(nullptr);
      oldModel->deleteLater();
    }

    // 设置新模型
    auto* queryModel = getAllFilesInDir(dirPath);
    view->setModel(queryModel);

    // 给第0列自定义委托用于绘制图标
    view->setItemDelegateForColumn(0, new IconTextDelegate(view));
  }

  static void getAllFilesShowView(const QString& dirPath, QListView* view,
                                  const bool isIconView = false)
  {
    if (!view) {
      qWarning() << "Invalid view pointer";
      return;
    }

    // 获取已有模型并释放内存
    if (auto* oldModel = view->model()) {
      view->setModel(nullptr);
      oldModel->deleteLater();
    }

    // 获取文件数据
    auto* queryModel = getAllFilesInDir(dirPath);

    // 设置视图模式
    if (isIconView) {
      view->setViewMode(QListView::IconMode);
      view->setIconSize(QSize(64, 64));
      view->setGridSize(QSize(90, 90));
      view->setSpacing(10);
      view->setWrapping(true);
      view->setResizeMode(QListView::Adjust);
      view->setMovement(QListView::Static);
    }
    else {
      view->setViewMode(QListView::ListMode);
      view->setIconSize(QSize(16, 16));
      view->setSpacing(2);
    }

    // 设置视图属性
    view->setUniformItemSizes(true);
    view->setSelectionMode(QAbstractItemView::ExtendedSelection);

    // 设置模型到视图
    view->setModel(queryModel);
  }

  /**
   * @brief 获取所有文件信息
   * @param dirPath 目录路径
   */
  static QSqlQueryModel* getAllFilesInDir(const QString& dirPath)
  {
    auto* queryModel = new CustomQueryModel();

    if (dirPath.isEmpty()) {
      qWarning() << "Directory path is empty";
      return queryModel;
    }

    // 获取数据库连接
    const auto db = SqlManager::instance().getDatabase();
    if (!db) {
      qWarning() << "Failed to get database connection";
      return queryModel;
    }

    // 构造查询
    QSqlQuery query(*db);
    query.prepare(
      "SELECT "
      "file_name         AS '名称', "
      "file_path         AS '路径', "
      "file_size         AS '大小', "
      "file_type         AS '类型', "
      "creation_date     AS '创建时间', "
      "modification_date AS '修改时间', "
      "last_access_date  AS '最近修改时间', "
      "md5_hash          AS '哈希值', "
      "icon_path          AS '图标路径', "
      "CASE "
      "    WHEN is_encrypted = 0 THEN '否' "
      "    ELSE '是' "
      "END AS '是否加密' "
      "FROM Files WHERE file_path LIKE :path"
    );
    query.bindValue(":path", dirPath + "%");

    if (!query.exec()) {
      qWarning() << "Failed to get files in directory:"
        << dirPath << "Error:" << query.lastError().text();
      return queryModel;
    }

    queryModel->setQuery(std::move(query));
    return queryModel;
  }

private:
  static FileInfo createFileInfo(const QString& fileAbsPath)
  {
    const QFileInfo fileInfo(fileAbsPath);
    return FileInfo{
      fileInfo.fileName(),
      fileInfo.absolutePath(),
      fileAbsPath,
      fileInfo.size(),
      fileInfo.suffix(),
      fileInfo.birthTime().toString("yyyy/MM/dd hh:mm"),
      fileInfo.lastModified().toString("yyyy/MM/dd hh:mm"),
      fileInfo.lastRead().toString("yyyy/MM/dd hh:mm"),
      getHashByAbsPath(fileAbsPath),
      false,
      ":/suffixes/res/suffix/" + fileInfo.suffix().toLower() + ".png"
    };
  }
};
