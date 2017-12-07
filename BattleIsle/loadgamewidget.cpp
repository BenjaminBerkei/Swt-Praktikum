/*
 * Author: Manuel
 * Version: 0.1
 * Datum 04.12.2017
 */

#include "loadgamewidget.h"
#include "ui_loadgamewidget.h"

LoadGameWidget::LoadGameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadGameWidget)
{
    ui->setupUi(this);
}

LoadGameWidget::~LoadGameWidget()
{
    delete ui;
}

void LoadGameWidget::returnToStartMenue()
{
    emit SIGNAL_loadGChangeIndexFromStack(0);
}

void LoadGameWidget::on_qbutton_apply_clicked()
{
    //loadGame(SaveGame* saveGame_selection);
}

void LoadGameWidget::on_qbutton_cancel_clicked()
{
    returnToStartMenue();
}
