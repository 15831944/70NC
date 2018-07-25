#include "DlgRegSoft.h"
#include "ExternalText.h"
#include"CommonTools.h"
#include <QClipboard>
#include <qdebug>
extern mccdll::MotionControlCard* mcc;
DlgRegSoft::DlgRegSoft(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	setWindowOpacity(1);
	setLine();
	Init();
	LoadData();
}

DlgRegSoft::~DlgRegSoft()
{

}
void DlgRegSoft::TimeCheckReg()
{
	static int i = 7200 * 20-200;
	static int j = 7200 * 20;//两小时检测一次
	if (i++ <= j )
		return;
	i = 0;
	int k = mcc->GetGmode(14).toInt();
	if (k > 0 || k == -1) {
		SammonFunc::Getins()->isRegSoft = true;
		if (k > 0 && (GMode15Value.toInt() - k) <= 3) {
			emit SammonFunc::Getins()->ZhuCheKuaiDaoQi(ExternalText::ZHuCheDaoQi);
		}
	}
	else {
		SammonFunc::Getins()->isRegSoft = false;
		emit SammonFunc::Getins()->ZhuCheKuaiDaoQi(ExternalText::ZHuCheSiXiao);
	}
}
void DlgRegSoft::Init(){
	connect(ui.DlgC, &QPushButton::clicked, [this]() {
		close();
	});
	connect(ui.btclose, &QPushButton::clicked, [this]() {
		close();
	});
	QClipboard *clipboard = QGuiApplication::clipboard();
	connect(ui.btcopy, &QPushButton::clicked, [this, clipboard]() {
		QString str;
		str += "mode13:" + GMode13Value + "\n";
		str += "mode14:" + GMode14Value + "\n";
		str += "mode15:" + GMode15Value + "\n";
		str += "mode16:" + GMode16Value + "\n";
		clipboard->setText(str);
	});
	connect(ui.btwritein, &QPushButton::clicked, [this]() {
		QString str = ui.lineEdit->text();
		if (str == "")
			return;
		if (GMode14Value.toInt() == 0){
			mcc->SetParameter(501,0, str);
		}
		else {
			mcc->SetParameter(502, 0, str);
		}
		if (mcc->GetGmode(17).toInt() == 1)
			ui.TiShi_2->setText(QStringLiteral("写入成功，请重启"));
		else
			ui.TiShi_2->setText(QStringLiteral("写入失败"));
	});
	connect(ui.btwritein_jiesuo, &QPushButton::clicked, [this]() {
		QString str = ui.lineEdit_jiesuoma->text();
		if (str == "")
			return;
		mcc->SetParameter(503, 0, str);
		if (mcc->GetGmode(17).toInt() == 1)
			ui.TiShi_2->setText(QStringLiteral("写入成功，请重启"));
		else
			ui.TiShi_2->setText(QStringLiteral("写入失败"));
	});
}

void DlgRegSoft::LoadData() {
	GMode13Value = mcc->GetGmode(13);
	GMode14Value = mcc->GetGmode(14);
	GMode15Value = mcc->GetGmode(15);
	GMode16Value = mcc->GetGmode(16);

	int k = mcc->GetGmode(14).toInt();
	if (k > 0 || k == -1) {
		SammonFunc::Getins()->isRegSoft = true;
		if (k > 0 && (GMode15Value.toInt()- k) <= 3)
			emit SammonFunc::Getins()->ZhuCheKuaiDaoQi(ExternalText::ZHuCheDaoQi);
	}
	else {
		SammonFunc::Getins()->isRegSoft = false;
		emit SammonFunc::Getins()->ZhuCheKuaiDaoQi(ExternalText::ZHuCheSiXiao);
	}
}

void DlgRegSoft::showData()
{
	int gm14 = GMode14Value.toInt();
	if (gm14 == 0) {
		ui.TiShi->setText(ExternalText::GMode14Text0);
	}
	else if (gm14 == -1) {
		ui.TiShi->setText(ExternalText::GMode14Text1);
	}
	else if (gm14 == -2) {
		ui.TiShi->setText(ExternalText::GMode14Text2);
	}
	else if (gm14 == -3) {
		ui.TiShi->setText(ExternalText::GMode14Text3);
	}
	else if (gm14 >0) {
		ui.TiShi->setText(ExternalText::GMode14Text4.arg(gm14));
	}
	if (gm14 == 0) {
		ui.label_3->setText(QStringLiteral("注册码："));
		ui.btwritein->setText(QStringLiteral("写入注册码"));
	}
	else {
		ui.label_3->setText(QStringLiteral("延时码："));
		ui.btwritein->setText(QStringLiteral("写入延时码"));
	}

	ui.label_shijian->setText(GMode15Value);
	ui.label_jiqima->setText(GMode16Value.split("-")[0]);
}
