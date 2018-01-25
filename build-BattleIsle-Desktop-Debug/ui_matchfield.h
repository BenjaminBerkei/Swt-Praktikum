/********************************************************************************
** Form generated from reading UI file 'matchfield.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATCHFIELD_H
#define UI_MATCHFIELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_Matchfield
{
public:
    QGraphicsView *graphicsView;
    QGraphicsView *graphicsView_2;

    void setupUi(QDialog *Matchfield)
    {
        if (Matchfield->objectName().isEmpty())
            Matchfield->setObjectName(QStringLiteral("Matchfield"));
        Matchfield->resize(648, 668);
        graphicsView = new QGraphicsView(Matchfield);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 651, 551));
        graphicsView_2 = new QGraphicsView(Matchfield);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setGeometry(QRect(0, 551, 651, 111));

        retranslateUi(Matchfield);

        QMetaObject::connectSlotsByName(Matchfield);
    } // setupUi

    void retranslateUi(QDialog *Matchfield)
    {
        Matchfield->setWindowTitle(QApplication::translate("Matchfield", "Matchfield", 0));
    } // retranslateUi

};

namespace Ui {
    class Matchfield: public Ui_Matchfield {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATCHFIELD_H
