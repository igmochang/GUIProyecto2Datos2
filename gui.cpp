#include "gui.h"
#include "ui_gui.h"
#include "iostream"
#include <ctype.h>
#include <stdio.h>
#include <string>
#include <sstream>

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    setWindowTitle("C! IDE");


}

GUI::~GUI()
{
    delete ui;

}



void GUI::on_runButton_clicked()
{
    QString plainCode = this->ui->code->toPlainText().simplified();
    QStringList lineList = separateCode(plainCode);
    if(codeCheck(lineList[cont])){
        strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + elemList[3] + "\"}";
        ui->output->setText(strLinea);
    }
    cont++;
}


QStringList GUI::separateCode(QString code) {
    //QStringList lineList = code.split(QRegExp("[\n]"),QString::SkipEmptyParts);
    QRegExp lineDiv("(\\\n)");
    QRegExp lineElem("(\\ |\\;)");               

    lineList = code.split(lineDiv);
    lineList.removeAll(" ");
    elemList = lineList[cont].split(lineElem);




    return lineList;
}

bool GUI::codeCheck(QString codeline_) {
    QRegExp lineElem("(\\ |\\;)");
    QStringList elemList_ = codeline_.split(lineElem);

    if(elemList_[0] != "struct" or elemList_[0] != "{" or elemList_[0] != "}"){
        if(elemList_[0] == "int" or elemList_[0] == "long" or elemList_[0] == "char" or
                                  elemList_[0] == "float" or elemList_[0] == "double"){
            if((elemList_[1].at(0)<='z' && elemList_[1].at(0)>='a') || (elemList_[1].at(0)<='Z' && elemList_[1].at(0)>='A')){
                if(elemList_[2] == '='){

                    if(elemList_[0] == "int"){
                        QRegExp re("\\d*");
                        if(re.exactMatch(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                return true;
                            } else {ui->appLog->append("Error: se espera ';' al final de la linea");}
                        } else{ui->appLog->append("Error: Valor no es int");}
                    } else if (elemList_[0] == "float"){
                        if(isFloat(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                return true;
                            } else {ui->appLog->append("Error: se espera ';' al final de la linea");}
                        } else {ui->appLog->append("Error: Valor no es float");}
                    } else if (elemList_[0] == "double") {
                        if(isDouble(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                return true;
                            } else {ui->appLog->append("Error: se espera ';' al final de la linea");}
                        } else {ui->appLog->append("Error: Valor no es double");}
                    } else if (elemList_[0] == "long") {
                        if(isLong(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                return true;
                            } else {ui->appLog->append("Error: se espera ';' al final de la linea");}
                        } else {ui->appLog->append("Error: Valor no es long");}
                    } else if (elemList_[0] == "char") {
                        if(isChar(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                return true;
                            } else {ui->appLog->append("Error: se espera ';' al final de la linea");}
                        } else {ui->appLog->append("Error: Valor no es char");}
                    }
                }
            } else{ui->appLog->setText("Error en nombre de variable");}

        } else {ui->appLog->setText("Tipo de dato no reconocido"); }
    }

}

bool GUI::isFloat(QString n){
    bool ok;
    double f;
    f = n.toFloat(&ok);
    if(ok == true){
        return true;
    } else{return false;}
    return true;
}

bool GUI::isDouble(QString n){
    bool ok;
    double d;
    d = n.toDouble(&ok);
    if(ok == true){
        return true;
    } else{return false;}
}

bool GUI::isLong(QString n){
    bool ok;
    long l;
    l = n.toLong(&ok);
    if(ok == true){
        return true;
    } else{return false;}
}

bool GUI::isChar(QString n){
    if(n.at(0)=="\"" and n.endsWith("\"")){
        return true;
    } else{ return false; }
}









