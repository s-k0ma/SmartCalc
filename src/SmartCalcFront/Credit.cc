#include "Credit.h"

Credit::Credit(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    QVBoxLayout* calcLayout = new QVBoxLayout;
    QGridLayout* leftLayout = new QGridLayout;
    QHBoxLayout* bottomLayout = new QHBoxLayout;

    total = new QLabel("Total payment:");
    total->setObjectName("creditLabel");
    overpayment = new QLabel("Overpayment:");
    overpayment->setObjectName("creditLabel");
    monthly = new QLabel("Monthly payment:");
    monthly->setObjectName("creditLabel");

    QRegularExpression regex("(?:\\d*\\.?\\d+)");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex);
    QLabel* labLoan = new QLabel("Сумма:");
    loan = new QLineEdit;
    loan->setValidator(validator);
    loan->setObjectName("creditInput");
    QLabel* labPeriod = new QLabel("Срок\nкредита:");
    period = new QLineEdit;
    period->setValidator(validator);
    period->setObjectName("creditInput");
    QLabel* labRate = new QLabel("Cтавка:");
    rate = new QLineEdit;
    rate->setValidator(validator);
    rate->setObjectName("creditInput");

    type = new QPushButton("Аннуитетный");
    type->setObjectName("creditbutton");
    QMenu* pmnu = new QMenu(type);
    pmnu->addAction("Аннуитетный");
    pmnu->addAction("Дифференцированный");
    type->setMenu(pmnu);
    connect(pmnu, SIGNAL(triggered(QAction*)), this, SLOT(menuPointClicked(QAction*)));

    calculate = new QPushButton("Рассчитать");
    calculate->setObjectName("creditbutton");

    periodButton = new QPushButton("Лет");
    periodButton->setObjectName("creditbutton");
    QMenu* periodMnu = new QMenu(type);
    periodMnu->addAction("Лет");
    periodMnu->addAction("Месяцев");
    periodButton->setMenu(periodMnu);
    connect(periodMnu, SIGNAL(triggered(QAction*)), this, SLOT(menuPointClicked(QAction*)));

    leftLayout->addWidget(labLoan, 0, 0);
    leftLayout->addWidget(loan, 0, 1);
    leftLayout->addWidget(labPeriod, 1, 0);
    leftLayout->addWidget(period,1,1);
    leftLayout->addWidget(periodButton,1,2);
    leftLayout->addWidget(labRate,2,0);
    leftLayout->addWidget(rate,2,1);
    bottomLayout->addWidget(type);
    bottomLayout->addWidget(calculate);

    calcLayout->addLayout(leftLayout);
    calcLayout->addLayout(bottomLayout);
    calcLayout->addWidget(monthly);
    calcLayout->addWidget(overpayment);
    calcLayout->addWidget(total);

    setLayout(calcLayout);
}

void Credit::menuPointClicked(QAction* action) {
    if(action->text() == "Лет"){
        periodButton->setText("Лет");
    }else if(action->text() == "Месяцев"){
        periodButton->setText("Месяцев");
    }else if(action->text() == "Аннуитетный"){
        type->setText("Аннуитетный");
    }else if(action->text() == "Дифференцированный"){
        type->setText("Дифференцированный");
    }
}

QString Credit::getLoan(){
    return loan->text();
}
QString Credit::getPeriod(){
    return period->text();
}
QString Credit::getRate(){
    return rate->text();
}

QString Credit::getType(){
    return type->text();
}

QString Credit::getPeriodType(){
    return periodButton->text();
}

void Credit::answer(QString monthlyAns, QString overpaymentAns, QString totalAns){
    monthly->setText("Monthly payment: " + monthlyAns);
    overpayment->setText("Overpayment: " + overpaymentAns);
    total->setText("Total payment: " + totalAns);
}
