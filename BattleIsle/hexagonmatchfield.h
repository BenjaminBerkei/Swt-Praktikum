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
    std::string HexMatchfieldType; // im Diagramm TYP_type
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
    HexagonMatchfield(QPoint qpoint_gridPosition, std::string type/*, Unit* = 0*/);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void changeState(MATCHFIELDSTATE newState);

    //get und set Methoden
    std::string getHexMatchfieldType() {return HexMatchfieldType;}

signals:
    void SIGNAL_clicked(HexagonMatchfield*);
};

#endif // HEXAGONMATCHFIELD_H
