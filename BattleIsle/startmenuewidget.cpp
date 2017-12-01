#include "startmenuewidget.h"
#include "ui_startmenuewidget.h"

StartMenueWidget::StartMenueWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartMenueWidget)
{
    ui->setupUi(this);
}

StartMenueWidget::~StartMenueWidget()
{
    delete ui;
}
