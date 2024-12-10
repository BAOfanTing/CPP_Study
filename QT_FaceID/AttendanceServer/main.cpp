#include "attendancewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AttendanceWindow w;
    w.show();
    return a.exec();
}
