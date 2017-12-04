/********************************************************************************
** Form generated from reading UI file 'optionswidget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONSWIDGET_H
#define UI_OPTIONSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWidget
{
public:
    QPushButton *qbutton_apply;
    QPushButton *qbutton_cancel;

    void setupUi(QWidget *OptionsWidget)
    {
        if (OptionsWidget->objectName().isEmpty())
            OptionsWidget->setObjectName(QStringLiteral("OptionsWidget"));
        OptionsWidget->resize(400, 300);
        qbutton_apply = new QPushButton(OptionsWidget);
        qbutton_apply->setObjectName(QStringLiteral("qbutton_apply"));
        qbutton_apply->setGeometry(QRect(100, 250, 88, 34));
        qbutton_cancel = new QPushButton(OptionsWidget);
        qbutton_cancel->setObjectName(QStringLiteral("qbutton_cancel"));
        qbutton_cancel->setGeometry(QRect(220, 250, 88, 34));

        retranslateUi(OptionsWidget);

        QMetaObject::connectSlotsByName(OptionsWidget);
    } // setupUi

    void retranslateUi(QWidget *OptionsWidget)
    {
        OptionsWidget->setWindowTitle(QApplication::translate("OptionsWidget", "Form", 0));
        qbutton_apply->setText(QApplication::translate("OptionsWidget", "Ok", 0));
        qbutton_cancel->setText(QApplication::translate("OptionsWidget", "Abbrechen", 0));
    } // retranslateUi

};

namespace Ui {
    class OptionsWidget: public Ui_OptionsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONSWIDGET_H
