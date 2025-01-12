/**
 * @file FilesDBWorker.h
 *
 * @brief 系统文件写入数据库的头文件
 *
 * 该头文件用于将系统文件写入数据库
 * 写入数据库采用事务，原子性操作，确保数据一致性，安全完整
 * 多线程支持，保证现代系统中100万个文件内容在几分钟之内读取一遍
 *
 * @version 1.0
 * @date 2024/10/21
 *
 * @author uxinghai
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <QtConcurrent>

class SplashScreen;

/** 注释保留！
 *  从系统磁盘中读取文件到数据库
 * 难点：怎么监视所有磁盘文件的新增或删除。这样就只用更新具体数据库位置即可
 * 所有数据库应该怎么存！文件夹单独存放
 * 文件夹表：文件夹Id 文件夹名Name 父文件夹ID...。磁盘看作顶层文件夹C:/ D:/...
 * 文件表： 文件ID 文件名 ...... 父文件夹ID
 */
class FilesDBWorker {
public:
  bool doFullWork(SplashScreen* splash);
  bool doIncrementalScan(SplashScreen* splash);

private:
  static void updateLastBuildSqlTime();
  static void processDirectory(const QString& dirPath);
  static void processBatch(const QVector<QString>& files);
};
