#include "DlgParamString.h"
#include"ReadIni.h"
#include "ncpod.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
DlgParamString::DlgParamString(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	
	setAttribute(Qt::WA_DeleteOnClose, true);
	ui.setupUi(this);
	setLine();
	show();
	ResetLanguage();
	connect(ui.bty, &QPushButton::clicked, [this]() {
		func();
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {

		close();
	}
	);

}

DlgParamString::~DlgParamString()
{
}

void DlgParamString::ResetLanguage()
{
	setDlgName(TrLang::text(122));
	ui.rb_Y->setText(TrLang::text(246));
	ui.rb_N->setText(TrLang::text(247));
	ui.bty->setText(TrLang::text(160));
	ui.btn->setText(TrLang::text(111));
}

void DlgParamString::func()
{
	if (mId == QStringLiteral("N11003"))
	{
		readIni.SetSureMsg(ui.rb_Y->isChecked());	
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N12004"))
	{
		if (ui.rb_Y->isChecked()) {
			readIni.SetUseFeedrate(true);
			//mcc->SetFeedrateMultiple(readIni.GetFeedrate().toInt());
		}
		else
		{
			readIni.SetUseFeedrate(false);
			//mcc->SetFeedrateMultiple(-1);
		}
		if (readIni.GetUseFeedrate()) {
			mcc->SetFeedrateMultiple(readIni.GetFeedrate().toInt());
		}
		else {
			mcc->SetFeedrateMultiple(-1);
		}
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N11015"))
	{
		if (ui.rb_Y->isChecked()) {
			readIni.SetIsCloseSpindle(true);
		}
		else
		{
			readIni.SetIsCloseSpindle(false);
		}
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N11016"))
	{
		if (ui.rb_Y->isChecked()) {
			readIni.SetIsOpenSpindle(true);
		}
		else
		{
			readIni.SetIsOpenSpindle(false);
		}
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N25004"))
	{
		if (ui.rb_Y->isChecked()) {
			readIni.SetLmtEnalbe(true);
			NcPod::getIns()->Set_SoftLmtEnalb(0,true);
		}
		else
		{
			readIni.SetLmtEnalbe(false);
			NcPod::getIns()->Set_SoftLmtEnalb(0,false);
		}
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N25031")) {
		if (ui.rb_Y->isChecked()) {
			readIni.SetXOriginLmt(true);
			NcPod::getIns()->SetHomeLmtE(0,0, 0,true);
		}
		else
		{
			readIni.SetXOriginLmt(false);
			NcPod::getIns()->SetHomeLmtE(0, 0,0,false);
		}
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N25032")) {
		if (ui.rb_Y->isChecked()) {
			readIni.SetYOriginLmt(true);
			NcPod::getIns()->SetHomeLmtE(0,1,1 ,true);
		}
		else
		{
			readIni.SetYOriginLmt(false);
			NcPod::getIns()->SetHomeLmtE(0,1,1, false);
		}
		emit  ChioceYes();
		close();
	}
	else if (mId == QStringLiteral("N25033")) {
		if (ui.rb_Y->isChecked()) {
			readIni.SetZOriginLmt(true);
			NcPod::getIns()->SetHomeLmtE(0,2, 2,true);
		}
		else
		{
			readIni.SetZOriginLmt(false);
			NcPod::getIns()->SetHomeLmtE(0,2,2, false);
		}
		emit  ChioceYes();
		close();
	}

}
