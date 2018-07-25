#include "SCustomButton.h"

SCustomButton::SCustomButton(QWidget *parent)
	: QPushButton(parent), mURRectF(4, 4, 12, 12)
{
	ui.setupUi(this);
}

SCustomButton::~SCustomButton()
{
}
void SCustomButton::paintEvent(QPaintEvent *event) {
	int k = 4;
	int MinSize = 14;
	if (IsIOSet) {
		k =5;
		MinSize = 12;
	}
	int pointSize = height() / k >= MinSize ? height() / k : MinSize;
	

	QPushButton::paintEvent(event);

	mPainter.begin(this);
	QFont ftru;
	ftru.setPointSize(pointSize*2/3);
	mPainter.setFont(ftru);
	mPainter.setPen(Qt::blue);
	mURRectF.setRect(4, 4, height() / 3, height() / 3);
	mPainter.drawText(mURRectF,mURText);
	mPainter.end(); 

	QFont ft;
	ft.setPointSize(pointSize);
	//ft.setBold(1);
	setFont(ft);
}