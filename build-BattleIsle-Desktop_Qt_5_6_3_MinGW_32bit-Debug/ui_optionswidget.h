/********************************************************************************
** Form generated from reading UI file 'optionswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWIDGET_H
#define UI_OPTIONSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWidget
{
public:
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QGroupBox *groupBox_Opponent;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_human;
    QRadioButton *radioButton_computer;
    QGroupBox *groupBox_fogOfWar;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *radioButton_fogOfWarOn;
    QRadioButton *radioButton_fogOfWarOff;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_rounds;
    QComboBox *comboBox_rounds;
    QGroupBox *groupBox_maps;
    QVBoxLayout *verticalLayout_3;
    QListWidget *listWidget_maps;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *qbutton_apply;
    QPushButton *qbutton_cancel;

    void setupUi(QWidget *OptionsWidget)
    {
        if (OptionsWidget->objectName().isEmpty())
            OptionsWidget->setObjectName(QStringLiteral("OptionsWidget"));
        OptionsWidget->resize(380, 450);
        verticalLayout_4 = new QVBoxLayout(OptionsWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label = new QLabel(OptionsWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_4->addWidget(label);

        groupBox_Opponent = new QGroupBox(OptionsWidget);
        groupBox_Opponent->setObjectName(QStringLiteral("groupBox_Opponent"));
        verticalLayout = new QVBoxLayout(groupBox_Opponent);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        radioButton_human = new QRadioButton(groupBox_Opponent);
        radioButton_human->setObjectName(QStringLiteral("radioButton_human"));

        horizontalLayout->addWidget(radioButton_human);

        radioButton_computer = new QRadioButton(groupBox_Opponent);
        radioButton_computer->setObjectName(QStringLiteral("radioButton_computer"));

        horizontalLayout->addWidget(radioButton_computer);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_4->addWidget(groupBox_Opponent);

        groupBox_fogOfWar = new QGroupBox(OptionsWidget);
        groupBox_fogOfWar->setObjectName(QStringLiteral("groupBox_fogOfWar"));
        verticalLayout_2 = new QVBoxLayout(groupBox_fogOfWar);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        radioButton_fogOfWarOn = new QRadioButton(groupBox_fogOfWar);
        radioButton_fogOfWarOn->setObjectName(QStringLiteral("radioButton_fogOfWarOn"));

        horizontalLayout_2->addWidget(radioButton_fogOfWarOn);

        radioButton_fogOfWarOff = new QRadioButton(groupBox_fogOfWar);
        radioButton_fogOfWarOff->setObjectName(QStringLiteral("radioButton_fogOfWarOff"));

        horizontalLayout_2->addWidget(radioButton_fogOfWarOff);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_4->addWidget(groupBox_fogOfWar);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_rounds = new QLabel(OptionsWidget);
        label_rounds->setObjectName(QStringLiteral("label_rounds"));

        horizontalLayout_3->addWidget(label_rounds);

        comboBox_rounds = new QComboBox(OptionsWidget);
        comboBox_rounds->setObjectName(QStringLiteral("comboBox_rounds"));

        horizontalLayout_3->addWidget(comboBox_rounds);


        verticalLayout_4->addLayout(horizontalLayout_3);

        groupBox_maps = new QGroupBox(OptionsWidget);
        groupBox_maps->setObjectName(QStringLiteral("groupBox_maps"));
        verticalLayout_3 = new QVBoxLayout(groupBox_maps);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        listWidget_maps = new QListWidget(groupBox_maps);
        listWidget_maps->setObjectName(QStringLiteral("listWidget_maps"));

        verticalLayout_3->addWidget(listWidget_maps);


        verticalLayout_4->addWidget(groupBox_maps);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        qbutton_apply = new QPushButton(OptionsWidget);
        qbutton_apply->setObjectName(QStringLiteral("qbutton_apply"));

        horizontalLayout_4->addWidget(qbutton_apply);

        qbutton_cancel = new QPushButton(OptionsWidget);
        qbutton_cancel->setObjectName(QStringLiteral("qbutton_cancel"));

        horizontalLayout_4->addWidget(qbutton_cancel);


        verticalLayout_4->addLayout(horizontalLayout_4);

        qbutton_apply->raise();
        qbutton_cancel->raise();
        label->raise();
        groupBox_Opponent->raise();
        groupBox_fogOfWar->raise();
        comboBox_rounds->raise();
        label_rounds->raise();
        groupBox_maps->raise();
        groupBox_Opponent->raise();

        retranslateUi(OptionsWidget);

        QMetaObject::connectSlotsByName(OptionsWidget);
    } // setupUi

    void retranslateUi(QWidget *OptionsWidget)
    {
        OptionsWidget->setWindowTitle(QApplication::translate("OptionsWidget", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("OptionsWidget", "<html><head/><body><p align=\"center\"><span style=\" font-size:xx-large; font-weight:600;\">Optionen</span></p></body></html>", Q_NULLPTR));
        groupBox_Opponent->setTitle(QApplication::translate("OptionsWidget", "Gegner", Q_NULLPTR));
        radioButton_human->setText(QApplication::translate("OptionsWidget", "&Mensch", Q_NULLPTR));
        radioButton_computer->setText(QApplication::translate("OptionsWidget", "Computer", Q_NULLPTR));
        groupBox_fogOfWar->setTitle(QApplication::translate("OptionsWidget", "Fog of War", Q_NULLPTR));
        radioButton_fogOfWarOn->setText(QApplication::translate("OptionsWidget", "Ein", Q_NULLPTR));
        radioButton_fogOfWarOff->setText(QApplication::translate("OptionsWidget", "Aus", Q_NULLPTR));
        label_rounds->setText(QApplication::translate("OptionsWidget", "Runden:", Q_NULLPTR));
        comboBox_rounds->clear();
        comboBox_rounds->insertItems(0, QStringList()
         << QApplication::translate("OptionsWidget", "Kein Limit", Q_NULLPTR)
         << QApplication::translate("OptionsWidget", "4", Q_NULLPTR)
         << QApplication::translate("OptionsWidget", "8", Q_NULLPTR)
         << QApplication::translate("OptionsWidget", "16", Q_NULLPTR)
        );
        groupBox_maps->setTitle(QApplication::translate("OptionsWidget", "Karte", Q_NULLPTR));
        qbutton_apply->setText(QApplication::translate("OptionsWidget", "Ok", Q_NULLPTR));
        qbutton_cancel->setText(QApplication::translate("OptionsWidget", "Abbrechen", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OptionsWidget: public Ui_OptionsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWIDGET_H
