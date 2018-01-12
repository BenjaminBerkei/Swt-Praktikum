/*
 * Author: Miguel
 * Version: 0.1
 * Datum 04.01.2018
 * */

#include "unit.h"

int Unit::getUnitCurrentMoveRange() const
{
    return int_unitCurrentMoveRange;
}

void Unit::setUnitCurrentMoveRange(int value)
{
    int_unitCurrentMoveRange = value;
}

int Unit::getUnitMoveRange() const
{
    return int_unitMoveRange;
}

void Unit::setUnitMoveRange(int value)
{
    int_unitMoveRange = value;
}

int Unit::getUnitWaterAtt() const
{
    return int_unitWaterAtt;
}

void Unit::setUnitWaterAtt(int value)
{
    int_unitWaterAtt = value;
}

int Unit::getUnitGroundAtt() const
{
    return int_unitGroundAtt;
}

void Unit::setUnitGroundAtt(int value)
{
    int_unitGroundAtt = value;
}

int Unit::getUnitAirAtt() const
{
    return int_unitAirAtt;
}

void Unit::setUnitAirAtt(int value)
{
    int_unitAirAtt = value;
}

Unit::Unit()
    : str_unitName(""), unitPlayer(nullptr), int_unitView(0), int_unitHP(0), int_unitCurrentHP(0),
      str_unitDetails(""), str_unitType(""), int_unitCost(0), int_unitStorageMax(0), bool_unitUsed(false),
      unitFile(""), int_unitAirAtt(0), int_unitGroundAtt(0), int_unitWaterAtt(0), int_unitEXP(0),
      int_unitMoveRange(0), int_unitCurrentMoveRange(0) {}

Unit::~Unit(){}

QString Unit::getUnitName() const
{
	return str_unitName;
}

Player* Unit::getUnitPlayer() const
{
	return unitPlayer;
}

void Unit::setUnitEXP(int value){
	int_unitEXP = value;
}

int Unit::getUnitEXP() const {
	return int_unitEXP;
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

void Unit::setUnitName(QString name)
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

bool Unit::checkUnitDestroyed()
{
    return false;
}

int Unit::moveTo(HexagonMatchfield *)
{
    return -1;
}

void Unit::autoRepair()
{
    return;
}

void Unit::levelUpBonus()
{
    return;
}

void Unit::produceUnit(HexagonMatchfield*)
{
    return;
}

