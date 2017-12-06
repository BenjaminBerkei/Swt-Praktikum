#include "startmenuewidget.h"
#include "ui_startmenuewidget.h"

StartMenueWidget::StartMenueWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartMenueWidget)
{
    ui->setupUi(this);
}

StartMenueWidget::~StartMenueWidget()
{
    delete ui;
}

void StartMenueWidget::switchToOptions()
{
    emit SIGNAL_smwChangeIndexFromStack(1);
}

void StartMenueWidget::switchToLoadGame()
{

}

void StartMenueWidget::on_qbutton_startGame_clicked()
{

}

void StartMenueWidget::on_qbutton_loadGame_clicked()
{

}

void StartMenueWidget::on_qbutton_options_clicked()
{
    switchToOptions();
}
