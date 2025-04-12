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

#include "../../UI/ui_MainWindow.h"
#include "../DataBase/SqlQuery/FileActions.h"
#include "../DataBase/SqlQuery/Files.h"
#include "../Utils/Tools/LogOut.h"
#include "../Utils/Tools/MyInformationBox.h"
#include "../Widgets/mainWindow/MainWindow.h"
#include "../Widgets/photoShop/PS.h"

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
    return true;
  }
};
