#include "DlgSetAxisSpeed.h"
#include"ReadIni.h"
#include "CommonTools.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
DlgSetAxisSpeed::DlgSetAxisSpeed(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);

	setLine();
	ui.TiShi->setVisible(0);
	ui.lineEdit->setValidator(new QDoubleValidator());

	ui.lineEdit->setText(QString::number(mcc->GetParameterValue(106)));
	connect(ui.bty, &QPushButton::clicked, [this]() {		
		if (SammonFunc::IsNumber(ui.lineEdit->text()))
		{
			mcc->SetParameterValue(106, ui.lineEdit->text().toDouble());
			//readIni.SetSpindleSpeed(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setVisible(true);
		}
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {

		close();
	}
	);
	connect(ui.lineEdit, &QLineEdit::textChanged, [this]() {ui.TiShi->setVisible(false); });
}

DlgSetAxisSpeed::~DlgSetAxisSpeed()
{
}

void DlgSetAxisSpeed::ResetLanguage()
{
	setDlgName(TrLang::text(351));
	ui.label->setText(TrLang::text(352));
	ui.bty->setText(TrLang::text(160));
	ui.btn->setText(TrLang::text(111));
}
