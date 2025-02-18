/**
 * @file PS.h
 *
 * @brief 图像处理模块头文件
 *
 * 该文件定义了图像处理模块中的主要类和相关功能。
 * 模块主要负责处理图像的各种操作，包括打开、保存、调整大小、旋转、裁剪、应用滤镜等功能。
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

class PS;
QT_END_NAMESPACE

/**
 * @brief 图像处理模块类
 *
 * 该类是图像处理模块的核心实现，继承自QWidget，负责处理图像的加载、显示、编辑、保存以及历史记录管理等功能。
 */
inline MyAutoStack historyPixmap; ///< 用于存储图像处理的历史记录

// static 即使在析构函数中使 psInstance为nullptr但全局的值不会改变
inline PS* psInstance = nullptr;

class PS final : public QWidget {
  Q_OBJECT

public:
  /**
   * @brief 获取唯一实例
   * @return PS的静态引用
   */
  static PS* getInstance()
  {
    // 如果窗口没有被构建则构建并让窗口正常显示
    if (psInstance == nullptr) { psInstance = new PS(); }
    if (psInstance->isHidden()) { psInstance->show(); }
    if (psInstance->isMinimized()) { psInstance->showNormal(); }
    psInstance->raise();
    return psInstance;
  }

  // 禁用一切构造方法，以免意外构建
  explicit PS(PS* ps) = delete;
  PS(const PS&) = delete;
  PS& operator=(const PS&) = delete;
  PS(PS&&) = delete;
  PS& operator=(PS&&) = delete;

  /**
   * @brief 析构函数
   *
   * 清理资源，关闭窗口时销毁图像处理模块。
   */
  ~PS() override;

signals:
  /**
   * @brief 窗口关闭信号
   *
   * 当窗口关闭时触发。
   */
  void WindowClose();

protected:
  /**
   * @brief 拖拽事件处理
   *
   * 处理拖拽进入事件，用于加载图像。
   *
   * @param event 拖拽进入事件对象
   */
  void dragEnterEvent(QDragEnterEvent* event) override;

  /**
   * @brief 放下事件处理
   *
   * 处理拖拽放下事件，用于加载图像。
   *
   * @param event 放下事件对象
   */
  void dropEvent(QDropEvent* event) override;

  /**
   * @brief 关闭事件处理
   *
   * 处理窗口关闭事件，执行资源清理操作。
   *
   * @param event 关闭事件对象
   */
  void closeEvent(QCloseEvent* event) override;

private slots:
  /**
   * @brief 打开图像
   *
   * 打开本地存储的图像文件并加载到界面中。
   */
  void doImageOpen();

  /**
   * @brief 显示图像到界面
   *
   * 将图像显示到UI界面上。
   *
   * @param showPixmap 要显示的图像及其相关信息
   * @param noUpdateUi 不更新UI界面的标记
   */
  void showImgToUi(const QPair<cv::Mat, MatInfo>& showPixmap,
                   const bool& noUpdateUi = false);

  /**
   * @brief 撤销操作
   *
   * 撤销上一步的图像处理操作。
   */
  void doUndo();

  /**
   * @brief 重置图像
   *
   * 重置图像为初始状态。
   */
  void doReset();

  /**
   * @brief 改变图像大小
   *
   * 修改图像大小并更新显示。
   */
  void doSizeChange();

  /**
   * @brief 显示人脸检测结果
   *
   * 测试并显示图像中的人脸检测结果。
   */
  static void doShowFaceTest();

  /**
   * @brief 保存图像
   *
   * 保存当前图像到本地文件系统。
   *
   * @param isSaveAs 是否为另存为操作
   */
  void doImageSave(bool isSaveAs);

  /**
   * @brief 工具栏切换事件处理
   *
   * 当工具栏选择项发生变化时触发，进行相应的图像处理。
   *
   * @param index 选择的工具栏项索引
   */
  void doToolBoxChanged(int index);

  /**
   * @brief 裁剪框变化事件
   *
   * 当裁剪框的行发生变化时触发，更新裁剪区域。
   *
   * @param row 当前裁剪框的行索引
   */
  void doCropChange(int row);

  /**
   * @brief 尺寸变化事件
   *
   * 当图像尺寸调整时触发，更新图像的尺寸信息。
   *
   * @param row 当前尺寸的行索引
   */
  void doResizeChange(int row);

  /**
   * @brief 图像调整事件
   *
   * 对图像进行色调、对比度等调整。
   */
  void doAdjust();

private:
  /**
   * @brief 构造函数
   *
   * 初始化图像处理模块界面。
   *
   * @param parent 父控件
   */
  explicit PS(QWidget* parent = nullptr);

  /**
   * @brief 初始化界面
   *
   * 执行UI界面的初始化设置。
   */
  void init() const;

  /**
   * @brief 设置信号与槽的连接
   *
   * 为界面元素设置信号和槽的连接。
   */
  void setupConnections();

  /**
   * @brief 设置滑动条与数字框的连接
   *
   * 为滑动条和数字框设置同步连接，使得它们的值保持一致。
   *
   * @param slider 滑动条控件
   * @param spinBox 数字框控件
   * @param valueUpdateFunc 更新值的函数
   * @param sliderDivisor 滑动条的除数，用于调整值的缩放
   * @param spinBoxMultiplier 数字框的乘数，用于调整值的缩放
   */
  void setupSliderConnections(const NoWheelSlider* slider,
                              QDoubleSpinBox* spinBox,
                              const std::function<void(int)>& valueUpdateFunc,
                              double sliderDivisor = 1.0,
                              double spinBoxMultiplier = 1.0);

  /**
   * @brief 设置旋转工具的连接
   *
   * 设置旋转功能的信号与槽的连接。
   */
  void setupRotationConnections();

  /**
   * @brief 应用模糊算法
   *
   * 根据选中的模糊算法按钮应用不同的模糊效果。
   *
   * @param radioButtonName 模糊算法的按钮名称
   * @param blurFunc 应用的模糊算法函数
   */
  void applyBlurAlgorithm(const QString& radioButtonName,
                          const std::function<void(
                            const cv::Mat&, cv::Mat&, int)>& blurFunc);

  /**
   * @brief 设置模糊算法相关的连接
   *
   * 设置模糊算法相关功能的信号与槽的连接。
   */
  void setupBlurAlgorithmConnections();

  /**
   * @brief 更新图像与UI
   *
   * 更新图像数据并同步更新UI界面显示。
   */
  void updateMatAndUI();

  /**
   * @brief 更新UI界面的状态
   *
   * 启用或禁用UI界面的各个控件。
   *
   * @param enable 是否启用界面控件
   */
  void updateUIState(bool enable) const;

  /**
   * @brief 显示图像尺寸
   *
   * 在界面上显示当前图像的尺寸信息。
   *
   * @param showPixmap 要显示的图像
   */
  void showImgSize(const QPixmap& showPixmap) const;

  /**
   * @brief 将图像添加到历史记录
   *
   * 将当前图像及其相关信息保存到历史记录中。
   *
   * @param pixmap 当前图像及其信息
   */
  static void pushToHistory(const QPair<cv::Mat, MatInfo>& pixmap);

  /**
   * @brief 更新UI界面信息
   *
   * 根据MatInfo更新界面上的信息。
   *
   * @param matInfo 图像的相关信息
   */
  void updateUIFromInfo(const MatInfo& matInfo);

  /**
   * @brief 显示信息消息框
   *
   * 显示操作成功或失败的信息提示。
   *
   * @param message 要显示的消息内容
   * @param isSuccess 是否操作成功
   */
  void showInformationMessage(const QString& message, bool isSuccess);

  /**
   * @brief 设置滤镜工具的连接
   *
   * 设置滤镜相关功能的信号与槽的连接。
   */
  void setupFilterConnections();

  Ui::PS* ui;                     ///< UI界面指针
  QGraphicsScene* scene;          ///< 图像显示场景
  QString pixFilePath;            ///< 当前图像的文件路径
  QPair<cv::Mat, MatInfo> srcMat; ///< 原始图像及其信息
  QPair<cv::Mat, MatInfo> curMat; ///< 当前处理图像及其信息

  // 以下两个成员变量在程序中共享，用于统一管理图像数据
  cv::Mat processedMat;              ///< 图像处理后的数据
  MatInfo curMatInfo;                ///< 当前图像的相关信息
  bool isProgrammaticChange = false; ///< 标记某些信号是由程序触发的
};
