/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 * */
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <vector>
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
    Game* gameWidGame;
    QGraphicsScene *gameWidGameScene;
    QGraphicsScene *gameWidInfoScene;
    QGraphicsScene *gameWidOptionsScene;
    QGraphicsScene *gameWidButtonScene;

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void gameWidCreateMatchfield();

    //get und set Methoden
    void setGameWidGame(Game* game) { gameWidGame = game; }


signals:
    void SIGNAL_gameWidChangeIndexFromStack(int);
};

#endif // GAMEWIDGET_H
