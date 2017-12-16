/////////////////////////////////////////////
// staticunit.hpp // letzte Änderung: 16.12.17 //
// Letzte Editirung: Arne				   //
// Version: 0.1							   //
// -------- Kommentare --------------------//
/*
*/
/////////////////////////////////////////////

#include "dynamicunit.hpp"

//DynamicUnit

DynamicUnit::DynamicUnit(	string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: Unit(name, pl, view, hp, details, cost, used), int_unitAutoRep(autoRep), int_unitMoveRange(moveRange), int_unitEXP(0), int_unitAirAtt(airAtt), int_unitAirRange(airRange), int_unitGroundAtt(groundAtt), int_unitGroundRange(groundRange), int_unitWaterAtt(waterAtt), int_unitWaterRange(waterRange), int_unitLevel(1){}

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
int DynamicUnit::getUnitAirRange(){
		return int_unitAirRange;
}
int DynamicUnit::getUnitGroundAtt(){
		return int_unitGroundAtt;
}
int DynamicUnit::getUnitGroundRange(){
		return int_unitGroundRange;
}
int DynamicUnit::getUnitWaterAtt(){
		return int_unitWaterAtt;
}
int DynamicUnit::getUnitWaterRange(){
		return int_unitWaterRange;
}
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
void DynamicUnit::setUnitAirRange(const int newUnitAirRange)
{
	int_unitAirRange = newUnitAirRange;
	return;
}
void DynamicUnit::setUnitGroundAtt(const int newUnitGroundAtt)
{
	int_unitGroundAtt = newUnitGroundAtt;
	return;
}
void DynamicUnit::setUnitGroundRange(const int newUnitGroundRange)
{
	int_unitGroundRange = newUnitGroundRange;
	return;
}
void DynamicUnit::setUnitWaterAtt(const int newUnitWaterAtt)
{
	int_unitWaterAtt = newUnitWaterAtt;
	return;
}
void DynamicUnit::setUnitWaterRange(const int newUnitWaterRange)
{
	int_unitWaterRange = newUnitWaterRange;
	return;
}



// AirUnit

AirUnit::AirUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: DynamicUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

AirUnit::~AirUnit(){}

// TransporterAirUnit

TransporterAirUnit::TransporterAirUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange, int capacity, int currentCapacity)
	: AirUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange), int_transporterUnitCapacity(capacity), int_transporterUnitCurrentCapacity(currentCapacity) {}

TransporterAirUnit::~TransporterAirUnit(){}

int TransporterAirUnit::getTransporterUnitCapacity(){
		return int_transporterUnitCapacity;
}
int TransporterAirUnit::getTransporterUnitCurrentCapacity(){
		return int_transporterUnitCurrentCapacity;
}
void TransporterAirUnit::setTransporterUnitCurrentCapacity(const int newCurrentCapacity)
{
	int_transporterUnitCurrentCapacity = newCurrentCapacity;
	return;
}



// GroundUnit

GroundUnit::GroundUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: DynamicUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

GroundUnit::~GroundUnit(){}

// TransporterGroundUnit

TransporterGroundUnit::TransporterGroundUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange, int capacity, int currentCapacity)
	: WaterUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange), int_transporterUnitCapacity(capacity), int_transporterUnitCurrentCapacity(currentCapacity) {}

TransporterGroundUnit::~TransporterGroundUnit(){}

int TransporterGroundUnit::getTransporterUnitCapacity(){
		return int_transporterUnitCapacity;
}
int TransporterGroundUnit::getTransporterUnitCurrentCapacity(){
		return int_transporterUnitCurrentCapacity;
}
void TransporterGroundUnit::setTransporterUnitCurrentCapacity(const int newCurrentCapacity)
{
	int_transporterUnitCurrentCapacity = newCurrentCapacity;
	return;
}

// LightUnit

LightUnit::LightUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: GroundUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

LightUnit::~LightUnit(){}

// BuildLightUnit

BuildLightUnit::BuildLightUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: LightUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

BuildLightUnit::~BuildLightUnit(){}

// MediumUnit

MediumUnit::MediumUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: GroundUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

MediumUnit::~MediumUnit(){}

// HeavyUnit

HeavyUnit::HeavyUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: GroundUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

HeavyUnit::~HeavyUnit(){}



// WaterUnit

WaterUnit::WaterUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange)
	: DynamicUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange){}

WaterUnit::~WaterUnit(){}

// TransporterWaterUnit

TransporterWaterUnit::TransporterWaterUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int autoRep, int moveRange, int airAtt, int groundAtt, int waterAtt, int airRange, int groundRange, int waterRange, int capacity, int currentCapacity)
	: WaterUnit(name, pl, view, hp, details, cost, used, autoRep, moveRange, airAtt, groundAtt, waterAtt, airRange, groundRange, waterRange), int_transporterUnitCapacity(capacity), int_transporterUnitCurrentCapacity(currentCapacity) {}

TransporterWaterUnit::~TransporterWaterUnit(){}

int TransporterWaterUnit::getTransporterUnitCapacity(){
		return int_transporterUnitCapacity;
}
int TransporterWaterUnit::getTransporterUnitCurrentCapacity(){
		return int_transporterUnitCurrentCapacity;
}
void TransporterWaterUnit::setTransporterUnitCurrentCapacity(const int newCurrentCapacity)
{
	int_transporterUnitCurrentCapacity = newCurrentCapacity;
	return;
}
