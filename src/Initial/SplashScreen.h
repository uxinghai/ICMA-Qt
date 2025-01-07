/**
 * @file SplashScreen.h
 *
 * @brief 应用启动动画的头文件
 *
 * 该头文件用于应用程序正式启动前的加载动画
 * 给应用程序有足够的时间正确地配置相关内容
 *
 * @author uxinghai
 * @date 2024.8.2
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
    progressBar = new QProgressBar(this);
    progressBar->setAlignment(Qt::AlignCenter);
    progressBar->setStyleSheet(
      "QProgressBar { border: 2px solid grey; border-radius: 5px; text-align: center; } "
      "QProgressBar::chunk { background-color: #05B8CC; width: 20px; }");

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
