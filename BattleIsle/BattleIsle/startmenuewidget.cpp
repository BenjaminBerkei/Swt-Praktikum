/*
 * Author: Manuel
 * Version: 0.3
 * Datum: 07.12.2017
 *
 * Author: Manuel
 * Version: 0.4
 * Datum: 30.12.2017
 * Kommentar: Verbindung zu GameWidget hinzugefuegt
 */

#include "startmenuewidget.h"
#include "ui_startmenuewidget.h"


StartMenueWidget::StartMenueWidget(QWidget *parent , MenueWidget *ptr_menueWidget) :
    QWidget( parent ),
    ptr_smwMenueWidget(ptr_menueWidget),
    ui( new Ui::StartMenueWidget )
{
    ui->setupUi( this );
    ptr_smwOptions = new Options();

    //Die eingestellten Optionen anzeigen
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

void StartMenueWidget::startGame( Options *options_initOptions )
{
    ptr_smwMenueWidget->resize( 1200,750 );
    ptr_smwMenueWidget->ui->stack->resize( 1190, 740 );

    //Erstelle ein Objekt vom Typ Game
    Game game(options_initOptions, ptr_smwMenueWidget->getPtr_mwGameWidget());
    //Erstelle eine Assoziation von GameWidget zu Game
    ptr_smwMenueWidget->getPtr_mwGameWidget()->setGameWidGame(&game);

    //Wechsel zu Widget 3
    emit SIGNAL_smwChangeIndexFromStack( 3 );
    //Das Signal wird im Konstruktor von MenueWidget verbunden
}

void StartMenueWidget::switchToOptions()
{
    //Wechsel zu Widget 2
    emit SIGNAL_smwChangeIndexFromStack( 2 );
    //Das Signal wird im Konstruktor von MenueWidget verbunden
}

void StartMenueWidget::switchToLoadGame()
{
    //Wechsel zu Widget 1
    emit SIGNAL_smwChangeIndexFromStack( 1 );
    //Das Signal wird im Konstruktor von MenueWidget verbunden
}

void StartMenueWidget::smwUpdateSettings()
{
    //Die eingestellten Optionen updaten
    if( ptr_smwOptions->getBool_ki() == true )
        ui->label_opponent_indication->setText( "Computer" );
    else
        ui->label_opponent_indication->setText( "Mensch" );

    if( ptr_smwOptions->getBool_fogOfWar() == true )
        ui->label_fogOfWar_indication->setText( "Ein" );
    else
        ui->label_fogOfWar_indication->setText( "Aus" );

    ui->label_map_indication->setText( ptr_smwOptions->getStr_map() );

    if( ptr_smwOptions->getInt_roundLimit() == 0 )
        ui->label_limit_indication->setText("Kein Limit");
    else
        ui->label_limit_indication->setText(QString::number(ptr_smwOptions->getInt_roundLimit()));
}

void StartMenueWidget::on_qbutton_startGame_clicked()
{
    startGame( ptr_smwOptions );
}

void StartMenueWidget::on_qbutton_loadGame_clicked()
{
    switchToLoadGame();
}

void StartMenueWidget::on_qbutton_options_clicked()
{
    switchToOptions();
}