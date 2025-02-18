/**
 * @file imagecropperlabel.h
 *
 * @brief 图像裁剪器标签类的定义
 *
 * 该文件定义了 `ImageCropperLabel` 类，用于在 GUI 中进行图片裁剪操作。
 * 提供了多种裁剪形状、尺寸调整以及透明效果等功能。
 *
 * @version 1.0
 * @date 2025/1/26
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QLabel>
#include <QPen>
#include <QPixmap>

/**
 * @brief 裁剪器的形状枚举
 */
enum class CropperShape {
  UNDEFINED,    ///< 未定义
  RECT,         ///< 矩形
  SQUARE,       ///< 正方形
  FIXED_RECT,   ///< 固定尺寸的矩形
  CIRCLE,       ///< 圆形
  ELLIPSE,      ///< 椭圆
  FIXED_ELLIPSE ///< 固定尺寸的椭圆
};

/**
 * @brief 裁剪后图像的输出形状枚举
 */
enum class OutputShape {
  RECT,   ///< 矩形输出
  ELLIPSE ///< 椭圆输出
};

/**
 * @brief 裁剪器尺寸类型枚举
 */
enum class SizeType {
  fixedSize,          ///< 固定尺寸
  fitToMaxWidth,      ///< 适应最大宽度
  fitToMaxHeight,     ///< 适应最大高度
  fitToMaxWidthHeight ///< 同时适应最大宽度和高度
};

class ImageCropperLabel final : public QLabel {
  Q_OBJECT

public:
  /**
   * @brief 构造函数
   * @param parent 父组件指针
   */
  explicit ImageCropperLabel(QWidget* parent);

  void setCropperLabel(int width, int height);

  /**
   * @brief 设置原始图像
   * @param pixmap 原始图像
   */
  void setOriginalImage(const QPixmap& pixmap);

  /**
   * @brief 设置裁剪后图像的输出形状
   * @param shape 输出形状
   */
  void setOutputShape(const OutputShape shape) { outputShape = shape; }

  /**
   * @brief 获取裁剪后的图像
   * @return 裁剪后的图像
   */
  QPixmap getCroppedImage() const;

  /**
   * @brief 根据指定输出形状获取裁剪后的图像
   * @param shape 输出形状
   * @return 裁剪后的图像
   */
  QPixmap getCroppedImage(OutputShape shape) const;

  /**
   * @brief 设置裁剪器为矩形形状
   */
  void setRectCropper();

  /**
   * @brief 设置裁剪器为正方形形状
   */
  void setSquareCropper();

  /**
   * @brief 设置裁剪器为椭圆形状
   */
  void setEllipseCropper();

  /**
   * @brief 设置裁剪器为圆形
   */
  void setCircleCropper();

  /**
   * @brief 设置裁剪器为固定尺寸的矩形
   * @param size 固定尺寸
   */
  void setFixedRectCropper(QSize size);

  /**
   * @brief 设置裁剪器为固定尺寸的椭圆
   * @param size 固定尺寸
   */
  void setFixedEllipseCropper(QSize size);

  /**
   * @brief 设置裁剪器的形状和尺寸
   * @param shape 裁剪器形状
   * @param size  裁剪器尺寸
   * @note 不推荐使用该方法，请使用更具体的方法设置裁剪器形状。
   */
  void setCropper(CropperShape shape, QSize size);

  /**
   * @brief 设置裁剪器的固定尺寸
   * @param fixedWidth  固定宽度
   * @param fixedHeight 固定高度
   */
  void setCropperFixedSize(int fixedWidth, int fixedHeight);

  /**
   * @brief 设置裁剪器的固定宽度
   * @param fixedWidth 固定宽度
   */
  void setCropperFixedWidth(int fixedWidth);

  /**
   * @brief 设置裁剪器的固定高度
   * @param fixedHeight 固定高度
   */
  void setCropperFixedHeight(int fixedHeight);

  /**
   * @brief 设置裁剪器的最小尺寸
   * @param minWidth  最小宽度
   * @param minHeight 最小高度
   */
  void setCropperMinimumSize(const int minWidth, const int minHeight)
  {
    cropperMinimumWidth = minWidth;
    cropperMinimumHeight = minHeight;
  }

  /**
   * @brief 设置裁剪器的最小宽度
   * @param minWidth 最小宽度
   */
  void setCropperMinimumWidth(const int minWidth)
  {
    cropperMinimumWidth = minWidth;
  }

  /**
   * @brief 设置裁剪器的最小高度
   * @param minHeight 最小高度
   */
  void setCropperMinimumHeight(const int minHeight)
  {
    cropperMinimumHeight = minHeight;
  }

  /**
   * @brief 设置是否显示矩形边框
   * @param show 是否显示
   */
  void setShowRectBorder(const bool show) { isShowRectBorder = show; }

  /**
   * @brief 获取当前矩形边框的画笔
   * @return 矩形边框的画笔
   */
  QPen getBorderPen() { return borderPen; }

  /**
   * @brief 设置矩形边框的画笔
   * @param pen 矩形边框的画笔
   */
  void setBorderPen(const QPen& pen) { borderPen = pen; }

  /**
   * @brief 设置是否显示拖动方块
   * @param show 是否显示
   */
  void setShowDragSquare(const bool show) { isShowDragSquare = show; }

  /**
   * @brief 设置拖动方块的边长
   * @param edge 方块边长
   */
  void setDragSquareEdge(const int edge)
  {
    dragSquareEdge = (edge >= 3 ? edge : 3);
  }

  /**
   * @brief 设置拖动方块的颜色
   * @param color 方块颜色
   */
  void setDragSquareColor(const QColor& color) { dragSquareColor = color; }

  /**
   * @brief 启用或禁用透明效果
   * @param enable 是否启用透明效果
   */
  void enableOpacity(const bool enable = true) { isShowOpacityEffect = enable; }

  /**
   * @brief 设置透明效果的透明度
   * @param newOpacity 新的透明度值（范围：0.0 ~ 1.0）
   */
  void setOpacity(const double newOpacity) { opacity = newOpacity; }

signals:
  /**
   * @brief 当裁剪的图像发生变化时发出此信号
   */
  void croppedImageChanged();

protected:
  void paintEvent(QPaintEvent* event) override;
  void mousePressEvent(QMouseEvent* e) override;
  void mouseMoveEvent(QMouseEvent* e) override;
  void mouseReleaseEvent(QMouseEvent* e) override;

private:
  void drawFillRect(QPoint centralPoint, int edge, QColor color);
  void drawRectOpacity();
  void drawEllipseOpacity();
  void drawOpacity(const QPainterPath& path);
  void drawSquareEdge(bool onlyFourCorners);

  int getPosInCropperRect(const QPoint& pt);
  bool isPosNearDragSquare(const QPoint& pt1, const QPoint& pt2);
  void resetCropperPos();
  void changeCursor();

  enum {
    RECT_OUTSIZD = 0,
    RECT_INSIDE  = 1,
    RECT_TOP_LEFT, RECT_TOP, RECT_TOP_RIGHT, RECT_RIGHT,
    RECT_BOTTOM_RIGHT, RECT_BOTTOM, RECT_BOTTOM_LEFT, RECT_LEFT
  };

  const bool ONLY_FOUR_CORNERS = true;

  QPixmap originalImage;
  QPixmap tempImage;

  bool isShowRectBorder = true;
  QPen borderPen;

  CropperShape cropperShape = CropperShape::UNDEFINED;
  OutputShape outputShape = OutputShape::RECT;

  QRect imageRect;
  QRect cropperRect;
  QRect cropperRect_;
  double scaledRate = 1.0;

  bool isLButtonPressed = false;
  bool isCursorPosCalculated = false;
  int cursorPosInCropperRect = RECT_OUTSIZD;
  QPoint lastPos;
  QPoint currPos;

  bool isShowDragSquare = true;
  int dragSquareEdge = 8;
  QColor dragSquareColor = Qt::white;

  int cropperMinimumWidth = dragSquareEdge * 2;
  int cropperMinimumHeight = dragSquareEdge * 2;

  bool isShowOpacityEffect = false;
  double opacity = 0.6;
};
