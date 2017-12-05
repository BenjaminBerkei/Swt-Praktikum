/*
 * Author: Lucas
 * Version: 0.1
 * Datum 05.12.2017
 * */

#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <vector>
#include <string>
#include <QDebug>

#include "options.h"
#include "hexagonmatchfield.h"
class SaveGame
{
private:
    Options* options_savedOptions;
    //Round* round_roundState;
    //Player* player_playerOne;
    //Player* player_playerTwo;
    bool bool_activePlayer;     //0 -> playerOne, 1 -> playerTwo
    std::vector< std::vector <HexagonMatchfield* > > map_state;
public:
    SaveGame(std::string str_path);
};

#endif // SAVEGAME_H
