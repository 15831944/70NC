#include "DlgFindText.h"
#include "TrLang.h"
DlgFindText::DlgFindText(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setDlgName(QStringLiteral("²éÕÒ"));
	setLine();
	ui.TiShi->setVisible(false);
	connect(ui.bty, &QPushButton::clicked, [this]() {
		emit findText(ui.lineEdit->text());
		
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {

		close();
	}
	);
	ui.TiShi->setVisible(false);
	connect(ui.lineEdit, &QLineEdit::textChanged, [this]() {
		ui.TiShi->setVisible(false);
	});
}

DlgFindText::~DlgFindText()
{
	
}

void DlgFindText::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(119));
	ui.btn->setText(TrLang::Ins()->GetText(111));
	ui.bty->setText(TrLang::Ins()->GetText(119));
	ui.label->setText(TrLang::Ins()->GetText(118));
	ui.TiShi->setText(TrLang::Ins()->GetText(120));
}

void DlgFindText::showEvent(QShowEvent * e)
{
	ui.lineEdit->setFocus();
}
