#include "nuevomotivo.h"
#include "ui_nuevomotivo.h"
#include <QDebug>

QList<QString> Listado;

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

void NuevoMotivo::on_pushButton_2_clicked()                             //Añadir motivo
{
    if((ui->lineEdit->text())!=""){
        QString Nombre = ui->lineEdit->text();
        Nombre.replace(QString(" "), QString("-"));

        int Can = Listado.count();
        int coincidencia = 0;
        for (int var = 0; var < Can; ++var) {
            if (Listado[var] == Nombre) coincidencia++;
        }
        if (coincidencia){
            ui->label_3->setText("Ya Existe");
        }
        else{
        QString Carga = "INSERT INTO 'M0TIV0S'('motivo')VALUES('" ;
        Carga += Nombre;
        Carga += "');";
        QSqlQuery Cargar;
        if(Cargar.exec(Carga)){
        ui->lineEdit->setText("");
        ui->label_3->setText("OK");
        cargarmotivos();
        emit this->HayMotivosNuevos();
        }
        }
    }
}

void NuevoMotivo::cargarmotivos()                                       //Actualizar combobox
{
        Listado.clear();
        ui->comboBox->clear();
        QString C = "SELECT * FROM M0TIV0S;";
        QSqlQuery Pregunta;
        qDebug() << "Se pregunto bien?" << Pregunta.exec(C);
        while (Pregunta.next()){
        ui->comboBox->addItem(Pregunta.value(0).toString());
        Listado << Pregunta.value(0).toString();
      }
}

void NuevoMotivo::on_pushButton_3_clicked()                             //eliminar motivo
{
    QString Seleccion = ui->comboBox->currentText();
    if (Seleccion != "Otros"){
        QString C = "DELETE FROM `M0TIV0S` WHERE `motivo`='";
        C += Seleccion;
        C += "';";
        QSqlQuery Pregunta;
        qDebug() << C;
        if (Pregunta.exec(C)){
            Seleccion = "Se elimino " + Seleccion;
            ui->label_3->setText(Seleccion);
            cargarmotivos();
            emit this->HayMotivosNuevos();
        }
    }
    else
    {
        ui->label_3->setText("'Otros' no se puede borrar");
    }
}

void NuevoMotivo::on_lineEdit_textChanged(const QString &arg1)
{
    ui->label_3->setText("");
}
