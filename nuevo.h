#ifndef NUEVO_H
#define NUEVO_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>

namespace Ui {
class nuevo;
}

class nuevo : public QMainWindow
{
    Q_OBJECT

public:
    explicit nuevo(QWidget *parent = 0);
    void teEscribo(&QString dato);
    ~nuevo();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::nuevo *ui;
};

#endif // NUEVO_H
