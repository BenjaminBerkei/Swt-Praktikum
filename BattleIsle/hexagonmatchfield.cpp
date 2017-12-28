/*
 * Author: Lucas, Manuel
 * Version: 0.2
 * Datum 08.12.2017
 */
#include "hexagonmatchfield.h"

HexagonMatchfield::HexagonMatchfield( QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition) : //Unit noch hinzufügen (siehe hpp)
    HexagonBase( qpoint_center, int_size, qpoint_gridPosition )
{
    qDebug() << "HexagonMatchfield wurde erstellt";
}

void HexagonMatchfield::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    Q_UNUSED(event);
    //Hier muss evetntuell noch was hin.
    //emit SIGNAL_clicked( this );
}

void HexagonMatchfield::changeState( MATCHFIELDSTATE newState )
{
    state = newState;
    return;
}

WaterHex::WaterHex( QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, DEPTH depth_init ) :
    HexagonMatchfield( qpoint_center, int_size, qpoint_gridPosition ),
    depth_state( depth_init )
{

}

void WaterHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);

}

NormalHex::NormalHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_center, int_size, qpoint_gridPosition ),
    str_normalHexTyp( str_typ )
{

}

void NormalHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);

}

ForrestHex::ForrestHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_center, int_size, qpoint_gridPosition ),
    str_forrestHexTyp( str_typ )
{

}

void ForrestHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);

}

MountainHex::MountainHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_center, int_size, qpoint_gridPosition ),
    str_mountainHexTyp( str_typ )
{

}

void MountainHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);

}

StreetHex::StreetHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_center, int_size, qpoint_gridPosition ),
    str_streetHexTyp( str_typ )
{

}

void StreetHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);

}

BoltaniumHex::BoltaniumHex(QPoint qpoint_center, int int_size, QPoint qpoint_gridPosition, int int_cap) :
    HexagonMatchfield( qpoint_center, int_size, qpoint_gridPosition ),
    int_boltaniumCapacity( int_cap ),
    int_boltaniumCurrentCapacity( int_cap )
{

}

void BoltaniumHex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);

}
