/********************************************************************************
** Form generated from reading UI file 'startmenuewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENUEWIDGET_H
#define UI_STARTMENUEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenueWidget
{
public:
    QWidget *centralWidget;
    QPushButton *qbutton_startGame;
    QPushButton *qbutton_loadGame;
    QPushButton *qbutton_options;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *StartMenueWidget)
    {
        if (StartMenueWidget->objectName().isEmpty())
            StartMenueWidget->setObjectName(QStringLiteral("StartMenueWidget"));
        StartMenueWidget->resize(400, 300);
        centralWidget = new QWidget(StartMenueWidget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        qbutton_startGame = new QPushButton(centralWidget);
        qbutton_startGame->setObjectName(QStringLiteral("qbutton_startGame"));
        qbutton_startGame->setGeometry(QRect(150, 30, 88, 34));
        qbutton_loadGame = new QPushButton(centralWidget);
        qbutton_loadGame->setObjectName(QStringLiteral("qbutton_loadGame"));
        qbutton_loadGame->setGeometry(QRect(150, 80, 88, 34));
        qbutton_options = new QPushButton(centralWidget);
        qbutton_options->setObjectName(QStringLiteral("qbutton_options"));
        qbutton_options->setGeometry(QRect(150, 130, 88, 34));
        StartMenueWidget->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(StartMenueWidget);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 30));
        StartMenueWidget->setMenuBar(menuBar);
        mainToolBar = new QToolBar(StartMenueWidget);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        StartMenueWidget->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(StartMenueWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        StartMenueWidget->setStatusBar(statusBar);

        retranslateUi(StartMenueWidget);

        QMetaObject::connectSlotsByName(StartMenueWidget);
    } // setupUi

    void retranslateUi(QMainWindow *StartMenueWidget)
    {
        StartMenueWidget->setWindowTitle(QApplication::translate("StartMenueWidget", "StartMenueWidget", 0));
        qbutton_startGame->setText(QApplication::translate("StartMenueWidget", "Spiel starten", 0));
        qbutton_loadGame->setText(QApplication::translate("StartMenueWidget", "Spiel laden", 0));
        qbutton_options->setText(QApplication::translate("StartMenueWidget", "Optionen", 0));
    } // retranslateUi

};

namespace Ui {
    class StartMenueWidget: public Ui_StartMenueWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENUEWIDGET_H
