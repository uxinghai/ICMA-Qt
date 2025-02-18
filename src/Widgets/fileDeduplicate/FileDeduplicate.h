/**
 * @file FileDeduplicate.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/2/7
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE

namespace Ui
{
  class FileDeduplication;
}

QT_END_NAMESPACE

class FileDeduplicate final : public QMainWindow {
  Q_OBJECT

public:
  explicit FileDeduplicate(QWidget* parent = nullptr);
  ~FileDeduplicate() override;

signals:
  void WindowClose();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void getDeduplicationFiles(const QString& directoryPath, bool recursive);
  void doDelete();
  void setUIEnabled(bool enabled);
  void setHandCkStateChange(int state);
  void doBrowseDirectory();
  void doScanDirectory();

private:
  void init();
  void setupConnections();

  Ui::FileDeduplication* ui;

  QString directoryPath; ///< 要扫描的文件夹路径
  bool handSelect;

  struct DeleteResult {
    int totalFiles;
    int successCount;
    DeleteResult() = default;

    DeleteResult(const qint64 size, const int i) : totalFiles(size),
                                                   successCount(i) {}
  };

  void updateProgressBar(int current, int total) const;
  DeleteResult executeFileDeletion(const QStringList& filesToDelete) const;
  void showDeleteResult(const DeleteResult& result);
  QStringList getSelectedFilePaths() const;
  QStringList getDuplicateFilePaths() const;
  bool confirmDeletion(int fileCount);
};
