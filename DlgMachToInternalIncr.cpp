#include "DlgMachToInternalIncr.h"
#include "ncpod.h"
#include"CommonTools.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;

DlgMachToInternalIncr::DlgMachToInternalIncr(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	Init();
}

DlgMachToInternalIncr::~DlgMachToInternalIncr()
{
}

void DlgMachToInternalIncr::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(81));//脉冲当量计算
	ui.radioButton->setText(TrLang::Ins()->GetText(234));
	ui.radioButton2->setText(TrLang::Ins()->GetText(235));
	ui.label_7->setText(TrLang::Ins()->GetText(236));
	ui.label->setText(TrLang::Ins()->GetText(237));
	ui.label_6->setText(TrLang::Ins()->GetText(238));
	ui.label_4->setText(TrLang::Ins()->GetText(241));
	ui.btclose->setText(TrLang::Ins()->GetText(222));
	ui.btbaocuncanshu->setText(TrLang::Ins()->GetText(242));

	if (!ui.radioButton->isChecked()) {
		ui.label_2->setText(TrLang::Ins()->GetText(243));//电子齿轮比
		ui.label_3->setText(TrLang::Ins()->GetText(244));//编码器分辨率
	}
	else {
		ui.label_2->setText(TrLang::Ins()->GetText(239));
		ui.label_3->setText(TrLang::Ins()->GetText(240));
	}
}

void DlgMachToInternalIncr::JiSuanMaiChongDangLiang()
{
	if (isEmpty())return;
	if (ui.radioButton2->isChecked()) {
		goto SiFuDianJi;
	}
BuJngDianJi:
	{
		double XingCheng = ui.lineEdit_luoju->text().toDouble();
		double bujingjiao = ui.lineEdit_bujingjiao->text().toDouble();
		double xifen = ui.lineEdit_xifen->text().toDouble();
		double jiansubi = ui.lineEdit_jiansubi->text().toDouble();
	
		double maichongdangliang = XingCheng / 360 * bujingjiao / xifen / jiansubi;
		ui.maichongdangliang->setText(QString("%1").arg(1 / maichongdangliang));
		return;
	}
SiFuDianJi:
	{
		double XingCheng = ui.lineEdit_luoju->text().toDouble();
		double jiansubi = ui.lineEdit_jiansubi->text().toDouble();
		double DiZiCiLunBi = ui.lineEdit_bujingjiao->text().toDouble();
		double BianMaQiFenBianLv = ui.lineEdit_xifen->text().toDouble();

		double maichongdangliang = DiZiCiLunBi / jiansubi*XingCheng / BianMaQiFenBianLv;
		ui.maichongdangliang->setText(QString("%1").arg(1 / maichongdangliang));
		return;
	}
}
void DlgMachToInternalIncr::Init() {
	connect(ui.btclose, &QPushButton::clicked, [this]() {
		close();
	});
	connect(ui.lineEdit_luoju, &QLineEdit::textChanged, [this]() {
		JiSuanMaiChongDangLiang();
	});

	connect(ui.lineEdit_bujingjiao, &QLineEdit::textChanged, [this]() {
		JiSuanMaiChongDangLiang();
	});
	connect(ui.lineEdit_xifen, &QLineEdit::textChanged, [this]() {
		JiSuanMaiChongDangLiang();
	});
	connect(ui.lineEdit_jiansubi, &QLineEdit::textChanged, [this]() {
		JiSuanMaiChongDangLiang();
	});
	connect(ui.btbaocuncanshu, &QPushButton::clicked, [this] {
		if (isEmpty())return;
		int Axisflag = ui.comboBox->currentIndex();
	
		NcPod::getIns()->Set_Steppe(0, 0+ Axisflag, ui.maichongdangliang->text().toDouble());
		mcc->SetParameterValue(110+ Axisflag, mcc->GetParameterValue(120+ Axisflag) *ui.maichongdangliang->text().toDouble());
	});

	connect(ui.comboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), [this](int idx) {
		if (idx > 2)
			ui.lineEdit_luoju->setText("360");
		JiSuanMaiChongDangLiang();
	});
	connect(ui.radioButton2, &QRadioButton::toggled, [this](bool b){
		JiSuanMaiChongDangLiang();
		if (b) {
			ui.label_2->setText(TrLang::Ins()->GetText(243));//电子齿轮比
			ui.label_3->setText(TrLang::Ins()->GetText(244));//编码器分辨率
		}
		else {
			ui.label_2->setText(TrLang::Ins()->GetText(239));
			ui.label_3->setText(TrLang::Ins()->GetText(240));
		}
	});
	ui.radioButton->setChecked(1);
}
