/********************************************************************************
** Form generated from reading UI file 'loadgamewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADGAMEWIDGET_H
#define UI_LOADGAMEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadGameWidget
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *label_LoadGame;
    QGroupBox *groupBox_saveGames;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget_saveGames;
    QHBoxLayout *horizontalLayout;
    QPushButton *qbutton_apply;
    QPushButton *qbutton_cancel;

    void setupUi(QWidget *LoadGameWidget)
    {
        if (LoadGameWidget->objectName().isEmpty())
            LoadGameWidget->setObjectName(QStringLiteral("LoadGameWidget"));
        LoadGameWidget->resize(380, 450);
        verticalLayout_2 = new QVBoxLayout(LoadGameWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_LoadGame = new QLabel(LoadGameWidget);
        label_LoadGame->setObjectName(QStringLiteral("label_LoadGame"));

        verticalLayout_2->addWidget(label_LoadGame);

        groupBox_saveGames = new QGroupBox(LoadGameWidget);
        groupBox_saveGames->setObjectName(QStringLiteral("groupBox_saveGames"));
        verticalLayout = new QVBoxLayout(groupBox_saveGames);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget_saveGames = new QListWidget(groupBox_saveGames);
        listWidget_saveGames->setObjectName(QStringLiteral("listWidget_saveGames"));

        verticalLayout->addWidget(listWidget_saveGames);

        listWidget_saveGames->raise();
        listWidget_saveGames->raise();

        verticalLayout_2->addWidget(groupBox_saveGames);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        qbutton_apply = new QPushButton(LoadGameWidget);
        qbutton_apply->setObjectName(QStringLiteral("qbutton_apply"));

        horizontalLayout->addWidget(qbutton_apply);

        qbutton_cancel = new QPushButton(LoadGameWidget);
        qbutton_cancel->setObjectName(QStringLiteral("qbutton_cancel"));

        horizontalLayout->addWidget(qbutton_cancel);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(LoadGameWidget);

        QMetaObject::connectSlotsByName(LoadGameWidget);
    } // setupUi

    void retranslateUi(QWidget *LoadGameWidget)
    {
        LoadGameWidget->setWindowTitle(QApplication::translate("LoadGameWidget", "Form", 0));
        label_LoadGame->setText(QApplication::translate("LoadGameWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:xx-large; font-weight:600;\">Spiel laden</span></p></body></html>", 0));
        groupBox_saveGames->setTitle(QApplication::translate("LoadGameWidget", "Gespeicherte Spiele", 0));
        qbutton_apply->setText(QApplication::translate("LoadGameWidget", "OK", 0));
        qbutton_cancel->setText(QApplication::translate("LoadGameWidget", "Abbrechen", 0));
    } // retranslateUi

};

namespace Ui {
    class LoadGameWidget: public Ui_LoadGameWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADGAMEWIDGET_H
