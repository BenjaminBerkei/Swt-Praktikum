/********************************************************************************
** Form generated from reading UI file 'startmenuewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTMENUEWIDGET_H
#define UI_STARTMENUEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartMenueWidget
{
public:
    QPushButton *qbutton_startGame;
    QPushButton *qbutton_loadGame;
    QPushButton *qbutton_options;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_opponent;
    QLabel *label_opponent_indication;
    QLabel *label_limit;
    QLabel *label_limit_indication;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_fogOfWar;
    QLabel *label_fogOfWar_indication;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_map;
    QLabel *label_map_indication;
    QLabel *label;

    void setupUi(QWidget *StartMenueWidget)
    {
        if (StartMenueWidget->objectName().isEmpty())
            StartMenueWidget->setObjectName(QStringLiteral("StartMenueWidget"));
        StartMenueWidget->resize(380, 450);
        qbutton_startGame = new QPushButton(StartMenueWidget);
        qbutton_startGame->setObjectName(QStringLiteral("qbutton_startGame"));
        qbutton_startGame->setGeometry(QRect(100, 60, 200, 50));
        qbutton_loadGame = new QPushButton(StartMenueWidget);
        qbutton_loadGame->setObjectName(QStringLiteral("qbutton_loadGame"));
        qbutton_loadGame->setGeometry(QRect(100, 120, 200, 50));
        qbutton_options = new QPushButton(StartMenueWidget);
        qbutton_options->setObjectName(QStringLiteral("qbutton_options"));
        qbutton_options->setGeometry(QRect(100, 180, 200, 50));
        groupBox = new QGroupBox(StartMenueWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 260, 361, 181));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 40, 321, 131));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_opponent = new QLabel(layoutWidget);
        label_opponent->setObjectName(QStringLiteral("label_opponent"));

        horizontalLayout->addWidget(label_opponent);

        label_opponent_indication = new QLabel(layoutWidget);
        label_opponent_indication->setObjectName(QStringLiteral("label_opponent_indication"));

        horizontalLayout->addWidget(label_opponent_indication);

        label_limit = new QLabel(layoutWidget);
        label_limit->setObjectName(QStringLiteral("label_limit"));

        horizontalLayout->addWidget(label_limit);

        label_limit_indication = new QLabel(layoutWidget);
        label_limit_indication->setObjectName(QStringLiteral("label_limit_indication"));

        horizontalLayout->addWidget(label_limit_indication);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_fogOfWar = new QLabel(layoutWidget);
        label_fogOfWar->setObjectName(QStringLiteral("label_fogOfWar"));

        horizontalLayout_2->addWidget(label_fogOfWar);

        label_fogOfWar_indication = new QLabel(layoutWidget);
        label_fogOfWar_indication->setObjectName(QStringLiteral("label_fogOfWar_indication"));

        horizontalLayout_2->addWidget(label_fogOfWar_indication);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_map = new QLabel(layoutWidget);
        label_map->setObjectName(QStringLiteral("label_map"));

        horizontalLayout_3->addWidget(label_map);

        label_map_indication = new QLabel(layoutWidget);
        label_map_indication->setObjectName(QStringLiteral("label_map_indication"));

        horizontalLayout_3->addWidget(label_map_indication);


        verticalLayout->addLayout(horizontalLayout_3);

        label = new QLabel(StartMenueWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 10, 271, 31));

        retranslateUi(StartMenueWidget);

        QMetaObject::connectSlotsByName(StartMenueWidget);
    } // setupUi

    void retranslateUi(QWidget *StartMenueWidget)
    {
        StartMenueWidget->setWindowTitle(QApplication::translate("StartMenueWidget", "Form", Q_NULLPTR));
        qbutton_startGame->setText(QApplication::translate("StartMenueWidget", "Spiel starten", Q_NULLPTR));
        qbutton_loadGame->setText(QApplication::translate("StartMenueWidget", "Spiel laden", Q_NULLPTR));
        qbutton_options->setText(QApplication::translate("StartMenueWidget", "Optionen", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("StartMenueWidget", "Eingestellte Optionen", Q_NULLPTR));
        label_opponent->setText(QApplication::translate("StartMenueWidget", "<strong>Gegner:</strong>", Q_NULLPTR));
        label_opponent_indication->setText(QApplication::translate("StartMenueWidget", "Mensch", Q_NULLPTR));
        label_limit->setText(QApplication::translate("StartMenueWidget", "<strong>Limit:</strong>", Q_NULLPTR));
        label_limit_indication->setText(QApplication::translate("StartMenueWidget", "Keines", Q_NULLPTR));
        label_fogOfWar->setText(QApplication::translate("StartMenueWidget", "<strong>Fog of War:</strong>", Q_NULLPTR));
        label_fogOfWar_indication->setText(QApplication::translate("StartMenueWidget", "Ein", Q_NULLPTR));
        label_map->setText(QApplication::translate("StartMenueWidget", "<strong>Karte:</strong>", Q_NULLPTR));
        label_map_indication->setText(QApplication::translate("StartMenueWidget", "Erste", Q_NULLPTR));
        label->setText(QApplication::translate("StartMenueWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:xx-large; font-weight:600;\">Battle Isle Clone</span></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class StartMenueWidget: public Ui_StartMenueWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTMENUEWIDGET_H
