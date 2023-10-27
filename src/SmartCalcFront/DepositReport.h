#pragma once

#include <QtWidgets>
extern "C" {
#include "../backend/bank.h"
}

class QPushButton;
class QTableWidget;

class DepositReport : public QWidget {
  Q_OBJECT
 private:
  QPushButton* cleanButton;

 private slots:
  void cleanButtonClicked();

 public:
  DepositReport(QWidget* pwgt = 0);
  QTableWidget* table;
  QPushButton* hideButton;
  void addRow(QString date, DebetNode debetNode);
};
