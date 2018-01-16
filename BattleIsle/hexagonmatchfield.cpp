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
 *
 * Author: Lucas, Manuel
 * Version: 0.5
 * Datum: 13.01.2018
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
    {
        setZValue(0);
        qcolor_HexColor = Qt::black;
    }
    else if(state == TARGET)
    {
        setZValue(1);
        qcolor_HexColor = Qt::yellow;
    }
    else if(state == ACTIVE)
    {
        qDebug() << "\t Active set";
        setZValue(2);
        qcolor_HexColor = Qt::red;
    }
    else if(state == PATH)
    {
        setZValue(2);
        qcolor_HexColor = Qt::green;
    }
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

QColor HexagonMatchfield::getQcolor_HexColor() const
{
    return qcolor_HexColor;
}

bool HexagonMatchfield::getHexFogOfWar() const
{
    return bool_hexFogOfWar;
}

void HexagonMatchfield::setHexFogOfWar(bool value)
{
    bool_hexFogOfWar = value;
    if(unit_stationed != nullptr)
    {
        qreal zValue = 0;
        if(bool_hexFogOfWar == true)
        {
            zValue = -1;
        }else{
            zValue = 5;
        }
        unit_stationed->setZValue(zValue);
    }
}

HexagonMatchfield::HexagonMatchfield(QPoint qpoint_gridPosition, QString type, Unit *stationedUnit) :
    HexagonBase( qpoint_gridPosition ), bool_hexFogOfWar(false), unit_stationed(stationedUnit), state(INACTIVE),
    HexMatchfieldType(type),int_boltaniumCurrent(0), qcolor_HexColor(Qt::black)
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

    if(int_boltaniumCurrent > 0)
    {
        qpixmap_boltanium.load(":/img/Boltanium/Boltanium_high.png");
        qpixmap_boltanium = qpixmap_boltanium.scaled(64,64);
    }

    ptr_hexMfieldDisplay = new HexagonDisplayInfo(this);
}

void HexagonMatchfield::mousePressEvent( QGraphicsSceneMouseEvent *)
{
    //Hier muss evetntuell noch was hin.
    emit SIGNAL_clicked( this );
}

void HexagonMatchfield::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsPixmapItem::paint(painter, option, widget);

    QPen pen;
    pen.setColor(qcolor_HexColor);
    pen.setWidth(2);
    painter->setPen(pen);

    painter->drawPath(shape());

    if(int_boltaniumCurrent > 0)
    {
        painter->drawPixmap(0,0,qpixmap_boltanium);
    }
    if(bool_hexFogOfWar)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::black);

        painter->setOpacity(.5);
        painter->setBrush(brush);

        painter->drawPath(shape());
    }
}

int HexagonMatchfield::getBoltaniumCurrent() const{
    return int_boltaniumCurrent;
}
 
void HexagonMatchfield::setBoltaniumCurrent(int value){
    int_boltaniumCurrent = value;
}
