/////////////////////////////////////////////
// staticunit.hpp // letzte Änderung: 10.12.17 //
// Letzte Editirung: Miguel				   //	
// Version: 0.1							   //	
// -------- Kommentare --------------------//
/*
*/
/////////////////////////////////////////////

#include "staticunit.hpp"

//StaticUnit

StaticUnit::StaticUnit(	string name, Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage) 
	: Unit(name, pl, view, hp, details, cost, used), int_unitStorage(unitStorage), int_unitCurrentStorage(0){}

StaticUnit::~StaticUnit(){}

int StaticUnit::getUnitStorage() const
{
	return int_unitStorage;
}

int StaticUnit::getUnitCurrentStorage() const
{
	return int_unitCurrentStorage;
}

void StaticUnit::setUnitCurrentStorage(const int newUnitSt)
{
	int_unitCurrentStorage = newUnitSt;
	return;
}

// HQ

HeadquaterUnit::HeadquaterUnit(string name,Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage, int energieSt)
	: StaticUnit(name, pl, view, hp, details, cost, used, unitStorage), int_hqEnergieStorage(energieST), int_hqCurrentEnergieStorage(0) {}

HeadquaterUnit::~HeadquaterUnit(){}

int HeadquaterUnit::getHqEnergieStorage() const
{
	return int_hqEnergieStorage;
}

int HeadquaterUnit::getHqCurrentEnergieStorage() const
{
	return int_hqCurrentEnergieStorage;
}

void HeadquaterUnit::setHqCurrentEnergieStorage(const int newEnSt)
{
	int_hqCurrentEnergieStorage = newEnSt;
	return;
}

// Depot

DepotUnit::DepotUnit(string name ,Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage, int energieSt)
	: StaticUnit(name, pl, view, hp, details, cost, used, unitStorage), int_depotEnergieStorage(energieST), int_depotCurrentEnergieStorage(0) {}

DepotUnit::~DepotUnit() {}

int DepotUnit::getDepotEnergieStorage() const
{
	return int_depotEnergieStorage;
}

int DepotUnit::getDepotCurrentEnergieStorage() const
{
	return int_depotCurrentEnergieStorage;
}

void DepotUnit::setDepotCurrentEnergieStorage(const int newEnSt)
{
	int_depotCurrentEnergieStorage = newEnSt;
	return;
}

// Factory

FactoryUnit::FactoryUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage, int energieSt)
	: StaticUnit(name, pl, view, hp, details, cost, used, unitStorage), int_factoryEnergieStorage(energieST), int_factoryCurrentEnergieStorage(0) {}

FactoryUnit::~FactoryUnit() {}

int FactoryUnit::getFactoryEnergieStorage() const
{
	return int_factoryEnergieStorage;
}

int FactoryUnit::getFactoryCurrentEnergieStorage() const
{
	return int_factoryCurrentEnergieStorage;
}

void FactoryUnit::setFactoryCurrentEnergieStorage(const int newEnSt)
{
	int_factoryCurrentEnergieStorage = newEnSt;
	return;
}

GroundFactoryUnit::GroundFactoryUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage, int energieSt)
	: FactoryUnit(name, pl, view, hp, details, cost, used, unitStorage, energieST){}

GroundFactoryUnit::~GroundFactoryUnit() {}

WaterFactoryUnit::WaterFactoryUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage, int energieSt)
	: FactoryUnit(name, pl, view, hp, details, cost, used, unitStorage, energieST) {}

WaterFactoryUnit::~WaterFactoryUnit() {}

AirFactoryUnit::AirFactoryUnit(string name, Player* pl, int view, int hp, string details, int cost, bool used, int unitStorage, int energieSt)
	: FactoryUnit(name, pl, view, hp, details, cost, used, unitStorage, energieST) {}

AirFactoryUnit::~AirFactoryUnit() {}