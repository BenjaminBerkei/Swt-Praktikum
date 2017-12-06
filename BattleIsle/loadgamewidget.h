#ifndef LOADGAMEWIDGET_H
#define LOADGAMEWIDGET_H

#include <QWidget>

namespace Ui {
class LoadGameWidget;
}

class LoadGameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadGameWidget(QWidget *parent = 0);
    ~LoadGameWidget();

private:
    Ui::LoadGameWidget *ui;
};

#endif // LOADGAMEWIDGET_H
