#pragma once

#include <qcustomplot.h>

#include <QtWidgets>
extern "C" {
#include "../backend/calc.h"
}

class QLineEdit;
class QLabel;
class QPushButton;
class QRegularExpressionValidator;
class QCustomPlot;

class Graph : public QWidget {
  Q_OBJECT

 private:
  QLineEdit* xMin;
  QLineEdit* xMax;
  QLineEdit* yMin;
  QLineEdit* yMax;
  QLabel* xMinLab;
  QLabel* xMaxLab;
  QLabel* yMinLab;
  QLabel* yMaxLab;
  QPushButton* clearButton;

 public:
  Graph(QWidget* pwgt = 0);
  QPushButton* drawButton;
  QCustomPlot* table;
  QLineEdit* getXmin() const;
  QLineEdit* getXmax() const;
  QLineEdit* getYmin() const;
  QLineEdit* getYmax() const;
  //    ~Graph();

 public slots:
  void slotButtonClicked();

 private:
  QPushButton* createButton(const QString& str);
  QCustomPlot* buildGraph();

 private slots:
  void zoomIn();
  void zoomOut();
};