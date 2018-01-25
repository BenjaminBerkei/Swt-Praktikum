/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 *
 * Author: Lucas
 * Version: 0.4
 * Datum 14.01.2018
 * Kommentare: ProcessSelection bearbeitet, Dijkstra gefixed, reset funktion geändert, Player cameFrom und current_cost eingefügt,
 *              ChangePhase & Move Button Implementiert, Hilfsfunktionen  eingefügt
 * */
#include "game.h"
#include <typeinfo>
using namespace std;

std::vector<QPoint> Game::vector_evenNeighbors = {QPoint(1,0),QPoint(1,-1),QPoint(0,-1),QPoint(-1,-1),QPoint(-1,0),QPoint(0,1)};
std::vector<QPoint> Game::vector_oddNeighbors = {QPoint(1,1),QPoint(1,0),QPoint(0,-1),QPoint(-1,0),QPoint(-1,1),QPoint(0,1)};


Game::Game(Options *init_options, GameWidget *ptr_gameWid) :
    selectionCache(nullptr), gameOptions(init_options), ptr_gameGameWid(ptr_gameWid),
    ptr_playerOne(new Player("Eins", 1)), ptr_playerTwo(new Player("Zwei", 2)),
    ptr_playerActive(ptr_playerOne), MenueView(false)
{
/*Starten eines Spiels mit den Optionen definiert in init_Options*/

    ptr_roundCurrent = new Round(gameOptions->getInt_roundLimit());

    if(loadMapForNewGame(gameOptions->getStr_map()))
    {
        qDebug() << "Map konnte geladen werden";
    }
    else
    {
        createRandomMap();
    }

    ptr_gameGameWid->gameWidCreateMatchfield(hexagonMatchfield_gameGrid);
    countUnits();
    setFogOfWar();

    //Buttons Einfuegen
    createButtons();

    ptr_gameGameWid->setPlayerLabel(ptr_playerActive->getPlayerName());
    ptr_gameGameWid->setPhaseLabel("Move");
    ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
}

Game::Game(QString filepath, GameWidget *gameWidegt)
    : selectionCache(nullptr), ptr_gameGameWid(gameWidegt)
{
    readSaveGame(filepath);

    ptr_gameGameWid->gameWidCreateMatchfield(hexagonMatchfield_gameGrid);
    countUnits();
    setFogOfWar();

    //Buttons Einfuegen
    createButtons();

    ptr_gameGameWid->setPlayerLabel(ptr_playerActive->getPlayerName());
    if(ptr_roundCurrent->getCurrentPhase() == MOVE)
    {
        ptr_gameGameWid->setPhaseLabel("Move");
    }
    else
    {
        ptr_gameGameWid->setPhaseLabel("Action");
    }
    ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
}

Game::~Game()
{
    resetHexMatchfield();
    for(auto &it : hexagonMatchfield_gameGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
    }

    for(auto &it : unit_UnitGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
    }

    for(auto &it : button_menueBar)
    {
        delete it;
    }
    delete ptr_playerOne;
    delete ptr_playerTwo;
}

void Game::loadGame(QString )
{
    qDebug() << "Load Game";
}

void Game::saveGame()
{
    qDebug() << "SaveGame";
    QString qstring_pathToSaveFile = QFileDialog::getSaveFileName(ptr_gameGameWid, tr("Save File"), "", tr("Data Text (*.txt);;All Files (*)"));

    if(qstring_pathToSaveFile.isEmpty())
    {
        qDebug() << "File Name Empty";
        return;
    }

    QFile file_saveFile(qstring_pathToSaveFile);

    if(!file_saveFile.open(QIODevice::WriteOnly))
    {
        qDebug() << " Could not open the file for writing";
        return;
    }

    QTextStream out(&file_saveFile);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    serialize(out);
}

void Game::endGame()
{
    emit gameOver();

    ptr_gameGameWid->resetGameWidget();
}

void Game::processSelection(HexagonMatchfield *selection)
{
    /*
     * Verarbeitet die Eingabe des Nutzers.
     * Zustad von Selection:
     *      INACTIVE: Der SelectionCache wird auf selection gesetzt. Zudem werden die Scenes in gameWidget entsprechend angepasst.
     *                  Der TargetCache wird zurückgesetzt und der state von selection wir auf ACTIVE gesetzt
     *      ACTIVE: Das Spielfeld wird zurückgesetzt und der SelectionCache auf nullptr
     *      TARGET: Wenn Round MOVE zurückliefert wird der Weg vom SelectionCache zur selection angezeigt
     *              Wenn Round ACTION zurückliefert wird die action Funktion der der ausgewählten Einheit ausgeführt
     *      PATH: Die ausgewählte Einheit wird auf die selection verlegt
     * */

    if(selection == nullptr)
    {
        qDebug() << "Fehler: selection ist ein Nullptr! In processSelection(HexagonMatchfield*)";
    }

    switch(selection->getState())
    {
    case INACTIVE:
        resetHexMatchfield();
        selectionCache = selection;
        ptr_gameGameWid->setInfoScene(selectionCache->getPtr_hexMfieldDisplay());
        if(selectionCache->getUnit_stationed() != nullptr && selectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
        {
            selectionCache->getUnit_stationed()->resetBuildUnloadParameter();
            ptr_gameGameWid->setOptScene(selectionCache->getUnit_stationed()->getVector_unitStorage());
        }
        //Angeklicktes auf AKTIVE setzten
        selectionCache->setState(ACTIVE);
        break;

    case ACTIVE:
        resetHexMatchfield();

        /*Wenn vorher eine auswahl da war, welche ein transporter oder factory war, müssen die zurückgesetzt werden*/
        if(selectionCache != nullptr && selectionCache->getUnit_stationed() != nullptr)
        {
            selectionCache->getUnit_stationed()->resetBuildUnloadParameter();
        }
        break;

    case TARGET:
        if(ptr_roundCurrent->getCurrentPhase() == MOVE)     //Move Phase
        {
            for(auto &it : targetCache)        //Ziele auf zustand TARGET zurücksetzen
            {
                it->setState(TARGET);
            }
            showPath(selection);            //Weg von Ziel zu auswahl anzeigen

        }else if(ptr_roundCurrent->getCurrentPhase() == ACTION )    //Action Phase
        {
            if(selectionCache->getUnit_stationed()->action(selection))  //Wenn die Action geglückt ist
            {
                /*Prüfen ob eine neue Einheit auf dem Grid ist*/
                if(selection->getUnit_stationed() != nullptr
                        && unit_UnitGrid[selection->getQpoint_gridPosition().x()][selection->getQpoint_gridPosition().y()] == nullptr)
                {
                    unit_UnitGrid[selection->getQpoint_gridPosition().x()][selection->getQpoint_gridPosition().y()] = selection->getUnit_stationed(); // in das Grid einfügen
                    selection->getUnit_stationed()->setPos(selection->pos());   //Position in der Scene setzen
                    ptr_gameGameWid->getGameWidGameScene()->addItem(selection->getUnit_stationed());    //in die Scene einfügen
                }
                ptr_gameGameWid->setOptScene(selectionCache->getUnit_stationed()->getVector_unitStorage());

                ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());    //Label updaten
                ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());

                setFogOfWar();
            }
            resetTargetCache();
        }
        break;
    case PATH :
        moveUnitTo(selection);

        /*Neuen Selection Cache nach Bewegung*/
        selectionCache = selection;
        selectionCache->setState(ACTIVE);

        /*Darstellungen setzen*/
        ptr_gameGameWid->setInfoScene(selectionCache->getPtr_hexMfieldDisplay());
        ptr_gameGameWid->setOptScene(selectionCache->getUnit_stationed()->getVector_unitStorage());

        resetTargetCache();
        setFogOfWar();
        break;
    }
    checkUnitGrid();
    countUnits();
    ptr_gameGameWid->updateInfoOptScenes();
    ptr_gameGameWid->updateMatchfieldScene();
    checkWinCondition();
}

void Game::Dijkstra()
{
    /*
     * Berechnung aller kürzesten Wege vom SelectionCache aus innerhalb der Reichweite
     * Setzt den TargetChache mit den berechneten Zielen und setzt deren state auf TARGET
     * */
    HexagonMatchfield* target = selectionCache;

    std::priority_queue<std::pair<HexagonMatchfield*, int>, std::vector<std::pair<HexagonMatchfield*, int>>, Compare> frontier;

    frontier.push(std::pair<HexagonMatchfield*, int>(target, 0));
    came_from[target] = target;
    current_cost[target] = 0;

    /*Solange es Elemente gibt, die in der Range liegen*/
    while(!frontier.empty())
    {
        /*Erstes Element aus der Schlange entfernen*/
        HexagonMatchfield* current = frontier.top().first;
        frontier.pop();

        /*Durchlaufen der Nachbarn des Elements*/
        vector<QPoint> neighbours;
        if(current->getQpoint_gridPosition().x() & 1)
        {
            neighbours = vector_oddNeighbors;
        }else{
            neighbours = vector_evenNeighbors;
        }

        for(auto &it : neighbours)
        {
            int x = current->getQpoint_gridPosition().x() + it.x();
            int y = current->getQpoint_gridPosition().y() + it.y();

            /*Prüfen ob Nachbarn auf Spielfeld liegen*/
            if(x >= 0 && x < ptr_gameGameWid->getSizeX() && y >= 0 && y < ptr_gameGameWid->getSizeY()
                    && hexagonMatchfield_gameGrid[x][y]->getState() != ACTIVE)
            {
                /*Speichern des zu betrachtenden Nachbarn*/
                HexagonMatchfield* neighbour = hexagonMatchfield_gameGrid[x][y];

                /*Berechnen der neuen Kosten, bestehend aus den Kosten um auf das Aktuelle Feld zu kommen + die Kosten um zum  Nachbarn zu kommen*/
                if(target->getUnit_stationed()->moveTo(neighbour) != -1)
                {

                        /*Wenn dieser noch nicht betrachtet wurde, kosten absurd hochlegen, damit diese auf jeden fall gesetzt werden*/
                        if(current_cost.find(neighbour) == current_cost.end())
                            current_cost[neighbour] = 999;

                        int new_cost = current_cost[current] + target->getUnit_stationed()->moveTo(neighbour);

                        /*Wenn diese Kosten geringer als die Reichweite der Einheit und besser als die bisherigen Kosten sind, dann..*/
                        if(new_cost <= target->getUnit_stationed()->getUnitCurrentMoveRange() && new_cost < current_cost[neighbour])
                        {
                            current_cost[neighbour] = new_cost; //Kosten aktualisieren
                            came_from[neighbour] = current;     //Vorgänger auf das Aktuelle Feld setzem
                            frontier.push(std::pair<HexagonMatchfield*, int> (neighbour, current_cost[neighbour])); //Den Nachbarn der Queue hinzufügen

                            targetCache.push_back(neighbour);   //und in den Target Cache Stecken
                            neighbour->setState(TARGET);
                        }

                }
            }
        }
    }
}

bool Game::loadMapForNewGame(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File nicht gefunden";
        return false;
    }

    QTextStream in(&file);
    QString typeHex;
    QString unitType;
    QString unitPath;
    int int_playerID;
    int int_isUnitSet;
    int boltanium;
    int dimX, dimY;

    in >> dimX;
    in >> dimY;
    ptr_gameGameWid->setSizeX(dimX);
    ptr_gameGameWid->setSizeY(dimY);

    //Hexagone einlesen
    for(int i = 0; i < dimX; i++)
    {
        std::vector<HexagonMatchfield*> vecHexagon;
        std::vector<Unit*> vecUnit;
        for(int j = 0; j < dimY; j++)
        {
            in >> typeHex;
            in >> boltanium;
            in >> int_isUnitSet;
            qDebug() << "Eingelesen: " << "\n\t" << typeHex << "\n\t" << boltanium << "\n\t" << int_isUnitSet;
            if(int_isUnitSet != 0)
            {
                in >> int_playerID;
                in >> unitType;
                in >> unitPath;
                qDebug() << "Player einlesen: " << "\n\t" << int_playerID;
                qDebug() << "Unit Einlesen:" << "\n\t" << unitType << "\n\t" << unitPath;
                Player* ptr_playerTemp = nullptr;
                if(int_playerID == 1)
                {
                    ptr_playerTemp = ptr_playerOne;
                }
                else
                {
                    ptr_playerTemp = ptr_playerTwo;
                }

                if(unitType == "FACTORYUNIT")
                {
                   vecUnit.push_back(new FactoryUnit(unitPath, true, ptr_playerTemp));
                }
                else if( unitType == "HEADQUATERUNIT")
                {
                    vecUnit.push_back(new HeadquaterUnit(unitPath,ptr_playerTemp));
                }
                else if(unitType == "AIRUNIT")
                {
                    vecUnit.push_back(new AirUnit(unitPath, ptr_playerTemp));
                }
                //Hier spaeter noch weiter ausbauen (andere Unittypen hinzufuegen)
                else
                {
                    vecUnit.push_back(nullptr);
                }
            }else{
                vecUnit.push_back(nullptr);
            }
            vecHexagon.push_back(new HexagonMatchfield(QPoint(i,j), typeHex, vecUnit[j]));
            vecHexagon[j]->setBoltaniumCurrent(boltanium);

            connect(vecHexagon[j],SIGNAL(SIGNAL_clicked(HexagonMatchfield*)),this,SLOT(processSelection(HexagonMatchfield*)));
            connect(vecHexagon[j],SIGNAL(SIGNAL_centerThis(HexagonMatchfield*)), ptr_gameGameWid, SLOT(SLOT_gameWidCenterHex(HexagonMatchfield*)));
        }
        unit_UnitGrid.push_back(vecUnit);
        hexagonMatchfield_gameGrid.push_back(vecHexagon);
    }

    return true;
}

bool Game::loadMapFromSaveGame(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File nicht gefunden";
        return false;
    }

    QTextStream in(&file);
    QString tmp;
    QString typeHex;
    int dimX, dimY;

    in >> dimX;
    in >> dimY;
    ptr_gameGameWid->setSizeX(dimX);
    ptr_gameGameWid->setSizeY(dimY);

    //Leere den Vektor falls er etwas enthaelt
    if(hexagonMatchfield_gameGrid.size() != 0)
    {
        for(auto &it : hexagonMatchfield_gameGrid)
        {
            for(auto &ut : it)
            {
                delete ut;
            }
            it.clear();
        }
        hexagonMatchfield_gameGrid.clear();
    }

    //Hexagone einlesen
    for(int i = 0; i < dimX; i++)
    {
        std::vector<HexagonMatchfield*> vecHexagon;
        for(int j = 0; j < dimY; j++)
        {
            in >> typeHex;
            vecHexagon.push_back(new HexagonMatchfield(QPoint(i,j), typeHex, nullptr));
            connect(vecHexagon[j],SIGNAL(SIGNAL_clicked(HexagonMatchfield*)),this,SLOT(processSelection(HexagonMatchfield*)));
            connect(vecHexagon[j],SIGNAL(SIGNAL_centerThis(HexagonMatchfield*)), ptr_gameGameWid, SLOT(SLOT_gameWidCenterHex(HexagonMatchfield*)));
            tmp = in.readLine();
        }
        hexagonMatchfield_gameGrid.push_back(vecHexagon);
    }


    //UnitGrid mit Nullptr initialisieren
    for(int i = 0; i < dimX; i++)
    {
        std::vector<Unit*> vecUnit;
        for(int j = 0; j < dimY; j++)
        {
            vecUnit.push_back(nullptr);
        }
        unit_UnitGrid.push_back(vecUnit);
    }
    return true;
}

/*Move Button ausgewählt*/
void Game::buttonPressedMove()
{
    /*
     * Wenn der SLOT ausgelöst wird, wir
     * */
    if(ptr_roundCurrent->getCurrentPhase() == MOVE)     //Phase prüfen
    {
        /*Wenn ein Feld ausgewählt wurde auf dem eine Einheit steht, welche dem aktiven Spieler gehört*/
        if(selectionCache != nullptr && selectionCache->getUnit_stationed() != nullptr
                && selectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
        {
            Dijkstra();     //Berechnen aller möglichen Ziele
        }
    }
}

void Game::buttonPressedAction()
{
    if(ptr_roundCurrent->getCurrentPhase() == ACTION )
    {
        if(selectionCache != nullptr && selectionCache->getUnit_stationed() != nullptr
                && selectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive
                && selectionCache->getUnit_stationed()->getUnitUsed() == false)
        {
            calculateTargets(selectionCache, selectionCache->getUnit_stationed()->getActionRange());
        }
    }
}

void Game::buttonPressedMap()
{
        ptr_gameGameWid->setEnableButtonScene(false);
        ptr_gameGameWid->gameWidCreateMap(hexagonMatchfield_gameGrid);
        ptr_gameGameWid->getGameWidGameView()->setScene(ptr_gameGameWid->getGameWidMapScene());   
}

void Game::buttonPressedMenue()
{
    if(MenueView){
        ptr_gameGameWid->getGameWidGameView()->setScene(ptr_gameGameWid->getGameWidGameScene());
        ptr_gameGameWid->setEnableButtonScene(true);
        MenueView = false;
    }else{
        ptr_gameGameWid->getGameWidGameView()->setScene(ptr_gameGameWid->getGameWidMenueScene());
        ptr_gameGameWid->setEnableButtonScene(false);
        button_menueBar[4]->setEnabled(true);
        MenueView = true;
    }
}

void Game::buttonPressedChangePhase()
{
    ptr_roundCurrent->changePhase();

    if(ptr_roundCurrent->getCurrentPhase() == MOVE)
    {
        ptr_playerActive = ptr_playerActive == ptr_playerOne ? ptr_playerTwo : ptr_playerOne;
        resetHexMatchfield();
        setFogOfWar();        
    }
    SLOT_checkStateOfButtons();
    resetTargetCache();

    ptr_gameGameWid->setPlayerLabel(ptr_playerActive->getPlayerName());
    ptr_gameGameWid->setPhaseLabel(ptr_roundCurrent->getCurrentPhase() == MOVE ? "Move" : "Action");
    ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
    if(selectionCache != nullptr && selectionCache->getUnit_stationed() != nullptr)
    {
        selectionCache->getUnit_stationed()->resetBuildUnloadParameter();
    }
    resetUnits();
    ptr_gameGameWid->repaintGameView();
    ptr_gameGameWid->getGameWidButtonScene()->update();
}

void Game::SLOT_MenueButtonSelected(int menue)
{
    switch(menue)
    {
    case 0 : saveGame(); return;
    case 1 : loadGame(""); return;
    case 2 : endGame(); return;
    case 3 :
        ptr_gameGameWid->getGameWidGameView()->setScene(ptr_gameGameWid->getGameWidGameScene());
        ptr_gameGameWid->setEnableButtonScene(true);
        return;
    }

}

void Game::SLOT_checkStateOfButtons()
{
    if(ptr_roundCurrent->getCurrentPhase() == MOVE)
    {
        button_menueBar[0]->setEnabled(true); // Setze das der Movebutton nicht "geschwaertzt" werden soll
        button_menueBar[1]->setEnabled(false);// Setze das der Actionbutton "geschwaertzt" werden soll
    }
    else
    {
        button_menueBar[0]->setEnabled(false); // Setze das der Movebutton "geschwaertzt" werden soll
        button_menueBar[1]->setEnabled(true); // Setze das der Actionbutton nicht "geschwaertzt" werden soll
    }
}

/*HilfsFunktionen Start#######################################################################*/
void Game::resetHexMatchfield()
{
    /*Zurücksetzen der Auswahl*/
    if(selectionCache != nullptr)
    {
        selectionCache->setState(INACTIVE);
        selectionCache = nullptr;
    }
    resetTargetCache();
    ptr_gameGameWid->clearInfoScene();
    ptr_gameGameWid->clearOptionsScene();
}

void Game::resetTargetCache()
{
    for(auto &it : targetCache)
    {
        it->setState(INACTIVE);
    }
    targetCache.clear();
    came_from.clear();
    current_cost.clear();
}
void Game::moveUnitTo(HexagonMatchfield * target)
{
    Unit* unitToMove = selectionCache->getUnit_stationed();
    unitToMove->setUnitCurrentMoveRange(unitToMove->getUnitCurrentMoveRange() - current_cost[target]);

    if(target->getUnit_stationed() != nullptr &&
            (target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
            || target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
            || target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER"))
    {
        target->getUnit_stationed()->addUnitToStorage(unitToMove); // Einheit in den Vektor der Transportereinheit verlegt
        ptr_gameGameWid->getGameWidGameScene()->removeItem(unitToMove); // Einheit aus der Scene gelöscht
    }
    else
    {
        target->setUnit_stationed(unitToMove);      //Einheit verlegen auf das Ziel
        unit_UnitGrid[target->getQpoint_gridPosition().x()][target->getQpoint_gridPosition().y()] = unitToMove; //Einheit im Grid verlegt

        /*Animation*/
        vector<QPointF> path;
        for(auto& iterator = target; iterator != selectionCache; iterator = came_from[iterator])
        {
            path.push_back(iterator->pos());
        }
        ptr_gameGameWid->animateUnit(unitToMove, path);
    }
    unit_UnitGrid[selectionCache->getQpoint_gridPosition().x()][selectionCache->getQpoint_gridPosition().y()] = nullptr; //Einheit aus dem UnitGrid löschen
    selectionCache->setUnit_stationed(nullptr);     //Einheit vom alten feld entfernen
    selectionCache->setState(INACTIVE);     //Auswahl auf inactiv setzen
    selectionCache = nullptr;
}
void Game::showNeighbors(HexagonMatchfield * center)
{
    if(center->getQpoint_gridPosition().x() & 1)
    {
        for(auto &it: vector_oddNeighbors)
        {
            int x = center->getQpoint_gridPosition().x() + it.x();
            int y = center->getQpoint_gridPosition().y() + it.y();
            if(x >= 0 && x < ptr_gameGameWid->getSizeX() && y >= 0 && ptr_gameGameWid->getSizeY())
            {
                hexagonMatchfield_gameGrid[x][y]->setState(TARGET);
                targetCache.push_back(hexagonMatchfield_gameGrid[x][y]);
            }
        }
    }else{
        for(auto &it: vector_evenNeighbors)
        {
            int x = center->getQpoint_gridPosition().x() + it.x();
            int y = center->getQpoint_gridPosition().y() + it.y();
            {
                hexagonMatchfield_gameGrid[x][y]->setState(TARGET);
                targetCache.push_back(hexagonMatchfield_gameGrid[x][y]);
            }
        }
    }
}

void Game::calculateTargets(HexagonMatchfield * center, int range)
{
    std::queue<HexagonMatchfield*> frontier;
    frontier.push(center);

    while(!frontier.empty())    //Solange zulässige Ziele gefunden werdenn
    {
        HexagonMatchfield* current = frontier.front();
        frontier.pop();

        /*Durchlaufen der Nachbarn des Elements*/
        vector<QPoint> neighbours;
        if(current->getQpoint_gridPosition().x() & 1)
        {
            neighbours = vector_oddNeighbors;
        }else{
            neighbours = vector_evenNeighbors;
        }

        for(auto &it : neighbours)    //Durchlaufen der Nachbarn
        {
            int x = current->getQpoint_gridPosition().x() + it.x();    //Koordinaten des neuen Ziels
            int y = current->getQpoint_gridPosition().y() + it.y();

            if(x >= 0 && x < ptr_gameGameWid->getSizeX() && y >= 0 && y < ptr_gameGameWid->getSizeY()         //Wenn das ziel auf dem Spielfeld liegt
                    && hexagonMatchfield_gameGrid[x][y]->getState() != TARGET && hexagonMatchfield_gameGrid[x][y]->getState() != ACTIVE)  //Wenn das Ziel nicht bereits als TARGET markiert wurde
            {
                HexagonMatchfield* neighbour = hexagonMatchfield_gameGrid[x][y];         //Zwischenspeichern für lesbarkeite
                if(offset_distance(center->getQpoint_gridPosition(), neighbour->getQpoint_gridPosition()) <= range)          //Wenn das ziel in der Reichweite der Einheite liegt
                {
                    neighbour->setState(TARGET);
                    targetCache.push_back(neighbour);
                    frontier.push(neighbour);
                }
            }
        }
    }
}

void Game::setFogOfWar()
{
    for(auto &iterator : hexagonMatchfield_gameGrid)
    {
        for(auto &hex : iterator)
        {
            hex->setHexFogOfWar(true);
        }
    }
    for(auto &iterator : hexagonMatchfield_gameGrid)
    {
        for(auto &hex : iterator)
        {
            if(hex->getUnit_stationed() != nullptr && hex->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
            {
                calculateTargets(hex, hex->getUnit_stationed()->getUnitView());
                for(auto &it : targetCache)
                {
                    it->setHexFogOfWar(false);
                }
                hex->setHexFogOfWar(false);
                resetTargetCache();
            }
        }
    }
    ptr_gameGameWid->repaintGameView();
}

void Game::showPath(HexagonMatchfield* target)
{
    for(auto &it = target; it != selectionCache; it = came_from[it])
    {
        it->setState(PATH);
    }
}

void Game::checkUnitGrid()
{
    for(int x = 0; x < ptr_gameGameWid->getSizeX(); x++)
    {
        for(int y = 0; y < ptr_gameGameWid->getSizeY(); y++)
        {
            if(unit_UnitGrid[x][y] != nullptr && unit_UnitGrid[x][y]->checkUnitDestroyed())
            {
                hexagonMatchfield_gameGrid[x][y]->setUnit_stationed(nullptr);
                delete unit_UnitGrid[x][y];
                unit_UnitGrid[x][y] = nullptr;
            }
        }
    }
    ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
}

void Game::checkWinCondition()
{   //Prüfen ob ein Spieler verloren hat, also keine Einheiten oder kein HQ mehr hat
    if(ptr_playerOne->getPlayerUnitNumber() == 0 || ptr_playerOne->getHQDestroyed())
    {
        qDebug() << "Spieler Eins Verloren";
        endGame();
    }else if(ptr_playerTwo->getPlayerUnitNumber() == 0 || ptr_playerTwo->getHQDestroyed())
    {
        qDebug() << "Spieler Zwei Verloren";
        endGame();
    }
}

void Game::resetUnits()
{
    for(auto &iteratorX : unit_UnitGrid)    //Durchlaufen des Grids
    {
        for(auto &unit : iteratorX)
        {
            if(unit != nullptr)
            {
                unit->resetMovementRange();     //Untis Move range zurücksetzen
                unit->resetUnitUsed();
            }
        }
    }
}

void Game::countUnits()
{
    ptr_playerOne->setPlayerUnitNumber(0);
    ptr_playerTwo->setPlayerUnitNumber(0);

    for(auto &iterator : unit_UnitGrid)
    {
        for(auto &unit : iterator)
        {
            if(unit != nullptr && unit->getUnitPlayer() != nullptr)
            {
                unit->getUnitPlayer()->increaseUnitNumber();

                if(unit->getUnitType() == "TRANSPORTERAIR" || unit->getUnitType() == "TRANSPORTERGROUND"
                        || unit->getUnitType() == "TRANSPORTERWATER")
                {
                    for(auto &iteratorUnitStorage : unit->getVector_unitStorage())
                    {
                        iteratorUnitStorage->getUnitPlayer()->increaseUnitNumber();
                    }
                }
            }
        }
    }
}
/*Für Referenzen betrachte https://www.redblobgames.com/grids/hexagons/#distances , Kapitel: Distance*/
QVector3D Game::oddqToCube(QPoint oddqCoord)
{
    int x = oddqCoord.x();
    int z = oddqCoord.y() - (oddqCoord.x() - ((int)oddqCoord.x() & 1)) / 2;
    int y = (-1) * x - z;
    return QVector3D(x,y,z);
}

QPoint Game::cubeToOddq(QVector3D cubeCoord)
{
    int x = cubeCoord.x();
    int y = cubeCoord.z() + (cubeCoord.x() - ((int)cubeCoord.x() & 1)) / 2;
    return QPoint(x,y);
}

int Game::cube_distance(QVector3D a, QVector3D b)
{
    return (abs(a.x() - b.x()) + abs(a.y() - b.y()) + abs(a.z() - b.z())) / 2;
}

void Game::readSaveGame(QString filepath)
{
    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File nicht gefunden";
        return;
    }

    QTextStream in(&file);
    QString tmp;
    QString Version;
    in >> tmp;
    in >> tmp;
    in >> tmp;
    in >> Version;

    //Ueberpruefe Version
    if(Version != "V2.7")
    {
        qDebug() << "Falsche Version. Eingelesene Version: " << Version;
        return;
    }

    tmp = in.readLine();

    //Ueberpruefe Format
    QString textType;
    textType = in.readLine();

    if(textType != "Save Game")
    {
        qDebug() << "Falsches Format. Eingelesen: " << textType;
        return;
    }

    gameOptions = Options::unserialize(in);

    if( gameOptions->getBool_ki() == true)
    {
        ptr_playerOne = Player::unserialize(in);
        //später
    }
    else
    {
        ptr_playerOne = Player::unserialize(in);
        ptr_playerTwo = Player::unserialize(in);
    }

    int playerActive;
    in >> playerActive;

    if(playerActive == 1)
    {
        ptr_playerActive = ptr_playerOne;
    }
    else
    {
        ptr_playerActive = ptr_playerTwo;
    }

    ptr_roundCurrent = Round::unserialize(in);
    loadMapFromSaveGame(gameOptions->getStr_map());

    int posX, posY, boltanium, unitStationed, unitPlayer, unitHP, unitMoveRange, unitUsed, unitLevel;
    QString unitType, unitPath;

    in >> tmp;
    while(tmp != "")
    {
       posX = tmp.toInt();
       in >> posY;
       in >> boltanium;
       in >> unitStationed;

       hexagonMatchfield_gameGrid[posX][posY]->setBoltaniumCurrent(boltanium);

       if(unitStationed == 1)
       {
           in >> unitType;
           in >> unitPath;
           in >> unitPlayer;
           in >> unitHP;
           in >> unitUsed;
           qDebug() << "Eingelesene Einheit: " << "\n\t" << unitType << "\n\t" << unitPath
                    << "\n\t" << unitPlayer << "\n\t" << unitHP;
           Player* ptr_playerTemp = nullptr;

           if(unitPlayer == 1)
           {
               ptr_playerTemp = ptr_playerOne;
           }else{
               ptr_playerTemp = ptr_playerTwo;
           }

           if(unitType == "FACTORYUNIT")
           {
               unit_UnitGrid[posX][posY] = new FactoryUnit(unitPath, true, ptr_playerTemp);
               hexagonMatchfield_gameGrid[posX][posY]->setUnit_stationed(unit_UnitGrid[posX][posY]);
               unit_UnitGrid[posX][posY]->setUnitCurrentHP(unitHP);
               unit_UnitGrid[posX][posY]->setUnitUsed((bool)unitUsed);
           }
           else if( unitType == "HEADQUATERUNIT")
           {
               unit_UnitGrid[posX][posY] = new HeadquaterUnit(unitPath,ptr_playerTemp);
               hexagonMatchfield_gameGrid[posX][posY]->setUnit_stationed(unit_UnitGrid[posX][posY]);
               unit_UnitGrid[posX][posY]->setUnitCurrentHP(unitHP);
               unit_UnitGrid[posX][posY]->setUnitUsed((bool)unitUsed);
           }
           else if(unitType == "AIRUNIT")
           {
               unit_UnitGrid[posX][posY] = new AirUnit(unitPath, ptr_playerTemp);
               hexagonMatchfield_gameGrid[posX][posY]->setUnit_stationed(unit_UnitGrid[posX][posY]);

               in >> unitMoveRange;
               in >> unitLevel;
               qDebug() << "\t" << unit_UnitGrid[posX][posY]->getUnitMoveRange() << "\n\t" << unitLevel;

               unit_UnitGrid[posX][posY]->setUnitCurrentHP(unitHP);
               unit_UnitGrid[posX][posY]->setUnitUsed((bool)unitUsed);
               unit_UnitGrid[posX][posY]->setUnitCurrentMoveRange(unitMoveRange);

               //unit_UnitGrid[posX][posY]->setUnitLevel(unitLevel);
           }
           //Hier spaeter noch weiter ausbauen (andere Unittypen hinzufuegen)
           else
           {
               unit_UnitGrid[posX][posY] = nullptr;
           }
       }
       in >> tmp;
    }

}

void Game::createRandomMap()
{
    //Größe
    int sizeX = ptr_gameGameWid->getSizeX();
    int sizeY = ptr_gameGameWid->getSizeY();

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
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "waterDeep", 0));
            else if( i == 1 || i == sizeX - 2 || j == 1 || j == sizeY - 2 )
                vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "waterSeashore", 0));
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
                        vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "mountainTop", 0));
                    else
                        vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "grassland", 0));
                else
                    vectorHex.push_back(new HexagonMatchfield(QPoint(i,j), "forrest", 0));
            }
            int randBoltanium = qrand() % 100;
            if(randBoltanium < 20)
            {
                int randBoltaniumAmount = (qrand() % 200) + 50;
                vectorHex[j]->setBoltaniumCurrent(randBoltaniumAmount);
            }
            connect(vectorHex[j],SIGNAL(SIGNAL_clicked(HexagonMatchfield*)),this,SLOT(processSelection(HexagonMatchfield*)));
            connect(vectorHex[j],SIGNAL(SIGNAL_centerThis(HexagonMatchfield*)), ptr_gameGameWid, SLOT(SLOT_gameWidCenterHex(HexagonMatchfield*)));
        }
        hexagonMatchfield_gameGrid.push_back(vectorHex);
    }

    qDebug() << "Bemerkung: Zufallsfeld erstellt (in Klasse Game). Nur für Testzwecke.";

    //Einheiten belegen

    int anzHQ = 0;

    for(int i = 0; i < sizeX; i++)
    {
        std::vector<Unit*> vectorUnit;
        for(int j = 0; j < sizeY; j++)
        {
                int randomInt = qrand() % 100;
                if(randomInt < 5)
                {
                    Unit* randomUnit = nullptr;
                    QString hexType = hexagonMatchfield_gameGrid[i][j]->getHexMatchfieldType();
                    Player* randPlayer = (qrand() % 2) == 0 ? ptr_playerOne : ptr_playerTwo;

                    if(hexType != "waterDeep" && hexType != "waterSeashore")
                    {
                        int randomUnitType = qrand() % 9;

                        switch(randomUnitType)
                        {
                        case 0 : randomUnit = new AirUnit(":/dynamic/dynamicUnit/derbolten.txt", randPlayer); break;
                        case 1 : randomUnit = new TransporterGroundUnit(":/dynamic/dynamicUnit/kevarn.txt", randPlayer); break;
                        case 2 : randomUnit = new LightUnit(":/dynamic/dynamicUnit/ben.txt", randPlayer); break;
                        case 3 : randomUnit = new MediumUnit(":/dynamic/dynamicUnit/lucas.txt", randPlayer); break;
                        case 4 : randomUnit = new HeavyUnit(":/dynamic/dynamicUnit/mannuel.txt", randPlayer); break;
                        case 5 : randomUnit = new DepotUnit(":/static/staticUnit/depot.txt", randPlayer); break;
                        case 6 : randomUnit = new FactoryUnit(":/static/staticUnit/factory.txt", true, randPlayer); break;
                        case 7 :
                            if(anzHQ < 2)
                            {
                                randomUnit = new HeadquaterUnit(":/static/staticUnit/headquater.txt", anzHQ == 0 ? ptr_playerOne : ptr_playerTwo);
                                anzHQ++;
                            }
                            break;
                        case 8 : randomUnit = new BuildLightUnit(":/dynamic/dynamicUnit/scpmerlin", true, randPlayer); break;
                        }
                    }else{
                        randomUnit = new WaterUnit(":/dynamic/dynamicUnit/msmiguel.txt", randPlayer);
                    }

                    vectorUnit.push_back(randomUnit);
                    hexagonMatchfield_gameGrid[i][j]->setUnit_stationed(vectorUnit[j]);

                }else{
                    vectorUnit.push_back(nullptr);
                }
        }
        unit_UnitGrid.push_back(vectorUnit);
    }
}

void Game::createButtons()
{
    ButtonMove* movebutton = new ButtonMove(64,64);
    ButtonAction* actionbutton = new ButtonAction(64,64);
    ButtonChangePhase* changephasebutton = new ButtonChangePhase(64,64);
    ButtonMap* mapbutton = new ButtonMap(64,64);
    ButtonMenue* menuebutton = new ButtonMenue(64,64);

    button_menueBar.push_back(movebutton);
    button_menueBar.push_back(actionbutton);
    button_menueBar.push_back(changephasebutton);
    button_menueBar.push_back(mapbutton);
    button_menueBar.push_back(menuebutton);
    connect(movebutton,SIGNAL(clicked()),this,SLOT(buttonPressedMove()));
    connect(actionbutton,SIGNAL(clicked()),this,SLOT(buttonPressedAction()));
    connect(changephasebutton,SIGNAL(clicked()),this,SLOT(buttonPressedChangePhase()));
    connect(mapbutton, SIGNAL(clicked()), this, SLOT(buttonPressedMap()));
    connect(menuebutton,SIGNAL(clicked()),this,SLOT(buttonPressedMenue()));

    connect(ptr_gameGameWid, SIGNAL(SIGNAL_MenueButtonPushed(int)), this, SLOT(SLOT_MenueButtonSelected(int)));
    connect(ptr_gameGameWid, SIGNAL(SIGNAL_changeStateOfButtons()), this, SLOT(SLOT_checkStateOfButtons()));
    SLOT_checkStateOfButtons();

    ptr_gameGameWid->gameWidCreateButtonBar(button_menueBar);
}

int Game::offset_distance(QPoint a, QPoint b)
{
    QVector3D ac = oddqToCube(a);
    QVector3D bc = oddqToCube(b);
    return cube_distance(ac, bc);
}

void Game::serialize(QTextStream &out)
{
    out << "Battle Isle Clone V2.7\nSave Game\n";
    gameOptions->serialize(out);
    ptr_playerOne->serialize(out);
    ptr_playerTwo->serialize(out);
    out << ptr_playerActive->getPlayerID() << "\n";
    ptr_roundCurrent->serialize(out);
    for(auto &iteratorX : hexagonMatchfield_gameGrid)
    {
        for(auto &hex : iteratorX)
        {
            hex->serialize(out);
        }
    }
}


/*HilfsFunktionen Ende#######################################################################*/

bool Compare::operator()(std::pair<HexagonMatchfield*, int> a, std::pair<HexagonMatchfield*, int> b)
{
    return a.second < b.second;
}
