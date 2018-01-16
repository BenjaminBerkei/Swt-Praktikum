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
using namespace std;

/*Noch fertig schreiben*/
std::vector<QPoint> Game::vector_evenNeighbors = {QPoint(1,0),QPoint(1,-1),QPoint(0,-1),QPoint(-1,-1),QPoint(-1,0),QPoint(0,1)};
std::vector<QPoint> Game::vector_oddNeighbors = {QPoint(1,1),QPoint(1,0),QPoint(0,-1),QPoint(-1,0),QPoint(-1,1),QPoint(0,1)};


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
    ptr_gameGameWid(ptr_gameWid), ptr_playerOne(new Player("Eins", 1)), ptr_playerTwo(new Player("Zwei", 2)), ptr_playerActive(ptr_playerOne),
    ptr_roundCurrent(new Round(10))
{
    // Erstelle eine Map
    // Dies ist nur für Testzwecke! Sollte später gelöscht werden:
    //##################################################################
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
            connect(vectorHex[j],SIGNAL(SIGNAL_clicked(HexagonMatchfield*)),this,SLOT(processSelection(HexagonMatchfield*)));
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
                        int randomUnitType = qrand() % 8;

                        switch(randomUnitType)
                        {
                        case 0 : randomUnit = new AirUnit(":/dynamic/dynamicUnit/derbolten.txt", randPlayer); break;
                        case 1 : randomUnit = new TransporterGroundUnit(":/dynamic/dynamicUnit/kevarn.txt", randPlayer); break;
                        case 2 : randomUnit = new LightUnit(":/dynamic/dynamicUnit/ben.txt", randPlayer); break;
                        case 3 : randomUnit = new MediumUnit(":/dynamic/dynamicUnit/lucas.txt", randPlayer); break;
                        case 4 : randomUnit = new HeavyUnit(":/dynamic/dynamicUnit/mannuel.txt", randPlayer); break;
                        case 5 : randomUnit = new DepotUnit(":/static/staticUnit/depot.txt", randPlayer); break;
                        case 6 : randomUnit = new FactoryUnit(":/static/staticUnit/factory.txt", randPlayer); break;
                        case 7 :
                            if(anzHQ < 2)
                            {
                                randomUnit = new HeadquaterUnit(":/static/staticUnit/headquater.txt", anzHQ == 0 ? ptr_playerOne : ptr_playerTwo);
                                anzHQ++;
                            }
                            break;
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
    ptr_gameGameWid->gameWidCreateMatchfield(hexagonMatchfield_gameGrid);
    countUnits();
    setFogOfWar();


    ptr_gameGameWid->setPlayerLabel(ptr_playerActive->getPlayerName());
    ptr_gameGameWid->setPhaseLabel("Move");
    ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
       //##################################################################

    //Buttons Einfuegen
    ButtonMove* movebutton = new ButtonMove(64,64);
    ButtonAction* actionbutton = new ButtonAction(64,64);
    ButtonChangePhase* changephasebutton = new ButtonChangePhase(64,64);
    //ButtonMenue* menuebutton = new ButtonMenue(64,64);

    button_menueBar.push_back(movebutton);
    button_menueBar.push_back(actionbutton);
    button_menueBar.push_back(changephasebutton);
    //button_menueBar.push_back(menuebutton);
    connect(movebutton,SIGNAL(clicked()),this,SLOT(buttonPressedMove()));
    connect(actionbutton,SIGNAL(clicked()),this,SLOT(buttonPressedAction()));
    connect(changephasebutton,SIGNAL(clicked()),this,SLOT(buttonPressedChangePhase()));
    //connect(menuebutton,SIGNAL(clicked()),this,SLOT(buttonPressedMenue()));

    ptr_gameGameWid->gameWidCreateButtonBar(button_menueBar);
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
        qDebug() << "case INACTIVE";

        /*Wenn vorher eine auswahl da war, welche ein transporter oder factory war, müssen die zurückgesetzt werden*/
        if(SelectionCache != nullptr && SelectionCache->getUnit_stationed() != nullptr)
        {
            SelectionCache->getUnit_stationed()->resetBuildUnloadParameter();
        }

        resetHexMatchfield();
        SelectionCache = selection;
        ptr_gameGameWid->setInfoScene(SelectionCache->getPtr_hexMfieldDisplay());

        if(SelectionCache->getUnit_stationed() != nullptr && SelectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
        {
            ptr_gameGameWid->setOptScene(SelectionCache->getUnit_stationed()->getVector_unitStorage());
        }
        //Angeklicktes auf AKTIVE setzten
        SelectionCache->setState(ACTIVE);
        break;

    case ACTIVE:
        qDebug() << "case ACTIVE";

        /*Wenn vorher eine auswahl da war, welche ein transporter oder factory war, müssen die zurückgesetzt werden*/
        if(SelectionCache != nullptr && SelectionCache->getUnit_stationed() != nullptr)
        {
            SelectionCache->getUnit_stationed()->resetBuildUnloadParameter();
        }
        resetHexMatchfield();
        break;

    case TARGET:
        qDebug() << "case TARGET";
        if(ptr_roundCurrent->getCurrentPhase() == MOVE)     //Move Phase
        {
            for(auto &it : TargetChache)        //Ziele auf zustand TARGET zurücksetzen
            {
                it->setState(TARGET);
            }
            showPath(selection);            //Weg von Ziel zu auswahl anzeigen

        }else if(ptr_roundCurrent->getCurrentPhase() == ACTION )    //Action Phase
        {
            if(SelectionCache->getUnit_stationed()->action(selection))  //Wenn die Action geglückt ist
            {
                /*Prüfen ob eine neue Einheit auf dem Grid ist*/
                if(selection->getUnit_stationed() != nullptr
                        && unit_UnitGrid[selection->getQpoint_gridPosition().x()][selection->getQpoint_gridPosition().y()] == nullptr)
                {
                    unit_UnitGrid[selection->getQpoint_gridPosition().x()][selection->getQpoint_gridPosition().y()] = selection->getUnit_stationed(); // in das Grid einfügen
                    selection->getUnit_stationed()->setPos(selection->pos());   //Position in der Scene setzen
                    ptr_gameGameWid->getGameWidGameScene()->addItem(selection->getUnit_stationed());    //in die Scene einfügen
                }
                ptr_gameGameWid->setOptScene(SelectionCache->getUnit_stationed()->getVector_unitStorage());

                ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());    //Label updaten
                ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());

                setFogOfWar();
            }
            resetTargetChache();
        }
        break;
    case PATH :
        qDebug() << "case PATH";
        moveUnitTo(selection);
        qDebug() << "nach moveUnitTo";

        /*Neuen Selection Cache nach Bewegung*/
        SelectionCache = selection;
        SelectionCache->setState(ACTIVE);

        qDebug() << "SelectionCache State:" << SelectionCache->getState() << "\n"
                 << "\t" << SelectionCache->getQcolor_HexColor();

        /*Darstellungen setzen*/
        ptr_gameGameWid->setInfoScene(SelectionCache->getPtr_hexMfieldDisplay());
        ptr_gameGameWid->setOptScene(SelectionCache->getUnit_stationed()->getVector_unitStorage());

        resetTargetChache();
        setFogOfWar();
        break;
    }
    qDebug() << "Switch ende";
    checkUnitGrid();
    checkWinCondition();
    countUnits();
    ptr_gameGameWid->updateInfoOptScenes();
    ptr_gameGameWid->updateMatchfieldScene();
    qDebug() << "ProcessSelection ende";
}

void Game::Dijkstra()
{
    HexagonMatchfield* target = SelectionCache;

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

                            TargetChache.push_back(neighbour);   //und in den Target Cache Stecken
                            neighbour->setState(TARGET);
                        }

                }
            }
        }
    }
}





/*Move Button ausgewählt*/
void Game::buttonPressedMove()
{
    if(ptr_roundCurrent->getCurrentPhase() == MOVE)     //Phase prüfen
    {
        /*Wenn ein Feld ausgewählt wurde auf dem eine Einheit steht, welche dem aktiven Spieler gehört*/
        if(SelectionCache != nullptr && SelectionCache->getUnit_stationed() != nullptr
                && SelectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
        {
            Dijkstra();     //Berechnen aller möglichen Ziele
        }
    }
}

void Game::buttonPressedAction()
{
    if(ptr_roundCurrent->getCurrentPhase() == ACTION )
    {
        if(SelectionCache != nullptr && SelectionCache->getUnit_stationed() != nullptr
                && SelectionCache->getUnit_stationed()->getUnitPlayer() == ptr_playerActive
                && SelectionCache->getUnit_stationed()->getUnitUsed() == false)
        {
            calculateTargets(SelectionCache, SelectionCache->getUnit_stationed()->getActionRange());
        }
    }
}

void Game::buttonPressedMenue()
{

}

void Game::buttonPressedChangePhase()
{
    ptr_roundCurrent->changePhase();

    if(ptr_roundCurrent->getCurrentPhase() == MOVE)
    {
        ptr_playerActive = ptr_playerActive == ptr_playerOne ? ptr_playerTwo : ptr_playerOne;
        resetUnits(ptr_playerActive);
        resetHexMatchfield();
        setFogOfWar();
    }
    resetTargetChache();

    ptr_gameGameWid->setPlayerLabel(ptr_playerActive->getPlayerName());
    ptr_gameGameWid->setPhaseLabel(ptr_roundCurrent->getCurrentPhase() == MOVE ? "Move" : "Action");
    ptr_gameGameWid->setUnitsLabel(ptr_playerActive->getPlayerUnitNumber());
    ptr_gameGameWid->setEnergieLabel(ptr_playerActive->getCurrentEnergieStorage(), ptr_playerActive->getPlayerTotalEnergie());
    if(SelectionCache != nullptr && SelectionCache->getUnit_stationed() != nullptr)
    {
        SelectionCache->getUnit_stationed()->resetBuildUnloadParameter();
    }
}

/*HilfsFunktionen Start#######################################################################*/
void Game::resetHexMatchfield()
{
    /*Zurücksetzen der Auswahl*/
    if(SelectionCache != nullptr)
    {
        SelectionCache->setState(INACTIVE);
        SelectionCache = nullptr;
    }
    resetTargetChache();
    ptr_gameGameWid->clearScenes();
}

void Game::resetTargetChache()
{
    for(auto &it : TargetChache)
    {
        it->setState(INACTIVE);
    }
    TargetChache.clear();
    came_from.clear();
    current_cost.clear();
}
void Game::moveUnitTo(HexagonMatchfield * target)
{
    Unit* unitToMove = SelectionCache->getUnit_stationed();
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
        for(auto& iterator = target; iterator != SelectionCache; iterator = came_from[iterator])
        {
            path.push_back(iterator->pos());
        }
        ptr_gameGameWid->animateUnit(unitToMove, path);
    }
    unit_UnitGrid[SelectionCache->getQpoint_gridPosition().x()][SelectionCache->getQpoint_gridPosition().y()] = nullptr; //Einheit aus dem UnitGrid löschen
    SelectionCache->setUnit_stationed(nullptr);     //Einheit vom alten feld entfernen
    SelectionCache->setState(INACTIVE);     //Auswahl auf inactiv setzen
    SelectionCache = nullptr;
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
                TargetChache.push_back(hexagonMatchfield_gameGrid[x][y]);
            }
        }
    }else{
        for(auto &it: vector_evenNeighbors)
        {
            int x = center->getQpoint_gridPosition().x() + it.x();
            int y = center->getQpoint_gridPosition().y() + it.y();
            {
                hexagonMatchfield_gameGrid[x][y]->setState(TARGET);
                TargetChache.push_back(hexagonMatchfield_gameGrid[x][y]);
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
                    TargetChache.push_back(neighbour);
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
            if(hex->getUnit_stationed() != nullptr && hex->getUnit_stationed()->getUnitPlayer() == ptr_playerActive)
            {
                calculateTargets(hex, hex->getUnit_stationed()->getUnitView());
            }
        }
    }

    for(auto &iterator : hexagonMatchfield_gameGrid)
    {
        for(auto &hex : iterator)
        {
            if(hex->getState() == INACTIVE)
            {
                hex->setHexFogOfWar(true);
            }else{
                hex->setHexFogOfWar(false);
            }
        }
    }
    resetTargetChache();
}

void Game::showPath(HexagonMatchfield* target)
{
    for(auto &it = target; it != SelectionCache; it = came_from[it])
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
    }
    if(ptr_playerTwo->getPlayerUnitNumber() == 0 || ptr_playerTwo->getHQDestroyed())
    {
        qDebug() << "Spieler Zwei Verloren";
    }
}

void Game::resetUnits(Player * player)
{
    for(auto &iteratorX : unit_UnitGrid)    //Durchlaufen des Grids
    {
        for(auto &unit : iteratorX)
        {
            if(unit != nullptr && unit->getUnitPlayer() == player)
            {
                unit->resetUnit();     //Untis Move range zurücksetzen
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
            if(unit != nullptr)
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

int Game::offset_distance(QPoint a, QPoint b)
{
    QVector3D ac = oddqToCube(a);
    QVector3D bc = oddqToCube(b);
    return cube_distance(ac, bc);
}


/*HilfsFunktionen Ende#######################################################################*/

bool Compare::operator()(std::pair<HexagonMatchfield*, int> a, std::pair<HexagonMatchfield*, int> b)
{
    return a.second < b.second;
}
