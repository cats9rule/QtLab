#ifndef CALCULATORLOGIC_H
#define CALCULATORLOGIC_H

#include <QObject>

class CalculatorLogic : public QObject
{
    Q_OBJECT

private:

    QString sResult = ""; // pamti rezultat

    QString tempHistory = ""; // pamti liniju koja ce se upisati u History
    QString history = ""; // istorija racunanja

    QString number1 = ""; // pamti broj pre unosa operacije
    QString tempNumber = ""; // temp var koji pamti broj
    int operation=0; // kod operacije

public:
    CalculatorLogic(QObject* parent = 0);
    virtual ~CalculatorLogic(){};

    QString getResult() const {return sResult;}
    QString getHistory() const {return history;}

    void doCommand(QString command);


signals:
    void resultChanged(QString);
    void resultHistoryChanged(QString);
};


#endif // CALCULATORLOGIC_H
