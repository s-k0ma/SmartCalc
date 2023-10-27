#include "MainWindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget* pwgt/*= 0*/) : QMainWindow(pwgt) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setWindowTitle("Smart Calc v1.0 by Opresspa");

    QHBoxLayout* mainLo = new QHBoxLayout(centralWidget);
    calculator = new Calculator;
    connect(calculator, &Calculator::graphButtonClicked, this, &MainWindow::handleGraphButton);

    graph = new Graph;
    connect(graph->drawButton, SIGNAL(clicked()), this, SLOT(handleDrawButton()));
    graph->hide();

    mainLo->addWidget(calculator);
    mainLo->addWidget(graph);

    credit = new Credit;

    connect(credit->calculate, SIGNAL(clicked()),this, SLOT(handleCalculateButton()));
    mainLo->addWidget(credit);

    differCredit = new DifferCredit;
    connect(differCredit->hideButton, SIGNAL(clicked()),this, SLOT(handleHideButton()));
    differCredit->hide();
    mainLo->addWidget(differCredit);

    deposit = new Deposit;
    deposit->depositReport->hide();
    connect(deposit->showGraphBut, SIGNAL(clicked()), this, SLOT(showDepositReportButton()));
    connect(deposit->depositReport->hideButton, SIGNAL(clicked()), this, SLOT(hideDepositReportButton()));
    mainLo->addWidget(deposit);
    mainLo->addWidget(deposit->depositReport);


    QTabWidget* tab = new QTabWidget(this);
    tab->addTab(calculator, "Calc");
    tab->addTab(deposit, "Deposit");
    tab->addTab(credit, "Credit");

    QFile styleFile(":/styles.css");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&styleFile);
        QString styleSheet = in.readAll();
        styleFile.close();

        setStyleSheet(styleSheet);
    } else {
        qDebug() << "File do not open" << styleFile.errorString();
    }

    mainLo->addWidget(tab);
}

void MainWindow::handleGraphButton() {
    if (graph) {
        bool isVisible = graph->isVisible();
        graph->setVisible(!isVisible);

        if (isVisible) {
            graph->hide();
            setFixedSize(QSize(calculator->width(), height()));
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        } else {
            graph->show();
            setFixedSize(QSize(1172, height()));
            setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        }
    }
}

void MainWindow::handleHideButton() {
    if(differCredit){
        differCredit->hide();
        setFixedSize(credit->width(), height());
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
}

void MainWindow::handleDrawButton(){

    QString str = ((QPushButton*)sender())->text();
    if(str.contains("draw")) {
            if (!calculator->getInputExp()->text().isEmpty()) {
            Axises *praxis = drawingGraph(calculator->getInputExp()->text().toLocal8Bit().data(),
                                          graph->getXmax()->text().isEmpty() ? 10 : graph->getXmax()->text().toDouble(),
                                          graph->getXmin()->text().isEmpty() ? -10 : graph->getXmin()->text().toDouble());
            if (praxis != NULL) {
                QVector<double> xDataVector;
                QVector<double> yDataVector;
                for (int i = 0; i < 1000; i++) {
                    xDataVector.append(praxis->axisX[i]);
                    yDataVector.append(praxis->axisY[i]);
                }
                graph->table->xAxis->setRange(graph->getXmin()->text().toDouble(), graph->getXmax()->text().toDouble());
                graph->table->yAxis->setRange(graph->getYmin()->text().toDouble(), graph->getYmax()->text().toDouble());
                graph->table->graph(0)->setData(xDataVector, yDataVector);
                graph->table->graph(0)->setPen(QPen(Qt::darkMagenta));
                graph->table->replot();
                destroyAxises(praxis);
            }
        }
    }
}

void MainWindow::handleCalculateButton(){
    QString str = ((QPushButton*)sender())->text();

    if(str == "Рассчитать") {
        if(credit->getLoan().isEmpty() || credit->getPeriod().isEmpty() || credit->getRate().isEmpty()){
            QMessageBox::critical(this, "error", "form filled incorrect");
        }else {
            int timePeriod = 0;
            double request = credit->getLoan().toDouble();
            double percent = credit->getRate().toDouble();
            if (credit->getPeriodType() == "Лет") {
                timePeriod = credit->getPeriod().toInt() * 12;
            }
            if (credit->getPeriodType()  == "Месяцев") {
                timePeriod = credit->getPeriod().toInt();
            }

            double monthlyPl = 0;
            double overpaymentPl = 0;
            double totalPl = 0;

            if (credit->getType() == "Аннуитетный") {
                annuityCredit(request, timePeriod, percent,
                              &monthlyPl, &overpaymentPl, &totalPl);
                credit->answer(QString::number(monthlyPl, 'f', 2),
                               QString::number(overpaymentPl, 'f', 2),
                               QString::number(totalPl, 'f', 2));

            } else if (credit->getType() == "Дифференцированный") {
                differCredit->show();
                setFixedSize(QSize(1172, height()));

                DiffNode* diffNode = differentialPayment(request, percent, timePeriod);
                QDate currentDate = QDate::currentDate();

                for(int i = 0; i < timePeriod; i++){
                    differCredit->addRow(currentDate.toString("MMMM"), diffNode[i]);
                    currentDate = currentDate.addMonths(1);
                }
                free(diffNode);
            }
        }
    }
}

void MainWindow::showDepositReportButton(){
    if (deposit){
        deposit->depositReport->show();
        setFixedSize(QSize(1172, height()));
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
}

void MainWindow::hideDepositReportButton(){
    if (deposit->depositReport){
        deposit->depositReport->hide();
        setFixedSize(QSize(deposit->width(), height()));
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    }
}