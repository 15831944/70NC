#include "PasswordDlg.h"
#include "TrLang.h"
extern QString MyStyle;
PasswordDlg::PasswordDlg(int flag, QString leabel,QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
	setLine();
	setWindowModality(Qt::ApplicationModal);
	setStyleSheet(MyStyle);
	ui.TiShi->setVisible(0);
	ui.lineEdit->setEchoMode(QLineEdit::Password);
	connect(ui.bty, &QPushButton::clicked, [this]() {
		if (PwdFlag == DeveLoperPwd&&sDevelopPwd == ui.lineEdit->text()) {
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setVisible(true);
		}
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {

		close();
	}); 
	connect(ui.lineEdit, &QLineEdit::textChanged, [this]() {
		ui.TiShi->setVisible(false);
	});
	ui.lineEdit->installEventFilter(this);
	ui.bty->installEventFilter(this);
	ui.btn->installEventFilter(this);


	setDlgName(TrLang::Ins()->GetText(159));
	ui.bty->setText(TrLang::Ins()->GetText(160));
	ui.btn->setText(TrLang::Ins()->GetText(111));
	show(flag, leabel);
}

PasswordDlg::~PasswordDlg()
{

}

void PasswordDlg::show(int flag, QString leabel)
{
	ui.lineEdit->setFocus();
	ui.TiShi->setVisible(0);
	ui.lineEdit->clear();
	PwdFlag =(PassWordFlag) flag;
	ui.label->setText(leabel);
	QWidget::show();
}

bool PasswordDlg::eventFilter(QObject * obj, QEvent * event) {

	if (obj == ui.lineEdit ||
		obj == ui.bty ||
		obj == ui.btn) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Return|| key_event->key() == Qt::Key_Enter) {
				QWidget* w = focusWidget();
				QPushButton* btSub = dynamic_cast<QPushButton*>(w);
				if (btSub) {
					btSub->clicked(1);
				}
				else {
					ui.bty->clicked(1);
				}
				return 1;
			}
		}
	}
	return QWidget::eventFilter(obj, event);


}