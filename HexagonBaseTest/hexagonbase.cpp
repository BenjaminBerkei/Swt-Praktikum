#include "hexagonbase.h"

HexagonBase::HexagonBase(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    :  qpoint_gridPosition(qpoint_position), hexShape(calculateShape(qpoint_center, int_size))
{

}

QRectF HexagonBase::boundingRect() const
{
    return hexShape.boundingRect();
}

QPolygon HexagonBase::calculateShape(QPoint qpoint_center, int int_size)
{
    QPolygon qpolygon_calculatedShape;

    for(int i = 0; i < 6; i++)
    {
        double angle_deg = 60 * i + 30;
        double angle_rad = M_PI / 180 * angle_deg;

        qpolygon_calculatedShape << QPoint(qpoint_center.x() + int_size * cos(angle_rad),
                  qpoint_center.y() + int_size * sin(angle_rad));
    }

    return qpolygon_calculatedShape;
}
