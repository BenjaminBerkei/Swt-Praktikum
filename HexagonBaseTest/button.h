#ifndef BUTTON_H
#define BUTTON_H
#include "hexagonbase.h"
#include <QDebug>
class Button : public HexagonBase
{
    Q_OBJECT
public:
    Button(QPoint qpoint_center, int int_size, QPoint qpoint_position);

    void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
};


/*New Class*/
class ButtonMove : public Button
{
    Q_OBJECT
public:
    ButtonMove(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void printType();
signals:
    void clicked(ButtonMove*);
};


/*New Class*/
class ButtonAction : public Button
{
    Q_OBJECT
public:
    ButtonAction(QPoint qpoint_center, int int_size, QPoint qpoint_position);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void printType();
signals:
    void clicked(ButtonAction*);

};
#endif // BUTTON_H
