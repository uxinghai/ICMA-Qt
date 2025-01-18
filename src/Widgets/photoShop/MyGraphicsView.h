/**
 * @file MyGraphicsView.h
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

#include <qevent.h>
#include <QGraphicsView>

#include "../../Utils/Tools/TipLabel.h"
#include "ShareSrc.h"

class MyGraphicsView final : public QGraphicsView {
public:
  explicit MyGraphicsView(QWidget* parent = nullptr)
    : QGraphicsView(parent),
      scaleTip(new TipLabel(tr("配合Ctrl缩放"), this))
  {
    this->setRenderHint(QPainter::Antialiasing);
    this->setCacheMode(CacheBackground);
    this->setViewportUpdateMode(BoundingRectViewportUpdate);
    this->setAcceptDrops(true);
  }

protected:
  void wheelEvent(QWheelEvent* event) override
  {
    if (event->modifiers() & Qt::ControlModifier) {
      if (event->angleDelta().y() > 0) { this->scale(1.01, 1.01); }
      else { this->scale(0.99, 0.99); }
    }
    else {
      const QPoint nowPos = QCursor::pos();
      if (nowPos == lastPos) { return; }
      scaleTip->showTip(nowPos);
    }
  }

  void dragEnterEvent(QDragEnterEvent* event) override
  {
    if (const auto mimeData = event->mimeData();
      mimeData->hasUrls()) {
      const QString localFile = mimeData->urls().first().toLocalFile();
      if (const QFileInfo info(localFile);
        suffixList.contains(info.suffix())) { event->acceptProposedAction(); }
    }
    else { QGraphicsView::dragEnterEvent(event); }
  }

  void dropEvent(QDropEvent* event) override
  {
    QGraphicsView::dropEvent(event);
  }

  // 明天读一遍
  void resizeEvent(QResizeEvent* event) override
  {
    // 处理空或无效的情况
    if (!event || event->size().isEmpty()) {
      QGraphicsView::resizeEvent(event);
      return;
    }

    const QSizeF oldSize = event->oldSize();
    const QSizeF newSize = event->size();

    // 处理首次调整大小的情况
    if (oldSize.isEmpty()) {
      QGraphicsView::resizeEvent(event);
      if (this->scene()) {
        this->fitInView(this->scene()->sceneRect(), Qt::KeepAspectRatio);
      }
      return;
    }

    // 计算缩放因子
    qreal scaleX = newSize.width() / oldSize.width();
    qreal scaleY = newSize.height() / oldSize.height();

    // 避免过小或过大的缩放
    constexpr qreal minScale = 0.1;
    constexpr qreal maxScale = 10.0;
    scaleX = qBound(minScale, scaleX, maxScale);
    scaleY = qBound(minScale, scaleY, maxScale);

    // 保持当前视图的中心点
    const QPointF centerPoint = mapToScene(viewport()->rect().center());

    // 应用变换
    QTransform transform = this->transform();
    transform.scale(scaleX, scaleY);
    this->setTransform(transform);

    // 重新居中视图
    if (scene()) {
      centerOn(centerPoint);
      // 确保内容完全可见
      ensureVisible(scene()->sceneRect(), 0, 0);
    }

    QGraphicsView::resizeEvent(event);
  }

private:
  TipLabel* scaleTip;

  QPoint lastPos;
};
