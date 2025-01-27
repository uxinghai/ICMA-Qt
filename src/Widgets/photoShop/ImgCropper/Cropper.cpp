#include "Cropper.h"

#include <QFileDialog>

#include "./base/SimpleCropperDialog.h"
#include "imagecropperdemo.h"

Cropper::Cropper(QString filePath, QWidget* parent)
  : QMainWindow(parent),
    filePath(std::move(filePath)) { setupLayout(); }

void Cropper::doCustomCrop()
{
  // 创建高级裁剪的对象
  auto* imageCropperDemo = new ImageCropperDemo(this);
  imageCropperDemo->show();
  this->hide();
}

void Cropper::doSimpleCrop()
{
  const QPixmap image = SimpleCropperDialog::getCroppedImage(filePath,
    600, 400, CropperShape::CIRCLE);
  if (image.isNull()) { return; }

  auto* dialog = new QDialog(nullptr);
  dialog->setAttribute(Qt::WA_DeleteOnClose);
  auto* label = new QLabel(dialog);
  label->setFixedSize(image.size());
  label->setPixmap(image);
  dialog->exec();
  this->hide();
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

Cropper::~Cropper() = default;
