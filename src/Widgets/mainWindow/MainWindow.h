/**
 * @file MainWindow.h
 *
 * @brief 主程序窗口的头文件
 *
 * 该文件定义了 `MainWindow` 类，为程序的主窗口，提供用户界面和主要功能入口。
 * 包括文件管理、界面语言切换、文件传输、图像处理、和系统自启动设置等功能。
 *
 * @version 0.1
 * @date 2024.07.30
 *
 * @author uxinghai
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QProgressBar>
#include <QSettings>

QT_BEGIN_NAMESPACE
class SystemTrayIcon;

namespace Ui
{
  class MainWindow;
}

QT_END_NAMESPACE

class MainWindow final : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow() override;

public slots:
  /**
   * @brief 初始化主窗口
  */
  void doInit();

protected:
  /**
   * @brief 重写关闭事件，用于窗口关闭时的处理
   * @param event 关闭事件指针
   */
  void closeEvent(QCloseEvent* event) override;

  /**
   * @brief 重写键盘按下事件，用于ESC快捷键处理
   * @param event 键盘事件指针
   */
  void keyPressEvent(QKeyEvent* event) override;

private slots:
  void doChangeTheme() const;
  void doSetActionVisible(const bool& checked) const;
  void doShowICMABrief();
  static void doEnableLogOut(const bool& checked);

private:
  void readIniConfig(); ///< 程序启动时读取文件配置界面
  // 程序退出时读取界面写入文件，两个必要的信息通过参数获取
  void savaIniConfig(const QString& closeMethod, bool noRequire) const;
  void setupConnections();

  /**
   * @brief 在视图上显示进度条
   * @param progress 进度条指针
   */
  void displayOnView(QProgressBar* progress);

  /**
   * @brief 设置系统自启动功能
   * @param isAutoRun 是否启用自启动
   * @param ApplicationName 应用程序名称
   * @param ApplicationPath 应用程序路径
   */
  static void autoRunSystem(const bool isAutoRun,
                            const QString& ApplicationName,
                            const QString& ApplicationPath)
  {
    QSettings regedit(R"(HKEY_CURRENT_USER\Software\
                            Microsoft\Windows\CurrentVersion\Run)",
                      QSettings::NativeFormat);
    if (isAutoRun) { regedit.setValue(ApplicationName, ApplicationPath); }
    else { regedit.remove(ApplicationName); }
  }

  Ui::MainWindow* ui;
  QLabel* lbStatus; ///< 状态栏显示的标签
  QString filePath; ///< 保存文件路径，用于 Windows 右键菜单操作时动态更新

  std::unique_ptr<SystemTrayIcon> icmaTrayIcon; ///< 系统托盘图标
};
