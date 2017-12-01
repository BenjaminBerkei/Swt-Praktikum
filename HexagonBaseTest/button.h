#ifndef BUTTON_H
#define BUTTON_H
#include "hexagonbase.h"

class Button : public HexagonBase
{
    Q_OBJECT
public:
    Button(QPoint qpoint_center, int int_size, QPoint qpoint_position);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget, STATE state) = 0;

    /*Test*/
    QPolygon getShape()const;
    /*Test_Ende*/
};

#endif // BUTTON_H
