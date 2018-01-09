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
#include "hexagonmatchfield.h"

namespace Ui {
class GameWidget;
}

class Game; //Vorwärtsdeklaration
class HexagonMatchfield;
class HexagonDisplayInfo;

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
    void setInfoScene(HexagonDisplayInfo *info);

signals:
    void SIGNAL_gameWidChangeIndexFromStack(int);
};

//Klasse um die Hexagons in der Infobox anzeigen zu lassen
class HexagonDisplayInfo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    HexagonMatchfield* hexToDisplay;
    QString qStringHexDispHexType;

public:
    HexagonDisplayInfo(HexagonMatchfield* ptr_hexMfield);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    //void update();
};

#endif // GAMEWIDGET_H
