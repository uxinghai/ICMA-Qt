/**
 * @file MyTableView.h
 * @brief 自定义 QTableView 视图，提供列选择、悬停提示等功能。
 *
 * 该类继承自 QTableView，添加了鼠标悬停提示、右键菜单列管理、
 * 以及仅允许选择第一列的功能。
 *
 * @version 1.1
 * @date 2025/2/17
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QHeaderView>
#include <QMenu>
#include <QMouseEvent>
#include <QTableView>
#include <QTimer>
#include <QWidget>

#include "../../Manager/Config/iniManager.h"

class MyTableView final : public QTableView {
  Q_OBJECT

public:
  explicit MyTableView(QWidget* parent = nullptr) : QTableView(parent)
  {
    init();
    setupConnections();

    this->setMouseTracking(true);
    this->setToolTipDuration(-1); ///< -1表示提示将一直显示直到鼠标移开
  }

  /**
   * @brief 设置自定义选择模型，仅允许选择第一列
   * @param selectionModel 选择模型指针
   */
  void setTheSelectionModel(QItemSelectionModel* selectionModel)
  {
    selectModel = selectionModel;

    // 禁用除第0列外的所有列选择
    connect(selectModel, &QItemSelectionModel::selectionChanged,
            [this](const QItemSelection& selected,
                   const QItemSelection&) {
              for (const QModelIndex& index : selected.indexes()) {
                if (index.column() != 0) { selectModel->clear(); }
              }
            });
  }

  void initHeaderCustomMenu(QAction* fit, QAction* fitCol, QAction* name,
                            QAction* path, QAction* size, QAction* type,
                            QAction* creatDate, QAction* modifyDate,
                            QAction* lastReadDate, QAction* hash,
                            QAction* isEncrypt)
  {
    struct ColumnAction {
      QAction* action;     ///< 动作项
      int columnIndex;     ///< 所处列
      bool initialChecked; ///< 是否可复选
      bool initialEnabled; ///< 是否可用
    };

    // 使用结构体数组统一管理列动作
    const auto settings = iniManager::getIniSetting();
    const QVector<ColumnAction> columnActions = {
      {
        name, 0, settings.value("Settings/" + name->objectName()).toBool(),
        false
      },
      {
        path, 1, settings.value("Settings/" + path->objectName()).toBool(), true
      },
      {
        size, 2, settings.value("Settings/" + size->objectName()).toBool(),
        true
      },
      {
        type, 3, settings.value("Settings/" + type->objectName()).toBool(),
        true
      },
      {
        creatDate, 4,
        settings.value("Settings/" + creatDate->objectName()).toBool(), true
      },
      {
        modifyDate, 5,
        settings.value("Settings/" + modifyDate->objectName()).toBool(), true
      },
      {
        lastReadDate, 6,
        settings.value("Settings/" + lastReadDate->objectName()).toBool(), true
      },
      {
        hash, 7, settings.value("Settings/" + hash->objectName()).toBool(), true
      },
      {
        isEncrypt, 9,
        settings.value("Settings/" + isEncrypt->objectName()).toBool(), true
      }
    };

    // 初始化所有列动作的状态
    for (const auto& col : columnActions) {
      if (!col.initialChecked) { this->setColumnHidden(col.columnIndex, true); }
      col.action->setChecked(col.initialChecked);
      col.action->setEnabled(col.initialEnabled);

      // 统一处理列显示/隐藏的连接
      if (col.columnIndex > 0) { ///< 跳过 name 列
        connect(col.action, &QAction::triggered, [this, col] {
          this->setColumnHidden(col.columnIndex, !col.action->isChecked());
        });
      }
    }
    this->setColumnHidden(8, true); ///< 图标路径永久隐藏

    // 表头右键菜单
    connect(this->horizontalHeader(), &QHeaderView::customContextMenuRequested,
            [this, fit, fitCol, columnActions] { ///< columnActions不能引用捕获
              const auto menu = std::make_unique<QMenu>();

              // 添加自适应选项
              menu->addAction(fit);
              menu->addAction(fitCol);
              menu->addSeparator();

              // 添加列显示选项
              for (const auto& [action, columnIndex,
                     initialChecked, initialEnabled] : columnActions) {
                menu->addAction(action);
              }

              menu->exec(QCursor::pos());
            });

    // 统一处理自适应功能
    auto handleResizeMode = [this](const QHeaderView::ResizeMode mode) {
      const auto header = this->horizontalHeader();

      // 先应用调整模式
      header->setSectionResizeMode(mode);

      // 保存调整后的列宽
      const int columnCount = header->count();
      QVector<int> columnWidths;
      columnWidths.reserve(columnCount);

      for (int i = 0; i < columnCount; ++i) {
        columnWidths.append(header->sectionSize(i));
      }

      // 恢复为交互模式并应用保存的宽度
      header->setSectionResizeMode(QHeaderView::Interactive);

      for (int i = 0; i < columnCount; ++i) {
        header->resizeSection(i, columnWidths[i]);
      }
    };

    // 连接自适应动作
    connect(fit, &QAction::triggered, [handleResizeMode] {
      handleResizeMode(QHeaderView::ResizeToContents);
    });
    connect(fitCol, &QAction::triggered, [handleResizeMode] {
      handleResizeMode(QHeaderView::Stretch);
    });
  }

  ~MyTableView() override = default;

protected:
  /**
  * @brief 鼠标移动事件，控制悬停提示的显示
  * @param event 鼠标事件
  */
  void mouseMoveEvent(QMouseEvent* event) override
  {
    // 只在鼠标明显移动时显示
    if (const QModelIndex curIndex = indexAt(event->pos());
      curIndex != lastHoveredIndex) {
      hoverTimer->stop(); ///< 停止之前的计时
      setToolTip("");     ///< 清除现有提示

      lastHoveredIndex = curIndex;

      // 只有在有效的目标列时才启动定时器
      if (curIndex.isValid() &&
        (curIndex.column() == 0 || curIndex.column() == 1)) {
        hoverTimer->start(500);
      }
    }

    QTableView::mouseMoveEvent(event);
  }

private slots:
  /**
  * @brief 显示鼠标悬停提示
  */
  void showToolTip()
  {
    if (!lastHoveredIndex.isValid()) { return; }

    const int column = lastHoveredIndex.column();
    if (column != 0 && column != 1) { return; }

    // 获取需要显示的数据
    const QString name = model()->data(
      model()->index(lastHoveredIndex.row(), 0)).toString();
    const QString path = model()->data(
      model()->index(lastHoveredIndex.row(), 1)).toString();
    const QString size = model()->data(
      model()->index(lastHoveredIndex.row(), 2)).toString();
    const QString modTime = model()->data(
      model()->index(lastHoveredIndex.row(), 5)).toString();

    QString tipText;
    if (column == 1) { ///< 路径列只显示完整路径
      tipText = path;
    }
    else { ///< 名称列显示所有信息
      tipText = QString("名称: %1\n路径: %2\n大小: %3\n修改时间: %4")
                .arg(name)
                .arg(path)
                .arg(size)
                .arg(modTime);
    }

    if (toolTip() != tipText) { setToolTip(tipText); }
  }

private:
  /**
  * @brief 初始化界面
  */
  void init()
  {
    // 设置自定义右键菜单
    this->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setContextMenuPolicy(Qt::CustomContextMenu);

    // 创建单个定时器实例
    hoverTimer = new QTimer(this);
    hoverTimer->setSingleShot(true); ///< 设置为单次触发
  }

  /**
    * @brief 连接信号与槽
    */
  void setupConnections()
  {
    connect(hoverTimer, &QTimer::timeout, this, &MyTableView::showToolTip);
  }

  // 成员变量
  QTimer* hoverTimer = nullptr; ///< 悬停提示定时器
  QModelIndex lastHoveredIndex; ///< 记录上次鼠标悬停位置

  QItemSelectionModel* selectModel = nullptr; ///< 选择模型
};
