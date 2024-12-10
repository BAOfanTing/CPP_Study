#include "cell_main.h"

#include <QApplication>
#include "cell/cell_standui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Cell_main w;
    w.hide();

    cell_Standui standui;
    standui.show();

    return a.exec();
}
