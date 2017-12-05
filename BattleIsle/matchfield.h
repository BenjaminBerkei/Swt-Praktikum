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
    std::vector< std::vector < HexagonMatchfield* > > hexagonMatchfield_gameGrid;
    std::vector < Button* > button_menueBar;

    QGraphicsView *qview_gameView;
    QGraphicsView *qview_menueBarView;
    QGraphicsScene *qscene_gameScene;
    QGraphicsScene *qscene_menueBarScene;

    Ui::Matchfield *ui;

public:
    Matchfield(std::string name, QWidget *parent = 0);
    /*Programmieren wenn savegame geschrieben*/
    //Matchfield(saveInit *Savegame, QWidget *parent = 0);
    ~Matchfield();
    bool readMap(const std::string pathToMap);
};

#endif // MATCHFIELD_H
