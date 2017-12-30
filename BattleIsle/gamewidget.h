/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 * */
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "game.h"

namespace Ui {
class GameWidget;
}

class Game; //Vorwärtsdeklaration

class GameWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::GameWidget *ui;
    Game* GameWidGame;

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

    //get und set Methoden
    void setGameWidGame(Game* game) { GameWidGame = game; }

signals:
    void SIGNAL_gameWidChangeIndexFromStack(int);
};

#endif // GAMEWIDGET_H
