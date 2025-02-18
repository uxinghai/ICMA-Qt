/**
 * @file CustomQueryModel.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/2/17
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QSqlQueryModel>

#include "DataUnitCalc.h"

class CustomQueryModel final : public QSqlQueryModel {
public:
  QVariant data(const QModelIndex& index,
                const int role = Qt::DisplayRole) const override
  {
    // 检查是否是"大小"列
    if (role == Qt::DisplayRole && index.column() == 2) { ///< "大小"是第3列
      // 获取原始数据
      const QVariant originalData = QSqlQueryModel::data(index, role);
      return DataUnitCalc::setDataUnit(originalData.toLongLong());
    }
    return QSqlQueryModel::data(index, role);
  }
};
