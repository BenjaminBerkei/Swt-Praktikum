/////////////////////////////////////////////
// unit.hpp // letzte Änderung: 04.01.18	//
// Letzte Editirung: Miguel				    //	
// Version: 0.1								//	
// -------- Kommentare --------------------//
/*
*/
/////////////////////////////////////////////

#include "unit.hpp"

Unit::Unit()
	: str_unitName(""), unitPlayer(nullptr), int_unitView(0), int_unitHP(0), int_unitCurrentHP(0), str_unitDetails(""), str_unitType(""), int_unitCost(""), int_unitStorageMax(0), bool_unitUsed(false), unitFile("") {}

Unit::~Unit(){}

QString Unit::getUnitName() const
{
	return str_unitName;
}

Player* Unit::getUnitPlayer() const
{
	return unitPlayer;
}

int Unit::getUnitView() const
{
	return int_unitView;
}

int Unit::getUnitHP() const
{
	return int_unitHP;
}

int Unit::getUnitCurrentHP() const
{
	return int_unitCurrentHP;
}

QString Unit::getUnitDetails() const
{
	return str_unitDetails;
}

QString Unit::getUnitType() const
{
	return str_unitType;
}

int Unit::getUnitCost() const
{
	return int_unitCost;
}

bool Unit::getUnitUsed() const
{
	return bool_unitUsed;
}

void Unit::setUnitName(Qstring name)
{
	str_unitName = name;
	return;
}

void Unit::setUnitPlayer(Player* player)
{
	unitPlayer = player;
	return;
}

void Unit::setUnitHP(int hp)
{
	int_unitHP = hp;
	return;
}

void Unit::setUnitCurrentHP(int hp)
{
	int_unitCurrentHP = hp;
	return;
}

void Unit::setUnitUsed(bool used)
{
	bool_unitUsed = used;
	return;
}

virtual Unit* Unit::createUnit()
{
	return new Unit();
}

virtual bool Unit::checkUnitDestroyed()
{
	return int_unitCurrentHP <= 0 ? true : false;
}

virtual int Unit::moveTo(HexagonMatchfield* mf) 
{
	return -1;
}

virtual void Unit::autoRepair() 
{ 
	return; 
}

virtual void Unit::levelUpBonus()
{
	return;
}

virtual void Unit::produceUnit(HexagonMatchfield* mf)
{
	return;
}