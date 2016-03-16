#include "visualizar_lista.h"
#include "ui_visualizar_lista.h"
#include <QDebug>

QList<QString> Lista;

Visualizar_lista::Visualizar_lista(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Visualizar_lista)
{
    ui->setupUi(this);
    artualizarcombo();
    QString Basededatos = BaseActual();
    cargarlista(Basededatos);
}

Visualizar_lista::~Visualizar_lista()
{
    delete ui;
}

void Visualizar_lista::artualizarcombo()
{
    int Cantidad = ui->comboBox->count();
    for (int var = 0; var < Cantidad; ++var) {
        ui->comboBox->removeItem(var);
    }
    QString Basededatos = BaseActual();
    ui->comboBox->addItem(Basededatos);
    Lista << Basededatos;

    QString C = "SELECT * FROM 'L!s74';";
    QSqlQuery Pregunta;
    qDebug() << "Se pregunto bien?" << Pregunta.exec(C);
    while (Pregunta.next()){
    QString item = Pregunta.value(0).toString();
    if (item != Basededatos){
    ui->comboBox->addItem(item);
    Lista << Pregunta.value(0).toString();
    }
    }
}

void Visualizar_lista::SettablaActual(QString tabla)
{
    QFile file("List.info");
    file.open(QIODevice::Text | QIODevice::WriteOnly);
    QTextStream out(&file);
    out << tabla;
    file.close();
}

QString Visualizar_lista::BaseActual()
{
    QFile file("List.info");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString Basededatos = in.readLine();
    file.close();
    return Basededatos;
}

void Visualizar_lista::cargarlista(QString Basededatos)
{
    int fila=0;
    QString consulta ="SELECT * FROM '";
    consulta += Basededatos;
    consulta += "';";
    qDebug() << consulta;
    QSqlQuery consultar;
    consultar.prepare(consulta);
    qDebug() << consultar.exec(consulta);
    ui->tableWidget->setRowCount(0);

        while (consultar.next()){
            ui->tableWidget->insertRow(fila);
            ui->tableWidget->setItem(fila,0,new QTableWidgetItem(consultar.value(0).toByteArray().constData()));//   consultar.value(1)
            ui->tableWidget->setItem(fila,1,new QTableWidgetItem(consultar.value(1).toByteArray().constData()));
            ui->tableWidget->setItem(fila,2,new QTableWidgetItem(consultar.value(2).toByteArray().constData()));
            ui->tableWidget->setItem(fila,3,new QTableWidgetItem(consultar.value(3).toByteArray().constData()));

            QString Detalle = consultar.value(4).toByteArray().constData();
            QString Gasto = consultar.value(5).toByteArray().constData();

            if (Detalle == "")
            {
                ui->tableWidget->setItem(fila,4,new QTableWidgetItem("Sin comentario"));
            }
            else
            {
                ui->tableWidget->setItem(fila,4,new QTableWidgetItem(Detalle));
            }
            if (Gasto == "1")
            {
                ui->tableWidget->setItem(fila,5,new QTableWidgetItem("Gasto"));
            }
            else
            {
                ui->tableWidget->setItem(fila,5,new QTableWidgetItem("Ganancia"));
            }
            fila++;
        }
        ui->label_2->setText(Basededatos);
}

void Visualizar_lista::on_comboBox_currentTextChanged(const QString &arg1)
{
    cargarlista(arg1);
}





void Visualizar_lista::on_pushButton_clicked()
{
    SettablaActual(ui->comboBox->currentText());
    emit this->HayActualizacion();
    close();
}

void Visualizar_lista::on_tableWidget_cellDoubleClicked(int row, int column)
{
    QString Tabla = ui->label_2->text();

    QTableWidgetItem *Temp;
    Temp= ui->tableWidget->item(row,0);
    QString Dia = Temp->text();
    Temp = ui->tableWidget->item(row,1);
    QString Hora = Temp->text();

    QString Borra = "DELETE FROM `";
    Borra += Tabla;
    Borra += "` WHERE `dia`='";
    Borra += Dia;
    Borra += "'  AND `hora`='";
    Borra += Hora;
    Borra += "';";

    QSqlQuery Actuar;
    Actuar.exec(Borra);
    cargarlista(Tabla);
}
