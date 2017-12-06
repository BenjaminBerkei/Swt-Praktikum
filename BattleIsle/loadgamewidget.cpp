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
