/*
 * Author: Manuel
 * Version: 0.1
 * Datum 04.12.2017
 */

#ifndef STARTMENUEWIDGET_H
#define STARTMENUEWIDGET_H

#include <QWidget>
#include "options.h"

#include <QDebug>

namespace Ui {
class StartMenueWidget;
}

class StartMenueWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::StartMenueWidget *ui;
    Options *ptr_smwOptions;

public:
    explicit StartMenueWidget(QWidget *parent = 0);
    ~StartMenueWidget();
    //void startGame(Options* options_initOptions);
    void switchToOptions();
    void switchToLoadGame();

private slots:
    void on_qbutton_startGame_clicked();
    void on_qbutton_loadGame_clicked();
    void on_qbutton_options_clicked();

signals:
    void SIGNAL_smwChangeIndexFromStack(int);

};

#endif // STARTMENUEWIDGET_H
