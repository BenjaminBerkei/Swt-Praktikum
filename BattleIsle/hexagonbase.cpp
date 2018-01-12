/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 * */

#include "hexagonbase.h"

QPoint HexagonBase::getQpoint_gridPosition() const
{
    return qpoint_gridPosition;
}

HexagonBase::HexagonBase(QPoint qpoint_position, Game *ptr_game)
    :  qpoint_gridPosition(qpoint_position),
      ptr_hexBaseGame(ptr_game)
{

}
