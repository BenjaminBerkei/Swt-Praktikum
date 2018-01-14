/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 *
 * Author: Manuel
 * version: 0.2
 * Datum: 12.01.2018
 * Kommentar: Buttons angepasst
 *
 * Author: Lucas
 * version: 0.3
 * Datum: 14.01.2018
 * Kommentar: Buttons angepasst
 * */

#include "button.h"
/*Base Class: Button*/
Button::Button()
    : HexagonBase( QPoint(0,0) ), state(DISABLED)
{
}

void Button::changeState(BUTTONSTATE newState)
{
    state = newState;
}

/*ButtonMove*/
ButtonMove::ButtonMove(int sizeX, int sizeY)
{
    QPixmap pix(":/buttonRess/Buttons/MoveMit.png");
    setPixmap(pix.scaled(sizeX,sizeY));
}

void ButtonMove::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}


void ButtonMove::printType()
{
    qDebug() << "ButtonMove";
}

/*ButtonAction*/
ButtonAction::ButtonAction(int sizeX, int sizeY)
{
    QPixmap pix(":/buttonRess/Buttons/AttackeMit.png");
    setPixmap(pix.scaled(sizeX,sizeY));
}

void ButtonAction::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void ButtonAction::printType()
{
    qDebug() << "ButtonAction";
}

/*ButtonMap*/
ButtonMap::ButtonMap(int , int )
{
    //Noch implementieren
    //QPixmap(""));
    //setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonMap::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Meldung: Map Button gedrückt.";
    emit clicked();
}

void ButtonMap::printType()
{
    qDebug() << "ButtonMap";
}

/*ButtonInformation*/
ButtonInformation::ButtonInformation(int , int )
{
    //Noch implemetieren
    //QPixmap(""));
    //setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonInformation::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Meldung: Information Button gedrückt.";
    emit clicked();
}

void ButtonInformation::printType()
{
    qDebug() << "ButtonInformation";
}

/*ButtonChangePhase*/
ButtonChangePhase::ButtonChangePhase(int sizeX, int sizeY)
{
    QPixmap pix(":/buttonRess/Buttons/PhasenwechselMit.png");
    setPixmap(pix.scaled(sizeX,sizeY));
}

void ButtonChangePhase::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    emit clicked();
}

void ButtonChangePhase::printType()
{
    qDebug() << "ButtonChangePhase";
}

/*ButtonMenue*/
ButtonMenue::ButtonMenue(int sizeX, int sizeY)
{
    QPixmap pix(":/img/Buttons/hexagonGruenMenue.png");
    setPixmap(pix.scaled(sizeX,sizeY));
}

void ButtonMenue::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Meldung: Menue Button gedrückt.";
    emit clicked();
}

void ButtonMenue::printType()
{
    qDebug() << "ButtonMenue";
}
