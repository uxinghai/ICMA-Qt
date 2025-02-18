/**
 * @file SimpleCropperDialog.h
 *
 * @Breife 简单裁剪--固定尺寸
 *
 * @version 1.0
 * @date 2025/1/26
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QDialog>
#include <QPainter>
#include <QPushButton>
#include <QString>
#include <QWidget>

#include "../../../../../UI/ui_SimpleCrop.h"
#include "../Tool/Imagecropperlabel.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
  class SimpleCrop;
}

class PS;
QT_END_NAMESPACE

class SimpleCropperDialog final : public QDialog {
  Q_OBJECT

public:
  /**
   * @brief 构造函数
   * @param imageIn 待处理图像
   * @param windowWidth 窗口宽度
   * @param windowHeight 窗口高度
   * @param shape 形状
   * @param cropperSize 裁剪器大小
   */
  SimpleCropperDialog(const QPixmap& imageIn,
                      const int windowWidth,
                      const int windowHeight,
                      const CropperShape shape,
                      const QSize cropperSize = QSize())
    : QDialog(nullptr), ui(new Ui::SimpleCrop)
  {
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(tr("图像裁剪器"));
    this->setMouseTracking(true);
    this->setModal(true);

    // 使用裁剪器设置图像标签
    ui->imgCropperLabel->setCropperLabel(windowWidth, windowHeight);
    ui->imgCropperLabel->setCropper(shape, cropperSize);
    ui->imgCropperLabel->setOutputShape(OutputShape::RECT);
    ui->imgCropperLabel->setOriginalImage(imageIn);
    ui->imgCropperLabel->enableOpacity(true);

    // 建立按钮连接
    connect(ui->btnSavePreview, &QPushButton::clicked, [this] {
      emit getOutputImage(ui->imgCropperLabel->getCroppedImage());
      this->accept();
    });
    connect(ui->btnQuit, &QPushButton::clicked, [this] {
      emit errorGetOutputImage("Failed to processed image.");
      this->reject();
    });
  }

signals:
  void getOutputImage(QPixmap pixmap);
  void errorGetOutputImage(QString errorText);

private:
  Ui::SimpleCrop* ui;
};
