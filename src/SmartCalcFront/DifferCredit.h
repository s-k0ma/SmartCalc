#pragma once

#include <QtWidgets>
extern "C" {
#include "../backend/bank.h"
}

class QPushButton;
class QTableWidget;

class DifferCredit : public QWidget {
  Q_OBJECT
 private:
  QTableWidget* table;
  QPushButton* cleanButton;

 private slots:
  void cleanButtonClicked();

 public:
  DifferCredit(QWidget* pwgt = 0);
  QPushButton* hideButton;
  void addRow(QString date, DiffNode diffNode);
};
