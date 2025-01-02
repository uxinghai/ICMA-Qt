// /**
//  * @file MainWindow.h
//  * @brief 主程序窗口的头文件
//  *
//  * 该文件定义了 `MainWindow` 类，为程序的主窗口，提供用户界面和主要功能入口。
//  * 包括文件管理、界面语言切换、文件传输、图像处理、和系统自启动设置等功能。
//  *
//  * @version 0.1
//  * @date 2024.07.30
//  *
//  * @note 使用 `QMainWindow` 作为基础类，提供信号槽机制和菜单操作的实现。
//  *
//  * @author uxinghai
//  * @copyright Copyright (c) 2024
//  */
//
// #ifndef MAINWINDOW_H
// #define MAINWINDOW_H
//
// #include <QLabel>
// #include <QMainWindow>
// #include <QMenu>
// #include <QProgressBar>
// #include <QSettings>
// #include <QTableView>
//
// /**
//  * @enum FileActionType
//  * @brief 文件操作类型的枚举，标识文件的行为类型
//  */
// enum class FileActionType {
//   Open   = 0, ///< 打开文件
//   Edit   = 1, ///< 编辑文件
//   Delete = 2  ///< 删除文件
// };
//
// QT_BEGIN_NAMESPACE
//
// namespace Ui
// {
//   class MainWindow;
// }
//
// QT_END_NAMESPACE
//
// class MainWindow final : public QMainWindow {
//   Q_OBJECT
//
// public:
//   explicit MainWindow(QWidget* parent = nullptr);
//
//   ~MainWindow() override;
//
//   Ui::MainWindow* ui;
//
//   /**
//    * @brief 初始化主窗口
//    */
//   void init();
//
// protected:
//   /**
//    * @brief 重写关闭事件，用于窗口关闭时的处理
//    * @param event 关闭事件指针
//    */
//   void closeEvent(QCloseEvent* event) override;
//
//   /**
//    * @brief 重写键盘按下事件，用于快捷键处理
//    * @param event 键盘事件指针
//    */
//   void keyPressEvent(QKeyEvent* event) override;
//
// private slots:
//   /**
//    * @brief 创建新窗口的槽函数
//    */
//   void on_actionnewWindow_triggered();
//
//   /**
//    * @brief 退出程序的槽函数
//    */
//   void on_actiontuichu_triggered();
//
//   /**
//    * @brief 搜索输入框编辑的槽函数
//    * @param text 用户输入的文本
//    */
//   static void on_lineEdit_textEdited(const QString& text);
//
//   /**
//    * @brief 过滤器显示切换的槽函数
//    * @param checked 是否启用过滤器
//    */
//   void on_actionfilter_triggered(bool checked) const;
//
//   /**
//    * @brief 预览显示切换的槽函数
//    * @param checked 是否启用预览
//    */
//   void on_actionpreview_triggered(bool checked) const;
//
//   /**
//    * @brief 状态栏显示切换的槽函数
//    * @param checked 是否显示状态栏
//    */
//   void on_actionstatusbar_triggered(bool checked) const;
//
//   /**
//    * @brief 导入文件的槽函数
//    */
//   void on_actiondaori_triggered();
//
//   /**
//    * @brief 设置程序是否开机自启动的槽函数
//    * @param checked 是否自启动
//    */
//   void on_actionautoRun_triggered(bool checked);
//
//   /**
//    * @brief 重译界面，用于语言切换
//    * @param lang 语言代码
//    * @param path 语言文件路径
//    */
//   void retranslate(const QString& lang, const QString& path);
//
//   /**
//    * @brief 切换界面至中文
//    */
//   void on_actionCN_triggered();
//
//   /**
//    * @brief 切换界面至英文
//    */
//   void on_actionEN_triggered();
//
//   /**
//    * @brief 切换界面至日文
//    */
//   void on_actionJP_triggered();
//
//   /**
//    * @brief 显示关于信息的槽函数
//    */
//   void on_actionabout_triggered();
//
//   /**
//    * @brief 打开文件传输助手
//    */
//   void on_actiontransmission_triggered();
//
//   /**
//    * @brief 打开简易图像处理工具
//    */
//   void on_actionPS_triggered();
//
// private:
//   /**
//    * @brief 在视图上显示进度条
//    * @param progress 进度条指针
//    */
//   void displayOnView(QProgressBar* progress);
//
//   /**
//    * @brief 显示右键菜单
//    * @param globalPos 鼠标点击的全局坐标
//    */
//   void showWindowsContextMenu(const QPoint& globalPos);
//
//   /**
//    * @brief 设置系统自启动功能
//    * @param isAutoRun 是否启用自启动
//    * @param ApplicationName 应用程序名称
//    * @param ApplicationPath 应用程序路径
//    */
//   static void autoRunSystem(bool isAutoRun, const QString& ApplicationName,
//                             const QString& ApplicationPath)
//   {
//     QSettings regedit(R"(HKEY_CURRENT_USER\Software\
//                             Microsoft\Windows\CurrentVersion\Run)",
//                       QSettings::NativeFormat);
//     if (isAutoRun) {
//       regedit.setValue(ApplicationName, ApplicationPath);
//     } else { regedit.remove(ApplicationName); }
//   }
//
//   QLabel* lbStatus{}; ///< 状态栏显示的标签
//   QString filePath;   ///< 保存文件路径，用于 Windows 右键菜单操作时动态更新
// };
//
// #endif // MAINWINDOW_H
