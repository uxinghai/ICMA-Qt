#include "QuickGuideWindow.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPainter>
#include <QPrinter>
#include <QPushButton>
#include <QTextBrowser>
#include <QTextCharFormat>
#include <QTextCursor>

#include "../../Utils/Tools/MyInformationBox.h"

QuickGuideWindow::QuickGuideWindow(QWidget* parent)
  : QWidget(parent)
{
  this->setWindowIcon(QIcon(":/icons/res/ShouCe.png"));
  this->setWindowTitle("快速入门指南");
  this->resize(800, 600);

  textBrowser = new QTextBrowser(this);
  searchEdit = new QLineEdit(this);
  pdfButton = new QPushButton("导出 PDF", this);
  confirmButton = new QPushButton("确定", this);
  const auto searchBtn = new QPushButton("搜索", this);

  const auto topLayout = new QHBoxLayout;
  topLayout->addWidget(searchEdit);
  topLayout->addWidget(searchBtn);
  topLayout->addWidget(pdfButton);

  const auto mainLayout = new QVBoxLayout(this);
  mainLayout->addLayout(topLayout);
  mainLayout->addWidget(textBrowser);

  const auto bottomLayout = new QHBoxLayout;
  bottomLayout->addStretch();
  bottomLayout->addWidget(confirmButton);

  mainLayout->addLayout(topLayout);
  mainLayout->addWidget(textBrowser);
  mainLayout->addLayout(bottomLayout);

  connect(confirmButton, &QPushButton::clicked, this, &QuickGuideWindow::close);
  connect(searchBtn, &QPushButton::clicked, this, &QuickGuideWindow::searchText);
  connect(pdfButton, &QPushButton::clicked, this, &QuickGuideWindow::exportToPdf);
}

void QuickGuideWindow::setHtmlContent(const QString& html) const
{
  textBrowser->setHtml(html);
}

void QuickGuideWindow::searchText() const
{
  const QString keyword = searchEdit->text();
  if (keyword.isEmpty()) {
    clearHighlights();
    return;
  }

  highlightText(keyword);
}

void QuickGuideWindow::highlightText(const QString& text) const
{
  QTextCursor cursor = textBrowser->textCursor();
  cursor.movePosition(QTextCursor::Start);

  const QTextCharFormat plainFormat(cursor.charFormat());
  QTextCharFormat highlightFormat = plainFormat;
  highlightFormat.setBackground(Qt::yellow);
  highlightFormat.setForeground(Qt::black);

  QTextDocument* document = textBrowser->document();
  cursor = QTextCursor(document);

  cursor.beginEditBlock();

  QTextCursor highlightCursor(document);
  while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
    highlightCursor = document->find(text, highlightCursor);
    if (!highlightCursor.isNull()) { highlightCursor.mergeCharFormat(highlightFormat); }
  }

  cursor.endEditBlock();
}

void QuickGuideWindow::clearHighlights() const
{
  QTextCursor cursor = textBrowser->textCursor();
  cursor.movePosition(QTextCursor::Start);

  QTextCharFormat clearFormat;
  clearFormat.setBackground(Qt::transparent);
  clearFormat.setForeground(Qt::black);

  QTextDocument* document = textBrowser->document();
  cursor = QTextCursor(document);

  cursor.beginEditBlock();

  QTextCursor highlightCursor(document);
  while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
    highlightCursor = document->find(searchEdit->text(), highlightCursor);
    if (!highlightCursor.isNull()) { highlightCursor.mergeCharFormat(clearFormat); }
  }

  cursor.endEditBlock();
}

void QuickGuideWindow::exportToPdf()
{
  const QString fileName = QFileDialog::getSaveFileName(this,
                                                        "导出为 PDF", "", "*.pdf");
  if (fileName.isEmpty())
    return;

  QPrinter printer(QPrinter::HighResolution);
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName(fileName);
  printer.setPageOrientation(QPageLayout::Portrait);

  textBrowser->document()->print(&printer);
  quickInformation->quickShow(this,"导出成功");
}
