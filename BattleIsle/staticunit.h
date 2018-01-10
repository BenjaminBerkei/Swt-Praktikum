/*
 * Author: Miguel
 * Version: 0.2
 * Datum 03.01.2018
 */


#ifndef STATICUNIT_HPP
#define STATICUNIT_HPP

#include "unit.h"
#include "hexagonmatchfield.h"
#include "player.h"
#include <map>
#include <QFile>
#include <QTextStream>
#include <QString> 
#include <QPoint>

class StaticUnit : public Unit
{
protected:
	int int_EnergieStorage;

public:
    StaticUnit(QString, Player*);
	~StaticUnit();

	int getEnergieStorage() const;	
	bool checkUnitDestroyed();
	int moveTo(HexagonMatchfield*);
};

class HeadquaterUnit : public StaticUnit
{
public:
    HeadquaterUnit(QString, Player*);
	~HeadquaterUnit();

	bool action(HexagonMatchfield*);
	Unit* createUnit();
};

class DepotUnit : public StaticUnit
{
public:
    DepotUnit(QString, Player*);
	~DepotUnit();

	bool action(HexagonMatchfield*);
	void repairUnit(Unit*);
	Unit* createUnit();
};
/*
class FactoryUnit : public StaticUnit
{
protected:
	QString unitToBuild; 
    std::map<QString, Unit*> production;

public:
    FactoryUnit(QString, Player*);
	~FactoryUnit();

	QString getUnitToBuild() const;
	void setUnitToBuild(const QString);

	bool action(HexagonMatchfield*);
	void produceUnit(HexagonMatchfield*);
	Unit* createUnit();
};
*/
#endif
