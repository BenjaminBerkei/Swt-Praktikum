/*
 * Author: Miguel
 * Version: 0.2
 * Datum 03.01.2018
 */

#include "staticunit.h"

//StaticUnit

StaticUnit::StaticUnit(QString filepath, Player* player = nullptr)
{
    QFile file(filepath);
    QTextStream in(&file);

	in >> str_unitName;
	in >> int_unitView;
	in >> int_unitHP;
	in >> int_unitStorageMax;
	in >> int_EnergieStorage;
	in >> str_unitType;
	in >> str_unitDetails;

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

int StaticUnit::moveTo(HexagonMatchfield* hexTarget)
{
	return -1;
}

// HQ

HeadquaterUnit::HeadquaterUnit(QString filepath, Player* player = nullptr)
	: StaticUnit(filepath, player){}

HeadquaterUnit::~HeadquaterUnit(){}

bool HeadquaterUnit::action(HexagonMatchfield* hexTarget)
{
	return true;
}

Unit* HeadquaterUnit::createUnit()
{
	return new HeadquaterUnit(unitFile);
}

// Depot

DepotUnit::DepotUnit(QString filepath, Player* player = nullptr)
	: StaticUnit(filepath, player) {}

DepotUnit::~DepotUnit() {}

bool DepotUnit::action(HexagonMatchfield* hexTarget) 
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
/*
FactoryUnit::FactoryUnit(QString filepath, Player* player = nullptr)
	: StaticUnit(filepath, player), unitToBuild("")
{
	production["DerBolten"] = new AirUnit("path");
	production["BEN"] = new LightUnit("path");
	production["KevArn"] = new TransporterGroundUnit("path");
	production["Lucas"] = new MediumUnit("path");
	production["MannuEl"] = new HeavyUnit("path");
	production["MSMiguel"] = new WaterUnit("path");
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
	if(hexTarget->unit_stationed == nullptr)
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

void FactoryUnit::produceUnit(HexagonMatchfield* hexTarget)
{
	hexTarget->unit_stationed = production[getUnitToBuild()]->createUnit();
	hexTarget->unit_stationed->setUnitPlayer(this->unitPlayer);
	hexTarget->unit_stationed->setQpoint_gridPosition(hexTarget->getQpoint_gridPosition());
	unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() - hexTarget->getUnitCost());
}

Unit* FactoryUnit::createUnit()
{
	return new FactoryUnit(unitFile);
}
*/
