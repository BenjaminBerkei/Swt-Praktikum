#include "displayhextest.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    displayHexTest w;
    w.show();

    return a.exec();
}
