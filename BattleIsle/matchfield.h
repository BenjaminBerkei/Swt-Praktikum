/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum 30.12.2017
 * Kommentar: hexagonMatchfield_gameGrid und button_menueBar raus genommen
 * */
#ifndef MATCHFIELD_H
#define MATCHFIELD_H

#include <QDialog>
#include <string>
#include <vector>
#include <fstream>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDebug>

#include "button.h"
#include "hexagonbase.h"
#include "hexagonmatchfield.h"
#include "game.h"

namespace Ui {
class Matchfield;
}

class Matchfield : public QDialog
{
    Q_OBJECT
private:
    const std::string str_matchfieldName;
    int int_matchfieldSizeX;
    int int_matchfieldSizeY;
    Game* ptr_mfieldGame;
    //Folgendes wurde nach Entwurf 2.1 in die Klasse Game gelegt:
    //std::vector< std::vector < HexagonMatchfield* > > hexagonMatchfield_gameGrid;
    //std::vector < Button* > button_menueBar;

    Ui::Matchfield *ui;

public:
    Matchfield(std::string name, Game* game, QWidget *parent = 0);
    /*Programmieren wenn savegame geschrieben*/
    //Matchfield(saveInit *Savegame, QWidget *parent = 0);
    ~Matchfield();
    bool readMap(const std::string pathToMap);
};

#endif // MATCHFIELD_H
