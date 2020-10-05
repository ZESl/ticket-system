#include "ticketsystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ticketsystem w;
    w.show();
    return a.exec();
}
