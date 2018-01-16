/*
 * Author: Manuel
 * Version: 0.3
 * Datum 07.12.2017
 */
/*
 * Author: Lucas
 * Version: 0.4
 * Datum: 12.01.18
 * */

#include "menuewidget.h"
#include "ui_menuewidget.h"

MenueWidget::MenueWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenueWidget)
{
    ui->setupUi(this);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    ptr_mwStartMenueWidget = new StartMenueWidget(this, this);
    ptr_mwOptionsWidget = new OptionsWidget(this, this, ptr_mwStartMenueWidget->getPtr_smwOptions());
    ptr_mwLoadGameWidget = new LoadGameWidget(this);
    ptr_mwGameWidget = new GameWidget(this);

    //Füge die Verschiedenen Fenster dem MenueWidget zu
    ui->stack->addWidget(ptr_mwStartMenueWidget);
    ui->stack->addWidget(ptr_mwLoadGameWidget);
    ui->stack->addWidget(ptr_mwOptionsWidget);
    ui->stack->addWidget(ptr_mwGameWidget);
    ui->stack->setCurrentIndex(0);

    connect(ptr_mwStartMenueWidget, SIGNAL(SIGNAL_smwChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
    connect(ptr_mwOptionsWidget, SIGNAL(SIGNAL_optChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
    connect(ptr_mwLoadGameWidget, SIGNAL(SIGNAL_loadGChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
    connect(ptr_mwGameWidget, SIGNAL(SIGNAL_gameWidChangeIndexFromStack(int)), ui->stack, SLOT(setCurrentIndex(int)));
}

MenueWidget::~MenueWidget()
{
    delete ui;
}

void MenueWidget::resizeEvent(QResizeEvent *event)
{
    if(ui->stack->currentIndex() == 3)
    {
        ptr_mwGameWidget->resizeEvent(event, this->height(), this->width());
    }
}
