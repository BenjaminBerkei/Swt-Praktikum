#include "button.h"
/*Base Class: Button*/
Button::Button(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : HexagonBase(qpoint_center, int_size, qpoint_position)
{

}
void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);
}

/*ButtonMove*/
ButtonMove::ButtonMove(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
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
ButtonAction::ButtonAction(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
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
ButtonMap::ButtonMap(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
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
ButtonInformation::ButtonInformation(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
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
ButtonChangePhase::ButtonChangePhase(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
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
ButtonMenue::ButtonMenue(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
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
