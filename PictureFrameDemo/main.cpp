#include "mainwindow.h"

#include <QApplication>
#include<QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	auto t = new QTranslator(qApp);
	t->load(QApplication::applicationDirPath() + "./Translation_zh.qm");
	bool ret = qApp->installTranslator(t);

    MainWindow w;
    w.show();
    return a.exec();
	
}
