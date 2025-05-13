/**
 * @file SetupConnections.h
 *
 * @Breife 所有主界面的右键动作项信号槽连接
 *
 * @version 1.0
 * @date 2025/3/23
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QClipboard>
#include <QDesktopServices>
#include <QItemDelegate>
#include <QMessageBox>
#include <qprocess.h>
#include <QPushButton>
#include <QStandardPaths>
#include <qtextedit.h>

#include "../../UI/ui_MainWindow.h"
#include "../../UI/ui_Renamer.h"
#include "../DataBase/SqlQuery/FileActions.h"
#include "../DataBase/SqlQuery/Files.h"
#include "../Manager/JsonManager.h"
#include "../Network/UpdateChecker .h"
#include "../Utils/Tools/EncryptFile.h"
#include "../Utils/Tools/LogOut.h"
#include "../Utils/Tools/MyInformationBox.h"
#include "../Widgets/mainWindow/MainWindow.h"
#include "../Widgets/photoShop/PS.h"
#include "../Widgets/Renamer/Renamer.h"

class SetupConnections final : public QObject {
  Q_OBJECT;

public:
  /**
   * @brief 建立主界面 UI 信号
   * @param ui
   * @param widget 信号监听者
   * @return
   */
  static bool setupActionsConnection(Ui::MainWindow* ui, MainWindow* widget)
  {
    // 显示正则表达式语法帮助
    connect(ui->actionRegExp, &QAction::triggered, [ui,widget] {
      // 创建一个对话框
      const auto regexHelpDialog = new QDialog(widget);
      regexHelpDialog->setWindowTitle(tr("正则表达式语法"));
      regexHelpDialog->setMinimumSize(500, 600);

      // 创建布局
     const auto layout = new QVBoxLayout(regexHelpDialog);

      // 创建一个标签，用于显示标题
      const auto titleLabel = new QLabel(tr("<h2>正则表达式语法</h2>"), regexHelpDialog);
      titleLabel->setAlignment(Qt::AlignCenter);
      layout->addWidget(titleLabel);

      // 创建一个文本编辑器，用于显示内容
      const auto textEdit = new QTextEdit(regexHelpDialog);
      textEdit->setReadOnly(true);

      // 设置文本内容
      const QString helpText = tr(R"(
<h3>基本语法</h3>
<table border="0" cellspacing="5" cellpadding="5">
<tr><td><b>a|b</b></td><td>匹配 a 或 b</td></tr>
<tr><td><b>gr(a|e)y</b></td><td>匹配 gray 或 grey</td></tr>
<tr><td><b>.</b></td><td>匹配任一字符</td></tr>
<tr><td><b>[abc]</b></td><td>匹配任一字符: a 或 b 或 c</td></tr>
<tr><td><b>[^abc]</b></td><td>匹配任一字符, 但不包括 a, b, c</td></tr>
<tr><td><b>[a-z]</b></td><td>匹配从 a 到 z 之间的任一字符</td></tr>
<tr><td><b>[a-zA-Z]</b></td><td>匹配从 a 到 z, 及从 A 到 Z 之间的任一字符</td></tr>
<tr><td><b>^</b></td><td>匹配文件名的头部</td></tr>
<tr><td><b>$</b></td><td>匹配文件名的尾部</td></tr>
<tr><td><b>( )</b></td><td>匹配标记的子表达式</td></tr>
<tr><td><b>\n</b></td><td>匹配第 nth 个标记的子表达式, nth 代表 1 到 9</td></tr>
<tr><td><b>\b</b></td><td>匹配字词边界</td></tr>
<tr><td><b>*</b></td><td>匹配前一项内容 0 或多次</td></tr>
<tr><td><b>?</b></td><td>匹配前一项内容 0 或 1 次</td></tr>
<tr><td><b>+</b></td><td>匹配前一项内容 1 或多次</td></tr>
<tr><td><b>*?</b></td><td>匹配前一项内容 0 或多次 (懒人模式)</td></tr>
<tr><td><b>+?</b></td><td>匹配前一项内容 1 或多次 (懒人模式)</td></tr>
<tr><td><b>{x}</b></td><td>匹配前一项内容 x 次</td></tr>
<tr><td><b>{x,}</b></td><td>匹配前一项内容 x 或多次</td></tr>
<tr><td><b>{x,y}</b></td><td>匹配前一项内容次数介于 x 和 y 之间</td></tr>
<tr><td><b>\</b></td><td>特殊转义字符</td></tr>
</table>

<h3>使用示例</h3>
<table border="0" cellspacing="5" cellpadding="5">
<tr><th>正则表达式</th><th>说明</th><th>匹配示例</th></tr>
<tr>
    <td><code>file\d+</code></td>
    <td>匹配以"file"开头，后跟一个或多个数字的文件名</td>
    <td>file1, file42, file007</td>
</tr>
<tr>
    <td><code>^test</code></td>
    <td>匹配以"test"开头的文件名</td>
    <td>test.txt, testing.doc</td>
</tr>
<tr>
    <td><code>\.txt$</code></td>
    <td>匹配以".txt"结尾的文件名</td>
    <td>readme.txt, notes.txt</td>
</tr>
<tr>
    <td><code>(log|txt)$</code></td>
    <td>匹配以"log"或"txt"结尾的文件名</td>
    <td>error.log, readme.txt</td>
</tr>
<tr>
    <td><code>^[a-c].*\.doc$</code></td>
    <td>匹配以a、b或c开头，并以.doc结尾的文件名</td>
    <td>a-report.doc, business.doc</td>
</tr>
<tr>
    <td><code>report[0-9]{1,3}</code></td>
    <td>匹配"report"后跟1到3个数字的文件名</td>
    <td>report7, report42, report123</td>
</tr>
<tr>
    <td><code>back.?up</code></td>
    <td>匹配"back"和"up"之间有0或1个任意字符的文件名</td>
    <td>backup, back-up, back.up</td>
</tr>
<tr>
    <td><code>data\..+</code></td>
    <td>匹配以"data."开头，后跟一个或多个任意字符的文件名</td>
    <td>data.txt, data.csv, data.json</td>
</tr>
<tr>
    <td><code>\bword\b</code></td>
    <td>匹配完整单词"word"（在单词边界处）</td>
    <td>word, hello word bye（但不匹配"keyword"）</td>
</tr>
<tr>
    <td><code>img_(small|medium|large)</code></td>
    <td>匹配"img_"后跟"small"、"medium"或"large"的文件名</td>
    <td>img_small, img_medium, img_large</td>
</tr>
</table>

<h3>常用通配符</h3>
<p>在普通搜索模式下，系统也支持简单的通配符搜索：</p>
<ul>
    <li><b>*</b> - 匹配任意数量的任意字符（例如：<code>*.txt</code> 匹配所有以 .txt 结尾的文件）</li>
    <li><b>?</b> - 匹配任意单个字符（例如：<code>file?.txt</code> 匹配 file1.txt, fileA.txt 等）</li>
</ul>

<p><i>注意：要使用完整的正则表达式功能，请确保启用了"正则表达式"模式。</i></p>
)");

      textEdit->setHtml(helpText);
      layout->addWidget(textEdit);

      // 创建一个关闭按钮
      const auto closeButton = new QPushButton(tr("关闭"), regexHelpDialog);
      connect(closeButton, &QPushButton::clicked, regexHelpDialog, &QDialog::accept);

      // 创建一个水平布局，用于放置按钮
     const auto  buttonLayout = new QHBoxLayout();
      buttonLayout->addStretch();
      buttonLayout->addWidget(closeButton);
      layout->addLayout(buttonLayout);

      // 显示对话框，并在关闭后自动删除
      regexHelpDialog->setAttribute(Qt::WA_DeleteOnClose);
      regexHelpDialog->show();
    });

    // 打开文件
    connect(ui->actionFileOpen, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString fileAbsPath = indexes.first().siblingAtColumn(1).data().toString() +
        "/" +
        indexes.first().siblingAtColumn(0).data().toString();
      sLog.logf("打开文件: %s", fileAbsPath.toStdString().c_str());

      if (QFileInfo::exists(fileAbsPath)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileAbsPath));
        quickInformation->quickShow(widget, "打开成功");

        // 更新数据库 文件被打开次数
        sFileActionsDB.updateFileAction(fileAbsPath, "打开");
      }
    });

    // 打开文件路径
    connect(ui->actionFileOpenExplore, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString path = indexes.first().siblingAtColumn(1).data().toString();
      sLog.logf("打开文件路径: %s", path.toStdString().c_str());

      if (QFileInfo::exists(path)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        quickInformation->quickShow(widget, "打开成功");
      }
    });

    // 复制文件名
    connect(ui->actionFileCopyName, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 0 列文件名
      const QString name = indexes.first().siblingAtColumn(0).data().toString();
      sLog.logf("复制文件名: %s", name.toStdString().c_str());

      QApplication::clipboard()->setText(name);

      quickInformation->quickShow(widget, "复制成功");
    });

    // 复制文件路径不含文件名
    connect(ui->actionFileCopyPath, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString path = indexes.first().siblingAtColumn(1).data().toString();
      sLog.logf("复制文件路径不含文件名: %s", path.toStdString().c_str());

      QApplication::clipboard()->setText(path);
      quickInformation->quickShow(widget, "复制成功");
    });

    // 复制文件绝对路径
    connect(ui->actionFileCopyAbsPath, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString path = indexes.first().siblingAtColumn(1).data().toString() + "\\" +
        indexes.first().siblingAtColumn(0).data().toString();
      sLog.logf("复制文件绝对路径: %s", path.toStdString().c_str());

      QApplication::clipboard()->setText(path);
      quickInformation->quickShow(widget, "复制成功");
    });

    // 删除文件
    connect(ui->actionFileDelete, &QAction::triggered, [ui, widget] {
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      if (QMessageBox::warning(widget, tr("警告"), tr("该操作会删除所有所选文件，是否确定？"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No) ==
        QMessageBox::No) { return; }
      for (const auto& index : indexes) {
        const QString filePath = index.siblingAtColumn(1).data().toString();
        const QString fileAbsPath = filePath + "/" +
          index.siblingAtColumn(0).data().toString();

        if (QFile::remove(fileAbsPath)) {
          sLog.logf("删除文件: %s", fileAbsPath.toStdString().c_str());
          quickInformation->quickShow(widget, "删除成功");
          // 更新数据库
          sFileDB.delectRowByFileAbsPath(fileAbsPath, "Files");
          ui->tableView->update();
        }
        else { quickInformation->quickShow(widget, "删除失败"); }
      }
    });

    // 使用文本编辑器编辑
    connect(ui->actionEditText, &QAction::triggered, [widget, ui] {
      auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      const QString filePath = indexes.first().siblingAtColumn(1).data().
                                       toString();
      const QString fileAbsPath = filePath + "/" +
        indexes.first().siblingAtColumn(0).data().toString();

      // 使用文本编辑器打开
      QString textEditorPath;
#ifdef Q_OS_WIN
      textEditorPath = "notepad.exe";
#elif defined(Q_OS_MAC)
    textEditorPath = "/Applications/TextEdit.app/Contents/MacOS/TextEdit";
#else // Linux
    textEditorPath = "gedit";
#endif

      if (QProcess::startDetached(textEditorPath, QStringList() << fileAbsPath)) {
        sLog.logf("使用文本编辑器打开文件: %s", fileAbsPath.toStdString().c_str());
        quickInformation->quickShow(widget, "打开成功");
      }
      else { quickInformation->quickShow(widget, "打开失败"); }
    });

    // 编辑图像
    connect(ui->actionImgEditorPix, &QAction::triggered, [widget, ui] {
      auto* psWidget = PS::getInstance();
      connect(psWidget, &PS::WindowClose, widget, &MainWindow::show);
      widget->hide();
      psWidget->show();
      auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      const QString path = indexes.first().siblingAtColumn(1).data().
                                   toString();
      const QString imgFilePath = path + "\\" +
        indexes.first().siblingAtColumn(0).data().toString();
      psWidget->OpenImage(imgFilePath);

      sLog.logf("打开编辑图像: %s", imgFilePath.toStdString().c_str());
    });

    // 文件加密/解密
    connect(ui->actionJiaMi, &QAction::triggered, [widget, ui] {
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      if (QMessageBox::warning(widget, tr("警告"), tr("该操作会加密所选文件，是否确定？"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No) ==
        QMessageBox::No) { return; }

      for (const auto& index : indexes) {
        const QString filePath = index.siblingAtColumn(1).data().toString();
        const QString jsonFilePath = QStandardPaths::writableLocation(
          QStandardPaths::ConfigLocation) + "/ICMA_EncryptFile.json";
        if (aesEncryptFile(filePath + "/" +
                           index.siblingAtColumn(0).data().toString(),
                           filePath + "/" +
                           index.siblingAtColumn(0).data().toString() + ".enc",
                           sJsonManager.getConfig(jsonFilePath, "aesKey").
                                        toLocal8Bit(),
                           sJsonManager.getConfig(jsonFilePath, "aesIv").
                                        toLocal8Bit())) {
          sLog.logf("加密文件: %s", filePath.toStdString().c_str());
          quickInformation->quickShow(widget, "加密成功");
          // 更新数据库
          sFileDB.delectRowByFileAbsPath(filePath + "/" +
                                         index.siblingAtColumn(0).data().
                                               toString(),
                                         "Files");
          sFileDB.insertFileInto("Files", sFileDB.createFileInfo(filePath + "/" +
                                   index.siblingAtColumn(0).data().toString() +
                                   ".enc",
                                   true));
          ui->tableView->update();
        }
        else { quickInformation->quickShow(widget, "加密失败"); }
      }
    });
    connect(ui->actionJieMi, &QAction::triggered, [widget, ui] {
      const auto indexes = ui->tableView->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      if (QMessageBox::warning(widget, tr("警告"), tr("该操作会解密所选文件，是否确定？"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No) ==
        QMessageBox::No) { return; }

      for (const auto& index : indexes) {
        const QString filePath = index.siblingAtColumn(1).data().toString();
        const QString jsonFilePath = QStandardPaths::writableLocation(
          QStandardPaths::ConfigLocation) + "/ICMA_EncryptFile.json";
        if (aesDecryptFile(filePath + "/" +
                           index.siblingAtColumn(0).data().toString() + ".enc",
                           filePath + "/" +
                           index.siblingAtColumn(0).data().toString(),
                           sJsonManager.getConfig(jsonFilePath, "aesKey").
                                        toLocal8Bit(),
                           sJsonManager.getConfig(jsonFilePath, "aesIv").
                                        toLocal8Bit())) {
          sLog.logf("解密文件: %s", filePath.toStdString().c_str());
          quickInformation->quickShow(widget, "解密成功");
          // 更新数据库
          sFileDB.delectRowByFileAbsPath(filePath + "/" +
                                         index.siblingAtColumn(0).data().
                                               toString() + ".enc",
                                         "Files");
          sFileDB.insertFileInto("Files", sFileDB.createFileInfo(filePath + "/" +
                                   index.siblingAtColumn(0).data().toString(),
                                   true));
        }
      }
    });

    connect(ui->actionBigFont, &QAction::triggered, [] {
      const int newSize = QApplication::font().pointSize() + 1;
      const QString styleSheet = QString("* { font-size: %1pt; }").arg(newSize);
      qApp->setStyleSheet(qApp->styleSheet() + styleSheet);
      sLog.logf("设置字体大小为: %d", newSize);
    });

    connect(ui->actionSmallFont, &QAction::triggered, [] {
      const int newSize = QApplication::font().pointSize() - 1;
      const QString styleSheet = QString("* { font-size: %1pt; }").arg(newSize);
      qApp->setStyleSheet(qApp->styleSheet() + styleSheet);
      sLog.logf("设置字体大小为: %d", newSize);
    });

    connect(ui->actionGeneralFont, &QAction::triggered, [] {
      const QString styleSheet = "* { font-size: 10pt; }";
      qApp->setStyleSheet(qApp->styleSheet() + styleSheet);
      sLog.log("恢复字体到默认(10号)");
    });
    return true;
  }
};

class SetupConnectionsRenamer final : public QObject {
  Q_OBJECT;

public:
  /**
   * @brief 建立主界面 UI 信号
   * @param ui
   * @param widget 信号监听者
   * @return
   */
  static bool setupActionsConnection(Ui::Renamer* ui, Renamer* widget)
  {
    // 打开文件
    connect(ui->actionFileOpen, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->fileTableWidget->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      const QString fileAbsPath = indexes.first().siblingAtColumn(6).data().toString() +
        "/" +
        indexes.first().siblingAtColumn(1).data().toString();
      sLog.logf("打开文件: %s", fileAbsPath.toStdString().c_str());

      if (QFileInfo::exists(fileAbsPath)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileAbsPath));
        quickInformation->quickShow(widget, "打开成功");

        // 更新数据库 文件被打开次数
        sFileActionsDB.updateFileAction(fileAbsPath, "打开");
      }
    });

    // 打开文件路径
    connect(ui->actionFileOpenExplore, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->fileTableWidget->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString path = indexes.first().siblingAtColumn(6).data().toString();
      sLog.logf("打开文件路径: %s", path.toStdString().c_str());

      if (QFileInfo::exists(path)) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(path));
        quickInformation->quickShow(widget, "打开成功");
      }
    });

    // 复制文件名
    connect(ui->actionFileCopyName, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->fileTableWidget->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 0 列文件名
      const QString name = indexes.first().siblingAtColumn(1).data().toString();
      sLog.logf("复制文件名: %s", name.toStdString().c_str());

      QApplication::clipboard()->setText(name);

      quickInformation->quickShow(widget, "复制成功");
    });

    connect(ui->actionFileCopyNewName, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->fileTableWidget->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 0 列文件名
      const QString name = indexes.first().siblingAtColumn(2).data().toString();
      sLog.logf("复制文件名: %s", name.toStdString().c_str());

      QApplication::clipboard()->setText(name);

      quickInformation->quickShow(widget, "复制成功");
    });

    // 复制文件路径不含文件名
    connect(ui->actionFileCopyPath, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->fileTableWidget->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString path = indexes.first().siblingAtColumn(6).data().toString();
      sLog.logf("复制文件路径不含文件名: %s", path.toStdString().c_str());

      QApplication::clipboard()->setText(path);
      quickInformation->quickShow(widget, "复制成功");
    });

    // 复制文件绝对路径
    connect(ui->actionFileCopyAbsPath, &QAction::triggered, [ui, widget] {
      // 获取tableView被点击的项
      const auto indexes = ui->fileTableWidget->selectionModel()->selectedIndexes();
      if (indexes.isEmpty()) { return; }

      // 获取第 0 项的第 1 列完整文件路径
      const QString path = indexes.first().siblingAtColumn(6).data().toString() + "\\" +
        indexes.first().siblingAtColumn(1).data().toString();
      sLog.logf("复制文件绝对路径: %s", path.toStdString().c_str());

      QApplication::clipboard()->setText(path);
      quickInformation->quickShow(widget, "复制成功");
    });

    return true;
  }
};
