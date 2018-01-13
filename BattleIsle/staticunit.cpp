/*
 * Author: Miguel
 * Version: 0.2
 * Datum 03.01.2018
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
    unitPlayer = player;
}

StaticUnit::~StaticUnit(){}

int StaticUnit::getEnergieStorage() const
{
	return int_EnergieStorage;
}

bool StaticUnit::checkUnitDestroyed() 
{
	return int_unitCurrentHP <= 0 ? true : false;
}

int StaticUnit::moveTo(HexagonMatchfield* )
{
	return -1;
}

// HQ

HeadquaterUnit::HeadquaterUnit(QString filepath, Player* player)
	: StaticUnit(filepath, player){}

HeadquaterUnit::~HeadquaterUnit(){}

bool HeadquaterUnit::action(HexagonMatchfield* )
{
	return true;
}

Unit* HeadquaterUnit::createUnit()
{
	return new HeadquaterUnit(unitFile);
}

// Depot

DepotUnit::DepotUnit(QString filepath, Player* player)
	: StaticUnit(filepath, player) {}

DepotUnit::~DepotUnit() {}

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
    production["DerBolten"] = new AirUnit(":/dynamic/dynamicUnit/derbolten.txt");
    production["BEN"] = new LightUnit(":/dynamic/dynamicUnit/ben.txt");
    production["KevArn"] = new TransporterGroundUnit(":/dynamic/dynamicUnit/kevarn.txt");
    production["Lucas"] = new MediumUnit(":/dynamic/dynamicUnit/lucas.txt");
    production["MannuEl"] = new HeavyUnit(":/dynamic/dynamicUnit/mannuel.txt");
    production["MSMiguel"] = new WaterUnit(":/dynamic/dynamicUnit/msmiguel.txt");
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
    if(hexTarget->getUnit_stationed() == nullptr)
	{
		if(unitToBuild != "")
		{
			if (production[unitToBuild]->moveTo(hexTarget) != -1)
			{
				produceUnit(hexTarget);
				bool_unitUsed = true;
				unitToBuild = "";
				return true;
			}
		}
	}
	unitToBuild = "";
	return false;
}

void FactoryUnit::produceUnit(HexagonMatchfield*)
{
    /*
    hexTarget->getUnit_stationed() = production[getUnitToBuild()]->createUnit();
    hexTarget->getUnit_stationed()->setUnitPlayer(this->unitPlayer);
    hexTarget->getUnit_stationed()->setQpoint_gridPosition(hexTarget->getQpoint_gridPosition());
	unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() - hexTarget->getUnitCost());
    */
    qDebug() << "Produce Unit";
}

Unit* FactoryUnit::createUnit()
{
	return new FactoryUnit(unitFile);
}

