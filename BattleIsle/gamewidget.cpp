/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 * */

#include "gamewidget.h"
#include "ui_gamewidget.h"

void GameWidget::setInfoScene(HexagonDisplayInfo *info)
{
    qDebug() << "Bemerkung: In Funktion setInfoScene";

    for(auto &it : gameWidInfoScene->items())
    {
        qDebug() << "removeItems";
        gameWidInfoScene->removeItem(it);
    }
    qDebug() << "Bemerkung: remove in setInfoScene ausgefuehrt";
    gameWidInfoScene->addItem(info);
    qDebug() << "Bemerkung: addItem mit info in setInfoScene ausgefuehrt";
    gameWidInfoScene->update();
    qDebug() << "Bemerkung: update in setInfoScene ausgefuehrt";
}


GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    gameWidGame(NULL),
    ui(new Ui::GameWidget),
    gameWidGameScene(new QGraphicsScene(this)), gameWidInfoScene(new QGraphicsScene(this)),
    gameWidOptionsScene(new QGraphicsScene(this)), gameWidButtonScene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    ui->graphicsView_buttonView->setScene(gameWidButtonScene);
    ui->graphicsView_gameView->setScene(gameWidGameScene);
    ui->graphicsView_informationsView->setScene(gameWidInfoScene);
    ui->graphicsView_optionsView->setScene(gameWidOptionsScene);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::gameWidCreateMatchfield()
{


    for(unsigned int i = 0; i < gameWidGame->getVectorVectorHexagonMatchfield().size(); i++)
    {
        for(unsigned int j = 0; j < (gameWidGame->getVectorVectorHexagonMatchfield()[i]).size(); j++)
        {
            HexagonMatchfield* hex = gameWidGame->getVectorVectorHexagonMatchfield()[i][j];

            //Groesse der Bilder
            int PicSizeX = hex->pixmap().size().width();
            int PicSizeY = hex->pixmap().size().height();
            if(i & 1)
            {
                hex->setPos( i * 2 * PicSizeX / 3, j * PicSizeY + (PicSizeY / 2) );
            }
            else
            {
                hex->setPos( i * 2 * PicSizeX / 3, j * PicSizeY );
            }
            gameWidGameScene->addItem(hex);
        }
    }
    ui->graphicsView_gameView->setScene( gameWidGameScene );
}

HexagonDisplayInfo::HexagonDisplayInfo(HexagonMatchfield *ptr_hexMfield)
:QObject(0), QGraphicsRectItem(QRectF(-50,-50,230,100), 0), hexToDisplay(ptr_hexMfield)
{
    qStringHexDispHexType = "Typ: " + QString::fromStdString( hexToDisplay->getHexMatchfieldType() );
}

void HexagonDisplayInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-50 ,-50, hexToDisplay->pixmap());
    painter->drawText(QRectF(20,-50,200,20),qStringHexDispHexType);
}
