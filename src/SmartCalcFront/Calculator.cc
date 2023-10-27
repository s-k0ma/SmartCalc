#include "Calculator.h"

Calculator::Calculator(QWidget* pwgt/*= 0*/) : QWidget(pwgt)
{
    QVBoxLayout* mainLo = new QVBoxLayout;
    QHBoxLayout* topLo = new QHBoxLayout;

    m_plcd = new QLineEdit(this);
    m_plcd->setObjectName("inputLine");

    QRegularExpression regex("^(?!^[/*])"
                             "(?:[*/^]?[-+]?"
                             "(?:\\d*\\.?\\d+|X|sin|cos|tan|asin|acos|atan|ln|log|mod|sqrt|"
                             "(?:\\((?:[*/^]?[-+])?|(?:\\d*\\.?\\d+|X|"
                             "\\((?: X|\\([^)]*\\))*\\))*\\))"
                             ")){1,255}$");

    QRegularExpressionValidator* mainValidator = new QRegularExpressionValidator(regex, this);
    m_plcd->setValidator(mainValidator);
    m_plcd->setFocusPolicy(Qt::StrongFocus);

    topLo->addWidget(m_plcd);
    topLo->addWidget(createButton("⌫"));
    mainLo->addLayout(topLo);

    QHBoxLayout* additionalInputLayout = new QHBoxLayout;

    x_plcd = new QLineEdit(this);
    x_plcd->setObjectName("additionalInput");
    x_plcd->setFocusPolicy(Qt::StrongFocus);
    QRegularExpression xRegex("[-]?\\d*\\.?\\d+");
    QRegularExpressionValidator* xValidator = new QRegularExpressionValidator(xRegex);
    x_plcd->setValidator(xValidator);

    additionalInputLayout->addWidget(x_plcd);
    additionalInputLayout->addWidget(createButton("X"));
    additionalInputLayout->addWidget(createButton("CE"));

    mainLo->addLayout(additionalInputLayout);


    QString aButtons[5][6] = {{"cos", "acos", "7", "8", "9", "/"},
                              {"sin", "asin", "4", "5", "6", "*"},
                              {"tan", "atan", "1", "2", "3", "-"},
                              {"ln", "log", "0", "(", ")", "+"},
                              {"mod", "sqrt", "^", ".", "=", "graph"}
    };

    QGridLayout* ptopLayout = new QGridLayout;
    for(int i = 0; i < 5; ++i){
        for(int j = 0; j < 6; ++j){
            ptopLayout->addWidget(createButton(aButtons[i][j]), i + 2, j);
        }
    }

    mainLo->addLayout(ptopLayout);
    setLayout(mainLo);
}

QPushButton* Calculator::createButton(const QString &str) {
    QPushButton* pcmd = new QPushButton(str);
    pcmd->setMinimumSize(50, 50);
    pcmd->setObjectName("calculatorButton");
    str.contains("graph") ? connect(pcmd, &QPushButton::clicked, this, &Calculator::graphButtonClicked) :
    connect(pcmd, SIGNAL(clicked()), SLOT(slotButtonClicked()));

    return pcmd;
}

void Calculator::slotButtonClicked() {
    QString str = ((QPushButton*)sender())->text();

    if(str.contains("CE")){
        m_plcd->clear();
        m_strDisplay = m_plcd->text();
        x_plcd->clear();
        x_strDisplay = m_plcd->text();
    }else if(str.contains("⌫")){
        if(m_plcd->hasFocus()){
            m_plcd->backspace();
            m_strDisplay = m_plcd->text();
        }else if(x_plcd->hasFocus()){
            x_plcd->backspace();
            x_strDisplay = m_plcd->text();
        }
    }else if(str.contains("=")){
        if(!m_plcd->text().isEmpty() && !x_plcd->text().isEmpty()) {
            double x = calculation(m_plcd->text().replace("X", x_plcd->text()).toLocal8Bit().data());
            m_strDisplay = QString::number(x);
            m_plcd->setText(m_strDisplay);
            x_plcd->clear();
        }else if(!m_plcd->text().isEmpty() && x_plcd->text().isEmpty()){
            double x = calculation(m_plcd->text().toLocal8Bit().data());
            m_strDisplay = QString::number(x);
            m_plcd->setText(m_strDisplay);
        }
    }else{
         if(m_plcd->hasFocus()) {
             if(str == "sin" || str == "cos" || str == "tan" ||
                str == "asin" || str == "acos" || str == "atan" ||
                str == "log" || str == "sqrt" || str == "ln" || str == "mod") str += "(";
            m_strDisplay = m_plcd->text().isEmpty() ? m_strDisplay + str : m_plcd->text() + str;
            m_plcd->setText(m_strDisplay);
        }else if(x_plcd->hasFocus() && str.contains(QRegularExpression("[.0-9]"))){
             x_strDisplay = x_plcd->text().isEmpty() ? x_strDisplay + str : x_plcd->text() + str;
             x_plcd->setText(x_strDisplay);
        }
    }
}

void Calculator::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab) {
        if (m_plcd->hasFocus()) {
            x_plcd->setFocus();
            x_plcd->setCursorPosition(x_plcd->text().length());
        } else if (x_plcd->hasFocus()) {
            m_plcd->setFocus();
            m_plcd->setCursorPosition(m_plcd->text().length());
        }
    }
    QWidget::keyPressEvent(event);
}

QLineEdit* Calculator::getInputExp() const{
    return m_plcd;
}

Calculator::~Calculator(){
}