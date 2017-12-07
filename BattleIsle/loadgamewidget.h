/*
 * Author: Manuel
 * Version: 0.1
 * Datum 04.12.2017
 */

#ifndef LOADGAMEWIDGET_H
#define LOADGAMEWIDGET_H

#include <QWidget>

namespace Ui {
class LoadGameWidget;
}

class LoadGameWidget : public QWidget
{
    Q_OBJECT

private:
    Ui::LoadGameWidget *ui;

public:
    explicit LoadGameWidget(QWidget *parent = 0);
    ~LoadGameWidget();
    //void loadGame(SaveGame *saveGame_selection);
    void returnToStartMenue();

private slots:
    void on_qbutton_apply_clicked();
    void on_qbutton_cancel_clicked();

signals:
    void SIGNAL_loadGChangeIndexFromStack(int);
};

#endif // LOADGAMEWIDGET_H
