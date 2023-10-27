#include "DifferCredit.h"

DifferCredit::DifferCredit(QWidget *pwgt) : QWidget(pwgt){
    QVBoxLayout* tableLo = new QVBoxLayout;
    table = new QTableWidget(1, 5, this);
    QStringList headers;
    headers << "Месяц" << "Погашение\nосновного долга" << "Погашение\nпроцента" << "Месячный\nплатеж" << "Остаток\nзадолженности";
    table->setHorizontalHeaderLabels(headers);
    for(int i = 0; i < table->columnCount(); ++i){
        QTableWidgetItem* item = table->item(0, i);
        if(item) item->setFont(QFont("Times New Roman", 12));
    }
    tableLo->addWidget(table);

    hideButton = new QPushButton("Hide");
    hideButton->setObjectName("creditbutton");
    cleanButton = new QPushButton("Clean");
    cleanButton->setObjectName("creditbutton");
    connect(cleanButton, SIGNAL(clicked()), this, SLOT(cleanButtonClicked()));
    QHBoxLayout* buttonsLo = new QHBoxLayout;
    buttonsLo->addWidget(cleanButton);
    buttonsLo->addWidget(hideButton);

    tableLo->addLayout(buttonsLo);
    setLayout(tableLo);
}

void DifferCredit::addRow(QString date, DiffNode diffNode){
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(row, 0, new QTableWidgetItem(date));
    table->setItem(row, 1, new QTableWidgetItem(QString::number(diffNode.mainPay, 'f', 2)));
    table->setItem(row, 2, new QTableWidgetItem(QString::number(diffNode.persentPay, 'f', 2)));
    table->setItem(row, 3, new QTableWidgetItem(QString::number(diffNode.monthPay, 'f', 2)));
    table->setItem(row, 4, new QTableWidgetItem(QString::number(diffNode.dept, 'f', 2)));
}

void DifferCredit::cleanButtonClicked(){
    table->setRowCount(0);
}