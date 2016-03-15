#ifndef NUEVO_H
#define NUEVO_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "chau.h"

class Chau;
namespace Ui {
class nuevo;
}

class nuevo : public QMainWindow
{
    Q_OBJECT

public:
    explicit nuevo(Chau *esta, QWidget *parent = 0);
    ~nuevo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::nuevo *ui;
    Chau *miChau;
};

#endif // NUEVO_H
