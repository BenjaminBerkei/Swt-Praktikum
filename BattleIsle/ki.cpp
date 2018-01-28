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
    updateKiMyBolt();
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

void KI::updateKiMyBolt()
{
    kiMyBoltanium = kiPlayer->getCurrentEnergieStorage();
}

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
        std::this_thread::sleep_for (std::chrono::milliseconds(10*kiMyUnits.size()));
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
    fillKiMyUnits_Cache();
	for (auto it : kiMyUnits)
	{
		autoActionPhase(it);
        std::this_thread::sleep_for (std::chrono::milliseconds(10*kiMyUnits.size()));
	}
	delKiMyUnits_Cache();

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
        if(tmpCache.size() == 0)
            return;
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
                if(itCache->getUnitStationed() == nullptr)
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


void KI::autoActionPhase(HexagonMatchfield* hex)
{
    kiGame->processSelection(hex);
    kiGame->calculateTargets(hex, hex->getUnitStationed()->getActionRange());
    std::unordered_set<HexagonMatchfield*> tmpCache = kiGame->getTargetCache();
    qDebug() << hex->getUnitStationed()->getUnitType();
    if(hex->getUnitStationed()->getUnitType().contains("TRANSPORTER"))
	{
        for(auto it : tmpCache)
        {
            if(it->getBoltaniumCurrent() > 0)
            {
                hex->getUnitStationed()->action(it);
                return;
            }
        }
	}
    else if(hex->getUnitStationed()->getUnitType() == "BUILDERUNIT")
    {
        if(kiTargetFactorys > kiMyFactorys && kiTargetCache.size() >= kiMyUnits.size())
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            if(tmpCache.size() == 0)
                return;
            int moveRand = qrand() % tmpCache.size();
            int i = 0;
            for(auto it : tmpCache)
            {
                if(i >= moveRand)
                {
                    if(it->getUnitStationed()!= nullptr || it->getHexMatchfieldType().contains("street") || it->getHexMatchfieldType().contains("forrest"))
                        return;
                    else
                    {
                        hex->getUnitStationed()->setUnitToBuild("Fabrik");
                        if(kiPlayer->getCurrentEnergieStorage() >= 500)
                        {
                            kiProduceUnit(hex, it);
                            return;
                        }
                        else
                            return;
                    }
                }
                i++;
            }
        }
        else if(kiMapBoltanium > 1000 + 200* kiMyFactorys + 500* kiMyDepots)
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            if(tmpCache.size() == 0)
                return;
            int moveRand = qrand() % tmpCache.size();
            int i = 0;
            for(auto it : tmpCache)
            {
                if(i >= moveRand)
                {
                    if(it->getUnitStationed()!= nullptr || it->getHexMatchfieldType().contains("street" || "forrest"))
                        return;
                    else
                    {
                        hex->getUnitStationed()->setUnitToBuild("Depot");
                        if(kiPlayer->getCurrentEnergieStorage() >= 500)
                        {
                            kiProduceUnit(hex, it);
                            return;
                        }
                        else
                            return;
                    }
                }
                i++;
            }
        }
	}
    else if( hex->getUnitStationed()->getUnitType().contains("FACTORY") || hex->getUnitStationed()->getUnitType().contains("HEADQUATER"))
    {
        if(kiMyBoltanium < 100)
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            if(tmpCache.size() == 0)
                return;
            int moveRand = qrand() % tmpCache.size();
            int i = 0;
            for(auto it : tmpCache)
            {
                if(i >= moveRand)
                {
                    if(it->getUnitStationed()!= nullptr)
                        return;
                    else
                    {
                        hex->getUnitStationed()->setUnitToBuild("Kevarn");
                        kiProduceUnit(hex, it);
                        return;
                    }
                }
                i++;
            }
        }
        else if(kiTargetAir > kiTargetGround && kiTargetAir > kiTargetWater)
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            if(tmpCache.size() == 0)
                return;
            int moveRand = qrand() % tmpCache.size();
            int i = 0;
            for(auto it : tmpCache)
            {
                if(i >= moveRand)
                {
                    if(it->getUnitStationed()!= nullptr)
                        return;
                    else
                    {
                        if(kiPlayer->getCurrentEnergieStorage() >= 200)
                        {
                            hex->getUnitStationed()->setUnitToBuild("Der Bolten");
                            kiProduceUnit(hex, it);
                            return;
                        }
                        else
                            return;
                    }
                }
                i++;
            }
        }
        else if(kiTargetGround > kiTargetAir && kiTargetGround > kiTargetWater)
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            if(tmpCache.size() == 0)
                return;
            int moveRand = qrand() % tmpCache.size();
            int i = 0;
            for(auto it : tmpCache)
            {
                if(i >= moveRand)
                {
                    if(it->getUnitStationed()!= nullptr)
                        return;
                    else
                    {
                        hex->getUnitStationed()->setUnitToBuild("Lucas");
                        kiProduceUnit(hex, it);
                        return;
                    }
                }
                i++;
            }
        }
        else
        {
            QTime time = QTime::currentTime();
            qsrand((uint)time.msec());
            if(tmpCache.size() == 0)
                return;
            int randUnit = qrand() % 14;
            int moveRand = qrand() % tmpCache.size();
            switch(randUnit)
            {
            case 0: hex->getUnitStationed()->setUnitToBuild("B.E.N"); break;
            case 1: hex->getUnitStationed()->setUnitToBuild("R-1 Demon"); break;
            case 2: hex->getUnitStationed()->setUnitToBuild("T-3 Scorpion"); break;
            case 3: hex->getUnitStationed()->setUnitToBuild("Lucas"); break;
            case 4: hex->getUnitStationed()->setUnitToBuild("Mann u. El"); break;
            case 5: hex->getUnitStationed()->setUnitToBuild("T-4 Gladiator"); break;
            case 6: hex->getUnitStationed()->setUnitToBuild("Kevarn"); break;
            case 7: hex->getUnitStationed()->setUnitToBuild("Der Bolten"); break;
            case 8: hex->getUnitStationed()->setUnitToBuild("XA-7 Raven"); break;
            case 9: hex->getUnitStationed()->setUnitToBuild("XF-7 Mosquito"); break;
            case 10: hex->getUnitStationed()->setUnitToBuild("M.S Miguel"); break;
            case 11: hex->getUnitStationed()->setUnitToBuild("MB-A Buccaneer"); break;
            case 12: hex->getUnitStationed()->setUnitToBuild("W-1 Fortress"); break;
            case 13: hex->getUnitStationed()->setUnitToBuild("SC-P Merlin"); break;
            }
            int i = 0;
            for(auto it : tmpCache)
            {
                if(i >= moveRand)
                {
                    if(it->getUnitStationed()!= nullptr)
                        return;
                    else
                    {
                        if(kiPlayer->getCurrentEnergieStorage() >= 100)
                        {
                            if(randUnit >= 10 && randUnit <= 12 && (it->getHexMatchfieldType()!= "waterSeashore" || it->getHexMatchfieldType()!= "waterDeep"))
                                return;
                            kiProduceUnit(hex, it);
                            return;
                        }
                        else
                        {
                            hex->getUnitStationed()->setUnitToBuild("SC-P Merlin");
                            kiProduceUnit(hex, it);
                            return;
                        }
                    }
                }
                i++;
            }
        }

    }
    else if(hex->getUnitStationed()->getUnitType() == "DEPOTUNIT")
    {
        for( auto it : tmpCache)
        {
            if(it->getUnitStationed()!=nullptr)
            {
                if(it->getUnitStationed()->getUnitCurrentHP() < it->getUnitStationed()->getUnitHP())
                {
                    qDebug() << "ich heile!";
                    hex->getUnitStationed()->action(it);
                    return;
                }
            }
        }
    }
    else if(hex->getUnitStationed()->getUnitType() == "WATERUNIT" || hex->getUnitStationed()->getUnitType() == "AIRUNIT" || hex->getUnitStationed()->getUnitType() == "WATERUNIT" ||hex->getUnitStationed()->getUnitType() == "LIGHTUNIT" ||hex->getUnitStationed()->getUnitType() == "MEDIUMUNIT" || hex->getUnitStationed()->getUnitType() == "HEAVYUNIT")
    {
        for( auto it : tmpCache)
        {
            for ( auto danger : prioCache)
            {
                if(it->getQpoint_gridPosition() == danger->getQpoint_gridPosition())
                {
                    hex->getUnitStationed()->action(it);
                    return;
                }
            }
        }
        for( auto it : tmpCache)
        {
            if(it->getQpoint_gridPosition() == kiEnemyHq->getQpoint_gridPosition())
                hex->getUnitStationed()->action(it);
                return;
        }
        for( auto it: tmpCache)
        {
            for(auto target : kiTargetCache)
            {
                if(it->getQpoint_gridPosition() == target->getQpoint_gridPosition())
                {
                    hex->getUnitStationed()->action(it);
                    return;
                }
            }
        }
    }
}

void KI::fillKiMyUnits_Cache()
{
    kiMapBoltanium = 0;
    kiMyFactorys = 0;
    kiMyDepots = 0;
    kiTargetFactorys = 0;
    kiTargetAir = 0;
    kiTargetGround = 0;
    kiTargetWater = 0;
    for (unsigned int i = 0; i < kiMyMatchfield.size(); i++)
	{
        for (unsigned int j = 0; j < kiMyMatchfield[i].size(); j++)
		{
            kiMapBoltanium += kiMyMatchfield[i][j]->getBoltaniumCurrent();
			if (kiMyMatchfield[i][j]->getUnitStationed() != nullptr)
			{
				if (kiMyMatchfield[i][j]->getUnitStationed()->getUnitPlayer()->getPlayerID() == kiPlayer->getPlayerID())
				{
                    kiMyUnits.insert(kiMyMatchfield[i][j]);
                    if (kiMyMatchfield[i][j]->getUnitStationed()->getUnitType().contains("DEPOT"))
                        kiMyDepots++;
                    else if(kiMyMatchfield[i][j]->getUnitStationed()->getUnitType().contains("FACTORY"))
                        kiMyFactorys++;
				}
				else
				{
                    kiTargetCache.insert(kiMyMatchfield[i][j]);
                    if (kiMyMatchfield[i][j]->getUnitStationed()->getUnitType().contains("FACTORY"))
                        kiTargetFactorys++;
                    else if(kiMyMatchfield[i][j]->getUnitStationed()->getUnitType().contains("WATER"))
                        kiTargetWater++;
                    else if(kiMyMatchfield[i][j]->getUnitStationed()->getUnitType().contains("AIR"))
                        kiTargetAir++;
                    else if(kiMyMatchfield[i][j]->getUnitStationed()->getUnitType().contains("GROUND" || "HEAVY" || "MEDIUM" || "LIGHT"))
                        kiTargetGround++;
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

void KI::kiProduceUnit(HexagonMatchfield * hex, HexagonMatchfield * targetHex)
{
    hex->getUnitStationed()->action(targetHex);
    targetHex->getUnitStationed()->setPos(targetHex->pos());   //Position in der Scene setzen
    kiGame->getPtr_gameWidget()->getGameWidGameScene()->addItem(targetHex->getUnitStationed());
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
