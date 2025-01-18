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

class QLabel;
class LoadingGif;
class QGraphicsScene;
class MyGraphicsView;
class QGraphicsPixmapItem;
QT_BEGIN_NAMESPACE

namespace Ui
{
  class PS;
}

QT_END_NAMESPACE

class PS final : public QWidget {
  Q_OBJECT

public:
  PS();
  ~PS() override;

protected:
  void dragEnterEvent(QDragEnterEvent* event) override;
  void dropEvent(QDropEvent* event) override;

private slots:
  static void doGetTokenReady(const QString& token);
  void doOpenImg();
  void showImgToUi(const QString& imgPath);

private:
  void init();
  void setupConnections();
  void getBaiduAIToken();
  void setEnableButton(bool enable) const;

  Ui::PS* ui;

  QGraphicsScene* scene;
  QGraphicsPixmapItem* mySceneItem;
};
