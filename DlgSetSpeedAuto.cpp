#include "DlgSetSpeedAuto.h"
#include"readini.h"
#include "CommonTools.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
DlgSetSpeedAuto::DlgSetSpeedAuto(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);

	setLine();
	ui.TiShi->setVisible(false);
	if (readIni.GetUseFeedrate()) {
		mcc->SetFeedrateMultiple(readIni.GetFeedrate().toInt());
	}
	else {
		mcc->SetFeedrateMultiple(-1);
	}
	
	char  str[20];
	sprintf(str, "%.3f", mcc->GetParameterValue(130));
	ui.lineEditLow->setText(str);
	ui.lineEditHigh->setText(readIni.GetFeedrate());

	ui.lineEditHigh->setValidator(new QDoubleValidator());
	ui.lineEditLow->setValidator(new QDoubleValidator());
	connect(ui.bty, &QPushButton::clicked, [this]() {

		if (ui.lineEditHigh->text().toInt()>=150&& ui.lineEditHigh->text().toInt() <= 20000)
		{

			int GJspeed = ui.lineEditHigh->text().toInt();
			mcc->SetFeedrateMultiple(GJspeed);//设置进给速度
			readIni.SetFeedrate(QString::number(GJspeed));
			mcc->SetParameterValue(105, (float)GJspeed*1.5);
			double v = ui.lineEditLow->text().toDouble();//G0速度，空程速度
			mcc->SetParameterValue(130,v);
			mcc->SetParameterValue(131, v);
			mcc->SetParameterValue(132, v);
			mcc->SetParameterValue(133, v);
			mcc->SetParameterValue(134, v);
			mcc->SetParameterValue(135, v);
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

	connect(ui.lineEditHigh, &QLineEdit::textChanged, [this]() {ui.TiShi->setVisible(false); });
	connect(ui.lineEditLow, &QLineEdit::textChanged, [this]() {ui.TiShi->setVisible(false); });
}

DlgSetSpeedAuto::~DlgSetSpeedAuto()
{
}

void DlgSetSpeedAuto::ResetLanguage()
{
	setDlgName(TrLang::text(350));

	ui.TiShi->setText(TrLang::text(349));
	ui.label_3->setText(TrLang::text(48));
	ui.label_4->setText(TrLang::text(254));


	ui.bty->setText(TrLang::text(160));
	ui.btn->setText(TrLang::text(111));
}

