/**
* @file PS.h
 *
 * @brief 图像处理模块
 *
 * @version 1.0
 * @date 2025/01/17
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <opencv2/core/mat.hpp>
#include <QSpinBox>
#include <QWidget>

#include "../../Utils/Tools/MyAutoStack.h"
#include "ShareSrc.h"

QT_BEGIN_NAMESPACE
class QGraphicsScene;
class NoWheelSlider;

namespace Ui
{
  class PS;
}

QT_END_NAMESPACE

inline MyAutoStack historyPixmap;

class PS final : public QWidget {
  Q_OBJECT

public:
  explicit PS(QWidget* parent = nullptr);
  ~PS() override;

signals:
  void WindowClose();

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;
  void closeEvent(QCloseEvent* event) override;

private slots:
  void doImageOpen();
  void showImgToUi(const QPair<cv::Mat, MatInfo>& showPixmap);
  void doUndo();
  void doReset();
  void doSizeChange();
  static void doShowFaceTest();
  void doImageSave(bool isSaveAs);
  void doToolBoxChanged(int index);
  void doCropChange(int row);
  void doResizeChange(int row);
  void doAdjust();

private:
  void init() const;
  void setupConnections();
  void setupSliderConnections(const NoWheelSlider* slider,
                              QDoubleSpinBox* spinBox,
                              const std::function<void(int)>& valueUpdateFunc,
                              double sliderDivisor = 1.0,
                              double spinBoxMultiplier = 1.0);
  void setupRotationConnections();
  void applyBlurAlgorithm(const QString& radioButtonName,
                          const std::function<void(
                            const cv::Mat&, cv::Mat&, int)>
                          & blurFunc);
  void setupBlurAlgorithmConnections();
  void updateMatAndUI();
  void updateUIState(bool enable) const;
  void showImgSize(const QPixmap& showPixmap) const;
  static void pushToHistory(const QPair<cv::Mat, MatInfo>& pixmap);
  void updateUIFromInfo(const MatInfo& matInfo);
  void showInformationMessage(const QString& message, bool isSuccess);
  void setupFilterConnections();

  Ui::PS* ui;
  QGraphicsScene* scene;
  QString pixFilePath;
  QPair<cv::Mat, MatInfo> srcMat;
  QPair<cv::Mat, MatInfo> curMat;

  // 以下两个在程序中共享，想要仔细统筹
  cv::Mat processedMat; ///< 图像初始时、功能模块切换时、图像撤回时
  MatInfo curMatInfo;
  bool isProgrammaticChange = false; ///< 标记某些信号是由程序触发
};
