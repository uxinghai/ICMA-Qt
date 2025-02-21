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

#include <QSqlQuery>
#include <QSqlQueryModel>

#include "../../Manager/SqlManager.h"
#include "DataUnitCalc.h"

class MyQueryModel final : public QSqlQueryModel {
public:
  // 大小列统一修改格式
  QVariant data(const QModelIndex& index,
                const int role = Qt::DisplayRole) const override
  {
    if (role == Qt::DisplayRole && index.column() == 2) { ///< "大小"是第3列
      // 获取原始数据
      const QVariant originalData = QSqlQueryModel::data(index, role);
      return DataUnitCalc::setDataUnit(originalData.toLongLong());
    }
    return QSqlQueryModel::data(index, role);
  }

  // 按列排序 后续再写，现在排序提示数据库意外被关闭，所以无法排序
  //   void sort(const int column, const Qt::SortOrder order) override
  //   {
  //     // 获取当前 SQL 语句
  //     QString baseQuery = this->query().lastQuery();
  //
  //     // 获取排序字段
  //     QString orderStr = (order == Qt::AscendingOrder) ? "ASC" : "DESC";
  //     QString columnName = this->headerData(column, Qt::Horizontal).toString();
  //
  //     // 重新构造 SQL 语句
  //     const QString sortedQuery = QString("%1 ORDER BY \"%2\" %3").arg(
  //       baseQuery, columnName, orderStr);
  // qDebug() << sortedQuery;
  //     // 执行新查询
  //     this->setQuery(sortedQuery);
  //   }
};
