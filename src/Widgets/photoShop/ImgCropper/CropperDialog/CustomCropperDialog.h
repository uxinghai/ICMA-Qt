/**
 * @file CustomCropperDialog.h
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

#include <QComboBox>
#include <QDialog>
#include <QLineEdit>

#include "../Tool/ImageCropperLabel.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
  class CustomCrop;
}

QT_END_NAMESPACE

class CustomCropperDialog final : public QDialog {
  Q_OBJECT

public:
  explicit CustomCropperDialog(const QString& imgFilePath,
                               QWidget* parent = nullptr);

  ~CustomCropperDialog() override;

signals:
  void getOutputImage(QPixmap pixmap);
  void errorGetOutputImage(QString text);

public slots:
  void doOutputShapeChanged(int idx) const;
  void doCropperShapeChanged(int idx) const;
  void doEnableOpacityChanged(int state) const;
  void doShowDragSquareChanged(int state) const;
  void doDragSquareEdgeChanged(const QString& edge) const;
  void doOpacityChanged(int val) const;
  void doFixedWidthChanged(const QString& width) const;
  void doFixedHeightChanged(const QString& height) const;
  void doMinWidthChanged(const QString& width) const;
  void doMinHeightChanged(const QString& height) const;
  void doShowRectBorder(int state) const;
  void doChooseRectBorderColor();
  void doChooseDragSquareColor();
  void doUpdatePreview() const;
  void doSaveCroppedImage();

private:
  void setupConnections();
  void openOriginalImg(const QString& imgFilePath);
  static void setLabelColor(QLabel* label, QColor color);

  Ui::CustomCrop* ui;
};
