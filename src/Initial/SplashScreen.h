/**
 * @file SplashScreen.h
 *
 * @brief
 * 该头文件用于应用程序正式启动前的加载动画
 * 给应用程序有足够的时间正确地配置相关内容
 *
 * @version 1.0
 * @date 2025/01/09
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */
#pragma once

#include <QProgressBar>
#include <QSplashScreen>
#include <QVBoxLayout>

class SplashScreen final : public QSplashScreen {
  Q_OBJECT

public:
  explicit SplashScreen(const QPixmap& pixmap = QPixmap())
    : QSplashScreen(pixmap)
  {
    this->setFixedSize(200, 70);
    progressBar = new QProgressBar(this);
    progressBar->setRange(0,10000000);
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setStyleSheet(
      "QProgressBar { "
      "    border: 2px solid grey; "
      "    border-radius: 5px; "
      "    text-align: center; "
      "} "
      "QProgressBar::chunk { "
      "    background: QLinearGradient(x1:0, y1:0, x2:1, y2:0, "
      "        stop:0 #05B8CC, stop:1 #A1EAFB); "
      "    border-radius: 5px; "
      "} "
    );

    const auto layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(progressBar);
    this->setLayout(layout);
  }

  ~SplashScreen() override = default;

  void setProgress(const int value) const { progressBar->setValue(value); }

private:
  QProgressBar* progressBar;
};
