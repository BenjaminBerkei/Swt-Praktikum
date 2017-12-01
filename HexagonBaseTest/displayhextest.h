#ifndef DISPLAYHEXTEST_H
#define DISPLAYHEXTEST_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "hexagonbase.h"
#include "button.h"
namespace Ui {
class displayHexTest;
}

class displayHexTest : public QDialog
{
    Q_OBJECT

public:
    explicit displayHexTest(QWidget *parent = 0);
    ~displayHexTest();

private:
    Ui::displayHexTest *ui;
    QGraphicsView *testView;
    QGraphicsScene *testScene;
public slots:
    void print(ButtonMove *button);
    void print(ButtonAction *button);
    void print(ButtonMap *button);
    void print(ButtonInformation *button);
    void print(ButtonChangePhase *button);
    void print(ButtonMenue *button);
};

#endif // DISPLAYHEXTEST_H
