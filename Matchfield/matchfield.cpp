#include "matchfield.h"
#include "ui_matchfield.h"

Matchfield::Matchfield(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Matchfield)
{
    ui->setupUi(this);
}

Matchfield::~Matchfield()
{
    delete ui;
}
