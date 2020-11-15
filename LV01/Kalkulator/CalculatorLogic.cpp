#include "CalculatorLogic.h"

CalculatorLogic::CalculatorLogic(QObject* parent){
    this->setParent(parent);
}

void CalculatorLogic::doCommand(QString command){

    // number1 je prvi broj, tempNumber je drugi
    // operation: 1+ 2- 3* 4/ , 0-not valid

    QString operacije = "+-*/";

    tempHistory+=command;

    // ako prethodno nije uneta operacija, treba zapamtiti prvi broj
    if(operacije.contains(command) && operation == 0){
        number1 = tempNumber;
        tempNumber = "";
        tempHistory = number1 + command;
    }

    if(command == "+"){

        // store operation

        operation = 1;
    }
    else if(command == "-"){

        operation = 2;
    }
    else if(command == "*"){

        operation = 3;
    }
    else if (command == "/"){

        operation = 4;
    }
    else if(command == "←"){

        // erase last input
        // if its an operation, do nothing

        tempHistory.chop(1); // brise strelicu

        if(!tempNumber.isEmpty()){
            tempNumber.chop(1);
            tempHistory.chop(1);
            sResult = tempNumber;
        }

    }
    else if(command == "±"){

        // get last number and mul by -1

        sResult = QString::number(tempNumber.toDouble()*(-1));
        tempHistory = command + sResult;

    }
    else if(command == "√"){

        // take last number and get sqrt
        if(sResult.toDouble()>=0){

            tempHistory = command + sResult + "=";
            sResult = QString::number(sqrt(sResult.toDouble()));
            tempHistory += sResult;
        }

        else {
            tempHistory = command + tempNumber + "=" + "NAN";
        }
    }
    else if(command == "C"){

        // clear all

        tempNumber = "";
        number1 = "";
        tempHistory = "";
        history = "";
        sResult = "";
        operation = 0;

    }
    else if(command == "="){

        // kod treba da uzme u obzir operaciju i dva broja

        if(operation < 1 || (!number1.isEmpty() && tempHistory.isEmpty())){

            // ako nije uneta operacija, ili je uneta operacija i samo prvi broj
            // ne radi nista

            return;
        }

        switch(operation){
        case 1:
            sResult = QString::number(number1.toDouble() + tempNumber.toDouble());
            tempHistory += sResult;
            break;

        case 2:
            sResult = QString::number(number1.toDouble() - tempNumber.toDouble());
            tempHistory += sResult;
            break;

        case 3:
            sResult = QString::number(number1.toDouble() * tempNumber.toDouble());
            tempHistory += sResult;
            break;

        case 4:
            if(tempNumber.toDouble() != 0){
                sResult = QString::number(number1.toDouble() / tempNumber.toDouble());
                tempHistory += sResult;
            }
            else{
                tempHistory += "NAN";
            }
            break;
        }
        operation = 0;

    }
    else {
        // ako nije ukucana operacija, onda je ili cifra ili (decimalna tacka)
        // pamti se broj

        tempNumber+=command;
        sResult = tempNumber;
    }


    emit resultChanged(sResult);

    // ako je neka od sledecih konandi treba emit historyChanged
    QString historyUpdaters = "±√C=";

    if(historyUpdaters.contains(command)){
        history += tempHistory + "\n";
        tempHistory = "";
        tempNumber = sResult;
        emit resultHistoryChanged(history);
    }

}
