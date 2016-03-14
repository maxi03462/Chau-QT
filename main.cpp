#include "chau.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Chau w;
    w.show();

    return a.exec();
}
