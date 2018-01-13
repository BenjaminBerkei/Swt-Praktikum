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

DynamicUnit::DynamicUnit(QString filepath, Player* player = nullptr)
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
    QPixmap pix(in.readLine());

    setPixmap(pix.scaled(64,64));

    int_unitCurrentHP = int_unitHP;
    int_unitCurrentMoveRange = int_unitMoveRange;
    unitFile = filepath;
    unitPlayer = player;
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
	if (int_unitEXP % 30 == 0) {
		int_unitLevel += 1;
	}
}


// TransporterUnit

TransporterUnit::TransporterUnit(QString filepath, Player* player = nullptr)
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
		if(hex_target->getBoltaniumCurrent() > 0 ){
			farmBoltanium(hex_target);
			return true;
		}
	}
		   
    if(hex_target->getUnit_stationed() != nullptr){
		unload(hex_target);
		return true;
	}
	
	return false;
}

void TransporterUnit::unload(HexagonMatchfield* hex_target){
	hex_target->setUnit_stationed(unitToUnload);
	
	int i = 0;
	for(Unit *x : vector_unitStorage){
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


// TransporterAirUnit

TransporterAirUnit::TransporterAirUnit(QString filepath, Player* player = nullptr)
    : TransporterUnit(filepath, player){}

TransporterAirUnit::~TransporterAirUnit(){}

int TransporterAirUnit::moveTo(HexagonMatchfield *){
	//Flugzeug hat selbe Kosten für alles.
	return 1;
}





// TransporterGroundUnit

TransporterGroundUnit::TransporterGroundUnit(QString filepath, Player* player = nullptr)
    : TransporterUnit(filepath, player){}

TransporterGroundUnit::~TransporterGroundUnit(){}

int TransporterGroundUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

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

	else if(hex_type == "waterDeep"){
		return -1;
	}

	else if(hex_type == "waterSeashore"){
		return -1;
	}

}




// TransporterWaterUnit

TransporterWaterUnit::TransporterWaterUnit(QString filepath, Player* player = nullptr)
    : TransporterUnit(filepath, player){}

TransporterWaterUnit::~TransporterWaterUnit(){}

int TransporterWaterUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

	if(hex_type == "grassland"){
		return -1;
	}

	else if(hex_type == "streetStraight"){
		return -1;
	}

	else if(hex_type == "streetCurve"){
		return -1;
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

	else if(hex_type == "waterDeep"){
		return 2;
	}

	else if(hex_type == "waterSeashore"){
		return 1;
	}

}



// AirUnit

AirUnit::AirUnit(QString filepath, Player* player = nullptr)
	: DynamicUnit(filepath, player){}

AirUnit::~AirUnit(){}

int AirUnit::moveTo(HexagonMatchfield *hex_target){
	//Flugzeug hat selbe Kosten für alles.
	return 1;
}

bool AirUnit::action(HexagonMatchfield *hex_target) {
    Unit *target = hex_target->getUnit_stationed();
	
	if(target == nullptr){
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
				return true;
			}

			else{
				int_unitCurrentHP -= backfire;
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
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);
			return true;
		}
	}

	return false;

}


// GroundUnit

GroundUnit::GroundUnit(QString filepath, Player* player = nullptr)
	: DynamicUnit(filepath, player){}

GroundUnit::~GroundUnit(){}

bool GroundUnit::action(HexagonMatchfield *hex_target) {
    Unit *target = hex_target->getUnit_stationed();
	
	if(target == nullptr){
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
				return true;
			}

			else{
				int_unitCurrentHP -= backfire;
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
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);
			return true;
		}
	}

	return false;

}

// LightUnit

LightUnit::LightUnit(QString filepath, Player* player = nullptr)
	: GroundUnit(filepath, player){}

LightUnit::~LightUnit(){}

int LightUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

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

	else if(hex_type == "waterDeep"){
		return -1;
	}

	else if(hex_type == "waterSeashore"){
		return -1;
	}

}

// BuildLightUnit

BuildLightUnit::BuildLightUnit(QString filepath, Player* player = nullptr)
	: LightUnit(filepath, player){}

BuildLightUnit::~BuildLightUnit(){}

bool BuildLightUnit::action(HexagonMatchfield* hex_target){
	
	produceUnit(hex_target);
    if(hex_target->getUnit_stationed() != nullptr){
		return true;
	}

	return false;
}


void BuildLightUnit::produceUnit(HexagonMatchfield* hex_target){
	int int_energy = unitPlayer->getCurrentEnergieStorage();
	if(int_energy >= 50){
        hex_target->setUnit_stationed(new DepotUnit(":/static/staticUnit/depot.txt", unitPlayer));
		unitPlayer->setCurrentEnergieStorage(int_energy - 50);
	}
}


// MediumUnit

MediumUnit::MediumUnit(QString filepath, Player* player = nullptr)
	: GroundUnit(filepath, player){}

MediumUnit::~MediumUnit(){}

int MediumUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

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

	else if(hex_type == "waterDeep"){
		return -1;
	}

	else if(hex_type == "waterSeashore"){
		return -1;
	}

}
// HeavyUnit

HeavyUnit::HeavyUnit(QString filepath, Player* player = nullptr)
	: GroundUnit(filepath, player){}

HeavyUnit::~HeavyUnit(){}

int HeavyUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

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
		return 3;
	}

	else if(hex_type == "mountainTop" ){
		return 3;
	}

	else if(hex_type == "mountainSide"){
        return 4;
	}

	else if(hex_type == "waterDeep"){
		return -1;
	}

	else if(hex_type == "waterSeashore"){
		return -1;
	}

}


// WaterUnit

WaterUnit::WaterUnit(QString filepath, Player* player = nullptr)
	: DynamicUnit(filepath, player){}

WaterUnit::~WaterUnit(){}

int WaterUnit::moveTo(HexagonMatchfield *hex_target){

    QString hex_type = hex_target->getHexMatchfieldType();

	if(hex_type == "grassland"){
		return -1;
	}

	else if(hex_type == "streetStraight"){
		return -1;
	}

	else if(hex_type == "streetCurve"){
		return -1;
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

	else if(hex_type == "waterDeep"){
		return 1;
	}

	else if(hex_type == "waterSeashore"){
		return 2;
	}

}

bool WaterUnit::action(HexagonMatchfield *hex_target) {
    Unit *target = hex_target->getUnit_stationed();
	
	if(target == nullptr){
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
				return true;
			}

			else{
				int_unitCurrentHP -= backfire;
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
			return true;
		}

		else {
			target->setUnitCurrentHP(int_target_current_hp - int_unitSpecificAtt);
			return true;
		}
	}

	return false;

}
