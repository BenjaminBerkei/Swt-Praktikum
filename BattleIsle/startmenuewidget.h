#ifndef STARTMENUEWIDGET_H
#define STARTMENUEWIDGET_H

#include <QMainWindow>

namespace Ui {
class StartMenueWidget;
}

class StartMenueWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartMenueWidget(QWidget *parent = 0);
    ~StartMenueWidget();

private:
    Ui::StartMenueWidget *ui;
};

#endif // STARTMENUEWIDGET_H
