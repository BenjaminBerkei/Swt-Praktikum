/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 * */

#include "gamewidget.h"
#include "ui_gamewidget.h"

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    GameWidGame(NULL),
    ui(new Ui::GameWidget)
{
    ui->setupUi(this);
}

GameWidget::~GameWidget()
{
    delete ui;
}
