#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <bits/stdc++.h>
//#include <array>


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{

    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private slots:
    void on_runButton_clicked();

    

    void on_verticalScrollBar_sliderMoved(int position);

private:
    Ui::GUI *ui;
    
    QStringList separateCode(QString code);
    bool codeCheck(QString codeline_);
    bool isNumber(QString strnum);
    bool isInt(QString n);
    bool isFloat(QString n);
    bool isDouble(QString n);
    bool isLong(QString n);
    bool isChar(QString n);
    int findVariableNameIndex(QString varName);
    bool isVariable(QString varName);
    bool areCompatible(QString n1, QString n2);
    int convertToAscii(std::string n);
    QString fromAscii(int n);
    QString getValue(QString varName);
    QString getAddr(QString varName);
    //std::vector<std::array>
    QVector<std::array<QString, 4>> vecArray;




    //std::vector<array> vecArray;

    //QString matriz[2][2];

    ///QList< array > listArray;

    QStringList lineList;
    QString strLinea;
    QStringList elemList;
    QJsonArray arrayElem;
    int cont = 0;
};
#endif // GUI_H
