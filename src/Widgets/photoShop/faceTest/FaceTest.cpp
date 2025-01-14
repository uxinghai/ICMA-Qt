#include "FaceTest.h"

#include <QCamera>
#include <QImageCapture>
#include <QMediaCaptureSession>

#include  "../../../../UI/ui_FaceTest.h"

extern QString Token;

FaceTest::FaceTest()
  : ui(new Ui::FaceTest)
{
  ui->setupUi(this);
  init();
  setupConnections();
}

void FaceTest::init()
{
  captureSession = new QMediaCaptureSession(this);
  camera = new QCamera;
  captureSession->setCamera(camera);

  imageCapture = new QImageCapture();
  captureSession->setImageCapture(imageCapture);

  camera->start();
  //on shutter button pressed
  imageCapture->capture();
}

void FaceTest::setupConnections()
{
  connect(imageCapture, &QImageCapture::imageCaptured,
          [this](const int id, const QImage& preview) {
            qDebug() << "捕获";
            Q_UNUSED(id);
            ui->lbCamera->setPixmap(QPixmap::fromImage(preview));
          });
}

FaceTest::~FaceTest() { delete ui; }
