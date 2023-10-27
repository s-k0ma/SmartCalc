#include "Deposit.h"

Deposit::Deposit(QWidget* pwgt/*= 0*/) : QWidget(pwgt){
    mainLayout = new QGridLayout;

    //виджеты пополнений
    bottomAddictions = new QVBoxLayout;
    QHBoxLayout* addictionsButLo = new QHBoxLayout;

    addAddictionBut = new QPushButton;
    addAddictionBut->setIcon(QIcon(":/add.png"));
    connect(addAddictionBut, SIGNAL(clicked()), this, SLOT(handleAddButton()));

    deleteAddictionBut = new QPushButton;
    deleteAddictionBut->setIcon(QIcon(":/delete.png"));
    connect(deleteAddictionBut, SIGNAL(clicked()), this, SLOT(handleDelButton()));
    addictions = new QStack<QHBoxLayout*>;

    QLabel* addictionsLab = new QLabel("Пополнения:");

    addictionsButLo->addWidget(addictionsLab);
    addictionsButLo->addWidget(addAddictionBut);
    addictionsButLo->addWidget(deleteAddictionBut);
    bottomAddictions->addLayout(addictionsButLo);


    //виджеты списаний
    bottomDecomission = new QVBoxLayout;
    QHBoxLayout* decomissionButLo = new QHBoxLayout;

    addDecomissionBut = new QPushButton;
    addDecomissionBut->setIcon(QIcon(":/add.png"));
    connect(addDecomissionBut, SIGNAL(clicked()), this, SLOT(handleAddButton()));

    deleteDecomissionBut = new QPushButton;
    deleteDecomissionBut->setIcon(QIcon(":/delete.png"));
    connect(deleteDecomissionBut, SIGNAL(clicked()), this, SLOT(handleDelButton()));
    decomissions = new QStack<QHBoxLayout*>;

    QLabel* decomissionLab = new QLabel("Списания:");

    decomissionButLo->addWidget(decomissionLab);
    decomissionButLo->addWidget(addDecomissionBut);
    decomissionButLo->addWidget(deleteDecomissionBut);
    bottomDecomission->addLayout(decomissionButLo);

    //сумма вклада
    QLabel* startDepositLab = new QLabel("Сумма вклада: ");
    startDeposit = new QLineEdit;
    startDeposit->setPlaceholderText("Сумма вклада:");
    QRegularExpression regex("(?:\\d*\\.?\\d+)");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex);
    startDeposit->setValidator(validator);
    QHBoxLayout* startLo = new QHBoxLayout;
    startLo->addWidget(startDepositLab);
    startLo->addWidget(startDeposit);

    //срок размещения
    QLabel* periodLab = new QLabel("Срок размещения: ");
    periodDepost = new QLineEdit;
    periodDepost->setPlaceholderText("Срок вклада:");
    periodDepost->setValidator(validator);
    periodType = new QPushButton("Лет");
    QMenu* pmnu = new QMenu(periodType);
    pmnu->addAction("Лет");
    pmnu->addAction("Месяцев");
    periodType->setMenu(pmnu);
    connect(pmnu, SIGNAL(triggered(QAction*)), this, SLOT(menuPointClicked(QAction*)));
    QHBoxLayout* periodLo = new QHBoxLayout;
    periodLo->addWidget(periodLab);
    periodLo->addWidget(periodDepost);
    periodLo->addWidget(periodType);

    //ставка вклада и налоговая
    QLabel* rateLab = new QLabel("Ставка %");
    rate = new QLineEdit;
    rate->setPlaceholderText("%");
    rate->setValidator(validator);
    QLabel* taxLab = new QLabel("Налог %");
    tax = new QLineEdit;
    tax->setPlaceholderText("%");
    tax->setValidator(validator);
    QHBoxLayout* taxesLo = new QHBoxLayout;
    taxesLo->addWidget(rateLab);
    taxesLo->addWidget(rate);
    taxesLo->addWidget(taxLab);
    taxesLo->addWidget(tax);

    //периодичность и капитализация
    dividensLab = new QLabel("Периодичность выплат ");
    dividends = new QPushButton("в конце срока");
    QMenu* divmnu = new QMenu(dividends);
    divmnu->addAction("в конце срока");
    divmnu->addAction("каждый месяц");
    divmnu->addAction("раз в год");
    dividends->setMenu(divmnu);
    connect(divmnu, SIGNAL(triggered(QAction*)), this, SLOT(menuPointClicked(QAction*)));
    capitalization = new QCheckBox("Капитализация %");
    connect(capitalization, SIGNAL(stateChanged(int)), this, SLOT(handleCheckBox(int)));
    QHBoxLayout* dividendsLo = new QHBoxLayout;
    dividendsLo->addWidget(dividensLab);
    dividendsLo->addWidget(dividends);
    dividendsLo->addWidget(capitalization);

    //Вывод расчетов
    totalPercent = new QLabel("Начисленные проценты: ");
    totalTax = new QLabel("Налог: ");
    totalSumm = new QLabel("Итоговая сумма: ");
    QVBoxLayout* totalLo = new QVBoxLayout;
    totalLo->addWidget(totalPercent);
    totalLo->addWidget(totalTax);
    totalLo->addWidget(totalSumm);

    //итоги
    depositReport = new DepositReport;
    calculate = new QPushButton("Рассчитать");
    connect(calculate, SIGNAL(clicked()), this, SLOT(handleCalculateButton()));
    showGraphBut = new QPushButton("Show Graph");
    showGraphBut->hide();
    QHBoxLayout* butsLo = new QHBoxLayout;
    butsLo->addWidget(calculate);
    butsLo->addWidget(showGraphBut);

    //Компоновка окна
    mainLayout->addLayout(startLo, 0, 0);
    mainLayout->addLayout(periodLo, 1, 0);
    mainLayout->addLayout(taxesLo, 2, 0);
    mainLayout->addLayout(dividendsLo, 3, 0);
    mainLayout->addLayout(bottomAddictions, 4, 0);
    mainLayout->addLayout(bottomDecomission, 5, 0);
    mainLayout->addLayout(totalLo, 6, 0);
    mainLayout->addLayout(butsLo,7,0);

    setLayout(mainLayout);
}

void Deposit::addDecommision(){
    QHBoxLayout* decomissionLo = new QHBoxLayout;
    QRegularExpression regex("(?:\\d*\\.?\\d+)");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex);
    QLabel* decomissionLab = new QLabel("Списание");
    QLineEdit* decomissionInp = new QLineEdit;
    decomissionInp->setValidator(validator);
    decomissionInp->setPlaceholderText("Сумма списания:");
    QLineEdit* decomissionDate = new QLineEdit;
    decomissionDate->setPlaceholderText("дата \"ДД.ММ.ГГГГ\"");

    decomissionLo->addWidget(decomissionLab);
    decomissionLo->addWidget(decomissionInp);
    decomissionLo->addWidget(decomissionDate);

    bottomDecomission->addLayout(decomissionLo);
    decomissions->push(decomissionLo);
}

void Deposit::deleteDecommision(){
    if(!decomissions->isEmpty()){
        QHBoxLayout* layout = decomissions->pop();
        QLayoutItem* item;
        while ((item = layout->takeAt(0)) != 0) {
            if (QWidget* widget = item->widget()) {
                layout->removeWidget(widget);
                delete widget;
            }
            delete item;
       }
        delete layout;
   }
}

void Deposit::addAddiction() {
    QHBoxLayout* addictionLo = new QHBoxLayout;
    QRegularExpression regex("(?:\\d*\\.?\\d+)");
    QRegularExpression regDate("^(0[1-9]|[12][0-9]|3[01])\\.(0[1-9]|1[0-2])\\.\\d{4}$");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex);
    QRegularExpressionValidator* dateVal = new QRegularExpressionValidator(regDate);
    QLabel* addictionLab = new QLabel("Пополнение");
    QLineEdit* addictionInp = new QLineEdit;
    addictionInp->setValidator(validator);
    addictionInp->setPlaceholderText("Сумма пополнения:");
    QLineEdit* addictionDate = new QLineEdit;
    addictionDate->setValidator(dateVal);
    addictionDate->setPlaceholderText("дата \"ДД.ММ.ГГГГ\"");

    addictionLo->addWidget(addictionLab);
    addictionLo->addWidget(addictionInp);
    addictionLo->addWidget(addictionDate);

    bottomAddictions->addLayout(addictionLo);
    addictions->push(addictionLo);
}

void Deposit::deleteAddiction() {
    if (!addictions->isEmpty()) {
        QHBoxLayout *layout = addictions->pop();
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != 0) {
            if (QWidget *widget = item->widget()) {
                layout->removeWidget(widget);
                delete widget;
            }
            delete item;
        }
        delete layout;
    }
}

void Deposit::handleDelButton() {
    QObject* senderObject = sender();

    if (senderObject == deleteDecomissionBut) {
        deleteDecommision();
    } else if (senderObject == deleteAddictionBut) {
        deleteAddiction();
    }
}

void Deposit::handleAddButton() {
    QObject* senderObject = sender();

    if (senderObject == addDecomissionBut) {
        addDecommision();
    } else if (senderObject == addAddictionBut) {
        addAddiction();
    }
}

void Deposit::menuPointClicked(QAction* action) {
    if(action->text() == "Лет"){
        periodType->setText("Лет");
    }else if(action->text() == "Месяцев"){
        periodType->setText("Месяцев");
    }else if(action->text() == "в конце срока"){
        dividends->setText("в конце срока");
    }else if(action->text() == "каждый месяц"){
        dividends->setText("каждый месяц");
    }else if(action->text() == "раз в год"){
        dividends->setText("раз в год");
    }
}

void Deposit::handleCheckBox(int state){
    if(state == Qt::Checked){
        dividensLab->setText("Периодичность капитализации ");
        dividends->setText("каждый месяц");
    }else if(state == Qt::Unchecked){
        dividensLab->setText("Периодичность выплат ");
    }
}

void Deposit::handleCalculateButton(){
    if(checkLines()){
        double rateVal = rate->text().toDouble() / 100;
        double taxVal = tax->text().toDouble() / 100;
        int periodVal = 0;
        int capital = 0;

        if(capitalization->checkState() == Qt::Checked) capital = 1;

        if(periodType->text() == "Лет"){
            periodVal = periodDepost->text().toInt() * 12;
        }else if(periodType->text() == "Месяцев"){
            periodVal = periodDepost->text().toInt();
        }
        DebetNode* debetNode = (DebetNode*)calloc((periodVal+1), sizeof(DebetNode));
        debetNode[0].balance = startDeposit->text().toDouble();

        if(!decomissions->isEmpty() || !addictions->isEmpty()){
            if(writeChanges(&debetNode, periodVal) != 1) QMessageBox::critical(this, "error", "form filled incorrect");;
        } else for(int i = 0; i < periodVal; i++) debetNode[i].balanceChange = 0;
        standartDeposit(rateVal, periodVal, capital, &debetNode);
        totalPercent->setText("Сумма дохода: " + QString::number(debetNode[periodVal].payment, 'f', 2));
        totalSumm->setText("Итоговая сумма:" + QString::number(debetNode[periodVal].balance, 'f', 2));
        totalTax->setText("Налог: " + QString::number(calculateTax(&debetNode[periodVal].balance, taxVal), 'f', 2));

        QDate currentDate = QDate::currentDate();
        depositReport->table->setRowCount(0); // Clear the existing table content
        depositReport->table->setRowCount(periodVal); // Set the row count

        for(int i = 0; i < periodVal; i++){
            depositReport->table->setItem(i, 0, new QTableWidgetItem(currentDate.toString("MMMM")));
            depositReport->table->setItem(i, 1, new QTableWidgetItem(QString::number(debetNode[i].percentCharged, 'f', 2)));
            depositReport->table->setItem(i, 2, new QTableWidgetItem(QString::number(debetNode[i].balanceChange, 'f', 2)));
            depositReport->table->setItem(i, 3, new QTableWidgetItem(QString::number(debetNode[i].payment, 'f', 2)));
            depositReport->table->setItem(i, 4, new QTableWidgetItem(QString::number(debetNode[i].balance, 'f', 2)));
            currentDate = currentDate.addMonths(1);
        }
        free(debetNode);
        showGraphBut->show();
    }else QMessageBox::critical(this, "error", "form filled incorrect");
}

int Deposit::checkLines(){
    int result = 1;
    if(startDeposit->text().isEmpty() || periodDepost->text().isEmpty()||
    rate->text().isEmpty() || tax->text().isEmpty()){
        result = 0;
    }
    return result;
}

int Deposit::writeChanges(DebetNode** debetNode, int periodVal){
    int result = 0;
    for(int i = 0; i < periodVal; i++) (*debetNode)[i].balanceChange = 0;
    while(!addictions->isEmpty()){
        QHBoxLayout *layout = addictions->pop();
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(layout->itemAt(1)->widget());
        QLineEdit *dateEdit = qobject_cast<QLineEdit *>(layout->itemAt(2)->widget());

        (*debetNode)[monthsBetweenDates(dateEdit->text())].balanceChange += lineEdit->text().toDouble();
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != 0) {
            if (QWidget *widget = item->widget()) {
                layout->removeWidget(widget);
                delete widget;
            }
            delete item;
        }
        delete layout;
    }

    while(!decomissions->isEmpty()){
        QHBoxLayout *layout = decomissions->pop();
        QLineEdit *lineEdit = qobject_cast<QLineEdit *>(layout->itemAt(1)->widget());
        QLineEdit *dateEdit = qobject_cast<QLineEdit *>(layout->itemAt(2)->widget());

        (*debetNode)[monthsBetweenDates(dateEdit->text())].balanceChange += (lineEdit->text().toDouble()* -1);
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != 0) {
            if (QWidget *widget = item->widget()) {
                layout->removeWidget(widget);
                delete widget;
            }
            delete item;
        }
        delete layout;
    }
    result = 1;
    return result;
}

int Deposit::monthsBetweenDates(const QString& dateString) {
    QDate currentDate = QDate::currentDate();

    QStringList dateParts = dateString.split('.');
    if (dateParts.size() != 3) {
        return -1;
    }

    int day = dateParts[0].toInt();
    int month = dateParts[1].toInt();
    int year = dateParts[2].toInt();

    QDate givenDate(year, month, day);

    int years = givenDate.year() - currentDate.year();
    int months = givenDate.month() - currentDate.month();

    int totalMonths = (years * 12) + months;

    return totalMonths;
}