#ifndef MATCHFIELD_H
#define MATCHFIELD_H

#include <QDialog>

namespace Ui {
class Matchfield;
}

class Matchfield : public QDialog
{
    Q_OBJECT

public:
    explicit Matchfield(QWidget *parent = 0);
    ~Matchfield();

private:
    Ui::Matchfield *ui;
};

#endif // MATCHFIELD_H
