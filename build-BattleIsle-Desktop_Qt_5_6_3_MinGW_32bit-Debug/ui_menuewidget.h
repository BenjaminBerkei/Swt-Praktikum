/********************************************************************************
** Form generated from reading UI file 'menuewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUEWIDGET_H
#define UI_MENUEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenueWidget
{
public:
    QWidget *centralWidget;
    QStackedWidget *stack;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MenueWidget)
    {
        if (MenueWidget->objectName().isEmpty())
            MenueWidget->setObjectName(QStringLiteral("MenueWidget"));
        MenueWidget->resize(400, 500);
        centralWidget = new QWidget(MenueWidget);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        stack = new QStackedWidget(centralWidget);
        stack->setObjectName(QStringLiteral("stack"));
        stack->setGeometry(QRect(10, 0, 380, 450));
        MenueWidget->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MenueWidget);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 30));
        MenueWidget->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MenueWidget);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MenueWidget->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MenueWidget);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MenueWidget->setStatusBar(statusBar);

        retranslateUi(MenueWidget);

        QMetaObject::connectSlotsByName(MenueWidget);
    } // setupUi

    void retranslateUi(QMainWindow *MenueWidget)
    {
        MenueWidget->setWindowTitle(QApplication::translate("MenueWidget", "StartMenueWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MenueWidget: public Ui_MenueWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUEWIDGET_H
