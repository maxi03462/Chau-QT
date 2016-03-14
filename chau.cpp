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
