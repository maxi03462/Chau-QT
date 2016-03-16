#include "chau.h"
#include "ui_chau.h"
#include <QDebug>

Chau::Chau(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chau)
{
    ui->setupUi(this);

    ui->lineEdit->setInputMethodHints(Qt::ImhPreferNumbers);
    ui->lineEdit->setInputMethodHints(Qt::ImhFormattedNumbersOnly);

    /*-crear/cargar base de datos----------------------------------*/
    QString nombreSQL = "Chau.sqlite";
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(nombreSQL);
    db.open();
    creartabla();
    cargarmotivos();
    primertablar();
    ui->Lista_actual->setText(BaseActual());
    contar();
}

Chau::~Chau()
{
    delete ui;
}

void Chau::on_actionListas_triggered()
{

}

void Chau::primertablar()
{
    QString Tabla = "SELECT * FROM 'L!s74';";
    QSqlQuery Leer;
    Leer.exec(Tabla);
    Leer.next();
    QString Leido = Leer.value(0).toString();
    if (Leido == ""){
        QString Crear = "CREATE TABLE IF NOT EXISTS 'Principal'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),motivo VARCHAR(255),detalle VARCHAR(255),ok INT);";
        QSqlQuery Crea;
        qDebug() << "Se creo la tabla" <<Crea.exec(Crear);
        QString Anadir = "INSERT INTO `L!s74`(`listado`) VALUES ('Principal');";
        QSqlQuery Agregar;
        qDebug() << "Se agrego al listado" << Agregar.exec(Anadir);
        SettablaActual("Principal");
    }
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
    // CREATE TABLE IF NOT EXISTS 'L!s74'(dia VARCHAR(255),hora VARCHAR(255),gasto VARCHAR(255),comentario VARCHAR(255),ok VARCHAR(255));
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
    ventanamotivo = new NuevoMotivo();
    ventanamotivo->showMaximized();
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

void Chau::on_pushButton_2_clicked() //Gasto
{
    /*----------------------------------------------*/
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString Hora = time.toString("hh:mm:ss");
    QString Fecha = date.toString("dd/MM/yyyy");
    /*----------------------------------------------*/
    QString Pesos = ui->lineEdit->text();
    QString Motivo = ui->comboBox->currentText();
    QString Detalles = ui->lineEdit_2->text();
    /*----------------------------------------------*/
    QString Basededatos = BaseActual();
    /*----------------------------------------------*/

    if(Pesos != ""){
        QString Consulta ="INSERT INTO '";
        Consulta += Basededatos;
        Consulta += "'(dia,hora,gasto,motivo,detalle,ok)VALUES('";
        Consulta += Fecha;
        Consulta += "','";
        Consulta += Hora;
        Consulta += "','";
        Consulta += Pesos;
        Consulta += "','";
        Consulta += Motivo;
        Consulta += "','";
        Consulta += Detalles;
        Consulta += "','";
        Consulta += "1";        //Gasto es 1
        Consulta += "');";
        qDebug() << Consulta;
        QSqlQuery Insertar;
        qDebug() << "se creo??" << Insertar.exec(Consulta);
    }
}

QString Chau::BaseActual()
{
    QFile file("List.info");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString Basededatos = in.readLine();
    file.close();
    return Basededatos;
}

void Chau::on_pushButton_clicked()
{
    /*----------------------------------------------*/
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();
    QString Hora = time.toString("hh:mm:ss");
    QString Fecha = date.toString("dd/MM/yyyy");
    /*----------------------------------------------*/
    QString Pesos = ui->lineEdit->text();
    QString Motivo = ui->comboBox->currentText();
    QString Detalles = ui->lineEdit_2->text();
    /*----------------------------------------------*/
    QString Basededatos = BaseActual();
    /*----------------------------------------------*/

    if(Pesos != ""){
        QString Consulta ="INSERT INTO '";
        Consulta += Basededatos;
        Consulta += "'(dia,hora,gasto,motivo,detalle,ok)VALUES('";
        Consulta += Fecha;
        Consulta += "','";
        Consulta += Hora;
        Consulta += "','";
        Consulta += Pesos;
        Consulta += "','";
        Consulta += Motivo;
        Consulta += "','";
        Consulta += Detalles;
        Consulta += "','";
        Consulta += "0";        //Ganancia es 0
        Consulta += "');";
        qDebug() << Consulta;
        QSqlQuery Insertar;
        qDebug() << "se creo??" << Insertar.exec(Consulta);
    }
}

void Chau::contar()
{
    QString Basededatos = BaseActual();
    QSqlQuery consultar;
    float Total = 0;
    QString consulta ="SELECT * FROM '";
    consulta += Basededatos;
    consulta += "';";
    consultar.exec(consulta);
    while (consultar.next()) {
        QString tmp2 = consultar.value(2).toString();
        float tmp = consultar.value(2).toFloat();
        Total += tmp;
    }
    ui->label_3->setText(QString::number(Total, 'f', 2));
}
