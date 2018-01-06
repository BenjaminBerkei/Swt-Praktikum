/*
 * Author: Miguel
 * Version: 0.1
 * Datum 04.01.2018
 * */

#include "unit.h"

Unit::Unit()
    : str_unitName(""), unitPlayer(nullptr), int_unitView(0), int_unitHP(0), int_unitCurrentHP(0), str_unitDetails(""), str_unitType(""), int_unitCost(0), int_unitStorageMax(0), bool_unitUsed(false), unitFile("") {}

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

int Unit::moveTo(HexagonMatchfield * mf)
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

void Unit::produceUnit(HexagonMatchfield* mf)
{
    return;
}
