/*
 * Author: Lucas
 * Version: 0.1
 * Datum 01.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum 30.12.2017
 * Kommentar: hexagonMatchfield_gameGrid und button_menueBar raus genommen in der .h Datei
 * */

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
