#include "chau.h"
#include "ui_chau.h"
#include <QDebug>

Chau::Chau(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chau)
{
    ui->setupUi(this);
    /*-crear/cargar base de datos----------------------------------*/
    QString nombreSQL = "Chau.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombreSQL);
    db.open();
    creartabla1();
    creartabla2();
}

Chau::~Chau()
{
    delete ui;
}

void Chau::on_actionListas_triggered()
{

}

void Chau::on_actionNuevo_triggered()
{

}

void Chau::on_actionVisualizar_triggered()
{

}

void Chau::on_actionExportar_triggered()
{

}

void Chau::creartabla1()
{
    // CREATE TABLE IF NOT EXISTS 'L!s74'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok INT);
    // creamos la tabla para la lista de las tablas
    QString Consulta ="CREATE TABLE IF NOT EXISTS 'L!s74'(listado VARCHAR(255));";
    QSqlQuery crear;
    qDebug() << "Se creo la tabla1?: " << crear.exec(Consulta);
}

void Chau::creartabla2()
{
    //CREATE TABLE IF NOT EXISTS 'M0TIV0S'(motivo VARCHAR(255));
    QString Consulta ="CREATE TABLE IF NOT EXISTS 'M0TIV0S'(motivo VARCHAR(255));";
    QSqlQuery crear;
    qDebug() << "Se creo la tabla2?: " << crear.exec(Consulta);
}
