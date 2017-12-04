/*
 * Author: Manuel
 * Version: 0.1
 * Datum 04.12.2017
 */

#include "optionswidget.h"
#include "ui_optionswidget.h"

OptionsWidget::OptionsWidget(QWidget *parent) :
    ptr_optParent(parent),
    ui(new Ui::OptionsWidget)
{
    ui->setupUi(this);
}

OptionsWidget::~OptionsWidget()
{
    delete ui;
}

void OptionsWidget::returnToStartMenue()
{
    hide();
    ptr_optParent->show();
}

void OptionsWidget::on_qbutton_apply_clicked()
{
    returnToStartMenue();
}

void OptionsWidget::on_qbutton_cancel_clicked()
{
    returnToStartMenue();
}
