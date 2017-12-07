/*
 * Author: Manuel
 * Version: 0.3
 * Datum 07.12.2017
 */


#include "menuewidget.h"
#include "ui_menuewidget.h"

MenueWidget::MenueWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenueWidget)
{
    ui->setupUi(this);
    ptr_mwStartMenueWidget = new StartMenueWidget(this);
    ptr_mwOptionsWidget = new OptionsWidget(this, this, ptr_mwStartMenueWidget->getPtr_smwOptions());
    ptr_mwLoadGameWidget = new LoadGameWidget(this);

    //Füge die Verschiedenen Fenster dem MenueWidget zu
    ui->stack->addWidget(ptr_mwStartMenueWidget);
    ui->stack->addWidget(ptr_mwLoadGameWidget);
    ui->stack->addWidget(ptr_mwOptionsWidget);
    ui->stack->setCurrentIndex(0);

    connect(ptr_mwStartMenueWidget, SIGNAL(SIGNAL_smwChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
    connect(ptr_mwOptionsWidget, SIGNAL(SIGNAL_optChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
    connect(ptr_mwLoadGameWidget, SIGNAL(SIGNAL_loadGChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
}

MenueWidget::~MenueWidget()
{
    delete ui;
}
