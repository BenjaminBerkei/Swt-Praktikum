/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 *
 * Author: Manuel
 * Version: 0.3
 * Datum: 12.01.2018
 * Kommentar: Buttons hinzugefuegt
 *
 * Author: Lucas, Manuel
 * Version: 0.4
 * Datum: 13.01.2018
 * */
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <vector>
#include "hexagonmatchfield.h"
#include "button.h"

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
    QGraphicsScene *gameWidGameScene;
    QGraphicsScene *gameWidInfoScene;
    QGraphicsScene *gameWidOptionsScene;
    QGraphicsScene *gameWidButtonScene;
    int sizeX;
    int sizeY;

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void gameWidCreateMatchfield(std::vector<std::vector<HexagonMatchfield*>> &hexagonGrid);
    void gameWidcreateButtonBar(std::vector<Button *> buttonVector);
    void setInfoScene(HexagonDisplayInfo *info);
    void clearScenes();

    //get und set Methoden
    QGraphicsScene *getGameWidInfoScene() const;

    int getSizeX() const;
    int getSizeY() const;

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
    QString qStringUnitDispUnitType;
    QString qStringUnitDispUnitLife;
    QString qStringUnitDispMovement;
    QString qStringUnitDispUnitAttack;
public:
    HexagonDisplayInfo(HexagonMatchfield* ptr_hexMfield);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void updateText();
};

#endif // GAMEWIDGET_H
