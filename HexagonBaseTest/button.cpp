#include "button.h"
/*Base Class: Button*/
Button::Button(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : HexagonBase(qpoint_center, int_size, qpoint_position)
{

}

/*ButtonMove*/
ButtonMove::ButtonMove(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
{

}

void ButtonMove::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
}

void ButtonMove::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);
}

void ButtonMove::printType()
{
    qDebug() << "Button Move";
}

/*ButtonAction*/
ButtonAction::ButtonAction(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : Button(qpoint_center, int_size, qpoint_position)
{

}

void ButtonAction::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked(this);
}

void ButtonAction::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 3);
    painter->setPen(pen);
    painter->drawPolygon(hexShape);
}

void ButtonAction::printType()
{
    qDebug() << "Button Action";
}
