/*
 * Author: Manuel
 * Version: 0.2
 * Datum 07.12.2017
 * */


#include "options.h"

/*StandardKonstruktor, kann noch angepasst werden*/
Options::Options()
    : Options(0, 1, "Standard", 16)
{

}

Options::Options(bool bool_KI, bool bool_fog, QString str_m, int int_limit)
    : bool_ki(bool_KI), bool_fogOfWar(bool_fog), str_map(str_m), int_roundLimit(int_limit)
{

}
