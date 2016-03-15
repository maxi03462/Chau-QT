#ifndef CHAU_H
#define CHAU_H

#include "nuevo.h"
#include "nuevomotivo.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtWidgets>
#include <QString>
#include <QFile>
#include <QTextStream>

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
    ~Chau();

private slots:
    void on_actionListas_triggered();

    void on_actionNuevo_triggered();

    void on_actionVisualizar_triggered();

    void on_actionExportar_triggered();

    void creartabla();

    void on_actionMotivos_triggered();

    void cargarmotivos();
private:
    Ui::Chau *ui;
    QSqlDatabase db;
    nuevo *ventana;
    NuevoMotivo *ventanamotivo;

};

#endif // CHAU_H
