/**
* @file PS.h
 *
 * @brief none
 *
 *
 * @version 0.1
 * @date 2024.07.30
 *
 * @author uxinghai
 * @copyright Copyright (c) 2024
 */

#pragma once

#include <QUrl>
#include <QWidget>

QT_BEGIN_NAMESPACE

namespace Ui
{
  class PS;
}

QT_END_NAMESPACE

class PS final : public QWidget {
  Q_OBJECT

public:
  PS();
  ~PS() override;

private slots:
  static void doGetTokenReady(const QString& token);

private:
  void setupConnections();
  void getBaiduAIToken();

  Ui::PS* ui;
};
