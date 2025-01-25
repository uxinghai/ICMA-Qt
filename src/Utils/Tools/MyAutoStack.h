/**
 * @file MyAutoStack.h
 *
 * @Breife 自定义栈用于保留系统历史记录，可用设置最大记录数量
 *
 * @version 1.0
 * @date 2025/1/19
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <opencv2/opencv.hpp>
#include <QStack>

#include "../../Widgets/photoShop/ShareSrc.h"

class MyAutoStack {
public:
  MyAutoStack() = default;
  explicit MyAutoStack(const int size) : maxHistorySize(size) {}

  void push(const QPair<cv::Mat, MatInfo>& pixmap)
  {
    // 栈满则弹出最近一个然后再放入
    if (stk.size() >= maxHistorySize) { stk.pop(); }
    stk.push(pixmap);
  }

  QPair<cv::Mat, MatInfo>& top()
  {
    if (stk.empty()) { throw std::runtime_error("Stack is empty"); }
    return stk.top();
  }

  QPair<cv::Mat, MatInfo>& bottom()
  {
    if (stk.empty()) { throw std::runtime_error("Stack is empty"); }
    return stk.front();
  }

  [[nodiscard]] const QPair<cv::Mat, MatInfo>& top() const
  {
    if (stk.empty()) { throw std::runtime_error("Stack is empty"); }
    return stk.top();
  }

  void pop() { if (!stk.empty()) { stk.pop(); } }

  [[nodiscard]] bool empty() const { return stk.empty(); }
  [[nodiscard]] size_t size() const { return stk.size(); }

  void afterSavePixmap()
  {
    if (!stk.empty()) {
      const auto top = stk.top();
      stk.pop();
      stk.push(top);
    }
  }

  void clear() { stk.clear(); }

private:
  int maxHistorySize = 100;
  QStack<QPair<cv::Mat, MatInfo>> stk;
};
