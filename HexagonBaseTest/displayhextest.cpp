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
    /*Alle Buttons einmal erzeugt*/
    int size = 30;

    ButtonMove *testMove = new ButtonMove(QPoint(10,10),size,QPoint(0,0));
    ButtonAction *testAction = new ButtonAction(QPoint(10 + 2 * size, 10),size,QPoint(1,0));
    ButtonMap *testMap = new ButtonMap(QPoint(10 + 4 * size, 10),size,QPoint(2,0));
    ButtonInformation *testInformation = new ButtonInformation(QPoint(10 + 6 * size, 10),size,QPoint(3,0));
    ButtonChangePhase *testChangePhase = new ButtonChangePhase(QPoint(10 + 8 * size, 10),size,QPoint(4,0));
    ButtonMenue *testMenue = new ButtonMenue(QPoint(10 + 10 * size,10),size,QPoint(5,0));

    testScene->addItem(testMove);
    testScene->addItem(testAction);
    testScene->addItem(testMap);
    testScene->addItem(testInformation);
    testScene->addItem(testChangePhase);
    testScene->addItem(testMenue);

    ui->testView->setScene(testScene);

    QObject::connect(testMove, SIGNAL(clicked(ButtonMove*)), this, SLOT(print(ButtonMove*)));
    QObject::connect(testAction, SIGNAL(clicked(ButtonAction*)), this, SLOT(print(ButtonAction*)));
    QObject::connect(testMap, SIGNAL(clicked(ButtonMap*)), this, SLOT(print(ButtonMap*)));
    QObject::connect(testInformation, SIGNAL(clicked(ButtonInformation*)), this, SLOT(print(ButtonInformation*)));
    QObject::connect(testChangePhase, SIGNAL(clicked(ButtonChangePhase*)), this, SLOT(print(ButtonChangePhase*)));
    QObject::connect(testMenue, SIGNAL(clicked(ButtonMenue*)), this, SLOT(print(ButtonMenue*)));

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
void displayHexTest::print(ButtonMap *button)
{
    button->printType();
}
void displayHexTest::print(ButtonInformation *button)
{
    button->printType();
}
void displayHexTest::print(ButtonChangePhase *button)
{
    button->printType();
}
void displayHexTest::print(ButtonMenue *button)
{
    button->printType();
}
