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

/*Noch fertig schreiben*/
std::vector<QPoint> Game::vector_evenNeighbors = {QPoint(0,0)};
std::vector<QPoint> Game::vector_oddNeighbors = {QPoint(0,0)};


std::vector<Button *> Game::getButton_menueBar()
{
    return button_menueBar;
}

void Game::setButton_menueBar(const std::vector<Button *> &value)
{
    button_menueBar = value;
}

Game::Game(Options *init_options, GameWidget *ptr_gameWid) :
    SelectionCache(NULL),
    gameOptions(init_options),
    ptr_gameGameWid(ptr_gameWid)
{
    ptr_gameGameWid->setGameWidGame(this);

    // Erstelle eine Mapm
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

    //Buttons Einfuegen
    ButtonMove* movebutton = new ButtonMove(64,64);
    ButtonAction* actionbutton = new ButtonAction(64,64);
    ButtonChangePhase* changephasebutton = new ButtonChangePhase(64,64);
    ButtonMenue* menuebutton = new ButtonMenue(64,64);

    button_menueBar.push_back(movebutton);
    button_menueBar.push_back(actionbutton);
    button_menueBar.push_back(changephasebutton);
    button_menueBar.push_back(menuebutton);

    ptr_gameGameWid->gameWidcreateButtonBar();
}

vector<vector<HexagonMatchfield*> > Game::getVectorVectorHexagonMatchfield()
{
    return hexagonMatchfield_gameGrid;
}

void Game::processSelection(HexagonMatchfield *selection)
{
    switch(selection->getState())
    {
        case INACTIVE:
            resetStateHex();
            SelectionCache = selection;
            ptr_gameGameWid->setInfoScene(SelectionCache->getPtr_hexMfieldDisplay());

            //Angeklicktes auf AKTIVE setzten
            SelectionCache->setState(ACTIVE);
            break;

        case ACTIVE:
            resetStateHex();
            ptr_gameGameWid->clearScenes();
            break;

        case TARGET:
        /*
         Pseudocode:
            if(selectionCache.getStationedUnit != nullptr)
                if(move)
                {
                    moveUnitTo(target;)
                }
                if(action)
                {
                    selectionCache.getStationedUnt().action(target);
                }
                reset()
        */
            break;
    }


    //if(SelectionCache->unit_stationed == NULL) hier spaeter einfuegen
}

void Game::Dijkstra()
{

}

void Game::buttonPressedMove()
{
    Dijkstra();
}

void Game::buttonPressedAction()
{

}

void Game::buttonPressedMenue()
{

}

void Game::buttonPressedChangePhase()
{

}

void Game::resetStateHex()
{
    SelectionCache = nullptr;
    for(unsigned int i = 0; i < hexagonMatchfield_gameGrid.size(); i++)
    {
        for(unsigned int j = 0; j < hexagonMatchfield_gameGrid[i].size(); j++)
            hexagonMatchfield_gameGrid[i][j]->setState(INACTIVE);
    }
}
