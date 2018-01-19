/*
 * Author: Arne
 * Version: 0.2
 * Kommentar: Wer noch irgendwo Static statt Dynamic findet bekommt n Eis von mir, lg Arne
 *
 * Author: Lucas
 * Version: 0.3
 * Datum: 12.01.17
 * Kommentar: Fehlerbehebung
 *
 * Author: Lucas, Manuel
 * Version: 0.4
 * Datum: 13.01.2018
 */
#include "dynamicunit.h"
#include "staticunit.h"
#include <stdlib.h>     // srand 
#include <time.h>       // time 

//DynamicUnit

DynamicUnit::DynamicUnit(QString filepath, Player* player)
    : Unit()
{
    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "Warnung: File nicht gefunden";
        return;
    }
    QTextStream in(&file);
	
    str_unitName = in.readLine();
	in >> int_unitView;
    in >> int_actionRange;
	in >> int_unitHP;
	in >> int_unitStorageMax;
    in >> int_unitCost;
    in >> int_unitMoveRange;
    in >> int_unitAirAtt;
    in >> int_unitWaterAtt;
    in >> int_unitGroundAtt;
    in >> int_unitAutoRep;
	in >> str_unitType;

    QString buffer; //Aufgrund des Zeilenumbruchs
    buffer = in.readLine();
    str_unitDetails = in.readLine();

    QString pixmapPathPlayerOne = in.readLine();
    QString pixmapPathPlayerTwo = in.readLine();

    QPixmap pix;
    if(player == nullptr)
    {
        pix.load(pixmapPathPlayerOne);
    }else if(player->getPlayerID() == 1)
    {
        pix.load(pixmapPathPlayerOne);
    }else if(player->getPlayerID() == 2)
    {
        pix.load(pixmapPathPlayerTwo);
    }

    setPixmap(pix.scaled(64,64));

    int_unitCurrentHP = int_unitHP;
    int_unitCurrentMoveRange = int_unitMoveRange;
    unitFile = filepath;

    setUnitPlayer(player);

    if(int_unitView < int_unitMoveRange)
    {
        int_unitView = int_unitMoveRange;
    }
}

DynamicUnit::~DynamicUnit(){}

int DynamicUnit::getUnitAutoRep() const{
		return int_unitAutoRep;
}

int DynamicUnit::getUnitLevel() const{
		return int_unitLevel;
}

void DynamicUnit::setUnitAutoRep(const int newUnitAutoRep)
{
    int_unitAutoRep = newUnitAutoRep;
	return;
}

void DynamicUnit::autoRepair() {
	if (int_unitCurrentHP + int_unitAutoRep > int_unitHP) {
		int_unitCurrentHP = int_unitHP;
	}

	else {
		int_unitCurrentHP = int_unitCurrentHP + int_unitAutoRep;
	}
}
void DynamicUnit::levelUpBonus() {
	double percentage = (double)int_unitEXP / 100.0;
	int_unitAirAtt = int_unitAirAtt*(1 + percentage);
	int_unitGroundAtt = int_unitGroundAtt*(1 + percentage);
	int_unitWaterAtt = int_unitWaterAtt*(1 + percentage);
	//setze Level alle 3 Kills eins höher
    if (int_unitEXP == 30) {
		int_unitLevel += 1;
        int_unitEXP = 0;
    }
}

void DynamicUnit::resetUnit()
{
    int_unitCurrentMoveRange = int_unitMoveRange;
    bool_unitUsed = false;
    if((int_unitCurrentHP += int_unitAutoRep) > int_unitHP)
    {
        int_unitCurrentHP = int_unitHP;
    }
}


// TransporterUnit

TransporterUnit::TransporterUnit(QString filepath, Player* player)
	: DynamicUnit(filepath, player){}

TransporterUnit::~TransporterUnit(){}

int TransporterUnit::getTransporterUnitCapacity() const{
		return int_transporterUnitCapacity;
}
int TransporterUnit::getTransporterUnitCurrentCapacity() const{
		return int_transporterUnitCurrentCapacity;
}
void TransporterUnit::setTransporterUnitCurrentCapacity(const int newCurrentCapacity)
{
	int_transporterUnitCurrentCapacity = newCurrentCapacity;
	return;
}


bool TransporterUnit::action(HexagonMatchfield* hex_target){
    if(hex_target->getUnit_stationed() == nullptr){
        if(unitToUnload != nullptr && unitToUnload->moveTo(hex_target) != -1)
        {
            unload(hex_target);
            resetBuildUnloadParameter();
            return true;
        }
        else if(hex_target->getBoltaniumCurrent() > 0 ){
			farmBoltanium(hex_target);
			return true;
		}
    }
    resetBuildUnloadParameter();
	return false;
}

void TransporterUnit::unload(HexagonMatchfield* hex_target){
	hex_target->setUnit_stationed(unitToUnload);
    disconnect(unitToUnload->getUnitDisplay(), SIGNAL(unitDispl_clicked(Unit*)), this, SLOT(SLOT_setUnitToUnload(Unit*)));
	
	int i = 0;
    for(auto &x : vector_unitStorage){
		if(unitToUnload == x){
			vector_unitStorage.erase(vector_unitStorage.begin() + i);
			break;
		}
		i++;
	}
}

void TransporterUnit::farmBoltanium(HexagonMatchfield* hex_target){
	if(hex_target->getBoltaniumCurrent() > 10){
		unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() + 10);
		hex_target->setBoltaniumCurrent(hex_target->getBoltaniumCurrent() - 10);
	}
	
	else{
		unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() + hex_target->getBoltaniumCurrent());
		hex_target->setBoltaniumCurrent(0);
    }
}

void TransporterUnit::addUnitToStorage(Unit *unit)
{
    vector_unitStorage.push_back(unit);
    connect(unit->getUnitDisplay(),SIGNAL(unitDispl_clicked(Unit*)),this, SLOT(SLOT_setUnitToUnload(Unit*)));
}

void TransporterUnit::resetBuildUnloadParameter()
{
    qDebug() << "ResetBuidlLoadParamter";
    if(unitToUnload != nullptr)
    {
        for(auto &it : vector_unitStorage)
        {
            it->getUnitDisplay()->setColor(Qt::black);
            it->getUnitDisplay()->setZValue(0);
            unitToUnload = nullptr;
        }
    }
}

void TransporterUnit::SLOT_setUnitToUnload(Unit *unit)
{
    resetBuildUnloadParameter();
    unitToUnload = unit;
}


// TransporterAirUnit

TransporterAirUnit::TransporterAirUnit(QString filepath, Player* player)
    : TransporterUnit(filepath, player){}

TransporterAirUnit::~TransporterAirUnit(){}

int TransporterAirUnit::moveTo(HexagonMatchfield *hex_target){
	//Flugzeug hat selbe Kosten für alles.
    if(hex_target->getUnit_stationed() == nullptr)
    {
        return 1;
    }else if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }
    return -1;
}

TransporterAirUnit *TransporterAirUnit::createUnit()
{
    return new TransporterAirUnit(unitFile, unitPlayer);
}





// TransporterGroundUnit

TransporterGroundUnit::TransporterGroundUnit(QString filepath, Player* player)
    : TransporterUnit(filepath, player){}

TransporterGroundUnit::~TransporterGroundUnit(){}

int TransporterGroundUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

    if(hex_target->getUnit_stationed() == nullptr)
    {

        if(hex_type == "grassland"){
            return 1;
        }

        else if(hex_type == "streetStraight"){
            return 1;
        }

        else if(hex_type == "streetCurve"){
            return 1;
        }

        else if(hex_type == "forrest" ){
            return 2;
        }

        else if(hex_type == "mountainTop" ){
            return 2;
        }

        else if(hex_type == "mountainSide"){
            return 2;
        }
    }
    if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER"))
    {
        return 1;
    }

    return -1;
}

TransporterGroundUnit *TransporterGroundUnit::createUnit()
{
    return new TransporterGroundUnit(unitFile, unitPlayer);
}




// TransporterWaterUnit

TransporterWaterUnit::TransporterWaterUnit(QString filepath, Player* player)
    : TransporterUnit(filepath, player){}

TransporterWaterUnit::~TransporterWaterUnit(){}

int TransporterWaterUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();
    if(hex_target->getUnit_stationed() == nullptr)
    {
        if(hex_type == "waterDeep"){
            return 2;
        }
        else if(hex_type == "waterSeashore"){
            return 1;
        }
    }

    if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }

    return -1;
}

TransporterWaterUnit *TransporterWaterUnit::createUnit()
{
    return new TransporterWaterUnit(unitFile, unitPlayer);
}



// AirUnit

AirUnit::AirUnit(QString filepath, Player* player)
	: DynamicUnit(filepath, player){}

AirUnit::~AirUnit(){}

int AirUnit::moveTo(HexagonMatchfield *hex_target)
{
	//Flugzeug hat selbe Kosten für alles.
    if(hex_target->getUnit_stationed() == nullptr)
    {
        return 1;
    }else if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }
    return -1;
}

bool AirUnit::action(HexagonMatchfield *hex_target) {
    if(bool_unitUsed)
    {
        return false;
    }
    Unit *target = hex_target->getUnit_stationed();
	
    if(target == nullptr)
    {
		return false;
    }

    if(target->getUnitPlayer() == this->getUnitPlayer())
    {
        return false;
    }

	int int_target_current_hp = target->getUnitCurrentHP();
    QString target_type = target->getUnitType();

	/* RNG mit zufälligem Seed für später initalisieren */
	srand(time(NULL));

	int int_unitSpecificAtt = 0;
	bool bool_fights_back = false;

	if(target_type == "LIGHTUNIT" || target_type == "MEDIUMUNIT" || target_type == "HEAVYUNIT"){
		int_unitSpecificAtt = int_unitGroundAtt; bool_fights_back = true;
	}

	else if(target_type == "WATERUNIT"){
		int_unitSpecificAtt = int_unitWaterAtt; bool_fights_back = true;
	}

	else if(target_type == "AIRUNIT"){
		int_unitSpecificAtt = int_unitAirAtt; bool_fights_back = true;
	}

	if(bool_fights_back){

		if (int_target_current_hp - int_unitSpecificAtt <= 0) {
			target->setUnitCurrentHP(0);
			int_unitEXP +=10;
			levelUpBonus();
            bool_unitUsed = true;
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);

			//zurück angreifen mit 50 - 75% unseres Attk. Wertes
			int int_generated_number = (rand() % 26) + 50;
			double db_percentage_value = ((double)int_generated_number) / 100.0;

			int backfire = (int)(target->getUnitAirAtt()*db_percentage_value);
			if(int_unitCurrentHP - backfire <= 0){
				int_unitCurrentHP = 0;
				target->setUnitEXP(target->getUnitEXP() + 10);
				target->levelUpBonus();
                bool_unitUsed = true;
				return true;
			}

			else{
				int_unitCurrentHP -= backfire;
                bool_unitUsed = true;
				return true;
			}

		}
	}

	if(!bool_fights_back){
		if(target_type == "TRANSPORTERAIR"){
			int_unitSpecificAtt = int_unitAirAtt;
		}

		else if(target_type == "TRANSPORTERWATER"){
			int_unitSpecificAtt = int_unitWaterAtt;
		}

		else if(target_type == "TRANSPORTERGROUND"){
			int_unitSpecificAtt = int_unitGroundAtt;
		}

		//Gebäude
		else{
			int_unitSpecificAtt = int_unitGroundAtt;
		}

		if (int_target_current_hp - int_unitSpecificAtt <= 0) {
			target->setUnitCurrentHP(0);
			int_unitEXP +=10;
			levelUpBonus();
            bool_unitUsed = true;
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);
            bool_unitUsed = true;
			return true;
		}
	}
	return false;

}

AirUnit *AirUnit::createUnit()
{
    return new AirUnit(unitFile, unitPlayer);
}

// GroundUnit

GroundUnit::GroundUnit(QString filepath, Player* player)
	: DynamicUnit(filepath, player){}

GroundUnit::~GroundUnit(){}

bool GroundUnit::action(HexagonMatchfield *hex_target) {
    if(bool_unitUsed)
    {
        return false;
    }

    Unit *target = hex_target->getUnit_stationed();
	
	if(target == nullptr){
		return false;
	}

    if(target->getUnitPlayer() == this->getUnitPlayer())
    {
        return false;
    }

	int int_target_current_hp = target->getUnitCurrentHP();
    QString target_type = target->getUnitType();

	/* RNG mit zufälligem Seed für später initalisieren */
	srand(time(NULL));

	int int_unitSpecificAtt = 0;
	bool bool_fights_back = false;

	if(target_type == "LIGHTUNIT" || target_type == "MEDIUMUNIT" || target_type == "HEAVYUNIT"){
		int_unitSpecificAtt = int_unitGroundAtt; bool_fights_back = true;
	}

	else if(target_type == "WATERUNIT"){
		int_unitSpecificAtt = int_unitWaterAtt; bool_fights_back = true;
	}

	else if(target_type == "AIRUNIT"){
		int_unitSpecificAtt = int_unitAirAtt; bool_fights_back = true;
	}

	if(bool_fights_back){

		if (int_target_current_hp - int_unitSpecificAtt <= 0) {
			target->setUnitCurrentHP(0);
			int_unitEXP +=10;
			levelUpBonus();
            bool_unitUsed = true;
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);

			//zurück angreifen mit 50 - 75% unseres Attk. Wertes
			int int_generated_number = (rand() % 26) + 50;
			double db_percentage_value = ((double)int_generated_number) / 100.0;

			int backfire = (int)(target->getUnitGroundAtt()*db_percentage_value);
			if(int_unitCurrentHP - backfire <= 0){
				int_unitCurrentHP = 0;
				target->setUnitEXP(target->getUnitEXP() + 10);
				target->levelUpBonus();
                bool_unitUsed = true;
				return true;
			}

			else{
				int_unitCurrentHP -= backfire;
                bool_unitUsed = true;
				return true;
			}

		}
	}

	if(!bool_fights_back){
		if(target_type == "TRANSPORTERAIR"){
			int_unitSpecificAtt = int_unitAirAtt;
		}

		else if(target_type == "TRANSPORTERWATER"){
			int_unitSpecificAtt = int_unitWaterAtt;
		}

		else if(target_type == "TRANSPORTERGROUND"){
			int_unitSpecificAtt = int_unitGroundAtt;
		}

		//Gebäude
		else{
			int_unitSpecificAtt = int_unitGroundAtt;
		}

		if (int_target_current_hp - int_unitSpecificAtt <= 0) {
			target->setUnitCurrentHP(0);
			int_unitEXP +=10;
			levelUpBonus();
            bool_unitUsed = true;
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);
            bool_unitUsed = true;
			return true;
		}
	}
	return false;

}

// LightUnit

LightUnit::LightUnit(QString filepath, Player* player)
	: GroundUnit(filepath, player){}

LightUnit::~LightUnit(){}

int LightUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();
    if(hex_target->getUnit_stationed() == nullptr)
    {
        if(hex_type == "grassland"){
            return 1;
        }

        else if(hex_type == "streetStraight"){
            return 1;
        }

        else if(hex_type == "streetCurve"){
            return 1;
        }

        else if(hex_type == "forrest" ){
            return 1;
        }

        else if(hex_type == "mountainTop" ){
            return 1;
        }

        else if(hex_type == "mountainSide"){
            return 2;
        }
    }
    if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }

    return -1;
}

LightUnit *LightUnit::createUnit()
{
    return new LightUnit(unitFile, unitPlayer);
}

// BuildLightUnit

BuildLightUnit::BuildLightUnit(QString filepath, Player* player)
    : LightUnit(filepath, player)
{
    production["Depot"] = new DepotUnit(":/static/staticUnit/depot.txt", unitPlayer);
    production["Fabrik"] = new FactoryUnit(":/static/staticUnit/factory.txt", unitPlayer);

    for(auto &it : production)
    {
        connect(it.second->getUnitDisplay(), SIGNAL(unitDispl_clicked(Unit*)), this, SLOT(SLOT_setUnitToBuild(Unit*)));
        vector_unitStorage.push_back(it.second);
    }
}

BuildLightUnit::~BuildLightUnit(){}

bool BuildLightUnit::action(HexagonMatchfield* hexTarget){
	
    if(bool_unitUsed == true)
    {
        return false;
    }
    qDebug() << "Builder Action:";
    qDebug() << "\t" << unitToBuild;
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


void BuildLightUnit::produceUnit(HexagonMatchfield* hexTarget)
{
    hexTarget->setUnit_stationed(production[unitToBuild]->createUnit());
    unitPlayer->setCurrentEnergieStorage(unitPlayer->getCurrentEnergieStorage() - hexTarget->getUnit_stationed()->getUnitCost());
}

BuildLightUnit *BuildLightUnit::createUnit()
{
    return new BuildLightUnit(unitFile, unitPlayer);
}

void BuildLightUnit::resetBuildUnloadParameter()
{
    if(unitToBuild != "")
    {
        production[unitToBuild]->getUnitDisplay()->setColor(Qt::black);
        production[unitToBuild]->getUnitDisplay()->setZValue(0);
        unitToBuild = "";
    }
}

void BuildLightUnit::SLOT_setUnitToBuild(Unit *unit)
{
    resetBuildUnloadParameter();
    unitToBuild = unit->getUnitName();
}


// MediumUnit

MediumUnit::MediumUnit(QString filepath, Player* player)
	: GroundUnit(filepath, player){}

MediumUnit::~MediumUnit(){}

int MediumUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();
    if(hex_target->getUnit_stationed() == nullptr)
    {
        if(hex_type == "grassland"){
            return 1;
        }

        else if(hex_type == "streetStraight"){
            return 1;
        }

        else if(hex_type == "streetCurve"){
            return 1;
        }

        else if(hex_type == "forrest" ){
            return 2;
        }

        else if(hex_type == "mountainTop" ){
            return -1;
        }

        else if(hex_type == "mountainSide"){
            return -1;
        }
    }
    if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }

    return -1;

}

MediumUnit *MediumUnit::createUnit()
{
    return new MediumUnit(unitFile, unitPlayer);
}
// HeavyUnit

HeavyUnit::HeavyUnit(QString filepath, Player* player)
	: GroundUnit(filepath, player){}

HeavyUnit::~HeavyUnit(){}

int HeavyUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();
    if(hex_target->getUnit_stationed() == nullptr)
    {
        if(hex_type == "grassland"){
            return 2;
        }

        else if(hex_type == "streetStraight"){
            return 2;
        }

        else if(hex_type == "streetCurve"){
            return 2;
        }

        else if(hex_type == "forrest" ){
            return -1;
        }

        else if(hex_type == "mountainTop" ){
            return -1;
        }

        else if(hex_type == "mountainSide"){
            return -1;
        }
    }
    if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }
    return -1;
}

HeavyUnit *HeavyUnit::createUnit()
{
    return new HeavyUnit(unitFile, unitPlayer);
}


// WaterUnit

WaterUnit::WaterUnit(QString filepath, Player* player)
	: DynamicUnit(filepath, player){}

WaterUnit::~WaterUnit(){}

int WaterUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();
    if(hex_target->getUnit_stationed() == nullptr)
    {
        if(hex_type == "waterDeep"){
            return 1;
        }
        else if(hex_type == "waterSeashore"){
            return 2;
        }
    }
    if(hex_target->getUnit_stationed() != nullptr
            && hex_target->getUnit_stationed()->getUnitPlayer() == unitPlayer
            && (hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERAIR"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERGROUND"
                || hex_target->getUnit_stationed()->getUnitType() == "TRANSPORTERWATER")){
        return 1;
    }

    return -1;

}

bool WaterUnit::action(HexagonMatchfield *hex_target) {
    if(bool_unitUsed)
    {
        return false;
    }

    Unit *target = hex_target->getUnit_stationed();
	
	if(target == nullptr){
		return false;
	}

    if(target->getUnitPlayer() == this->getUnitPlayer())
    {
        return false;
    }

	int int_target_current_hp = target->getUnitCurrentHP();
    QString target_type = target->getUnitType();

	/* RNG mit zufälligem Seed für später initalisieren */
	srand(time(NULL));

	int int_unitSpecificAtt = 0;
	bool bool_fights_back = false;

	if(target_type == "LIGHTUNIT" || target_type == "MEDIUMUNIT" || target_type == "HEAVYUNIT"){
		int_unitSpecificAtt = int_unitGroundAtt; bool_fights_back = true;
	}

	else if(target_type == "WATERUNIT"){
		int_unitSpecificAtt = int_unitWaterAtt; bool_fights_back = true;
	}

	else if(target_type == "AIRUNIT"){
		int_unitSpecificAtt = int_unitAirAtt; bool_fights_back = true;
	}

	if(bool_fights_back){

		if (int_target_current_hp - int_unitSpecificAtt <= 0) {
			target->setUnitCurrentHP(0);
			int_unitEXP +=10;
			levelUpBonus();
            bool_unitUsed = true;
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);

			//zurück angreifen mit 50 - 75% unseres Attk. Wertes
			int int_generated_number = (rand() % 26) + 50;
			double db_percentage_value = ((double)int_generated_number) / 100.0;

			int backfire = (int)(target->getUnitWaterAtt()*db_percentage_value);
			if(int_unitCurrentHP - backfire <= 0){
				int_unitCurrentHP = 0;
				target->setUnitEXP(target->getUnitEXP() + 10);
				target->levelUpBonus();
                bool_unitUsed = true;
				return true;
			}

			else{
				int_unitCurrentHP -= backfire;
                bool_unitUsed = true;
				return true;
			}

		}
	}

	if(!bool_fights_back){
		if(target_type == "TRANSPORTERAIR"){
			int_unitSpecificAtt = int_unitAirAtt;
		}

		else if(target_type == "TRANSPORTERWATER"){
			int_unitSpecificAtt = int_unitWaterAtt;
		}

		else if(target_type == "TRANSPORTERGROUND"){
			int_unitSpecificAtt = int_unitGroundAtt;
		}

		//Gebäude
		else{
			int_unitSpecificAtt = int_unitGroundAtt;
		}

		if (int_target_current_hp - int_unitSpecificAtt <= 0) {
			target->setUnitCurrentHP(0);
			int_unitEXP +=10;
			levelUpBonus();
            bool_unitUsed = true;
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);
            bool_unitUsed = true;
			return true;
		}
	}
	return false;

}

WaterUnit *WaterUnit::createUnit()
{
    return new WaterUnit(unitFile, unitPlayer);
}
