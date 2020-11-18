#include "CalculatorLogic.h"

CalculatorLogic::CalculatorLogic(QObject* parent){
    this->setParent(parent);
}

void CalculatorLogic::doCommand(QString command){

    // number1 je prvi broj, tempNumber je drugi
    // operation: 1+ 2- 3* 4/ , 0-not valid

    if(sResult == "nan" && command != "C"){
        // potrebno je resetovati kalkulator kada se postavi na nan vrednost
        return;
    }

    bool decimal = sResult.contains("."); // da li je broj decimal
    if(decimal && command == "."){
        // ne moze dupli decimalni broj
        return;
    }
    if(decimal && sResult.right(1) == "."){
        // ako je poslednje uneta decimalna tacka, potrebno preformatirati
        if(!command.data()[0].isDigit() && command != "←"){
            // ako je sada uneta neka komanda, a ne cifra, tacka nije validna
            sResult.chop(1);
            tempNumber = sResult;
            tempHistory.chop(1);
        }
        else if(sResult.size() == 1){
            // ako je tacka prva u broju, ispred nje treba dodati nulu
            sResult.insert(0, "0");
            tempNumber = sResult;
            tempHistory.chop(1);
            tempHistory += "0.";
        }
    }
    QString operacije = "+-*/";
    if(operation > 0 && operacije.contains(command) && operacije.contains(tempHistory.right(1))){
        // poslednje uneta je operacija, a ponovo je uneta operacija
        // potrebno je izbrisati prethodnu operaciju radi zamene
        tempHistory.chop(1);
    }

    tempHistory+=command; // dodaje se komanda u zapis

    if(operacije.contains(command) && operation > 0 && !tempNumber.isEmpty() && !number1.isEmpty()){
        /*
            **** nadovezivanje operacija ****

            postoje dva broja, postoji operacija, uneta je nova operacija
            treba sracunati vrednost nakon prve operacije, postaviti prvi broj na tu vrednost
            i spremiti kalkulator za unos sledeceg broja
        */
        executeOperation();
        number1 = sResult;
        tempNumber = "";
        decimal = false;
    }
    // ako prethodno nije uneta operacija, treba zapamtiti prvi broj
    if(operacije.contains(command) && operation == 0){
        tempHistory.chop(1);
        tempNumber = sResult;
        if(tempNumber == ""){
            tempNumber = "0";
        }
        number1 = tempNumber;
        tempNumber = "";
        tempHistory = number1 + command;
    }
    // ispitivanje koja komanda je uneta i odredjivanje akcije koja treba da se izvrsi
    if(command == "+"){
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
        tempHistory.chop(1);
        if(tempNumber.isEmpty()){
            // ako je poslednje uneta operacija, ili tek sracunato nesto, ne radi nista
            return;
        }
        tempNumber.chop(1);
        tempHistory.chop(1);
        sResult = tempNumber;
    }
    else if(command == "±"){
        // promena znaka

        if(operation > 0 && !tempNumber.isEmpty() && !number1.isEmpty()){
            // ukoliko ima operacije spremne za izvrsavanje, izvrsiti
            executeOperation();
            number1 = sResult;
        }
        else if(number1.isEmpty()){
            number1 = tempNumber;
        }
        sResult = QString::number(number1.toDouble()*(-1));        
        // kod za ispis u history
        tempHistory.chop(1);
        if(tempHistory.isEmpty()){
            tempHistory = number1;
        }
        if(number1.isEmpty()){
            tempHistory += "0";
        }
        while(tempHistory.right(1) == "=" || operacije.contains(tempHistory.right(1))){
            // ako je bio unos vise znakova jednako, treba ih obrisati
            // neizvrsene operacije treba obrisati
            tempHistory.chop(1);
        }
        tempHistory += ")=" + sResult;
        tempHistory.insert(0, "(");
        tempHistory.insert(0, command);

        number1 = sResult;
        tempNumber = "";
    }
    else if(command == "√"){
        tempHistory.chop(1);
        if(operation > 0 && !tempNumber.isEmpty() && !number1.isEmpty()){
            executeOperation();
            number1 = sResult;
        }
        else if(number1.isEmpty()){
            number1 = tempNumber;
        }
        // ne moze koren iz negativnog broja
        if(sResult.toDouble()>=0){
            sResult = QString::number(sqrt(sResult.toDouble()));
            number1 = sResult;
        }
        else {
            sResult = "nan";
        }

        tempHistory.insert(0, "(");
        tempHistory.insert(0, command);
        while(tempHistory.right(1) == "=" || operacije.contains(tempHistory.right(1))){
            tempHistory.chop(1);
        }
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
        if(operacije.contains(tempHistory.right(2).left(1))){
            // brise suvisni znak operacije iz istorije
            tempHistory.chop(1);
        }
        if(operation < 1 || (!number1.isEmpty() && (tempHistory.isEmpty() || tempNumber.isEmpty()))){
            // ako nije uneta operacija, ili je uneta operacija i samo prvi broj,
            // onda ne treba da radi nista
            if(number1.isEmpty() || number1 == "0"){
                operation = 0;
            }
            return;
        }
        executeOperation(); // postavlja sResult na vrednost rezultata
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
        tempNumber = sResult;
        operation = 0;
        emit resultHistoryChanged(history);
    }
}

void CalculatorLogic::executeOperation(){
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
