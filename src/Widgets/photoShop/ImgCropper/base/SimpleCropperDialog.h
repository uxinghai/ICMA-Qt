/**
 * @file SimpleCropperDialog.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/26
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>

#include "Imagecropperlabel.h"

class SimpleCropperDialog final : public QDialog {
  Q_OBJECT

public:
  static QPixmap getCroppedImage(const QString& filename,
                                 const int windowWidth,
                                 const int windowHeight,
                                 const CropperShape cropperShape,
                                 const QSize cropperSize = QSize())
  {
    QPixmap inputImage;
    if (!inputImage.load(filename)) {
      QMessageBox::critical(nullptr, tr("错误"),
                            tr("图像加载失败!"), QMessageBox::Ok);
      return {};
    }

    // 构建简单裁剪对话框对象
    SimpleCropperDialog dialog(inputImage, windowWidth, windowHeight,
                               cropperShape, cropperSize);
    dialog.exec();
    return dialog.getOutputImage();
  }

private:
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
    : QDialog(nullptr), isResult(false)
  {
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle(tr("图像裁剪器"));
    this->setMouseTracking(true);
    this->setModal(true);

    // 使用裁剪器设置图像标签
    imageLabel = new ImageCropperLabel(windowWidth, windowHeight, this);
    imageLabel->setCropper(shape, cropperSize);
    imageLabel->setOutputShape(OutputShape::RECT);
    imageLabel->setOriginalImage(imageIn);
    imageLabel->enableOpacity(true);

    // 设置按钮
    auto* btnLayout = new QHBoxLayout();
    auto* btnOk = new QPushButton(tr("确认"), this);
    auto* btnCancel = new QPushButton(tr("取消"), this);
    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);

    // 设置主布局
    auto* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(imageLabel);
    mainLayout->addLayout(btnLayout);

    // 建立按钮连接
    connect(btnOk, &QPushButton::clicked, [this] {
      isResult = true;
      QDialog::accept();
    });
    connect(btnCancel, &QPushButton::clicked, [this] {
      isResult = false;
      QDialog::reject();
    });
  }

  QPixmap getOutputImage() const
  {
    return isResult ? imageLabel->getCroppedImage() : QPixmap();
  }

  ImageCropperLabel* imageLabel;
  bool isResult; ///< 是否为结果，用于标记用户是否裁剪完成或者取消裁剪
};
