#include "QuicklySettings.h"
#include "mccdll.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
QuicklySettings::QuicklySettings(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	setHideButton();
	InitValue();
	connect(ui.left, &QPushButton::clicked, [this]() {
		int t =  ui.stackedWidget->currentIndex() - 1;
		ui.stackedWidget->setCurrentIndex(t);
		setHideButton();
	});
	connect(ui.right, &QPushButton::clicked, [this]() {
		int t = ui.stackedWidget->currentIndex() + 1;
		ui.stackedWidget->setCurrentIndex(t);
		setHideButton();
	});
	connect(ui.ok, &QPushButton::clicked, [this]() {
		SaveValue();
		hide();
	});

}

QuicklySettings::~QuicklySettings()
{
}

void QuicklySettings::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(83));
	ui.label_11->setText(TrLang::text(333));
	ui.label_29->setText(TrLang::text(334));
	ui.left->setText(TrLang::text(335));
	ui.right->setText(TrLang::text(336));
	ui.label_9->setText(TrLang::text(278));
	ui.label_30->setText(TrLang::text(310));
	ui.ok->setText(TrLang::text(109));
}

void QuicklySettings::InitValue()
{
	ui.ds0->setText(QString::number(mcc->GetParameterValue(320)));//x µÍËÙ
	ui.ds1->setText(QString::number(mcc->GetParameterValue(321)));
	ui.ds2->setText(QString::number(mcc->GetParameterValue(322)));
	ui.ds3->setText(QString::number(mcc->GetParameterValue(323)));
	ui.ds4->setText(QString::number(mcc->GetParameterValue(324)));
	ui.ds5->setText(QString::number(mcc->GetParameterValue(325)));
	ui.gs0->setText(QString::number(mcc->GetParameterValue(330)));//x ¸ßËÙ
	ui.gs1->setText(QString::number(mcc->GetParameterValue(331)));
	ui.gs2->setText(QString::number(mcc->GetParameterValue(332)));
	ui.gs3->setText(QString::number(mcc->GetParameterValue(333)));
	ui.gs4->setText(QString::number(mcc->GetParameterValue(334)));
	ui.gs5->setText(QString::number(mcc->GetParameterValue(335)));
	int i = 0;
	double js0 = mcc->GetParameterValue(380 + i) / (mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	double js1 = mcc->GetParameterValue(380 + i) / (mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	double js2 = mcc->GetParameterValue(380 + i) / (mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	double js3 = mcc->GetParameterValue(380 + i) / (mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	double js4 = mcc->GetParameterValue(380 + i) / (mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	double js5 = mcc->GetParameterValue(380 + i) / (mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i));
	ui.js0->setText(QString::number(js0));
	ui.js1->setText(QString::number(js1));
	ui.js2->setText(QString::number(js2));
	ui.js3->setText(QString::number(js3));
	ui.js4->setText(QString::number(js4));
	ui.js5->setText(QString::number(js5));

	i = 0;
	double mc0 = mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++);
	double mc1 = mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++);
	double mc2 = mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++);
	double mc3 = mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++);
	double mc4 = mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++);
	double mc5 = mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i);
	ui.mc0->setText(QString::number(mc0));
	ui.mc1->setText(QString::number(mc1));
	ui.mc2->setText(QString::number(mc2));
	ui.mc3->setText(QString::number(mc3));
	ui.mc4->setText(QString::number(mc4));
	ui.mc5->setText(QString::number(mc5));
}

void QuicklySettings::SaveValue()
{
	int i = 0;
	mcc->SetParameterValue(320 + i++, ui.ds0->text().toDouble());
	mcc->SetParameterValue(320 + i++, ui.ds1->text().toDouble());
	mcc->SetParameterValue(320 + i++, ui.ds2->text().toDouble());
	mcc->SetParameterValue(320 + i++, ui.ds3->text().toDouble());
	mcc->SetParameterValue(320 + i++, ui.ds4->text().toDouble());
	mcc->SetParameterValue(320 + i, ui.ds5->text().toDouble());
	i = 0;
	mcc->SetParameterValue(330 + i++, ui.gs0->text().toDouble());
	mcc->SetParameterValue(330 + i++, ui.gs1->text().toDouble());
	mcc->SetParameterValue(330 + i++, ui.gs2->text().toDouble());
	mcc->SetParameterValue(330 + i++, ui.gs3->text().toDouble());
	mcc->SetParameterValue(330 + i++, ui.gs4->text().toDouble());
	mcc->SetParameterValue(330 + i, ui.gs5->text().toDouble());
	i = 0;
	mcc->SetParameterValue(380 + i, ui.js0->text().toDouble()*mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	mcc->SetParameterValue(380 + i, ui.js1->text().toDouble()*mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	mcc->SetParameterValue(380 + i, ui.js2->text().toDouble()*mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	mcc->SetParameterValue(380 + i, ui.js3->text().toDouble()*mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	mcc->SetParameterValue(380 + i, ui.js4->text().toDouble()*mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i++));
	mcc->SetParameterValue(380 + i, ui.js5->text().toDouble()*mcc->GetParameterValue(110 + i) / mcc->GetParameterValue(120 + i));
	i = 0;
	mcc->SetParameterValue(110 + i, mcc->GetParameterValue(120 + i++) *ui.mc0->text().toDouble());
	mcc->SetParameterValue(110 + i, mcc->GetParameterValue(120 + i++) *ui.mc1->text().toDouble());
	mcc->SetParameterValue(110 + i, mcc->GetParameterValue(120 + i++) *ui.mc2->text().toDouble());
	mcc->SetParameterValue(110 + i, mcc->GetParameterValue(120 + i++) *ui.mc3->text().toDouble());
	mcc->SetParameterValue(110 + i, mcc->GetParameterValue(120 + i++) *ui.mc4->text().toDouble());
	mcc->SetParameterValue(110 + i, mcc->GetParameterValue(120 + i) *ui.mc5->text().toDouble());
}

void QuicklySettings::setHideButton()
{
	int t = ui.stackedWidget->count();
	int ct = ui.stackedWidget->currentIndex();
	if (ct == 0)
		ui.left->hide();
	else 
		ui.left->show();
	if (ct == t - 1)
		ui.right->hide(), ui.ok->show();
	else 
		ui.right->show(), ui.ok->hide();
	
}
