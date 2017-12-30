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

#include "hexagonmatchfield.h"

HexagonMatchfield::HexagonMatchfield(QPoint qpoint_gridPosition) : //Unit noch hinzufügen (siehe hpp)
    HexagonBase( qpoint_gridPosition )
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

WaterHex::WaterHex(QPoint qpoint_gridPosition, DEPTH depth_init ) :
    HexagonMatchfield( qpoint_gridPosition ),
    depth_state( depth_init )
{

}

NormalHex::NormalHex(QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_gridPosition ),
    str_normalHexTyp( str_typ )
{

}

ForrestHex::ForrestHex(QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_gridPosition ),
    str_forrestHexTyp( str_typ )
{

}

MountainHex::MountainHex(QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_gridPosition ),
    str_mountainHexTyp( str_typ )
{

}

StreetHex::StreetHex(QPoint qpoint_gridPosition, std::string str_typ) :
    HexagonMatchfield( qpoint_gridPosition ),
    str_streetHexTyp( str_typ )
{

}

BoltaniumHex::BoltaniumHex(QPoint qpoint_gridPosition, int int_cap) :
    HexagonMatchfield( qpoint_gridPosition ),
    int_boltaniumCapacity( int_cap ),
    int_boltaniumCurrentCapacity( int_cap )
{

}
