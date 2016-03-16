#ifndef CHAU_H
#define CHAU_H

#include "nuevo.h"
#include "nuevomotivo.h"
#include "visualizar_lista.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QTime>
#include <QDate>

class nuevo;
namespace Ui {
class Chau;
}

class Chau : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chau(QWidget *parent = 0);
    void SettablaActual(QString tabla);
    void contar();
    ~Chau();

private slots:

    void on_actionNuevo_triggered();

    void on_actionVisualizar_triggered();

    void on_actionExportar_triggered();

    void creartabla();

    void on_actionMotivos_triggered();

    void cargarmotivos();

    void on_actionListas_triggered();

    void primertablar();

    void on_pushButton_2_clicked();

    QString BaseActual();

    void on_pushButton_clicked();

private:
    Ui::Chau *ui;
    QSqlDatabase db;
    nuevo *ventana;
    NuevoMotivo *ventanamotivo;
    Visualizar_lista *verlista;

};

#endif // CHAU_H
