#include "matchfield.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Matchfield w;
    w.show();

    return a.exec();
}
