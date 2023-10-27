#pragma once

#include <QtWidgets>
extern "C" {
#include "../backend/calc.h"
}
class QLineEdit;
class QPushButton;
class QRegularExpressionValidator;

class Calculator : public QWidget {
  Q_OBJECT

 private:
  QLineEdit* m_plcd;
  QLineEdit* x_plcd;
  QString m_strDisplay;
  QString x_strDisplay;

 public:
  Calculator(QWidget* pwgt = 0);
  QPushButton* createButton(const QString& str);
  QLineEdit* getInputExp() const;
  ~Calculator();

 protected:
  void keyPressEvent(QKeyEvent* event) override;

 signals:
  void graphButtonClicked();

 public slots:
  void slotButtonClicked();
};
