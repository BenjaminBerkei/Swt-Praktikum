/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 * */

#ifndef HEXAGONBASE_H
#define HEXAGONBASE_H

#include<QGraphicsObject>
#include<QPainter>
#include<cmath>
#include <QDebug>

class HexagonBase : public QGraphicsObject
{
    Q_OBJECT
protected:
    QPoint qpoint_gridPosition; //Position im Grid
    QPolygon hexShape;     //Form des Feldes
public:
    HexagonBase(QPoint qpoint_center, int int_size, QPoint qpoint_position);

    QRectF boundingRect() const;
    QPolygon calculateShape(QPoint qpoint_center, int int_size);    //Berechnung der Ecken des Feldes

    /*Müssen in Subclassen ausgeprägt werden*/
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;
};

#endif // HEXAGONBASE_H
