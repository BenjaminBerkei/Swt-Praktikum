#ifndef STARTMENUEWIDGET_H
#define STARTMENUEWIDGET_H

#include <QMainWindow>
#include "optionswidget.h"

class OptionsWidget;

namespace Ui {
class StartMenueWidget;
}

class StartMenueWidget : public QMainWindow
{
    Q_OBJECT
private:
    Ui::StartMenueWidget *ui;
    OptionsWidget *ptr_smwOptionsWidget;

public:
    explicit StartMenueWidget( QWidget *parent = 0 );
    ~StartMenueWidget();

    //void startGame(Options* options_initOptions);
    void switchToOptions();
    void switchToLoadGame();

private slots:
    void on_qbutton_startGame_clicked();
    void on_qbutton_loadGame_clicked();
    void on_qbutton_options_clicked();

};

#endif // STARTMENUEWIDGET_H
