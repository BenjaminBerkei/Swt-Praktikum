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
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenMove.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Move Button gedrückt.";
    ptr_hexBaseGame->buttonPressedMove();
    emit clicked(this);
}


void ButtonMove::printType()
{
    qDebug() << "ButtonMove";
}

/*ButtonAction*/
ButtonAction::ButtonAction(int sizeX, int sizeY)
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenAction.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonAction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Action Button gedrückt.";
    ptr_hexBaseGame->buttonPressedAction();
    emit clicked(this);
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

void ButtonMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Map Button gedrückt.";
    emit clicked(this);
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

void ButtonInformation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Information Button gedrückt.";
    emit clicked(this);
}

void ButtonInformation::printType()
{
    qDebug() << "ButtonInformation";
}

/*ButtonChangePhase*/
ButtonChangePhase::ButtonChangePhase(int sizeX, int sizeY)
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenChangePhase.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonChangePhase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Change Phase Button gedrückt.";
    ptr_hexBaseGame->buttonPressedChangePhase();
    emit clicked(this);
}

void ButtonChangePhase::printType()
{
    qDebug() << "ButtonChangePhase";
}

/*ButtonMenue*/
ButtonMenue::ButtonMenue(int sizeX, int sizeY)
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenMenue.png"));
    setPixmap(pixmap().scaled(sizeX,sizeY));
}

void ButtonMenue::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Menue Button gedrückt.";
    ptr_hexBaseGame->buttonPressedMenue();
    emit clicked(this);
}

void ButtonMenue::printType()
{
    qDebug() << "ButtonMenue";
}
