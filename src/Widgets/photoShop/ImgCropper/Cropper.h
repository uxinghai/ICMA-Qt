/**
 * @file Cropper.h
 *
 * @Breife 裁剪器模式选择，提供简单模式和功能更多的高级裁剪模式
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

class Cropper final : public QMainWindow {
  Q_OBJECT

public:
  explicit Cropper(QString filePath, QWidget* parent = nullptr);
  ~Cropper() override;

signals:
  void WindowClose();
  void ProcessedPixmap(QPixmap pixmap);

public slots:
  void doCustomCrop();
  void doSimpleCrop();
  void closeEvent(QCloseEvent* event) override;
  void doGetProcessedPixmap(const QPixmap& pixmap);

private:
  void setupLayout();

  QPushButton* btnCustomCrop;
  QPushButton* btnSimpleCrop;
  QString filePath; ///< 待裁剪图像路径
};
