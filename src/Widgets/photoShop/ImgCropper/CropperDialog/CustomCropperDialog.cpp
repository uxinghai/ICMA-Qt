#include "CustomCropperDialog.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "../../../../../UI/ui_CustomCrop.h"

CustomCropperDialog::CustomCropperDialog(const QString& imgFilePath,
                                         QWidget* parent)
  : QDialog(parent), ui(new Ui::CustomCrop)
{
  ui->setupUi(this);
  ui->imgCropperLabel->setRectCropper();
  setupConnections();
  ui->imgCropperLabel->update(); ///< 立即更新
  this->setModal(true);

  openOriginalImg(imgFilePath); ///< 打开传输进入的原图
  this->setAttribute(Qt::WA_DeleteOnClose);
}

void CustomCropperDialog::setupConnections()
{
  connect(ui->imgCropperLabel, &ImageCropperLabel::croppedImageChanged,
          this, &CustomCropperDialog::doUpdatePreview);

  // 输出形状改变
  connect(ui->comboOutputShape, &QComboBox::currentIndexChanged,
          this, &CustomCropperDialog::doOutputShapeChanged);

  // 裁剪形状改变
  connect(ui->comboCropperShape, &QComboBox::currentIndexChanged,
          this, &CustomCropperDialog::doCropperShapeChanged);

  connect(ui->editCropperFixedWidth, &QLineEdit::textChanged,
          this, &CustomCropperDialog::doFixedWidthChanged);
  connect(ui->editCropperFixedHeight, &QLineEdit::textChanged,
          this, &CustomCropperDialog::doFixedHeightChanged);
  // connect(ui->editCropperMinWidth, &QLineEdit::textChanged,
  //         this, &CustomCropperDialog::doMinWidthChanged);
  // connect(ui->editCropperMinHeight, &QLineEdit::textChanged,
  //         this, &CustomCropperDialog::doMinHeightChanged);

  connect(ui->checkEnableOpacity, &QCheckBox::stateChanged,
          this, &CustomCropperDialog::doEnableOpacityChanged);

  connect(ui->checkShowDragSquare, &QCheckBox::stateChanged,
          this, &CustomCropperDialog::doShowDragSquareChanged);
  connect(ui->editDragSquareEdge, &QLineEdit::textChanged,
          this, &CustomCropperDialog::doDragSquareEdgeChanged);

  connect(ui->sliderOpacity, &QSlider::valueChanged,
          this, &CustomCropperDialog::doOpacityChanged);

  connect(ui->checkShowRectBorder, &QCheckBox::stateChanged,
          this, &CustomCropperDialog::doShowRectBorder);

  setLabelColor(ui->labelRectBorderColor, Qt::white);

  connect(ui->btnChooseRectBorderColor, &QPushButton::clicked,
          this, &CustomCropperDialog::doChooseRectBorderColor);

  setLabelColor(ui->labelDragSquareColor, Qt::white);

  connect(ui->btnChooseDragSquareColor, &QPushButton::clicked,
          this, &CustomCropperDialog::doChooseDragSquareColor);

  connect(ui->btnSavePreview, &QPushButton::clicked,
          this, &CustomCropperDialog::doSaveCroppedImage);
  connect(ui->btnQuit, &QPushButton::clicked,
          this, &CustomCropperDialog::close);
}

void CustomCropperDialog::setLabelColor(QLabel* label, const QColor color)
{
  // 设置一个彩色图像
  QPixmap pixmap(QSize(80, 25));
  pixmap.fill(color);
  label->setPixmap(pixmap);
}

void CustomCropperDialog::doOutputShapeChanged(const int idx) const
{
  if (idx == 0) { ui->imgCropperLabel->setOutputShape(OutputShape::RECT); }
  else { ui->imgCropperLabel->setOutputShape(OutputShape::ELLIPSE); }
  doUpdatePreview();
}

void CustomCropperDialog::doCropperShapeChanged(const int idx) const
{
  switch (static_cast<CropperShape>(idx + 1)) {
  case CropperShape::RECT: ///< 矩形
    {
      ui->imgCropperLabel->setRectCropper();
      ui->editCropperFixedWidth->setEnabled(false);
      ui->editCropperFixedHeight->setEnabled(false);
      ui->editCropperMinWidth->setEnabled(true);
      ui->editCropperMinHeight->setEnabled(true);
      ui->checkShowDragSquare->setEnabled(true);
      ui->editDragSquareEdge->setEnabled(true);
      ui->btnChooseDragSquareColor->setEnabled(true);
      break;
    }
  case CropperShape::SQUARE:
    {
      ui->imgCropperLabel->setSquareCropper();
      ui->editCropperFixedWidth->setEnabled(false);
      ui->editCropperFixedHeight->setEnabled(false);
      ui->editCropperMinWidth->setEnabled(true);
      ui->editCropperMinHeight->setEnabled(true);
      ui->checkShowDragSquare->setEnabled(true);
      ui->editDragSquareEdge->setEnabled(true);
      ui->btnChooseDragSquareColor->setEnabled(true);
      break;
    }
  case CropperShape::FIXED_RECT:
    {
      ui->imgCropperLabel->setFixedRectCropper(QSize(64, 64));
      ui->editCropperFixedWidth->setEnabled(true);
      ui->editCropperFixedHeight->setEnabled(true);
      ui->editCropperMinWidth->setEnabled(false);
      ui->editCropperMinHeight->setEnabled(false);
      ui->editCropperFixedWidth->setText("64");
      ui->editCropperFixedHeight->setText("64");
      ui->checkShowDragSquare->setEnabled(false);
      ui->editDragSquareEdge->setEnabled(false);
      ui->btnChooseDragSquareColor->setEnabled(false);
      break;
    }
  case CropperShape::ELLIPSE:
    {
      ui->imgCropperLabel->setEllipseCropper();
      ui->editCropperFixedWidth->setEnabled(false);
      ui->editCropperFixedHeight->setEnabled(false);
      ui->editCropperMinWidth->setEnabled(true);
      ui->editCropperMinHeight->setEnabled(true);
      ui->checkShowDragSquare->setEnabled(true);
      ui->editDragSquareEdge->setEnabled(true);
      ui->btnChooseDragSquareColor->setEnabled(true);
      break;
    }
  case CropperShape::CIRCLE:
    {
      ui->imgCropperLabel->setCircleCropper();
      ui->editCropperFixedWidth->setEnabled(false);
      ui->editCropperFixedHeight->setEnabled(false);
      ui->editCropperMinWidth->setEnabled(true);
      ui->editCropperMinHeight->setEnabled(true);
      ui->checkShowDragSquare->setEnabled(true);
      ui->editDragSquareEdge->setEnabled(true);
      ui->btnChooseDragSquareColor->setEnabled(true);
      break;
    }
  case CropperShape::FIXED_ELLIPSE: ui->imgCropperLabel->setFixedEllipseCropper(
      QSize(64, 64));
    ui->editCropperFixedWidth->setEnabled(true);
    ui->editCropperFixedHeight->setEnabled(true);
    ui->editCropperMinWidth->setEnabled(false);
    ui->editCropperMinHeight->setEnabled(false);
    ui->editCropperFixedWidth->setText("64");
    ui->editCropperFixedHeight->setText("64");
    ui->checkShowDragSquare->setEnabled(false);
    ui->editDragSquareEdge->setEnabled(false);
    ui->btnChooseDragSquareColor->setEnabled(false);
    break;
  case CropperShape::UNDEFINED: break;
  }

  ui->imgCropperLabel->update();
  doUpdatePreview();
}

void CustomCropperDialog::doEnableOpacityChanged(const int state) const
{
  if (state == Qt::Checked) {
    ui->sliderOpacity->setEnabled(true);
    ui->imgCropperLabel->enableOpacity(true);
  }
  else {
    ui->sliderOpacity->setEnabled(false);
    ui->imgCropperLabel->enableOpacity(false);
  }
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doShowDragSquareChanged(const int state) const
{
  if (state == Qt::Checked) {
    ui->editDragSquareEdge->setEnabled(true);
    ui->btnChooseDragSquareColor->setEnabled(true);
    ui->imgCropperLabel->setShowDragSquare(true);
  }
  else {
    ui->editDragSquareEdge->setEnabled(false);
    ui->btnChooseDragSquareColor->setEnabled(false);
    ui->imgCropperLabel->setShowDragSquare(false);
  }
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doDragSquareEdgeChanged(const QString& edge) const
{
  ui->imgCropperLabel->setDragSquareEdge(edge.toInt());
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doOpacityChanged(const int val) const
{
  ui->imgCropperLabel->setOpacity(val / 100.0);
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doFixedWidthChanged(const QString& width) const
{
  ui->imgCropperLabel->setCropperFixedWidth(width.toInt());
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doFixedHeightChanged(const QString& height) const
{
  ui->imgCropperLabel->setCropperFixedHeight(height.toInt());
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doMinWidthChanged(const QString& width) const
{
  ui->imgCropperLabel->setCropperMinimumWidth(width.toInt());
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doMinHeightChanged(const QString& height) const
{
  ui->imgCropperLabel->setMinimumHeight(height.toInt());
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doShowRectBorder(const int state) const
{
  if (state == Qt::Checked) {
    ui->btnChooseRectBorderColor->setEnabled(true);
    ui->imgCropperLabel->setShowRectBorder(true);
  }
  else {
    ui->btnChooseRectBorderColor->setEnabled(false);
    ui->imgCropperLabel->setShowRectBorder(false);
  }
  ui->imgCropperLabel->update();
}

void CustomCropperDialog::doChooseRectBorderColor()
{
  const QColor color = QColorDialog::getColor(
    ui->imgCropperLabel->getBorderPen().color(),
    this);
  if (color.isValid()) {
    setLabelColor(ui->labelRectBorderColor, color);
    QPen pen = ui->imgCropperLabel->getBorderPen();
    pen.setColor(color);
    ui->imgCropperLabel->setBorderPen(pen);
    ui->imgCropperLabel->update();
  }
}

void CustomCropperDialog::doChooseDragSquareColor()
{
  if (const QColor color = QColorDialog::getColor(Qt::white, this);
    color.isValid()) {
    setLabelColor(ui->labelDragSquareColor, color);
    ui->imgCropperLabel->setDragSquareColor(color);
    ui->imgCropperLabel->update();
  }
}

void CustomCropperDialog::doUpdatePreview() const
{
  QPixmap preview = ui->imgCropperLabel->getCroppedImage();
  preview = preview.scaled(ui->labelPreviewImage->width(),
                           ui->labelPreviewImage->height(),
                           Qt::KeepAspectRatio, Qt::SmoothTransformation);
  ui->labelPreviewImage->setPixmap(preview);
}

void CustomCropperDialog::openOriginalImg(const QString& imgFilePath)
{
  QPixmap pixmap;
  if (!pixmap.load(imgFilePath)) {
    QMessageBox::critical(this, tr("错误"), tr("加载图像失败"),
                          QMessageBox::Ok);
    return;
  }

  ui->imgCropperLabel->setOriginalImage(pixmap);
  ui->imgCropperLabel->update();
  doUpdatePreview();
  ui->labelPreviewImage->setFrameStyle(0);
}

void CustomCropperDialog::doSaveCroppedImage()
{
  if (const QPixmap pixmap = ui->labelPreviewImage->pixmap();
    !pixmap) {
    emit errorGetOutputImage("no image");
    return;
  }

  emit getOutputImage(ui->imgCropperLabel->getCroppedImage());
}

CustomCropperDialog::~CustomCropperDialog() { delete ui; }
