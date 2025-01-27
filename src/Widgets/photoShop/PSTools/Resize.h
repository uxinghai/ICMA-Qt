/**
 * @file Resize.h
 *
 * @Breife PS中的修改尺寸大小模块
 *
 * @version 1.0
 * @date 2025/1/21
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <array>
#include <QPixmap>

namespace AutoResize
{
  inline QPixmap autoResize(QPixmap pixmap, const int width,
                            const int height, const bool lockAspectRatio)
  {
    if (pixmap.isNull()) { return pixmap; }
    if (width == 0 && height == 0) { return pixmap; }
    auto mode = Qt::KeepAspectRatio;
    if (!lockAspectRatio) { mode = Qt::IgnoreAspectRatio; }
    return pixmap.scaled(width, height, mode, Qt::SmoothTransformation);
  }
}

namespace DoResize
{
  // 定义预设尺寸结构体
  struct Size {
    int width;
    int height;
    const char* description;
  };

  // 预设尺寸数组
  constexpr std::array<Size, 15> PRESET_SIZES{
    {
      {0, 0, "Original"},
      {1000, 1000, "1000x1000"},
      {800, 1200, "800x1200"},
      {800, 800, "800x800"},
      {500, 500, "500x500"},
      {500, 500, "500x500"},
      {480, 480, "480x480"},
      {600, 800, "600x800"},
      {600, 600, "600x600"},
      {295, 413, "295x413"},
      {390, 567, "390x567"},
      {413, 579, "413x579"},
      {150, 150, "150x150"},
      {200, 200, "200x200"},
      {300, 300, "300x300"}
    }
  };

  /**
   *
   * @param pixmap
   * @param row
   * @param lockAspectRatio
   * @param pixWidth 自定义尺寸时由用户填入
   * @param pixHeight 自定义尺寸时由用户填入
   * @return
   */
  inline QPixmap resizePixmapBy(QPixmap pixmap, const int row,
                                const bool lockAspectRatio,
                                const int pixWidth = 0,
                                const int pixHeight = 0)
  {
    if (pixmap.isNull() || (row < 0 || row >= PRESET_SIZES.size())) {
      return pixmap;
    }

    // 如果row为0调用自定义
    if (row == 0) {
      return AutoResize::autoResize(pixmap, pixWidth, pixHeight,
                                    lockAspectRatio);
    }

    // 如果尺寸为0，直接返回
    const auto& [width, height, description] = PRESET_SIZES[row];
    if ((width == 0 && height == 0)) { return pixmap; }

    const auto mode = lockAspectRatio
                        ? Qt::KeepAspectRatio
                        : Qt::IgnoreAspectRatio;
    return pixmap.scaled(width, height, mode,
                         Qt::SmoothTransformation);
  }
} // namespace Resize
