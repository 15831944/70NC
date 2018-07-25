#include "MyCustomRadioButton.h"
#include "QPainter"
#include<qDebug>
MyCustomRadioButton::MyCustomRadioButton(QWidget *parent)
	: QRadioButton(parent)
{
	ui.setupUi(this);
}

MyCustomRadioButton::~MyCustomRadioButton()
{
}

void MyCustomRadioButton::paintEvent(QPaintEvent * event)
{
	QFont ft;
	ft.setPointSize(12);
	//ft.setBold(1);
	setFont(ft);
	
	QRadioButton::paintEvent(event);
}
