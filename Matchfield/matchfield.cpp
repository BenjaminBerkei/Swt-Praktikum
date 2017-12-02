#include "matchfield.h"
#include "ui_matchfield.h"

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

Matchfield::~Matchfield()
{
    delete ui;
}

bool Matchfield::readMap(const std::string pathToMap)
{
    std::ifstream imapStream(pathToMap);    //Öffnen des Einlesestreams
    if(!imapStream.is_open())               //Falls nicht erfolgreich false zurückgeben
    {
        return false;
    }
    /*
     *Annahme: Datei aufgebaut wie folgt
     * dimX dimY
     * matrix(int)(dimX x dimY)
     * */
    imapStream >> int_matchfieldSizeX; //Einlesen der Dimensionen
    imapStream >> int_matchfieldSizeY;

    for(int x = 0; x < int_matchfieldSizeX; x++)    //Einlesen des Rests
    {
        hexagonMatchfield_gameGrid.push_back(std::vector< HexagonMatchfield* >() );
        for(int y = 0; y < int_matchfieldSizeY; y++)
        {
            int tmp;
            imapStream >> tmp;
            hexagonMatchfield_gameGrid[x].push_back(new HexagonMatchfield(tmp));
        }
    }
    return true;
}
