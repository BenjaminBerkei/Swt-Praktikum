/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 * */

#include "game.h"

Game::Game(Options *init_options, GameWidget *ptr_gameWid) :
    SelectionCache(NULL),
    gameOptions(init_options),
    ptr_gameGameWid(ptr_gameWid)
{

}
