///////////////////////////////////////
//ki.h
//version 0.2
//autor: Miguel
//letzte Änderung: 26.01.2018 (Miguel)
//Kommentar:
///////////////////////////////////////

#ifndef KI_H
#define KI_H

#include "game.h"
#include "player.h"
#include "unit.h"
#include "hexagonbase.h"
#include "hexagonmatchfield.h"
#include "round.h"
#include "gamewidget.h"
#include "staticunit.h"
#include "dynamicunit.h"
#include "button.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <QTime>
#include <QObject>
#include <QGraphicsView>
#include <QString>
#include <QDebug>
#include <chrono>
#include <thread>

class GameWidget; //Vorwärtsdeklaration
class HexagonMatchfield;
class Unit;
class Button;
class Player;
class Game;

class KI
{
private:
	Player* kiPlayer;
	Game* kiGame;
    std::unordered_set<HexagonMatchfield*> kiMyUnits;
    std::unordered_set<HexagonMatchfield*> kiTargetCache;
    std::unordered_set<HexagonMatchfield*> prioCache;
	std::vector<std::vector<HexagonMatchfield*>> kiMyMatchfield;
	HexagonMatchfield* kiEnemyHq;
	HexagonMatchfield* kiMyHq;
	bool kiHq_danger;

public:
	KI(Game*, Player*, std::vector<std::vector<HexagonMatchfield*>>);
    ~KI();

    void autoPlayMove();
	void autoMovePhase(HexagonMatchfield*);
    void autoPlayAction();
    //void autoActionPhase(HexagonMatchfield*);
	void fillKiMyUnits_Cache();
	void delKiMyUnits_Cache();
    //bool isHexInCache(HexagonMatchfield*,std::vector<HexagonMatchfield*>);

    void moveUnit(HexagonMatchfield*, HexagonMatchfield*, int);
    void unitMoveRandom(HexagonMatchfield*);
    HexagonMatchfield* calcActionRange(std::unordered_set<HexagonMatchfield*>, HexagonMatchfield*, int);
    std::unordered_set<HexagonMatchfield*> goodHexCache(std::unordered_set<HexagonMatchfield*>);
	void checkHQinDanger();
};

#endif // !KI_H
