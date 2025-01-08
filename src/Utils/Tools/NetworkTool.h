/**
 * @file NetworkTool.h
 *
 * @Breife 网络工具类
 *
 * @version 1.0
 * @date 2025/1/8 21:36
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QEventLoop>
#include <QNetworkReply>
#include <QObject>

class NetworkTool final {
public:
  static void waitForFinished(const QNetworkReply* reply)
  {
    // 阻塞网络请求直到完成
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); ///< 阻塞，直到事件循环退出
  }
};
