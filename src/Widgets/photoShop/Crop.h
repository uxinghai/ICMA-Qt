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

// 维护一个临时栈
// 保留修改用于撤销显示，在主界面应用修改后清空
inline MyAutoStack<QPixmap> tempStk;

namespace Crop
{
  // pixmap 是上一次保存的图l
  inline QPixmap cropPixmapBy(QPixmap pixmap, const int row)
  {
    if (pixmap.isNull()) { return {}; }

    // 获取原始宽高
    const auto width = pixmap.width();
    const auto height = pixmap.height();

    switch (row) {
    case 0: ///< 自由裁剪
      break;
    case 1: ///< 1:1
      {
        const auto factor = qMin(width, height);
        pixmap = pixmap.scaled(factor, factor);
      }
      break;
    case 2: ///< 3:4
      {
        const auto newWidth = qMin(width, height * 3 / 4);
        const auto newHeight = newWidth * 4 / 3;
        pixmap = pixmap.scaled(newWidth, newHeight);
      }
      break;
    case 3: ///< 2:3
      {
        const auto newWidth = qMin(width, height * 2 / 3);
        const auto newHeight = newWidth * 3 / 2;
        pixmap = pixmap.scaled(newWidth, newHeight);
      }
      break;
    case 4: ///< 9:16
      {
        const auto newWidth = qMin(width, height * 9 / 16);
        const auto newHeight = newWidth * 16 / 9;
        pixmap = pixmap.scaled(newWidth, newHeight);
      }
      break;
    case 5: ///< 4:3
      {
        const auto newWidth = qMin(width, height * 4 / 3);
        const auto newHeight = newWidth * 3 / 4;
        pixmap = pixmap.scaled(newWidth, newHeight);
      }
      break;
    case 6: ///< 3:2
      {
        const auto newWidth = qMin(width, height * 3 / 2);
        const auto newHeight = newWidth * 2 / 3;
        pixmap = pixmap.scaled(newWidth, newHeight);
      }
      break;
    case 7: ///< 16:9
      {
        const auto newWidth = qMin(width, height * 16 / 9);
        const auto newHeight = newWidth * 9 / 16;
        pixmap = pixmap.scaled(newWidth, newHeight);
      }
      break;
    case 8: ///< 一寸25mm x 35mm at 300dpi
      pixmap = pixmap.scaled(295, 413);
      break;
    case 9: ///< 大一寸33mm x 48mm at 300dpi
      pixmap = pixmap.scaled(390, 567);
      break;
    case 10: ///< 两寸35mm x 49mm at 300dpi
      pixmap = pixmap.scaled(413, 579);
      break;
    case 11: ///< 公众号首图
      pixmap = pixmap.scaled(900, 383);
      break;
    case 12: ///< 小红书配图
      pixmap = pixmap.scaled(1080, 1440);
      break;
    case 13: ///< 竖版视频封面
      pixmap = pixmap.scaled(720, 1280);
      break;
    case 14: ///< 横板视频封面
      pixmap = pixmap.scaled(1280, 720);
      break;
    default:
      qDebug() << "unsupported row";
      break;
    }

    tempStk.pushBack(pixmap);

    return pixmap;
  }
}
