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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
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
    QWidget *centralWidget;
    QGraphicsView *hexfieldGraphic;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *spinBoxX;
    QLabel *label_2;
    QSpinBox *spinBoxY;
    QGraphicsView *menueView;
    QPushButton *HexMenueBut;
    QPushButton *UnitMenueBut;
    QPushButton *ResetButton;
    QSpinBox *spinBoltanium;
    QLabel *label_3;
    QPushButton *rotateLBut;
    QPushButton *rotateRBut;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1851, 1046);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        hexfieldGraphic = new QGraphicsView(centralWidget);
        hexfieldGraphic->setObjectName(QStringLiteral("hexfieldGraphic"));
        hexfieldGraphic->setGeometry(QRect(210, 0, 1641, 951));
        hexfieldGraphic->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 10, 101, 48));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        spinBoxX = new QSpinBox(layoutWidget);
        spinBoxX->setObjectName(QStringLiteral("spinBoxX"));

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBoxX);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBoxY = new QSpinBox(layoutWidget);
        spinBoxY->setObjectName(QStringLiteral("spinBoxY"));

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxY);

        menueView = new QGraphicsView(centralWidget);
        menueView->setObjectName(QStringLiteral("menueView"));
        menueView->setGeometry(QRect(10, 70, 191, 841));
        HexMenueBut = new QPushButton(centralWidget);
        HexMenueBut->setObjectName(QStringLiteral("HexMenueBut"));
        HexMenueBut->setGeometry(QRect(10, 920, 60, 30));
        UnitMenueBut = new QPushButton(centralWidget);
        UnitMenueBut->setObjectName(QStringLiteral("UnitMenueBut"));
        UnitMenueBut->setGeometry(QRect(80, 920, 60, 30));
        ResetButton = new QPushButton(centralWidget);
        ResetButton->setObjectName(QStringLiteral("ResetButton"));
        ResetButton->setGeometry(QRect(10, 960, 131, 31));
        spinBoltanium = new QSpinBox(centralWidget);
        spinBoltanium->setObjectName(QStringLiteral("spinBoltanium"));
        spinBoltanium->setGeometry(QRect(160, 960, 71, 31));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 960, 71, 31));
        label_3->setFont(font);
        rotateLBut = new QPushButton(centralWidget);
        rotateLBut->setObjectName(QStringLiteral("rotateLBut"));
        rotateLBut->setGeometry(QRect(320, 950, 75, 41));
        rotateRBut = new QPushButton(centralWidget);
        rotateRBut->setObjectName(QStringLiteral("rotateRBut"));
        rotateRBut->setGeometry(QRect(400, 950, 75, 41));
        MainWindow->setCentralWidget(centralWidget);
        menueView->raise();
        hexfieldGraphic->raise();
        layoutWidget->raise();
        HexMenueBut->raise();
        UnitMenueBut->raise();
        ResetButton->raise();
        spinBoltanium->raise();
        label_3->raise();
        rotateLBut->raise();
        rotateRBut->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1851, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "X", 0));
        label_2->setText(QApplication::translate("MainWindow", "Y", 0));
        HexMenueBut->setText(QApplication::translate("MainWindow", "Hexagon", 0));
        UnitMenueBut->setText(QApplication::translate("MainWindow", "Einheiten", 0));
        ResetButton->setText(QApplication::translate("MainWindow", "Reset", 0));
        label_3->setText(QApplication::translate("MainWindow", "Boltanium", 0));
        rotateLBut->setText(QApplication::translate("MainWindow", "<- Rotate", 0));
        rotateRBut->setText(QApplication::translate("MainWindow", "Rotate ->", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
