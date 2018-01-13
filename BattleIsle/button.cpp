/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 *
 * Author: Manuel
 * version: 0.2
 * Datum: 12.01.2018
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
    setPixmap(QPixmap(":/img/Buttons/hexagonGruenMove.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonMove::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Meldung: Move Button gedrückt.";
    emit clicked();
}


void ButtonMove::printType()
{
    qDebug() << "ButtonMove";
}

/*ButtonAction*/
ButtonAction::ButtonAction(int sizeX, int sizeY)
{
    setPixmap(QPixmap(":/img/Buttons/hexagonGruenAction.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonAction::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Meldung: Action Button gedrückt.";
    emit clicked();
}

void ButtonAction::printType()
{
    qDebug() << "ButtonAction";
}

/*ButtonMap*/
ButtonMap::ButtonMap(int sizeX, int sizeY)
{
    //Noch implementieren
    //setPixmap(QPixmap(""));
    setPixmap(pixmap().scaled(sizeX,sizeY));
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
ButtonInformation::ButtonInformation(int sizeX, int sizeY)
{
    //Noch implemetieren
    //setPixmap(QPixmap(""));
    setPixmap(pixmap().scaled(sizeX,sizeY));
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
    setPixmap(QPixmap(":/img/Buttons/hexagonGruenChangePhase.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonChangePhase::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    qDebug() << "Meldung: Change Phase Button gedrückt.";
    emit clicked();
}

void ButtonChangePhase::printType()
{
    qDebug() << "ButtonChangePhase";
}

/*ButtonMenue*/
ButtonMenue::ButtonMenue(int sizeX, int sizeY)
{
    setPixmap(QPixmap(":/img/Buttons/hexagonGruenMenue.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
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
