/**
 *  @file gui.h
 *  @author Ignacio Morales
 *  @brief C! GUI
 *  @version 1.0
 *  @date 2021-05-05

 */
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
#include <QDateTime>
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
    /**
     * @brief lleva a cabo acciones al apretar boton run
     */
    void on_runButton_clicked();
    /**
     * @brief controla scroll de ventana
     * @param position
     */
    void on_verticalScrollBar_sliderMoved(int position);


private:
    Ui::GUI *ui;

    Json::Reader reader;
    Json::Value data;
    std::array<std::string, 5> text;

    /**
     * @brief separa el codigo en lineas
     * @param code
     * @return Lista de lineas de codigo
     */
    QStringList separateCode(QString code);
    /**
     * @brief convierte un booleano a string
     * @param b booleano
     * @return Booleano en string
     */
    QString boolToStr(bool b);
    /**
     * @brief revisa una linea de codigo
     * @param codeline_
     * @return booleano
     */
    bool codeCheck(QString codeline_);
    /**
     * @brief revisa si un QString es un numero
     * @param strnum
     * @return booleano
     */
    bool isNumber(QString strnum);
    /**
     * @brief revisa si entrada es int
     * @param n
     * @return booleano
     */
    bool isInt(QString n);
    /**
     * @brief revisa si entrada es float
     * @param n
     * @return booleano
     */
    bool isFloat(QString n);
    /**
     * @brief revisa si entrada es double
     * @param n
     * @return booleano
     */
    bool isDouble(QString n);
    /**
     * @brief revisa si entrada es long
     * @param n
     * @return booleano
     */
    bool isLong(QString n);
    /**
     * @brief revisa si entrada es Char
     * @param n
     * @return booleano
     */
    bool isChar(QString n);
    /**
     * @brief encuentra el indice de variable en vector
     * @param varName nombre de variable
     * @return indice de variable
     */
    int findVariableNameIndex(QString varName);
    /**
     * @brief revisa si parametro es una variable existente
     * @param varName nombre de variable
     * @return booleano
     */
    bool isVariable(QString varName);
    /**
     * @brief convierte string en su valor ASCII
     * @param n
     * @return valor ASCII en int
     */
    int convertToAscii(std::string n);
    /**
     * @brief convierte valor ASCII en QString
     * @param n
     * @return ASCII en QString
     */
    QString fromAscii(int n);
    /**
     * @brief obtiene valor segun nombre de variable
     * @param varName
     * @return valor en QString
     */
    QString getValue(QString varName);
    /**
     * @brief obtiene la direccion segun el nombre de variable
     * @param varName
     * @return Direccion de memoria en QString
     */
    QString getAddr(QString varName);
    QVector<std::array<QString, 5>> vecArray;

    QString time_format = "yyy-MM-dd HH:mm:ss";



    QStringList lineList;
    QString strLinea;
    QStringList elemList;
    QJsonArray arrayElem;
    int cont = 0;
    bool scope = false;
};
#endif // GUI_H
