#include "Graph.h"
#include <QGridLayout>
#include <QTransform>
#include <QtMath>
#include "Calculator.h"

Graph::Graph(QWidget* pwgt) : QWidget(pwgt) {

    table = buildGraph();

    QGridLayout* mainLayout = new QGridLayout;
    QVBoxLayout* rightLayout = new QVBoxLayout;
    QHBoxLayout* topLayout = new QHBoxLayout;
    QHBoxLayout* bottomLayout = new QHBoxLayout;

    QRegularExpression regex("[-]?\\d*\\.?\\d+");
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(regex);

    // Create labels and input fields
    xMinLab = new QLabel("min x:");
    xMin = new QLineEdit;
    xMin->setText(QString::number(-10));
    xMin->setValidator(validator);
    xMaxLab = new QLabel("max x:");
    xMax = new QLineEdit;
    xMax->setText(QString::number(10));
    xMax->setValidator(validator);
    yMinLab = new QLabel("min y:");
    yMin = new QLineEdit;
    yMin->setText(QString::number(-5));
    yMin->setValidator(validator);
    yMaxLab = new QLabel("max y:");
    yMax = new QLineEdit;
    yMax->setText(QString::number(5));
    yMax->setValidator(validator);

    // Add the labels and input fields to the top layout
    topLayout->addWidget(xMinLab);
    topLayout->addWidget(xMin);
    topLayout->addWidget(xMaxLab);
    topLayout->addWidget(xMax);
    topLayout->addWidget(yMinLab);
    topLayout->addWidget(yMin);
    topLayout->addWidget(yMaxLab);
    topLayout->addWidget(yMax);

    // Add the top layout and QCustomPlot to the right layout
    rightLayout->addLayout(topLayout);
    rightLayout->addWidget(table);

    // Create buttons and add them to the bottom layout
    drawButton = createButton("draw");
    clearButton = createButton("clear");
    QPushButton* zoomInButton = new QPushButton(this);
    zoomInButton->setObjectName("zoomButton");
    zoomInButton->setIcon(QIcon(":/zoomin.png"));
    QPushButton* zoomOutButton = new QPushButton(this);
    zoomOutButton->setObjectName("zoomButton");
    zoomOutButton->setIcon(QIcon(":/zoomout.png"));
    connect(zoomInButton, &QPushButton::clicked, this, &Graph::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &Graph::zoomOut);


    bottomLayout->addWidget(drawButton);
    bottomLayout->addWidget(clearButton);
    bottomLayout->addWidget(zoomInButton);
    bottomLayout->addWidget(zoomOutButton);

    // Add the bottom layout to the right layout
    rightLayout->addLayout(bottomLayout);

    // Set the main layout
    mainLayout->addLayout(rightLayout, 0, 0);

    setLayout(mainLayout);
}

QPushButton* Graph::createButton(const QString& str) {
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(25, 25);
    pcmd->setObjectName("graphButton");
    // Connect the button's clicked signal to a slot for processing
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));

    return pcmd;
}

void Graph::slotButtonClicked() {
    QString str = ((QPushButton*)sender())->text();
    if(str.contains("clear")){
        table->clearGraphs();
        table->addGraph();
        table->replot();
    }
}

QCustomPlot* Graph::buildGraph(){
    QCustomPlot* plott = new QCustomPlot;
    plott->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    plott->xAxis->setRange(-10, 10);
    plott->yAxis->setRange(-6, 6);



    plott->addGraph();
    return plott;
}

QLineEdit* Graph::getXmin() const{
    return xMin;
}
QLineEdit* Graph::getXmax() const{
    return xMax;
}
QLineEdit* Graph::getYmin() const{
    return yMin;
}
QLineEdit* Graph::getYmax() const{
    return yMax;
}

void Graph::zoomIn() {
    double zoomInFactor = 1.2;
    double minX = xMin->text().toDouble() / zoomInFactor;
    double maxX = xMax->text().toDouble() / zoomInFactor;
    double minY = yMin->text().toDouble() / zoomInFactor;
    double maxY = yMax->text().toDouble() / zoomInFactor;

    xMin->setText(QString::number(minX));
    xMax->setText(QString::number(maxX));
    yMin->setText(QString::number(minY));
    yMax->setText(QString::number(maxY));

    table->xAxis->setRange(minX, maxX);
    table->yAxis->setRange(minY, maxY);
    table->replot();
}

void Graph::zoomOut() {
    double zoomOutFactor = 1.2;

    double minX = xMin->text().toDouble() * zoomOutFactor;
    double maxX = xMax->text().toDouble() * zoomOutFactor;
    double minY = yMin->text().toDouble() * zoomOutFactor;
    double maxY = yMax->text().toDouble() * zoomOutFactor;

    xMin->setText(QString::number(minX));
    xMax->setText(QString::number(maxX));
    yMin->setText(QString::number(minY));
    yMax->setText(QString::number(maxY));

    table->xAxis->setRange(minX, maxX);
    table->yAxis->setRange(minY, maxY);
    table->replot();
}