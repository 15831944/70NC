#pragma once

#include <QPushButton>
#include "ui_SCustomButton.h"
#include<qpainter>
class SCustomButton : public QPushButton
{
	Q_OBJECT

public:
	SCustomButton(QWidget *parent = Q_NULLPTR);
	~SCustomButton();
	void setURText(QString str) { mURText = str; }
	bool IsIOSet = false;
protected:
	void paintEvent(QPaintEvent *event);
private:
	QString mURText;
	QRectF mURRectF;
	Ui::SCustomButton ui;
	QPainter	mPainter;
	
};
