/////////////////////////////////////////////
// dynamicunit.hpp // letzte Änderung: 10.1.17 //
// Letzte Editirung: Arne				   //
// Version: 0.2						   //
// -------- Kommentare --------------------//
/* Wer noch irgendwo Static statt Dynamic findet bekommt n Eis von mir, lg Arne
*/
/////////////////////////////////////////////
/*
 * Author: Lucas
 * Version: 0.3
 * Datum: 12.01.17
 * Kommentar: Fehlerbehebung
 */
#ifndef DYNAMICUNIT_HPP
#define DYNAMICUNIT_HPP


#include "unit.h"
#include "enumerations.h"
#include "staticunit.h"


class DynamicUnit : public Unit
{
protected:
  int int_unitAutoRep;
  int int_unitMoveRange;
  int int_unitLevel;


public:
DynamicUnit(QString, Player*);
~DynamicUnit();

  int getUnitAutoRep() const;
  int getUnitMoveRange() const;
  int getUnitLevel() const;

  void setUnitAutoRep(const int);
  void setUnitMoveRange(const int);
  void setUnitLevel(const int);
  
  void autoRepair();
  void levelUpBonus();

};



// Air

class AirUnit : public DynamicUnit
{
public:
	AirUnit(QString, Player*);
	~AirUnit();
	
	int moveTo(HexagonMatchfield* );
	bool action(HexagonMatchfield* );
};

// Transporter

class TransporterUnit : public DynamicUnit
{
protected:
	int int_transporterUnitCapacity;
	int int_transporterUnitCurrentCapacity;
    Unit* unitToUnload;
public:
	TransporterUnit(QString, Player*);
	~TransporterUnit();
	int getTransporterUnitCapacity() const;
  	int getTransporterUnitCurrentCapacity() const;
    void setTransporterUnitCurrentCapacity(const int);
    virtual bool action(HexagonMatchfield *hex_target);
    void unload(HexagonMatchfield *hex_target);
    void farmBoltanium(HexagonMatchfield *hex_target);
};

//TransporterAir

class TransporterAirUnit : public TransporterUnit
{
public:
	TransporterAirUnit(QString, Player*);
	~TransporterAirUnit();
  
  int moveTo(HexagonMatchfield* );
};

//TransporterGround

class TransporterGroundUnit : public TransporterUnit
{
public:
	TransporterGroundUnit(QString, Player*);
	~TransporterGroundUnit();

  int moveTo(HexagonMatchfield* );
};

// TransporterWater

class TransporterWaterUnit : public TransporterUnit
{
public:
	TransporterWaterUnit(QString, Player*);
	~TransporterWaterUnit();
  
  int moveTo(HexagonMatchfield* );
};

//Ground

class GroundUnit : public DynamicUnit
{
public:
	GroundUnit(QString, Player*);
	~GroundUnit();
	
	 bool action(HexagonMatchfield* );
};

// Light

class LightUnit : public GroundUnit
{
public:
	LightUnit(QString, Player*);
	~LightUnit();
	
	int moveTo(HexagonMatchfield* );
};

// BuilderLight

class BuildLightUnit : public LightUnit
{
public:
	BuildLightUnit(QString, Player*);
	~BuildLightUnit();
	
    bool action(HexagonMatchfield* );
    void produceUnit(HexagonMatchfield *hex_target);
};

// Medium

class MediumUnit : public GroundUnit
{
public:
	MediumUnit(QString, Player*);
	~MediumUnit();
	
	int moveTo(HexagonMatchfield* );
};

// Heavy

class HeavyUnit : public GroundUnit
{
public:
	HeavyUnit(QString, Player*);
	~HeavyUnit();
	
	int moveTo(HexagonMatchfield* );
};


// Water

class WaterUnit : public DynamicUnit
{
public:
	WaterUnit(QString, Player*);
	~WaterUnit();
	
	int moveTo(HexagonMatchfield* );
    bool action(HexagonMatchfield* );
};

#endif
