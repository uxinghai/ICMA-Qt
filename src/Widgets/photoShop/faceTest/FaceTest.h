/**
 * @file FaceTest.h
 *
 * @brief 利用百度API进行人脸检测
 * @note token的获取在启动PS时拿到
 *
 *
 * @version 1.0
 * @date 2025/01/14
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QWidget>

class QMediaCaptureSession;
class QCamera;
class QImageCapture;
QT_BEGIN_NAMESPACE

namespace Ui
{
  class FaceTest;
}

QT_END_NAMESPACE

class FaceTest final : public QWidget {
  Q_OBJECT

public:
  FaceTest();
  ~FaceTest() override;

private:
  void init();
  void setupConnections();

  Ui::FaceTest* ui;

  QMediaCaptureSession* captureSession;
  QCamera* camera;
  QImageCapture* imageCapture;
};
