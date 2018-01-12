/////////////////////////////////////////////
// dynamicunit.cpp // letzte Änderung: 16.12.17 //
// Letzte Editirung: Arne				   //
// Version: 0.2							   //
// -------- Kommentare --------------------//
/* Action Methoden Fehlen noch bei den einzelnen Transportern
*/
/////////////////////////////////////////////

#include "dynamicunit.hpp"

//DynamicUnit

DynamicUnit::DynamicUnit(QString filepath, Player* player = nullptr)
{
    QFile file(filepath);
    QTextStream in(&file);
	
	in >> str_unitName;
	in >> int_unitView;
	in >> int_unitHP;
	in >> int_unitStorageMax;
	in >> str_unitType;
	in >> str_unitDetails;
	
	in >> int_unitMoveRange;
	in >> int_unitAirAtt;
	in >> int_unitGroundAtt;
	in >> int_unitWaterAtt;
	in >> int_unitAutoRep;
	
    int_unitCurrentHP = int_unitHP;
    unitFile = filepath;
    unitPlayer = player;
}

DynamicUnit::~DynamicUnit(){}

int DynamicUnit::getUnitAutoRep(){
		return int_unitAutoRep;
}
int DynamicUnit::getUnitMoveRange(){
		return int_unitMoveRange;
}
int DynamicUnit::getUnitEXP(){
		return int_unitEXP;
}
int DynamicUnit::getUnitAirAtt(){
		return int_unitAirAtt;
}
/*int DynamicUnit::getUnitAirRange(){
		return int_unitAirRange;
}*/
int DynamicUnit::getUnitGroundAtt(){
		return int_unitGroundAtt;
}
/*int DynamicUnit::getUnitGroundRange(){
		return int_unitGroundRange;
}*/
int DynamicUnit::getUnitWaterAtt(){
		return int_unitWaterAtt;
}
/*int DynamicUnit::getUnitWaterRange(){
		return int_unitWaterRange;
}*/
int DynamicUnit::getUnitLevel(){
		return int_unitLevel;
}

void DynamicUnit::setUnitAutoRep(const int newUnitAutoRep)
{
	int_unitAutoRep = newUnitSt;
	return;
}
void DynamicUnit::setUnitMoveRange(const int newUnitMoveRange)
{
	int_unitMoveRange = newUnitMoveRange;
	return;
}
void DynamicUnit::setUnitEXP(const int newUnitEXP)
{
	int_unitEXP = newUnitEXP;
	return;
}
void DynamicUnit::setUnitAirAtt(const int newUnitAirAtt)
{
	int_unitAirAtt = newUnitAirAtt;
	return;
}
/*void DynamicUnit::setUnitAirRange(const int newUnitAirRange)
{
	int_unitAirRange = newUnitAirRange;
	return;
}*/
void DynamicUnit::setUnitGroundAtt(const int newUnitGroundAtt)
{
	int_unitGroundAtt = newUnitGroundAtt;
	return;
}
/*void DynamicUnit::setUnitGroundRange(const int newUnitGroundRange)
{
	int_unitGroundRange = newUnitGroundRange;
	return;
}*/
void DynamicUnit::setUnitWaterAtt(const int newUnitWaterAtt)
{
	int_unitWaterAtt = newUnitWaterAtt;
	return;
}
/*void DynamicUnit::setUnitWaterRange(const int newUnitWaterRange)
{
	int_unitWaterRange = newUnitWaterRange;
	return;
}*/
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

int TransporterUnit::getTransporterUnitCapacity(){
		return int_transporterUnitCapacity;
}
int TransporterUnit::getTransporterUnitCurrentCapacity(){
		return int_transporterUnitCurrentCapacity;
}
void TransporterUnit::setTransporterUnitCurrentCapacity(const int newCurrentCapacity)
{
	int_transporterUnitCurrentCapacity = newCurrentCapacity;
	return;
}

// TransporterAirUnit

TransporterAirUnit::TransporterAirUnit(QString filepath, Player* player = nullptr)
	: AirUnit(filepath, player){}

TransporterAirUnit::~TransporterAirUnit(){}

int TransporterAirUnit::moveTo(HexagonMatchfield *hex_target){
	//Flugzeug hat selbe Kosten für alles.
	return 1;
}



// Hier fehlt noch Action-Funktion //



// TransporterGroundUnit

TransporterGroundUnit::TransporterGroundUnit(QString filepath, Player* player = nullptr)
	: GroundUnit(filepath, player){}

TransporterGroundUnit::~TransporterGroundUnit(){}

int TransporterGroundUnit::moveTo(HexagonMatchfield *hex_target){

	String hex_type = hex_target->getHEXTYPE();

	if(hex_type == "grassland" || hex_type == "streetStraight" || hex_type == "streetCurve"){
		return 1;
	}

	else if(hex_type == "forrest" || hex_type == "mountainTop" || hex_type == "mountainSide"){
		return 2;
	}

	else{
		return -1;
	}

	return -1;

}




// Hier fehlt noch Action-Funktion //




// TransporterWaterUnit

TransporterWaterUnit::TransporterWaterUnit(QString filepath, Player* player = nullptr)
	: WaterUnit(filepath, player){}

TransporterWaterUnit::~TransporterWaterUnit(){}

int TransporterWaterUnit::moveTo(HexagonMatchfield *hex_target){

	String hex_type = hex_target->getHEXTYPE();

	if(hex_type == "grassland" || hex_type == "streetStraight" || hex_type == "streetCurve" || hex_type == "forrest" || hex_type == "mountainTop" || hex_type == "mountainSide"){
		return -1;
	}


	else if(hex_type == "waterDeep") {
		return 2;
	}

	else if(hex_type == "waterSeashore"){
		return 1;
	}

	return -1;

}


// Hier fehlt noch Action-Funktion //







// AirUnit

AirUnit::AirUnit(QString filepath, Player* player = nullptr)
	: DynamicUnit(filepath, player){}

AirUnit::~AirUnit(){}

int AirUnit::moveTo(HexagonMatchfield *hex_target){
	//Flugzeug hat selbe Kosten für alles.
	return 1;
}

bool AirUnit::action(HexagonMatchfield *hex_target) {
	Unit *target = hex_target->getUnitStationed();
	
	if(target == nullptr){
		return false;
	}

	int int_target_current_hp = target->getUnitCurrentHP();
	QString target_type = target->getUNITTYPE();

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
	Unit *target = hex_target->getUnitStationed();
	
	if(target == nullptr){
		return false;
	}

	int int_target_current_hp = target->getUnitCurrentHP();
	QString target_type = target->getUNITTYPE();

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

	String hex_type = hex_target->getHEXTYPE();


	if(hex_type == "grassland" || hex_type == "streetStraight" || hex_type == "streetCurve" || hex_type == "forrest" || hex_type == "mountainTop"){
		return 1;
	}

	else if(hex_type == "mountainSide"){
		return 2;
	}

	else{
		return -1;
	}

	return -1;

}

// BuildLightUnit

BuildLightUnit::BuildLightUnit(QString filepath, Player* player = nullptr)
	: LightUnit(filepath, player){}

BuildLightUnit::~BuildLightUnit(){}


// MediumUnit

MediumUnit::MediumUnit(QString filepath, Player* player = nullptr)
	: GroundUnit(filepath, player){}

MediumUnit::~MediumUnit(){}

int MediumUnit::moveTo(HexagonMatchfield *hex_target){

	String hex_type = hex_target->getHEXTYPE();

	if(hex_type == "grassland" || hex_type == "streetStraight" || hex_type == "streetCurve"){
		return 1;
	}

	else if(hex_type == "mountainSide" || hex_type == "forrest" || hex_type == "mountainTop"){
		return 2;
	}

	else{
		return -1;
	}

	return -1;

}

// HeavyUnit

HeavyUnit::HeavyUnit(QString filepath, Player* player = nullptr)
	: GroundUnit(filepath, player){}

HeavyUnit::~HeavyUnit(){}

int HeavyUnit::moveTo(HexagonMatchfield *hex_target){

	String hex_type = hex_target->getHEXTYPE();

	if(hex_type == "grassland" || hex_type == "streetStraight" || hex_type == "streetCurve"){
		return 2;
	}

	else if(hex_type == "forrest" || hex_type == "mountainTop"){
		return 3;
	}

	else if(hex_type == "mountainSide"){
		return 4;
	}

	else{
		return -1;
	}

	return -1;

}



// WaterUnit

WaterUnit::WaterUnit(QString filepath, Player* player = nullptr)
	: DynamicUnit(filepath, player){}

WaterUnit::WaterUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: DynamicUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

WaterUnit::~WaterUnit(){}

int WaterUnit::moveTo(HexagonMatchfield *hex_target){

	String hex_type = hex_target->getHEXTYPE();

	if(hex_type == "grassland" || hex_type == "streetStraight" || hex_type == "streetCurve" || hex_type == "forrest" || hex_type == "mountainTop" || hex_type == "mountainSide"){
		return -1;
	}

	else{
		return 1;
	}

	return -1;

}

bool WaterUnit::action(HexagonMatchfield *hex_target) {
	Unit *target = hex_target->getUnitStationed();
	
	if(target == nullptr){
		return false;
	}

	int int_target_current_hp = target->getUnitCurrentHP();
	QString target_type = target->getUNITTYPE();

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
