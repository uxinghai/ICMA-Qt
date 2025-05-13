/**
 * @file Renamer.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/5/5
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QMainWindow>
#include <qrandom.h>

QT_BEGIN_NAMESPACE
class QTableWidgetItem;
class QLabel;
class QTableWidget;
class QToolButton;

namespace Ui
{
  class Renamer;
}

QT_END_NAMESPACE

template <class T>
class MyVector : public QVector<T> {
public:
  qsizetype size() const { return QVector<T>::size(); }

  bool isEmpty() const { return QVector<T>::isEmpty(); }

  void push_back(const T& value)
  {
    while (size() > 30) { QVector<T>::pop_front(); }
    QVector<T>::push_back(value);
  }
};

class Renamer final : public QMainWindow {
  Q_OBJECT

public:
  explicit Renamer(QWidget* parent = nullptr);
  ~Renamer() override;

signals:
  void WindowClose();

protected:
  void closeEvent(QCloseEvent* event) override;

private slots:
  void doAddFile();
  void doAddDir();
  void doClearFileList();
  void doItemChanged(QTableWidgetItem* item);
  void doUndo();
  void doConfirm();

  // 处理文本转换
  void doTextConversion(int conversionType);

  // 整体
  void doSuffixAllCase();
  void doSuffixNoCase();
  void doSuffixNo();
  void doNumUp();
  void doRandom();
  void doFirstCase();
  void doNoCase();
  void doAllCase() const;
  void doNo();

  // 替换
  void doReplace();

  // 添加
  void doAddSuffixPreFix(const bool& addToNowText = false);
  void doAddToIndex();
  void doAddTextTo();

  // 删除
  void doDeleteText(const QString& text);
  void doDelete();
  void onCheckBoxStateChanged(int state);
  void doDeleteIndex();

  // 序号
  void doNumberlise();

private:
  void initUI();
  void setupConnections();
  void setupConnectionsAll();
  void setupConnectionsReplace();
  void setupConnectionsAdd();
  void setupConnectionsDelete();
  void setupConnectionsNumber();

  void reapplyRemainingFilters();
  void insertRows(QTableWidget* widget);
  void clearContentAndStruct(QTableWidget* widget);
  void setupCustomMenu();

  QString convertSimplifiedToTraditional(const QString& text); ///< 简体转繁体
  QString convertTraditionalToSimplified(const QString& text); ///< 繁体转简体
  QString convertChineseNumToArabic(const QString& text);      ///< 中文数字转阿拉伯数字
  QString convertArabicNumToChinese(const QString& text);      ///< 阿拉伯数字转中文数字

  static QString generateRandomString(int length = 32);

  Ui::Renamer* ui;
  QStringList filesList;
  QLabel* statusLabel;
  QToolButton* confirmButton;

  std::map<std::string, std::function<std::string()>> map;

  MyVector<QStringList> history;
  QVector<QString> tempHistory;

  QMap<QString, QVector<QString>> checkBoxStates; ///< 存储每个复选框对应的文件名状态
};

inline QString Renamer::generateRandomString(const int length)
{
  const QString charset = "abcdefghijklmnopqrstuvwxyz0123456789";
  QString result;
  result.reserve(length);

  for (int i = 0; i < length; ++i) {
    const int index = QRandomGenerator::global()->bounded(charset.size());
    result.append(charset.at(index));
  }

  return result;
}
