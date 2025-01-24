#include "PS.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>
#include <QMimeData>
#include <QStandardPaths>
#include <QUrl>

#include "../../../UI/ui_FaceTest.h"
#include "../../../UI/ui_PS.h"
#include "../../Manager/Config/iniManager.h"
#include "../../Network/GetBaiduToken.h"
#include "../../Utils/Tools/MyInformationBox.h"
#include "Adjust.h"
#include "Crop.h"
#include "faceTest/FaceTest.h"
#include "faceTest/ToGetToken.h"
#include "Resize.h"

PS::PS(QWidget* parent) : QWidget(parent), ui(new Ui::PS),
                          scene(new QGraphicsScene(this))
{
  ui->setupUi(this);
  init();
  ToGetToken::getBaiduAIToken();
  setupConnections();
}

void PS::init()
{
  ui->GraphicsView->setScene(scene);
  auto font = this->font();
  font.setPointSize(14);
  scene->addSimpleText(tr("拖入图片到此窗口或点击打开图片"), font);
}

void PS::setupConnections()
{
  // 连接各种信号和槽
  connect(ui->btnOpenImg, &QToolButton::clicked, this, &PS::doImageOpen);
  connect(ui->btnUndo, &QToolButton::clicked, this, &PS::doUndo);
  connect(ui->btnReset, &QToolButton::clicked, this, &PS::doReset);

  // 图像对比
  connect(ui->btnComparison, &QToolButton::pressed, [this] {
    ui->btnComparison->setIcon(QIcon(":/ps/res/ps/OpenEye.png"));
    showImgToUi(curMat);
  });

  connect(ui->btnComparison, &QToolButton::released, [this] {
    ui->btnComparison->setIcon(QIcon(":/ps/res/ps/CloseEye.png"));
    showImgToUi(historyPixmap.top());
  });

  // 图像保存
  connect(ui->btnDireSave, &QToolButton::clicked,
          [this] { doImageSave(false); });
  connect(ui->btnSaveAs, &QToolButton::clicked, [this] { doImageSave(true); });

  // 其他连接（调整、尺寸、裁剪等）
  connect(ui->toolBox, &QToolBox::currentChanged, this, &PS::doToolBoxChanged);
  connect(ui->cropList, &QListWidget::currentRowChanged, this,
          &PS::doCropChange);
  connect(ui->sizeList, &QListWidget::currentRowChanged, this,
          &PS::doResizeChange);

  // 图像调整滑动条处理
  connect(ui->brightnessSlider, &QSlider::valueChanged,
          [this](const int value) {
            ui->spinBoxBrightness->setValue(value);
            curMatInfo.adjustValue.brightness = value;

            const cv::Mat mat = Adjust::adjustMat(processedMat,
                                                  ui->spinBoxBrightness->
                                                  value(),
                                                  ui->spinBoxContrast->value(),
                                                  ui->spinBoxSaturation->
                                                  value(),
                                                  ui->spinBoxContrary->value());
            curMat.first = mat;
            curMat.second = curMatInfo;
            showImgToUi(curMat);
          });
  connect(ui->brightnessSlider, &QSlider::sliderReleased, [this] {
    pushToHistory(curMat);
  });
  connect(ui->contrastSlider, &QSlider::valueChanged,
          [this](const int value) {
            ui->spinBoxContrast->setValue(value / 10.0);
            curMatInfo.adjustValue.contrast = value;

            const cv::Mat mat = Adjust::adjustMat(processedMat,
                                                  ui->spinBoxBrightness->
                                                  value(),
                                                  ui->spinBoxContrast->value(),
                                                  ui->spinBoxSaturation->
                                                  value(),
                                                  ui->spinBoxContrary->value());
            curMat.first = mat;
            curMat.second = curMatInfo;
            showImgToUi(curMat);
          });
  connect(ui->contrastSlider, &QSlider::sliderReleased, [this] {
    pushToHistory(curMat);
  });
  connect(ui->saturationSlider, &QSlider::valueChanged,
          [this](const int value) {
            ui->spinBoxSaturation->setValue(value / 100.0);
            curMatInfo.adjustValue.saturation = value;

            const cv::Mat mat = Adjust::adjustMat(processedMat,
                                                  ui->spinBoxBrightness->
                                                  value(),
                                                  ui->spinBoxContrast->value(),
                                                  ui->spinBoxSaturation->
                                                  value(),
                                                  ui->spinBoxContrary->value());
            curMat.first = mat;
            curMat.second = curMatInfo;
            showImgToUi(curMat);
          });
  connect(ui->saturationSlider, &QSlider::sliderReleased, [this] {
    pushToHistory(curMat);
  });
  connect(ui->contrarySlider, &QSlider::valueChanged,
          [this](const int value) {
            ui->spinBoxContrary->setValue(value / 255.0 * 100.0);
            curMatInfo.adjustValue.contrary = value;

            const cv::Mat mat = Adjust::adjustMat(processedMat,
                                                  ui->spinBoxBrightness->
                                                  value(),
                                                  ui->spinBoxContrast->value(),
                                                  ui->spinBoxSaturation->
                                                  value(),
                                                  ui->spinBoxContrary->value());
            curMat.first = mat;
            curMat.second = curMatInfo;
            showImgToUi(curMat);
          });
  connect(ui->contrarySlider, &QSlider::sliderReleased, [this] {
    pushToHistory(curMat);
  });

  // 尺寸输入
  connect(ui->leSizeW, &QLineEdit::textEdited, this, &PS::doSizeChange);
  connect(ui->leSizeH, &QLineEdit::textEdited, this, &PS::doSizeChange);

  // 人脸检测
  connect(ui->FaceTestToolBtn, &QToolButton::clicked, this,
          &PS::doShowFaceTest);
}

void PS::doImageOpen()
{
  // 构建选择文件对话框
  QString filter = tr("图片文件(");
  for (const auto& suffix : suffixList) { filter += "*." + suffix + " "; }
  filter += ")";
  pixFilePath = QFileDialog::getOpenFileName(this, tr("打开图片"), "../", filter);
  if (pixFilePath.isEmpty()) { return; }

  // 加载图像并检查
  cv::Mat mat = cv::imread(pixFilePath.toLocal8Bit().toStdString(), 1);
  if (mat.empty()) {
    QMessageBox::warning(this, tr("错误"), tr("无法加载图片文件！"));
    return;
  }

  // 转换到 RGB 格式并备份
  cvtColor(mat, mat, cv::COLOR_BGR2RGB);
  processedMat = mat.clone();

  // 更新 srcMat
  srcMat.first = mat;
  srcMat.second = curMatInfo;

  // 显示图像到 UI，并更新状态
  showImgToUi(srcMat);
  pushToHistory(srcMat);         ///< 存入历史记录
  updateUIState(true);           ///< 更新按钮状态
  ui->toolBox->setEnabled(true); ///< 启用工具栏
}

void PS::dragEnterEvent(QDragEnterEvent* event)
{
  // 检查拖入的文件是否有效
  if (const auto* mimeData = event->mimeData(); mimeData->hasUrls()) {
    const QString localFile = mimeData->urls().first().toLocalFile();

    if (const QFileInfo info(localFile);
      suffixList.contains(info.suffix().toUpper())) {
      event->acceptProposedAction();
      return;
    }
  }
  QWidget::dragEnterEvent(event);
}

void PS::dropEvent(QDropEvent* event)
{
  if (!event) { return; }

  // 检查拖入的文件
  if (const auto* mimeData = event->mimeData(); mimeData->hasUrls()) {
    const QString localFile = mimeData->urls().first().toLocalFile();
    cv::Mat mat = cv::imread(localFile.toLocal8Bit().toStdString(), 1);

    if (mat.empty()) {
      QMessageBox::warning(this, tr("错误"), tr("无法加载拖放的图片文件！"));
      return;
    }

    // 转换到 RGB 格式并更新
    cvtColor(mat, mat, cv::COLOR_BGR2RGB);
    processedMat = mat.clone();

    // 更新 srcMat
    srcMat.first = mat;
    srcMat.second = curMatInfo;

    // 显示图像到 UI
    showImgToUi(srcMat);
    processedMat = srcMat.first;
    updateUIFromInfo(srcMat.second);

    // 更新历史记录和工具栏状态
    pushToHistory(srcMat);
    ui->toolBox->setEnabled(true);

    // 更新文件路径
    pixFilePath = localFile;
  }
  QWidget::dropEvent(event);
}

void PS::doUndo()
{
  if (historyPixmap.size() > 2) {
    historyPixmap.pop();
    showImgToUi(historyPixmap.top());
    updateUIFromInfo(curMat.second);
  }
  else { ui->btnReset->click(); }
}

void PS::doReset()
{
  showImgToUi(srcMat);
  historyPixmap.clear(); ///< 还原清空历史记录
  historyPixmap.push(srcMat);
  updateUIFromInfo(srcMat.second);
}

void PS::doCropChange(const int row)
{
  const auto pixmap = DoCrop::cropPixmapBy(matToPixmap(processedMat), row);
  curMat.first = pixmapToMat(pixmap);
  curMatInfo.crop.cropValue = row;
  curMat.second = curMatInfo;
  showImgToUi(curMat);
  pushToHistory(curMat);
}

void PS::doResizeChange(const int row)
{
  const QPixmap pixmap = DoResize::resizePixmapBy(
    matToPixmap(processedMat), row,
    ui->lockedWHRatio->isChecked());

  curMat.first = pixmapToMat(pixmap);
  curMatInfo.resize.resizeValue = row;
  curMat.second = curMatInfo;
  showImgToUi(curMat);
  pushToHistory(curMat);
}

void PS::doSizeChange()
{
  ui->sizeList->setCurrentRow(0);
  const auto pixmap = DoResize::resizePixmapBy(
    matToPixmap(processedMat),
    0,
    ui->lockedWHRatio->isChecked(),
    ui->leSizeW->text().toInt(),
    ui->leSizeH->text().toInt()
  );

  curMat.first = pixmapToMat(pixmap);
  curMat.second = curMatInfo;
  showImgToUi(curMat);
  pushToHistory(curMat);
}

void PS::doShowFaceTest()
{
  const auto faceTestWidget = new FaceTest();
  faceTestWidget->setAttribute(Qt::WA_DeleteOnClose);
  faceTestWidget->show();
}

void PS::doImageSave(const bool isSaveAs)
{
  if (!isSaveAs) {
    if (QMessageBox::information(this, tr("询问"), tr("是否要替换文件"),
                                 QMessageBox::Ok | QMessageBox::Cancel) !=
      QMessageBox::Ok) { return; }
  }
  else {
    pixFilePath = QFileDialog::getSaveFileName(
      this,
      tr("另存为"),
      QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
      "*.png;;*.jpg;;*.jpeg"
    );
    if (pixFilePath.isEmpty()) { return; }
  }

  // 保存栈顶图像
  if (const cv::Mat mat = historyPixmap.top().first;
    matToPixmap(mat).save(pixFilePath)) {
    showInformationMessage(tr("保存成功"), true);
    historyPixmap.afterSavePixmap();
    srcMat = historyPixmap.top();
    processedMat = mat;
  }
  else { showInformationMessage(tr("保存失败"), false); }
}

void PS::showInformationMessage(const QString& message, const bool isSuccess)
{
  auto* information = new MyInformationBox(this);
  if (isSuccess) { information->setText(message); }
  else { information->setText(tr("保存失败")); }
  information->show();
}

void PS::doToolBoxChanged(const int index)
{
  Q_UNUSED(index);
  processedMat = historyPixmap.top().first;
}

void PS::showImgToUi(const QPair<cv::Mat, MatInfo>& showPixmap)
{
  scene->clear();
  const cv::Mat mat = showPixmap.first;
  const auto pixmap = matToPixmap(mat);

  auto* pixmapItem = new QGraphicsPixmapItem(pixmap);
  scene->addItem(pixmapItem);
  scene->setSceneRect(pixmap.rect());

  ui->GraphicsView->setSceneRect(scene->sceneRect());
  ui->GraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

  showImgSize(pixmap);
  curMatInfo = showPixmap.second;
  updateUIFromInfo(curMatInfo);
}

void PS::updateUIState(const bool enable) const
{
  ui->btnReset->setEnabled(enable);
  ui->btnUndo->setEnabled(enable);
  ui->btnComparison->setEnabled(enable);
  ui->btnSaveAs->setEnabled(enable);
  ui->btnDireSave->setEnabled(enable);
}

void PS::showImgSize(const QPixmap& showPixmap) const
{
  if (!showPixmap.isNull()) {
    const QString height = QString::number(showPixmap.height());
    const QString width = QString::number(showPixmap.width());
    ui->leSizeH->setText(height);
    ui->leSizeH2->setText(height);
    ui->leSizeW->setText(width);
    ui->leSizeW2->setText(width);
  }
}

void PS::pushToHistory(const QPair<cv::Mat, MatInfo>& pixmap)
{
  if (historyPixmap.empty()) { historyPixmap.push(pixmap); }
  const MatInfo lastMatInfo = historyPixmap.top().second;
  if (const MatInfo curMatInfo = pixmap.second;
    lastMatInfo != curMatInfo) { historyPixmap.push(pixmap); }
}

void PS::updateUIFromInfo(const MatInfo& matInfo) const
{
  ui->brightnessSlider->setValue(matInfo.adjustValue.brightness);
  ui->saturationSlider->setValue(matInfo.adjustValue.saturation);
  ui->contrastSlider->setValue(matInfo.adjustValue.contrast);
  ui->contrarySlider->setValue(matInfo.adjustValue.contrary);
  ui->kernelValue->setValue(matInfo.algorithm.kernelValue);
  for (const auto obj : ui->algorithm->findChildren<QRadioButton*>()) {
    if (obj->objectName() == matInfo.algorithm.radioButtonObjName) {
      obj->setChecked(true);
    }
  }
  ui->rotaSlider->setValue(matInfo.crop.cropValue);
  ui->sizeList->setCurrentRow(matInfo.resize.resizeValue);
  ui->cropList->setCurrentRow(matInfo.crop.cropValue);
}

PS::~PS() { delete ui; }
