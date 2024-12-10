#ifndef CELL_MAIN_H
#define CELL_MAIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Cell_main;
}
QT_END_NAMESPACE

class Cell_main : public QMainWindow
{
    Q_OBJECT

public:
    Cell_main(QWidget *parent = nullptr);
    ~Cell_main();

private:
    Ui::Cell_main *ui;
};
#endif // CELL_MAIN_H
