#include "StyleDlg.h"

StyleDlg::StyleDlg(QWidget *parent)
	: label("Title"),bt("X"),QWidget(parent)
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setWindowOpacity(1);
	connect(&bt, &QPushButton::clicked, [this]() {	close();});
	label.setObjectName("DlgT");
	bt.setObjectName("DlgC");

}

StyleDlg::~StyleDlg()
{
}
