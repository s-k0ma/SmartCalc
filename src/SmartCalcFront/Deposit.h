#pragma once

#include <QtWidgets>

#include "DepositReport.h"
extern "C" {
#include "../backend/bank.h"
}

class QLabel;
class QLineEdit;
class QPushButton;
class QCheckBox;
class DepositReport;

class Deposit : public QWidget {
  Q_OBJECT
 public:
  Deposit(QWidget* pwgt = 0);
  QPushButton* showGraphBut;
  DepositReport* depositReport;

 private:
  QPushButton* calculate;
  QPushButton* addDecomissionBut;
  QPushButton* deleteDecomissionBut;
  QPushButton* addAddictionBut;
  QPushButton* deleteAddictionBut;
  QPushButton* periodType;
  QLineEdit* startDeposit;
  QLineEdit* periodDepost;
  QLineEdit* rate;
  QLineEdit* tax;
  QLabel* dividensLab;
  QPushButton* dividends;
  QCheckBox* capitalization;
  QLabel* totalPercent;
  QLabel* totalTax;
  QLabel* totalSumm;
  QStack<QHBoxLayout*>* decomissions;
  QStack<QHBoxLayout*>* addictions;
  QVBoxLayout* bottomDecomission;
  QVBoxLayout* bottomAddictions;
  QGridLayout* mainLayout;
  void addDecommision();
  void deleteDecommision();
  void addAddiction();
  void deleteAddiction();
  int checkLines();
  int writeChanges(DebetNode** debetNode, int periodVal);
  int monthsBetweenDates(const QString& dateString);

 private slots:
  void handleDelButton();
  void handleAddButton();
  void menuPointClicked(QAction* action);
  void handleCheckBox(int state);
  void handleCalculateButton();
};
