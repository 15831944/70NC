#pragma once

#include <QRadioButton>
#include "ui_MyCustomRadioButton.h"

class MyCustomRadioButton : public QRadioButton
{
	Q_OBJECT

public:
	MyCustomRadioButton(QWidget *parent = Q_NULLPTR);
	~MyCustomRadioButton();
protected:
	void paintEvent(QPaintEvent *event);
private:
	Ui::MyCustomRadioButton ui;
};
