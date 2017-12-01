#include "displayhextest.h"
#include "ui_displayhextest.h"

displayHexTest::displayHexTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::displayHexTest)
{
    ui->setupUi(this);

    /*Testen*/
    testView = new QGraphicsView();
    testScene = new QGraphicsScene(this);
    ButtonMove *testMove = new ButtonMove(QPoint(10,10),30,QPoint(0,0));
    ButtonAction *testAction = new ButtonAction(QPoint(70,30),30,QPoint(1,0));
    testScene->addItem(testMove);
    testScene->addItem(testAction);
    ui->testView->setScene(testScene);
    QObject::connect(testMove, SIGNAL(clicked(ButtonMove*)), this, SLOT(print(ButtonMove*)));
    QObject::connect(testAction, SIGNAL(clicked(ButtonAction*)), this, SLOT(print(ButtonAction*)));

    /*Testen_Ende*/
}

displayHexTest::~displayHexTest()
{
    delete testView;
    delete testScene;
    delete ui;
}

void displayHexTest::print(ButtonMove *button)
{
    button->printType();
}

void displayHexTest::print(ButtonAction *button)
{
    button->printType();
}
