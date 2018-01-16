/*
 * Author: Miguel
 * Version: 0.2
 * Datum 03.01.2018
 */
/*
 * Author: Lucas
 * Version: 0.3
 * Datum 14.01.2018
 * Kommentar: Chechunitdestroyed von HQ ausgeprägt
 */

#include "staticunit.h"

//StaticUnit

StaticUnit::StaticUnit(QString filepath, Player* player)
    : Unit()
{
    QFile file(filepath);
    QTextStream in(&file);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Warnung: File nicht gefunden";
        return;
    }
    str_unitName = in.readLine();
	in >> int_unitView;
    in >> int_actionRange;
	in >> int_unitHP;
	in >> int_unitStorageMax;
    in >> int_EnergieStorage;
    str_unitType = in.readLine();
    str_unitDetails = in.readLine();

    QString pixmapPathPlayerNeutral = in.readLine();
    QString pixmapPathPlayerOne = in.readLine();
    QString pixmapPathPlayerTwo = in.readLine();

    QPixmap pix;
    if(player == nullptr)
    {
        pix.load(pixmapPathPlayerNeutral);
    }else if(player->getPlayerID() == 1)
    {
        pix.load(pixmapPathPlayerOne);
    }else if(player->getPlayerID() == 2)
    {
        pix.load(pixmapPathPlayerTwo);
    }

    setPixmap(pix.scaled(64,64));

    int_unitCurrentHP = int_unitHP;
    unitFile = filepath;
    setUnitPlayer(player);

    if(int_unitView < int_unitMoveRange)
    {
        int_unitView = int_unitMoveRange;
    }
}

int StaticUnit::getEnergieStorage() const
{
	return int_EnergieStorage;
}

int StaticUnit::moveTo(HexagonMatchfield* )
{
    return 1;
}

// HQ

HeadquaterUnit::HeadquaterUnit(QString filepath, Player* player)
	: StaticUnit(filepath, player){}

HeadquaterUnit::~HeadquaterUnit(){}

bool HeadquaterUnit::action(HexagonMatchfield* )
{
    return true;
}

bool HeadquaterUnit::checkUnitDestroyed()
{
    if(int_unitCurrentHP <= 0)
    {
        unitPlayer->setHQDestroyed(true);
        return true;
    }
    return false;
}

Unit* HeadquaterUnit::createUnit()
{
	return new HeadquaterUnit(unitFile);
}

// Depot

DepotUnit::DepotUnit(QString filepath, Player* player)
    : StaticUnit(filepath, player)
{
    if(player != nullptr)
    {
        player->setPlayerTotalEnergie(player->getPlayerTotalEnergie() + int_EnergieStorage);
    }
}

DepotUnit::~DepotUnit()
{
    for(auto &it : vector_unitStorage)
        delete it;
    unitPlayer->setPlayerTotalEnergie(unitPlayer->getPlayerTotalEnergie() - int_EnergieStorage);
}

bool DepotUnit::action(HexagonMatchfield* )
{
	return true;
}

void DepotUnit::repairUnit(Unit* unitTarget)
{	
	if(unitTarget->getUnitCurrentHP() < unitTarget->getUnitHP())
	{
		unitTarget->setUnitCurrentHP(unitTarget->getUnitHP());
        unitPlayer->setCurrentEnergieStorage(((unitTarget->getUnitCurrentHP() * 100 / unitTarget->getUnitHP()) * unitTarget->getUnitCost()) / 100);
		bool_unitUsed = true;
	}
	return;
}

Unit* DepotUnit::createUnit()
{
	return new DepotUnit(unitFile);
}

// Factory

FactoryUnit::FactoryUnit(QString filepath, Player* player)
	: StaticUnit(filepath, player), unitToBuild("")
{
    production["Der Bolten"] = new AirUnit(":/dynamic/dynamicUnit/derbolten.txt", unitPlayer);
    production["B.E.N"] = new LightUnit(":/dynamic/dynamicUnit/ben.txt", unitPlayer);
    production["Kevarn"] = new TransporterGroundUnit(":/dynamic/dynamicUnit/kevarn.txt", unitPlayer);
    production["Lucas"] = new MediumUnit(":/dynamic/dynamicUnit/lucas.txt", unitPlayer);
    production["Mann u. El"] = new HeavyUnit(":/dynamic/dynamicUnit/mannuel.txt", unitPlayer);
    production["M.S Miguel"] = new WaterUnit(":/dynamic/dynamicUnit/msmiguel.txt", unitPlayer);

    for(auto &it : production)
    {
        connect(it.second->getUnitDisplay(), SIGNAL(unitDispl_clicked(Unit*)), this, SLOT(SLOT_setUnitToBuild(Unit*)));
        vector_unitStorage.push_back(it.second);
    }
}

FactoryUnit::~FactoryUnit() {}

QString FactoryUnit::getUnitToBuild() const
{
	return unitToBuild;
}
void FactoryUnit::setUnitToBuild(const QString unitTarget)
{
	unitToBuild = unitTarget;
	return;
}

bool FactoryUnit::action(HexagonMatchfield* hexTarget)
{
    if(bool_unitUsed == true)
    {
        return false;
    }
    qDebug() << "Factory Action:";
    qDebug() << "\t" << unitToBuild;
    if(unitToBuild != "" && unitPlayer->getCurrentEnergieStorage() - production[unitToBuild]->getUnitCost() >= 0
            && hexTarget->getUnit_stationed() == nullptr && production[unitToBuild]->moveTo(hexTarget) != -1)
    {
        produceUnit(hexTarget);
        unitToBuild = "";
        bool_unitUsed = true;
        return true;
    }
    unitToBuild = "";
    return false;
}

void FactoryUnit::produceUnit(HexagonMatchfield* hexTarget)
{
    hexTarget->setUnit_stationed(production[unitToBuild]->createUnit());
    unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() - hexTarget->getUnit_stationed()->getUnitCost());
}

Unit* FactoryUnit::createUnit()
{
    return new FactoryUnit(unitFile);
}

void FactoryUnit::resetBuildUnloadParameter()
{
    if(unitToBuild != "")
    {
        production[unitToBuild]->setColor(Qt::black);
        production[unitToBuild]->setZValue(0);
        unitToBuild = "";
    }
}

void FactoryUnit::SLOT_setUnitToBuild(Unit *unit)
{
    unitToBuild = unit->getUnitName();
    qDebug() << unitToBuild;
}

