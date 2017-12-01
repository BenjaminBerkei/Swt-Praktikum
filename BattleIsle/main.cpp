#include "startmenuewidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartMenueWidget w;
    w.show();

    return a.exec();
}
