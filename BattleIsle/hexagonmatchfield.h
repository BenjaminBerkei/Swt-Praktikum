/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum 11.12.2017
 * Kommentar: Klassen mit Operationen hinzugefuegt
 * */
#ifndef HEXAGONMATCHFIELD_H
#define HEXAGONMATCHFIELD_H

#include "enumerations.h"
#include "hexagonbase.h"
#include <QDebug>

class HexagonMatchfield : public HexagonBase
{
private:

protected:
    bool bool_hexFogOfWar;
    //Unit* unit_stationed;
    MATCHFIELDSTATE state;
public:
    HexagonMatchfield(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition/*, Unit* = 0*/);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    void changeState(MATCHFIELDSTATE newState);

signals:
    void SIGNAL_clicked(HexagonMatchfield*);
};

/*New Class*/
class WaterHex : HexagonMatchfield
{
private:
    DEPTH depth_state;

public:
    WaterHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, DEPTH depth_init/*, Unit* = 0*/);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

/*New Class*/
class NormalHex : HexagonMatchfield
{
private:
    std::string str_normalHexTyp;

public:
    NormalHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ/*, Unit* = 0*/);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

/*New Class*/
class ForrestHex : HexagonMatchfield
{
private:
    std::string str_forrestHexTyp;

public:
    ForrestHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ/*, Unit* = 0*/);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

/*New Class*/
class MountainHex : HexagonMatchfield
{
private:
    std::string str_mountainHexTyp;

public:
    MountainHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ/*, Unit* = 0*/);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

/*New Class*/
class StreetHex : HexagonMatchfield
{
private:
    std::string str_streetHexTyp;

public:
    StreetHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ/*, Unit* = 0*/);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

/*New Class*/
class BoltaniumHex : HexagonMatchfield
{
private:
    int int_boltaniumCapacity;
    int int_boltaniumCurrentCapacity;

public:
    BoltaniumHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, int int_cap/*, Unit* = 0*/);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};



#endif // HEXAGONMATCHFIELD_H
