/////////////////////////////////////////////
// staticunit.hpp // letzte Änderung: 10.12.17 //
// Letzte Editirung: Miguel				   //	
// Version: 0.1							   //	
// -------- Kommentare --------------------//
/* 
*/
/////////////////////////////////////////////

#ifndef STATICUNIT_HPP
#define STATICUNIT_HPP

#include "unit.hpp"

class StaticUnit : public Unit
{
protected:
	int int_unitStorage;
	int int_unitCurrentStorage;

public:
	StaticUnit(string, Player*, int, int, int, string, int, bool, int);
	~StaticUnit();

	int getUnitStorage() const;
	int getUnitCurrentStorage() const;
	void setUnitCurrentStorage(const int);
};

class HeadquaterUnit : public StaticUnit
{
private:
	int int_hqEnergieStorage;
	int int_hqCurrentEnergieStorage;

public:
	HeadquaterUnit(string, Player*, int, int, int, string, int, bool, int, int);
	~HeadquaterUnit();

	int getHqEnergieStorage() const;
	int getHqCurrentEnergieStorage() const;
	void setHqCurrentEnergieStorage(const int);
};

class DepotUnit : public StaticUnit
{
private:
	int int_depotEnergieStorage;
	int int_depotCurrentEnergieStorage;

public:
	DepotUnit(string, Player*, int, int, int, string, int, bool, int, int);
	~DepotUnit();

	int getDepotEnergieStorage() const;
	int getDepotCurrentEnergieStorage() const;
	void setDepotCurrentEnergieStorage(const int);
};

class FactoryUnit : public StaticUnit
{
protected:
	int int_factoryEnergieStorage;
	int int_factoryCurrentEnergieStorage;

public:
	FactoryUnit(string, Player*, int, int, int, string, int, bool, int, int);
	~FactoryUnit();

	int getFactoryEnergieStorage() const;
	int getFactoryCurrentEnergieStorage() const;
	void setFactoryCurrentEnergieStorage(const int);
};

class GroundFactoryUnit : FactoryUnit
{
public:
	GroundFactoryUnit(string, Player*, int, int, int, string, int, bool, int, int);
	~GroundFactoryUnit();
};

class WaterFactoryUnit : FactoryUnit
{
public:
	WaterFactoryUnit(string, Player*, int, int, int, string, int, bool, int, int);
	~WaterFactoryUnit();
};

class AirFactoryUnit : FactoryUnit
{
public:
	AirFactoryUnit(string, Player*, int, int, int, string, int, bool, int, int);
	~AirFactoryUnit();
};

#endif