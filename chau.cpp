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
    creartabla();
    cargarmotivos();

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
    ventana = new nuevo(this,this);
    ventana->showMaximized();
}

void Chau::on_actionVisualizar_triggered()
{

}

void Chau::on_actionExportar_triggered()
{

}

void Chau::creartabla()
{
    // CREATE TABLE IF NOT EXISTS 'L!s74'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok INT);
    // creamos la tabla para la lista de las tablas
    QString Consulta1 ="CREATE TABLE IF NOT EXISTS 'L!s74'(listado VARCHAR(255));";
    QSqlQuery crear1;
    qDebug() << "Se creo la tabla1?: " << crear1.exec(Consulta1);
    /*------------------------------------------------------------------------------*/
    QString Consulta2 ="CREATE TABLE IF NOT EXISTS 'M0TIV0S'(motivo VARCHAR(255));";
    QSqlQuery crear2;
    qDebug() << "Se creo la tabla2?: " << crear2.exec(Consulta2);
    /*------------------------------------------------------------------------------*/
    QString consulta ="SELECT count(motivo) FROM M0TIV0S;";
    QSqlQuery crear;
    crear.prepare(consulta);
    qDebug() << "Se conto bien??" << crear.exec();
    crear.next();
    if (!crear.value(0).toInt()){
        consulta ="INSERT INTO M0TIV0S(motivo)VALUES('Otros');";
        QSqlQuery insertar;
        insertar.exec(consulta);
        qDebug() << "Se creo la opcion 'Otros'";
    }
}

void Chau::SettablaActual(QString tabla)
{
    QFile file("List.info");
    file.open(QIODevice::Text | QIODevice::WriteOnly);
    QTextStream out(&file);
    out << tabla;
    file.close();
}

void Chau::on_actionMotivos_triggered()
{

}

void Chau::cargarmotivos()
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
