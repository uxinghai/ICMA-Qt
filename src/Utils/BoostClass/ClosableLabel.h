/**
 * @file ClosableLabel.h
 *
 * @Breife 可被关闭的 Label
 *
 * @version 1.0
 * @date 2025/5/10
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

class ClosableLabel final : public QLabel {
  Q_OBJECT

public:
  explicit ClosableLabel(QWidget* parent = nullptr, const QString& text = QString());
  ~ClosableLabel() override = default;

  // 设置是否显示关闭按钮
  void setCloseButtonVisible(bool visible);
  bool isCloseButtonVisible() const;

signals:
  // 点击关闭按钮时发出的信号
  void closeClicked();

protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void leaveEvent(QEvent* event) override;

private:
  QRect closeButtonRect() const;

  bool m_closeButtonVisible = true;
  bool m_hoverClose = false;
  int m_closeButtonSize = 16;
  int m_closeButtonPadding = 5;
};

inline ClosableLabel::ClosableLabel(QWidget* parent, const QString& text)
  : QLabel(text, parent)
{
  // 为了确保有足够的空间放置关闭按钮
  this->setContentsMargins(m_closeButtonSize + m_closeButtonPadding * 2, 0, 0, 0);
  this->setMouseTracking(true);
}

inline void ClosableLabel::setCloseButtonVisible(const bool visible)
{
  if (m_closeButtonVisible != visible) {
    m_closeButtonVisible = visible;
    update();
  }
}

inline bool ClosableLabel::isCloseButtonVisible() const { return m_closeButtonVisible; }

inline void ClosableLabel::paintEvent(QPaintEvent* event)
{
  // 先绘制标准QLabel内容
  QLabel::paintEvent(event);

  // 如果关闭按钮可见，绘制关闭按钮
  if (m_closeButtonVisible) {
    QPainter painter(this);

    // 设置抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);

    const QRect closeRect = closeButtonRect();

    // 如果鼠标悬停在关闭按钮上，绘制背景
    if (m_hoverClose) {
      painter.setPen(Qt::NoPen);
      painter.setBrush(QColor(200, 200, 200, 100));
      painter.drawEllipse(closeRect);
    }

    // 绘制叉号
    painter.setPen(QPen(QColor(120, 120, 120), 2));
    constexpr int margin = 4;
    painter.drawLine(
      closeRect.left() + margin,
      closeRect.top() + margin,
      closeRect.right() - margin,
      closeRect.bottom() - margin
    );
    painter.drawLine(
      closeRect.right() - margin,
      closeRect.top() + margin,
      closeRect.left() + margin,
      closeRect.bottom() - margin
    );
  }
}

inline void ClosableLabel::mousePressEvent(QMouseEvent* event)
{
  if (m_closeButtonVisible && closeButtonRect().contains(event->pos())) {
    emit closeClicked();
    event->accept();
    return;
  }

  QLabel::mousePressEvent(event);
}

inline void ClosableLabel::mouseMoveEvent(QMouseEvent* event)
{
  if (m_closeButtonVisible) {
    if (const bool hoverClose = closeButtonRect().contains(event->pos());
      hoverClose != m_hoverClose) {
      m_hoverClose = hoverClose;
      update();

      // 改变鼠标样式
      if (m_hoverClose) { setCursor(Qt::PointingHandCursor); }
      else { setCursor(Qt::ArrowCursor); }
    }
  }

  QLabel::mouseMoveEvent(event);
}

inline void ClosableLabel::leaveEvent(QEvent* event)
{
  if (m_hoverClose) {
    m_hoverClose = false;
    update();
    setCursor(Qt::ArrowCursor);
  }

  QLabel::leaveEvent(event);
}

inline QRect ClosableLabel::closeButtonRect() const
{
  // 关闭按钮放置在标签左侧
  return QRect(
    m_closeButtonPadding,
    (height() - m_closeButtonSize) / 2,
    m_closeButtonSize,
    m_closeButtonSize
  );
}
