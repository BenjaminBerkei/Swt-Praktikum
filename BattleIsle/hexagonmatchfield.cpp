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
 * Author: Lucas
 * Version 0.4
 * Datum: 06.01.2018
 * Kommentar: Skalierung eingeführt
 * */

#include "hexagonmatchfield.h"

MATCHFIELDSTATE HexagonMatchfield::getState() const
{
    return state;
}

void HexagonMatchfield::setState(const MATCHFIELDSTATE &value)
{
    state = value;
    if(state == INACTIVE)
        setZValue(0);
    else if(state == TARGET)
        setZValue(1);
    else if(state == ACTIVE)
        setZValue(2);
}

HexagonDisplayInfo *HexagonMatchfield::getPtr_hexMfieldDisplay() const
{
    return ptr_hexMfieldDisplay;
}

Unit *HexagonMatchfield::getUnit_stationed() const
{
    return unit_stationed;
}

void HexagonMatchfield::setUnit_stationed(Unit *value)
{
    unit_stationed = value;
}

HexagonMatchfield::HexagonMatchfield(QPoint qpoint_gridPosition, QString type, Unit *stationedUnit, Game *ptr_game) :
    HexagonBase( qpoint_gridPosition , ptr_game ),
    unit_stationed(stationedUnit),
    state(INACTIVE),
    HexMatchfieldType(type)
{
    if(HexMatchfieldType == "waterDeep")
        setPixmap(QPixmap(":/img/HexagonBilder/Meer.png"));
    else if(HexMatchfieldType == "waterSeashore")
        setPixmap(QPixmap(":/img/HexagonBilder/Kueste.png"));
    else if(HexMatchfieldType == "forrest")
        setPixmap(QPixmap(":/img/HexagonBilder/Forest.png"));
    else if(HexMatchfieldType == "grassland")
        setPixmap(QPixmap(":/img/HexagonBilder/Grass.png"));
    else if(HexMatchfieldType == "streetStraight")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest.png"));
    else if(HexMatchfieldType == "streetCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest.png"));
    else if(HexMatchfieldType == "mountainTop")
        setPixmap(QPixmap(":/img/HexagonBilder/Mountain.png"));
    else if(HexMatchfieldType == "mountainSide")
        qDebug() << "Warnung: Für Bergseite ist noch kein Bild hinterlegt. (HexagonMatchfield von typ mountainSide erzeugt)";
    else
    {
        setPixmap(QPixmap(":/img/HexagonBilder/Grass.png"));
        qDebug() << "Warnung: Ein HexagonMatchfield ist vom Typ default (siehe switch(HexMatchfieldType) im Konstruktor)";
    }
    //Skalierung kann hier angepasst werden
    setPixmap(pixmap().scaled(64,64));

    ptr_hexMfieldDisplay = new HexagonDisplayInfo(this);
}

void HexagonMatchfield::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    Q_UNUSED(event);
    ptr_hexBaseGame->processSelection(this);


    //Hier muss evetntuell noch was hin.
    //emit SIGNAL_clicked( this );
}

void HexagonMatchfield::changeState( MATCHFIELDSTATE newState )
{
    state = newState;
    qDebug() << "Meldung: state vom HexagonMatchfield geändert in " << state;
    return;
}

void HexagonMatchfield::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);
    QPen pen;
    if(state == ACTIVE)
    {
        pen.setColor(Qt::red);
    }else if(state == TARGET)
    {
        pen.setColor(Qt::yellow);
    }
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawPath(shape());
}

int HexagonMatchfield::getBoltaniumCurrent() const{
    return int_boltaniumCurrent;
}
 
void HexagonMatchfield::setBoltaniumCurrent(int value){
    int_boltaniumCurrent = value;
}
