/**
 * @file FileScanner.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/5/4
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QMap>

class FileScanner {
public:
  static QMap<QString, qint64> getFileTypeSizes(const QString& path);
};
