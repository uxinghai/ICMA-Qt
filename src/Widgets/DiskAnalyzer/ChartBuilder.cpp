#include "ChartBuilder.h"

#include "FileScanner.h"

QChart* ChartBuilder::buildPieChart(const QString& path)
{
  auto sizes = FileScanner::getFileTypeSizes(path);
  const auto series = new QPieSeries();

  for (auto it = sizes.begin(); it != sizes.end(); ++it) {
    series->append(it.key(), it.value() / 1024.0);
  }

  const auto chart = new QChart();
  chart->addSeries(series);
  chart->setTitle("文件类型占用 (KB)");
  chart->legend()->setAlignment(Qt::AlignRight);

  return chart;
}
