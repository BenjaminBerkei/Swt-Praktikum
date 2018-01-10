/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 * */

#include "game.h"
using namespace std;

Game::Game(Options *init_options, GameWidget *ptr_gameWid) :
    SelectionCache(NULL),
    gameOptions(init_options),
    ptr_gameGameWid(ptr_gameWid)
{
    ptr_gameGameWid->setGameWidGame(this);

    // Erstelle eine Map
    // Dies ist nur für Testzwecke! Sollte später gelöscht werden:
    //##################################################################
    //Größe
    int sizeX = 50;
    int sizeY = 20;

    //Für eine Zufallszahl
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

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
            if( i == 0 || i == sizeX-1 || j == 0 || j == sizeY-1 )
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "waterDeep", 0, this));
            else if( i == 1 || i == sizeX - 2 || j == 1 || j == sizeY - 2 )
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "waterSeashore", 0, this));
            else
            {
                int modulo = 10;
                if(hexagonMatchfield_gameGrid[i-1][j]->getHexMatchfieldType() == "forrest")
                    modulo += 6;
                if(hexagonMatchfield_gameGrid[i-1][j-1]->getHexMatchfieldType() == "forrest")
                    modulo += 6;
                if(vectorHex[j-1]->getHexMatchfieldType() == "forrest")
                    modulo += 6;
                int randomInt = qrand() % modulo;
                if(randomInt < 8)
                    if(randomInt < 1)
                        vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "mountainTop", 0, this));
                    else
                        vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "grassland", 0, this));
                else
                    vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "forrest", 0, this));
            }
        }
        hexagonMatchfield_gameGrid.push_back(vectorHex);
    }

    qDebug() << "Bemerkung: Zufallsfeld erstellt (in Klasse Game). Nur für Testzwecke.";

    ptr_gameGameWid->gameWidCreateMatchfield();

    //##################################################################
}

vector<vector<HexagonMatchfield*> > Game::getVectorVectorHexagonMatchfield()
{
    return hexagonMatchfield_gameGrid;
}

void Game::SLOT_processSelection(HexagonMatchfield *selection)
{
    SelectionCache = selection;
    if(SelectionCache->getState() == INACTIVE)
    {
        //Alle Hexagons auf INACIVE setzten
        for(unsigned int i = 0; i < hexagonMatchfield_gameGrid.size(); i++)
        {
            for(unsigned int j = 0; j < hexagonMatchfield_gameGrid[i].size(); j++)
                hexagonMatchfield_gameGrid[i][j]->setState(INACTIVE);
        }

        //Angeklicktes auf AKTIVE setzten
        SelectionCache->setState(ACTIVE);
    }
    else if(SelectionCache->getState() == ACTIVE)
        SelectionCache->setState(INACTIVE);

    //if(SelectionCache->unit_stationed == NULL) hier spaeter einfuegen
    ptr_gameGameWid->setInfoScene(SelectionCache->getPtr_hexMfieldDisplay());
}
