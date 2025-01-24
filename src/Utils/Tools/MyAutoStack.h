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

  void push(const cv::Mat& mat, const MatInfo& info)
  {
    if (stk.size() >= maxHistorySize) { stk.removeFirst(); }
    stk.push(std::make_pair(mat, info));
  }

  void push(const QPair<cv::Mat, MatInfo>& pixmap)
  {
    if (stk.size() >= maxHistorySize) { stk.removeFirst(); }
    stk.push(pixmap);
  }

  std::pair<cv::Mat, MatInfo>& top()
  {
    if (stk.empty()) { throw std::runtime_error("Stack is empty"); }
    return stk.top();
  }

  [[nodiscard]] const std::pair<cv::Mat, MatInfo>& top() const
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
  int maxHistorySize = 50;
  QStack<QPair<cv::Mat, MatInfo>> stk;
};
