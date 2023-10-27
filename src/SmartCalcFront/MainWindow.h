#pragma once

#include <QMainWindow>

#include "Calculator.h"
#include "Credit.h"
#include "Deposit.h"
#include "DifferCredit.h"
#include "Graph.h"

class Calculator;
class Graph;
class QPushButton;
class Credit;
class DifferCredit;
class Deposit;

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* pwgt = 0);

 public slots:
  void handleGraphButton();
  void handleDrawButton();
  void handleCalculateButton();
  void handleHideButton();
  void showDepositReportButton();
  void hideDepositReportButton();

 private:
  Calculator* calculator;
  Graph* graph;
  Credit* credit;
  DifferCredit* differCredit;
  Deposit* deposit;
  QWidget* centralWidget;
};
