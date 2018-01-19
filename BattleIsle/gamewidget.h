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
 *
 * Author: Lucas
 * Version: 0.5
 * Datum: 14.01.2018
 * Kommentar: Label für den zustand des spiels eingefügt: player & playerUnitNumber
 * */
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <vector>
#include "hexagonmatchfield.h"
#include "unit.h"
#include "button.h"
#include "player.h"
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class Unit;
class Player;

namespace Ui {
class GameWidget;
}

class Game; //Vorwärtsdeklaration
class HexagonMatchfield;
class HexagonDisplayInfo;
class MapPixel;

class GameWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::GameWidget *ui;
    QGraphicsScene *gameWidGameScene;
    QGraphicsScene *gameWidInfoScene;
    QGraphicsScene *gameWidOptionsScene;
    QGraphicsScene *gameWidButtonScene;
    QGraphicsScene *gameWidMenueScene;
    QGraphicsScene *gameWidMapScene;

    QGraphicsTextItem *textItem_currentPlayer;
    QGraphicsTextItem *textItem_currentEnergie;
    QGraphicsTextItem *textItem_currentUnits;
    QGraphicsTextItem *textItem_currentPhase;

    QPushButton* qbuttonSaveGame;
    QPushButton* qbuttonEndGame;
    QPushButton* qbuttonLoadGame;
    QPushButton* qbuttonResume;

    int sizeX;
    int sizeY;

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();
    void resizeEvent(QResizeEvent*, int mainHeight, int mainWdith);
    void gameWidCreateMatchfield(std::vector<std::vector<HexagonMatchfield*>> &hexagonGrid);
    void gameWidCreateButtonBar(std::vector<Button *> buttonVector);
    void gameWidCreateMap(std::vector<std::vector<HexagonMatchfield*>> &hexagonGrid); //Erstellt die Map Uebersicht
    void clearButtonScene();
    void clearInfoScene();
    void clearOptionsScene();
    void clearGameScene();
    void clearAllScenes(); //Loescht alle Scenen
    void resetGameWidget();
    void setEnableButtonScene(bool);
    void updateInfoOptScenes();
    void updateMatchfieldScene();
    void repaintGameView();
    void animateUnit(Unit*, std::vector<QPointF>);


    //get und set Methoden
    void setInfoScene(HexagonDisplayInfo *info);
    void setOptScene(std::vector<Unit*>);
    void setPlayerLabel(QString);
    void setPhaseLabel(QString);
    void setUnitsLabel(int value);
    void setEnergieLabel(int current, int max);
    int getSizeX() const;
    int getSizeY() const;
    QGraphicsScene *getGameWidInfoScene() const;
    QGraphicsScene *getGameWidOptionsScene() const;
    QGraphicsScene *getGameWidGameScene() const;
    QGraphicsScene *getGameWidButtonScene() const;
    QGraphicsScene *getGameWidMenueScene() const;
    QGraphicsView* getGameWidGameView() const;
    QGraphicsScene *getGameWidMapScene() const;

private:
    void gameWidCreateMenueScene();

private slots:
    void SLOT_qbuttonSaveGame_clicked();
    void SLOT_qbuttonLoadGame_clicked();
    void SLOT_qbuttonEndGame_clicked();
    void SLOT_qbuttonResume_clicked();

signals:
    void SIGNAL_gameWidChangeIndexFromStack(int);
    void SIGNAL_MenueButtonPushed(int);
};

//Klasse um die Hexagons in der Infobox anzeigen zu lassen
class HexagonDisplayInfo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    HexagonMatchfield* hexToDisplay;
    QString qStringHexDispHexType;
    QString qStringUnitDispUnitName;
    QString qStringUnitDispUnitType;
    QString qStringUnitDispUnitLife;
    QString qStringUnitDispMovement;
    QString qStringUnitDispUnitAttack;
public:
    HexagonDisplayInfo(HexagonMatchfield* ptr_hexMfield);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void updateText();
};

//Klasse um die Hexagons in der Infobox anzeigen zu lassen
class UnitDisplayInfo : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    Unit* ptr_UnitToDisplay;
    QString qStringUnitDispUnitName;
    QString qStringUnitDispUnitType;
    QString qStringUnitDispUnitLife;
    QString qStringUnitDispMovement;
    QString qStringUnitDispUnitAttack;
    QString qStringUnitDispUnitCost;
    QColor color;

public:
    UnitDisplayInfo(Unit* ptr_Unit);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void updateText();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(const QColor &value);

signals:
    void unitDispl_clicked(Unit* unit);
};


class MapPixel : public QGraphicsRectItem
{
private:
    Qt::GlobalColor colorRect;
public:
    MapPixel(int x, int y, Qt::GlobalColor color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
    QRectF boundingRect();
};
#endif // GAMEWIDGET_H
