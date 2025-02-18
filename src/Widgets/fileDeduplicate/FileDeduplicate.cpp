#include "FileDeduplicate.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QtConcurrent>

#include "../../../UI/ui_FileDeduplication.h"
#include "../../DataBase/SqlQuery/Files.h"
#include "../../Utils/ThreadWorkers/File/FilesDBWorker.h"
#include "../../Utils/Tools/DataUnitCalc.h"

FileDeduplicate::FileDeduplicate(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::FileDeduplication), handSelect(false)
{
  ui->setupUi(this);
  setupConnections();
  init();
}

void FileDeduplicate::init()
{
  ui->progressBar->setValue(0);
  ui->btnDelete->setEnabled(false);
  setHandCkStateChange(false);
}

void FileDeduplicate::setupConnections()
{
  // 浏览按钮
  connect(ui->btnBrowse, &QPushButton::clicked, this,
          &FileDeduplicate::doBrowseDirectory);

  // 扫描按钮
  connect(ui->btnScan, &QPushButton::clicked, this,
          &FileDeduplicate::doScanDirectory);

  // 删除按钮
  connect(ui->btnDelete, &QPushButton::clicked, this,
          &FileDeduplicate::doDelete);

  // 手动选择checkbox
  connect(ui->handCheck, &QCheckBox::stateChanged, this,
          &FileDeduplicate::setHandCkStateChange);

  // 全选按钮
  connect(ui->toolBtnAllSelect, &QToolButton::clicked, [this]() {
    ui->resultTable->selectAll();
  });

  // 取消选择按钮
  connect(ui->toolBtnCancelSelect, &QToolButton::clicked, [this] {
    ui->resultTable->clearSelection();
  });

  // 反选按钮
  connect(ui->toolBtnReverse, &QToolButton::clicked, [this] {
    auto* selectionModel = ui->resultTable->selectionModel();
    for (int row = 0; row < ui->resultTable->rowCount(); ++row) {
      QModelIndex index = ui->resultTable->model()->index(row, 0);
      // Toggle：表示切换当前行的选中状态（如果已选中则取消选中，反之亦然）
      selectionModel->select(
        index, QItemSelectionModel::Toggle | QItemSelectionModel::Rows);
    }
  });  
}

void FileDeduplicate::updateProgressBar(const int current,
                                        const int total) const
{
  if (total > 0) { ui->progressBar->setValue(current * 100 / total); }
}

FileDeduplicate::DeleteResult FileDeduplicate::executeFileDeletion(
  const QStringList& filesToDelete) const
{
  DeleteResult result{filesToDelete.size(), 0};
  ui->progressBar->setValue(0);

  for (int i = 0; i < filesToDelete.size(); ++i) {
    const QString& filePath = filesToDelete[i];
    if (QFile file(filePath); file.remove()) {
      result.successCount++;
      FilesDB::removeFile(filePath);
    }
    updateProgressBar(i + 1, result.totalFiles);
  }

  return result;
}

void FileDeduplicate::showDeleteResult(const DeleteResult& result)
{
  QMessageBox::information(
    this,
    tr("删除完成"),
    tr("成功删除 %1 个文件，失败 %2 个文件。")
    .arg(result.successCount)
    .arg(result.totalFiles - result.successCount)
  );
}

QStringList FileDeduplicate::getSelectedFilePaths() const
{
  QStringList filePaths;
  for (const auto& item : ui->resultTable->selectedItems()) {
    if (item->column() == 1) { ///< 文件路径列
      filePaths.append(item->text() + "/" +
        ui->resultTable->item(item->row(), 0)->text());
    }
  }
  return filePaths;
}

QStringList FileDeduplicate::getDuplicateFilePaths() const
{
  QMap<QString, QList<QPair<QDateTime, QString>>> fileGroups;

  // 按文件名分组
  for (int i = 0; i < ui->resultTable->rowCount(); ++i) {
    QString fileName = ui->resultTable->item(i, 0)->text();
    QString filePath = ui->resultTable->item(i, 1)->text() + "/" + fileName;
    QDateTime modTime = QDateTime::fromString(
      ui->resultTable->item(i, 3)->text(),
      "yyyy-MM-dd HH:mm"
    );
    fileGroups[fileName].append(qMakePair(modTime, filePath));
  }

  QStringList filesToDelete;
  // 每组保留最早的文件，删除其他
  for (auto& group : fileGroups) {
    std::sort(group.begin(), group.end(),
              [](const auto& a, const auto& b) { return a.first < b.first; });
    for (int i = 1; i < group.size(); ++i) {
      filesToDelete.append(group[i].second);
    }
  }

  return filesToDelete;
}

bool FileDeduplicate::confirmDeletion(const int fileCount)
{
  const QString message = fileCount == 0
                            ? tr("确定要删除选中的文件吗？此操作不可恢复！")
                            : tr("确定要删除 %1 个重复文件吗？此操作不可恢复！").arg(fileCount);

  return QMessageBox::question(
    this,
    tr("确认删除"),
    message,
    QMessageBox::Yes | QMessageBox::No
  ) == QMessageBox::Yes;
}

void FileDeduplicate::doBrowseDirectory()
{
  const QString path = QFileDialog::getExistingDirectory(
    this, tr("打开文件夹"), "", QFileDialog::ShowDirsOnly);
  if (!path.isEmpty()) {
    directoryPath = path;
    ui->lePath->setText(directoryPath);
    ui->btnScan->setEnabled(true);
  }
}

void FileDeduplicate::doScanDirectory()
{
  if (directoryPath.isEmpty()) {
    QMessageBox::warning(this, tr("警告"), tr("请先选择要扫描的文件夹！"));
    return;
  }

  setUIEnabled(false);
  ui->progressBar->setValue(30);

  const bool recursive = ui->subfolderCheck->isChecked();
  QCoreApplication::processEvents();

  // 使用QtConcurrent进行异步扫描
  QFuture<void> future = QtConcurrent::run([this, recursive]() {
    FilesDBWorker::doScanDirectory(directoryPath, recursive);
  });

  // 等待扫描完成
  future.waitForFinished();

  ui->progressBar->setValue(90);
  getDeduplicationFiles(directoryPath, recursive);
  setUIEnabled(true);
}

void FileDeduplicate::doDelete()
{
  QStringList filesToDelete;

  if (handSelect) {
    filesToDelete = getSelectedFilePaths();
    if (filesToDelete.isEmpty()) {
      QMessageBox::warning(this, tr("警告"), tr("请选择要删除的文件！"));
      return;
    }
  }
  else {
    filesToDelete = getDuplicateFilePaths();
    qDebug() << filesToDelete;
    if (filesToDelete.isEmpty()) {
      QMessageBox::information(this, tr("无重复文件"),
                               tr("没有可删除的重复文件。"));
      return;
    }
  }

  if (!confirmDeletion(handSelect ? 0 : filesToDelete.size())) { return; }

  const DeleteResult result = executeFileDeletion(filesToDelete);
  getDeduplicationFiles(directoryPath, ui->subfolderCheck->isChecked());
  showDeleteResult(result);
}

void FileDeduplicate::setUIEnabled(const bool enabled)
{
  this->setEnabled(enabled);
  this->blockSignals(!enabled);
}

void FileDeduplicate::setHandCkStateChange(const int state)
{
  const bool isChecked = state == Qt::Checked;
  handSelect = isChecked;
  // 设置按钮可见性
  ui->toolBtnAllSelect->setVisible(isChecked);
  ui->toolBtnCancelSelect->setVisible(isChecked);
  ui->toolBtnReverse->setVisible(isChecked);

  // 设置按钮可用性
  ui->btnBrowse->setEnabled(!isChecked);
  ui->btnScan->setEnabled(!isChecked && !directoryPath.isEmpty());
  ui->btnDelete->setEnabled(isChecked);
  if (ui->resultTable->rowCount() > 0) { ui->btnDelete->setEnabled(true); }
  ui->toolBtnAllSelect->setEnabled(isChecked);
  ui->toolBtnCancelSelect->setEnabled(isChecked);
  ui->toolBtnReverse->setEnabled(isChecked);
}

void FileDeduplicate::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
  QMainWindow::closeEvent(event);
}

void FileDeduplicate::getDeduplicationFiles(const QString& directoryPath,
                                            const bool recursive)
{
  // 获取哈希值一致的文件路径（绝对路径）
  QVector<FileInfo> files =
    FilesDB::getAllFilesWithSameHash(directoryPath, recursive);
  if (files.empty()) {
    ui->btnDelete->setEnabled(false);
    ui->progressBar->setValue(100);
    QMessageBox::critical(this, tr("错误"), tr("没有找到重复的文件！"));
    return;
  }
  std::sort(files.begin(), files.end(),
            [](const FileInfo& file1, const FileInfo& file2) {
              // 按md5值排序相同则按修改时间升序排列
              if (file1.md5Value == file2.md5Value) {
                return file1.modificationDate < file2.modificationDate;
              }
              return file1.md5Value < file2.md5Value;
            });
  ui->btnDelete->setEnabled(true);
  // 所有相同的 files 显示在 UI 上
  ui->resultTable->setRowCount(0);
  ui->resultTable->setRowCount(files.size());
  ui->resultTable->horizontalHeader()->setStretchLastSection(true);
  for (int i = 0; i < files.size(); ++i) {
    ui->progressBar->setValue(i % 10 + 90);

    QList items = {
      new QTableWidgetItem(files[i].fileName),
      new QTableWidgetItem(files[i].filePath),
      new QTableWidgetItem(DataUnitCalc::setDataUnit(files[i].fileSize)),
      new QTableWidgetItem(files[i].modificationDate),
      new QTableWidgetItem(files[i].md5Value)
    };

    for (int j = 0; j < items.size(); ++j) {
      items[j]->setFlags(items[j]->flags() & ~Qt::ItemIsEditable); ///< 设置不可编辑
      ui->resultTable->setItem(i, j, items[j]);
    }
  }

  ui->resultTable->resizeColumnsToContents();
  ui->resultTable->resizeRowsToContents();
  ui->progressBar->setValue(100);
}

FileDeduplicate::~FileDeduplicate() { delete ui; }
