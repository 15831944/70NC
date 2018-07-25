#include "CustomLabel.h"

CustomLabel::CustomLabel(QWidget *parent)
	: QLabel(parent)
{
	ui.setupUi(this);
}

CustomLabel::~CustomLabel()
{
}
void CustomLabel::paintEvent(QPaintEvent * event)
{
	QFont ft;
	ft.setPointSize(height() / 4 >= 14 ? height() / 4 : 14);
	ft.setBold(1);
	setFont(ft);

	QLabel::paintEvent(event);
}