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
    ButtonMove *test = new ButtonMove(QPoint(10,10),50,QPoint(0,0));
    testScene->addItem(test);
    ui->testView->setScene(testScene);
    QObject::connect(test, SIGNAL(clicked(Button*)), this, SLOT(print(Button*)));

    /*Testen_Ende*/
}

displayHexTest::~displayHexTest()
{
    delete testView;
    delete testScene;
    delete ui;
}

void displayHexTest::print(Button *button)
{
    qDebug() << button->getShape();
}
