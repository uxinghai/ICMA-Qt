/**
 * @file DiskAnalyzer.h
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

#include <QFileSystemModel>
#include <QMainWindow>

class QChart;
class QChartView;
QT_BEGIN_NAMESPACE

namespace Ui
{
  class DiskAnalyzer;
}

QT_END_NAMESPACE

class DiskAnalyzer final : public QMainWindow {
  Q_OBJECT

public:
  explicit DiskAnalyzer(QWidget* parent = nullptr);
  ~DiskAnalyzer() override;

signals:
  void WindowClose();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void onDirectorySelected(const QModelIndex& index);
  void on_actionScan_triggered();
  void on_actionSwitchTo2D_triggered();
  void on_actionSwitchTo3D_triggered();
  void onDriveChanged(int index);

private:
  Ui::DiskAnalyzer* ui;
  QFileSystemModel* dirModel;
  QChartView* chartView;
  QChart* chart;
  void loadFileTable(const QString& path);
  void updateChart(const QString& path);
  void updateDriveInfoWidget();
  void onUpdateBarChartClicked();
};
