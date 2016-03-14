#ifndef CHAU_H
#define CHAU_H

#include <QMainWindow>

namespace Ui {
class Chau;
}

class Chau : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chau(QWidget *parent = 0);
    ~Chau();

private slots:
    void on_actionListas_triggered();

    void on_actionNuevo_triggered();

    void on_actionVisualizar_triggered();

    void on_actionExportar_triggered();

private:
    Ui::Chau *ui;
};

#endif // CHAU_H
