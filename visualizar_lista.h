#ifndef VISUALIZAR_LISTA_H
#define VISUALIZAR_LISTA_H

#include <QMainWindow>
#include <QDialog>
#include <QTextStream>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QFile>

namespace Ui {
class Visualizar_lista;
}

class Visualizar_lista : public QMainWindow
{
    Q_OBJECT

public:
    explicit Visualizar_lista(QWidget *parent = 0);
    ~Visualizar_lista();

private:
    Ui::Visualizar_lista *ui;

private slots:
    void artualizarcombo();

    void SettablaActual(QString tabla);

    QString BaseActual();

    void cargarlista(QString Basededatos);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_tableWidget_cellDoubleClicked(int row, int column);

signals:
    void HayActualizacion();
};

#endif // VISUALIZAR_LISTA_H
