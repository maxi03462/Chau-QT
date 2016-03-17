#ifndef NUEVOMOTIVO_H
#define NUEVOMOTIVO_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

namespace Ui {
class NuevoMotivo;
}

class NuevoMotivo : public QMainWindow
{
    Q_OBJECT

public:
    explicit NuevoMotivo(QWidget *parent = 0);
    ~NuevoMotivo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void cargarmotivos();

    void on_pushButton_3_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::NuevoMotivo *ui;

signals:
    void HayMotivosNuevos();
};

#endif // NUEVOMOTIVO_H
