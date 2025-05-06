#include "Renamer.h"

#include <QDirIterator>
#include <QFileDialog>
#include <QMessageBox>
#include <QRegExp>

#include  "../../../UI/ui_Renamer.h"
#include "../../Utils/Tools/DataUnitCalc.h"
#include "../../Utils/Tools/LogOut.h"
#include "D:/A-Develop/ToolLibrary/OpenCC/src/opencc.h"

Renamer::Renamer(QWidget* parent)
  : QMainWindow(parent), ui(new Ui::Renamer), statusLabel(new QLabel(this))
{
  ui->setupUi(this);

  initUI();
  setupConnections();
}

void Renamer::initUI()
{
  ui->tabWidget->resize(ui->tabWidget->width(), 180);
  ui->statusBar->addWidget(statusLabel);
}

void Renamer::setupConnections()
{
  // 工具栏 Actions
  connect(ui->actionAddFile, &QAction::triggered, this, &Renamer::doAddFile);
  connect(ui->actionAddFileFormDir, &QAction::triggered, this, &Renamer::doAddDir);
  connect(ui->actionClearFileList, &QAction::triggered, this, &Renamer::doClearFileList);

  // 监听项变化改变颜色
  connect(ui->fileTableWidget, &QTableWidget::itemChanged, this, &Renamer::doItemChanged);

  // Tab Widget
  setupConnectionsAll();      // 整体
  setupConnectionsReplace();  // 替换
  setupConnectionsAdd();      //添加
  setupConnectionsDelete();   // 删除
  setupConnectionsNumber();   // 序号
  setupConnectionsTemplate(); // 模板
  setupConnectionsTextMode(); // 文本模式
}

void Renamer::setupConnectionsAll()
{
  connect(ui->radioButtonAllCase, &QRadioButton::clicked, this, &Renamer::doAllCase);
  connect(ui->radioButtonNoCase, &QRadioButton::clicked, this, &Renamer::doNoCase);
  connect(ui->radioButtonFirstCase, &QRadioButton::clicked, this, &Renamer::doFirstCase);
  connect(ui->radioButtonRan, &QRadioButton::clicked, this, &Renamer::doRandom);
  connect(ui->radioButtonNumUp, &QRadioButton::clicked, this, &Renamer::doNumUp);
  connect(ui->comboBox_2, &QComboBox::editTextChanged, [this](const QString& text) {
    if (text.isEmpty()) {
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
          const auto itemOld = ui->fileTableWidget->item(i, 1);
          item->setText(
            text + itemOld->text().right(
              itemOld->text().size() - itemOld->text().lastIndexOf(".")));
        }
      }
    }
  });

  connect(ui->radioButtonNo, &QRadioButton::clicked, this, &Renamer::doNo);

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
                const auto oldItemStr = ui->fileTableWidget->item(i, 1)->text();
                if (const auto item = ui->fileTableWidget->item(i, 2);
                  item->text().contains(".")) {
                  const auto index = oldItemStr.lastIndexOf(".");
                  item->setText(oldItemStr.left(index) + "." + text);
                }

                if (const auto item = ui->fileTableWidget->item(i, 4)) {
                  item->setText("." + text);
                }
              }
            }
          });
}

void Renamer::setupConnectionsReplace() {}
void Renamer::setupConnectionsAdd() {}
void Renamer::setupConnectionsDelete() {}
void Renamer::setupConnectionsNumber() {}
void Renamer::setupConnectionsTemplate() {}
void Renamer::setupConnectionsTextMode() {}

void Renamer::closeEvent(QCloseEvent* event)
{
  emit WindowClose();
}

void Renamer::doAddFile()
{
  filesList = QFileDialog::getOpenFileNames(this, tr("添加文件"), "", "*.*");
  insertRows(ui->fileTableWidget);
  sLog.logf("批量重命名：添加了文件共：%d 条", filesList.size());
}

void Renamer::doAddDir()
{
  // 选择文件夹
  const QString dir = QFileDialog::getExistingDirectory(this, tr("添加文件来自文件夹"), "",
                                                        QFileDialog::ShowDirsOnly);
  if (dir.isEmpty())
    return;

  QDirIterator it(dir, QDir::Files, QDirIterator::Subdirectories);
  while (it.hasNext()) {
    const QString filePath = it.next();
    filesList.append(QFileInfo(filePath).absoluteFilePath());
  }

  insertRows(ui->fileTableWidget);
  sLog.logf("批量重命名：添加了文件共：%d 条", filesList.size());
  statusLabel->setText(QString("%1 条").arg(filesList.size()));
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
  // 只有第2列是变化的 判断和第一列是否不完全相等，如果是则改为红色，否则默认黑色
  if (item->column() == 2) {
    if (ui->fileTableWidget->item(item->row(), 1)->text() !=
      ui->fileTableWidget->item(item->row(), 2)->text()) {
      item->setForeground(QBrush(Qt::red));
    }
    else { item->setForeground(QBrush(Qt::black)); }
  }
}

void Renamer::doTextConversion(int conversionType)
{
  // 获取输入文本
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      QString inputText = item->text();
      QString outputText;

      // 根据选择执行相应的转换
      switch (conversionType) {
      case 1: // 简体转繁体
        outputText = convertSimplifiedToTraditional(inputText);
        break;
      case 2: // 繁体转简体
        outputText = convertTraditionalToSimplified(inputText);
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
  ui->comboBoxSuffix->setCurrentText("");
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 后缀全大写
    const auto oldItemStr = ui->fileTableWidget->item(i, 1)->text();
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) {
      const auto index = oldItemStr.lastIndexOf(".");
      item->setText(oldItemStr.left(index) + oldItemStr.right(oldItemStr.size()
        - index).toUpper());
    }
    if (const auto item = ui->fileTableWidget->item(i, 4)) {
      item->setText(oldItemStr.right(
        oldItemStr.size() - oldItemStr.lastIndexOf(".")).toUpper());
    }
  }
}

void Renamer::doSuffixNoCase()
{
  ui->comboBoxSuffix->setCurrentText("");
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 后缀全小写
    const auto oldItemStr = ui->fileTableWidget->item(i, 1)->text();
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) {
      const auto index = oldItemStr.lastIndexOf(".");
      item->setText(oldItemStr.left(index) + oldItemStr.right(oldItemStr.size()
        - index).toLower());
    }

    if (const auto item = ui->fileTableWidget->item(i, 4)) {
      item->setText(
        oldItemStr.right(oldItemStr.size() - oldItemStr.lastIndexOf(".")).
                   toLower());
    }
  }
}

void Renamer::doSuffixNo()
{
  ui->comboBoxSuffix->setCurrentText("");
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    const auto oldItem = ui->fileTableWidget->item(i, 1);
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) { item->setText(oldItem->text()); }
    if (const auto item = ui->fileTableWidget->item(i, 4)) {
      item->setText(oldItem->text().right(oldItem->text().size() -
        oldItem->text().lastIndexOf(".")));
    }
  }
}

void Renamer::doNumUp()
{
  ui->comboBox_2->setCurrentText("");
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 数字递增
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      const auto itemOld = ui->fileTableWidget->item(i, 1);
      item->setText(QString::number(i + 1) +
        itemOld->text().right(
          itemOld->text().size() - itemOld->text().lastIndexOf(".")));
    }
  }
}

void Renamer::doRandom()
{
  ui->comboBox_2->setCurrentText("");
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 随机数
    if (const auto item = ui->fileTableWidget->item(i, 2)) {
      const auto itemOld = ui->fileTableWidget->item(i, 1);
      const auto index = itemOld->text().lastIndexOf(".");
      item->setText(generateRandomString() +
        itemOld->text().right(itemOld->text().size() - index));
    }
  }
}

void Renamer::doFirstCase()
{
  ui->comboBox_2->setCurrentText("");
  // 首字母大写
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 后缀不变，其他字母变为首字母大写
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) {
      const auto itemOld = ui->fileTableWidget->item(i, 1);
      const auto index = itemOld->text().lastIndexOf(".");
      item->setText(itemOld->text().left(index).toLower().replace(0, 1,
          itemOld->text().left(index).toLower().at(0).toUpper()) +
        itemOld->text().right(itemOld->text().size() - index));
    }
    else {
      item->setText(item->text().toLower().replace(0, 1,
                                                   item->text().at(0).toUpper()));
    }
  }
}

void Renamer::doNoCase()
{
  ui->comboBox_2->setCurrentText("");
  // 全部字母小写
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 后缀不变，其他字母变为小写
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) {
      const auto itemOld = ui->fileTableWidget->item(i, 1);
      const auto index = itemOld->text().lastIndexOf(".");
      item->setText(itemOld->text().left(index).toLower() +
        itemOld->text().right(itemOld->text().size() - index));
    }
    else { item->setText(item->text().toLower()); }
  }
}

void Renamer::doAllCase()
{
  ui->comboBox_2->setCurrentText("");
  // 全部字母大写
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 后缀不变，其他字母变为大写
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text().contains(".")) {
      const auto itemOld = ui->fileTableWidget->item(i, 1);
      const auto index = itemOld->text().lastIndexOf(".");
      item->setText(itemOld->text().left(index).toUpper() +
        itemOld->text().right(itemOld->text().size() - index));
    }
    else { item->setText(item->text().toUpper()); }
  }
}

void Renamer::doNo()
{
  ui->comboBox_2->setCurrentText("");
  // 改回为第1列的文件名
  for (int i = 0; i < ui->fileTableWidget->rowCount(); ++i) {
    // 第二列文本变成第一列的文本
    if (const auto item = ui->fileTableWidget->item(i, 2);
      item->text() != ui->fileTableWidget->item(i, 1)->text()) {
      item->setText(ui->fileTableWidget->item(i, 1)->text());
    }
  }
}

void Renamer::insertRows(QTableWidget* widget)
{
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
    widget->setItem(row, 2, new QTableWidgetItem(fileInfo.fileName()));
    //widget->setItem(row, 3, new QTableWidgetItem(fileInfo));
    widget->setItem(row, 4, new QTableWidgetItem("." + fileInfo.suffix()));
    widget->setItem(row, 5,
                    new QTableWidgetItem(sDataUnitCalc.setDataUnit(fileInfo.size())));
    widget->setItem(row, 6, new QTableWidgetItem(fileInfo.filePath()));
  }
}

// 简体转繁体
QString Renamer::convertSimplifiedToTraditional(const QString& text)
{
  // opencc_t converter = opencc_open("s2t.json"); // 简体到繁体配置
  // if (converter == NULL) {
  //   QMessageBox::critical(this, tr("错误"), tr("无法初始化OpenCC转换器"));
  //   return text;
  // }
  //
  // std::string input = text.toStdString();
  // char* converted = opencc_convert_utf8(converter, input.c_str(), input.length());
  // QString result = QString::fromUtf8(converted);
  // opencc_convert_utf8_free(converted);
  // opencc_close(converter);
  //
  // return result;
  return QString();
}

// 繁体转简体
QString Renamer::convertTraditionalToSimplified(const QString& text)
{
  // opencc_t converter = opencc_open("t2s.json"); // 繁体到简体配置
  // if (converter == NULL) {
  //   QMessageBox::critical(this, tr("错误"), tr("无法初始化OpenCC转换器"));
  //   return text;
  // }
  //
  // std::string input = text.toStdString();
  // char* converted = opencc_convert_utf8(converter, input.c_str(), input.length());
  // QString result = QString::fromUtf8(converted);
  // opencc_convert_utf8_free(converted);
  // opencc_close(converter);
  //
  // return result;
  return QString();
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
    bool foundChineseNum = false;

    // 查找可能的中文数字序列
    if (chineseNumMap.find(result[i]) != chineseNumMap.end() ||
      chineseUnitMap.find(result[i]) != chineseUnitMap.end()) {
      int start = i;
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
        QChar ch = chineseNumStr[j];

        if (chineseNumMap.find(ch) != chineseNumMap.end()) {
          tempNum = chineseNumMap.at(ch);
        }
        else if (chineseUnitMap.find(ch) != chineseUnitMap.end()) {
          int unit = chineseUnitMap.at(ch);
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
      foundChineseNum = true;
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
    int num = numStr.toInt();
    if (num == 0) { chineseNumStr = simpleChineseNum[0]; }
    else {
      int unitGroupCount = 0;

      while (num > 0) {
        int groupValue = num % 10000;
        QString groupStr;

        if (groupValue > 0) {
          for (int i = 0; i < 4; i++) {
            int digit = groupValue % 10;
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

Renamer::~Renamer() { delete ui; }
