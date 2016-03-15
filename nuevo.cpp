#include "nuevo.h"
#include "ui_nuevo.h"
#include <QDebug>

nuevo::nuevo(Chau *esta, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::nuevo)
{
    ui->setupUi(this);
    miChau = esta;
    ui->lineEdit->setText("");
}

nuevo::~nuevo()
{
    delete ui;
}

void nuevo::on_pushButton_clicked()
{
    close();
}

void nuevo::on_pushButton_2_clicked()
{
    if((ui->lineEdit->text()) != ""){
    QString nombre = ui->lineEdit->text();
    nombre.replace(QString(" "), QString("-"));

    QString Ext = "SELECT * FROM 'L!s74';";
    QSqlQuery existe;
    existe.exec(Ext);
    int coincidencia = 0;
    QString text;
    while (existe.next()) {
        text = existe.value(0).toString();
        if(text == nombre) coincidencia++;
    }

    if(!coincidencia){
    //CREATE TABLE IF NOT EXISTS 'L!s74'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok INT);
    QString Consulta ="CREATE TABLE IF NOT EXISTS '";
    Consulta.append(nombre);
    Consulta.append("'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok INT);");
    QSqlQuery crear;
    qDebug() << Consulta;
    qDebug() << "Se creo la tabla " << nombre << "?" << crear.exec(Consulta);
    /*--------------------------------------------------------------------------------------------------------------------*/

    //INSERT INTO `L!s74`(`listado`) VALUES ("'Holaa'");

    QString Ins ="INSERT INTO `L!s74`(`listado`) VALUES ('";
    Ins.append(nombre);
    Ins += "');";
    QSqlQuery insertar;
    qDebug() << "Comando" << Ins;
    if (insertar.exec(Ins)){
        qDebug() << "Se creo la entrada";
        ui->label_2->setText("Todo OK");
        miChau->SettablaActual(nombre);
            close();
    }
    else{
        ui->label_2->setText("Algo salio mal");
        qDebug() << "No se creo la entrada";
    }
    }
    else{
        ui->label_2->setText("Ya Existe");
        ui->lineEdit->setText("");
    }
    }
}
