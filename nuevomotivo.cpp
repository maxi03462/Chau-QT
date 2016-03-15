#include "nuevomotivo.h"
#include "ui_nuevomotivo.h"

NuevoMotivo::NuevoMotivo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NuevoMotivo)
{
    ui->setupUi(this);
    ui->lineEdit->setText("");
    cargarmotivos();
}

NuevoMotivo::~NuevoMotivo()
{
    delete ui;
}

void NuevoMotivo::on_pushButton_clicked()
{
    close();
}

void NuevoMotivo::on_pushButton_2_clicked()
{
    if((ui->lineEdit->text())!=""){


    }
}

void NuevoMotivo::cargarmotivos()
{
        int a = ui->comboBox->count();
        for (int var = 0; var < a; ++var) {
            ui->comboBox->removeItem(var);
        }
        QString C = "SELECT * FROM M0TIV0S;";
        QSqlQuery Pregunta;
        qDebug() << "Se pregunto bien?" << Pregunta.exec(C);
        while (Pregunta.next()){
        ui->comboBox->addItem(Pregunta.value(0).toString());
        }
}
