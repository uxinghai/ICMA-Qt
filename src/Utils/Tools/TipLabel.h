/**
 * @file TipLabel.h
 *
 * @Breife 用于在鼠标位置提示信息
 *          控制器透明度
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
  explicit TipLabel(QWidget* parent,
                    QString tipText,
                    const int displayDuration = 3000,
                    const int fadeTime = 200)
    : QLabel(parent)
      , text(std::move(tipText))
      , displayDuration(displayDuration)
      , anim(new QPropertyAnimation(this, "windowOpacity", this))
  {
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setAlignment(Qt::AlignCenter);
    this->setMinimumHeight(30);

    anim->setDuration(fadeTime); ///< Duration 指的是动画从初始状态到终止状态的时长
    anim->setEasingCurve(QEasingCurve::InOutQuad);
  }

  void show(const QPoint& pos)
  {
    this->setText(text);
    this->move(pos);

    disconnect(anim, &QPropertyAnimation::finished,
               this, &TipLabel::hide);

    // 开始显示动画
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    QLabel::show();
    anim->start();

    // 设置定时隐藏
    QTimer::singleShot(displayDuration, [this] {
      anim->setStartValue(1.0);
      anim->setEndValue(0.0);
      anim->start();
      connect(anim, &QPropertyAnimation::finished,
              this, &TipLabel::hide);
    });
  }

  // 允许动态更新提示文本
  void updateTipText(const QString& newText) { text = newText; }

private:
  QString text;
  int displayDuration;
  QPropertyAnimation* anim;
};
