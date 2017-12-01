#ifndef BUTTONMOVE_H
#define BUTTONMOVE_H
#include "button.h"

class ButtonMove : public Button
{
    Q_OBJECT
public:
    ButtonMove(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, STATE state);
signals:
    void clicked(Button *self);
};

#endif // BUTTONMOVE_H
