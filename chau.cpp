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

void Chau::on_actionListas_triggered()      //Pantalla de las listas
{
    verlista = new Visualizar_lista();
    verlista->showMaximized();
    QObject::connect(verlista, SIGNAL(HayActualizacion()),this, SLOT(ActualizarDatos()));
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

void Chau::on_actionNuevo_triggered()       //Ventana de las listas nuevas
{
    ventana = new nuevo(this,this);
    ventana->showMaximized();
}

void Chau::on_actionExportar_triggered()    //Exportar datos
{
    QList<QString> Tablas;

    QString consulta ="SELECT * FROM 'L!s74'";
    QSqlQuery consultar;
    consultar.prepare(consulta);
    consultar.exec();
    while(consultar.next()){
        Tablas << consultar.value(0).toString();
    }
    int total = Tablas.count();
            for (int var = 0; var < total; ++var) {
        Exportar(Tablas[var]);
    }
}

void Chau::Exportar(QString Nombre)         //Funcion utilizada en exportar
{
    QString Dir  =  "/storage/emulated/0/Chau/";

    QDir dir(Dir);
    if (!dir.exists()) {
        qDebug() << dir.mkpath(Dir);
    }

    QString nombre = Nombre;
    nombre.replace(QString("/"), QString("-"));
    Dir += nombre;
    Dir += ".csv";
    qDebug() << Dir;
    QFile file(Dir);
    file.open(QIODevice::Text | QIODevice::WriteOnly);
    QTextStream out(&file);

    QString consulta ="SELECT * FROM '";
    consulta += Nombre;
    consulta += "';";
    QSqlQuery consultar;
    qDebug() << consulta;
    qDebug() << consultar.exec(consulta);

    QDate date = QDate::currentDate();
    QString Fecha = date.toString("dd/MM/yyyy");

    out << "Exportado el dia:" << Fecha << "\n";
    out << "Dia;Hora;$;Motivo;Detalle;Gasto o Ganancia \n";

    int Pasadas = 0;
    while(consultar.next()){
        out << consultar.value(0).toString() << ";" << consultar.value(1).toString() << ";";

        if ((consultar.value(5).toString()) == "1"){
            QString Pesos =consultar.value(2).toString();
            Pesos.replace(QString("."), QString(","));
            out << "-" << Pesos;
        }
        else
        {
            QString Pesos =consultar.value(2).toString();
            Pesos.replace(QString("."), QString(","));
            out << "+" << Pesos;
        }

        out << ";" << consultar.value(3).toString() << ";" << consultar.value(4).toString() << ";";

        if ((consultar.value(5).toString()) == "1"){
            out << "Gasto" << "\n";
        }
        else
        {
            out << "Ganancia" << "\n";
        }
        Pasadas++;
    }
    if (Pasadas != 0){
    out << ";Total:;=SUMA(C3:C" ;
    Pasadas += 2;
    out << QString::number(Pasadas);
    out << ");;;";
    }
    file.close();
}

void Chau::creartabla()                     //Se crean las tablas lista y motivo
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

void Chau::SettablaActual(QString tabla)    //Setea la tabla sobre la cual trabajar
{
    QFile file("List.info");
    file.open(QIODevice::Text | QIODevice::WriteOnly);
    QTextStream out(&file);
    out << tabla;
    file.close();
}

void Chau::on_actionMotivos_triggered()     //Pantalla de los motivos
{
    ventanamotivo = new NuevoMotivo();
    ventanamotivo->showMaximized();
    QObject::connect(ventanamotivo, SIGNAL(HayMotivosNuevos()),this, SLOT(cargarmotivos()));
}

void Chau::cargarmotivos()                  //obtiene los motivos listados
{
    ui->comboBox->clear();
    QString C = "SELECT * FROM M0TIV0S;";
    QSqlQuery Pregunta;
    qDebug() << "Se pregunto bien?" << Pregunta.exec(C);
    while (Pregunta.next()){
    ui->comboBox->addItem(Pregunta.value(0).toString());
    }

}

QString Chau::BaseActual()                  //Me dice que Base se esta usando
{
    QFile file("List.info");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString Basededatos = in.readLine();
    file.close();
    return Basededatos;
}

void Chau::on_pushButton_2_clicked()        //Gasto
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
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        contar();
    }
}

void Chau::on_pushButton_clicked()          //Ganancia
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
        ui->lineEdit->setText("");
        ui->lineEdit_2->setText("");
        contar();
    }
}

void Chau::ActualizarDatos()                //Me actualiza los datos cuando cambio de base
{
    ui->Lista_actual->setText(BaseActual());
    contar();
}

void Chau::contar()                         //Me da el valor Total
{
    QString Basededatos = BaseActual();
    QSqlQuery consultar;
    double Total = 0;
    QString consulta ="SELECT * FROM '";
    consulta += Basededatos;
    consulta += "';";
    consultar.exec(consulta);
    while (consultar.next()) {
    float tmp = consultar.value(2).toDouble();

        if ((consultar.value(5).toString()) == "1"){
            Total -= tmp;
        }
        else
        {
            Total += tmp;
        }
    }
    ui->label_3->setText(QString::number(Total, 'd', 2));
    ui->Lista_actual->setText(BaseActual());
}
