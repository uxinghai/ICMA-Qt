/**
 * @file DataUnitCalc.h
 *
 * @Breife 用于返回传入数据的合适单位
 *         小于 1kb 显示为 b
 *         小于 1Mb 显示为 kb
 *         以此类推
 *
 * @version 1.0
 * @date 2025/2/9
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QString>

class DataUnitCalc final {
public:
  /**
   * @brief 返回传入数据的合适单位
   * @param data 传入的数据量 (qsizetype 类型)
   * @return QString 数据量和单位
   */
  static QString setDataUnit(const qsizetype& data)
  {
    const QString strData = QString::number(data);
    if (strData.isEmpty()) { return {}; }
    if (strData.toLongLong() < 1024.0) { return QString("%1 B").arg(strData); }
    if (strData.toLongLong() < 1024.0 * 1024.0) {
      return QString("%1 KB").arg(strData.toLongLong() / 1024.0);
    }
    if (strData.toLongLong() < 1024.0 * 1024.0 * 1024.0) {
      return QString("%1 MB").arg(strData.toLongLong() / (1024.0 * 1024.0));
    }
    if (strData.toLongLong() < 1024.0 * 1024.0 * 1024.0 * 1024.0) {
      return QString("%1 GB").arg(
        strData.toLongLong() / (1024.0 * 1024.0 * 1024.0));
    }
    return QString("%1 TB").arg(
      strData.toLongLong() / (1024.0 * 1024.0 * 1024.0 * 1024.0));
  }

  /**
   * @brief 获取数据量单位
   * @param data 传入的数据量 (qsizetype 类型)
   * @return QString 数据量的单位
   */
  static QString getOnlyUnit(const qsizetype& data)
  {
    const QString strData = QString::number(data);
    if (strData.isEmpty()) { return {}; }
    if (strData.toLongLong() < 1024.0) { return "B"; }
    if (strData.toLongLong() < 1024.0 * 1024.0) { return "KB"; }
    if (strData.toLongLong() < 1024.0 * 1024.0 * 1024.0) { return "MB"; }
    if (strData.toLongLong() < 1024.0 * 1024.0 * 1024.0 * 1024.0) {
      return "GB";
    }
    return "TB";
  }

  /**
   * @brief 根据单位获取对应的除数
   * @param unit 单位
   * @return qsizetype
   */
  static double getDivisorByUnit(const QString& unit)
  {
    if (unit == "B") { return 1; }
    if (unit == "KB") { return 1024.0; }
    if (unit == "MB") { return 1024.0 * 1024.0; }
    if (unit == "GB") { return 1024.0 * 1024.0 * 1024.0; }
    if (unit == "TB") { return 1024.0 * 1024.0 * 1024.0 * 1024.0; }
    return 0;
  }
};
