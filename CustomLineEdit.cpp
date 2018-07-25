#include "CustomLineEdit.h"

CustomLineEdit::CustomLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	ui.setupUi(this);
}

CustomLineEdit::~CustomLineEdit()
{
}

void CustomLineEdit::paintEvent(QPaintEvent * event)
{
	QFont ft;
	ft.setPointSize(height() / 4 >= 10 ? height() / 4 : 10);
	ft.setBold(1);
	setFont(ft);

	QLineEdit::paintEvent(event);
}
