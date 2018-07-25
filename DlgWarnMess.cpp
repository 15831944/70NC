#include "DlgWarnMess.h"
#include"CommonTools.h"
#include "TrLang.h"
extern QString MyStyle;
DlgWarnMess::DlgWarnMess(QString str,QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setStyleSheet(MyStyle);

	setLine();
	setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_DeleteOnClose, true);
	show();
	ui.btn->setFocus();
	connect(ui.btn, &QPushButton::clicked, [this]() {close();});
	ui.label->setText(str);
	ResetLanguage();
}

DlgWarnMess::~DlgWarnMess()
{

}

void DlgWarnMess::ResetLanguage()
{
	setDlgName(TrLang::text(353));
	ui.btn->setText(TrLang::text(222));
}

void DlgWarnMess::keyReleaseEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Return) {
		QWidget* w = focusWidget();
		QPushButton* btSub = dynamic_cast<QPushButton*>(w);
		if (btSub) {
			btSub->clicked(1);
		}
	}
	QWidget::keyReleaseEvent(event);
}
