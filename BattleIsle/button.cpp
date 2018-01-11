/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 * */

#include "button.h"
/*Base Class: Button*/
Button::Button(QPoint qpoint_position)
    : HexagonBase( qpoint_position ), state(DISABLED)
{

}

void Button::changeState(BUTTONSTATE newState)
{
    state = newState;
}

/*ButtonMove*/
ButtonMove::ButtonMove(QPoint qpoint_position)
    : Button( qpoint_position )
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenMove.png"));
    setPixmap(pixmap().scaled(64,64));
    setPos(qpoint_position.x(),qpoint_position.y());
}

void ButtonMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Move Button gedrückt.";
    emit clicked(this);
}


void ButtonMove::printType()
{
    qDebug() << "ButtonMove";
}

/*ButtonAction*/
ButtonAction::ButtonAction(QPoint qpoint_position)
    : Button( qpoint_position )
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenAction.png"));
    setPixmap(pixmap().scaled(64,64));
    setPos(qpoint_position.x(),qpoint_position.y());
}

void ButtonAction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Action Button gedrückt.";
    emit clicked(this);
}

void ButtonAction::printType()
{
    qDebug() << "ButtonAction";
}

/*ButtonMap*/
ButtonMap::ButtonMap(QPoint qpoint_position)
    : Button( qpoint_position )
{
    //Noch implementieren
    //setPixmap(QPixmap(""));
    setPixmap(pixmap().scaled(64,64));
    setPos(qpoint_position.x(),qpoint_position.y());
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
ButtonInformation::ButtonInformation(QPoint qpoint_position)
    : Button(qpoint_position)
{
    //Noch implemetieren
    //setPixmap(QPixmap(""));
    setPixmap(pixmap().scaled(64,64));
    setPos(qpoint_position.x(),qpoint_position.y());
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
ButtonChangePhase::ButtonChangePhase(QPoint qpoint_position)
    : Button(qpoint_position)
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenChangePhase.png"));
    setPixmap(pixmap().scaled(64,64));
    setPos(qpoint_position.x(),qpoint_position.y());
}

void ButtonChangePhase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Change Phase Button gedrückt.";
    emit clicked(this);
}

void ButtonChangePhase::printType()
{
    qDebug() << "ButtonChangePhase";
}

/*ButtonMenue*/
ButtonMenue::ButtonMenue(QPoint qpoint_position)
    : Button(qpoint_position)
{
    setPixmap(QPixmap(":/images/Buttons/hexagonGruenMenue.png"));
    setPixmap(pixmap().scaled(64,64));
    setPos(qpoint_position.x(),qpoint_position.y());
}

void ButtonMenue::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    qDebug() << "Meldung: Menue Button gedrückt.";
    emit clicked(this);
}

void ButtonMenue::printType()
{
    qDebug() << "ButtonMenue";
}
