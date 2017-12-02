#include "matchfield.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Matchfield w("/home/lucas/Schreibtisch/GitTest/Swt-Praktikum/Matchfield/maps/testMap.txt");
    w.show();

    return a.exec();
}
