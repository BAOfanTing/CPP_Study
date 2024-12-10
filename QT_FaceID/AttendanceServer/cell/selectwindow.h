#ifndef SELECTWINDOW_H
#define SELECTWINDOW_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class selectwindow;
}

class selectwindow : public QWidget
{
    Q_OBJECT

public:
    explicit selectwindow(QWidget *parent = nullptr);
    ~selectwindow();

private:
    Ui::selectwindow *ui;

    QSqlTableModel *model;
};

#endif // SELECTWINDOW_H
