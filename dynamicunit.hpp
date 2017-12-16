/////////////////////////////////////////////
// staticunit.hpp // letzte Änderung: 16.12.17 //
// Letzte Editirung: Arne				   //
// Version: 0.1							   //
// -------- Kommentare --------------------//
/*
*/
/////////////////////////////////////////////

#ifndef DYNAMICUNIT_HPP
#define DYNAMICUNIT_HPP


#include "unit.hpp"


class DynamicUnit : public Unit
{
protected:
	int int_unitAutoRep;
  int int_unitMoveRange;
  int int_unitEXP;
  int int_unitAirAtt;
  int int_unitAirRange;
  int int_unitGroundAtt;
  int int_unitGroundRange;
  int int_unitWaterAtt;
  int int_unitWaterRange;
  int int_unitLevel;

public:
	StaticUnit(string, Player*, int, int, int, string, int, bool, int);
	~StaticUnit();

	int getUnitAutoRep() const;
  int getUnitMoveRange() const;
  int getUnitEXP() const;
  int getUnitAirAtt() const;
  int getUnitAirRange() const;
  int getUnitGroundAtt() const;
  int getUnitGroundRange() const;
  int getUnitWaterAtt() const;
  int getUnitWaterRange() const;
  int getUnitLevel() const;

  void setUnitAutoRep(const int);
  void setUnitMoveRange(const int);
  void setUnitEXP(const int);
  void setUnitAirAtt(const int);
  void setUnitAirRange(const int);
  void setUnitGroundAtt(const int);
  void setUnitGroundRange(const int);
  void setUnitWaterAtt(const int);
  void setUnitWaterRange(const int);
  void setUnitLevel(const int);
};

// Air

class AirUnit : public StaticUnit
{
public:
	AirUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~AirUnit();
};

class TransporterAirUnit : public AirUnit
{
private:
	int int_transporterUnitCapacity;
	int int_transporterUnitCurrentCapacity;

public:
	TransporterAirUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int, int, int);
	~TransporterAirUnit();
	int getTransporterUnitCapacity() const;
  int getTransporterUnitCurrentCapacity() const;
  void setTransporterUnitCurrentCapacity(const int);
};

//Ground

class GroundUnit : public StaticUnit
{
public:
	GroundUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~GroundUnit();
};

class LightUnit : public GroundUnit
{
public:
	LightUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~LightUnit();
};

class BuildLightUnit : public LightUnit
{
public:
	BuildLightUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~BuildLightUnit();
};

class MediumUnit : public GroundUnit
{
public:
	MediumUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~MediumUnit();
};

class HeavyUnit : public GroundUnit
{
public:
	HeavyUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~HeavyUnit();
};

class TransporterGroundUnit : public GroundUnit
{
private:
	int int_transporterUnitCapacity;
	int int_transporterUnitCurrentCapacity;

public:
	TransporterGroundUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int, int, int);
	~TransporterGroundUnit();
	int getTransporterUnitCapacity() const;
  int getTransporterUnitCurrentCapacity() const;
  void setTransporterUnitCurrentCapacity(const int);
};

// Water

class WaterUnit : public StaticUnit
{
public:
	WaterUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int);
	~WaterUnit();
};

class TransporterWaterUnit : public WaterUnit
{
private:
	int int_transporterUnitCapacity;
	int int_transporterUnitCurrentCapacity;

public:
	TransporterWaterUnit((string, Player*, int view, int, string, int, bool, int, int, int, int, int, int, int, int, int, int);
	~TransporterWaterUnit();
	int getTransporterUnitCapacity() const;
  int getTransporterUnitCurrentCapacity() const;
  void setTransporterUnitCurrentCapacity(const int);
};

#endif
