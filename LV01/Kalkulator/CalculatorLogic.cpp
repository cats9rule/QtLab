#include "CalculatorLogic.h"

CalculatorLogic::CalculatorLogic(QObject* parent){
    this->setParent(parent);
}

void CalculatorLogic::doCommand(QString command){

    // number1 je prvi broj, tempNumber je drugi
    // operation: 1+ 2- 3* 4/ , 0-not valid

    if(sResult == "nan" && command != "C"){

        // ko ti kriv kad delis nulom slino jedna

        return;
    }

    bool decimal = sResult.contains(".");

    if(decimal && command == "."){

        // ne moze dupli decimalni broj

        return;
    }

    QString operacije = "+-*/";

    if(decimal && sResult.right(1) == "."){

        // ako je poslednje uneta decimalna tacka

        int sizeTemp = sResult.size();

        if(!command.data()[0].isDigit() && command != "←"){

            // ako je sada uneta neka komanda, a ne cifra, tacka nije validna

            sResult.chop(1);
            tempNumber = sResult;
            tempHistory.chop(1);
        }
        else if(sizeTemp == 1){

            // ako je tacka prva u broju, ispred nje treba dodati nulu

            sResult.insert(0, "0");
            tempNumber = sResult;
            tempHistory.chop(1);
            tempHistory += "0.";

        }
    }

    //int sizeHistory = tempHistory.size();


//    if(!decimal){
//        if(sizeTemp == 1 && tempNumber.data()[sizeTemp-1] == "."){

//            tempNumber = "0.";
//            tempHistory.chop(1);
//            tempHistory += tempNumber;

//            if(operacije.contains(command)){
//                tempNumber.chop(1);
//                tempHistory.chop(1);
//            }
//        }
//    }
//    else if(command == "."){

//    }



    if(operation > 0 && operacije.contains(command) && operacije.contains(tempHistory.right(1))){

        // poslednje uneta je operacija, a ponovo je uneta operacija
        // potrebno je izbrisati prethodnu operaciju

        tempHistory.chop(1);
    }

    tempHistory+=command;

    if(operacije.contains(command) && operation > 0 && !tempNumber.isEmpty() && !number1.isEmpty()){

        // postoje dva broja, postoji operacija, unesena je nova operacija
        // treba sracunati vrednost nakon prve operacije, postaviti prvi broj na tu vrednost
        // i spremiti za unos sledeceg broja

        executeOperation();
        number1 = sResult;
        tempNumber = "";
        decimal = false;
    }

    // ako prethodno nije uneta operacija, treba zapamtiti prvi broj
    if(operacije.contains(command) && operation == 0){

        tempHistory.chop(1); // operacija treba da ide nakon prvog broja

        tempNumber = sResult;

        if(tempNumber == ""){

            // ako broj ne postoji, upisati nulu
            tempNumber = "0";
            decimal = false;
        }

        number1 = tempNumber;
        tempNumber = "";
        decimal = false;
        tempHistory = number1 + command;
    }

    if(command == "+"){

        // pamti operaciju

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

        tempHistory.chop(1); // brise strelicu

        if(tempNumber.isEmpty()){

            // ako je poslednje uneta operacija, ne radi nista

            return;
        }


        tempNumber.chop(1);
        tempHistory.chop(1);
        sResult = tempNumber;

    }

    else if(command == "±"){

        if(operation > 0 && !tempNumber.isEmpty() && !number1.isEmpty()){
            executeOperation();
            number1 = sResult;
        }

        if(number1.isEmpty()){
            number1 = tempNumber;
        }

        sResult = QString::number(number1.toDouble()*(-1));
        tempHistory.chop(1);

        if(tempHistory.isEmpty()){
            tempHistory = number1;
        }
        if(number1.isEmpty()){
            tempHistory += "0";
        }

        tempHistory += ")=" + sResult;
        tempHistory.insert(0, "(");
        tempHistory.insert(0, command);

        number1 = tempNumber = "";

    }

    else if(command == "√"){

        tempHistory.chop(1);

        if(operation > 0 && !tempNumber.isEmpty() && !number1.isEmpty()){
            executeOperation();
            number1 = sResult;
        }

        if(number1.isEmpty()){
            number1 = tempNumber;
        }

        // ne moze koren iz negativnog broja

        if(sResult.toDouble()>=0){

            sResult = QString::number(sqrt(sResult.toDouble()));
        }
        else {
            sResult = "nan";
        }
        tempHistory.insert(0, "(");
        tempHistory.insert(0, command);
        tempHistory += ")=";
        tempHistory += sResult;
    }
    else if(command == "C"){

        // resetuje sve

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

            // ako nije uneta operacija, ili je uneta operacija i samo prvi broj,
            // onda ne treba da radi nista

            return;
        }

        executeOperation(); // postavlja sResult na vrednost
        tempHistory += sResult;
        number1 = sResult;
        tempNumber = "";

        operation = 0;

    }
    else {
        // ako nije ukucana operacija, onda je ili cifra ili (decimalna tacka)
        // pamti se broj u svakom slucaju

        if(command == "."){
            decimal = true;
        }

        tempNumber+=command;
        sResult = tempNumber;
    }

    emit resultChanged(sResult);

    // ako je neka od sledecih komandi, treba emit historyChanged

    QString historyUpdaters = "±√C=";

    if(historyUpdaters.contains(command)){
        history += tempHistory + "\n";
        tempHistory = sResult;
        number1 = sResult;
        operation = 0;
        emit resultHistoryChanged(history);
    }

}

void CalculatorLogic::executeOperation(){

    // ne dira history, samo racuna

    // rezultat = prvi broj (operacija) drugi broj
    // u zavisnosti od opcode operation bira se odgovarajuca operacija

    switch(operation){
    case 1:
        sResult = QString::number(number1.toDouble() + tempNumber.toDouble());
        break;

    case 2:
        sResult = QString::number(number1.toDouble() - tempNumber.toDouble());
        break;

    case 3:
        sResult = QString::number(number1.toDouble() * tempNumber.toDouble());
        break;

    case 4:

        // ne moze deljenje nulom

        if(tempNumber.toDouble() != 0){
            sResult = QString::number(number1.toDouble() / tempNumber.toDouble());
        }
        else{
            sResult = "nan";
        }
        break;
    }
}
