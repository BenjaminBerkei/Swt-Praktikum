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
 * Kommentare: ProcessSelection bearbeitet, Dijkstra gefixed, reset funktion geändert, Player cameFrom und map_hexCurrentCost eingefügt,
 *              ChangePhase & Move Button Implementiert, Hilfsfunktionen  eingefügt
 *
 * Author: Miguel
 * Version: 0.5
 * Datum: 23.01.2018
 * Kommentar: getter und setter für targetCache, camefrom und costs. Dijkstra muss jetzt ein HexagonMatchfield* uebergeben bekommen
 * 		Grund für die Aenderung ist die KI.
 * */
#include "game.h"
#include <typeinfo>
using namespace std;

std::vector<QPoint> Game::vec_qpointEvenNeighbors = {QPoint(1,0),QPoint(1,-1),QPoint(0,-1),QPoint(-1,-1),QPoint(-1,0),QPoint(0,1)};
std::vector<QPoint> Game::vec_qpointOddNeighbors = {QPoint(1,1),QPoint(1,0),QPoint(0,-1),QPoint(-1,0),QPoint(-1,1),QPoint(0,1)};


Game::Game(Options *init_options, GameWidget *ptr_gameWid) :
    ptr_hexSelectionCache(nullptr), ptr_options(init_options), ptr_gameWidget(ptr_gameWid),
    ptr_playerOne(new Player("Eins", 1)), ptr_playerTwo(new Player("Zwei", 2)),
    ptr_playerActive(ptr_playerOne), bool_menueView(false)
{
/*Starten eines Spiels mit den Optionen definiert in init_Options*/

    ptr_roundCurrent = new Round(ptr_options->getInt_roundLimit());

    if(!loadMapForNewGame(ptr_options->getStr_map()))

    {
        createRandomMap();
    }

    ptr_gameWidget->gameWidCreateMatchfield(vec_hexGameGrid);
    countUnits();
    setFogOfWar();

    //Buttons Einfuegen
    createButtons();

    ptr_gameWidget->setPlayerLabel(ptr_playerActive->getPlayerName());
    ptr_gameWidget->setPhaseLabel("Move");
    ptr_gameWidget->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameWidget->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
}

Game::Game(QString filepath, GameWidget *gameWidegt)
    : ptr_hexSelectionCache(nullptr), ptr_gameWidget(gameWidegt)
{
    if(!readSaveGame(filepath))
    {
        createRandomMap();
    }

    ptr_gameWidget->gameWidCreateMatchfield(vec_hexGameGrid);
    countUnits();
    setFogOfWar();

    //Buttons Einfuegen
    createButtons();

    ptr_gameWidget->setPlayerLabel(ptr_playerActive->getPlayerName());
    if(ptr_roundCurrent->getCurrentPhase() == MOVE)
    {
        ptr_gameWidget->setPhaseLabel("Move");
    }
    else
    {
        ptr_gameWidget->setPhaseLabel("Action");
    }
    ptr_gameWidget->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameWidget->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
}

Game::~Game()
{
    qDebug() << "Destruktor Game";
    resetHexMatchfield();
    for(auto &it : vec_hexGameGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
    }
    qDebug() << "\t Hexagon Matchfield Grid gelöscht";
    for(auto &it : vec_unitGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
    }
    qDebug() << "\t Unit Grid gelöscht";
    for(auto &it : vec_buttonMenueBar)
    {
        delete it;
    }
    qDebug() << "\t Button Bar gelöscht";
    delete ptr_playerOne;
    delete ptr_playerTwo;
    qDebug() << "\t Player Gelöscht";
}

void Game::saveGame()
{
    if(ptr_options->getStr_map() != "Random")
    {
        qDebug() << "SaveGame";
        QString qstring_pathToSaveFile = QFileDialog::getSaveFileName(ptr_gameWidget, tr("Save File"), "", tr("Data Text (*.txt);;All Files (*)"));

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
    }else{
        qDebug() << "Random Spiele können nicht gespeichert werden";
    }
}

void Game::endGame()
{
    emit gameOver();

    ptr_gameWidget->resetGameWidget();
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
        ptr_hexSelectionCache = selection;
        ptr_gameWidget->setInfoScene(ptr_hexSelectionCache->getPtr_hexMfieldDisplay());
        if(ptr_hexSelectionCache->getUnit_stationed() != nullptr && ptr_hexSelectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
        {
            ptr_hexSelectionCache->getUnit_stationed()->resetBuildUnloadParameter();
            ptr_gameWidget->setOptScene(ptr_hexSelectionCache->getUnit_stationed()->getVector_unitStorage());
        }
        //Angeklicktes auf AKTIVE setzten
        ptr_hexSelectionCache->setState(ACTIVE);
        break;

    case ACTIVE:
        resetHexMatchfield();

        /*Wenn vorher eine auswahl da war, welche ein transporter oder factory war, müssen die zurückgesetzt werden*/
        if(ptr_hexSelectionCache != nullptr && ptr_hexSelectionCache->getUnit_stationed() != nullptr)
        {
            ptr_hexSelectionCache->getUnit_stationed()->resetBuildUnloadParameter();
        }
        break;

    case TARGET:
        if(ptr_roundCurrent->getCurrentPhase() == MOVE)     //Move Phase
        {
            for(auto &it : vec_hexTargetCache)        //Ziele auf zustand TARGET zurücksetzen
            {
                it->setState(TARGET);
            }
            showPath(selection);            //Weg von Ziel zu auswahl anzeigen

        }else if(ptr_roundCurrent->getCurrentPhase() == ACTION )    //Action Phase
        {
            if(ptr_hexSelectionCache->getUnit_stationed()->action(selection))  //Wenn die Action geglückt ist
            {
                /*Prüfen ob eine neue Einheit auf dem Grid ist*/
                if(selection->getUnit_stationed() != nullptr
                        && vec_unitGrid[selection->getQpoint_gridPosition().x()][selection->getQpoint_gridPosition().y()] == nullptr)
                {
                    vec_unitGrid[selection->getQpoint_gridPosition().x()][selection->getQpoint_gridPosition().y()] = selection->getUnit_stationed(); // in das Grid einfügen
                    selection->getUnit_stationed()->setPos(selection->pos());   //Position in der Scene setzen
                    ptr_gameWidget->getGameWidGameScene()->addItem(selection->getUnit_stationed());    //in die Scene einfügen
                }
                ptr_gameWidget->setOptScene(ptr_hexSelectionCache->getUnit_stationed()->getVector_unitStorage());

                ptr_gameWidget->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());    //Label updaten
                ptr_gameWidget->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());

                setFogOfWar();
            }
            resetTargetCache();
        }
        break;
    case PATH :
        moveUnitTo(selection);

        /*Neuen Selection Cache nach Bewegung*/
        ptr_hexSelectionCache = selection;
        ptr_hexSelectionCache->setState(ACTIVE);

        /*Darstellungen setzen*/
        ptr_gameWidget->setInfoScene(ptr_hexSelectionCache->getPtr_hexMfieldDisplay());
        ptr_gameWidget->setOptScene(ptr_hexSelectionCache->getUnit_stationed()->getVector_unitStorage());

        resetTargetCache();
        setFogOfWar();
        break;
    }
    checkUnitGrid();
    countUnits();
    ptr_gameWidget->updateInfoOptScenes();
    ptr_gameWidget->updateMatchfieldScene();
    checkWinCondition();
}

void Game::Dijkstra(HexagonMatchfield* start, int factor)
{
    /*
     * Berechnung aller kürzesten Wege vom SelectionCache aus innerhalb der Reichweite
     * Setzt den TargetChache mit den berechneten Zielen und setzt deren state auf TARGET
     * */
    HexagonMatchfield* target = start;

    std::priority_queue<std::pair<HexagonMatchfield*, int>, std::vector<std::pair<HexagonMatchfield*, int>>, Compare> frontier;

    frontier.push(std::pair<HexagonMatchfield*, int>(target, 0));
    map_hexCameFrom[target] = target;
    map_hexCurrentCost[target] = 0;

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
            neighbours = vec_qpointOddNeighbors;
        }else{
            neighbours = vec_qpointEvenNeighbors;
        }

        for(auto &it : neighbours)
        {
            int x = current->getQpoint_gridPosition().x() + it.x();
            int y = current->getQpoint_gridPosition().y() + it.y();

            /*Prüfen ob Nachbarn auf Spielfeld liegen*/
            if(x >= 0 && x < ptr_gameWidget->getSizeX() && y >= 0 && y < ptr_gameWidget->getSizeY()
                    && vec_hexGameGrid[x][y]->getState() != ACTIVE)
            {
                /*Speichern des zu betrachtenden Nachbarn*/
                HexagonMatchfield* neighbour = vec_hexGameGrid[x][y];

                /*Berechnen der neuen Kosten, bestehend aus den Kosten um auf das Aktuelle Feld zu kommen + die Kosten um zum  Nachbarn zu kommen*/
                if(target->getUnit_stationed()->moveTo(neighbour) != -1)
                {

                        /*Wenn dieser noch nicht betrachtet wurde, kosten absurd hochlegen, damit diese auf jeden fall gesetzt werden*/
                        if(map_hexCurrentCost.find(neighbour) == map_hexCurrentCost.end())
                            map_hexCurrentCost[neighbour] = 999;

                        int new_cost = map_hexCurrentCost[current] + target->getUnit_stationed()->moveTo(neighbour);

                        /*Wenn diese Kosten geringer als die Reichweite der Einheit und besser als die bisherigen Kosten sind, dann..*/
                        if(new_cost <= target->getUnit_stationed()->getUnitCurrentMoveRange()*factor && new_cost < map_hexCurrentCost[neighbour])
                        {
                            map_hexCurrentCost[neighbour] = new_cost; //Kosten aktualisieren
                            map_hexCameFrom[neighbour] = current;     //Vorgänger auf das Aktuelle Feld setzem
                            frontier.push(std::pair<HexagonMatchfield*, int> (neighbour, map_hexCurrentCost[neighbour])); //Den Nachbarn der Queue hinzufügen

                            vec_hexTargetCache.push_back(neighbour);   //und in den Target Cache Stecken
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
    ptr_gameWidget->setSizeX(dimX);
    ptr_gameWidget->setSizeY(dimY);

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
                if(unitType == "DEPOTUNIT")
                {
                   vecUnit.push_back(new DepotUnit(unitPath, ptr_playerTemp));
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
            connect(vecHexagon[j],SIGNAL(SIGNAL_centerThis(HexagonMatchfield*)), ptr_gameWidget, SLOT(SLOT_gameWidCenterHex(HexagonMatchfield*)));
        }
        vec_unitGrid.push_back(vecUnit);
        vec_hexGameGrid.push_back(vecHexagon);
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

    //Leere den das Spielfeld und befreie Speicher
    for(auto &it : vec_hexGameGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
        it.clear();
    }
    vec_hexGameGrid.clear();
    for(auto &it : vec_unitGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
        it.clear();
    }
    vec_unitGrid.clear();

    /*Einlesen der Dimensionen*/
    in >> dimX;
    in >> dimY;
    ptr_gameWidget->setSizeX(dimX);
    ptr_gameWidget->setSizeY(dimY);

    //Hexagone einlesen
    for(int i = 0; i < dimX; i++)
    {
        std::vector<HexagonMatchfield*> vecHexagon;
        for(int j = 0; j < dimY; j++)
        {
            in >> typeHex;
            vecHexagon.push_back(new HexagonMatchfield(QPoint(i,j), typeHex, nullptr));
            connect(vecHexagon[j],SIGNAL(SIGNAL_clicked(HexagonMatchfield*)),this,SLOT(processSelection(HexagonMatchfield*)));
            connect(vecHexagon[j],SIGNAL(SIGNAL_centerThis(HexagonMatchfield*)), ptr_gameWidget, SLOT(SLOT_gameWidCenterHex(HexagonMatchfield*)));
            tmp = in.readLine();
        }
        vec_hexGameGrid.push_back(vecHexagon);
    }


    //UnitGrid mit Nullptr initialisieren
    for(int i = 0; i < dimX; i++)
    {
        std::vector<Unit*> vecUnit;
        for(int j = 0; j < dimY; j++)
        {
            vecUnit.push_back(nullptr);
        }
        vec_unitGrid.push_back(vecUnit);
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
        if(ptr_hexSelectionCache != nullptr && ptr_hexSelectionCache->getUnit_stationed() != nullptr
                && ptr_hexSelectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
        {
            Dijkstra(ptr_hexSelectionCache);     //Berechnen aller möglichen Ziele
        }
    }
}

void Game::buttonPressedAction()
{
    if(ptr_roundCurrent->getCurrentPhase() == ACTION )
    {
        if(ptr_hexSelectionCache != nullptr && ptr_hexSelectionCache->getUnit_stationed() != nullptr
                && ptr_hexSelectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive
                && ptr_hexSelectionCache->getUnit_stationed()->getUnitUsed() == false)
        {
            calculateTargets(ptr_hexSelectionCache, ptr_hexSelectionCache->getUnit_stationed()->getActionRange());
        }
    }
}

void Game::buttonPressedMap()
{
        ptr_gameWidget->setEnableButtonScene(false);
        ptr_gameWidget->gameWidCreateMap(vec_hexGameGrid);
        ptr_gameWidget->getGameWidGameView()->setScene(ptr_gameWidget->getGameWidMapScene());
}

void Game::buttonPressedMenue()
{
    if(bool_menueView){
        ptr_gameWidget->getGameWidGameView()->setScene(ptr_gameWidget->getGameWidGameScene());
        ptr_gameWidget->setEnableButtonScene(true);
        bool_menueView = false;
    }else{
        ptr_gameWidget->getGameWidGameView()->setScene(ptr_gameWidget->getGameWidMenueScene());
        ptr_gameWidget->setEnableButtonScene(false);
        vec_buttonMenueBar[4]->setEnabled(true);
        bool_menueView = true;
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

    ptr_gameWidget->setPlayerLabel(ptr_playerActive->getPlayerName());
    ptr_gameWidget->setPhaseLabel(ptr_roundCurrent->getCurrentPhase() == MOVE ? "Move" : "Action");
    ptr_gameWidget->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameWidget->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
    if(ptr_hexSelectionCache != nullptr && ptr_hexSelectionCache->getUnit_stationed() != nullptr)
    {
        ptr_hexSelectionCache->getUnit_stationed()->resetBuildUnloadParameter();
    }
    resetUnits();
    ptr_gameWidget->repaintGameView();
    ptr_gameWidget->getGameWidButtonScene()->update();
}

void Game::SLOT_MenueButtonSelected(int menue)
{
    QString pathToLoadFile = "";
    switch(menue)
    {
    case 0 : saveGame(); return;
    case 1 : endGame(); return;
    case 2 :
        ptr_gameWidget->getGameWidGameView()->setScene(ptr_gameWidget->getGameWidGameScene());
        ptr_gameWidget->setEnableButtonScene(true);
        return;
    }

}

void Game::SLOT_checkStateOfButtons()
{
    if(ptr_roundCurrent->getCurrentPhase() == MOVE)
    {
        vec_buttonMenueBar[0]->setEnabled(true); // Setze das der Movebutton nicht "geschwaertzt" werden soll
        vec_buttonMenueBar[1]->setEnabled(false);// Setze das der Actionbutton "geschwaertzt" werden soll
    }
    else
    {
        vec_buttonMenueBar[0]->setEnabled(false); // Setze das der Movebutton "geschwaertzt" werden soll
        vec_buttonMenueBar[1]->setEnabled(true); // Setze das der Actionbutton nicht "geschwaertzt" werden soll
    }
}

/*HilfsFunktionen Start#######################################################################*/
void Game::resetHexMatchfield()
{
    /*Zurücksetzen der Auswahl*/
    if(ptr_hexSelectionCache != nullptr)
    {
        ptr_hexSelectionCache->setState(INACTIVE);
        ptr_hexSelectionCache = nullptr;
    }
    resetTargetCache();
    ptr_gameWidget->clearInfoScene();
    ptr_gameWidget->clearOptionsScene();
}

void Game::resetTargetCache()
{
    for(auto &it : vec_hexTargetCache)
    {
        it->setState(INACTIVE);
    }
    vec_hexTargetCache.clear();
    map_hexCameFrom.clear();
    map_hexCurrentCost.clear();
}
void Game::moveUnitTo(HexagonMatchfield * target)
{
    Unit* unitToMove = ptr_hexSelectionCache->getUnit_stationed();
    unitToMove->setUnitCurrentMoveRange(unitToMove->getUnitCurrentMoveRange() - map_hexCurrentCost[target]);

    if(target->getUnit_stationed() != nullptr &&
            (target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
            || target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
            || target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER"))
    {
        target->getUnit_stationed()->addUnitToStorage(unitToMove); // Einheit in den Vektor der Transportereinheit verlegt
        ptr_gameWidget->getGameWidGameScene()->removeItem(unitToMove); // Einheit aus der Scene gelöscht
    }
    else
    {
        target->setUnit_stationed(unitToMove);      //Einheit verlegen auf das Ziel
        vec_unitGrid[target->getQpoint_gridPosition().x()][target->getQpoint_gridPosition().y()] = unitToMove; //Einheit im Grid verlegt

        /*Animation*/
        vector<QPointF> path;
        for(auto& iterator = target; iterator != ptr_hexSelectionCache; iterator = map_hexCameFrom[iterator])
        {
            path.push_back(iterator->pos());
        }
        ptr_gameWidget->animateUnit(unitToMove, path);
    }
    vec_unitGrid[ptr_hexSelectionCache->getQpoint_gridPosition().x()][ptr_hexSelectionCache->getQpoint_gridPosition().y()] = nullptr; //Einheit aus dem UnitGrid löschen
    ptr_hexSelectionCache->setUnit_stationed(nullptr);     //Einheit vom alten feld entfernen
    ptr_hexSelectionCache->setState(INACTIVE);     //Auswahl auf inactiv setzen
    ptr_hexSelectionCache = nullptr;
}
void Game::showNeighbors(HexagonMatchfield * center)
{
    if(center->getQpoint_gridPosition().x() & 1)
    {
        for(auto &it: vec_qpointOddNeighbors)
        {
            int x = center->getQpoint_gridPosition().x() + it.x();
            int y = center->getQpoint_gridPosition().y() + it.y();
            if(x >= 0 && x < ptr_gameWidget->getSizeX() && y >= 0 && ptr_gameWidget->getSizeY())
            {
                vec_hexGameGrid[x][y]->setState(TARGET);
                vec_hexTargetCache.push_back(vec_hexGameGrid[x][y]);
            }
        }
    }else{
        for(auto &it: vec_qpointEvenNeighbors)
        {
            int x = center->getQpoint_gridPosition().x() + it.x();
            int y = center->getQpoint_gridPosition().y() + it.y();
            {
                vec_hexGameGrid[x][y]->setState(TARGET);
                vec_hexTargetCache.push_back(vec_hexGameGrid[x][y]);
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
            neighbours = vec_qpointOddNeighbors;
        }else{
            neighbours = vec_qpointEvenNeighbors;
        }

        for(auto &it : neighbours)    //Durchlaufen der Nachbarn
        {
            int x = current->getQpoint_gridPosition().x() + it.x();    //Koordinaten des neuen Ziels
            int y = current->getQpoint_gridPosition().y() + it.y();

            if(x >= 0 && x < ptr_gameWidget->getSizeX() && y >= 0 && y < ptr_gameWidget->getSizeY()         //Wenn das ziel auf dem Spielfeld liegt
                    && vec_hexGameGrid[x][y]->getState() != TARGET && vec_hexGameGrid[x][y]->getState() != ACTIVE)  //Wenn das Ziel nicht bereits als TARGET markiert wurde
            {
                HexagonMatchfield* neighbour = vec_hexGameGrid[x][y];         //Zwischenspeichern für lesbarkeite
                if(offset_distance(center->getQpoint_gridPosition(), neighbour->getQpoint_gridPosition()) <= range)          //Wenn das ziel in der Reichweite der Einheite liegt
                {
                    neighbour->setState(TARGET);
                    vec_hexTargetCache.push_back(neighbour);
                    frontier.push(neighbour);
                }
            }
        }
    }
}

void Game::setFogOfWar()
{
    for(auto &iterator : vec_hexGameGrid)
    {
        for(auto &hex : iterator)
        {
            hex->setHexFogOfWar(true);
        }
    }
    for(auto &iterator : vec_hexGameGrid)
    {
        for(auto &hex : iterator)
        {
            if(hex->getUnit_stationed() != nullptr && hex->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
            {
                calculateTargets(hex, hex->getUnit_stationed()->getUnitView());
                for(auto &it : vec_hexTargetCache)
                {
                    it->setHexFogOfWar(false);
                }
                hex->setHexFogOfWar(false);
                resetTargetCache();
            }
        }
    }
    ptr_gameWidget->repaintGameView();
}

void Game::showPath(HexagonMatchfield* target)
{
    for(auto &it = target; it != ptr_hexSelectionCache; it = map_hexCameFrom[it])
    {
        it->setState(PATH);
    }
}

void Game::checkUnitGrid()
{
    for(int x = 0; x < ptr_gameWidget->getSizeX(); x++)
    {
        for(int y = 0; y < ptr_gameWidget->getSizeY(); y++)
        {
            if(vec_unitGrid[x][y] != nullptr && vec_unitGrid[x][y]->checkUnitDestroyed())
            {
                vec_hexGameGrid[x][y]->setUnit_stationed(nullptr);
                delete vec_unitGrid[x][y];
                vec_unitGrid[x][y] = nullptr;
            }
        }
    }
    ptr_gameWidget->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
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
    for(auto &iteratorX : vec_unitGrid)    //Durchlaufen des Grids
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

    for(auto &iterator : vec_unitGrid)
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

bool Game::readSaveGame(QString filepath)
{
    /*
     * Lade ein Spiel aus einer gespeicherten txt Datei mit dem Pfad filepath
     * Versionsnummer muss mit der Version des Ladens übereinstimmen
     * */
    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "File nicht gefunden";
        return false;
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
        return false;
    }

    tmp = in.readLine();

    //Ueberpruefe Format
    QString textType;
    textType = in.readLine();

    if(textType != "Save Game")
    {
        qDebug() << "Falsches Format. Eingelesen: " << textType;
        return false;
    }

    ptr_options = Options::unserialize(in);

    if( ptr_options->getBool_ki() == true)

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

    loadMapFromSaveGame(ptr_options->getStr_map());

    int posX, posY, boltanium, unitStationed;

    in >> tmp;
    while(tmp != "")
    {
       posX = tmp.toInt();
       in >> posY;
       in >> boltanium;
       in >> unitStationed;

       vec_hexGameGrid[posX][posY]->setBoltaniumCurrent(boltanium);

       if(unitStationed == 1)
       {
           vec_unitGrid[posX][posY] = readUnitFromStream(in);
           if(vec_unitGrid[posX][posY] != nullptr)
           {
               vec_hexGameGrid[posX][posY]->setUnit_stationed(vec_unitGrid[posX][posY]);
           }

       }else{
           vec_unitGrid[posX][posY] = nullptr;
       }
       in >> tmp;
    }
    return true;
}

void Game::createRandomMap()
{

    //Für eine Zufallszahl
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    //Größe
    int sizeX = qrand() % 100 + 20;
    int sizeY = qrand() % 100 + 20;

    ptr_gameWidget->setSizeX(sizeX);
    ptr_gameWidget->setSizeY(sizeY);

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
    for(auto &it : vec_hexGameGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
        it.clear();
    }
    vec_hexGameGrid.clear();

    for(auto &it : vec_unitGrid)
    {
        for(auto &ut : it)
        {
            delete ut;
        }
        it.clear();
    }
    vec_unitGrid.clear();

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
                if(vec_hexGameGrid[i-1][j]->getHexMatchfieldType() == "forrest")
                    modulo += 6;
                if(vec_hexGameGrid[i-1][j-1]->getHexMatchfieldType() == "forrest")
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
            connect(vectorHex[j],SIGNAL(SIGNAL_centerThis(HexagonMatchfield*)), ptr_gameWidget, SLOT(SLOT_gameWidCenterHex(HexagonMatchfield*)));
        }
        vec_hexGameGrid.push_back(vectorHex);
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
                    QString hexType = vec_hexGameGrid[i][j]->getHexMatchfieldType();
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
                    vec_hexGameGrid[i][j]->setUnit_stationed(vectorUnit[j]);

                }else{
                    vectorUnit.push_back(nullptr);
                }
        }
        vec_unitGrid.push_back(vectorUnit);
    }
}

void Game::createButtons()
{
    ButtonMove* movebutton = new ButtonMove(64,64);
    ButtonAction* actionbutton = new ButtonAction(64,64);
    ButtonChangePhase* changephasebutton = new ButtonChangePhase(64,64);
    ButtonMap* mapbutton = new ButtonMap(64,64);
    ButtonMenue* menuebutton = new ButtonMenue(64,64);

    vec_buttonMenueBar.push_back(movebutton);
    vec_buttonMenueBar.push_back(actionbutton);
    vec_buttonMenueBar.push_back(changephasebutton);
    vec_buttonMenueBar.push_back(mapbutton);
    vec_buttonMenueBar.push_back(menuebutton);
    connect(movebutton,SIGNAL(clicked()),this,SLOT(buttonPressedMove()));
    connect(actionbutton,SIGNAL(clicked()),this,SLOT(buttonPressedAction()));
    connect(changephasebutton,SIGNAL(clicked()),this,SLOT(buttonPressedChangePhase()));
    connect(mapbutton, SIGNAL(clicked()), this, SLOT(buttonPressedMap()));
    connect(menuebutton,SIGNAL(clicked()),this,SLOT(buttonPressedMenue()));

    connect(ptr_gameWidget, SIGNAL(SIGNAL_MenueButtonPushed(int)), this, SLOT(SLOT_MenueButtonSelected(int)));
    connect(ptr_gameWidget, SIGNAL(SIGNAL_changeStateOfButtons()), this, SLOT(SLOT_checkStateOfButtons()));
    SLOT_checkStateOfButtons();

    ptr_gameWidget->gameWidCreateButtonBar(vec_buttonMenueBar);
}

Unit *Game::createUnitFromType(QString unitType, QString unitPath, Player * ptr_playerTemp)
{
    if(unitType == "FACTORYUNIT")
    {
        return new FactoryUnit(unitPath, true, ptr_playerTemp);
    }

    if( unitType == "HEADQUATERUNIT")
    {
        return new HeadquaterUnit(unitPath,ptr_playerTemp);
    }

    if( unitType == "DEPOTUNIT")
    {
        return new DepotUnit(unitPath,ptr_playerTemp);
    }

    if(unitType == "AIRUNIT")
    {
        return new AirUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "LIGHTUNIT")
    {
        return new LightUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "MEDIUMUNIT")
    {
        return new MediumUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "HEAVYUNIT")
    {
        return new HeavyUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "WATERUNIT")
    {
        return new WaterUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "TRANSPORTERGROUND")
    {
        return new TransporterGroundUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "TRANSPORTERWATER")
    {
        return new TransporterWaterUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "TRANSPORTERAIR")
    {
        return new TransporterAirUnit(unitPath, ptr_playerTemp);
    }

    if(unitType == "BUILDERUNIT")
    {
        return new BuildLightUnit(unitPath, true,ptr_playerTemp);
    }

    return nullptr;
}

Unit *Game::readUnitFromStream(QTextStream &in)
{
    int unitPlayer, unitHP, unitMoveRange, unitUsed, unitLevel;
    QString unitType, unitPath;

    bool isDynamicUnit = true;
    bool isTransporterUnit = false;
    Unit* unitFromStream = nullptr;

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

    unitFromStream = createUnitFromType(unitType, unitPath, ptr_playerTemp);
    if(unitFromStream != nullptr)
    {
        unitFromStream->setUnitCurrentHP(unitHP);
        unitFromStream->setUnitUsed(unitUsed);

        if(unitType == "DEPOTUNIT" || unitType == "HEADQUATERUNIT" || unitType == "FACTORYUNIT")
        {
            isDynamicUnit = false;
        }else if(unitType.contains("TRANSPORTER"))
        {
            isTransporterUnit = true;
        }

        qDebug() << "\t" << isDynamicUnit << "\n\t" << isTransporterUnit;
        if(isDynamicUnit == true)
        {
            in >> unitLevel;
            in >> unitMoveRange;
            unitFromStream->setUnitCurrentMoveRange(unitMoveRange);
            //unitFromStream->setUnitLevel(unitLevel);
            qDebug() << "\t" << unitMoveRange << "\n\t" << unitLevel;
        }

        if(isTransporterUnit == true)
        {
            loadInventory(in, unitFromStream);
        }
    }
    return unitFromStream;
}

void Game::loadInventory(QTextStream & in, Unit * containerUnit)
{
    int size = 0;
    in >> size;
    for(int i = 0; i < size; i++)
    {
        containerUnit->addUnitToStorage(readUnitFromStream(in));
    }
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
    ptr_options->serialize(out);
    ptr_playerOne->serialize(out);
    ptr_playerTwo->serialize(out);
    out << ptr_playerActive->getPlayerID() << "\n";
    ptr_roundCurrent->serialize(out);
    for(auto &iteratorX : vec_hexGameGrid)
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

//fuer ki
std::vector<HexagonMatchfield*> Game::getTargetCache() const
{
    return vec_hexTargetCache;
}

std::map<HexagonMatchfield*, HexagonMatchfield*> Game::getCamefrom() const
{
    return map_hexCameFrom;
}
std::map<HexagonMatchfield*, int> Game::getCurrentCost() const
{
    return map_hexCurrentCost;
}
