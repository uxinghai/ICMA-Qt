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

#include <QUrl>
#include <QWidget>

#include "../../Utils/Tools/MyAutoStack.h"

QT_BEGIN_NAMESPACE
class QLabel;
class LoadingGif;
class QGraphicsScene;
class MyGraphicsView;
class MyInformationBox;
class QGraphicsPixmapItem;

namespace Ui
{
  class PS;
}

QT_END_NAMESPACE

// 维护历史记录
// 栈顶元素是最新保存的图像
inline MyAutoStack<QPixmap> historyPixmap;

class PS final : public QWidget {
  Q_OBJECT

public:
  explicit PS(QWidget* parent = nullptr);
  ~PS() override;

protected:
  // 此处实现的拖拽勿删
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;

private slots:
  static void doGetTokenReady(const QString& token);
  void doImageOpen();
  void showImgToUi(const QPixmap& pixmap) const;
  void doUndo() const;
  void doSizeChange() const;
  static void doShowFaceTest();

  // 保存图像，未指定路径则给用户选择
  void doImageSave(bool isSaveAs);
  void showInformationMessage(const QString& message, bool isSuccess);

  void doToolBoxChanged(int index);
  void doCropChange(int row) const;
  void doResizeChange(int row) const;

private:
  void init();
  void setupConnections();
  void getBaiduAIToken();
  void updateUIState(bool enable) const;
  void showImgSize(const QPixmap& showPixmap) const;
  static void pushToHistory(const QPixmap& pixmap);
  Ui::PS* ui;

  QGraphicsScene* scene;

  QString pixFilePath;       ///< 打开的图像位置，是filePath完整路径
  QPixmap srcPixmap;         ///< 保留原始图片
  QPixmap shouldBeProcessed; ///< !!!应该被处理的图像（每次切换模块时变换）
  QPixmap curPixmap;         ///< 显示的当前图像，每次调用show之前保留
};
