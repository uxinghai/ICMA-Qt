/**
 * @file NoWheelSlider.h
 *
 * @Breife 自定义滑动条禁止滚轮滑动
 *
 * @version 1.0
 * @date 2025/1/23
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QSlider>
#include <QWheelEvent>

class NoWheelSlider final : public QSlider {
  Q_OBJECT

public:
  explicit NoWheelSlider(QWidget* parent = nullptr)
    : QSlider(parent) { this->setFocusPolicy(Qt::NoFocus); }

protected:
  void wheelEvent(QWheelEvent* event) override { event->ignore(); }
};
