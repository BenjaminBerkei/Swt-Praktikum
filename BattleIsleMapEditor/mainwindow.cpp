#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    hexfield(new QGraphicsScene(this)),
    menuefield(new QGraphicsScene(this)),
    hexType(""), hexCacheField(nullptr), hexCacheMenue(nullptr), hexCacheUnit(nullptr),
    sizeX(15), sizeY(10),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->hexfieldGraphic->setScene(hexfield);
    ui->menueView->setScene(menuefield); 

    connect(ui->spinBoxX, SIGNAL(valueChanged(int)), this, SLOT(spinBoxX_valueChanged(int)));
    connect(ui->spinBoxY, SIGNAL(valueChanged(int)), this, SLOT(spinBoxY_valueChanged(int)));
    connect(ui->HexMenueBut, SIGNAL(clicked(bool)), this, SLOT(on_HexMenueBut_clicked()));
    connect(ui->UnitMenueBut, SIGNAL(clicked(bool)), this, SLOT(on_UnitMenueBut_clicked()));
    connect(ui->ResetButton, SIGNAL(clicked(bool)), this, SLOT(on_ResetButton_clicked()));
    connect(ui->spinBoltanium,SIGNAL(valueChanged(int)), this, SLOT(on_spinBoltanium_valueChanged(int)));


    ui->spinBoxX->setValue(sizeX);
    ui->spinBoxY->setValue(sizeY);

    ui->spinBoxX->setRange(1,150);
    ui->spinBoxY->setRange(1,150);
    ui->spinBoltanium->setRange(0,500);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createHexfield(std::vector<std::vector<Hexagon*>> &hexagonGrid)
{


    for(unsigned int i = 0; i < hexagonGrid.size(); i++)
    {
        for(unsigned int j = 0; j < hexagonGrid[i].size(); j++)
        {
            Hexagon* hex = hexagonGrid[i][j];
            connect(hex,SIGNAL(SIGNAL_clicked(Hexagon*)),this,SLOT(slot_changeHexType(Hexagon*)));
            connect(hex,SIGNAL(SIGNAL_clicked(Hexagon*)),this,SLOT(slot_changeUnit(Hexagon*)));

            //Groesse der Bilder
            int PicSizeX = hex->pixmap().size().width();
            int PicSizeY = hex->pixmap().size().height();

            int PicCoordX, PicCoordY; //Koordinaten der Bilder
            if(i & 1)
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY + (PicSizeY / 2);
            }
            else
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY;
            }

            if(hex->getUnit_stationed() != nullptr)
            {
                hexfield->addItem(hex->getUnit_stationed());
                hex->getUnit_stationed()->setPos(PicCoordX,PicCoordY);
            }

           hex->setPos(PicCoordX, PicCoordY);
           hexfield->addItem(hex);
        }
    }
    ui->hexfieldGraphic->setScene( hexfield );
}

void MainWindow::createMenue(std::vector<Hexagon*> &hexagonGrid)
{
    int i=0;
    for(auto & it : hexagonGrid)
    {
        connect(it,SIGNAL(SIGNAL_clicked(Hexagon*)),this,SLOT(slot_getHexType(Hexagon*)));
        it->setPos(0, i* it->pixmap().size().height());
        menuefield->addItem(it);
        i++;
    }
    ui->menueView->setScene(menuefield);
}

void MainWindow::createUnitfield(std::vector<std::vector<Hexagon *>> &hexagonGrid)
{
    for(unsigned int i = 0; i < hexagonGrid.size(); i++)
    {
        for(unsigned int j = 0; j < hexagonGrid[i].size(); j++)
        {
            Hexagon* hex = hexagonGrid[i][j];
            connect(hex,SIGNAL(SIGNAL_clicked(Hexagon*)),this,SLOT(slot_getUnit(Hexagon*)));

            //Groesse der Bilder
            int PicSizeX = hex->pixmap().size().width();
            int PicSizeY = hex->pixmap().size().height();

            int PicCoordX, PicCoordY; //Koordinaten der Bilder
            if(i & 1)
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY + (PicSizeY / 2);
            }
            else
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY;
            }

            if(hex->getUnit_stationed() != nullptr)
            {
                menuefield->addItem(hex->getUnit_stationed());
                hex->getUnit_stationed()->setPos(PicCoordX,PicCoordY);
            }

           hex->setPos(PicCoordX, PicCoordY);
           menuefield->addItem(hex);
        }
    }
    ui->menueView->setScene( menuefield );
}

//getter und setter
int MainWindow::getSizeX() const
{
    return sizeX;
}

int MainWindow::getSizeY() const
{
    return sizeY;
}

std::vector<std::vector<Hexagon*>> MainWindow::getMyField() const
{
    return myField;
}

std::vector<std::vector<Hexagon*>> MainWindow::getMyUnit() const
{
    return myUnit;
}

 std::vector<Hexagon*> MainWindow::getMyMenue() const
 {
     return myMenue;
 }

 QString MainWindow::getHexType() const
 {
     return hexType;
 }

void MainWindow::setSizeX(int arg)
{
    sizeX = arg;
}

void MainWindow::setSizeY(int arg)
{
    sizeY = arg;
}

void MainWindow::setMyField(std::vector<std::vector<Hexagon*>> &hexagonGrid)
{
    myField = hexagonGrid;
}

void MainWindow::setMyUnit(std::vector<std::vector<Hexagon*>> &hexagonGrid)
{
    myUnit = hexagonGrid;
}

void MainWindow::setMyMenue(std::vector<Hexagon *> &hexagonGrid)
{
    myMenue = hexagonGrid;
}

void MainWindow::setHexType(QString type)
{
    hexType = type;
}
// Ende

void MainWindow::updateBolt(){
    ui->spinBoltanium->setValue(hexCacheField->getBoltaniumCurrent());
}

void MainWindow::spinBoxX_valueChanged(int arg1)
{
    int tmp = myField.size();
    sizeX=arg1;
    if(tmp < sizeX)
    {
        for(int i = tmp; i < arg1; i++)
        {
            std::vector<Hexagon*> vectorHex;
            for( int j = 0; j < sizeY; j++ )
            {
                vectorHex.push_back(new Hexagon(QPoint(i,j), "waterDeep"));
            }
            myField.push_back(vectorHex);
        }
    }
    else if( tmp > sizeX)
    {
        for(int i = tmp; i > sizeX; i--)
        {
                myField.pop_back();
        }
    }
    for(auto & it : hexfield->items())
    {
        hexfield->removeItem(it);
    }
    createHexfield(myField);
}

void MainWindow::spinBoxY_valueChanged(int arg1)
{
   int tmp = myField[0].size();
   sizeY=arg1;
   if(tmp < sizeY)
   for(int i = 0 ; i < sizeX ; i++)
   {
       for(int j = tmp; j < sizeY; j++)
           myField[i].push_back(new Hexagon(QPoint(i,j), "waterDeep"));
   }
   else if(tmp > sizeY)
   {
       for(int i = 0 ; i < sizeX ; i++)
          {
              for(int j = tmp; j > sizeY; j--)
                  myField[i].pop_back();
          }
   }
   for(auto & it : hexfield->items())
   {
       hexfield->removeItem(it);
   }
   createHexfield(myField);
}

void MainWindow::slot_changeHexType(Hexagon* hex)
{
    if(hexType != "")
    {
        hex->setHexMatchfieldType(hexType);
    }
    if(hexCacheField != nullptr)
    {
        hexCacheField->setHexColor(Qt::black);
        hexCacheField->setZValue(0);
    }
    hex->setHexColor(Qt::red);
    hex->setZValue(3);

    hexCacheField = hex;
    hexfield->update();
    updateBolt();
}

void MainWindow::slot_getHexType(Hexagon * hex)
{
    if(hexCacheMenue != nullptr)
    {
        hexCacheMenue->setHexColor(Qt::black);
        hexCacheMenue->setZValue(0);
    }
    hexType = hex->getHexMatchfieldType();
    hex->setHexColor(Qt::red);
    hex->setZValue(3);

    hexCacheMenue = hex;
    menuefield->update();
}

void MainWindow::on_HexMenueBut_clicked()
{
    hexCacheUnit= nullptr;
    for(auto & it : menuefield->items())
    {
        menuefield->removeItem(it);
    }
    createMenue(myMenue);
}

void MainWindow::on_UnitMenueBut_clicked()
{
    hexCacheMenue= nullptr;
    for(auto & it : menuefield->items())
    {
        menuefield->removeItem(it);
    }
    createUnitfield(myUnit);
}

void MainWindow::on_ResetButton_clicked()
{
    if(hexCacheMenue != nullptr)
    {
        hexCacheMenue->setHexColor(Qt::black);
        hexCacheMenue->setZValue(0);
        hexCacheMenue= nullptr;
        hexType="";
     }
    if(hexCacheField != nullptr)
    {
        hexCacheField->setHexColor(Qt::black);
        hexCacheField->setZValue(0);
        hexCacheField= nullptr;
    }
    if(hexCacheUnit != nullptr)
    {
        hexCacheUnit->setHexColor(Qt::black);
        hexCacheUnit->setZValue(0);
        hexCacheUnit= nullptr;
    }

    menuefield->update();
    hexfield->update();
}

void MainWindow::on_spinBoltanium_valueChanged(int arg1)
{
    hexCacheField->setBoltaniumCurrent(arg1);
    hexfield->update();
}

void MainWindow::slot_getUnit(Hexagon *hex)
{
    if(hexCacheUnit != nullptr)
    {
        hexCacheUnit->setHexColor(Qt::black);
        hexCacheUnit->setZValue(0);
    }
    hexCacheUnit = hex;
    hexCacheUnit->setHexColor(Qt::red);
    hexCacheUnit->setZValue(3);
    setHexType("");
}

void MainWindow::slot_changeUnit(Hexagon *hex)
{
    if(hexCacheUnit != nullptr && hexCacheUnit->getUnit_stationed() != nullptr)
    {
        if(hex->getUnit_stationed() != nullptr)
        {
            hexfield->removeItem(hex->getUnit_stationed());
        }

        QPoint tmpPoint = hex->getQpoint_gridPosition();
        QString tmpName = hexCacheUnit->getUnit_stationed()->getName();
        int tmpPly = hexCacheUnit->getUnit_stationed()->getPLY();
        Unit* tmp = new Unit(tmpPoint, tmpName, tmpPly);
        hex->setUnit_stationed(tmp);
        hex->getUnit_stationed()->setPos(hex->pos());
        hexfield->addItem(hex->getUnit_stationed());
        fieldUnit.push_back(tmp);
    }
    hexfield->update();
}
