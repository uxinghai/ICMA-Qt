/**
* @file FileTransfer.h
 * @brief 文件传输助手界面的头文件
 *
 * 该头文件定义了 `FileTrans` 类，用于程序中的文件传输助手界面。
 * 提供用户选择是否作为服务器或客户端启动的功能，并启动相应的传输模式。
 *
 * @version 0.2
 * @date 2024.11.1
 *
 * @author uxinghai
 * @copyright Copyright (c) 2024
 */
#pragma once

#include <QWidget>

class AServer;
class AClient;

namespace Ui
{
  class FileTrans;
}

class FileTrans final : public QWidget {
  Q_OBJECT

public:
  explicit FileTrans(QWidget* parent = nullptr);
  ~FileTrans() override;

signals:
  void WindowClose();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void doOpenSender();
  void doOpenReceiver();

private:
  void setupConnections();

  Ui::FileTrans* ui;
  QSharedPointer<AServer> aServer; // 管理服务器实例的智能指针
  QSharedPointer<AClient> aClient; // 管理客户端实例的智能指针
};
