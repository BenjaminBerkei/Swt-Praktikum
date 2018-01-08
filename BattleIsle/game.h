/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 * */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <QTime>
#include <QObject>
#include "options.h"
#include "hexagonmatchfield.h"
#include "button.h"
#include "gamewidget.h"
#include "unit.h"

class GameWidget; //Vorwärtsdeklaration
class HexagonMatchfield;
class Unit;
class Button;

class Game : public QObject
{
    Q_OBJECT
private:
    HexagonMatchfield* SelectionCache;
    std::vector<HexagonMatchfield*> TargetChache;
    std::vector<std::vector<HexagonMatchfield*>> hexagonMatchfield_gameGrid;
    std::vector<std::vector<Unit*>> unit_UnitGrid;
    std::vector<Button*> button_menueBar;
    Options* gameOptions;
    GameWidget* ptr_gameGameWid;

public:
    Game(Options* init_options, GameWidget* ptr_gameWid);
    //Game(SaveGame* savegame_initSave);
    //void loadGame(SaveGame* savegame_initSave);
    //void saveGame();
    //void endGame();
    //int showUnitNumber(Player* player);
    //int showTotalEnergie(Player* player);
    // ...

    // get und set Methoden
    std::vector<std::vector<HexagonMatchfield*>> getVectorVectorHexagonMatchfield();

public slots:
    void SLOT_processSelection(HexagonMatchfield* selection);
};

#endif // GAME_H
