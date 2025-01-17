/**
 * @file ImageToBase64.h
 *
 * @Breife 非线程版本
 *
 * @version 1.0
 * @date 2025/1/16
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#pragma once

#include <QBuffer>
#include <QImage>

class ImageToBase64 final {
public:
  static QString toBase64(const QImage& img)
  {
    QByteArray byteArray;
    QBuffer buf(&byteArray);
    img.save(&buf, "png");
    buf.close();
    return byteArray.toBase64();
  }
};
