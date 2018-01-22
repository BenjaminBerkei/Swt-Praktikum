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
    in >> str_unitType;

    QString buffer; //Aufgrund des Zeilenumbruchs
    buffer = in.readLine();

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

void StaticUnit::serialize(QTextStream &out)
{
    out << str_unitType << " " << unitFile << " " << unitPlayer->getPlayerID() << " "
        << int_unitCurrentHP << "\n";
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
    : FactoryUnit(filepath, true, player)
{
}

HeadquaterUnit::~HeadquaterUnit(){}

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
    return new HeadquaterUnit(unitFile, unitPlayer);
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

bool DepotUnit::action(HexagonMatchfield* hexTarget)
{
    if(bool_unitUsed == true)
    {
        return false;
    }
    if(hexTarget->getUnit_stationed() != nullptr && hexTarget->getUnit_stationed()->getUnitPlayer() == unitPlayer)
    {
        repairUnit(hexTarget->getUnit_stationed());
        bool_unitUsed = true;
        return true;
    }
    return false;
}

void DepotUnit::repairUnit(Unit* unitTarget)
{	
    if(unitTarget->getUnitCurrentHP() < unitTarget->getUnitHP() && unitPlayer->getCurrentEnergieStorage() - (unitTarget->getUnitHP() - unitTarget->getUnitCurrentHP()) > 0)
	{
		unitTarget->setUnitCurrentHP(unitTarget->getUnitHP());
        unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() - (unitTarget->getUnitHP() - unitTarget->getUnitCurrentHP()));
		bool_unitUsed = true;
	}
	return;
}

Unit* DepotUnit::createUnit()
{
    return new DepotUnit(unitFile, unitPlayer);
}

// Factory

FactoryUnit::FactoryUnit(QString filepath, bool bool_loadInventory, Player* player)
	: StaticUnit(filepath, player), unitToBuild("")
{
    if(bool_loadInventory == true)
    {
        production["B.E.N"] = new LightUnit(":/dynamic/dynamicUnit/ben.txt", unitPlayer);
        production["R-1 Demon"] = new LightUnit(":/dynamic/dynamicUnit/r1demon", unitPlayer);
        production["SC-P Merlin"] = new BuildLightUnit(":/dynamic/dynamicUnit/scpmerlin", false, unitPlayer);

        //production["AD-5 Blitz"] = new MediumUnit(":/dynamic/dynamicUnit/ad5blitz", unitPlayer);
        production["T-3 Scorpion"] = new MediumUnit(":/dynamic/dynamicUnit/t3scorpion", unitPlayer);
        production["Lucas"] = new MediumUnit(":/dynamic/dynamicUnit/lucas.txt", unitPlayer);

        production["Mann u. El"] = new HeavyUnit(":/dynamic/dynamicUnit/mannuel.txt", unitPlayer);
        production["T-4 Gladiator"] = new HeavyUnit(":/dynamic/dynamicUnit/t4gladiator", unitPlayer);
        //production["T-7 Crusader"] = new HeavyUnit(":/dynamic/dynamicUnit/t7crusader", unitPlayer);

        production["Kevarn"] = new TransporterGroundUnit(":/dynamic/dynamicUnit/kevarn.txt", unitPlayer);

        production["Der Bolten"] = new AirUnit(":/dynamic/dynamicUnit/derbolten.txt", unitPlayer);
        //production["CAS Firebird"] = new AirUnit(":/dynamic/dynamicUnit/casfirebird", unitPlayer);
        production["XA-7 Raven"] = new AirUnit(":/dynamic/dynamicUnit/xa7raven", unitPlayer);
        production["XF-7 Mosquito"] = new AirUnit(":/dynamic/dynamicUnit/xf7mosquito", unitPlayer);

        production["M.S Miguel"] = new WaterUnit(":/dynamic/dynamicUnit/msmiguel.txt", unitPlayer);
        production["MB-A Buccaneer"] = new WaterUnit(":/dynamic/dynamicUnit/mbabuccaneer", unitPlayer);
        production["W-1 Fortress"] = new WaterUnit(":/dynamic/dynamicUnit/w1fortress", unitPlayer);

        for(auto &it : production)
        {
            connect(it.second->getUnitDisplay(), SIGNAL(unitDispl_clicked(Unit*)), this, SLOT(SLOT_setUnitToBuild(Unit*)));
            vector_unitStorage.push_back(it.second);
        }
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
    if(unitToBuild != "" && unitPlayer->getCurrentEnergieStorage() - production[unitToBuild]->getUnitCost() >= 0
            && hexTarget->getUnit_stationed() == nullptr && production[unitToBuild]->moveTo(hexTarget) != -1)
    {
        produceUnit(hexTarget);
        resetBuildUnloadParameter();
        bool_unitUsed = true;
        return true;
    }
    resetBuildUnloadParameter();
    return false;
}

void FactoryUnit::produceUnit(HexagonMatchfield* hexTarget)
{
    hexTarget->setUnit_stationed(production[unitToBuild]->createUnit());
    unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() - hexTarget->getUnit_stationed()->getUnitCost());
}

Unit* FactoryUnit::createUnit()
{
    return new FactoryUnit(unitFile, true, unitPlayer);
}

void FactoryUnit::resetBuildUnloadParameter()
{
    if(unitToBuild != "")
    {
        production[unitToBuild]->getUnitDisplay()->setColor(Qt::black);
        production[unitToBuild]->getUnitDisplay()->setZValue(0);
        unitToBuild = "";
    }
}

void FactoryUnit::SLOT_setUnitToBuild(Unit *unit)
{
    resetBuildUnloadParameter();
    unitToBuild = unit->getUnitName();
}

