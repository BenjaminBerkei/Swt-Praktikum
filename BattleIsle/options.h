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
    bool bool_ki; //true = mit KI, false = ohne KI
    bool bool_fogOfWar; //true = mit Fog of War, false = ohne Fog of War
    QString str_map;
    int int_roundLimit; // 0 = kein Limit

public:
    Options();
    Options(bool bool_KI, bool bool_fog, QString str_m, int int_limit);
    bool getBool_ki() { return bool_ki; }
    bool getBool_fogOfWar() { return bool_fogOfWar; }
    QString getStr_map() { return str_map; }
    int getInt_roundLimit() { return int_roundLimit; }

public slots:
    void SLOT_setOptions(bool bool_KI, bool bool_fog, QString str_m, int int_limit);
};

#endif // OPTIONS_H
