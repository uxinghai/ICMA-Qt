#include "Renamer.h"

#include <QDirIterator>
#include <QFileDialog>
#include <QRegExp>
#include <QToolButton>

#include  "../../../UI/ui_Renamer.h"
#include "../../Connections/SetupConnections.h"
#include "../../Utils/Tools/DataUnitCalc.h"
#include "../../Utils/Tools/LogOut.h"
#include "D:/A-Develop/ToolLibrary/OpenCC/src/opencc.h"

Renamer::Renamer(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::Renamer), statusLabel(new QLabel(this))
{
  ui->setupUi(this);

  sLog.log("文件批量去重工具打开成功.");

  initUI();
  setupConnections();
  SetupConnectionsRenamer::setupActionsConnection(ui, this);

  // 构建映射函数
  std::function doMapDate = [this] {
    const QString curDate = QDate::currentDate().toString("yyyyMMdd");
    return curDate.toStdString();
  };
  std::function doMapTime = [this] {
    const QString curTime = QTime::currentTime().toString("hhmmss");
    return curTime.toStdString();
  };
  std::function doMapcDate = [this] {
    const QString curDate = QDate::currentDate().toString("yyyy-MM-dd");
    return curDate.toStdString();
  };
  std::function doMapcTime = [this] {
    const QString curTime = QTime::currentTime().toString("hh:mm:ss");
    return curTime.toStdString();
  };
  std::function doMapmDate = [this] {
    const QString curDateTime = QDateTime::currentDateTime().toString("yyyyMMdd hhmmss");
    return curDateTime.toStdString();
  };
  std::function doMapmTime = [this] {
    const QString curDateTime = QDateTime::currentDateTime().toString(
      "yyyy-MM-dd hh:mm:ss");
    return curDateTime.toStdString();
  };

  map.insert({"<date>", doMapDate});
  map.insert({"<time>", doMapTime});
  map.insert({"<cdate>", doMapcDate});
  map.insert({"<ctime>", doMapcTime});
  map.insert({"<mdate>", doMapmDate});
  map.insert({"<mtime>", doMapmTime});

  setupCustomMenu();
}

void Renamer::initUI()
{
  ui->tabWidget->resize(ui->tabWidget->width(), 180);
  ui->statusBar->addWidget(statusLabel);
  ui->fileTableWidget->horizontalHeader()->setSectionResizeMode(
    QHeaderView::ResizeToContents);
  ui->tabWidget->setEnabled(false);

  confirmButton = new QToolButton(this);
  confirmButton->setIcon(QIcon(":/icons/res/confirm.png"));
  confirmButton->setText("执行改名");
  confirmButton->setStyleSheet(R"(
    QToolButton {
        border: 0.5px solid #999999;
        border-radius: 4px;
        padding: 0px;
        margin: 0px;
        background-color: #f0f0f0;
    }
    QToolButton:hover {
        background-color: #e0e0e0;
    }
    QToolButton:pressed {
        background-color: #d0d0d0;
    })");

  confirmButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  ui->toolBar->addWidget(confirmButton);
}

void Renamer::setupConnections()
{
  // 工具栏 Actions
  connect(ui->actionAddFile, &QAction::triggered, this, &Renamer::doAddFile);
  connect(ui->actionAddFileFormDir, &QAction::triggered, this, &Renamer::doAddDir);
  connect(ui->actionClearFileList, &QAction::triggered, this, &Renamer::doClearFileList);

  // 监听项变化改变颜色
  connect(ui->fileTableWidget, &QTableWidget::itemChanged, this, &Renamer::doItemChanged);

  // Tab切换则保留当前新的文件名
  connect(ui->tabWidget, &QTabWidget::currentChanged, [this](const int&) {
    QStringList addToHistory;
    for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
      addToHistory << ui->fileTableWidget->item(i, 2)->text();
    }
    if (addToHistory != history.last()) { history.push_back(addToHistory); }
  });

  // 执行改名
  connect(confirmButton, &QToolButton::clicked, this, &Renamer::doConfirm);
  connect(ui->actionUndoRename, &QAction::triggered, this, &Renamer::doUndo);

  // Tab Widget
  setupConnectionsAll();     ///< 整体
  setupConnectionsReplace(); ///< 替换
  setupConnectionsAdd();     ///< 添加
  setupConnectionsDelete();  ///< 删除
  setupConnectionsNumber();  ///< 序号
}

void Renamer::setupConnectionsAll()
{
  connect(ui->radioButtonAllCase, &QRadioButton::clicked, this, &Renamer::doAllCase);
  connect(ui->radioButtonNoCase, &QRadioButton::clicked, this, &Renamer::doNoCase);
  connect(ui->radioButtonFirstCase, &QRadioButton::clicked, this, &Renamer::doFirstCase);
  connect(ui->radioButtonRan, &QRadioButton::clicked, this, &Renamer::doRandom);
  connect(ui->radioButtonNumUp, &QRadioButton::clicked, this, &Renamer::doNumUp);
  connect(ui->comboBox_2, &QComboBox::editTextChanged, [this](const QString& text) {
    if (text.isEmpty() && ui->comboBox->currentIndex() == 0) {
      // 判断哪一个按钮被选中，执行对应操作
      for (const auto rd : ui->groupBox->findChildren<QRadioButton*>()) {
        if (rd->isChecked()) {
          if (rd->text() == "全部大写") { doAllCase(); }
          else if (rd->text() == "全部小写") { doNoCase(); }
          else if (rd->text() == "首字母大写") { doFirstCase(); }
          else if (rd->text() == "随机数") { doRandom(); }
          else if (rd->text() == "数字递增") { doNumUp(); }
          else if (rd->text() == "保持不变") { doNo(); }
        }
      }
    }
    else {
      for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
        if (const auto item = ui->fileTableWidget->item(i, 2)) {
          const auto lastText = history.last()[i];
          item->setText(
            text + lastText.right(lastText.size() - lastText.lastIndexOf(".")));
        }
      }
    }
  });
  connect(ui->comboBox, &QComboBox::currentIndexChanged,
          [this](const int& index) {
            switch (index) {
            case 0:
              doTextConversion(0);
              break;
            case 1: ///< 简体转繁体
              //doTextConversion(1);
              break;
            case 2: ///< 繁体转简体
              //doTextConversion(2);
              break;
            case 3: ///< 一二三转123
              doTextConversion(3);
              break;
            case 4: ///< 123转一二三
              doTextConversion(4);
              break;
            default:
              break;;
            }
          });
  connect(ui->radioButtonNo, &QRadioButton::clicked, this, &Renamer::doNo);

  /////////////////////////////////////////////////////////////////

  connect(ui->radioButtonSuffAllCase, &QRadioButton::clicked, this,
          &Renamer::doSuffixAllCase);
  connect(ui->radioButtonSuffNoCase, &QRadioButton::clicked, this,
          &Renamer::doSuffixNoCase);
  connect(ui->radioButtonSuffNo, &QRadioButton::clicked, this, &Renamer::doSuffixNo);

  connect(ui->comboBoxSuffix, &QComboBox::editTextChanged,
          [this](const QString& text) {
            if (text.isEmpty()) {
              // 判断哪一个按钮被选中，执行对应操作
              for (const auto rd : ui->groupBox_2->findChildren<QRadioButton*>()) {
                if (rd->isChecked()) {
                  if (rd->text() == "全部大写") { doSuffixAllCase(); }
                  else if (rd->text() == "全部小写") { doSuffixNoCase(); }
                  else if (rd->text() == "保持不变") { doSuffixNo(); }
                }
              }
            }
            else {
              for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
                const auto oldItemStr = history.last()[i];
                const auto index = oldItemStr.lastIndexOf(".");
                ui->fileTableWidget->item(i, 2)->setText(
                  oldItemStr.left(index) + "." + text);

                ui->fileTableWidget->item(i, 4)->setText(
                  ui->fileTableWidget->item(i, 2)->text().right
                  (ui->fileTableWidget->item(i, 2)->text().size() -
                    ui->fileTableWidget->item(i, 2)->text().lastIndexOf(".")));
              }
            }
          });
}

void Renamer::setupConnectionsReplace()
{
  connect(ui->comboBoxSouce, &QComboBox::editTextChanged, [this](const QString&) {
    doReplace();
  });

  connect(ui->comboBoxDest, &QComboBox::editTextChanged, [this](const QString&) {
    doReplace();
  });

  connect(ui->checkBoxCase, &QCheckBox::clicked, [this](const bool&) { doReplace(); });
}

void Renamer::setupConnectionsAdd()
{
  connect(ui->comboBoxSuffix_2, &QComboBox::editTextChanged,
          [this](const QString&) {
            doAddSuffixPreFix(!ui->comboBox_8->currentText().isEmpty());
          });
  connect(ui->comboBoxPreFix, &QComboBox::editTextChanged,
          [this](const QString&) {
            doAddSuffixPreFix(!ui->comboBox_8->currentText().isEmpty());
          });

  connect(ui->comboBox_8, &QComboBox::editTextChanged, [this](const QString&) {
    doAddToIndex();
  });
  connect(ui->spinBox, &QSpinBox::valueChanged, [this](const int&) { doAddToIndex(); });
  connect(ui->checkBox_4, &QCheckBox::clicked, [this](const bool&) { doAddToIndex(); });

  connect(ui->comboBox_9, &QComboBox::editTextChanged, [this](const QString&) {
    doAddTextTo();
  });
  connect(ui->comboBoxTxt, &QComboBox::editTextChanged, [this](const QString&) {
    doAddTextTo();
  });
  connect(ui->comboBox_11, &QComboBox::currentIndexChanged, [this](const int&) {
    doAddTextTo();
  });
}

void Renamer::setupConnectionsDelete()
{
  connect(ui->comboBox_12, &QComboBox::editTextChanged, [this](const QString& text) {
    doDeleteText(text);
  });

  for (const auto chk : ui->widget->findChildren<QCheckBox*>()) {
    connect(chk, &QCheckBox::stateChanged, this, [this](const int state) {
      onCheckBoxStateChanged(state);
    });
  }

  connect(ui->spinBox_2, &QSpinBox::valueChanged, [this](const int&) {
    doDeleteIndex();
  });
  connect(ui->checkBox_5, &QCheckBox::stateChanged,
          [this](const int) { doDeleteIndex(); });
  connect(ui->spinBox_3, &QSpinBox::valueChanged, [this](const int&) {
    doDeleteIndex();
  });
}

void Renamer::setupConnectionsNumber()
{
  connect(ui->checkBox_12, &QCheckBox::stateChanged, [this](const int&) {
    doNumberlise();
  });
  connect(ui->spinBox_5, &QSpinBox::valueChanged, [this](const int&) { doNumberlise(); });
  connect(ui->spinBox_6, &QSpinBox::valueChanged, [this](const int&) { doNumberlise(); });
  connect(ui->spinBox_7, &QSpinBox::valueChanged, [this](const int&) { doNumberlise(); });
}

void Renamer::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
}

void Renamer::doAddFile()
{
  filesList = QFileDialog::getOpenFileNames(this, tr("添加文件"), "", "*.*");
  if (filesList.isEmpty()) { return; }
  insertRows(ui->fileTableWidget);
  sLog.logf("批量重命名：添加了文件共：%d 条", filesList.size());
  ui->tabWidget->setEnabled(true);
}

void Renamer::doAddDir()
{
  // 选择文件夹
  const QString dir = QFileDialog::getExistingDirectory(this, tr("添加文件来自文件夹"), "",
                                                        QFileDialog::ShowDirsOnly);
  if (dir.isEmpty()) { return; }

  QDirIterator it(dir, QDir::Files, QDirIterator::Subdirectories);
  while (it.hasNext()) {
    const QString filePath = it.next();
    filesList.append(QFileInfo(filePath).absoluteFilePath());
  }

  insertRows(ui->fileTableWidget);
  sLog.logf("批量重命名：添加了文件共：%d 条", filesList.size());
  statusLabel->setText(QString("%1 条").arg(filesList.size()));
  ui->tabWidget->setEnabled(true);
}

void Renamer::doClearFileList()
{
  filesList.clear();
  clearContentAndStruct(ui->fileTableWidget);
  statusLabel->setText("0 条");
  sLog.log("批量重命名：清空了文件列表");
}

void Renamer::doItemChanged(QTableWidgetItem* item)
{
  // 只有第2列和4列是变化的 判断和第一列是否不完全相等，如果是则改为红色，否则默认黑色
  if (item->column() == 2) {
    if (ui->fileTableWidget->item(item->row(), 1)->text() !=
      ui->fileTableWidget->item(item->row(), 2)->text()) {
      item->setForeground(QBrush(Qt::red));
    }
    else { item->setForeground(QBrush(Qt::black)); }
  }

  if (ui->fileTableWidget->item(item->row(), 4) && ui->fileTableWidget->
                                                       item(item->row(), 2)) {
    ui->fileTableWidget->item(item->row(), 4)->setText(ui->fileTableWidget->item
      (item->row(), 2)->text().right(
        ui->fileTableWidget->item(item->row(), 2)->text().size
        () - ui->fileTableWidget->item(item->row(), 2)->text().lastIndexOf(".")));
  }
  if (item->column() == 4) {
    const QString text = ui->fileTableWidget->item(item->row(), 1)->text();
    if (const auto nowText = ui->fileTableWidget->item(item->row(), 4);
      text.right(text.size() - text.lastIndexOf(".")) !=
      nowText->text()) { item->setForeground(QBrush(Qt::red)); }
    else { item->setForeground(QBrush(Qt::black)); }
  }
}

void Renamer::doUndo()
{
  if (history.size() <= 1) {
    sLog.log("批量重命名：没有可撤销的记录");
    return;
  }
  history.pop_back();

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      item->setText(history.last()[i]);
    }
  }
}

void Renamer::doConfirm()
{
  if (ui->fileTableWidget->rowCount() == 0) {
    sLog.log("批量重命名：没有文件需要重命名");
    return;
  }

  if (QMessageBox::question(this, "提示", "是否确认重命名？",
                            QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
    return;
  }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      const QString newName = item->text();
      const QString oldName = ui->fileTableWidget->item(i, 1)->text();
      const QString oldPath = ui->fileTableWidget->item(i, 5)->text();
      if (const QString newPath = oldPath.left(oldPath.lastIndexOf("/") + 1) + newName;
        QFile::rename(oldPath, newPath)) {
        sLog.logf("批量重命名：重命名了文件：%s", oldName.toStdString().c_str());
      }
      else { sLog.logf("批量重命名：重命名文件失败：%s", oldName.toStdString().c_str()); }
    }
  }
}

void Renamer::doTextConversion(const int conversionType)
{
  if (conversionType == 0 && ui->comboBox_2->currentText().isEmpty()) {
    for (const auto rd : ui->groupBox->findChildren<QRadioButton*>()) {
      if (rd->isChecked()) {
        if (rd->text() == "全部大写") { doAllCase(); }
        else if (rd->text() == "全部小写") { doNoCase(); }
        else if (rd->text() == "首字母大写") { doFirstCase(); }
        else if (rd->text() == "随机数") { doRandom(); }
        else if (rd->text() == "数字递增") { doNumUp(); }
        else if (rd->text() == "保持不变") { doNo(); }
      }
    }
    return;
  }
  // 获取输入文本
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      QString inputText = history.last()[i];
      QString outputText;

      // 根据选择执行相应的转换
      switch (conversionType) {
      case 1: // 简体转繁体
        // outputText = convertSimplifiedToTraditional(inputText);
        break;
      case 2: // 繁体转简体
        // outputText = convertTraditionalToSimplified(inputText);
        break;
      case 3: // 中文数字转阿拉伯数字
        outputText = convertChineseNumToArabic(inputText);
        break;
      case 4: // 阿拉伯数字转中文数字
        outputText = convertArabicNumToChinese(inputText);
        break;
      default:
        outputText = inputText;
        break;
      }

      // 显示转换后的文本
      item->setText(outputText);
    }
  }
}

void Renamer::doSuffixAllCase()
{
  if (!ui->comboBoxSuffix->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto oldItemStr = history.last()[i];
    const auto index = oldItemStr.lastIndexOf(".");
    const auto item = ui->fileTableWidget->item(i, 2);
    item->setText(oldItemStr.left(index) + oldItemStr.right(oldItemStr.size() -
      index).toUpper());
  }
}

void Renamer::doSuffixNoCase()
{
  if (!ui->comboBoxSuffix->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto oldItemStr = history.last()[i];
    const auto item = ui->fileTableWidget->item(i, 2);
    const auto index = oldItemStr.lastIndexOf(".");
    item->setText(oldItemStr.left(index) + oldItemStr.right(oldItemStr.size()
      - index).toLower());
  }
}

void Renamer::doSuffixNo()
{
  if (!ui->comboBoxSuffix->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto oldStr = history.last()[i];
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) { item->setText(oldStr); }
  }
}

void Renamer::doNumUp()
{
  if (history.isEmpty() || ui->comboBox->currentIndex() != 0 ||
    !ui->comboBox_2->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto item = ui->fileTableWidget->item(i, 2);
    const auto lastText = history.last()[i];
    item->setText(QString::number(i + 1) +
      lastText.right(lastText.size() - lastText.lastIndexOf(".")));
  }
}

void Renamer::doRandom()
{
  if (history.isEmpty() || ui->comboBox->currentIndex() != 0 ||
    !ui->comboBox_2->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto item = ui->fileTableWidget->item(i, 2);
    const auto lastText = history.last()[i];
    const auto index = lastText.lastIndexOf(".");
    item->setText(generateRandomString() + lastText.right(lastText.size() - index));
  }
}

void Renamer::doFirstCase()
{
  if (history.isEmpty() || ui->comboBox->currentIndex() != 0 ||
    !ui->comboBox_2->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto item = ui->fileTableWidget->item(i, 2);
    const auto lastText = history.last()[i];
    const auto index = lastText.lastIndexOf(".");
    item->setText(lastText.left(index).toLower().replace(0, 1,
                                                         lastText.left(index).toLower().
                                                         at(0).toUpper()) +
      lastText.right(lastText.size() - index));
  }
}

void Renamer::doNoCase()
{
  if (history.isEmpty() || ui->comboBox->currentIndex() != 0 ||
    !ui->comboBox_2->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto item = ui->fileTableWidget->item(i, 2);
    const auto lastText = history.last()[i];
    const auto index = lastText.lastIndexOf(".");
    item->setText(
      lastText.left(index).toLower() + lastText.right(lastText.size() - index));
  }
}

void Renamer::doAllCase() const
{
  if (history.isEmpty() || ui->comboBox->currentIndex() != 0 ||
    !ui->comboBox_2->currentText().isEmpty()) { return; }

  // 全部字母大写
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto lastText = history.last()[i];
    const auto item = ui->fileTableWidget->item(i, 2);
    const auto index = lastText.lastIndexOf(".");
    item->setText(lastText.left(index).toUpper() + lastText.right(
      lastText.size() - index));
  }
}

void Renamer::doNo()
{
  if (history.isEmpty() || ui->comboBox->currentIndex() != 0 ||
    !ui->comboBox_2->currentText().isEmpty()) { return; }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto item = ui->fileTableWidget->item(i, 2);
    item->setText(history.last()[i]);
  }
}

void Renamer::doReplace()
{
  const QString srcStr = ui->comboBoxSouce->currentText();
  const QString destStr = ui->comboBoxDest->currentText();

  if (srcStr.isEmpty() || destStr.isEmpty()) {
    for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
      if (const auto item = ui->fileTableWidget->item(i, 2)) {
        item->setText(history.last()[i]);
      }
    }
    return;
  }

  const bool isCase = ui->checkBoxCase->isChecked();

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto historyText = history.last()[i];

    QString oldItemStr = historyText.left(historyText.lastIndexOf("."));
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      QString replacedStr = oldItemStr.replace(srcStr, destStr,
                                               isCase
                                                 ? Qt::CaseSensitive
                                                 : Qt::CaseInsensitive);
      item->setText(replacedStr + ui->fileTableWidget->item(i, 4)->text());
    }
  }
}

void Renamer::doAddSuffixPreFix(const bool& addToNowText)
{
  QString prefix = ui->comboBoxPreFix->currentText();
  QString suffix = ui->comboBoxSuffix_2->currentText();

  if (prefix.isEmpty() && suffix.isEmpty()) {
    // for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    //   const auto item = ui->fileTableWidget->item(i, 2);
    //   item->setText(history.last()[i]);
    // }
    return;
  }

  const std::string key = prefix.toStdString();
  if (const auto it = map.find(key); it != map.end()) {
    prefix = QString::fromStdString(it->second());
  }

  const std::string key2 = suffix.toStdString();
  if (const auto it = map.find(key2); it != map.end()) {
    suffix = QString::fromStdString(it->second());
  }

  if (addToNowText) {
    for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
      const QString oldText = ui->fileTableWidget->item(i, 2)->text();
      QString oldItemStr = oldText.left(oldText.lastIndexOf("."));
      if (const auto item = ui->fileTableWidget->item(i, 2)) {
        item->setText(
          prefix + oldItemStr + suffix + ui->fileTableWidget->item(i, 4)->text());
      }
    }

    return;
  }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const QString oldText = history.last()[i];
    QString oldItemStr = oldText.left(oldText.lastIndexOf("."));
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      item->setText(
        prefix + oldItemStr + suffix + ui->fileTableWidget->item(i, 4)->text());
    }
  }
}

void Renamer::doAddToIndex()
{
  const auto index = ui->spinBox->value();
  const bool rightToLeft = ui->checkBox_4->isChecked(); ///< 是否从右往左数
  QString text = ui->comboBox_8->currentText();

  const std::string key = text.toStdString();
  if (const auto it = map.find(key); it != map.end()) {
    text = QString::fromStdString(it->second());
  }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const QString oldText = history.last()[i];
    QString oldItemStr = oldText.left(oldText.lastIndexOf("."));
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      if (rightToLeft) {
        item->setText(oldItemStr.right(oldItemStr.size() - index) + text +
          oldItemStr.left(index) + ui->fileTableWidget->item(i, 4)->text());
      }
      else {
        item->setText(oldItemStr.left(index) + text +
          oldItemStr.right(oldItemStr.size() - index) +
          ui->fileTableWidget->item(i, 4)->text());
      }
    }
  }

  doAddSuffixPreFix(true);
}

void Renamer::doAddTextTo()
{
  const QString findText = ui->comboBoxTxt->currentText();
  const bool isFront = ui->comboBox_11->currentIndex() == 0; ///< 前面添加或者后面添加
  QString addText = ui->comboBox_9->currentText();

  const std::string key = addText.toStdString();
  if (const auto it = map.find(key); it != map.end()) {
    addText = QString::fromStdString(it->second());
  }

  if (findText.isEmpty() || addText.isEmpty()) {
    for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
      if (const auto item = ui->fileTableWidget->item(i, 2)) {
        item->setText(history.last()[i]);
      }
    }
    return;
  }

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const QString oldText = history.last()[i];
    QString oldItemStr = oldText.left(oldText.lastIndexOf("."));
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      if (isFront) {
        item->setText(oldItemStr.replace(oldItemStr.indexOf(findText),
                                         findText.size(), addText + findText) +
          ui->fileTableWidget->item(i, 4)->text());
      }
      else {
        item->setText(oldItemStr.replace(oldItemStr.indexOf(findText),
                                         findText.size(), findText + addText) +
          ui->fileTableWidget->item(i, 4)->text());
      }
    }
  }
}

void Renamer::doDeleteText(const QString& text)
{
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    QString oldText = tempHistory[i].left(tempHistory[i].lastIndexOf("."));
    const auto item = ui->fileTableWidget->item(i, 2);
    if (oldText.contains(text)) {
      item->setText(oldText.replace(text, "") +
        ui->fileTableWidget->item(i, 4)->text());
    }
  }
}

void Renamer::doDelete()
{
  // 保存当前状态到临时历史
  QVector<QString> currentState;
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    currentState.append(ui->fileTableWidget->item(i, 2)->text());
  }
  tempHistory = currentState;

  // 删除空格
  if (ui->checkBox_6->isChecked()) {
    if (!checkBoxStates.contains("checkBox_6")) {
      checkBoxStates["checkBox_6"] = currentState;
    }
    doDeleteText(" ");
  }

  // 删除所有数字
  else if (ui->checkBox_7->isChecked()) {
    if (!checkBoxStates.contains("checkBox_7")) {
      checkBoxStates["checkBox_7"] = currentState;
    }
    for (const auto& num : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) {
      doDeleteText(QString::number(num));
    }
  }

  // 删除所有小写字母
  else if (ui->checkBox_8->isChecked()) {
    if (!checkBoxStates.contains("checkBox_8")) {
      checkBoxStates["checkBox_8"] = currentState;
    }
    for (const auto& letter : "abcdefghjklmnopqrstuvwxyz") {
      doDeleteText(QString(letter));
    }
  }

  // 删除所有大写字母
  else if (ui->checkBox_9->isChecked()) {
    if (!checkBoxStates.contains("checkBox_9")) {
      checkBoxStates["checkBox_9"] = currentState;
    }
    for (const auto& letter : "ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
      doDeleteText(QString(letter));
    }
  }

  // 删除所有特殊字符
  else if (ui->checkBox_10->isChecked()) {
    if (!checkBoxStates.contains("checkBox_10")) {
      checkBoxStates["checkBox_10"] = currentState;
    }
    for (const auto& letter : {
           "~", "`", "!", "@", "#", "$", "%", "^", "&", "*",
           "(", ")", "-", "_", "+", "=", "[", "{", "]", "}",
           "\\", "|", ";", ":", "'", "\"", ",", "<",
           ">", "/", "?"
         }) { doDeleteText(QString(letter)); }
  }
}

void Renamer::doDeleteIndex()
{
  const int index = ui->spinBox_2->value();          ///< 开始索引
  const bool formRtoL = ui->checkBox_5->isChecked(); ///< 从右向左的标记
  const int num = ui->spinBox_3->value();            ///< 删除个数

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    QString oldText;
    if (tempHistory.isEmpty()) {
      oldText = history.last()[i].left(history.last()[i].lastIndexOf("."));
    }
    else { oldText = tempHistory[i].left(tempHistory[i].lastIndexOf(".")); }
    if (formRtoL) {
      ui->fileTableWidget->item(i, 2)->setText(oldText.left(index) +
        oldText.mid(index + num) + ui->fileTableWidget->item(i, 4)->text());
    }
    else {
      ui->fileTableWidget->item(i, 2)->setText(oldText.left(index) +
        oldText.mid(index) + ui->fileTableWidget->item(i, 4)->text());
    }
  }
}

void Renamer::doNumberlise()
{
  if (const bool isEnable = ui->checkBox_12->isChecked(); isEnable == false) {
    for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
      if (const auto item = ui->fileTableWidget->item(i, 2)) {
        item->setText(history.last()[i]);
      }
    }
    return;
  }

  const int startValue = ui->spinBox_5->value(); ///< 起始值
  const int stepValue = ui->spinBox_6->value();  ///< 增量
  const int numValue = ui->spinBox_7->value();   ///< 位数 5位则类似00000

  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const int value = startValue + i * stepValue;
    QString newText = QString("%1").arg(value, numValue, 10, QChar('0'));
    ui->fileTableWidget->item(i, 2)->setText(newText +
      ui->fileTableWidget->item(i, 4)->text());
  }
}

void Renamer::onCheckBoxStateChanged(int state)
{
  // 获取发送信号的复选框
  const auto checkBox = qobject_cast<QCheckBox*>(sender());
  if (!checkBox) { return; }
  // 如果是取消选中状态且有保存的状态
  if (const QString checkBoxName = checkBox->objectName();
    state == Qt::Unchecked && checkBoxStates.contains(checkBoxName)) {
    // 恢复该复选框操作前的状态
    QVector<QString> previousState = checkBoxStates[checkBoxName];

    // 更新表格显示
    for (int i = 0; i < ui->fileTableWidget->rowCount() &&
         i < previousState.size(); ++i) {
      ui->fileTableWidget->item(i, 2)->setText(previousState[i]);
    }

    // 从状态记录中移除该复选框的记录
    checkBoxStates.remove(checkBoxName);
  }
  else if (state == Qt::Checked) {
    // 如果是勾选，则执行删除操作
    doDelete();
  }
}

// 重新应用其余选中的过滤器
void Renamer::reapplyRemainingFilters()
{
  // 先保存当前状态
  QVector<QString> currentState;
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    currentState.append(ui->fileTableWidget->item(i, 2)->text());
  }

  // 清空所有复选框状态记录
  QMap<QString, QVector<QString>> tempStates = checkBoxStates;
  checkBoxStates.clear();

  // 如果没有选中任何复选框，直接返回
  if (!ui->checkBox_6->isChecked() &&
    !ui->checkBox_7->isChecked() &&
    !ui->checkBox_8->isChecked() &&
    !ui->checkBox_9->isChecked() &&
    !ui->checkBox_10->isChecked()) { return; }

  // 手动调用doDelete重新应用所有选中的过滤器
  doDelete();
}

void Renamer::insertRows(QTableWidget* widget)
{
  QStringList addToHistory;
  for (auto& file : filesList) {
    // 新增一行
    const auto row = widget->rowCount();
    widget->insertRow(row);

    // 填充行
    QFileInfo fileInfo(file);
    const auto icon = QIcon(":/suffixes/res/suffix/" +
      fileInfo.suffix().toLower() + ".png");
    widget->setItem(row, 0, new QTableWidgetItem(icon, QString::number(row + 1)));
    widget->setItem(row, 1, new QTableWidgetItem(fileInfo.fileName()));
    addToHistory << fileInfo.fileName();
    widget->setItem(row, 2, new QTableWidgetItem(fileInfo.fileName()));
    //widget->setItem(row, 3, new QTableWidgetItem(fileInfo));
    widget->setItem(row, 4, new QTableWidgetItem("." + fileInfo.suffix()));
    widget->setItem(row, 5,
                    new QTableWidgetItem(sDataUnitCalc.setDataUnit(fileInfo.size())));
    widget->setItem(row, 6, new QTableWidgetItem(fileInfo.path()));
  }
  history.push_back(addToHistory);
}

// 中文数字转阿拉伯数字
QString Renamer::convertChineseNumToArabic(const QString& text)
{
  static const std::map<QChar, int> chineseNumMap = {
    {u'零', 0}, {u'一', 1}, {u'二', 2}, {u'三', 3}, {u'四', 4},
    {u'五', 5}, {u'六', 6}, {u'七', 7}, {u'八', 8}, {u'九', 9},
    {u'壹', 1}, {u'贰', 2}, {u'叁', 3}, {u'肆', 4}, {u'伍', 5},
    {u'陆', 6}, {u'柒', 7}, {u'捌', 8}, {u'玖', 9}
  };

  static const std::map<QChar, int> chineseUnitMap = {
    {u'十', 10}, {u'百', 100}, {u'千', 1000}, {u'万', 10000}, {u'亿', 100000000},
    {u'拾', 10}, {u'佰', 100}, {u'仟', 1000}
  };

  QString result = text;
  for (int i = 0; i < result.length(); i++) {
    // 查找可能的中文数字序列
    if (chineseNumMap.find(result[i]) != chineseNumMap.end() ||
      chineseUnitMap.find(result[i]) != chineseUnitMap.end()) {
      const int start = i;
      int end = i;

      // 找到这个中文数字序列的结束位置
      while (end < result.length() &&
        (chineseNumMap.find(result[end]) != chineseNumMap.end() ||
          chineseUnitMap.find(result[end]) != chineseUnitMap.end())) { end++; }

      // 提取中文数字序列
      QString chineseNumStr = result.mid(start, end - start);

      // 计算阿拉伯数字
      int arabicNum = 0;
      int tempNum = 0;

      for (int j = 0; j < chineseNumStr.length(); j++) {
        const QChar ch = chineseNumStr[j];

        if (chineseNumMap.find(ch) != chineseNumMap.end()) {
          tempNum = chineseNumMap.at(ch);
        }
        else if (chineseUnitMap.find(ch) != chineseUnitMap.end()) {
          const int unit = chineseUnitMap.at(ch);
          if (tempNum == 0) tempNum = 1;

          if (unit >= 10000) {
            arabicNum = (arabicNum + tempNum) * unit / 10000;
            tempNum = 0;
          }
          else {
            tempNum *= unit;
            arabicNum += tempNum;
            tempNum = 0;
          }
        }
      }

      arabicNum += tempNum;

      // 替换原文中的中文数字为阿拉伯数字
      result.replace(start, end - start, QString::number(arabicNum));
      i = start + QString::number(arabicNum).length() - 1;
    }
  }

  return result;
}

// 阿拉伯数字转中文数字
QString Renamer::convertArabicNumToChinese(const QString& text)
{
  static const QString simpleChineseNum[] = {
    "零", "一", "二", "三", "四", "五", "六", "七", "八", "九"
  };
  static const QString units[] = {"", "十", "百", "千"};
  static const QString bigUnits[] = {"", "万", "亿", "兆"};

  QString result = text;
  QRegExp rx("\\d+");
  int pos = 0;

  while ((pos = rx.indexIn(result, pos)) != -1) {
    QString numStr = rx.cap(0);
    QString chineseNumStr;

    // 转换整数部分
    if (int num = numStr.toInt(); num == 0) { chineseNumStr = simpleChineseNum[0]; }
    else {
      int unitGroupCount = 0;

      while (num > 0) {
        if (int groupValue = num % 10000; groupValue > 0) {
          QString groupStr;
          for (int i = 0; i < 4; i++) {
            const int digit = groupValue % 10;
            groupValue /= 10;

            if (digit > 0) { groupStr.prepend(simpleChineseNum[digit] + units[i]); }
            else if (!groupStr.isEmpty() && groupStr[0] != simpleChineseNum[0][0]) {
              groupStr.prepend(simpleChineseNum[0]);
            }
          }

          chineseNumStr.prepend(groupStr + bigUnits[unitGroupCount]);
        }
        else if (unitGroupCount > 0 && !chineseNumStr.isEmpty() &&
          chineseNumStr[0] != simpleChineseNum[0][0]) {
          chineseNumStr.prepend(simpleChineseNum[0]);
        }

        num /= 10000;
        unitGroupCount++;
      }

      // 处理十开头的特殊情况，如"十一"而不是"一十一"
      if (chineseNumStr.startsWith(simpleChineseNum[1] + units[1])) {
        chineseNumStr.remove(0, simpleChineseNum[1].length());
      }
    }

    // 替换原文中的阿拉伯数字为中文数字
    result.replace(pos, numStr.length(), chineseNumStr);
    pos += chineseNumStr.length();
  }

  return result;
}

void Renamer::clearContentAndStruct(QTableWidget* widget)
{
  widget->clearContents();
  widget->setRowCount(0);
}

void Renamer::setupCustomMenu()
{
  ui->fileTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->fileTableWidget, &Renamer::customContextMenuRequested,
          [this](const QPoint& pos) {
            if (!ui->fileTableWidget->rowCount()) { return; }
            const int item = ui->fileTableWidget->rowAt(pos.y());
            if (const auto menu = std::make_unique<QMenu>(); item != -1) {
              menu->addActions({
                ui->actionFileOpen, ui->actionFileOpenExplore,
                ui->actionFileCopyName, ui->actionFileCopyNewName,
                ui->actionFileCopyPath, ui->actionFileCopyAbsPath
              });
              menu->exec(QCursor::pos());
            }
          });
}

Renamer::~Renamer()
{
  sLog.log("文件批量去重工具已关闭.");
  delete ui;
}
