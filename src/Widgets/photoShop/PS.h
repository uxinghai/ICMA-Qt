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
#include <QWidget>

#include "../../Utils/Tools/MyAutoStack.h"
#include "ShareSrc.h"

QT_BEGIN_NAMESPACE

namespace Ui
{
  class PS;
}

class QGraphicsScene;
QT_END_NAMESPACE

inline MyAutoStack historyPixmap;

class PS final : public QWidget {
  Q_OBJECT

public:
  explicit PS(QWidget* parent = nullptr);
  ~PS() override;

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;

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

private:
  void init();
  void setupConnections();
  void updateUIState(bool enable) const;
  void showImgSize(const QPixmap& showPixmap) const;
  static void pushToHistory(const QPair<cv::Mat, MatInfo>& pixmap);
  void updateUIFromInfo(const MatInfo& matInfo) const;
  void showInformationMessage(const QString& message, bool isSuccess);

  Ui::PS* ui;
  QGraphicsScene* scene;
  QString pixFilePath;
  QPair<cv::Mat, MatInfo> srcMat;
  cv::Mat processedMat;
  MatInfo curMatInfo;
  QPair<cv::Mat, MatInfo> curMat;
};
