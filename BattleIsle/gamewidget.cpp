/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
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
    HexagonMatchfield* hex = gameWidGame->hexagonMatchfield_gameGrid[0][0];
    gameWidGameScene->addItem(hex);
    ui->graphicsView_gameView->setScene( gameWidGameScene );

    qDebug() << "Bemerkung: Funktion gameWidCreateMatchfield ausgeführt";
}
