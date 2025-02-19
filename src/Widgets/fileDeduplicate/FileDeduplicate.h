/**
 * @file FileDeduplicate.h
 * @brief 文件去重工具的主窗口类定义
 *
 * 该文件定义了 `FileDeduplicate` 类，该类继承自 `QMainWindow`，用于提供文件去重功能的 GUI 界面，
 * 包括文件扫描、重复文件识别及删除等操作。
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
  /**
   * @brief 窗口关闭信号
   *
   * 在窗口关闭时触发该信号。
   */
  void WindowClose();

protected:
  /**
   * @brief 处理窗口关闭事件
   * @param event 窗口关闭事件指针
   */
  void closeEvent(QCloseEvent* event) override;

private slots:
  /**
   * @brief 获取指定目录中的重复文件
   * @param directoryPath 目标目录路径
   * @param recursive 是否递归扫描子目录
   */
  void getDeduplicationFiles(const QString& directoryPath, bool recursive);

  /**
   * @brief 执行删除选中的重复文件
   */
  void doDelete();

  /**
   * @brief 设置 UI 控件的启用/禁用状态
   * @param enabled 是否启用 UI 控件
   */
  void setUIEnabled(bool enabled);

  /**
   * @brief 处理“手动选择”复选框的状态变化
   * @param state 复选框的当前状态
   */
  void setHandCkStateChange(int state);

  /**
   * @brief 打开目录选择对话框
   */
  void doBrowseDirectory();

  /**
   * @brief 扫描选定的目录以查找重复文件
   */
  void doScanDirectory();

private:
  /**
   * @brief 设置信号与槽的连接
   */
  void setupConnections();

  Ui::FileDeduplication* ui; ///< UI 界面指针

  QString directoryPath; ///< 要扫描的文件夹路径
  bool handSelect;       ///< 是否启用手动选择模式

  /**
   * @brief 文件删除结果结构体
   *
   * 该结构体用于存储删除操作的结果信息，包括总文件数和成功删除的文件数。
   */
  struct DeleteResult {
    int totalFiles;   ///< 总文件数
    int successCount; ///< 成功删除的文件数

    /**
     * @brief 默认构造函数
     */
    DeleteResult() = default;

    /**
     * @brief 构造函数
     * @param size 总文件数
     * @param i 成功删除的文件数
     */
    DeleteResult(const qint64 size, const int i) : totalFiles(size),
                                                   successCount(i) {}
  };

  /**
   * @brief 更新进度条
   * @param current 当前进度
   * @param total 总进度
   */
  void updateProgressBar(int current, int total) const;

  /**
   * @brief 执行文件删除操作
   * @param filesToDelete 需要删除的文件列表
   * @return 删除操作的结果
   */
  DeleteResult executeFileDeletion(const QStringList& filesToDelete) const;

  /**
   * @brief 显示删除结果
   * @param result 删除操作的结果
   */
  void showDeleteResult(const DeleteResult& result);

  /**
   * @brief 获取用户选择的文件路径列表
   * @return 选中文件的路径列表
   */
  QStringList getSelectedFilePaths() const;

  /**
   * @brief 获取检测出的重复文件路径列表
   * @return 发现的重复文件路径列表
   */
  QStringList getDuplicateFilePaths() const;

  /**
   * @brief 确认删除操作
   * @param fileCount 需要删除的文件数量
   * @return 用户是否确认删除
   */
  bool confirmDeletion(int fileCount);
};
