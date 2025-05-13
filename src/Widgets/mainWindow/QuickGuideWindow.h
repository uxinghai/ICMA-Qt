/**
 * @file QuickGuideWindow.h
 *
 * @Breife None
 *
 * @version 1.0
 * @date 2025/5/13
 *
 * @author uxinghai
 * @copyright Copyright (c) 2025
 */

#pragma once

#include <QWidget>

class QTextBrowser;
class QLineEdit;
class QPushButton;

class QuickGuideWindow final : public QWidget {
  Q_OBJECT

public:
  explicit QuickGuideWindow(QWidget* parent = nullptr);
  void setHtmlContent(const QString& html) const;

private slots:
  void searchText() const;
  void exportToPdf();

private:
  QTextBrowser* textBrowser;
  QLineEdit* searchEdit;
  QPushButton* pdfButton;
  QPushButton *confirmButton;

  void highlightText(const QString& text) const;
  void clearHighlights() const;
};
