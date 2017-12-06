/*
 * Author: Manuel
 * Version: 0.1
 * Datum 04.12.2017
 */

#ifndef OPTIONSWIDGET_H
#define OPTIONSWIDGET_H

#include <QWidget>
#include "menuewidget.h"
#include "startmenuewidget.h"

#include <QDebug>

class StartMenueWidget;

namespace Ui {
class OptionsWidget;
}

class OptionsWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::OptionsWidget *ui;

public:
    explicit OptionsWidget(QWidget *parent = 0);
    ~OptionsWidget();

    void returnToStartMenue();

private slots:
    void on_qbutton_apply_clicked();
    void on_qbutton_cancel_clicked();

signals:
    //void SIGNAL_sendOptions(bool bool_KI, bool bool_fogOfWar, string str_map, int int_roundLimit);
    void SIGNAL_optChangeIndexFromStack(int);
};

#endif // OPTIONSWIDGET_H
