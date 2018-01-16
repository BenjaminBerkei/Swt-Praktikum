/*
 * Author: Manuel
 * Version: 0.1
 * Datum 30.12.2017
 *
 * Author: Manuel
 * Version: 0.2
 * Datum: 04.01.2018
 *
 * Author: Manuel
 * Version: 0.3
 * Datum: 12.01.2018
 * Kommentar: Buttons hinzugefuegt
 *
 * Author: Lucas, Manuel
 * Version: 0.4
 * Datum: 13.01.2018
 *
 * Author: Lucas
 * Version: 0.5
 * Datum: 14.01.2018
 * Kommentar: Label für den zustand des spiels eingefügt: player & playerUnitNumber
 * */
#include "gamewidget.h"
#include "ui_gamewidget.h"

QGraphicsScene *GameWidget::getGameWidOptionsScene() const
{
    return gameWidOptionsScene;
}
QGraphicsScene *GameWidget::getGameWidGameScene() const
{
    return gameWidGameScene;
}

QGraphicsScene *GameWidget::getGameWidButtonScene() const
{
    return gameWidButtonScene;
}

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameWidget),
    gameWidGameScene(new QGraphicsScene(this)), gameWidInfoScene(new QGraphicsScene(this)),
    gameWidOptionsScene(new QGraphicsScene(this)), gameWidButtonScene(new QGraphicsScene(this)),
    sizeX(50), sizeY(50)
{
    ui->setupUi(this);
    ui->graphicsView_buttonView->setScene(gameWidButtonScene);
    ui->graphicsView_gameView->setScene(gameWidGameScene);
    ui->graphicsView_informationsView->setScene(gameWidInfoScene);
    ui->graphicsView_optionsView->setScene(gameWidOptionsScene);

    gameWidButtonScene->setSceneRect(ui->graphicsView_buttonView->rect());
    QGraphicsTextItem* playerTag = new QGraphicsTextItem("Player: ");
    QGraphicsTextItem* energieTag = new QGraphicsTextItem("Energie: ");
    QGraphicsTextItem* unitsTag = new QGraphicsTextItem("Units: ");
    QGraphicsTextItem* phaseTag = new QGraphicsTextItem("Phase: ");

    textItem_currentPlayer = new QGraphicsTextItem("");
    textItem_currentEnergie= new QGraphicsTextItem("");
    textItem_currentUnits= new QGraphicsTextItem("");
    textItem_currentPhase= new QGraphicsTextItem("");

    int x = 0;
    int y = 10;
    int xChange = 70;

    playerTag->setPos(x, y);
    phaseTag->setPos(x, 3 * y);
    unitsTag->setPos(x, 5 * y);
    energieTag->setPos(x, 7 * y);

    textItem_currentPlayer->setPos(x + xChange, y);
    textItem_currentPhase->setPos(x + xChange, 3 * y);
    textItem_currentUnits->setPos(x + xChange, 5 * y);
    textItem_currentEnergie->setPos(x + xChange, 7 * y);

    gameWidButtonScene->addItem(playerTag);
    gameWidButtonScene->addItem(energieTag);
    gameWidButtonScene->addItem(unitsTag);
    gameWidButtonScene->addItem(phaseTag);

    gameWidButtonScene->addItem(textItem_currentPlayer);
    gameWidButtonScene->addItem(textItem_currentPhase);
    gameWidButtonScene->addItem(textItem_currentEnergie);
    gameWidButtonScene->addItem(textItem_currentUnits);

    ui->graphicsView_optionsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_optionsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

GameWidget::~GameWidget()
{
    delete ui;
}

void GameWidget::resizeEvent(QResizeEvent *,int mainHeight, int mainWidth)
{
    int xLeftTop = ui->graphicsView_gameView->x();
    int yLeftTop = ui->graphicsView_gameView->y();

    ui->graphicsView_gameView->setGeometry(xLeftTop, yLeftTop, mainWidth - xLeftTop - 265, mainHeight - yLeftTop - 165);
    ui->graphicsView_informationsView->setGeometry(xLeftTop + ui->graphicsView_gameView->width() + 5, yLeftTop, 240, 160);
    ui->graphicsView_optionsView->setGeometry(xLeftTop + ui->graphicsView_gameView->width() + 5, yLeftTop + ui->graphicsView_informationsView->height() + 5, ui->graphicsView_informationsView->width(), this->height() - 100);
    ui->graphicsView_buttonView->setGeometry(xLeftTop, yLeftTop + ui->graphicsView_gameView->height() + 10, ui->graphicsView_gameView->width(), 110);

    gameWidOptionsScene->setSceneRect(0,0, ui->graphicsView_optionsView->width() + 10,120 * gameWidOptionsScene->items().size() + 20);
}

void GameWidget::gameWidCreateMatchfield(std::vector<std::vector<HexagonMatchfield*>> &hexagonGrid)
{


    for(unsigned int i = 0; i < hexagonGrid.size(); i++)
    {
        for(unsigned int j = 0; j < hexagonGrid[i].size(); j++)
        {
            HexagonMatchfield* hex = hexagonGrid[i][j];

            //Groesse der Bilder
            int PicSizeX = hex->pixmap().size().width();
            int PicSizeY = hex->pixmap().size().height();

            int PicCoordX, PicCoordY; //Koordinaten der Bilder
            if(i & 1)
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY + (PicSizeY / 2);
            }
            else
            {
                PicCoordX = i * 2 * PicSizeX / 3;
                PicCoordY = j * PicSizeY;
            }

            if(hex->getUnit_stationed() != nullptr)
            {
                gameWidGameScene->addItem(hex->getUnit_stationed());
                hex->getUnit_stationed()->setPos(PicCoordX,PicCoordY);
            }

            hex->setPos(PicCoordX, PicCoordY);
            gameWidGameScene->addItem(hex);
        }
    }
    ui->graphicsView_gameView->setScene( gameWidGameScene );
}

void GameWidget::gameWidCreateButtonBar(std::vector<Button*> buttonVector)
{
    double startPos = gameWidButtonScene->width() / double(buttonVector.size());
    for(unsigned int i = 0; i < buttonVector.size(); i++)
    {
        buttonVector[i]->setPos( startPos + (i+1) * buttonVector[i]->pixmap().size().width() ,25);
        gameWidButtonScene->addItem(buttonVector[i]);
    }
    gameWidButtonScene->update();
}

void GameWidget::clearScenes()
{
    //leere gameWidInfoScene
    for(auto &it : gameWidInfoScene->items())
    {
        gameWidInfoScene->removeItem(it);
    }
    gameWidInfoScene->update();

    //leere gameWidOptionsScene
    for(auto &it : gameWidOptionsScene->items())
    {
        gameWidOptionsScene->removeItem(it);
    }
    gameWidOptionsScene->update();
}

void GameWidget::updateInfoOptScenes()
{
    gameWidInfoScene->update(gameWidInfoScene->sceneRect());
    gameWidOptionsScene->update(gameWidOptionsScene->sceneRect());
}

void GameWidget::updateMatchfieldScene()
{
    gameWidGameScene->update(gameWidGameScene->sceneRect());
}

void GameWidget::animateUnit(Unit * unitToAnimate, std::vector<QPointF> points)
{
    QTimeLine *timer = new QTimeLine(2000);
    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;

    animation->setItem(unitToAnimate);
    animation->setTimeLine(timer);
    for(unsigned i = 1; i <= points.size(); i++)
    {
        animation->setPosAt(i/(double)points.size(), points[points.size() - i]);
    }
    timer->start();
}

void GameWidget::setInfoScene(HexagonDisplayInfo *info)
{
    for(auto &it : gameWidInfoScene->items())
    {
        gameWidInfoScene->removeItem(it);
    }
    gameWidInfoScene->addItem(info);
    gameWidInfoScene->update();
    gameWidGameScene->update();
}

void GameWidget::setOptScene(std::vector<Unit *> vector_Unit)
{
    for(auto &it : gameWidOptionsScene->items())
    {
        gameWidOptionsScene->removeItem(it);
    }

    if(vector_Unit.size() > 0)
    {
        gameWidOptionsScene->setSceneRect(0,0, vector_Unit[0]->getUnitDisplay()->rect().width(),
                                            120 * vector_Unit.size() + 20);
        for(unsigned i = 0; i < vector_Unit.size(); i++)
        {
            gameWidOptionsScene->addItem(vector_Unit[i]->getUnitDisplay());
            vector_Unit[i]->getUnitDisplay()->setPos(50, i * vector_Unit[i]->getUnitDisplay()->rect().height() + 60);
        }
    }
    gameWidOptionsScene->update();
}

void GameWidget::setPlayerLabel(QString text)
{
    textItem_currentPlayer->setPlainText(text);
}

void GameWidget::setPhaseLabel(QString text)
{
    textItem_currentPhase->setPlainText(text);
}

void GameWidget::setUnitsLabel(int value)
{
    textItem_currentUnits->setPlainText(QString::number(value));
}

void GameWidget::setEnergieLabel(int current, int max)
{
  textItem_currentEnergie->setPlainText(QString::number(current) + "/" + QString::number(max));
}

QGraphicsScene *GameWidget::getGameWidInfoScene() const
{
    return gameWidInfoScene;
}

int GameWidget::getSizeX() const
{
    return sizeX;
}

int GameWidget::getSizeY() const
{
    return sizeY;
}
HexagonDisplayInfo::HexagonDisplayInfo(HexagonMatchfield *ptr_hexMfield)
    :QObject(0), QGraphicsRectItem(QRectF(-50,-50,230,100), 0), hexToDisplay(ptr_hexMfield)
{
    updateText();
}

void HexagonDisplayInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    updateText();
    painter->drawPixmap(-50 ,-50, hexToDisplay->pixmap());
    painter->drawText(QRectF(20,-50,1000,200),qStringHexDispHexType);

    if(hexToDisplay->getHexFogOfWar() != true && hexToDisplay->getUnit_stationed() != nullptr)
    {
        painter->drawPixmap(-50,-50, hexToDisplay->getUnit_stationed()->pixmap());
        painter->drawText(QRectF(20,-30,200,20),qStringUnitDispUnitName);
        painter->drawText(QRectF(20,-10, 200,20),qStringUnitDispUnitType);
        painter->drawText(QRectF(20,10,200,20),qStringUnitDispUnitLife);

        if(qStringUnitDispMovement != "NONE")
        {
            painter->drawText(QRectF(20,30,200,20),qStringUnitDispMovement);
        }
        if(qStringUnitDispUnitAttack != "NONE")
        {
            painter->drawText(QRectF(20,50,200,20),qStringUnitDispUnitAttack);
        }
    }
}

void HexagonDisplayInfo::updateText()
{
    qStringHexDispHexType = "Hex Typ: " + hexToDisplay->getHexMatchfieldType();

    if(hexToDisplay->getUnit_stationed() != nullptr)
    {
        qStringUnitDispUnitName = "Name: " + hexToDisplay->getUnit_stationed()->getUnitName();
        qStringUnitDispUnitType = "Unit Typ: " + hexToDisplay->getUnit_stationed()->getUnitType();
        qStringUnitDispUnitLife = "HP: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitCurrentHP()) + "/"
                                            + QString::number(hexToDisplay->getUnit_stationed()->getUnitHP());
        if(hexToDisplay->getUnit_stationed()->getUnitMoveRange() > 0)
        {
            qStringUnitDispMovement = "MoveRange: " + QString::number(hexToDisplay->getUnit_stationed()->getUnitMoveRange()) + "/"
                    + QString::number(hexToDisplay->getUnit_stationed()->getUnitCurrentMoveRange());
        }else{
            qStringUnitDispMovement = "NONE";
        }
        if(hexToDisplay->getUnit_stationed()->getUnitAirAtt() == 0
                && hexToDisplay->getUnit_stationed()->getUnitGroundAtt() == 0
                && hexToDisplay->getUnit_stationed()->getUnitWaterAtt() == 0)
        {
            qStringUnitDispUnitAttack = "NONE";
        }else{
            qStringUnitDispUnitAttack = "Attack: A" + QString::number(hexToDisplay->getUnit_stationed()->getUnitAirAtt()) + "/"
                    + "G" + QString::number(hexToDisplay->getUnit_stationed()->getUnitGroundAtt()) + "/"
                    + "W" + QString::number(hexToDisplay->getUnit_stationed()->getUnitWaterAtt());
        }

    }else{
        qStringUnitDispUnitName = "";
        qStringUnitDispUnitType = "";
        qStringUnitDispUnitLife = "";
        qStringUnitDispMovement = "";
        qStringUnitDispUnitAttack = "";
    }
}

void UnitDisplayInfo::setColor(const QColor &value)
{
    color = value;
}

UnitDisplayInfo::UnitDisplayInfo(Unit *ptr_Unit)
    : QGraphicsRectItem(QRectF(-50,-50,230,100), 0), ptr_UnitToDisplay(ptr_Unit), color(Qt::black)
{
    updateText();
}

void UnitDisplayInfo::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    updateText();
    painter->drawPixmap(-50,-50, ptr_UnitToDisplay->pixmap());
    painter->drawText(QRectF(20,-50,200,20),qStringUnitDispUnitName);
    painter->drawText(QRectF(20,-30, 200,20),qStringUnitDispUnitType);
    painter->drawText(QRectF(20,-10,200,20),qStringUnitDispUnitLife);
    painter->drawText(QRectF(20,10,200,20),qStringUnitDispMovement);
    painter->drawText(QRectF(20,30,200,20),qStringUnitDispUnitAttack);

    painter->setPen(QPen(color));
    painter->drawRect(rect());

}

void UnitDisplayInfo::updateText()
{
    qStringUnitDispUnitName = "Name: " + ptr_UnitToDisplay->getUnitName();
    qStringUnitDispUnitType = "Typ: " + ptr_UnitToDisplay->getUnitType();
    qStringUnitDispUnitLife = "HP: " + QString::number(ptr_UnitToDisplay->getUnitCurrentHP()) + "/"
                                        + QString::number(ptr_UnitToDisplay->getUnitHP());
    qStringUnitDispMovement = "MoveRange: " + QString::number(ptr_UnitToDisplay->getUnitMoveRange()) + "/"
            + QString::number(ptr_UnitToDisplay->getUnitCurrentMoveRange());
    qStringUnitDispUnitAttack = "Attack: A" + QString::number(ptr_UnitToDisplay->getUnitAirAtt()) + "/"
            + "G" + QString::number(ptr_UnitToDisplay->getUnitGroundAtt()) + "/"
            + "W" + QString::number(ptr_UnitToDisplay->getUnitWaterAtt());
}

void UnitDisplayInfo::mousePressEvent(QGraphicsSceneMouseEvent*)
{
    color = Qt::red;
    setZValue(1);
    emit unitDispl_clicked(ptr_UnitToDisplay);
}
