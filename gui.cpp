#include "gui.h"
#include "ui_gui.h"
#include "iostream"
#include <ctype.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <Servidor/Client.h>

Client *Cliente = new Client();

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);
    setWindowTitle("C! IDE");
    qDebug("Ventana de C! creada");

}

GUI::~GUI()
{
    delete ui;
}



void GUI::on_runButton_clicked()
{
    QString plainCode = this->ui->code->toPlainText();
    QStringList lineList = separateCode(plainCode);
    ui->RLVtext->clear();

    if(codeCheck(lineList[cont])){
        cont++;

    }

    for(int i = 0; i<vecArray.length(); i++){
        ui->RLVtext->append(vecArray[i][3]+" "+ vecArray[i][2]+" "+vecArray[i][1]+" "+vecArray[i][4]);
    }
}

QStringList GUI::separateCode(QString code) {
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

    if(elemList_[0] != "struct" && elemList_[0] != "{" && elemList_[0] != "}" && elemList_[0].startsWith("cout") == false){
        if(elemList_[0] == "int" or elemList_[0] == "long" or elemList_[0] == "char" or
                elemList_[0] == "float" or elemList_[0] == "double" or elemList_[0].startsWith("reference")){
            if((elemList_[1].at(0)<='z' && elemList_[1].at(0)>='a') || (elemList_[1].at(0)<='Z' && elemList_[1].at(0)>='A')){
                if(elemList_[2] == '='){
                    if(elemList_[0] == "int"){
                        QRegExp re("\\d*");
                        if(re.exactMatch(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + elemList[3] + "\", \"corchete\":\"" + boolToStr(scope) + "\"}";
                                Cliente->Enviar(strLinea.toUtf8().constData());
                                text = Cliente->Recibir();

                                QString mem = QString::fromStdString(text[3]);
                                QString ref = QString::fromStdString(text[4]);
                                QString nom = QString::fromStdString(text[1]);
                                QString val = QString::fromStdString(text[2]);
                                QString tipo = QString::fromStdString(text[0]);

                                std::array<QString, 5> errex {{tipo, nom, val, mem, ref}};
                                vecArray.push_back(errex);

                                return true;
                            } else{
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as + " Error: se espera ';' al final de la linea");
                            }
                        } else{
                            QDateTime a = QDateTime::currentDateTime();
                            QString as = a.toString(time_format);
                            ui->appLog->append(as+" Error: Valor no es int");
                        }
                    } else if (elemList_[0] == "float"){
                        if(isFloat(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + elemList[3] + "\", \"corchete\":\"" + boolToStr(scope) + "\"}";
                                Cliente->Enviar(strLinea.toUtf8().constData());
                                text = Cliente->Recibir();

                                QString mem = QString::fromStdString(text[3]);
                                QString ref = QString::fromStdString(text[4]);
                                QString nom = QString::fromStdString(text[1]);
                                QString val = QString::fromStdString(text[2]);
                                QString tipo = QString::fromStdString(text[0]);

                                std::array<QString, 5> errex {{tipo, nom, val, mem, ref}};
                                vecArray.push_back(errex);

                                return true;
                            } else {
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as+" Error: se espera ';' al final de la linea");
                            }
                        } else {
                            QDateTime a = QDateTime::currentDateTime();
                            QString as = a.toString(time_format);
                            ui->appLog->append(as+" Error: Valor no es float");
                        }
                    } else if (elemList_[0] == "double") {
                        if(isDouble(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + elemList[3] + "\", \"corchete\":\"" + boolToStr(scope) + "\"}";
                                Cliente->Enviar(strLinea.toUtf8().constData());
                                text = Cliente->Recibir();

                                QString mem = QString::fromStdString(text[3]);
                                QString ref = QString::fromStdString(text[4]);
                                QString nom = QString::fromStdString(text[1]);
                                QString val = QString::fromStdString(text[2]);
                                QString tipo = QString::fromStdString(text[0]);

                                std::array<QString, 5> errex {{tipo, nom, val, mem, ref}};
                                vecArray.push_back(errex);

                                return true;
                            } else {
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as + " Error: se espera ';' al final de la linea");
                            }
                        } else {
                            QDateTime a = QDateTime::currentDateTime();
                            QString as = a.toString(time_format);
                            ui->appLog->append(as + " Error: Valor no es double");
                        }
                    } else if (elemList_[0] == "long") {
                        if(isLong(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + elemList[3] + "\", \"corchete\":\"" + boolToStr(scope) + "\"}";
                                Cliente->Enviar(strLinea.toUtf8().constData());
                                text = Cliente->Recibir();

                                QString mem = QString::fromStdString(text[3]);
                                QString ref = QString::fromStdString(text[4]);
                                QString nom = QString::fromStdString(text[1]);
                                QString val = QString::fromStdString(text[2]);
                                QString tipo = QString::fromStdString(text[0]);

                                std::array<QString, 5> errex {{tipo, nom, val, mem, ref}};
                                vecArray.push_back(errex);

                                return true;
                            } else {
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as + " Error: se espera ';' al final de la linea");
                            }
                        } else {
                            QDateTime a = QDateTime::currentDateTime();
                            QString as = a.toString(time_format);
                            ui->appLog->append(as+" Error: Valor no es long");
                        }
                    } else if (elemList_[0] == "char") {
                        if(isChar(elemList_[3])){
                            if(codeline_.endsWith(';')){
                                strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + elemList[3] + "\", \"corchete\":\"" + boolToStr(scope) + "\"}";
                                Cliente->Enviar(strLinea.toUtf8().constData());
                                text = Cliente->Recibir();

                                QString mem = QString::fromStdString(text[3]);
                                QString ref = QString::fromStdString(text[4]);
                                QString nom = QString::fromStdString(text[1]);
                                QString val = QString::fromStdString(text[2]);
                                QString tipo = QString::fromStdString(text[0]);

                                std::array<QString, 5> errex {{tipo, nom, val, mem, ref}};
                                vecArray.push_back(errex);

                                return true;
                            } else {
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as+" Error: se espera ';' al final de la linea");
                            }
                        } else {
                            QDateTime a = QDateTime::currentDateTime();
                            QString as = a.toString(time_format);
                            ui->appLog->append(as+" Error: Valor no es char");
                        }
                    } else if (elemList_.startsWith("reference")){
                        if (elemList_[2] == "="){
                            if(isVariable(elemList_[3].mid(8,elemList_[3].length()-9))){
                                strLinea = "{\"tipo\":\"" + elemList[0] + "\", \"nombre\":\"" + elemList[1] + "\", \"valor\":\"" + getAddr(elemList_[3].mid(8,elemList_[3].length()-9)) + "\", \"corchete\":\"" + boolToStr(scope) + "\"}";
                                Cliente->Enviar(strLinea.toUtf8().constData());
                                text = Cliente->Recibir();

                                QString mem = QString::fromStdString(text[3]);
                                QString ref = QString::fromStdString(text[4]);
                                QString nom = QString::fromStdString(text[1]);
                                QString val = QString::fromStdString(text[2]);
                                QString tipo = QString::fromStdString(text[0]);

                                std::array<QString, 5> errex {{tipo, nom, val, mem, ref}};
                                vecArray.push_back(errex);

                                return true;
                            }
                        }
                    }
                }
            } else{ui->appLog->setText("Error en nombre de variable");}
        } else {
            if(isVariable(elemList_[0]) && isVariable(elemList_[2])){
                if(vecArray[findVariableNameIndex(elemList_[0])][0] != "char" && vecArray[findVariableNameIndex(elemList_[2])][0] != "char"){
                    if(elemList_[1] == "="){
                        if(vecArray[findVariableNameIndex(elemList_[0])][0] == "int"){
                            vecArray[findVariableNameIndex(elemList_[0])][2] = QString::number((vecArray[findVariableNameIndex(elemList_[2])][2]).toInt());
                            return true;
                        } else if (vecArray[findVariableNameIndex(elemList_[0])][0] == "float") {
                            vecArray[findVariableNameIndex(elemList_[0])][2] = QString::number((vecArray[findVariableNameIndex(elemList_[2])][2]).toFloat());
                            return true;
                        } else if (vecArray[findVariableNameIndex(elemList_[0])][0] == "double") {
                            vecArray[findVariableNameIndex(elemList_[0])][2] = QString::number((vecArray[findVariableNameIndex(elemList_[2])][2]).toDouble());
                            return true;
                        } else if (vecArray[findVariableNameIndex(elemList_[0])][0] == "long") {
                            vecArray[findVariableNameIndex(elemList_[0])][2] = QString::number((vecArray[findVariableNameIndex(elemList_[2])][2]).toLong());
                            return true;
                        }
                    } else {
                        if(vecArray[findVariableNameIndex(elemList_[0])][0] == "double"
                                or vecArray[findVariableNameIndex(elemList_[2])][0] == "double"){
                            if(elemList_[1]=="+"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() + vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                return true;
                            } else if(elemList_[1]=="-"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() - vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                return true;
                            } else if(elemList_[1]=="*"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() * vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                return true;
                            } else if(elemList_[1]=="/"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() / vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                return true;
                            } else{
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as+" Error: Operacion no reconocida");
                                return false;
                            }

                        } else if(vecArray[findVariableNameIndex(elemList_[0])][0] == "float"
                                  or vecArray[findVariableNameIndex(elemList_[2])][0] == "float"){
                            if(elemList_[1]=="+"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() + vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                return true;
                            } else if(elemList_[1]=="-"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() - vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                return true;
                            } else if(elemList_[1]=="*"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() * vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                return true;
                            } else if(elemList_[1]=="/"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() / vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                return true;
                            } else{
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as + " Operacion no reconocida");
                                return false;
                            }

                        } else if(vecArray[findVariableNameIndex(elemList_[0])][0] == "long"
                                  or vecArray[findVariableNameIndex(elemList_[2])][0] == "long"){
                            if(elemList_[1]=="+"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() + vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                return true;
                            } else if(elemList_[1]=="-"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() - vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                return true;
                            } else if(elemList_[1]=="*"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() * vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                return true;
                            } else if(elemList_[1]=="/"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() / vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                return true;
                            } else{
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as+" Error: Operacion no reconocida");
                                return false;
                            }
                        } else{
                            if(elemList_[1]=="+"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() + vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                return true;
                            } else if(elemList_[1]=="-"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() - vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                return true;
                            } else if(elemList_[1]=="*"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() * vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                return true;
                            } else if(elemList_[1]=="/"){
                                ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() / vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                return true;
                            } else{
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->append(as+" Error: Operacion no reconocida");
                                return false;
                            }
                        }
                    }
                } else {
                    if(vecArray[findVariableNameIndex(elemList_[0])][0] != "char"){
                        if(elemList_[1] == "="){
                            if(vecArray[findVariableNameIndex(elemList_[0])][0] == "int"){
                                vecArray[findVariableNameIndex(elemList_[0])][2] = (convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString()));
                                return true;
                            } else if (vecArray[findVariableNameIndex(elemList_[0])][0] == "float") {
                                vecArray[findVariableNameIndex(elemList_[0])][2] = float(convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString()));
                                return true;
                            } else if (vecArray[findVariableNameIndex(elemList_[0])][0] == "double") {
                                vecArray[findVariableNameIndex(elemList_[0])][2] = double(convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString()));
                                return true;
                            } else if (vecArray[findVariableNameIndex(elemList_[0])][0] == "long") {
                                vecArray[findVariableNameIndex(elemList_[0])][2] = long(convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString()));
                                return true;
                            }
                        } else {
                            if(vecArray[findVariableNameIndex(elemList_[0])][0] == "double"
                                    or vecArray[findVariableNameIndex(elemList_[2])][0] == "double"){
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() + convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() - convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() * convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toDouble() / convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(as+" Error: Operacion no reconocida");
                                    return false;
                                }

                            } else if(vecArray[findVariableNameIndex(elemList_[0])][0] == "float"
                                      or vecArray[findVariableNameIndex(elemList_[2])][0] == "float"){
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() + convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() - convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() * convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toFloat() / convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(as+" Error: Operacion no reconocida");
                                    return false;
                                }

                            } else if(vecArray[findVariableNameIndex(elemList_[0])][0] == "long"
                                      or vecArray[findVariableNameIndex(elemList_[2])][0] == "long"){
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() + convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() - convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() * convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toLong() / convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(as+" Error: Operacion no reconocida");
                                    return false;
                                }
                            } else{
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() + convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() - convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() * convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(vecArray[findVariableNameIndex(elemList_[0])][2].toInt() / convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->setText(as+" Error: Operacion no reconocida");
                                    return false;
                                }
                            }
                        }
                    } else if(vecArray[findVariableNameIndex(elemList_[2])][0] != "char"){
                        if(elemList_[1] == "="){
                            vecArray[findVariableNameIndex(elemList_[0])][2] = fromAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toInt());
                        } else {
                            if(vecArray[findVariableNameIndex(elemList_[2])][0] == "double"){
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) + vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) - vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) * vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) / vecArray[findVariableNameIndex(elemList_[2])][2].toDouble()));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(as+" Error: Operacion no reconocida");
                                    return false;
                                }

                            } else if(vecArray[findVariableNameIndex(elemList_[2])][0] == "float"){
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) + vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) - vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) * vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) / vecArray[findVariableNameIndex(elemList_[2])][2].toFloat()));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(as+" Error: Operacion no reconocida");
                                    return false;
                                }

                            } else if(vecArray[findVariableNameIndex(elemList_[2])][0] == "long"){
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) + vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) - vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) * vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) / vecArray[findVariableNameIndex(elemList_[2])][2].toLong()));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(" Error: Operacion no reconocida");
                                    return false;
                                }
                            } else{
                                if(elemList_[1]=="+"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) + vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                    return true;
                                } else if(elemList_[1]=="-"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) - vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                    return true;
                                } else if(elemList_[1]=="*"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) * vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                    return true;
                                } else if(elemList_[1]=="/"){
                                    ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) / vecArray[findVariableNameIndex(elemList_[2])][2].toInt()));
                                    return true;
                                } else{
                                    QDateTime a = QDateTime::currentDateTime();
                                    QString as = a.toString(time_format);
                                    ui->appLog->append(as+" Error: Operacion no reconocida");
                                    return false;
                                }
                            }
                        }
                    } else{
                        if(elemList_[1] == "="){
                            vecArray[findVariableNameIndex(elemList_[0])][2] = vecArray[findVariableNameIndex(elemList_[2])][2];
                            return true;
                        } else {
                            if(elemList_[1]=="+"){
                                ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) + convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                return true;
                            } else if(elemList_[1]=="-"){
                                ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) - convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                return true;
                            } else if(elemList_[1]=="*"){
                                ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) * convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                return true;
                            } else if(elemList_[1]=="/"){
                                ui->output->append(QString::number(convertToAscii(vecArray[findVariableNameIndex(elemList_[0])][2].toStdString()) / convertToAscii((vecArray[findVariableNameIndex(elemList_[2])][2]).toStdString())));
                                return true;
                            } else{
                                QDateTime a = QDateTime::currentDateTime();
                                QString as = a.toString(time_format);
                                ui->appLog->setText(as+" Error: Operacion no reconocida");
                                return false;
                            }
                        }
                    }
                }
                ui->appLog->setText("Tipo de dato no reconocido");
            }
        }
    } else{
        if(elemList_[0].startsWith("cout")){
            qDebug("imprimiendo");
            if(elemList_[0].at(5) == "\""){
                ui->output->append(elemList_[0].mid(6, elemList_[0].length()-8));
                return true;
            } else if(isVariable(elemList_[0].mid(5, elemList_[0].length()-6))){
               ui->output->append(vecArray[findVariableNameIndex(elemList_[0].mid(5, elemList_[0].length()-6))][2]);
               return true;
            } else if(isNumber(elemList_[0].mid(5, elemList_[0].length()-6))){
                ui->output->append(elemList_[0].mid(5, elemList_[0].length()-6));
                return true;
            } else if(elemList_[0].mid(5, elemList_[0].length()-6).startsWith("getAddr")){
                ui->output->append(getAddr(elemList_[0].mid(13, elemList_[0].length()-14)));
                return true;
            } else if (elemList_[0].mid(5, elemList_[0].length()-6).startsWith("getValue")){
                ui->output->append(getValue(elemList_[0].mid(13, elemList_[0].length()-14)));
                return true;
            }
        } else if(elemList_[0] == "{"){
            scope = true;
            return true;
        } else if (elemList_[0] == "}"){
            scope = false;
            return true;
        }
    }
}

QString GUI::boolToStr(bool b){
    return b ? "true" : "false";
}
bool GUI::isNumber(QString strnum){
    if (isFloat(strnum) or isLong(strnum) or isDouble(strnum) or isInt(strnum)){
        return true;
    } else{return false;}
}

QString GUI::getValue(QString varName){
    return vecArray[findVariableNameIndex(varName)][2];
}

QString GUI::getAddr(QString varName){
    return vecArray[findVariableNameIndex(varName)][3];
}

QString GUI::fromAscii(int n){
    char ch = n;
    return QString(ch);
}

int GUI::convertToAscii(std::string n){
    for(int i = 0; i<n.length(); i++){
        char x = n.at(i);
        return x;
    }
}

bool GUI::isVariable(QString varName){
    for(int i = 0; i<vecArray.length(); i++) {
        if(vecArray[i][1] == varName){
            return true;
            break;
        }
    }
}

int GUI::findVariableNameIndex(QString varName){
    for(int i =0; i<vecArray.length();i++){
        if(vecArray[i][1]==varName){
            return i;
            break;
        }
    }
}

bool GUI::isInt(QString n){
    bool ok;
    double i;
    i = n.toInt(&ok);
    if(ok == true){
        return true;
    } else{return false;}
}

bool GUI::isFloat(QString n){
    bool ok;
    double f;
    f = n.toFloat(&ok);
    if(ok == true){
        return true;
    } else{return false;}
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


void GUI::on_verticalScrollBar_sliderMoved(int position)
{
    ui->lineNumb->verticalScrollBar()->setValue(10*position);
    ui->code->verticalScrollBar()->setValue(10*position);
}
