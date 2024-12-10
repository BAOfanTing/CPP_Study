#include "smallWidget.h"

smallWidget::smallWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	//QspinxBox移动，QSlider跟着移动 查手册，没有就查父类
	connect(ui.spinBox,&QSpinBox::valueChanged,ui.horizontalSlider,&QSlider::setValue);
	//QSilder移动，QspinxBox跟着移动
	connect(ui.horizontalSlider, &QSlider::sliderMoved,ui.spinBox, &QSpinBox::setValue);
}

smallWidget::~smallWidget()
{}

void smallWidget::setNumber(int value)
{
	//设置值
	ui.spinBox->setValue(value);
}

int smallWidget::getNumber()
{
	//返回值
	return ui.spinBox->value();
}
