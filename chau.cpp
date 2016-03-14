#include "chau.h"
#include "ui_chau.h"

Chau::Chau(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chau)
{
    ui->setupUi(this);
}

Chau::~Chau()
{
    delete ui;
}





void Chau::on_actionListas_triggered()
{

}

void Chau::on_actionNuevo_triggered()
{

}

void Chau::on_actionVisualizar_triggered()
{

}

void Chau::on_actionExportar_triggered()
{

}
