#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>

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

    

private:
    Ui::GUI *ui;
    
    QStringList separateCode(QString code);
    bool codeCheck(QString codeline_);
    bool isFloat(QString n);
    bool isDouble(QString n);
    bool isLong(QString n);
    bool isChar(QString n);
    
    QStringList lineList;
    QString strLinea;
    QStringList elemList;
    QJsonArray arrayElem;
    int cont = 0;
};
#endif // GUI_H
