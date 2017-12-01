#include "buttonmove.h"

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

void ButtonMove::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, STATE state)
{
}
