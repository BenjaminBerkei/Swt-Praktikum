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

void MenueWidget::setPtr_runningGame(Game *value)
{
    if(ptr_runningGame != nullptr)
    {
        delete ptr_runningGame;
    }
    ptr_runningGame = value;
}

Game *MenueWidget::getPtr_runningGame() const
{
    return ptr_runningGame;
}

MenueWidget::MenueWidget(QPointer<DebugBrowser> browser, QWidget *parent) :
    QMainWindow(parent),
    ptr_debugBrowser(browser), ui(new Ui::MenueWidget)
{
    ui->setupUi(this);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    ptr_mwStartMenueWidget = new StartMenueWidget(this, this);
    ptr_mwOptionsWidget = new OptionsWidget(this, this, ptr_mwStartMenueWidget->getPtr_smwOptions());
    ptr_mwLoadGameWidget = new LoadGameWidget(this);
    ptr_mwGameWidget = new GameWidget(this);
    ptr_runningGame = nullptr;

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

    ptr_debugBrowser->move(QApplication::desktop()->screen()->rect().center().x() - this->rect().center().x() + ptr_debugBrowser->width(),
                           QApplication::desktop()->screen()->rect().center().y() - this->rect().center().y());
}

MenueWidget::~MenueWidget()
{
    qDebug() << "Destruktor MenueWidget begin";
    delete ui;
    qDebug() << "\t Delete ui done";
    delete ptr_runningGame;
    qDebug() << "\t Delete ptr_runningGame done";
    delete ptr_mwStartMenueWidget;
    qDebug() << "\t Delete ptr_mwStartMenueWidget done";
    delete ptr_mwOptionsWidget;
    qDebug() << "\t Delete ptr_mwOptionsWidget done";
    delete ptr_mwLoadGameWidget;
    qDebug() << "\t Delete ptr_mwLoadGameWidget done";
    delete ptr_mwGameWidget;
    qDebug() << "\t Delete ptr_mwGameWidget done";
    delete ptr_debugBrowser;
    qDebug() << "\t Delete ptr_debugBrowser done";
    qDebug() << "Destruktor MenueWidget end";
}

void MenueWidget::resizeEvent(QResizeEvent *event)
{
    if(ui->stack->currentIndex() == 3 && ptr_runningGame != nullptr)
    {
        ptr_mwGameWidget->resizeEvent(event, this->height(), this->width());
    }
    qDebug() << "Resize event";
}
