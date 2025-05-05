#include "DiskAnalyzer.h"

#include <QDir>
#include <QFileInfo>
#include <QStandardItemModel>
#include <QStorageInfo>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QValueAxis>

#include "../../../UI/ui_DiskAnalyzer.h"
#include "ChartBuilder.h"

DiskAnalyzer::DiskAnalyzer(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::DiskAnalyzer)
{
  ui->setupUi(this);

  ui->label->setVisible(false);
  ui->driveComboBox->setVisible(false);

  ui->driveComboBox->clear();
  QFileInfoList drives = QDir::drives();
  for (const QFileInfo& drive : drives) {
    ui->driveComboBox->addItem(drive.absoluteFilePath());
  }
  dirModel = new QFileSystemModel(this);
  dirModel->setRootPath("");
  dirModel->setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
  ui->directoryTreeView->setModel(dirModel);
  ui->directoryTreeView->setRootIndex(dirModel->index(QDir::rootPath()));

  connect(ui->directoryTreeView, &QTreeView::clicked,
          this, &DiskAnalyzer::onDirectorySelected);
  connect(ui->driveComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &DiskAnalyzer::onDriveChanged);
  connect(ui->driveInfoWidget, &QTreeWidget::itemClicked,
          [this](QTreeWidgetItem* item, int column) {
            ui->driveComboBox->setCurrentIndex(ui->driveInfoWidget->currentIndex().row());
          });

  for (const auto Object : ui->widget->findChildren<QComboBox*>()) {
    connect(Object, &QComboBox::currentIndexChanged, this,
            &DiskAnalyzer::onUpdateBarChartClicked);
  }

  chartView = new QChartView();
  chartView->setRenderHint(QPainter::Antialiasing);
  const auto layout = new QVBoxLayout(ui->barChartView);
  layout->addWidget(chartView);

  onUpdateBarChartClicked();

  updateDriveInfoWidget();
}

DiskAnalyzer::~DiskAnalyzer() { delete ui; }

void DiskAnalyzer::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
  QMainWindow::closeEvent(event);
}

void DiskAnalyzer::onDirectorySelected(const QModelIndex& index)
{
  const QString path = dirModel->filePath(index);
  loadFileTable(path);
  updateChart(path);
}

void DiskAnalyzer::loadFileTable(const QString& path)
{
  const QDir dir(path);
  QFileInfoList list = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

  const auto model = new QStandardItemModel(this);
  model->setHorizontalHeaderLabels({"文件名", "大小 (KB)", "类型", "修改时间"});

  for (const QFileInfo& info : list) {
    QList<QStandardItem*> row;
    row << new QStandardItem(info.fileName());
    row << new QStandardItem(QString::number(info.size() / 1024.0, 'f', 2));
    row << new QStandardItem(info.suffix());
    row << new QStandardItem(info.lastModified().toString("yyyy-MM-dd HH:mm"));
    model->appendRow(row);
  }

  ui->fileTableView->setModel(model);
  ui->fileTableView->resizeColumnsToContents();
}

void DiskAnalyzer::on_actionScan_triggered()
{
  const QModelIndex index = ui->directoryTreeView->currentIndex();
  const QString path = dirModel->filePath(index);
  loadFileTable(path);
  updateChart(path);
}

void DiskAnalyzer::on_actionSwitchTo2D_triggered()
{
  ui->chartStackedWidget->setCurrentIndex(0);
}

void DiskAnalyzer::on_actionSwitchTo3D_triggered()
{
  ui->chartStackedWidget->setCurrentIndex(1);
}

void DiskAnalyzer::onDriveChanged(int index)
{
  QString drivePath = ui->driveComboBox->itemText(index);
  QModelIndex rootIndex = dirModel->index(drivePath);
  ui->directoryTreeView->setRootIndex(rootIndex);
}

void DiskAnalyzer::updateChart(const QString& path)
{
  const auto chart = ChartBuilder::buildPieChart(path);
  ui->chartView2D->setChart(chart);
}

void DiskAnalyzer::updateDriveInfoWidget()
{
  ui->driveInfoWidget->clear();
  ui->driveInfoWidget->setColumnCount(5);

  for (const QStorageInfo& storage : QStorageInfo::mountedVolumes()) {
    if (!storage.isValid() || !storage.isReady() || storage.isReadOnly()) continue;

    QString rootPath = storage.rootPath();
    const qint64 total = storage.bytesTotal();
    const qint64 free = storage.bytesAvailable();
    const qint64 used = total - free;
    const int percent = total > 0
                          ? static_cast<int>(static_cast<double>(used) / total * 100)
                          : 0;

    QString totalStr = QString::number(total / 1024.0 / 1024 / 1024, 'f', 2) + " GB";
    QString usedStr = QString::number(used / 1024.0 / 1024 / 1024, 'f', 2) + " GB";
    QString freeStr = QString::number(free / 1024.0 / 1024 / 1024, 'f', 2) + " GB";
    QString percentStr = QString::number(percent) + "%";

    const auto item = new QTreeWidgetItem({
      rootPath, totalStr, usedStr, freeStr, percentStr
    });
    ui->driveInfoWidget->addTopLevelItem(item);
  }
  ui->driveInfoWidget->resizeColumnToContents(0);
}

void DiskAnalyzer::onUpdateBarChartClicked()
{
  QString xField = ui->xAxisComboBox->currentText();
  QString yField = ui->yAxisComboBox->currentText();

  QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();

  QStringList xCategories;
  const auto barSet = new QBarSet(yField);

  for (const QStorageInfo& storage : volumes) {
    if (!storage.isValid() || !storage.isReady() || storage.isReadOnly()) continue;

    QString drive = storage.rootPath();
    qint64 total = storage.bytesTotal();
    qint64 free = storage.bytesAvailable();
    qint64 used = total - free;

    double value = 0;
    if (yField == "总容量") value = total / 1024.0 / 1024 / 1024;
    else if (yField == "已用空间") value = used / 1024.0 / 1024 / 1024;
    else if (yField == "可用空间") value = free / 1024.0 / 1024 / 1024;
    else if (yField == "使用率")
      value = total > 0
                ? static_cast<double>(used) / total * 100
                : 0;
    else value = 0;

    QString label;
    if (xField == "盘符") label = drive;
    else if (xField == "总容量")
      label = QString::number(total / 1024.0 / 1024 / 1024, 'f',
                              1) + "GB";
    else if (xField == "已用空间")
      label = QString::number(
        used / 1024.0 / 1024 / 1024, 'f', 1) + "GB";
    else if (xField == "可用空间")
      label = QString::number(
        free / 1024.0 / 1024 / 1024, 'f', 1) + "GB";
    else if (xField == "使用率")
      label = QString::number(static_cast<double>(used) / total * 100, 'f', 1)
        + "%";
    else label = "";

    xCategories << label;
    *barSet << value;
  }

  const auto series = new QBarSeries();
  series->append(barSet);

  chart = new QChart();
  chart->addSeries(series);
  chart->setTitle(QString("%1 vs %2").arg(xField, yField));
  chart->setAnimationOptions(QChart::SeriesAnimations);

  const auto axisX = new QBarCategoryAxis();
  axisX->append(xCategories);
  chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  const auto axisY = new QValueAxis();
  chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  chartView->setChart(chart);
}
