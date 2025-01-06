// /**
//  * @file FilesDBWorker
//  * @brief 系统文件写入数据库的头文件
//  *
//  * 该头文件在用户选择导入文件时使用
//  * 用于将指定路径文件写入数据库
//  * 写入数据库采用事务，原子性操作，确保数据一致性
//  *
//  * @author uxinghai
//  * @date 2024.10.21
//  */
//
// #ifndef FILESDBWORKER_H
// #define FILESDBWORKER_H
//
// #include <QCryptographicHash>
// #include <QFileInfo>
// #include <QObject>
//
// #include "cell/MainWindow.h"
// #include "SqlManager.h"
//
// extern QString DataBasePath;
//
// class FilesDBWorker : public QObject {
//     Q_OBJECT
// public:
//     explicit FilesDBWorker(const QStringList &files, QObject *parent = nullptr)
//         : QObject(parent), filesPath(files) {}
//
//     ~FilesDBWorker() {
//         if (SqlManager::instance().getDatabase().isOpen()) {
//             SqlManager::instance().getDatabase().close();
//         }
//     }
//
//     void start() {
//         if (filesPath.isEmpty()) {
//             emit resultReady(0);
//             return;
//         }
//         emit resultReady(writeToDataBase());
//     }
//
// signals:
//     void resultReady(qint32 filesNum);
//     void progressUpdated(int current, int total);
//
// protected:
//     QString calculateMD5(QFile &file) {
//         QCryptographicHash hash(QCryptographicHash::Md5);
//         constexpr qint64 bufferSize = 8 * 1024;           // 每次读取 8KB
//         QByteArray buffer(bufferSize, Qt::Uninitialized); // 预先分配 8KB 大小的缓冲区
//
//         qint64 bytesRead = 0;
//         qint32 cnt = 0;
//         while (!file.atEnd()) {
//             bytesRead = file.read(buffer.data(), bufferSize);
//             if (bytesRead > 0) {
//                 hash.addData(QByteArrayView(buffer.constData(), bytesRead));
//             }
//
//             // 每 100 次循环调用一次 processEvents
//             if (++cnt % 100 == 0) {
//                 QCoreApplication::processEvents();
//             }
//         }
//
//         return hash.result().toHex();
//     }
//
//     qint32 writeToDataBase() {
//         qint32 res = 0;
//         if (!SqlManager::instance().openDatabase(DataBasePath)) {
//             qDebug() << "Failed to open database at "
//                      << DataBasePath;
//             return 0;
//         }
//
//         QSqlDatabase db = SqlManager::instance().getDatabase();
//         db.transaction(); // 启用事务!
//
//         QSqlQuery query(db);
//         const qint32 totalFiles = filesPath.size();
//
//         for (auto i = 0; i < filesPath.size(); ++i) {
//             const auto &path = filesPath[i];
//             QFileInfo fileInfo(path); // 提取元数据
//
//             emit progressUpdated(i + 1, totalFiles);
//
//             if (!fileInfo.exists() || !fileInfo.isFile()) {
//                 qDebug() << "File does not exist or is not a regular file: "
//                          << path;
//                 continue;
//             }
//
//             QFile file(fileInfo.filePath());
//             if (!file.open(QIODevice::ReadOnly)) {
//                 qDebug() << "Failed to open file: "
//                          << fileInfo.absoluteFilePath();
//                 continue;
//             }
//
//             QString md5Hash = calculateMD5(file);
//             file.close();
//
//             if (!insertOrUpdateFile(query, fileInfo, md5Hash)) {
//                 qDebug() << "Failed to insert or update file: "
//                          << fileInfo.absoluteFilePath();
//                 continue;
//             }
//
//             if (!recordUserAction(query)) {
//                 qDebug() << "Failed to record user action";
//                 continue;
//             }
//
//             res++;
//         }
//
//         if (!db.commit()) {
//             db.rollback();
//             qDebug() << "Transaction failed, rolling back changes";
//             return 0;
//         }
//
//         return res;
//     }
//
// private:
//     // sqlite特有方法，如果存在则更新。类似地，insert or ignore
//     bool insertOrUpdateFile(QSqlQuery &query, const QFileInfo &fileInfo,
//                             const QString &md5Hash) {
//         query.prepare(
//             "INSERT OR REPLACE INTO Files ("
//             "   file_name, file_path, file_size, file_type, "
//             "   creation_date, modification_date, last_access_date, "
//             "   md5_hash, is_encrypted"
//             ") VALUES ("
//             "   :file_name, :file_path, :file_size, :file_type, "
//             "   :creation_date, :modification_date, :last_access_date, "
//             "   :md5_hash, :is_encrypted"
//             ")");
//
//         query.bindValue(":file_name", fileInfo.fileName());
//         query.bindValue(":file_path", fileInfo.absolutePath()); // 使用绝对路径
//         query.bindValue(":file_size", fileInfo.size());
//         query.bindValue(":file_type", fileInfo.suffix().toLower()); // 统一使用小写后缀
//         query.bindValue(":creation_date", fileInfo.birthTime());
//         query.bindValue(":modification_date", fileInfo.lastModified());
//         query.bindValue(":last_access_date", fileInfo.lastRead());
//         query.bindValue(":md5_hash", md5Hash);
//         query.bindValue(":is_encrypted", false);
//
//         return query.exec();
//     }
//
//     bool recordUserAction(QSqlQuery &query) {
//         query.prepare(
//             "INSERT INTO UserActions (action_type, action_date) "
//             "VALUES (:action_type, :action_date)");
//
//         query.bindValue(":action_type", static_cast<int>(FileActionType::Edit));
//         query.bindValue(":action_date", QDateTime::currentDateTime());
//
//         return query.exec();
//     }
//
//     const QStringList filesPath;
// };
//
// #endif // FILESDBWORKER_H