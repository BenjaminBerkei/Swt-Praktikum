/*
 * Author: Manuel
 * Version: 0.2
 * Datum 04.12.2017
 */

#include "startmenuewidget.h"
#include "ui_startmenuewidget.h"


StartMenueWidget::StartMenueWidget( QWidget *parent ) :
    QWidget( parent ),
    ui( new Ui::StartMenueWidget )
{
    ui->setupUi( this );
    ptr_smwOptions = new Options();

    //Die Eingestellten Optionen anzeigen
    if( ptr_smwOptions->getBool_ki() == true )
        ui->label_opponent_indication->setText( "Computer" );
    if( ptr_smwOptions->getBool_fogOfWar() == true )
        ui->label_fogOfWar_indication->setText( "Ein" );
    ui->label_map_indication->setText( ptr_smwOptions->getStr_map() );
    if( ptr_smwOptions->getInt_roundLimit() == 0)
        ui->label_limit_indication->setText("Kein Limit");
    else
        ui->label_limit_indication->setText(QString::number(ptr_smwOptions->getInt_roundLimit()));
}

StartMenueWidget::~StartMenueWidget()
{
    delete ui;
}

void StartMenueWidget::switchToOptions()
{
    //Wechsel zu Widget 2
    emit SIGNAL_smwChangeIndexFromStack(2);
    //Das Signal wird im Konstruktor von MenueWidget verbunden
}

void StartMenueWidget::switchToLoadGame()
{
    //Wechsel zu Widget 1
    emit SIGNAL_smwChangeIndexFromStack(1);
    //Das Signal wird im Konstruktor von MenueWidget verbunden
}

void StartMenueWidget::on_qbutton_startGame_clicked()
{
    //startGame(Options* options_initOptions);
}

void StartMenueWidget::on_qbutton_loadGame_clicked()
{
    switchToLoadGame();
}

void StartMenueWidget::on_qbutton_options_clicked()
{
    switchToOptions();
}
