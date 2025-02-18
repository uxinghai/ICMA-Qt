/**
 * @file ShareSrc.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/2/5
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QObject>
#include <QString>

inline QString getCommonHelpContent()
{
  return QObject::tr(
    "<p>欢迎使用本文件传输工具。以下是基本使用步骤：</p>"
    "<p>状态栏会显示当前的连接状态、传输模式。</p>"
    "<p>如果遇到任何问题，请检查网络连接或联系技术支持。</p>"
    "<p>致信开发者：uxinghaiwyi@163.com</p>");
}

inline QString getSenderHelpContent()
{
  return QObject::tr(
    "<h2>文件传输工具（发送方）使用说明</h2>"
    "<ol>"
    "<li><b>添加文件：</b> 点击工具栏的'添加文件'选项来选择要传输的文件。</li>"
    "<li><b>设置接收方IP：</b> 在工具栏的输入框中输入接收方的IP地址。</li>"
    "<li><b>连接：</b> 点击'连接'按钮与接收方建立连接。</li>"
    "<li><b>发送文件：</b> 连接成功后，点击'发送'按钮开始传输文件。</li>"
    "</ol>"
    "<h3>其他功能：</h3>"
    "<ul>"
    "<li><b>移除文件：</b> 右键点击文件列表中的文件，选择'移除'选项。</li>"
    "<li><b>清空列表：</b> 使用右键菜单中的'清空列表'选项可以清除所有待传输文件。</li>"
    "<li><b>断开连接：</b> 传输完成后，可以点击'断开连接'按钮终止与接收方的连接。</li>"
    "</ul>"
    "<p>状态栏会显示当前的连接状态、待传输文件数量和传输模式。</p>");
}

inline QString getReceiverHelpContent()
{
  return QObject::tr(
    "<h2>文件传输工具（接收方）使用说明</h2>"
    "<ol>"
    "<li><b>开始监听：</b> 点击工具栏的'开始监听'按钮来等待发送方的连接。</li>"
    "<li><b>设置保存路径：</b> 点击'设置保存路径'按钮选择接收文件的保存位置。</li>"
    "<li><b>接收文件：</b> 连接建立后，文件将自动开始接收。</li>"
    "</ol>"
    "<h3>其他功能：</h3>"
    "<ul>"
    "<li><b>查看IP地址：</b> 您的IP地址显示在工具栏上，可以提供给发送方。</li>"
    "<li><b>断开连接：</b> 点击'断开连接'按钮可以停止监听或断开当前连接。</li>"
    "<li><b>文件列表：</b> 接收的文件会显示在主窗口的列表中。</li>"
    "</ul>"
    "<p>状态栏会显示当前的连接状态、保存路径和传输模式。</p>"
    "<p>传输进度、当前文件名、文件大小、传输速度和剩余时间会在主窗口中实时更新。</p>");
}

inline QString getHelpContext(const bool isSender)
{
  const QString commonPart = getCommonHelpContent();
  if (isSender) { return getSenderHelpContent() + commonPart; }
  return getReceiverHelpContent() + commonPart;
}

// 辅助函数：用于把所有待传输文件显示在界面列表上
inline void addItemsToView(QListWidget* listWidget,
                           const QSet<QString>& filePaths)
{
  listWidget->clear();
  // 设置图标
  for (auto it = filePaths.constBegin(); it != filePaths.constEnd(); ++it) {
    QFileInfo info(*it);
    QString suffix = info.suffix().toLower();
    QString iconPath = ":/suffixes/res/suffix/" + suffix + ".png";
    listWidget->addItem(
      new QListWidgetItem(QIcon(iconPath), info.fileName()));
  }
}

inline void updateProgress(const qint64 curBytes, const qint64 allBytes,
                           const QString& fileName, const qint64 startTime,
                           const bool isSender,
                           QVector<QLabel*> labels)
{
  const auto [speed, remainingTime, curUnit, totalUnit, curDisplay,
    totalDisplay] = FileTransTool::calculateStats(
    curBytes, allBytes, startTime);
  if (isSender) { labels[0]->setText(QObject::tr("正在传输...")); }
  else { labels[0]->setText(QObject::tr("正在接收...")); }
  labels[1]->setText(fileName);
  labels[2]->setText(QString("%1 %2 / %3 %4")
                     .arg(curDisplay)
                     .arg(curUnit)
                     .arg(totalDisplay)
                     .arg(totalUnit));
  labels[3]->setText(QString("%1 KB/s").arg(speed));
  labels[4]->setText(QObject::tr("%1 秒").arg(remainingTime));
}
