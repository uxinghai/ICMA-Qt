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
#include "../../Utils/Tools/MyInformationBox.h"
#include "Adjust.h"
#include "Crop.h"
#include "faceTest/FaceTest.h"
#include "faceTest/ToGetToken.h"
#include "Resize.h"
#include "Rota.h"

PS::PS(QWidget* parent) : QWidget(parent), ui(new Ui::PS),
                          scene(new QGraphicsScene(this))
{
  ui->setupUi(this);
  init();
  ToGetToken::getBaiduAIToken();
  setupConnections();
}

void PS::init() const
{
  ui->GraphicsView->setScene(scene);
  auto font = this->font();
  font.setPointSize(14);
  scene->addSimpleText(tr("拖入图片到此窗口或点击打开图片"), font);
}

void PS::setupConnections()
{
  // 基本图像操作连接
  connect(ui->btnOpenImg, &QToolButton::clicked, this, &PS::doImageOpen);
  connect(ui->btnUndo, &QToolButton::clicked, this, &PS::doUndo);
  connect(ui->btnReset, &QToolButton::clicked, this, &PS::doReset);

  // 图像对比显示
  connect(ui->btnComparison, &QToolButton::pressed, [this] {
    ui->btnComparison->setIcon(QIcon(":/ps/res/ps/OpenEye.png"));
    showImgToUi(srcMat);
  });
  connect(ui->btnComparison, &QToolButton::released, [this] {
    ui->btnComparison->setIcon(QIcon(":/ps/res/ps/CloseEye.png"));
    showImgToUi(curMat);
  });

  // 图像保存
  connect(ui->btnDireSave, &QToolButton::clicked,
          [this] { doImageSave(false); });
  connect(ui->btnSaveAs, &QToolButton::clicked, [this] { doImageSave(true); });

  // 工具箱和列表连接
  connect(ui->toolBox, &QToolBox::currentChanged, this, &PS::doToolBoxChanged);
  connect(ui->cropList, &QListWidget::currentRowChanged, this,
          &PS::doCropChange);
  connect(ui->sizeList, &QListWidget::currentRowChanged, this,
          &PS::doResizeChange);

  // 图像调整滑动条处理
  setupSliderConnections(ui->brightnessSlider, ui->spinBoxBrightness,
                         [this](const int value) {
                           curMatInfo.adjustValue.brightness = value;
                           doAdjust();
                         });

  setupSliderConnections(ui->contrastSlider, ui->spinBoxContrast,
                         [this](const int value) {
                           curMatInfo.adjustValue.contrast = value;
                           doAdjust();
                         }, 10.0);

  setupSliderConnections(ui->saturationSlider, ui->spinBoxSaturation,
                         [this](const int value) {
                           curMatInfo.adjustValue.saturation = value;
                           doAdjust();
                         }, 100.0);

  setupSliderConnections(ui->contrarySlider, ui->spinBoxContrary,
                         [this](const int value) {
                           curMatInfo.adjustValue.contrary = value;
                           doAdjust();
                         }, 255.0, 100.0);

  // 图像旋转和翻转
  setupRotationConnections();

  // 尺寸输入
  connect(ui->leSizeW, &QLineEdit::textEdited, this, &PS::doSizeChange);
  connect(ui->leSizeH, &QLineEdit::textEdited, this, &PS::doSizeChange);

  // 模糊算法连接
  setupBlurAlgorithmConnections();

  // 人脸检测
  connect(ui->FaceTestToolBtn, &QToolButton::clicked, this,
          &PS::doShowFaceTest);
}

// 通用滑动条连接处理
void PS::setupSliderConnections(const NoWheelSlider* slider,
                                QDoubleSpinBox* spinBox,
                                const std::function<void(int)>& valueUpdateFunc,
                                double sliderDivisor,
                                double spinBoxMultiplier)
{
  connect(slider, &QSlider::valueChanged,
          [this, spinBox, valueUpdateFunc, sliderDivisor,
            spinBoxMultiplier](const int value) {
            spinBox->setValue(value / sliderDivisor * spinBoxMultiplier);
            valueUpdateFunc(value);
          });

  connect(slider, &QSlider::sliderReleased, [this] { pushToHistory(curMat); });
}

// 旋转和翻转连接处理
void PS::setupRotationConnections()
{
  // 旋转按钮
  connect(ui->btnRotateLeft, &QToolButton::clicked, [this] {
    rotate(processedMat, processedMat, cv::ROTATE_90_COUNTERCLOCKWISE);
    updateMatAndUI();
  });

  connect(ui->btnRotateRight, &QToolButton::clicked, [this] {
    rotate(processedMat, processedMat, cv::ROTATE_90_CLOCKWISE);
    updateMatAndUI();
  });

  // 翻转按钮
  connect(ui->btnFlipHorizontal, &QToolButton::clicked, [this] {
    flip(processedMat, processedMat, 1);
    updateMatAndUI();
  });

  connect(ui->btnFlipVertical, &QToolButton::clicked, [this] {
    flip(processedMat, processedMat, 0);
    updateMatAndUI();
  });

  // 自由旋转滑动条
  connect(ui->rotaSlider, &QSlider::valueChanged, [this](const int value) {
    curMatInfo.rota.rotaValue = value;
    const QPixmap pixmap = DoRota::rota(matToPixmap(processedMat),
                                        value);
    curMat.first = pixmapToMat(pixmap);
    curMat.second = curMatInfo;
    showImgToUi(curMat);
  });

  connect(ui->rotaSlider, &QSlider::sliderReleased, [this] {
    pushToHistory(curMat);
  });
}

// 定义通用模糊处理函数
void PS::applyBlurAlgorithm(const QString& radioButtonName,
                            const std::function<void(
                              const cv::Mat&, cv::Mat&, int)>& blurFunc)
{
  if (processedMat.empty()) { processedMat = srcMat.first; }
  // 以上方法不想用

  int kernelValue = curMatInfo.algorithm.kernelValue;
  kernelValue = (kernelValue % 2 == 0) ? kernelValue + 1 : kernelValue;

  cv::Mat mat = cv::Mat::zeros(processedMat.size(), CV_8UC3);
  blurFunc(processedMat, mat, kernelValue);

  curMat.first = mat;
  curMatInfo.algorithm.radioButtonObjName = radioButtonName;
  curMat.second = curMatInfo;
  showImgToUi(curMat);
}

// 模糊算法连接处理
void PS::setupBlurAlgorithmConnections()
{
  // 连接各种模糊算法单选按钮
  connect(ui->radioBlur, &QRadioButton::clicked,
          [this](const bool checked) {
            if (checked)
              applyBlurAlgorithm(ui->radioBlur->objectName(),
                                 [](const cv::Mat& src, cv::Mat& dst,
                                    const int kernelSize) {
                                   blur(src, dst,
                                        cv::Size(kernelSize, kernelSize));
                                 });
          });

  connect(ui->radioMedian, &QRadioButton::clicked,
          [this](const bool checked) {
            if (checked)
              applyBlurAlgorithm(ui->radioMedian->objectName(),
                                 [](const cv::Mat& src, cv::Mat& dst,
                                    const int kernelSize) {
                                   medianBlur(src, dst, kernelSize);
                                 });
          });

  connect(ui->radioGaussion, &QRadioButton::clicked,
          [this](const bool checked) {
            if (checked)
              applyBlurAlgorithm(ui->radioGaussion->objectName(),
                                 [](const cv::Mat& src, cv::Mat& dst,
                                    const int kernelSize) {
                                   GaussianBlur(
                                     src, dst, cv::Size(kernelSize, kernelSize),
                                     0, 0);
                                 });
          });

  connect(ui->radioBilateral, &QRadioButton::clicked,
          [this](const bool checked) {
            if (checked)
              applyBlurAlgorithm(ui->radioBilateral->objectName(),
                                 [](const cv::Mat& src, cv::Mat& dst,
                                    const int kernelSize) {
                                   bilateralFilter(
                                     src, dst, kernelSize, kernelSize * 2,
                                     kernelSize / 2);
                                 });
          });

  // Kernel值修改连接
  ui->kernelValue->setEnabled(true); ///< 明明界面上已经使能了...
  connect(ui->kernelValue, &QSlider::valueChanged, [this](const int value) {
    curMatInfo.algorithm.kernelValue = value;
    ui->spinBoxKernel->setValue(value);

    // 根据当前选中的模糊算法触发相应的单选按钮
    QRadioButton* currentRadioButton = nullptr;
    if (curMatInfo.algorithm.radioButtonObjName == "radioBlur")
      currentRadioButton = ui->radioBlur;
    else if (curMatInfo.algorithm.radioButtonObjName == "radioMedian")
      currentRadioButton = ui->radioMedian;
    else if (curMatInfo.algorithm.radioButtonObjName == "radioGaussion")
      currentRadioButton = ui->radioGaussion;
    else if (curMatInfo.algorithm.radioButtonObjName ==
      "radioBilateral")
      currentRadioButton = ui->radioBilateral;

    if (currentRadioButton)
      currentRadioButton->click();
  });

  connect(ui->kernelValue, &QSlider::sliderReleased, [this] {
    pushToHistory(curMat);
  });
}

// 辅助函数：更新图像并刷新UI
void PS::updateMatAndUI()
{
  curMat.first = processedMat;
  showImgToUi(curMat);
  pushToHistory(curMat);
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

    const auto curMat = historyPixmap.top();
    processedMat = curMat.first;
    curMatInfo = curMat.second;
    showImgToUi(curMat);
  }
  else { ///< 调用还原
    ui->btnReset->click();
  }
}

void PS::doReset()
{
  historyPixmap.clear(); ///< 还原清空历史记录
  historyPixmap.push(srcMat);
  processedMat = srcMat.first;
  curMatInfo = srcMat.second;
  showImgToUi(srcMat);
}

void PS::doCropChange(const int row)
{
  if (isProgrammaticChange) { return; }
  curMatInfo.crop.cropValue = row;
  const auto pixmap = DoCrop::cropPixmapBy(matToPixmap(processedMat), row);
  curMat.first = pixmapToMat(pixmap);
  curMat.second = curMatInfo;
  showImgToUi(curMat);
  pushToHistory(curMat);
}

void PS::doResizeChange(const int row)
{
  if (isProgrammaticChange) { return; }
  const QPixmap pixmap = DoResize::resizePixmapBy(
    matToPixmap(processedMat), row,
    ui->lockedWHRatio->isChecked());

  curMat.first = pixmapToMat(pixmap);
  curMatInfo.resize.resizeValue = row;
  curMat.second = curMatInfo;
  showImgToUi(curMat);
  pushToHistory(curMat);
}

void PS::doAdjust()
{
  // 有时候真不是想额外添加代码，但真找不到内在错误，只能解决表象上的错误了...
  if (processedMat.empty()) { processedMat = srcMat.first; }
  // 以上方法不想用
  const cv::Mat mat = Adjust::adjustMat(processedMat,
                                        ui->spinBoxBrightness->value(),
                                        ui->spinBoxContrast->value(),
                                        ui->spinBoxSaturation->value(),
                                        ui->spinBoxContrary->value());
  curMat.first = mat;
  curMat.second = curMatInfo;
  showImgToUi(curMat);
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
  if (!isSaveAs) { ///< 不是另存
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

  if (const cv::Mat mat = curMat.first;
    matToPixmap(mat).save(pixFilePath)) {
    showInformationMessage(tr("保存成功"), true);
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
  processedMat = curMat.first;
}

void PS::showImgToUi(const QPair<cv::Mat, MatInfo>& showPixmap)
{
  scene->clear();
  const cv::Mat mat = showPixmap.first;

  const auto pixmap = matToPixmap(mat);
  scene->addItem(new QGraphicsPixmapItem(pixmap));
  scene->setSceneRect(pixmap.rect());

  ui->GraphicsView->setSceneRect(scene->sceneRect());
  ui->GraphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

  showImgSize(pixmap);
  updateUIFromInfo(showPixmap.second);
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

void PS::updateUIFromInfo(const MatInfo& matInfo)
{
  isProgrammaticChange = true;
  ui->brightnessSlider->setValue(
    static_cast<int>(matInfo.adjustValue.brightness));
  ui->saturationSlider->setValue(
    static_cast<int>(matInfo.adjustValue.saturation));
  ui->contrastSlider->setValue(static_cast<int>(matInfo.adjustValue.contrast));
  ui->contrarySlider->setValue(static_cast<int>(matInfo.adjustValue.contrary));
  ui->kernelValue->setValue(matInfo.algorithm.kernelValue);
  for (const auto obj : ui->algorithm->findChildren<QRadioButton*>()) {
    if (obj->objectName() == matInfo.algorithm.radioButtonObjName) {
      obj->setChecked(true);
    }
  }
  //ui->rotaSlider->setValue(matInfo.crop.cropValue);///< 不需要！！！
  ui->sizeList->setCurrentRow(matInfo.resize.resizeValue);
  ui->cropList->setCurrentRow(matInfo.crop.cropValue);
  isProgrammaticChange = false;
}

PS::~PS() { delete ui; }
