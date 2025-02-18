/**
* @file Cropper.h
 * @brief 裁剪器模式选择，提供简单模式和高级裁剪模式
 *
 * 该类提供模式选择功能，并打开对应的裁剪窗口。
 * 当裁剪窗口返回裁剪完成的图像时，
 * 该类将其转发到PS文件，并显示在界面上。
 *
 * @version 1.0
 * @date 2025/1/26
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QMainWindow>
#include <QPushButton>

class Cropper;
static Cropper* cropInstance = nullptr;

class Cropper final : public QMainWindow {
  Q_OBJECT

public:
  /**
   * @brief 获取唯一实例
   * @param filePath 待裁剪图像的路径
   * @param parent 父窗口指针
   * @return 返回 Cropper 的静态实例
   */
  static Cropper* getInstance(const QString& filePath,
                              QWidget* parent = nullptr)
  {
    cropInstance = nullptr;
    cropInstance = new Cropper(filePath, parent);

    if (cropInstance->isHidden()) { cropInstance->show(); }
    if (cropInstance->isMinimized()) { cropInstance->showNormal(); }
    cropInstance->raise();
    return cropInstance;
  }

  // 禁用拷贝和移动构造，以防止意外构建实例
  Cropper(const Cropper&) = delete;
  Cropper& operator=(const Cropper&) = delete;
  Cropper(Cropper&&) = delete;
  Cropper& operator=(Cropper&&) = delete;

  ~Cropper() override;

signals:
  void WindowClose();                       ///< 窗口关闭信号
  void ProcessedPixmap(QPixmap pixmap);     ///< 处理完成的图像信号
  void ProcessedError(const QString& text); ///< 处理错误信号

public slots:
  void doCustomCrop();                              ///< 执行高级裁剪
  void doSimpleCrop();                              ///< 执行简单裁剪
  void closeEvent(QCloseEvent* event) override;     ///< 处理窗口关闭事件
  void doGetProcessedPixmap(const QPixmap& pixmap); ///< 处理接收到的裁剪图像

private:
  explicit Cropper(QString filePath, QWidget* parent = nullptr);
  void setupLayout(); ///< 设置窗口布局

  QPushButton* btnCustomCrop; ///< 高级裁剪按钮
  QPushButton* btnSimpleCrop; ///< 简单裁剪按钮
  QString filePath;           ///< 待裁剪图像路径
};
