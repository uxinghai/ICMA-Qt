/**
 * @file Tags.h
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

class TagDB {
public:
  static TagDB& getInstance()
  {
    static TagDB instance;
    return instance;
  }


  QStringList getTagsByFileID(const quint32& id)
  {
    QStringList res;

    return res;
  }
};

#define sTagDB TagDB::getInstance()
