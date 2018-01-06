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

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    gameWidGame(NULL),
    ui(new Ui::GameWidget)
{
    gameWidGameScene = new QGraphicsScene();
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::gameWidCreateMatchfield()
{
    //Groesse der Bilder
    int PicSizeX = 32;
    int PicSizeY = 32;

    for(unsigned int i = 0; i < gameWidGame->getVectorVectorHexagonMatchfield().size(); i++)
    {
        for(unsigned int j = 0; j < (gameWidGame->getVectorVectorHexagonMatchfield()[i]).size(); j++)
        {
            HexagonMatchfield* hex = gameWidGame->getVectorVectorHexagonMatchfield()[i][j];
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
