#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <vector>
#include <QGraphicsView>
#include <QSpinBox>
#include "hexagon.h"
#include "unit.h"

namespace Ui {
class MainWindow;
}

class Hexagon;
class Unit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QGraphicsScene *hexfield;
    QGraphicsScene *menuefield;
    std::vector<std::vector<Hexagon*>> myField;
    std::vector<std::vector<Hexagon*>> myUnit;
    std::vector<Hexagon*> myMenue;
    std::vector<Unit*> fieldUnit;
    QString hexType;
    int sizeX;
    int sizeY;
    Hexagon* hexCacheField;
    Hexagon* hexCacheMenue;
    Hexagon* hexCacheUnit;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createHexfield(std::vector<std::vector<Hexagon*>> &hexagonGrid);
    void createMenue(std::vector<Hexagon*> &hexagonGrid);
    void createUnitfield(std::vector<std::vector<Hexagon*>> &hexagonGrid);

    int getSizeX() const;
    int getSizeY() const;
    std::vector<std::vector<Hexagon*>> getMyField() const;
    std::vector<std::vector<Hexagon*>> getMyUnit() const;
    std::vector<Hexagon*> getMyMenue() const;
    QString getHexType() const;


    void setSizeX(int);
    void setSizeY(int);
    void setMyField(std::vector<std::vector<Hexagon*>> &hexagonGrid);
    void setMyUnit(std::vector<std::vector<Hexagon*>> &hexagonGrid);
    void setMyMenue(std::vector<Hexagon*> &hexagonGrid);
    void setHexType(QString);

    void updateBolt();

private slots:
    void spinBoxX_valueChanged(int arg1);
    void spinBoxY_valueChanged(int arg1);
    void slot_changeHexType(Hexagon*);
    void slot_getHexType(Hexagon*);
    void on_HexMenueBut_clicked();
    void on_UnitMenueBut_clicked();
    void on_ResetButton_clicked();
    void on_spinBoltanium_valueChanged(int arg1);
    void slot_getUnit(Hexagon*);
    void slot_changeUnit(Hexagon*);

};


#endif // MAINWINDOW_H
