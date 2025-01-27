/**
 * @file imagecropperdemo.h
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

#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSlider>

#include "./base/Imagecropperlabel.h"

class ImageCropperDemo : public QDialog {
  Q_OBJECT

public:
  ImageCropperDemo(QWidget* parent = nullptr);

  void setupLayout();

  void init();

public slots:
  void onOutputShapeChanged(int idx);
  void onCropperShapeChanged(int idx);
  void onEnableOpacityChanged(int state);
  void onShowDragSquareChanged(int state);
  void onDragSquareEdgeChanged(QString edge);
  void onOpacityChanged(int val);
  void onFixedWidthChanged(QString width);
  void onFixedHeightChanged(QString height);
  void onMinWidthChanged(QString width);
  void onMinHeightChanged(QString height);
  void onShowRectBorder(int state);
  void onChooseRectBorderColor();
  void onChooseDragSquareColor();

  void onChooseOriginalImage();
  void onUpdatePreview();
  void onSaveCroppedImage();

private:
  void setLabelColor(QLabel* label, QColor color)
  {
    QPixmap pixmap(QSize(80, 25));
    pixmap.fill(color);
    label->setPixmap(pixmap);
  }

private:
  ImageCropperLabel* imgCropperLabel;
  QHBoxLayout* mainLayout;

  QLabel* labelPreviewImage;

  QComboBox* comboOutputShape;
  QComboBox* comboCropperShape;

  QLineEdit* editOriginalImagePath;
  QPushButton* btnChooseOriginalImagePath;

  QLineEdit* editCropperFixedWidth;
  QLineEdit* editCropperFixedHeight;
  QLineEdit* editCropperMinWidth;
  QLineEdit* editCropperMinHeight;

  QCheckBox* checkShowDragSquare;
  QCheckBox* checkEnableOpacity;
  QSlider* sliderOpacity;
  QLineEdit* editDragSquareEdge;

  QCheckBox* checkShowRectBorder;
  QLabel* labelRectBorderColor;
  QPushButton* btnChooseRectBorderCorlor;

  QLabel* labelDragSquareColor;
  QPushButton* btnChooseDragSquareColor;

  QPushButton* btnSavePreview;
  QPushButton* btnQuit;
};
