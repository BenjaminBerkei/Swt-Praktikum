/*
 * Author: Manuel
 * Version: 0.3
 * Datum 07.12.2017
 */


#ifndef STARTMENUEWIDGET_H
#define STARTMENUEWIDGET_H

#include <QWidget>
#include "options.h"
#include "menuewidget.h"
#include "ui_menuewidget.h"
#include "gamewidget.h"
#include <QDebug>

namespace Ui {
class StartMenueWidget;
class MenueWidget;
}


class MenueWidget; //Vorwärtsdeklaration
class GameWidget; //Vorwärtsdeklaration

class StartMenueWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::StartMenueWidget *ui;
    Options *ptr_smwOptions;
    MenueWidget* ptr_smwMenueWidget;

public:
    explicit StartMenueWidget(QWidget *parent = 0, MenueWidget* ptr_menueWidget = 0);
    ~StartMenueWidget();
    void startGame(Options* options_initOptions);
    void switchToOptions();
    void switchToLoadGame();
    void smwUpdateSettings(); //Updatet die Anzeige der eingestellten Optionen

    //get und set Methoden
    Options* getPtr_smwOptions() { return ptr_smwOptions; }

private slots:
    void on_qbutton_startGame_clicked();
    void on_qbutton_loadGame_clicked();
    void on_qbutton_options_clicked();

signals:
    void SIGNAL_smwChangeIndexFromStack(int);

};

#endif // STARTMENUEWIDGET_H
