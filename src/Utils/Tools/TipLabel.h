/**
 * @file TipLabel.h
 *
 * @Breife 用于在鼠标位置提示信息
 *
 * @version 1.0
 * @date 2025/1/18
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>

class TipLabel final : public QLabel {
  Q_OBJECT

public:
  explicit TipLabel(QString tipText,
                    QWidget* parent = nullptr,
                    const int displayDuration = 3000,
                    const int fadeTime = 200)
    : QLabel(parent)
      , text(std::move(tipText))
      , displayDuration(displayDuration)
      , fadeAnimation(new QPropertyAnimation(this, "windowOpacity", this))
  {
    initializeLabel();
    setupAnimation(fadeTime);
  }

  void showTip(const QPoint& pos)
  {
    this->setText(text);
    this->move(pos);

    disconnect(fadeAnimation, &QPropertyAnimation::finished,
               this, &TipLabel::hide);

    // 开始显示动画
    fadeAnimation->setStartValue(0.0);
    fadeAnimation->setEndValue(1.0);
    this->show();
    fadeAnimation->start();

    // 设置定时隐藏
    QTimer::singleShot(displayDuration, [this] {
      fadeAnimation->setStartValue(1.0);
      fadeAnimation->setEndValue(0.0);
      fadeAnimation->start();
      connect(fadeAnimation, &QPropertyAnimation::finished,
              this, &TipLabel::hide);
    });
  }

  // 允许动态更新提示文本
  void updateTipText(const QString& newText) { text = newText; }

private:
  void initializeLabel()
  {
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setAlignment(Qt::AlignCenter);
    this->setMinimumHeight(30);
  }

  void setupAnimation(const int fadeTime) const
  {
    fadeAnimation->setDuration(fadeTime);
    fadeAnimation->setEasingCurve(QEasingCurve::InOutQuad);
  }

  QString text;
  int displayDuration;
  QPropertyAnimation* fadeAnimation;
};
