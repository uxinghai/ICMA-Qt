/**
 * @file IconTextDelegate.h
 *
 * @Breife 自定义委托类，为第 0 列的项绘制图标 + 文本
 *
 * @version 1.0
 * @date 2025/2/19
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QPainter>
#include <QStyledItemDelegate>

class IconTextDelegate final : public QStyledItemDelegate {
public:
  explicit IconTextDelegate(QObject* parent = nullptr)
    : QStyledItemDelegate(parent) {}

  /**
   * @brief 重写paint函数，自定义绘制项目，该绘制方式只应用于第0列
   * @param painter 用于执行实际绘制操作的QPainter指针
   * @param option 包含绘制项目所需的样式选项信息
   * @param index 当前要绘制的项目的模型索引
   */
  void paint(QPainter* painter, const QStyleOptionViewItem& option,
             const QModelIndex& index) const override
  {
    if (index.column() == 0) {
      painter->save(); ///< 保存画笔当前状态，后续恢复。即在这个函数中不修改画笔

      const QString text = index.data(Qt::DisplayRole).toString(); ///< 获取显示文本
      // 从第8列获取图标路径
      const QString iconPath = index.sibling(index.row(), 8).data().toString();
      const QIcon icon(iconPath); ///< 创建图标对象

      // 计算图标区域
      QRect iconRect = option.rect;
      iconRect.setWidth(20);
      iconRect.setHeight(20);
      iconRect.moveLeft(option.rect.left() + 5); ///< 左边留5像素边距

      // 计算文本区域
      QRect textRect = option.rect;
      textRect.setLeft(iconRect.right() + 5); ///< 文本区域从图标右侧开始，间隔5像素

      icon.paint(painter, iconRect);                       ///< 绘制图标
      painter->drawText(textRect, Qt::AlignVCenter, text); ///< 绘制文本，垂直居中对齐

      painter->restore(); ///< 恢复画笔到上次保存的状态
    }
    else {
      // 其他列默认绘制
      QStyledItemDelegate::paint(painter, option, index);
    }
  }
};
