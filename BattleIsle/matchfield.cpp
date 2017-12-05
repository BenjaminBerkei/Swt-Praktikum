#include "matchfield.h"
#include "ui_matchfield.h"

/*Ausarbeiten wenn wir uns auf die Art der Speicherung geeinigt haben*/
Matchfield::Matchfield(std::string name, QWidget *parent) :
    QDialog(parent), str_matchfieldName(name), ui(new Ui::Matchfield)
{
    ui->setupUi(this);

    /*
     * Einlesen der Parameter:
     *      int_matchfieldSizeX
     *      int_matchfieldSizeY
     *      hexagonMatchfield_gameGrid
     *
     * */

    if(readMap(str_matchfieldName))
    {
       qDebug() << "Map konnte erfolgreich gelesen werde";
    }else
    {
        qDebug() << "Map konnte nicht geöffnet werden";
    }


}
/*
Matchfield::Matchfield(saveInit *Savegame, QWidget *parent = 0)
{
	
}
*/
Matchfield::~Matchfield()
{
    delete ui;
}
/*Ausarbeiten wenn wir uns auf die Art der Speicherung geeinigt haben*/
bool Matchfield::readMap(const std::string pathToMap)
{
    return false;
}
