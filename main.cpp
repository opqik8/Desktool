#include "mainoperate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainOperate w;
    w.show();

    return a.exec();
}
