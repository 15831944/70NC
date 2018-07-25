#include "ToolSetting.h"
#include "mccdll.h"
#include "commontools.h"
#include "ReadIni.h"
#include"LogManager.h"
#include "Samcon.h"
#include"IOSet.h"
#include "ncpod.h"
#include "Samcon.h"
#include "DlgWorkpieceOffset.h"
#include "TrLang.h"
#include "MccTools.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern Samcon *w;
extern bool isSimulation; //
ToolSetting::ToolSetting(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	init();
	InitKeyboardCtrl();
}
//G53
ToolSetting::~ToolSetting()
{
}

void ToolSetting::ResetLanguage()
{
	ui.groupBox->setTitle(TrLang::Ins()->GetText(172));
	ui.label->setText(TrLang::Ins()->GetText(173).arg("X"));
	ui.label_2->setText(TrLang::Ins()->GetText(173).arg("Y"));

	ui.label_3->setText(TrLang::Ins()->GetText(174));
	ui.label_4->setText(TrLang::Ins()->GetText(175));
	ui.label_6->setText(TrLang::Ins()->GetText(176));
	ui.label_7->setText(TrLang::Ins()->GetText(177));

	ui.label_5->setText(TrLang::Ins()->GetText(178)+"(mm)");
	ui.sava->setText(TrLang::Ins()->GetText(15));
	ui.btTool->setText(TrLang::Ins()->GetText(179));
	ui.btFTool->setText(TrLang::Ins()->GetText(180));
	ui.btMTool->setText(TrLang::Ins()->GetText(181));

}

void ToolSetting::DoMAutoToolSetting()
{
	static bool DoM6Over = false;
	static bool DoM930Over = false;
	static bool ToolSettingOver = false;
	static int ToolId = 1;
	if (SammonFunc::Getins()->autoToolSetting) {
		if (w->isMCode)return;
		if (!DoM6Over && !DoM930Over&&mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {
			w->isMCode = true;
			w->MCodeName = "6";
			NcPod::getIns()->newT = ToolId;
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
			DoM6Over = true;
			return;
		}

		if (DoM6Over && !DoM930Over&&mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {
			w->isMCode = true;
			w->MCodeName = "930";
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
			DoM930Over = true;
		}

		if (DoM6Over&&DoM930Over) {
			DoM6Over = false;
			DoM930Over = false;
			ToolId++;
		}
		if (ToolId > readIni.GetToolCount().toInt()) {
			SammonFunc::Getins()->autoToolSetting = false;
		}

	}
	else {
		DoM6Over = false;
		DoM930Over = false;
		ToolId = 1;
	}

}

void ToolSetting::zToolSetting()
{
	static QTime tsTime;
	static bool dingwei = false;
	static int i = 0;
	static bool ss = false;
	if (SammonFunc::isToolSetting) {
		if (ss&& mcc->GetGmode(11).toInt() != 4 && mcc->IniPnowFlg() == 0) {
			mcc->SetIniPnowFlg(1);
		}
		if (i++ <= 3)return;
		i = 0;
		double d = readIni.GetZToolSettingdistance().toDouble() + readIni.GetToolsThickness().toDouble();
		if (mcc->GetMachineCoordinate(2) <= readIni.GetMinimaZ().toDouble() && dingwei) {//到达Z最低距离
			LogManager::getIns()->appendLog(TrLang::Ins()->GetText(168));
			mcc->CancelSpeedControl(2);
			SammonFunc::isToolSetting = false;
			dingwei = false;
			ss = false;

			return;
		}
		if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !dingwei) {//到 对刀起始点
			QString str;
			str = str + "G53X" + readIni.GetFixedX() + "Y" + readIni.GetFixedY() + "Z" + readIni.GetStaetZ() + "F" + readIni.GetZToolSettingSpeed();
			MccTools::SendMDI(str);
			dingwei = true;
			return;
		}
		else if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !ss&&dingwei) {//开始对刀
			double mc = mcc->GetParameterValue(112) / mcc->GetParameterValue(122);
			double Zzuididian = readIni.GetMinimaZ().toDouble()*mc;
			double d = readIni.GetZToolSettingdistance().toDouble();
			ss = true;
			//	mcc->SetSpeedControl(2, readIni.GetZToolSettingSpeed().toInt());
			//	mcc->SetIniPnowFlg(3000);

			NcPod::getIns()->setHomeTyp(0, 2);
			NcPod::getIns()->Set_MoveSpee(0, 2, readIni.GetZToolSettingSpeed().toDouble()*mc / 60.0);
			NcPod::getIns()->SignalMov(0, 2, 4, Zzuididian, d*mc, 0);
			w->homeLmtFlag = 2;
		}
		else if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && ss&&dingwei) {//duidao完成
			ss = false;

			double zero = readIni.GetZToolSettingdistance().toDouble() + readIni.GetToolsThickness().toDouble();
			mcc->SetSeekZero(14, zero);
			SammonFunc::isToolSetting = false;
			dingwei = false;
			ss = false;
			mcc->SetIniPnowFlg(0);
			//mcc->CancelSpeedControl(2);
			w->pDlgWorkpieceOffset->SetWorkpiece(2, mcc->GetMachineCoordinate(2) - zero);

			return;
		}

	}
	else {
		dingwei = false;
		ss = false;
		i = 0;
	}

}

void ToolSetting::zFToolSetting()
{
	static QTime tsTime;
	static int i = 0;
	static bool ss = false;
	if (SammonFunc::isFToolSetting) {
		if (ss&& mcc->GetGmode(11).toInt() != 4 && mcc->IniPnowFlg() == 0) {
			mcc->SetIniPnowFlg(1);
		}
		if (i++ < 3)return;
		i = 0;
		double d = readIni.GetZToolSettingdistance().toDouble() + readIni.GetToolsThickness().toDouble();
		if (mcc->GetMachineCoordinate(2) <= readIni.GetMinimaZ().toDouble()) {//到达Z最低距离
			LogManager::getIns()->appendLog(TrLang::Ins()->GetText(168));
			mcc->CancelSpeedControl(2);
			SammonFunc::isFToolSetting = false;
			ss = false;

			return;
		}
		if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !ss) {//开始对刀
			double mc = mcc->GetParameterValue(112) / mcc->GetParameterValue(122);
			double Zzuididian = readIni.GetMinimaZ().toDouble()*mc;
			double d = readIni.GetZToolSettingdistance().toDouble();
			ss = true;
			//mcc->SetIniPnowFlg(3000);
			NcPod::getIns()->setHomeTyp(0, 2);
			NcPod::getIns()->Set_MoveSpee(0, 2, readIni.GetZToolSettingSpeed().toDouble()*mc / 60.0);
			//mcc->SetSpeedControl(2, readIni.GetZToolSettingSpeed().toInt());
			NcPod::getIns()->SignalMov(0, 2, 4, Zzuididian, d*mc, 0);
			w->homeLmtFlag = 2;
		}
		else if (/*mcc->IniPnowFlg() == 0 &&*/ mcc->GetGmode(11).toInt() == 4 && ss) {//duidao完成
			ss = false;

			double zero = readIni.GetZToolSettingdistance().toDouble() + readIni.GetToolsThickness().toDouble();
			mcc->SetSeekZero(14, zero);
			SammonFunc::isFToolSetting = false;
			ss = false;
			mcc->SetIniPnowFlg(0);
			//mcc->CancelSpeedControl(2);
			w->pDlgWorkpieceOffset->SetWorkpiece(2, mcc->GetMachineCoordinate(2) - zero);

			return;
		}
	}
	else {
		ss = false;
		i = 0;
	}
}
void ToolSetting::MySetFocus()
{
	ui.fixedX->setFocus();
}
bool ToolSetting::MyGetFocus()
{
	bool b1 = ui.fixedX->hasFocus();
	bool b2 = ui.fixedY->hasFocus();
	bool b3 = ui.startZ->hasFocus();
	bool b4 = ui.MinimaZ->hasFocus();
	bool b5 = ui.ZToolSettingSpeed->hasFocus();
	bool b6 = ui.GetToolsThickness->hasFocus();
	bool b7 = ui.ZToolSettingdistance->hasFocus();
	bool b8 = ui.sava->hasFocus();
	bool b9 = ui.btTool->hasFocus();
	bool b10 = ui.btFTool->hasFocus();
	return b1||b2||b3||b4||b5||b6||b7||b8||b9||b10||hasFocus();
}
#include<QDebug>
#include <QMargins>
void ToolSetting::resizeEvent(QResizeEvent * event)
{
	QWidget::resizeEvent(event);
}

bool ToolSetting::eventFilter(QObject * obj, QEvent * event)
{

	if (obj==this||
		obj == ui.fixedX ||
		obj == ui.fixedY ||
		obj == ui.startZ ||
		obj == ui.MinimaZ ||
		obj == ui.ZToolSettingSpeed ||
		obj == ui.GetToolsThickness ||
		obj == ui.ZToolSettingdistance ||
		obj == ui.sava ||
		obj == ui.btTool ||
		obj == ui.btFTool) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);

			if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.fixedX->hasFocus();
				bool b2 = ui.fixedY->hasFocus();
				bool b3 = ui.startZ->hasFocus();
				bool b4 = ui.MinimaZ->hasFocus();
				bool b5 = ui.ZToolSettingSpeed->hasFocus();
				bool b6 = ui.GetToolsThickness->hasFocus();
				bool b7 = ui.ZToolSettingdistance->hasFocus();
				bool b8 = ui.sava->hasFocus();
				bool b9 = ui.btTool->hasFocus();
				bool b10 = ui.btFTool->hasFocus();
				if (b1) {
					focusNextChild();
					ui.fixedY->setFocus();
				}
				else if (b2) {
					focusNextChild();
					ui.startZ->setFocus();

				}
				else if (b3) {
					focusNextChild();
					ui.MinimaZ->setFocus();
				}
				else if (b4) {
					focusNextChild();
					ui.ZToolSettingSpeed->setFocus();
				}
				else if (b5) {
					focusNextChild();
					ui.GetToolsThickness->setFocus();
				}
				else if (b6) {
					focusNextChild();
					ui.ZToolSettingdistance->setFocus();
				}
				else if (b7) {
					focusNextChild();
					ui.sava->setFocus();
				}
				else if (b8) {
					focusNextChild();
					ui.btTool->setFocus();
				}
				else if (b9) {
					focusNextChild();
					ui.btFTool->setFocus();
				}
				else if (b10) {
					focusNextChild();
					ui.fixedX->setFocus();
				}
				else if(hasFocus()){
					focusNextChild();
					ui.fixedX->setFocus();
				}
				else
				{
					focusNextChild();
				}
				return true;
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}

void ToolSetting::keyReleaseEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Return) {
		QWidget* w = focusWidget();
		QPushButton* btSub = dynamic_cast<QPushButton*>(w);
		if (btSub) {
			btSub->clicked(1);
		}
	}
	QLineEdit* le = dynamic_cast<QLineEdit*>(focusWidget());
	if (le)return;
	QWidget::keyReleaseEvent(event);
}

void ToolSetting::showEvent(QShowEvent * event)
{
	ui.GetToolsThickness->setText(readIni.GetToolsThickness());
}

void ToolSetting::init()
{
	ui.fixedX->setValidator(new QDoubleValidator());
	ui.fixedY->setValidator(new QDoubleValidator());
	ui.startZ->setValidator(new QDoubleValidator());
	ui.MinimaZ->setValidator(new QDoubleValidator());
	ui.ZToolSettingSpeed->setValidator(new QDoubleValidator());
	ui.GetToolsThickness->setValidator(new QDoubleValidator());
	ui.ZToolSettingdistance->setValidator(new QDoubleValidator());
	ui.fixedX->setText(readIni.GetFixedX());
	ui.fixedY->setText(readIni.GetFixedY());
	ui.startZ->setText(readIni.GetStaetZ());
	ui.MinimaZ->setText(readIni.GetMinimaZ());
	ui.ZToolSettingSpeed->setText(readIni.GetZToolSettingSpeed());
	ui.GetToolsThickness->setText(readIni.GetToolsThickness());
	ui.ZToolSettingdistance->setText(readIni.GetZToolSettingdistance());

	connect(ui.sava, &QPushButton::clicked, [this]() {//停止
		SammonFunc::isToolSetting = false;
		SammonFunc::isFToolSetting = false;
		if (SammonFunc::IsPause == false) {
			NcPod::getIns()->StopPMov(0, 2);
			if (w->isMCode) {
				w->isMCode = false;
				NcPod::getIns()->StopMacr(0);
				SammonFunc::SetSpeedControl_stop(isSimulation);
			}
			mcc->SetSpeedControl(2, 0);
		}

		NcPod::getIns()->SetHomeLmt();
	});

	connect(ui.btFTool, &QPushButton::clicked, [this]() {
		save();
		
		if (!(((Samcon*)parent())->GetIO()->CheckToolSetting())) {
			emit SammonFunc::Getins()->updateState("", TrLang::Ins()->GetText(169));//对刀禁用
			return;
		}		
		if (!SammonFunc::CanDoit())return;
		mcc->SetParameterValue(142, abs(readIni.GetZToolSettingSpeed().toDouble())*-1);
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(170), "");//对刀
		SammonFunc::isFToolSetting = true;
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(171));//浮动对刀
	});
	connect(ui.btTool, &QPushButton::clicked,  [this]() {
		//save
		save();
		if (!(((Samcon*)parent())->GetIO()->CheckToolSetting())) {
			emit SammonFunc::Getins()->updateState("", TrLang::Ins()->GetText(169));//对刀禁用
			return;
		}
		if (!SammonFunc::CanDoit())return;
		mcc->SetParameterValue(142, abs(readIni.GetZToolSettingSpeed().toDouble())*-1);
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(170), "");//对刀
		SammonFunc::isToolSetting = true;
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(170));//对刀
	});
	connect(ui.btMTool, &QPushButton::clicked, [this]() {
		save();
		if (!(((Samcon*)parent())->GetIO()->CheckToolSetting())) {
			emit SammonFunc::Getins()->updateState("", TrLang::Ins()->GetText(169));//对刀禁用
			return;
		}
		if (!SammonFunc::CanDoit())return;
		w->MCodeFromMDI = true;
		w->isMCode = true;
		w->MCodeName = "930";
		SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);

		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(170), "");//对刀
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(170));//对刀
	});
}

void ToolSetting::save()
{
	readIni.SetFixedX(ui.fixedX->text());
	readIni.SetFixedY(ui.fixedY->text());
	readIni.SetStaetZ(ui.startZ->text());
	readIni.SetMinimaZ(ui.MinimaZ->text());
	readIni.SetZToolSettingSpeed(ui.ZToolSettingSpeed->text());
	readIni.SetToolsThickness(ui.GetToolsThickness->text());
	readIni.SetZToolSettingdistance(ui.ZToolSettingdistance->text());
}

void ToolSetting::InitKeyboardCtrl()
{
	installEventFilter(this);
	ui.fixedX->installEventFilter(this);
	ui.fixedY->installEventFilter(this);
	ui.startZ->installEventFilter(this);
	ui.MinimaZ->installEventFilter(this);
	ui.ZToolSettingSpeed->installEventFilter(this);
	ui.GetToolsThickness->installEventFilter(this);
	ui.ZToolSettingdistance->installEventFilter(this);
	ui.sava->installEventFilter(this);
	ui.btTool->installEventFilter(this);
	ui.btFTool->installEventFilter(this);
}
