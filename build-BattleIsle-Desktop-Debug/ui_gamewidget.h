/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWIDGET_H
#define UI_GAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWidget
{
public:
    QGraphicsView *graphicsView_gameView;
    QGraphicsView *graphicsView_informationsView;
    QGraphicsView *graphicsView_optionsView;
    QGraphicsView *graphicsView_buttonView;

    void setupUi(QWidget *GameWidget)
    {
        if (GameWidget->objectName().isEmpty())
            GameWidget->setObjectName(QStringLiteral("GameWidget"));
        GameWidget->resize(1180, 720);
        graphicsView_gameView = new QGraphicsView(GameWidget);
        graphicsView_gameView->setObjectName(QStringLiteral("graphicsView_gameView"));
        graphicsView_gameView->setGeometry(QRect(10, 10, 911, 581));
        graphicsView_informationsView = new QGraphicsView(GameWidget);
        graphicsView_informationsView->setObjectName(QStringLiteral("graphicsView_informationsView"));
        graphicsView_informationsView->setGeometry(QRect(930, 10, 241, 161));
        graphicsView_optionsView = new QGraphicsView(GameWidget);
        graphicsView_optionsView->setObjectName(QStringLiteral("graphicsView_optionsView"));
        graphicsView_optionsView->setGeometry(QRect(930, 180, 241, 531));
        graphicsView_buttonView = new QGraphicsView(GameWidget);
        graphicsView_buttonView->setObjectName(QStringLiteral("graphicsView_buttonView"));
        graphicsView_buttonView->setGeometry(QRect(10, 600, 911, 111));

        retranslateUi(GameWidget);

        QMetaObject::connectSlotsByName(GameWidget);
    } // setupUi

    void retranslateUi(QWidget *GameWidget)
    {
        GameWidget->setWindowTitle(QApplication::translate("GameWidget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class GameWidget: public Ui_GameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
