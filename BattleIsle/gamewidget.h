#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

namespace Ui {
class GameWidget;
}

class GameWidget : public QWidget
{
    Q_OBJECT
private:
    Ui::GameWidget *ui;

public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

signals:
    void SIGNAL_gameWidChangeIndexFromStack(int);
};

#endif // GAMEWIDGET_H
