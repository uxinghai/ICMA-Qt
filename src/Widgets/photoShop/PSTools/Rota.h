/**
 * @file Rota.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/25
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QPixmap>

namespace DoRota
{
  inline QPixmap rota(const QPixmap& pixmap, const int rotaValue)
  {
    return pixmap.transformed(QTransform().rotate(rotaValue));
  }
}
