#include "gui.h"
#include "ui_gui.h"
#include "iostream"

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
    QString plainCode = this->ui->code->toPlainText().toUtf8().constData();
    QStringList lineList = plainCode.split(QRegExp("[\n]"),QString::SkipEmptyParts);

    for(int i = 0; i<lineList.length();i++){
        if(lineList[i].at(lineList[i].length()-1) != ";"){
            ui->output->append("Linea " + QString::number(i+1) + " Malo");
        } else {
            ui->output->append("Linea " + QString::number(i+1) + " Bueno");
            for(int j = 0; j<lineList[i].length(); j++){
                if(lineList[i].at(j) == "="){
                    for(int k = 0; k<j; k++){
                        ui->output->insertPlainText(lineList[i].at(k));
                    }
                }
            }
        }
    }


    ui->RLVtextbrowser->setText(lineList[0].at(lineList[0].length()-1));

    ui->output->append(ui->code->toPlainText());

    QString codePlainText = ui->code->toPlainText();

    ui->output->append(codePlainText);
}










