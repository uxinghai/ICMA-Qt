/**
 * @file SystemTrayIcon.h
 * @brief 一个通用的系统托盘图标实现类
 *
 * 该类提供了一个可定制的系统托盘图标实现，支持：
 * - 自定义托盘图标和提示文本
 * - 可配置的上下文菜单项
 * - 支持 QWidget 窗口类型
 * 为什么定义为QWidget类型的传入：是因为所有可视的窗口都来自于QWidget包括QMainWindow
 * - 双击托盘图标显示主窗口
 *
 * 可以在initializeActions中自定义的添加或删除修改动作以及可视性
 *
 * @version 1.0
 * @date 2025/01/09
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <memory>
#include <QCoreApplication>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QWidget>

class SystemTrayIcon final : public QObject {
  Q_OBJECT

public:
  /**
   * @brief 构造函数 - QWidget 版本
   * @param icon 托盘图标
   * @param widget 窗口指针
   * @param toolTip 鼠标悬停提示文本
   */
  explicit SystemTrayIcon(const QIcon& icon, QWidget* widget,
                          const QString& toolTip);

  /**
   * @brief 析构函数
   * @details 清理所有动态分配的资源
   */
  ~SystemTrayIcon() override;

private:
  /**
   * @brief 初始化所有动作
   * @details 创建并存储所有菜单动作
   */
  void initializeActions();

  /**
   * @brief 创建托盘的上下文菜单
   * @details 根据 actionMap 中的配置添加可见的菜单项
   */
  void createContextMenu();

  /**
   * @brief 设置连接 - QWidget 版本
   * @details 连接托盘图标的信号和槽函数
   */
  void setupConnections(QWidget* widget);

  QSystemTrayIcon* trayIcon;          ///< 托盘图标对象指针
  std::unique_ptr<QMenu> contextMenu; ///< 托盘菜单指针
  std::vector<QAction*> actions;      ///< 存储所有动作的容器
  QHash<QAction*, bool> actionMap;    ///< 动作可视性映射
};

//                        *********
//                         *******
//                          *****
//                           ***
//                            *
//                        方法实现
inline SystemTrayIcon::SystemTrayIcon(const QIcon& icon,
                                      QWidget* widget,
                                      const QString& toolTip = "")
  : trayIcon(new QSystemTrayIcon(icon, this))
    , contextMenu(std::make_unique<QMenu>())
{
  trayIcon->setToolTip(toolTip);
  initializeActions();
  createContextMenu();
  setupConnections(widget);
  trayIcon->setContextMenu(contextMenu.get());
  trayIcon->show();
}

inline void SystemTrayIcon::initializeActions()
{
  // 此处可以新增动作
  const auto mainWindow = new QAction(QObject::tr("主窗口"));
  const auto minimize = new QAction(QObject::tr("最小化"));
  const auto restore = new QAction(QObject::tr("还原"));
  const auto maximize = new QAction(QObject::tr("最大化"));
  const auto about = new QAction(QObject::tr("关于"));
  const auto update = new QAction(QObject::tr("检查更新"));
  const auto settings = new QAction(QObject::tr("设置"));
  const auto exit = new QAction(QObject::tr("退出"));

  // 此处设置动作可视化
  actionMap.insert(mainWindow, true);
  actionMap.insert(minimize, false);
  actionMap.insert(restore, false);
  actionMap.insert(maximize, false);
  actionMap.insert(about, true);
  actionMap.insert(update, true);
  actionMap.insert(settings, false);
  actionMap.insert(exit, true);

  // 转移所有权到 actions 容器 方便创建信号槽连接及清理
  // 动作如果可视化被设置为 false 后续不会加入到 Menu，也就是说不会被 Menu管理内存
  // 因此用一个容器保留它们，最后一起清理
  actions.push_back(mainWindow);
  actions.push_back(minimize);
  actions.push_back(restore);
  actions.push_back(maximize);
  actions.push_back(about);
  actions.push_back(update);
  actions.push_back(settings);
  actions.push_back(exit);
}

inline void SystemTrayIcon::createContextMenu()
{
  for (const auto& action : actions) {
    if (actionMap.value(action, false)) { contextMenu->addAction(action); }
  }
}

inline void SystemTrayIcon::setupConnections(QWidget* widget)
{
  // Widget 版本的连接实现，类似于 QMainWindow 版本
  connect(trayIcon, &QSystemTrayIcon::activated,
          [widget](const QSystemTrayIcon::ActivationReason reason) {
            switch (reason) {
            case QSystemTrayIcon::Trigger:
            case QSystemTrayIcon::DoubleClick: widget->show();
              break;
            default: break;
            }
          });

  // 为每个动作连接相应的槽函数
  for (const auto& action : actions) {
    if (action == actions[0]) { // mainWindowAction
      connect(action, &QAction::triggered,
              [widget]() { widget->show(); });
    }
    else if (action == actions[1]) { // minimizeAction
      connect(action, &QAction::triggered,
              [widget]() { widget->showMinimized(); });
    }
    else if (action == actions[2]) { // restoreAction
      connect(action, &QAction::triggered,
              [widget]() { widget->showNormal(); });
    }
    else if (action == actions[3]) { // maximizeAction
      connect(action, &QAction::triggered,
              [widget]() { widget->showMaximized(); });
    }
    // 以下两个方法需要根据系统不同而自定义(没有通用标准)
    // else if (action == actions[4]) { // aboutAction
    //   connect(action, &QAction::triggered,
    //           [widget]() { widget->showAboutDialog(); });
    // }
    // else if (action == actions[5]) { // updateAction
    //   connect(action, &QAction::triggered,
    //           [widget]() { widget->showUpdateDialog(); });
    // }
    // else if (action == actions[6]) { // settingsAction
    //   connect(action, &QAction::triggered,
    //           [widget]() { widget->showSettingsDialog(); });
    // }
    else if (action == actions[7]) { // exitAction
      connect(action, &QAction::triggered, []() { qApp->exit(); });
    }
  }
}

inline SystemTrayIcon::~SystemTrayIcon()
{
  for (const auto& action : actions) {
    // 测试是否被正确清理(退出系统时会正常清理)
    // qDebug() << "清理动作:" << action->text();
    // 测试完成
    delete action;
  }
}
