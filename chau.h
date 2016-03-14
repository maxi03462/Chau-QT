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

private:
    Ui::Chau *ui;
};

#endif // CHAU_H
