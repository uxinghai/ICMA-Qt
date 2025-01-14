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

#include <QWidget>

inline QString API_KEY = "AXpJSMWfCfUzd0omZJheU7QZ";
inline QString SECRET_KEY = "TidB30gDa9QTdFIVqpjeN8ced15JMdmX";
static QString Token;

class GetBaiduTokenWorker;
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
  GetBaiduTokenWorker* getBaiduTokenWorker;

};
