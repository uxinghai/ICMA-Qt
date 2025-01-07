/**
 * @file closeWindowMsgBox.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/1/7 14:17
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QRadioButton>

class CloseWindowMsgBox final : public QDialog {
  Q_OBJECT

public:
  explicit CloseWindowMsgBox(QWidget* parent = nullptr)
    : QDialog(parent), checkBox(nullptr), radioMinWindow(nullptr),
      radioDirectClose(nullptr), cancelButton(nullptr), okButton(nullptr)
  {
    this->setFixedSize(563, 156);
    const QRect parentGeometry = parentWidget()->geometry();
    // 计算窗口位置,使其水平居中显示
    const int x = parentGeometry.x() +
      (parentGeometry.width() - this->width()) / 2;
    const int y = parentGeometry.y() + 20; ///< 距离顶部20像素
    this->move(x, y);
    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // 创建美观布局
    init();
  }

  ~CloseWindowMsgBox() override = default;

  bool isCloseNoRequireChecked = false;

protected:
  // 禁用 ESC 按钮
  void keyPressEvent(QKeyEvent* event) override
  {
    if (event->key() == Qt::Key_Escape) { event->ignore(); }
    else { QDialog::keyPressEvent(event); }
  }

private:
  void init()
  {
    // 创建主垂直布局
    auto* mainLayout = new QVBoxLayout(this);

    auto* messageLabel = new QLabel(tr("您点击了关闭按钮，您想要："), this);
    QFont font = messageLabel->font();
    font.setPointSize(11);
    messageLabel->setFont(font);
    mainLayout->addWidget(messageLabel);

    // 添加单选按钮组
    auto* radioGroup = new QVBoxLayout();
    radioMinWindow = new QRadioButton(tr("最小化到托盘"), this);
    radioDirectClose = new QRadioButton(tr("退出"), this);
    radioMinWindow->setChecked(true);
    radioGroup->setSpacing(5);
    radioGroup->addWidget(radioMinWindow);
    radioGroup->addWidget(radioDirectClose);
    radioGroup->setContentsMargins(20, 0, 20, 0);
    mainLayout->addLayout(radioGroup);

    auto* subWidget = new QWidget();
    subWidget->setContentsMargins(0, 0, 0, 0);

    // 创建水平布局来包含复选框和按钮
    auto* hLayout = new QHBoxLayout(subWidget);
    hLayout->setSpacing(10); // 设置按钮和复选框之间的间距

    // 添加复选框
    checkBox = new QCheckBox(tr("不再提示"), subWidget);
    checkBox->setContentsMargins(20, 0, 20, 0);

    // 添加按钮
    cancelButton = new QPushButton(tr("取消"), subWidget);
    okButton = new QPushButton(tr("确定"), subWidget);

    // 将复选框和按钮添加到水平布局中
    hLayout->addWidget(checkBox);
    hLayout->addStretch(); // 在复选框和按钮之间添加弹簧来推按钮到右侧
    hLayout->addWidget(cancelButton);
    hLayout->addWidget(okButton);

    // 设置按钮的最小宽度和统一的样式
    okButton->setMinimumWidth(80);
    cancelButton->setMinimumWidth(80);
    // 将子窗口添加到主布局
    mainLayout->addWidget(subWidget);
  }

  QCheckBox* checkBox;
  QRadioButton* radioMinWindow;
  QRadioButton* radioDirectClose;
  QPushButton* cancelButton;
  QPushButton* okButton;
};
