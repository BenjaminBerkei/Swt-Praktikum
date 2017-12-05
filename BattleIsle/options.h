/*
 * Author: Lucas
 * Version: 0.1
 * Datum 05.12.2017
 * */

#ifndef OPTIONS_H
#define OPTIONS_H
#include<QObject>
#include <string>
class Options : public QObject
{
    Q_OBJECT
private:
    bool bool_ki;
    bool bool_fogOfWar;
    std::string str_map;
    int int_roundLimit;
public:
    Options();
    Options(bool bool_KI, bool bool_fog, std::string str_m, int int_limit);
public slots:
    void SLOT_setOptions(bool bool_KI, bool bool_fog, std::string str_m, int int_limit);
};

#endif // OPTIONS_H
