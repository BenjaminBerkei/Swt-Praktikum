/********************************************************************************
** Form generated from reading UI file 'gamewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameWidget
{
public:
    QGraphicsView *graphicsView_gameView;
    QGraphicsView *graphicsView_informationsView;
    QGraphicsView *graphicsView_optionsView;
    QGraphicsView *graphicsView_buttonView;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *labelPlayer;
    QLabel *labelPlayerCurrent;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelPhase;
    QLabel *labelPhaseCurrent;

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
        widget = new QWidget(GameWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 610, 151, 46));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        labelPlayer = new QLabel(widget);
        labelPlayer->setObjectName(QStringLiteral("labelPlayer"));

        horizontalLayout->addWidget(labelPlayer);

        labelPlayerCurrent = new QLabel(widget);
        labelPlayerCurrent->setObjectName(QStringLiteral("labelPlayerCurrent"));

        horizontalLayout->addWidget(labelPlayerCurrent);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        labelPhase = new QLabel(widget);
        labelPhase->setObjectName(QStringLiteral("labelPhase"));

        horizontalLayout_2->addWidget(labelPhase);

        labelPhaseCurrent = new QLabel(widget);
        labelPhaseCurrent->setObjectName(QStringLiteral("labelPhaseCurrent"));

        horizontalLayout_2->addWidget(labelPhaseCurrent);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(GameWidget);

        QMetaObject::connectSlotsByName(GameWidget);
    } // setupUi

    void retranslateUi(QWidget *GameWidget)
    {
        GameWidget->setWindowTitle(QApplication::translate("GameWidget", "Form", 0));
        labelPlayer->setText(QApplication::translate("GameWidget", "Player: ", 0));
        labelPlayerCurrent->setText(QString());
        labelPhase->setText(QApplication::translate("GameWidget", "Phase:", 0));
        labelPhaseCurrent->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameWidget: public Ui_GameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWIDGET_H
