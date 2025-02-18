#include "Cropper.h"

#include <QFileDialog>
#include <QMessageBox>

#include "./CropperDialog/CustomCropperDialog.h"
#include "./CropperDialog/SimpleCropperDialog.h"

Cropper::Cropper(QString filePath, QWidget* parent)
  : QMainWindow(parent),
    filePath(std::move(filePath)) { setupLayout(); }

void Cropper::doCustomCrop()
{
  this->hide();
  auto* customCropDialog = new CustomCropperDialog(filePath, this);
  connect(customCropDialog, &CustomCropperDialog::getOutputImage,
          [this, customCropDialog](const QPixmap& pixmap) {
            emit ProcessedPixmap(pixmap);
            this->deleteLater();
            customCropDialog->deleteLater();
          });
  connect(customCropDialog, &CustomCropperDialog::errorGetOutputImage,
          [this, customCropDialog](const QString& text) {
            emit ProcessedError(text);
            this->deleteLater();
            customCropDialog->deleteLater();
          });
  customCropDialog->show();
}

void Cropper::doSimpleCrop()
{
  this->hide();
  QPixmap inputImage;
  if (!inputImage.load(filePath)) {
    QMessageBox::critical(nullptr, tr("错误"),
                          tr("图像加载失败!"), QMessageBox::Ok);
    return;
  }

  auto* simpleCropDialog = new SimpleCropperDialog(inputImage, 600, 400,
                                                   CropperShape::CIRCLE,
                                                   QSize());
  connect(simpleCropDialog, &SimpleCropperDialog::getOutputImage,
          [this, simpleCropDialog](const QPixmap& pixmap) {
            emit ProcessedPixmap(pixmap);
            this->deleteLater();
            simpleCropDialog->deleteLater();
          });
  connect(simpleCropDialog, &SimpleCropperDialog::errorGetOutputImage,
          [this, simpleCropDialog](const QString& text) {
            emit ProcessedError(text);
            this->deleteLater();
            simpleCropDialog->deleteLater();
          });
  simpleCropDialog->exec();
}

void Cropper::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
  QMainWindow::closeEvent(event);
}

void Cropper::doGetProcessedPixmap(const QPixmap& pixmap)
{
  emit ProcessedPixmap(pixmap);
}

void Cropper::setupLayout()
{
  auto* centralWidget = new QWidget(this);

  btnCustomCrop = new QPushButton(tr("使用高级裁剪"), centralWidget);
  btnSimpleCrop = new QPushButton(tr("使用简单裁剪"), centralWidget);

  auto* mainLayout = new QVBoxLayout(centralWidget);
  mainLayout->addWidget(btnCustomCrop);
  mainLayout->addWidget(btnSimpleCrop);
  this->setCentralWidget(centralWidget);

  connect(btnCustomCrop, &QPushButton::clicked, this, &Cropper::doCustomCrop);
  connect(btnSimpleCrop, &QPushButton::clicked, this, &Cropper::doSimpleCrop);
}

Cropper::~Cropper() { cropInstance = nullptr; }
