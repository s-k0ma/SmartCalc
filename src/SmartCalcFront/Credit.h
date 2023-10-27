#pragma once

#include <QtWidgets>
extern "C" {
#include "../backend/bank.h"
}

class QLineEdit;
class QPushButton;
class QLabel;

class Credit : public QWidget {
  Q_OBJECT
 private:
  QLineEdit* loan;
  QLineEdit* period;
  QLineEdit* rate;
  QPushButton* periodButton;
  QLabel* total;
  QLabel* monthly;
  QLabel* overpayment;
  QPushButton* type;

 public:
  Credit(QWidget* pwgt = 0);
  QPushButton* calculate;
  QString getLoan();
  QString getPeriod();
  QString getRate();
  QString getType();
  QString getPeriodType();
  void answer(QString monthlyAns, QString overpaymentAns, QString totalAns);

 private slots:
  void menuPointClicked(QAction* action);
};
