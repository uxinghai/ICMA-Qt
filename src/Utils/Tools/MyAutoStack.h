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

#include <QStack>

template <class T>
class MyAutoStack {
public:
  MyAutoStack() = default;

  explicit MyAutoStack(const int size) : maxHistorySize(size) {}

  MyAutoStack(MyAutoStack&&) noexcept = default;
  MyAutoStack& operator=(MyAutoStack&&) noexcept = default;

  MyAutoStack(const MyAutoStack&) = default;
  MyAutoStack& operator=(const MyAutoStack&) = default;

  void pushBack(const T& var)
  {
    if (stk.size() >= maxHistorySize) { stk.removeFirst(); }
    stk.push(var);
  }

  void pushBack(T&& var)
  {
    if (stk.size() >= maxHistorySize) { stk.removeFirst(); }
    stk.push(std::move(var));
  }

  void pushFront(const T& var)
  {
    if (stk.size() >= maxHistorySize) { stk.removeLast(); }
    stk.push_front(var);
  }

  void pushFront(T&& var)
  {
    if (stk.size() >= maxHistorySize) { stk.removeLast(); }
    stk.push_front(std::move(var));
  }

  [[nodiscard]] int maxSize() const noexcept { return maxHistorySize; }

  void setMaxSize(const int value)
  {
    if (value > 0) {
      maxHistorySize = value;

      while (stk.size() > maxHistorySize) { stk.pop(); }
    }
  }

  [[nodiscard]] bool empty() const noexcept { return stk.empty(); }

  [[nodiscard]] const T& top() const
  {
    if (stk.empty()) {
      throw std::runtime_error("Attempt to access top of an empty stack.");
    }
    return stk.top();
  }

  T& top()
  {
    if (stk.empty()) {
      throw std::runtime_error("Attempt to access top of an empty stack.");
    }
    return stk.top();
  }

  [[nodiscard]] int size() const noexcept { return stk.size(); }

  void push(const T& value) { stk.push(value); }

  void pop()
  {
    if (stk.empty()) {
      throw std::runtime_error("Attempt to pop from an empty stack.");
    }
    stk.pop();
  }

  T front()
  {
    if (stk.empty()) {
      throw std::runtime_error("Attempt to access front of an empty stack.");
    }
    return stk.front();
  }

  void clear() { stk.clear(); }

  // 特殊功能，在系统保存图像后只保留最新栈顶图像
  void afterSavePixmap()
  {
    const auto pixmap = stk.top();
    stk.clear();
    stk.push_back(pixmap);
  }
private:
  int maxHistorySize = 50;
  QStack<T> stk;
};
