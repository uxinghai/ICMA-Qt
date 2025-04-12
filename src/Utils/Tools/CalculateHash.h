/**
 * @file CalculateHash.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/3/9
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QCryptographicHash>
#include <QFile>
#include <QString>

/**
 * @brief   计算文件的哈希值
 * @param fileAbsPath  文件路径
 * @param algorithm  哈希算法
 * @return
 */
inline QString calculateHash(const QString& fileAbsPath,
                             const QCryptographicHash::Algorithm algorithm)
{
  QFile file(fileAbsPath);
  if (!file.open(QIODevice::ReadOnly)) { return {}; }

  QCryptographicHash hash(algorithm);

  // 获取文件大小用于进度计算
  const qint64 fileSize = file.size();
  int lastProgress = 0;

  // 使用分块读取处理大文件
  constexpr qint64 bufferSize = 1024 * 1024; ///< 1MB 缓冲区

  while (!file.atEnd()) {
    constexpr qint64 bytesRead = 0;
    QByteArray buffer = file.read(bufferSize);
    hash.addData(buffer);

    if (const int progress = static_cast<int>(bytesRead * 100 / fileSize);
      progress != lastProgress) { lastProgress = progress; }
  }

  return hash.result().toHex();
}
