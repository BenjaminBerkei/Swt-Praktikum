/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNeue_Map;
    QAction *actionLoad_Map;
    QAction *actionSpeichern;
    QAction *actionSpeichernForBIC;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLCDNumber *lcdPlayer1;
    QLabel *UnitAnzlabel;
    QLCDNumber *lcdPlayer2;
    QPushButton *rotateRBut;
    QLCDNumber *lcdTotal;
    QLCDNumber *lcdBoltCach;
    QSpinBox *spinBoltanium;
    QPushButton *zoomOutBut;
    QGraphicsView *menueView;
    QLabel *labelY;
    QSpinBox *spinBoxY;
    QPushButton *deleteAllBut;
    QPushButton *setBoltButt;
    QGraphicsView *hexfieldGraphic;
    QPushButton *ResetButton;
    QPushButton *deleteBoltBut;
    QLabel *UnitAnzlabel_2;
    QLCDNumber *lcdBoltTotal;
    QPushButton *deleteAllBoltBut;
    QPushButton *getBoltButt;
    QLabel *boltCachLabel;
    QLabel *boltLabel;
    QPushButton *deleteBut;
    QPushButton *UnitMenueBut;
    QPushButton *HexMenueBut;
    QPushButton *rotateLBut;
    QHBoxLayout *horizontalLayout;
    QLabel *fillingText;
    QLabel *fillingLabel;
    QLabel *labelTotal;
    QLabel *Ply1label;
    QLabel *Ply2label;
    QPushButton *zoomINBut;
    QSpinBox *spinBoxX;
    QLabel *labelX;
    QMenuBar *menuBar;
    QMenu *menuDatei;
    QMenu *menuHilfe;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1366, 845);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionNeue_Map = new QAction(MainWindow);
        actionNeue_Map->setObjectName(QStringLiteral("actionNeue_Map"));
        actionLoad_Map = new QAction(MainWindow);
        actionLoad_Map->setObjectName(QStringLiteral("actionLoad_Map"));
        actionSpeichern = new QAction(MainWindow);
        actionSpeichern->setObjectName(QStringLiteral("actionSpeichern"));
        actionSpeichernForBIC = new QAction(MainWindow);
        actionSpeichernForBIC->setObjectName(QStringLiteral("actionSpeichernForBIC"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lcdPlayer1 = new QLCDNumber(centralWidget);
        lcdPlayer1->setObjectName(QStringLiteral("lcdPlayer1"));
        lcdPlayer1->setStyleSheet(QLatin1String("selection-color: rgb(0, 0, 255);\n"
"color: rgb(0, 0, 255);"));
        lcdPlayer1->setFrameShape(QFrame::NoFrame);
        lcdPlayer1->setFrameShadow(QFrame::Plain);
        lcdPlayer1->setLineWidth(1);
        lcdPlayer1->setMidLineWidth(0);
        lcdPlayer1->setSegmentStyle(QLCDNumber::Filled);

        gridLayout->addWidget(lcdPlayer1, 6, 12, 1, 1);

        UnitAnzlabel = new QLabel(centralWidget);
        UnitAnzlabel->setObjectName(QStringLiteral("UnitAnzlabel"));
        QFont font;
        font.setPointSize(12);
        UnitAnzlabel->setFont(font);
        UnitAnzlabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(UnitAnzlabel, 6, 10, 1, 1);

        lcdPlayer2 = new QLCDNumber(centralWidget);
        lcdPlayer2->setObjectName(QStringLiteral("lcdPlayer2"));
        lcdPlayer2->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(lcdPlayer2, 6, 13, 1, 1);

        rotateRBut = new QPushButton(centralWidget);
        rotateRBut->setObjectName(QStringLiteral("rotateRBut"));

        gridLayout->addWidget(rotateRBut, 6, 8, 1, 1);

        lcdTotal = new QLCDNumber(centralWidget);
        lcdTotal->setObjectName(QStringLiteral("lcdTotal"));
        lcdTotal->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(lcdTotal, 6, 11, 1, 1);

        lcdBoltCach = new QLCDNumber(centralWidget);
        lcdBoltCach->setObjectName(QStringLiteral("lcdBoltCach"));
        lcdBoltCach->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(lcdBoltCach, 6, 4, 1, 1);

        spinBoltanium = new QSpinBox(centralWidget);
        spinBoltanium->setObjectName(QStringLiteral("spinBoltanium"));

        gridLayout->addWidget(spinBoltanium, 6, 3, 1, 1);

        zoomOutBut = new QPushButton(centralWidget);
        zoomOutBut->setObjectName(QStringLiteral("zoomOutBut"));

        gridLayout->addWidget(zoomOutBut, 6, 14, 1, 1);

        menueView = new QGraphicsView(centralWidget);
        menueView->setObjectName(QStringLiteral("menueView"));
        menueView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);

        gridLayout->addWidget(menueView, 0, 0, 3, 2);

        labelY = new QLabel(centralWidget);
        labelY->setObjectName(QStringLiteral("labelY"));
        QFont font1;
        font1.setPointSize(10);
        labelY->setFont(font1);
        labelY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelY, 6, 15, 1, 1);

        spinBoxY = new QSpinBox(centralWidget);
        spinBoxY->setObjectName(QStringLiteral("spinBoxY"));

        gridLayout->addWidget(spinBoxY, 6, 16, 1, 1);

        deleteAllBut = new QPushButton(centralWidget);
        deleteAllBut->setObjectName(QStringLiteral("deleteAllBut"));

        gridLayout->addWidget(deleteAllBut, 6, 2, 1, 1);

        setBoltButt = new QPushButton(centralWidget);
        setBoltButt->setObjectName(QStringLiteral("setBoltButt"));

        gridLayout->addWidget(setBoltButt, 6, 5, 1, 1);

        hexfieldGraphic = new QGraphicsView(centralWidget);
        hexfieldGraphic->setObjectName(QStringLiteral("hexfieldGraphic"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hexfieldGraphic->sizePolicy().hasHeightForWidth());
        hexfieldGraphic->setSizePolicy(sizePolicy1);
        hexfieldGraphic->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        hexfieldGraphic->setMouseTracking(true);
        hexfieldGraphic->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        hexfieldGraphic->setResizeAnchor(QGraphicsView::AnchorViewCenter);

        gridLayout->addWidget(hexfieldGraphic, 0, 2, 3, 15);

        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QStringLiteral("ResetButton"));

        gridLayout->addWidget(ResetButton, 6, 0, 1, 1);

        deleteBoltBut = new QPushButton(centralWidget);
        deleteBoltBut->setObjectName(QStringLiteral("deleteBoltBut"));

        gridLayout->addWidget(deleteBoltBut, 5, 7, 1, 1);

        UnitAnzlabel_2 = new QLabel(centralWidget);
        UnitAnzlabel_2->setObjectName(QStringLiteral("UnitAnzlabel_2"));
        UnitAnzlabel_2->setFont(font1);

        gridLayout->addWidget(UnitAnzlabel_2, 5, 6, 1, 1);

        lcdBoltTotal = new QLCDNumber(centralWidget);
        lcdBoltTotal->setObjectName(QStringLiteral("lcdBoltTotal"));
        lcdBoltTotal->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(lcdBoltTotal, 6, 6, 1, 1);

        deleteAllBoltBut = new QPushButton(centralWidget);
        deleteAllBoltBut->setObjectName(QStringLiteral("deleteAllBoltBut"));

        gridLayout->addWidget(deleteAllBoltBut, 6, 7, 1, 1);

        getBoltButt = new QPushButton(centralWidget);
        getBoltButt->setObjectName(QStringLiteral("getBoltButt"));

        gridLayout->addWidget(getBoltButt, 5, 5, 1, 1);

        boltCachLabel = new QLabel(centralWidget);
        boltCachLabel->setObjectName(QStringLiteral("boltCachLabel"));
        boltCachLabel->setFont(font1);
        boltCachLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(boltCachLabel, 5, 4, 1, 1);

        boltLabel = new QLabel(centralWidget);
        boltLabel->setObjectName(QStringLiteral("boltLabel"));
        boltLabel->setFont(font1);

        gridLayout->addWidget(boltLabel, 5, 3, 1, 1);

        deleteBut = new QPushButton(centralWidget);
        deleteBut->setObjectName(QStringLiteral("deleteBut"));

        gridLayout->addWidget(deleteBut, 5, 2, 1, 1);

        UnitMenueBut = new QPushButton(centralWidget);
        UnitMenueBut->setObjectName(QStringLiteral("UnitMenueBut"));

        gridLayout->addWidget(UnitMenueBut, 5, 1, 1, 1);

        HexMenueBut = new QPushButton(centralWidget);
        HexMenueBut->setObjectName(QStringLiteral("HexMenueBut"));

        gridLayout->addWidget(HexMenueBut, 5, 0, 1, 1);

        rotateLBut = new QPushButton(centralWidget);
        rotateLBut->setObjectName(QStringLiteral("rotateLBut"));

        gridLayout->addWidget(rotateLBut, 5, 8, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fillingText = new QLabel(centralWidget);
        fillingText->setObjectName(QStringLiteral("fillingText"));
        fillingText->setFont(font);

        horizontalLayout->addWidget(fillingText);

        fillingLabel = new QLabel(centralWidget);
        fillingLabel->setObjectName(QStringLiteral("fillingLabel"));
        fillingLabel->setFont(font);

        horizontalLayout->addWidget(fillingLabel);


        gridLayout->addLayout(horizontalLayout, 5, 9, 1, 1);

        labelTotal = new QLabel(centralWidget);
        labelTotal->setObjectName(QStringLiteral("labelTotal"));
        labelTotal->setFont(font);
        labelTotal->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelTotal, 5, 11, 1, 1);

        Ply1label = new QLabel(centralWidget);
        Ply1label->setObjectName(QStringLiteral("Ply1label"));
        Ply1label->setFont(font);
        Ply1label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Ply1label, 5, 12, 1, 1);

        Ply2label = new QLabel(centralWidget);
        Ply2label->setObjectName(QStringLiteral("Ply2label"));
        Ply2label->setFont(font);
        Ply2label->setFrameShape(QFrame::NoFrame);
        Ply2label->setFrameShadow(QFrame::Plain);
        Ply2label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Ply2label, 5, 13, 1, 1);

        zoomINBut = new QPushButton(centralWidget);
        zoomINBut->setObjectName(QStringLiteral("zoomINBut"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(zoomINBut->sizePolicy().hasHeightForWidth());
        zoomINBut->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(zoomINBut, 5, 14, 1, 1);

        spinBoxX = new QSpinBox(centralWidget);
        spinBoxX->setObjectName(QStringLiteral("spinBoxX"));

        gridLayout->addWidget(spinBoxX, 5, 16, 1, 1);

        labelX = new QLabel(centralWidget);
        labelX->setObjectName(QStringLiteral("labelX"));
        labelX->setFont(font1);
        labelX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(labelX, 5, 15, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menueView->raise();
        hexfieldGraphic->raise();
        setBoltButt->raise();
        lcdBoltCach->raise();
        spinBoltanium->raise();
        rotateRBut->raise();
        UnitAnzlabel->raise();
        lcdTotal->raise();
        lcdPlayer1->raise();
        lcdPlayer2->raise();
        zoomOutBut->raise();
        labelY->raise();
        spinBoxY->raise();
        deleteAllBut->raise();
        ResetButton->raise();
        deleteBoltBut->raise();
        UnitAnzlabel_2->raise();
        lcdBoltTotal->raise();
        deleteAllBoltBut->raise();
        getBoltButt->raise();
        boltCachLabel->raise();
        boltLabel->raise();
        deleteBut->raise();
        UnitMenueBut->raise();
        HexMenueBut->raise();
        rotateLBut->raise();
        labelTotal->raise();
        Ply1label->raise();
        Ply2label->raise();
        zoomINBut->raise();
        spinBoxX->raise();
        labelX->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1366, 21));
        menuDatei = new QMenu(menuBar);
        menuDatei->setObjectName(QStringLiteral("menuDatei"));
        menuHilfe = new QMenu(menuBar);
        menuHilfe->setObjectName(QStringLiteral("menuHilfe"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuDatei->menuAction());
        menuBar->addAction(menuHilfe->menuAction());
        menuDatei->addAction(actionNeue_Map);
        menuDatei->addAction(actionLoad_Map);
        menuDatei->addSeparator();
        menuDatei->addAction(actionSpeichern);
        menuDatei->addAction(actionSpeichernForBIC);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Battle Isle MapEditor", 0));
        actionNeue_Map->setText(QApplication::translate("MainWindow", "&Neue Map", 0));
        actionLoad_Map->setText(QApplication::translate("MainWindow", "&Load Map", 0));
        actionSpeichern->setText(QApplication::translate("MainWindow", "&Speichern", 0));
        actionSpeichernForBIC->setText(QApplication::translate("MainWindow", "Speichern &f\303\274r Battle Isle Clone", 0));
        UnitAnzlabel->setText(QApplication::translate("MainWindow", "Unit Anzahl:", 0));
        rotateRBut->setText(QApplication::translate("MainWindow", "Rotate ->", 0));
        zoomOutBut->setText(QApplication::translate("MainWindow", "Zoom OUT", 0));
        labelY->setText(QApplication::translate("MainWindow", "Y:", 0));
        deleteAllBut->setText(QApplication::translate("MainWindow", "Entferne alle Einheiten", 0));
        setBoltButt->setText(QApplication::translate("MainWindow", "setze Boltanium", 0));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        deleteBoltBut->setText(QApplication::translate("MainWindow", "Entferne Boltanium", 0));
        UnitAnzlabel_2->setText(QApplication::translate("MainWindow", "Total Boltanium", 0));
        deleteAllBoltBut->setText(QApplication::translate("MainWindow", "Entferne alles Boltanium", 0));
        getBoltButt->setText(QApplication::translate("MainWindow", "speicher Boltanium", 0));
        boltCachLabel->setText(QApplication::translate("MainWindow", "Speicher", 0));
        boltLabel->setText(QApplication::translate("MainWindow", "Boltanium", 0));
        deleteBut->setText(QApplication::translate("MainWindow", "Entferne Einheit", 0));
        UnitMenueBut->setText(QApplication::translate("MainWindow", "Einheiten", 0));
        HexMenueBut->setText(QApplication::translate("MainWindow", "Hexagon", 0));
        rotateLBut->setText(QApplication::translate("MainWindow", "<- Rotate", 0));
        fillingText->setText(QApplication::translate("MainWindow", "Fill: ", 0));
        fillingLabel->setText(QString());
        labelTotal->setText(QApplication::translate("MainWindow", "Total", 0));
        Ply1label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#0000ff;\">Spieler 1</span></p></body></html>", 0));
        Ply2label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ff0000;\">Spieler 2</span></p></body></html>", 0));
        zoomINBut->setText(QApplication::translate("MainWindow", "Zoom IN", 0));
        labelX->setText(QApplication::translate("MainWindow", "X:", 0));
        menuDatei->setTitle(QApplication::translate("MainWindow", "&Datei", 0));
        menuHilfe->setTitle(QApplication::translate("MainWindow", "&Hilfe", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
