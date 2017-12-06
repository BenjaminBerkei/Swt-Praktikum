#ifndef MENUEWIDGET_H
#define MENUEWIDGET_H

#include <QMainWindow>
#include <QStackedLayout>
#include "optionswidget.h"
#include "startmenuewidget.h"

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

public:
    explicit MenueWidget( QWidget *parent = 0 );
    ~MenueWidget();
};

#endif // STARTMENUEWIDGET_H
