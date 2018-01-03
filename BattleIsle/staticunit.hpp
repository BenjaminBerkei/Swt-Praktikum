/////////////////////////////////////////////
// staticunit.hpp // letzte Änderung: 03.01.18 //
// Letzte Editirung: Miguel				   //	
// Version: 0.2						   //	
// -------- Kommentare --------------------//
/* 
*/
/////////////////////////////////////////////

#ifndef STATICUNIT_HPP
#define STATICUNIT_HPP

#include "unit.hpp"
#include "hexagonmatchfield.hpp"
#include "player.hpp"
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
	StaticUnit(QString, Player* = nullptr);
	~StaticUnit();

	int getEnergieStorage() const;	
	bool checkUnitDestroyed();
	int moveTo(HexagonMatchfield*);
};

class HeadquaterUnit : public StaticUnit
{
public:
	HeadquaterUnit(QString, Player* = nullptr);
	~HeadquaterUnit();

	bool action(HexagonMatchfield*);
	Unit* createUnit();
};

class DepotUnit : public StaticUnit
{
public:
	DepotUnit(QString, Player* = nullptr);
	~DepotUnit();

	bool action(HexagonMatchfield*);
	void repairUnit(Unit*);
	Unit* createUnit();
};

class FactoryUnit : public StaticUnit
{
protected:
	QString unitToBuild; 
	std::map<QString, Unit*> production

public:
	FactoryUnit(QString, Player* = nullptr);
	~FactoryUnit();

	QString getUnitToBuild() const;
	void setUnitToBuild(const QString);

	bool action(HexagonMatchfield*);
	void produceUnit(QString);
	Unit* createUnit();
};

#endif