/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum 11.12.2017
 * Kommentar: Klassen mit Operationen hinzugefuegt
 *
 * Author: Manuel
 * Version: 0.3
 * Datum: 04.01.2018
 * Kommentar: Geändert nach dem neuen UML Diagramm
 *
 * Author: Manuel
 * Version: 0.4
 * Datum: 08.01.2018
 * */
#ifndef HEXAGONMATCHFIELD_H
#define HEXAGONMATCHFIELD_H

#include "enumerations.h"
#include "hexagonbase.h"
#include "unit.h"
#include "game.h"
#include "gamewidget.h"

#include <QString>

#include <QDebug>

class Unit;
class Game;
class HexagonDisplayInfo;

class HexagonMatchfield : public HexagonBase
{
private:

protected:
    /* Zum setZValue:
     * 0: alle inaktiven Hexagons
     * 1: Targets
     * 2: Selectet
     * 3:
     * 4:
     * 5: Units
     */
    bool bool_hexFogOfWar;
    Unit* unit_stationed;
    MATCHFIELDSTATE state;
    HexagonDisplayInfo* ptr_hexMfieldDisplay;
    QString HexMatchfieldType;
    //Mögliche Typen:
    //"waterDeep"           (Tiefes Meer)
    //"waterSeashore"       (Küste)
    //"forrest"             (Wald)
    //"grassland"           (Wiese)
    //"streetStraight"      (Straße Gerade)
    //"streetCurve"         (Straße mit Kurve)
    //"mountainTop"         (Bergspitze)
    //"mountainSide"        (Bergseite)
    //"boltanium"           (Boltanium)
    int int_boltaniumCurrent;

public:
    HexagonMatchfield(QPoint qpoint_gridPosition, QString type, Unit* stationedUnit= 0, Game* ptr_game = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void changeState(MATCHFIELDSTATE newState);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    //get und set Methoden
    QString getHexMatchfieldType() {return HexMatchfieldType;}
    MATCHFIELDSTATE getState() const;
    HexagonDisplayInfo *getPtr_hexMfieldDisplay() const;
    void setState(const MATCHFIELDSTATE &value);

    Unit *getUnit_stationed() const;
    void setUnit_stationed(Unit *value);
    
    int getBoltaniumCurrent() const;
    void setBoltaniumCurrent(int value);

signals:
    void SIGNAL_clicked(HexagonMatchfield*);
};

#endif // HEXAGONMATCHFIELD_H
