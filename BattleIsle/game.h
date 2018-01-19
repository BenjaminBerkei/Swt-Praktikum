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
 * Author: Lucas
 * Version: 0.4
 * Datum 14.01.2018
 * Kommentare: ProcessSelection bearbeitet, Dijkstra gefixed, reset funktion geändert, Player cameFrom und current_cost eingefügt,
 *              ChangePhase & Move Button Implementiert, Hilfsfunktionen  eingefügt
 * */

#ifndef GAME_H
#define GAME_H

#include "options.h"
#include "button.h"

#include "hexagonmatchfield.h"
#include "gamewidget.h"
#include "staticunit.h"
#include "dynamicunit.h"
#include "round.h"

#include <vector>
#include <QTime>
#include <QObject>
#include <queue>
#include <QVector3D>
#include <QGraphicsView>

class GameWidget; //Vorwärtsdeklaration
class HexagonMatchfield;
class Unit;
class Button;


class Game : public QObject
{
    Q_OBJECT
private:
    HexagonMatchfield* selectionCache;
    std::vector<HexagonMatchfield*> targetCache;

    std::vector<std::vector<HexagonMatchfield*>> hexagonMatchfield_gameGrid;
    std::vector<std::vector<Unit*>> unit_UnitGrid;
    std::vector<Button*> button_menueBar;

    Options* gameOptions;
    GameWidget* ptr_gameGameWid;

    std::map<HexagonMatchfield*, HexagonMatchfield*> came_from;
    std::map<HexagonMatchfield*, int> current_cost;

    Player* ptr_playerOne;
    Player* ptr_playerTwo;
    Player* ptr_playerActive;
    Round* ptr_roundCurrent;

    static std::vector<QPoint> vector_oddNeighbors;
    static std::vector<QPoint> vector_evenNeighbors;

    bool MenueView;
public:
    Game(Options* init_options, GameWidget* ptr_gameWid);
    ~Game();
    //Game(QString pathToSaveFile);
    void loadGame(QString pathToSaveFile);
    void saveGame();
    void endGame();
    void Dijkstra();

    /* Nicht im UML-Diagramm, sind nur eine Hilfsfunktionen für processSelection*/
    void resetHexMatchfield();
    void resetTargetCache();
    void moveUnitTo(HexagonMatchfield*);    //Einheit auf anderes Hex verlegen
    void showNeighbors(HexagonMatchfield*); //Nachbarn markieren -> später range markieren
    void calculateTargets(HexagonMatchfield*, int);
    void setFogOfWar();
    void showPath(HexagonMatchfield *);     //Weg einer bewegung anzeigen
    void checkUnitGrid();                   //Prüfen ob eine Einheit gestorben ist
    void checkWinCondition();               //Prüfen ob ein spieler gewonnen hat
    void resetUnits(Player*);
    void countUnits();
    int offset_distance(QPoint, QPoint);

private:
    QVector3D oddqToCube(QPoint);   //Für Referenzen betrachte https://www.redblobgames.com/grids/hexagons/#distances , Kapitel: Distance
    QPoint cubeToOddq(QVector3D);
    int cube_distance(QVector3D, QVector3D);
    /*Hilfsfunktionen Ende*/

public slots:
    void processSelection(HexagonMatchfield* selection);
    void buttonPressedMove();
    void buttonPressedAction();
    //void buttonPressedInformation();
    void buttonPressedMap();
    void buttonPressedMenue();
    void buttonPressedChangePhase();
    void SLOT_MenueButtonSelected(int);
signals:
    void gameOver();
};
class Compare
{
public:
    bool operator ()(std::pair<HexagonMatchfield *, int> a, std::pair<HexagonMatchfield *, int> b);
};

#endif // GAME_H
