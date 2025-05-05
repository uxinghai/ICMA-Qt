#include <QDir>
#include <QFileInfoList>

#include "filescanner.h"

QMap<QString, qint64> FileScanner::getFileTypeSizes(const QString& path)
{
  QMap<QString, qint64> typeSizeMap;
  const QDir dir(path);
  QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

  for (const QFileInfo& info : list) {
    QString suffix = info.suffix().toLower();
    if (suffix.isEmpty()) suffix = "其他";
    typeSizeMap[suffix] += info.size();
  }

  return typeSizeMap;
}
