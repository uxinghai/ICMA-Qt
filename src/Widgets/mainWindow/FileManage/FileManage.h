// /**
//  * @file FileManage.h
//  *
//  * @Breife 文件管理类
//  *         用于处理系统文件写入数据库，处理数据库文件在UI的显示
//  *
//  * @version 1.0
//  * @date 2025/1/9
//  *
//  * @author uxinghai
//  * @copyright Copyright (c) 2025
//  */
//
// #pragma once
//
// #include <QClipboard>
// #include <QDesktopServices>
// #include <QFuture>
// #include <QFutureWatcher>
// #include <QLabel>
// #include <QMainWindow>
// #include <QMessageBox>
// #include <QProgressBar>
// #include <QTableWidgetItem>
// #include <QtConcurrent/QtConcurrent>
//
// class FileManage final : public QObject {
//   Q_OBJECT
//
// public:
//   explicit FileManage(QWidget* parent = nullptr);
//   ~FileManage() override;
//
// protected:
//   void initializeTableData(const QFileInfoList& list);
//
// private slots:
//   void on_btnBrowse_clicked();
//   void on_btnSearch_clicked();
//   void on_tableWidget_customContextMenuRequested(const QPoint& pos);
//   void on_actOpen_triggered();
//   void on_actOpenPath_triggered();
//   void on_actCopy_triggered();
//   void on_tableWidget_itemDoubleClicked(QTableWidgetItem* item);
//
//   void on_leTerm_textEdited(const QString& term);
//
// private:
//   QLabel* lbLoad;
//   QString path; // Path selected by the user
//   static QString term;
//
//   QFutureWatcher<qint32> watcher;
//   QFuture<qint32> future;
//   QFutureWatcher<void> watcher2;
//   QFuture<void> future2;
//
//   QProgressBar* progress;
//   static QMutex mutex;
//   static QFileInfoList res;       // Stores all matching files
//   static QFileInfoList filterRes; // 过滤后的res
//   // Custom enum class for cell marking for subsequent operations
//   enum Type {
//     BaseName,
//     Path,
//     Suffix,
//     Size,
//     DateTime
//   };
//
//   void createItems(int i, const QFileInfoList& list);
//   void updateUIForSearching(bool isSearching);
//   void showErrorMessage(const QString& message);
//   void openFileOrPath(const QString& filePath);
//
//   void showFile(const QString& path);
//
//   static qint32 handleFilesInDirectory(const QString& path);
//   static bool filterFilesInfo(const QFileInfo& fileInfo);
// };
