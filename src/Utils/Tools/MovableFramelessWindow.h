/**
 * @file MovableFramelessWindow.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/7 15:19
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QMouseEvent>
#include <QWidget>

class MovableFramelessWindow final : public QWidget {
public:
  MovableFramelessWindow(QWidget* processWidget, const bool moveable)
    : processWidget(processWidget), moveable(moveable)
  {
    processWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    processWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    setMouseTracking(true);
    processWidget->setMouseTracking(true);
  }

protected:
  void mousePressEvent(QMouseEvent* event) override
  {
    if (!moveable) {
      event->ignore();
      return;
    }
    if (event->button() & Qt::LeftButton) { pos = event->pos(); }
    qDebug() << "按下：" << event->pos();
    QWidget::mousePressEvent(event);
  }

  void mouseMoveEvent(QMouseEvent* event) override
  {
    if (!moveable) {
      event->ignore();
      return;
    }
    const auto newPos = event->pos() - pos;
    processWidget->move(this->x() + newPos.x(), this->y() + newPos.y());
    qDebug() << "移动：" << newPos;
    QWidget::mouseMoveEvent(event);
  }

  void mouseReleaseEvent(QMouseEvent* event) override
  {
    if (!moveable) {
      event->ignore();
      return;
    }
    qDebug() << "释放";
    QWidget::mouseReleaseEvent(event);
  }

private:
  QPoint pos;
  QWidget* processWidget;
  bool moveable;
};
