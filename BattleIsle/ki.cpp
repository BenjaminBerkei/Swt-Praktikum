///////////////////////////////////////
//ki.cpp
//version 0.5
//autor: Miguel
//letzte Änderung: 26.01.2018 (Miguel)
//Kommentar: move funktioniert
///////////////////////////////////////

#include "ki.h"

KI::KI(Game* game, Player* player, std::vector<std::vector<HexagonMatchfield*>> matchfield)
	: kiGame(game), kiPlayer(player), kiMyMatchfield(matchfield), kiHq_danger(false)
{
    for (unsigned int i = 0; i < kiMyMatchfield.size(); i++)
	{
        for (unsigned int j = 0; j < kiMyMatchfield[i].size(); j++)
		{
			if (kiMyMatchfield[i][j]->getUnitStationed() != nullptr)
			{
                if (kiMyMatchfield[i][j]->getUnitStationed()->getUnitType() == "HEADQUATERUNIT")
				{
					if (kiMyMatchfield[i][j]->getUnitStationed()->getUnitPlayer()->getPlayerID() != kiPlayer->getPlayerID())
                    {
                        kiEnemyHq = kiMyMatchfield[i][j];
                        qDebug() << "enemy hq set" << kiMyMatchfield[i][j]->getQpoint_gridPosition().x() << kiMyMatchfield[i][j]->getQpoint_gridPosition().y();
                    }
					else
                    {
						kiMyHq = kiMyMatchfield[i][j];
                        qDebug() << "my hq set" << kiMyMatchfield[i][j]->getQpoint_gridPosition().x() << kiMyMatchfield[i][j]->getQpoint_gridPosition().y();
                    }
				}
			}
		}
	}
}

KI::~KI(){}

void KI::autoPlayMove()
{	
    QMessageBox msgBox;
    msgBox.setText("Ki Move Phase!\nBitte bestätigen.");
    msgBox.setDefaultButton(QMessageBox::NoButton);
    msgBox.exec();
    fillKiMyUnits_Cache();
    if(!prioCache.empty())
        prioCache.clear();
    checkHQinDanger();
    int i =0;
	for (auto it : kiMyUnits)
    {
		autoMovePhase(it);
        qDebug() << "auto fertig" << i;
        i++;
        std::this_thread::sleep_for (std::chrono::milliseconds(500));
	}
    qDebug() << "t moved all moveable units";
	delKiMyUnits_Cache();
	//changePhase
	kiGame->buttonPressedChangePhase();
}

void KI::autoPlayAction()
{
    QMessageBox msgBox;
    msgBox.setText("Ki Action Phase!\nBitte bestätigen.");
    msgBox.setDefaultButton(QMessageBox::NoButton);
    msgBox.exec();
    /*fillKiMyUnits_Cache();
	for (auto it : kiMyUnits)
	{
		autoActionPhase(it);
	}
	delKiMyUnits_Cache();
    */
	// changePhase
	kiGame->buttonPressedChangePhase();
}

void KI::autoMovePhase(HexagonMatchfield* hex)
{	
    qDebug() << hex->getUnitStationed()->getUnitType();
    kiGame->processSelection(hex);
    std::unordered_set<HexagonMatchfield*> tmpCache;
    qDebug() << tmpCache.size();
    for (int i = 1; i <= 4; i++)
    {
        kiGame->Dijkstra(hex, i);
        tmpCache = kiGame->getTargetCache();
        if(hex->getUnitStationed()->getUnitType().contains("TRANSPORTER"))
        {
            if (hex->getUnitStationed()->getUnitCurrentHP() <= hex->getUnitStationed()->getUnitHP() / 2)
            {
                std::unordered_set<HexagonMatchfield*> tmpGood = goodHexCache(tmpCache);
                tmpCache.clear();
                tmpCache = tmpGood;
            }
            for (auto itCache : tmpCache)
            {
                if (itCache->getBoltaniumCurrent() > 0)
                {
                    moveUnit(itCache, hex, i);
                    return;
                }
            }
        }
        else if(hex->getUnitStationed()->getUnitType() == "BUILDERUNIT")
        {
            if (hex->getUnitStationed()->getUnitCurrentHP() <= hex->getUnitStationed()->getUnitHP() / 2)
            {
                std::unordered_set<HexagonMatchfield*> tmpGood = goodHexCache(tmpCache);
                tmpCache.clear();
                tmpCache = tmpGood;
            }

            for (auto itCache : tmpCache)
            {
                if (itCache->getUnitStationed() == nullptr);
                {
                    moveUnit(itCache, hex, i);
                    return;
                }
            }
        }
        else if(hex->getUnitStationed()->getUnitType() == "WATERUNIT" || hex->getUnitStationed()->getUnitType() =="AIRUNIT" || hex->getUnitStationed()->getUnitType() =="LIGHTUNIT" || hex->getUnitStationed()->getUnitType() =="MEDIUMUNIT" || hex->getUnitStationed()->getUnitType() =="HEAVYUNIT")
        {
            int tmpRange = hex->getUnitStationed()->getActionRange();
            if (kiHq_danger == true)
            {
                for(auto danger : prioCache)
                {
                    HexagonMatchfield* tmpTarget = calcActionRange(tmpCache, danger, tmpRange);
                    if(tmpTarget != nullptr)
                    {
                        moveUnit(tmpTarget, hex, i);
                        return;
                    }
                }
            }
            if (hex->getUnitStationed()->getUnitCurrentHP() <= hex->getUnitStationed()->getUnitHP() / 2)
            {
                for (auto itCache : tmpCache)
                {
                    if (kiMyUnits.find(itCache) != kiMyUnits.end() && itCache->getUnitStationed()->getUnitType() == "DEPOTUNIT")
                    {
                        moveUnit(itCache, hex, i);
                        return;
                    }
                }
            }
            else
            {
                //Hauptziel gegnerisches HQ zerstören
                for(auto danger : kiTargetCache)
                {
                    if(danger->getQpoint_gridPosition() == kiEnemyHq->getQpoint_gridPosition())
                    {
                        HexagonMatchfield* tmpTarget = calcActionRange(tmpCache, danger, tmpRange);
                        if(tmpTarget != nullptr)
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                    }
                }
                //sonst andere ziele zerstören
                for(auto danger : kiTargetCache)
                {
                    QString enemyType = danger->getUnitStationed()->getUnitType();
                    QString myType = hex->getUnitStationed()->getUnitType();
                    HexagonMatchfield* tmpTarget = calcActionRange(tmpCache, danger, tmpRange);
                    if(tmpTarget != nullptr)
                    {
                        //wenn die gegnerische unit 1hit ist dann gehe zu ihr
                        if (enemyType == "WATERUNIT" && hex->getUnitStationed()->getUnitWaterAtt() >= danger->getUnitStationed()->getUnitCurrentHP())
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                        //wenn die gegnerische unit 1hit ist dann gehe zu ihr
                        else if (enemyType == "AIRUNIT" && hex->getUnitStationed()->getUnitAirAtt() >= danger->getUnitStationed()->getUnitCurrentHP())
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                        //wenn die gegnerische unit 1hit ist dann gehe zu ihr
                        else if ((enemyType == "LIGHTUNIT" || enemyType == "MEDIUMUNIT" || enemyType == "HEAVYUNIT") && hex->getUnitStationed()->getUnitGroundAtt() >= danger->getUnitStationed()->getUnitCurrentHP())
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                        //wenn ich nicht onehit bin, gehe dahin
                        else if (myType == "WATERUNIT" && hex->getUnitStationed()->getUnitCurrentHP() >= danger->getUnitStationed()->getUnitWaterAtt())
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                        //wenn ich nicht onehit bin, gehe dahin
                        else if (myType == "AIRUNIT" && hex->getUnitStationed()->getUnitCurrentHP() >= danger->getUnitStationed()->getUnitAirAtt())
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                        //wenn ich nicht onehit bin, gehe dahin
                        else if ((myType == "LIGHTUNIT" ||  myType =="MEDIUMUNIT" || myType =="HEAVYUNIT") && hex->getUnitStationed()->getUnitCurrentHP() >= danger->getUnitStationed()->getUnitAirAtt())
                        {
                            moveUnit(tmpTarget, hex, i);
                            return;
                        }
                    }
                }
            }
        }
    }
    if(hex->getUnitStationed()->getUnitCurrentMoveRange() > 0)
    {
        unitMoveRandom(hex);
        return;
    }
    return;
}


/*void KI::autoActionPhase(Unit* unit)
{
	if(unit->getUnitType() == ("TRANSPORTERAIRUNIT" || "TRANSPORTERWATERUNIT" || "TRANSPORTERGROUNDUNIT") )
	{
		if (unit->getTransporterUnitCurrentCapacity() == unit->getTransporterUnitCapacity())
		{
			// wenn nahe hauptgebäude -> ausladen
		}
		else {
			// Bolantium in der Nähe? dann einsammeln
		}
	}
	else if(unit->getUnitType() == "BUILDERLIGTHUNIT")
	{
		//wenn einheit drumherum die verwundet, repariere
	}
	else if(unit->getUnitType() == ("WATERUNIT" || "AIRUNIT" || "LIGHTUNIT" || "MEDIUMUNIT" || "HEAVYUNIT"))
	{
		//suche gegner den er besiegen kann
	}
	else if(unit->getUnitType() == "DEPOTUNIT")
	{
		//wenn einheit drinnen, repariere
	}
	else if(unit->getUnitType() == "FACTORYUNIT")
	{
		// guck wv boltanimu da ist, dann produziere teuerste einheit else return;
	}
	else
	{
		return;
	}
}
*/
void KI::fillKiMyUnits_Cache()
{
    for (unsigned int i = 0; i < kiMyMatchfield.size(); i++)
	{
        for (unsigned int j = 0; j < kiMyMatchfield[i].size(); j++)
		{
			if (kiMyMatchfield[i][j]->getUnitStationed() != nullptr)
			{
				if (kiMyMatchfield[i][j]->getUnitStationed()->getUnitPlayer()->getPlayerID() == kiPlayer->getPlayerID())
				{
                    kiMyUnits.insert(kiMyMatchfield[i][j]);
                    qDebug() << kiMyUnits.size() << "my unit";
				}
				else
				{
                    kiTargetCache.insert(kiMyMatchfield[i][j]);
				}
			}
		}
	}
}

void KI::delKiMyUnits_Cache()
{
	kiTargetCache.clear();
	kiMyUnits.clear();
}

/*bool KI::isHexInCache(HexagonMatchfield* hex, std::vector<HexagonMatchfield*> cache)
{
    for(auto it: cache)
    {
        if(it->getQpoint_gridPosition() == hex->getQpoint_gridPosition())
            return true;
    }
    return false;
}*/

void KI::moveUnit(HexagonMatchfield* it, HexagonMatchfield* hex, int size)
{
    kiGame->Dijkstra(hex, size);
    if(kiGame->getTargetCache().size() == 0)
        return;
    HexagonMatchfield* tmpCameFrom = kiGame->getCamefrom_Hex(it);
    int tmpCurrenCost = kiGame->getCurrentCost_Int(tmpCameFrom);
    while (tmpCurrenCost > hex->getUnitStationed()->getUnitCurrentMoveRange() || tmpCameFrom->getUnitStationed()!=nullptr)
    {
        tmpCameFrom = kiGame->getCamefrom_Hex(tmpCameFrom);
        tmpCurrenCost = kiGame->getCurrentCost_Int(tmpCameFrom);
    }
    kiGame->moveUnitTo(tmpCameFrom);
}

void KI::unitMoveRandom(HexagonMatchfield * hex)
{
    kiGame->Dijkstra(hex);
    std::unordered_set<HexagonMatchfield*>tmp= kiGame->getTargetCache();
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    if(tmp.size() == 0)
        return;
    int moveRand = qrand() % tmp.size();
    int i = 0;
    for(auto it : tmp){
        if(i >= moveRand)
        {
            if(it->getUnitStationed()!= nullptr)
                unitMoveRandom(hex);
            else
            {
                kiGame->moveUnitTo(it);
                return;
            }
        }
        i++;
    }

}

HexagonMatchfield *KI::calcActionRange(std::unordered_set<HexagonMatchfield *> cache, HexagonMatchfield* target, int range)
{
    for(auto it: cache)
    {
        kiGame->calculateTargets(it, range);
        for(auto tmp : kiGame->getTargetCache())
        {
            if(target->getQpoint_gridPosition() == tmp->getQpoint_gridPosition())
                return it;
        }
    }
    return nullptr;
}

std::unordered_set<HexagonMatchfield*> KI::goodHexCache(std::unordered_set<HexagonMatchfield*> cache1)
{
    for(auto it : kiTargetCache)
    {
        kiGame->Dijkstra(it);
        int tmpRange = it->getUnitStationed()->getActionRange();
        for(auto evil : kiGame->getTargetCache())
        {
            kiGame->calculateTargets(evil, tmpRange);
            for(auto danger : kiGame->getTargetCache())
            {
                if(cache1.find (danger) != cache1.end())
                    cache1.erase(danger);
            }
        }
    }
    return cache1;
}

void KI::checkHQinDanger()
{
	for (auto target : kiTargetCache)
	{
		int tmpRange = target->getUnitStationed()->getActionRange();
		kiGame->Dijkstra(target,2);
        std::unordered_set<HexagonMatchfield*> tmpCacheEvil;
        if(!tmpCacheEvil.empty())
            tmpCacheEvil.clear();
        tmpCacheEvil = kiGame->getTargetCache();
		for (auto evil : tmpCacheEvil)
		{
			kiGame->calculateTargets(evil, tmpRange);
            std::unordered_set<HexagonMatchfield*> tmpCacheRange = kiGame->getTargetCache();
			for (auto tmpIT : tmpCacheRange)
			{
                if (tmpIT->getQpoint_gridPosition() == kiMyHq->getQpoint_gridPosition())
                {
                        prioCache.insert(target);
                }
			}
				
		}
	}
    if (!prioCache.empty())
	{
		kiHq_danger = true;
        qDebug() << prioCache.size();
	}
	else
	{
		kiHq_danger = false;
	}
}
