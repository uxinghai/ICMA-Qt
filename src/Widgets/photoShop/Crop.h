/**
 * @file Crop.h
 *
 * @Breife ps中的裁剪模块
 *
 * @version 1.0
 * @date 2025/1/19
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <array>
#include <QPixmap>

namespace AutoCrop
{
  inline QPixmap autoCrop() { return {}; }
}

namespace Crop
{
  // 定义裁剪模式
  enum class CropMode {
    Ratio,    ///< 按比例裁剪
    FixedSize ///< 固定尺寸，有几个尺寸不是按比例
  };

  // 裁剪预设结构体
  struct CropPreset {
    CropMode mode;

    union {
      struct {
        int width_ratio;
        int height_ratio;
      } ratio;

      struct {
        int width;
        int height;
      } size;
    };

    const QString description;
  };

  // 预设配置数组
  inline std::array<CropPreset, 15> CROP_PRESETS{
    {
      {CropMode::Ratio, {.ratio = {0, 0}}, "自由裁剪"},           // 0
      {CropMode::Ratio, {.ratio = {1, 1}}, "1:1"},            // 1
      {CropMode::Ratio, {.ratio = {3, 4}}, "3:4"},            // 2
      {CropMode::Ratio, {.ratio = {2, 3}}, "2:3"},            // 3
      {CropMode::Ratio, {.ratio = {9, 16}}, "9:16"},          // 4
      {CropMode::Ratio, {.ratio = {4, 3}}, "4:3"},            // 5
      {CropMode::Ratio, {.ratio = {3, 2}}, "3:2"},            // 6
      {CropMode::Ratio, {.ratio = {16, 9}}, "16:9"},          // 7
      {CropMode::FixedSize, {.size = {295, 413}}, "一寸照片"},    // 8
      {CropMode::FixedSize, {.size = {390, 567}}, "大一寸照片"},   // 9
      {CropMode::FixedSize, {.size = {413, 579}}, "两寸照片"},    // 10
      {CropMode::FixedSize, {.size = {900, 383}}, "公众号首图"},   // 11
      {CropMode::FixedSize, {.size = {1080, 1440}}, "小红书配图"}, // 12
      {CropMode::FixedSize, {.size = {720, 1280}}, "竖版视频封面"}, // 13
      {CropMode::FixedSize, {.size = {1280, 720}}, "横版视频封面"}  // 14
    }
  };

  // 按比例计算新尺寸
  inline QSize calculateRatioSize(int width, int height, const int width_ratio,
                                  const int height_ratio)
  {
    if (width_ratio == 0 || height_ratio == 0) { return {width, height}; }
    const auto newWidth = qMin(width, height * width_ratio / height_ratio);
    const auto newHeight = newWidth * height_ratio / width_ratio;
    return {newWidth, newHeight};
  }

  inline QPixmap cropPixmapBy(QPixmap pixmap, const int row)
  {
    if (pixmap.isNull() || (row < 0 || row >= CROP_PRESETS.size())) {
      return pixmap;
    }

    if (row == 0) { return AutoCrop::autoCrop(); } ///< 自由裁剪

    const auto& preset = CROP_PRESETS[row];

    const auto width = pixmap.width();
    const auto height = pixmap.height();

    if (preset.mode == CropMode::Ratio) {
      const auto newSize = calculateRatioSize(
        width,
        height,
        preset.ratio.width_ratio,
        preset.ratio.height_ratio
      );
      return pixmap.scaled(newSize, Qt::IgnoreAspectRatio,
                           Qt::SmoothTransformation);
    }
    // CropMode::FixedSize 固定裁剪
    return pixmap.scaled(
      preset.size.width,
      preset.size.height,
      Qt::IgnoreAspectRatio,
      Qt::SmoothTransformation
    );
  }
} // namespace Crop
