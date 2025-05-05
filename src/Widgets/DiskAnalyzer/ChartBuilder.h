/**
 * @file ChartBuilder.h
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

#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>

class ChartBuilder {
public:
  static QChart* buildPieChart(const QString& path);
};
