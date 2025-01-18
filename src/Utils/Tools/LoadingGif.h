/**
 * @file LoadingGif.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/18
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QLabel>
#include <QMovie>
#include <QWidget>

class LoadingGif final : public QWidget {
public:
  explicit LoadingGif(QWidget* showWidget)
    : label(new QLabel(nullptr)),
      movie(new QMovie(":/icons/res/icons/Loading/dogLoading.gif", QByteArray(),
                       this))
  {
    const QSize size = showWidget->size();
    label->setFixedSize(size);
    label->move(0, 0); ///< 确保从左上角开始覆盖
    label->raise();    ///< 确保 label 在最前面显示
    label->setStyleSheet("background:transparent;");
    label->setAttribute(Qt::WA_TranslucentBackground);
    label->setMovie(movie);
    movie->start();
  }

  ~LoadingGif() override { label->deleteLater(); }

private:
  QLabel* label;
  QMovie* movie;
};
