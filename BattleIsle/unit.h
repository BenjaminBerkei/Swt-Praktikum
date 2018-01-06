/*
 * Author: Miguel
 * Version: 0.1
 * Datum 03.01.2018
 * */

#ifndef UNIT_HPP
#define UNIT_HPP

#include "hexagonmatchfield.h"
#include "player.h"
#include <map>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString> 
#include <QPoint>

class HexagonMatchfield;
class Player;

class Unit : public QObject, public QGraphicsPixmapItem
{
protected:
	QString str_unitName;
    Player* unitPlayer;
	int int_unitView;
	int int_unitHP;
	int int_unitCurrentHP;
	QString str_unitDetails;
	QString str_unitType;
	int int_unitCost;
    std::vector<Unit*> vector_unitStorage;
	int int_unitStorageMax;
	bool bool_unitUsed;
	QString unitFile;

public:
	Unit();
	~Unit();

	QString getUnitName() const;
	Player* getUnitPlayer() const;
	int getUnitView() const;
	int getUnitHP() const;
	int getUnitCurrentHP() const;
	QString getUnitDetails() const;
	QString getUnitType() const;
	int getUnitCost() const;
	bool getUnitUsed() const;

    void setUnitName(QString);
	void setUnitPlayer(Player*);
	void setUnitHP(int);
	void setUnitCurrentHP(int);
	void setUnitUsed(bool);

    virtual Unit* createUnit() = 0;
	virtual bool checkUnitDestroyed();
	virtual bool action(HexagonMatchfield*) = 0;
	virtual int moveTo(HexagonMatchfield*);
    virtual void autoRepair();
    virtual void levelUpBonus();
    virtual void produceUnit(HexagonMatchfield*);
};

#endif
