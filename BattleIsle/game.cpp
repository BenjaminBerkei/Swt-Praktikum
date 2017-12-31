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
    ptr_gameGameWid->setGameWidGame(this);
    qDebug() << "Bemerkung: Objekt game erstellt mit " << gameOptions;

    // Erstelle eine Map
    // Dies ist nur für Testzwecke! Sollte später gelöscht werden:
    //##################################################################
    int sizeX = 20;
    int sizeY = 20;


    //HexagonMatchfield(QPoint (*,*), string type)
    //Mögliche Typen:
    //"waterDeep"           (Tiefes Meer)
    //"waterSeashore"       (Küste)
    //"forrest"             (Wald)
    //"grassland"           (Wiese)
    //"streetStraight"      (Straße Gerade)
    //"streetCurve"         (Straße mit Kurve)
    //"mountainTop"         (Bergspitze)
    //"mountainSide"        (Bergseite)
    //"boltanium"           (Boltanium)

    for( int i = 0; i < sizeX; i++ )
    {
        vector<HexagonMatchfield*> vectorHex;
        for( int j = 0; j < sizeY; j++ )
        {
            if( i == 0 || i == sizeX || j == 0 || j == sizeY )
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "waterDeep"));
            else if( i == 1 || i == sizeX - 1 || j == 1 || j == sizeY - 1 )
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "waterSeashore"));
            else
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "grassland"));
        }
        hexagonMatchfield_gameGrid.push_back(vectorHex);
    }

    qDebug() << "Bemerkung: Feld erstellt (in Klasse Game)";

    ptr_gameGameWid->gameWidCreateMatchfield();

    //##################################################################
}

HexagonMatchfield *Game::getVectorVectorHexagonMatchfield(int x, int y)
{
    return hexagonMatchfield_gameGrid[x][y];
}
