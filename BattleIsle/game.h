/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 * */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "options.h"
#include "hexagonmatchfield.h"
#include "button.h"
#include "gamewidget.h"
//#include "unit.h"

using namespace std;

class GameWidget; //Vorwärtsdeklaration

class Game
{
private:
    HexagonMatchfield* SelectionCache;
    vector<HexagonMatchfield*> TargetChache;
    //vector<vector<Unit*>> unit_UnitGrid;
    vector<Button*> button_menueBar;
    Options* gameOptions;
    GameWidget* ptr_gameGameWid;

public:
    vector<vector<HexagonMatchfield*>> hexagonMatchfield_gameGrid;

    Game(Options* init_options, GameWidget* ptr_gameWid);
    //Game(SaveGame* savegame_initSave);
    //void loadGame(SaveGame* savegame_initSave);
    //void saveGame();
    //void endGame();
    //int showUnitNumber(Player* player);
    //int showTotalEnergie(Player* player);
    // ...

    // get und set Methoden
    HexagonMatchfield* getVectorVectorHexagonMatchfield(int x, int y);
};

#endif // GAME_H
