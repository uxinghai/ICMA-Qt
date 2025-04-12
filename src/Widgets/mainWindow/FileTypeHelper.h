/**
 * @file FileTypeHelper.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/4/6
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once
#include <QStringList>

// 后续便于直接在此处添加后缀
namespace FileTypeHelper
{
  inline QStringList PixmapSuffixes{
    "png", "jpg", "jpeg", "bmp", "gif", "svg", "ico", "webp"
  };

  inline QStringList TextSuffixes{
    "txt", "log", "ini", "json", "xml", "html", "css", "js", "cpp", "h"
  };
}
