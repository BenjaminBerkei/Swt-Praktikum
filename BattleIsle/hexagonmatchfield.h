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
#include <QDebug>

class Unit;
class Game;
class HexagonDisplayInfo;

class HexagonMatchfield : public HexagonBase
{
private:

protected:
    bool bool_hexFogOfWar;
    Unit* unit_stationed;
    MATCHFIELDSTATE state;
    HexagonDisplayInfo* ptr_hexMfieldDisplay;
    std::string HexMatchfieldType;
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

public:
    HexagonMatchfield(QPoint qpoint_gridPosition, std::string type, Unit* stationedUnit= 0, Game* ptr_game = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void changeState(MATCHFIELDSTATE newState);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


    //get und set Methoden
    std::string getHexMatchfieldType() {return HexMatchfieldType;}
    MATCHFIELDSTATE getState() const;
    HexagonDisplayInfo *getPtr_hexMfieldDisplay() const;
    void setState(const MATCHFIELDSTATE &value);

signals:
    void SIGNAL_clicked(HexagonMatchfield*);
};

#endif // HEXAGONMATCHFIELD_H
