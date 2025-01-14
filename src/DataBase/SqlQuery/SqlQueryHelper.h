/**
 * @file SqlQueryHelper.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/12
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include "../../Manager/SqlManager.h"

namespace SqlQueryHelper
{
  inline QSharedPointer<QSqlDatabase> ensureDatabaseIsOpen()
  {
    auto& sqlInstance = SqlManager::instance();
    if (!sqlInstance.getDatabase()) {
      qCritical() << "Directory.h-- Failed to open database";
      return {};
    }
    return sqlInstance.getDatabase(); ///< 返回打开后的数据库
  }

  inline void ensureDatabaseIsClose()
  {
    SqlManager::instance().closeDatabase();
  }
}
