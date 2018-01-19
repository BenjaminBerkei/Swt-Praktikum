#ifndef HEXAGON_H
#define HEXAGON_H

#include "mainwindow.h"
#include "unit.h"
#include <QString>
#include <QPixmap>
#include <QWidget>
#include <QGraphicsObject>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <cmath>
#include <QDebug>

class Unit;

class Hexagon : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
protected:
    Unit* unit_stationed;
    QString HexMatchfieldType;
    //Mögliche Typen:
    //"waterDeep"           (Tiefes Meer)
    //"waterSeashore"       (Küste)
    //"forrest"             (Wald)
    //"grassland"           (Wiese)
    //"streetStraight"      (Straße Gerade)
    //"streetCurve"         (Straße mit Kurve)
    //"streetCrossing"      (Straßenkruzung)
    //"mountainTop"         (Bergspitze)
    //"mountainSideStraight"(BergseiteGrade)
    //"mountainSideCurve"   (BergseiteSchräg)
    //"boltanium"           (Boltanium)
    int int_boltaniumCurrent;
    QColor qcolor_HexColor;
    QPixmap qpixmap_boltanium;
    QPoint qpoint_gridPosition;
public:
    Hexagon(QPoint, QString, Unit* stationedUnit= nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //get und set Methoden
    QString getHexMatchfieldType();
    void setHexMatchfieldType(QString);
    QColor getHexColor();
    void setHexColor(QColor);

  Unit *getUnit_stationed() const;
  void setUnit_stationed(Unit *value);

    int getBoltaniumCurrent() const;
    void setBoltaniumCurrent(int);

    QPoint getQpoint_gridPosition() const;

signals:
    void SIGNAL_clicked(Hexagon*);
};

#endif // HEXAGON_H
