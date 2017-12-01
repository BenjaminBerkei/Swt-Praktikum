#include "button.h"

Button::Button(QPoint qpoint_center, int int_size, QPoint qpoint_position)
    : HexagonBase(qpoint_center, int_size, qpoint_position)
{

}
/*Test*/
QPolygon Button::getShape() const
{
    return hexShape;
}
/*Test_Ende*/

