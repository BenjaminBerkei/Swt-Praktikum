/*
 * Author: Manuel
 * Version: 0.1
 * Datum 04.12.2017
 */

#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include "startmenuewidget.h"

class StartMenueWidget;

namespace Ui {
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::OptionsWidget *ui;
    QWidget *ptr_optParent;
    StartMenueWidget *ptr_optStartMenueWidget;


public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();

    void returnToStartMenue();

private slots:
    void on_qbutton_apply_clicked();
    void on_qbutton_cancel_clicked();

signals:
    //SIGNAL_sendOptions(bool bool_KI, bool bool_fogOfWar, string str_map, int int_roundLimit);
};

#endif // OPTIONSWIDGET_H
