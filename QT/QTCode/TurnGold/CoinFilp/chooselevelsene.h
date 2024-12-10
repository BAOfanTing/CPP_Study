#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QPainter>
#include "MyPushButton.h"
class chooselevelsene  : public QMainWindow
{
	Q_OBJECT

public:
	chooselevelsene(QWidget *parent);
	~chooselevelsene();

	//ÖØÐ´»æÍ¼ÊÂ¼þ£¬»­±³¾°Í¼
	void paintEvent(QPaintEvent*);
};
