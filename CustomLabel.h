#pragma once

#include <QLabel>
#include "ui_CustomLabel.h"

class CustomLabel : public QLabel
{
	Q_OBJECT

public:
	CustomLabel(QWidget *parent = Q_NULLPTR);
	~CustomLabel();
protected:
	void paintEvent(QPaintEvent * event);
private:
	Ui::CustomLabel ui;
};
