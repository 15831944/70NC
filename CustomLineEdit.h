#pragma once

#include <QLineEdit>
#include "ui_CustomLineEdit.h"

class CustomLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	CustomLineEdit(QWidget *parent = Q_NULLPTR);
	~CustomLineEdit();
protected:
	void paintEvent(QPaintEvent *event);
private:
	Ui::CustomLineEdit ui;
};
