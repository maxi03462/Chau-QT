#include "nuevo.h"
#include "ui_nuevo.h"
#include <QDebug>

nuevo::nuevo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::nuevo)
{
    ui->setupUi(this);
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
    QString nombre = ui->lineEdit->text();
    nombre.replace(QString(" "), QString("-"));
    //CREATE TABLE IF NOT EXISTS 'L!s74'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok INT);
    QString Consulta ="CREATE TABLE IF NOT EXISTS '";
    Consulta.append(nombre);
    Consulta.append("'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok INT);");
    QSqlQuery crear;
    qDebug() << Consulta;
    qDebug() << "Se creo la tabla1?: " << crear.exec(Consulta);
    close();
}
