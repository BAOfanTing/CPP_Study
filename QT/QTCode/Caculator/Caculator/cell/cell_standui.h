#ifndef CELL_STANDUI_H
#define CELL_STANDUI_H

#include <QMainWindow>
#include <QButtonGroup>>
#include <QDebug>
#include <QVector>
#include <QVariant>

namespace Ui {
class cell_Standui;
}

class cell_Standui : public QMainWindow
{
    Q_OBJECT

public:
    explicit cell_Standui(QWidget *parent = nullptr);
    ~cell_Standui();
    void initUI();

public slots:
    void onButtonGroupClicked(QAbstractButton* btn);

private:
    Ui::cell_Standui *ui;

    QVector<QVariant> vec;

    //记录上一个按钮的名字
    QString preBtn;
};

#endif // CELL_STANDUI_H
