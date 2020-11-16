#include "widget.h"
#include "ui_widget.h"
#include "CalculatorLogic.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    theBrain = new CalculatorLogic();

    connect(ui->btn0, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn1, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn2, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn3, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn4, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn5, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn6, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn7, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn8, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btn9, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnDecimal, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnAdd, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnSub, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnMul, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnDiv, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnSgnChange, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnSqrt, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnBack, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnC, SIGNAL(clicked()), this, SLOT(onBtnClicked()));
    connect(ui->btnEqual, SIGNAL(clicked()), this, SLOT(onBtnClicked()));

    connect(theBrain, SIGNAL(resultChanged(QString)), this, SLOT(onResultChanged()));
    connect(theBrain, SIGNAL(resultHistoryChanged(QString)), this, SLOT(onResultHistoryChanged()));

}

Widget::~Widget()
{
    delete ui;
    delete theBrain;
}

void Widget::onBtnClicked(){
    QPushButton* btn = (QPushButton*)sender();
    theBrain->doCommand(btn->text());
}

void Widget::onResultChanged(){
    if(ui->leInput->text() != theBrain->getResult()){
        ui->leInput->setText(theBrain->getResult());
    }
}

void Widget::onResultHistoryChanged(){
    if(ui->pteHistory->placeholderText() != theBrain->getHistory()){
        ui->pteHistory->setPlainText(theBrain->getHistory());
    }
}

