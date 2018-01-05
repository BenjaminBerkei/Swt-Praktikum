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

}

void ButtonMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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

}

void ButtonAction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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

}

void ButtonMap::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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

}

void ButtonInformation::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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

}

void ButtonChangePhase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
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

}

void ButtonMenue::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit clicked(this);
}

void ButtonMenue::printType()
{
    qDebug() << "ButtonMenue";
}
