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

class QTableWidgetItem;
class QLabel;
class QTableWidget;
QT_BEGIN_NAMESPACE

namespace Ui
{
  class Renamer;
}

QT_END_NAMESPACE

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
  void doAllCase();
  void doNo();

  // 替换

private:
  void initUI();
  void setupConnections();
  void setupConnectionsAll();
  void setupConnectionsReplace();
  void setupConnectionsAdd();
  void setupConnectionsDelete();
  void setupConnectionsNumber();
  void setupConnectionsTemplate();
  void setupConnectionsTextMode();
  void insertRows(QTableWidget* widget);
  void clearContentAndStruct(QTableWidget* widget);

  QString convertSimplifiedToTraditional(const QString& text); ///< 简体转繁体
  QString convertTraditionalToSimplified(const QString& text); ///< 繁体转简体
  QString convertChineseNumToArabic(const QString& text);      ///< 中文数字转阿拉伯数字
  QString convertArabicNumToChinese(const QString& text);      ///< 阿拉伯数字转中文数字

  static QString generateRandomString(int length = 32);

  Ui::Renamer* ui;
  QStringList filesList;
  QLabel* statusLabel;
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
