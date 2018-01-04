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

#include "hexagonmatchfield.h"

HexagonMatchfield::HexagonMatchfield(QPoint qpoint_gridPosition, std::string type) : //Unit noch hinzufügen (siehe hpp)
    HexagonBase( qpoint_gridPosition ),
    HexMatchfieldType(type)
{
    if(HexMatchfieldType == "waterDeep")
        setPixmap(QPixmap(":/images/Meer.png"));
    else if(HexMatchfieldType == "waterSeashore")
        setPixmap(QPixmap(":/images/Kueste.png"));
    else if(HexMatchfieldType == "forrest")
        setPixmap(QPixmap(":/images/Wald.png"));
    else if(HexMatchfieldType == "grassland")
        setPixmap(QPixmap(":/images/Wiese.png"));
    else if(HexMatchfieldType == "streetStraight")
        setPixmap(QPixmap(":/images/Strasse Grade.png"));
    else if(HexMatchfieldType == "streetCurve")
        setPixmap(QPixmap(":/images/Strasse Schraehg.png"));
    else if(HexMatchfieldType == "mountainTop")
        setPixmap(QPixmap(":/images/BergOben.png"));
    else if(HexMatchfieldType == "mountainSide")
        qDebug() << "Warnung: Für Bergseite ist noch kein Bild hinterlegt. (HexagonMatchfield von typ mountainSide erzeugt)";
    else if(HexMatchfieldType == "boltanium")
        qDebug() << "Warnung: Für Boltanium ist noch kein Bild hinterlegt. (HexagonMatchfield von typ boltanium erzeugt)";
    else
    {
        setPixmap(QPixmap(":/images/Wiese.png"));
        qDebug() << "Warnung: Ein HexagonMatchfield ist vom Typ default (siehe switch(HexMatchfieldType) im Konstruktor)";
    }
}

void HexagonMatchfield::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Maus gedrückt.";
    //Hier muss evetntuell noch was hin.
    //emit SIGNAL_clicked( this );
}

void HexagonMatchfield::changeState( MATCHFIELDSTATE newState )
{
    state = newState;
    qDebug() << "Meldung: state vom HexagonMatchfield geändert in " << state;
    return;
}
