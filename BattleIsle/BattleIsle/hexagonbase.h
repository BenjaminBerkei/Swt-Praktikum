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

class HexagonBase : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    QPoint qpoint_gridPosition; //Position im Grid
public:
    HexagonBase(QPoint qpoint_position);

    /*Müssen in Subklassen ausgeprägt werden*/
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
};

#endif // HEXAGONBASE_H
