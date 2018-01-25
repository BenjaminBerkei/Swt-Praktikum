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
    if(bool_hexFogOfWar != value)
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
        setPixmap(QPixmap(":/img/HexagonBilder/nordsued.png"));
    else if(HexMatchfieldType == "streetStraight60d")
        setPixmap(QPixmap(":/img/HexagonBilder/nordsued60d.png"));
    else if(HexMatchfieldType == "streetStraight120d")
        setPixmap(QPixmap(":/img/HexagonBilder/nordsued120d.png"));

    else if(HexMatchfieldType == "streetCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest.png"));
    else if(HexMatchfieldType == "streetCurve60d")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest60d.png"));
    else if(HexMatchfieldType == "streetCurve120d")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest120d.png"));
    else if(HexMatchfieldType == "streetCurve180d")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest180d.png"));
    else if(HexMatchfieldType == "streetCurve240d")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest240d.png"));
    else if(HexMatchfieldType == "streetCurve300d")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_nordwest300d.png"));

    else if(HexMatchfieldType == "streetCrossing")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_kreuzung.png"));
    else if(HexMatchfieldType == "streetCrossing60d")
        setPixmap(QPixmap(":/img/HexagonBilder/Street_kreuzung60d.png"));

    else if(HexMatchfieldType == "mountainTop")
        setPixmap(QPixmap(":/img/HexagonBilder/Mountain.png"));
    else if(HexMatchfieldType == "mountainSideStraight")
        setPixmap(QPixmap(":/img/HexagonBilder/BergSeiteGrade.png"));
    else if(HexMatchfieldType == "mountainSideCurve")
        setPixmap(QPixmap(":/img/HexagonBilder/BergSeiteSchräg.png"));

    //Skalierung kann hier angepasst werden
    setPixmap(pixmap().scaled(64,64));
    qpixmap_boltanium.load(":/img/Boltanium/Boltanium_high.png");
    qpixmap_boltanium = qpixmap_boltanium.scaled(64,64);

    ptr_hexMfieldDisplay = new HexagonDisplayInfo(this);
}

HexagonMatchfield::~HexagonMatchfield()
{
    delete ptr_hexMfieldDisplay;
}

void HexagonMatchfield::mousePressEvent( QGraphicsSceneMouseEvent *)
{
    if(isActive())
    {
        qDebug() << "Hexagon Aktiv.";
    }
    else
    {
        qDebug() << "Hexagon ist nicht Aktiv. Sende Signal SIGNAL_centerThis";
        emit SIGNAL_centerThis(this);
    }
    if(unit_stationed != nullptr)
    {
        unit_stationed->getUnitDisplay()->updateText();
    }
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

    if(bool_hexFogOfWar)
    {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::black);

        painter->setOpacity(.5);
        painter->setBrush(brush);

        painter->drawPath(shape());
    }else{
        if(int_boltaniumCurrent > 0 )
        {
            painter->drawPixmap(0,0,qpixmap_boltanium);
        }
    }
}

void HexagonMatchfield::serialize(QTextStream &out)
{
    if(int_boltaniumCurrent > 0 || unit_stationed != nullptr)
    {
        out << qpoint_gridPosition.x() << " " << qpoint_gridPosition.y() << " "
            << int_boltaniumCurrent << " ";
        if(unit_stationed != nullptr)
        {
            out << "1";
            out << "\n";
            unit_stationed->serialize(out);
        }else{
            out << "0";
            out << "\n";
        }
    }
}

int HexagonMatchfield::getBoltaniumCurrent() const{
    return int_boltaniumCurrent;
}
 
void HexagonMatchfield::setBoltaniumCurrent(int value){
    int_boltaniumCurrent = value;
}
