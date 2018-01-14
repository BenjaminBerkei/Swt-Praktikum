/*
 * Author: Miguel
 * Version: 0.1
 * Datum 03.01.2018
 *
 * Author: Lucas
 * Version: 0.2
 * Datum 14.01.2018
 * Kommentar: Unit destruktor geschrieben, setUnitPlayer() bearbeitet -> erhöht den Unit Count bei dem Spieler der gesetzt wird
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
	
     //von dynamic Unit verschobene Variablen [Auf Grund von Zurückangreifen]
    int int_unitAirAtt;
    int int_unitGroundAtt;
    int int_unitWaterAtt;
    int int_unitEXP;
    
    int int_unitMoveRange;
    int int_unitCurrentMoveRange;
    //int int_actionRange;

public:
	Unit();
    ~Unit();


    //virtual Unit* createUnit() = 0;
    virtual bool checkUnitDestroyed();
    virtual bool action(HexagonMatchfield*) = 0;
    virtual int moveTo(HexagonMatchfield*);
    virtual void autoRepair();
    virtual void levelUpBonus();
    virtual void produceUnit(HexagonMatchfield*);

	QString getUnitName() const;
	Player* getUnitPlayer() const;
	int getUnitView() const;
	int getUnitHP() const;
	int getUnitCurrentHP() const;
	QString getUnitDetails() const;
	QString getUnitType() const;
	int getUnitCost() const;
	bool getUnitUsed() const;

    void setUnitCurrentMoveRange(int value);
    void setUnitName(QString);
	void setUnitPlayer(Player*);
	void setUnitHP(int);
	void setUnitCurrentHP(int);
	void setUnitUsed(bool);

    int getUnitCurrentMoveRange() const;
    int getUnitMoveRange() const;
    void setUnitMoveRange(int value);
    int getUnitWaterAtt() const;
    void setUnitWaterAtt(int value);
    int getUnitGroundAtt() const;
    void setUnitGroundAtt(int value);
    int getUnitAirAtt() const;
    void setUnitAirAtt(int value);
    int getUnitEXP() const;
    void setUnitEXP(const int);
};

#endif
