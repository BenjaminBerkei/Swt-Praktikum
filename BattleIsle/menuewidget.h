/*
 * Author: Manuel
 * Version: 0.3
 * Datum 07.12.2017
 */

#ifndef MENUEWIDGET_H
#define MENUEWIDGET_H

#include <QMainWindow>
#include <QStackedLayout>
#include "optionswidget.h"
#include "startmenuewidget.h"
#include "loadgamewidget.h"

#include <QDebug>

class OptionsWidget;

namespace Ui {
    class MenueWidget;
}

class MenueWidget : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MenueWidget *ui;
    StartMenueWidget *ptr_mwStartMenueWidget;
    OptionsWidget *ptr_mwOptionsWidget;
    LoadGameWidget *ptr_mwLoadGameWidget;

public:
    explicit MenueWidget( QWidget *parent = 0 );
    ~MenueWidget();

    //get und set Methoden
    StartMenueWidget* getPtr_mwStartMenueWidget() { return ptr_mwStartMenueWidget; }
};

#endif // STARTMENUEWIDGET_H
