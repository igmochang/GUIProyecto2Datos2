#ifndef GUI_H
#define GUI_H

#include <jsoncpp/json/value.h>
#include <jsoncpp/json/json.h>
#include <QMainWindow>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <bits/stdc++.h>



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

    Json::Reader reader;
    Json::Value data;
    std::array<std::string, 5> text;

    QStringList separateCode(QString code);
    QString boolToStr(bool b);
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
    QVector<std::array<QString, 4>> vecArray;

    ///QList< array > listArray;

    QStringList lineList;
    QString strLinea;
    QStringList elemList;
    QJsonArray arrayElem;
    int cont = 0;
    bool scope = false;
};
#endif // GUI_H
