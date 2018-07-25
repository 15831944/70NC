#include "ResetAxis.h"
#include"ReadIni.h"
#include"LogManager.h"
#include"ncpod.h"
#include "Samcon.h"
#include "ioset.h"
#include "ExternalText.h"
#include "CommonTools.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern int bMachineReturn;
extern ReadIni readIni;
extern Samcon* w;
ResetAxis::ResetAxis(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	
	connect(ui.YN_Y, &QPushButton::clicked, [this]() {
	
		bMachineReturn = 0;
		if(SammonFunc::IsPause == false) {

			NcPod::getIns()->StopPMov(0, 0);
			NcPod::getIns()->StopPMov(0, 1);
			NcPod::getIns()->StopPMov(0, 2);
			NcPod::getIns()->StopPMov(0, 3);
			NcPod::getIns()->StopPMov(0, 4);
			NcPod::getIns()->StopPMov(0, 5);
			if (w->isMCode) {
				w->isMCode = false;
				NcPod::getIns()->StopMacr(0);
				mcc->CancelSpeedControl(0);
				mcc->CancelSpeedControl(1);
				mcc->CancelSpeedControl(2);
				mcc->CancelSpeedControl(3);
				mcc->CancelSpeedControl(4);
				mcc->CancelSpeedControl(5);
			}

		}
		//close();	
	});
	connect(ui.close, &QPushButton::clicked, [this]() {
		SaveValue();
		close();
	});
	Init();
	SetValue();
	InitKeyboardCtrl();
}

ResetAxis::~ResetAxis()
{
}

void ResetAxis::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(78));//回机床原点
	QString s1, s2;
	s1 = TrLang::Ins()->GetText(212); //负方向
	s2 = TrLang::Ins()->GetText(213); //正方向
	ui.cbx->setItemText(0, s1);
	ui.cby->setItemText(0, s1);
	ui.cbz->setItemText(0, s1);
	ui.cba->setItemText(0, s1);
	ui.cbb->setItemText(0, s1);
	ui.cbc->setItemText(0, s1);

	ui.cbx->setItemText(1, s2);
	ui.cby->setItemText(1, s2);
	ui.cbz->setItemText(1, s2);
	ui.cba->setItemText(1, s2);
	ui.cbb->setItemText(1, s2);
	ui.cbc->setItemText(1, s2);

	ui.groupBox_2->setTitle(TrLang::Ins()->GetText(214));
	ui.groupBox_3->setTitle(TrLang::Ins()->GetText(215));
	ui.groupBox_4->setTitle(TrLang::Ins()->GetText(178));

	ui.BtResetM->setText(TrLang::Ins()->GetText(216));
	ui.BtResetAll->setText(TrLang::Ins()->GetText(217));
	ui.seekzero1->setText(TrLang::Ins()->GetText(218));
	ui.seekzero2->setText(TrLang::Ins()->GetText(219));
	ui.seekzero0->setText(TrLang::Ins()->GetText(220));
	ui.label_11->setText(TrLang::Ins()->GetText(221));
	ui.YN_Y->setText(TrLang::Ins()->GetText(15));
	ui.close->setText(TrLang::Ins()->GetText(222));


	ui.tishix->setText(TrLang::Ins()->GetText(18));
	ui.tishiy->setText(TrLang::Ins()->GetText(19));
	ui.tishiz->setText(TrLang::Ins()->GetText(20));
	ui.tishia->setText(TrLang::Ins()->GetText(21));
	ui.tishib->setText(TrLang::Ins()->GetText(223));
	ui.tishic->setText(TrLang::Ins()->GetText(224));

}

void ResetAxis::SHowTiShi()
{
	{
		ui.tishix->setVisible(!SammonFunc::XHoneEnabled);
		ui.tishiy->setVisible(!SammonFunc::YHoneEnabled);
		ui.tishiz->setVisible(!SammonFunc::ZHoneEnabled);
		ui.tishia->setVisible(!SammonFunc::AHoneEnabled);
		ui.tishib->setVisible(!SammonFunc::BHoneEnabled);
		ui.tishic->setVisible(!SammonFunc::CHoneEnabled);
	}
}

void ResetAxis::MachineReturn() {
	if (!isHidden() || bMachineReturn) {//ui上显示 限位信息
		w->GetIO()->CheckHome();
		SHowTiShi();
	}
	static int i = 0;
	if (bMachineReturn) {
		if (i++ <= 3)return;
		i = 0;
		if (mcc->GetGmode(11).toInt() == 3) {
			w->strstateLabel = ExternalText::XianWei;
			bMachineReturn = 0;
		}
		if (bMachineReturn == 1) {//z	
			if (SammonFunc::ZHoneEnabled)
				returnAxis(1, 8, 2, readIni.GetZRollbackdistance().toDouble(), 2);
			else {
				w->strstateLabelWarn = ExternalText::ZHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 2) {//x		
			if (SammonFunc::XHoneEnabled) {
				returnAxis(2, 6, 3, readIni.GetXRollbackdistance().toDouble(), 0);
			}
			else {
				w->strstateLabelWarn = ExternalText::XHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 3) {//y		
			if (SammonFunc::YHoneEnabled) {
				returnAxis(3, 7, 4, readIni.GetYRollbackdistance().toDouble(), 1);
			}
			else {
				w->strstateLabelWarn = ExternalText::YHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 4) {
			if (SammonFunc::AHoneEnabled) {
				returnAxis(4, 9, 0, readIni.GetARollbackdistance().toDouble(), 3);
			}
			else {
				w->strstateLabelWarn = ExternalText::AHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 11) {//;x	
			if (SammonFunc::XHoneEnabled) {
				returnAxis(11, 6, 0, readIni.GetXRollbackdistance().toDouble(), 0);
			}
			else {
				w->strstateLabelWarn = ExternalText::XHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 12) {//y

			if (SammonFunc::YHoneEnabled) {
				returnAxis(12, 7, 0, readIni.GetYRollbackdistance().toDouble(), 1);
			}
			else {
				w->strstateLabelWarn = ExternalText::YHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 13) {//z
			if (SammonFunc::ZHoneEnabled) {
				returnAxis(13, 8, 0, readIni.GetZRollbackdistance().toDouble(), 2);
			}
			else {
				w->strstateLabelWarn = ExternalText::ZHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 14) {//a		
			if (SammonFunc::AHoneEnabled) {
				returnAxis(14, 9, 0, readIni.GetARollbackdistance().toDouble(), 3);
			}
			else {
				w->strstateLabelWarn = ExternalText::AHomeEnabled;
				bMachineReturn = 0;
			}
		}
		else 	if (bMachineReturn == 15) {//b		
			if (SammonFunc::AHoneEnabled) {
				returnAxis(15, 10, 0, readIni.GetARollbackdistance().toDouble(), 4);
			}
		}
		else 	if (bMachineReturn == 16) {//c		
			if (SammonFunc::AHoneEnabled) {
				returnAxis(16, 11, 0, readIni.GetARollbackdistance().toDouble(), 5);
			}
		}
	}
	else {
		returnAxis(0, 0, 0, 0, 0);
		i = 0;
	}
}

void ResetAxis::returnAxis(int MachineReturn, int returnAxis, int nextMachineReturn, double returnLen, int clearAxis) {
	static bool s = false;

	if (MachineReturn == 0) { //防止 急停时 s 未重制
		s = false;
		return;
	}
	double zero = 0;

	if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !s) {

		NcPod::getIns()->setHomeTyp(1, readIni.GetSeekZeroOpt());
		mcc->SetSeekZero(returnAxis, returnLen);
		s = true;
	}
	else if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && s) {
		s = false;
		mcc->SetSeekZero(clearAxis, zero);
		bMachineReturn = nextMachineReturn;
	}
}

void ResetAxis::ncpodRefer(int num)
{
	switch (num)
	{
	case 0:ui.BtResetX->click();
		break;
	case 1:ui.BtResetY->click();
		break;
	case 2:ui.BtResetZ->click();
		break;
	case 3:ui.BtResetA->click();
		break;
	case 4:ui.BtResetB->click();
		break;
	case 5:ui.BtResetC->click();
		break;
	}
}

void ResetAxis::showEvent(QShowEvent * event)
{
	ui.cbx->setFocus();
}

bool ResetAxis::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == this ||
		obj == ui.YN_Y ||
		obj == ui.close ||
		obj == ui.cbx ||
		obj == ui.cby ||
		obj == ui.cbz ||
		obj == ui.cba || 
		obj == ui.cbb ||
		obj == ui.cbc ||
		obj == ui.lex ||
		obj == ui.ley ||
		obj == ui.lez ||
		obj == ui.lea ||
		obj == ui.leb ||
		obj == ui.lec ||
		obj == ui.distX ||
		obj == ui.distY ||
		obj == ui.distZ ||
		obj == ui.dista ||
		obj == ui.distb ||
		obj == ui.distc ||
		obj == ui.BtResetAll ||
		obj == ui.BtResetZ ||
		obj == ui.BtResetX ||
		obj == ui.BtResetY ||
		obj == ui.BtResetB ||
		obj == ui.BtResetC ||
		obj == ui.BtResetA) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Return|| key_event->key() == Qt::Key_Enter) {
				QWidget* w = focusWidget();
				QPushButton* btSub = dynamic_cast<QPushButton*>(w);
				if (btSub) {
					btSub->clicked(1);
				}
				return 1;
			}
			if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.cbx->hasFocus();
				bool b2 = ui.cby->hasFocus();
				bool b3 = ui.cbz->hasFocus();
				bool b4 = ui.cba->hasFocus();
				bool b4_1 = ui.cbb->hasFocus();
				bool b4_2 = ui.cbc->hasFocus();

				bool b5 = ui.lex->hasFocus();
				bool b6 = ui.ley->hasFocus();
				bool b7 = ui.lez->hasFocus();
				bool b8 = ui.lea->hasFocus();
				bool b8_1 = ui.leb->hasFocus();
				bool b8_2 = ui.lec->hasFocus();

				bool b9 = ui.distX->hasFocus();
				bool b10 = ui.distY->hasFocus();
				bool b11= ui.distZ->hasFocus();
				bool b12 = ui.dista->hasFocus();
				bool b12_1 = ui.distb->hasFocus();
				bool b12_2 = ui.distc->hasFocus();

				bool b13 = ui.BtResetAll->hasFocus();

				bool b14= ui.BtResetZ->hasFocus();
				bool b15 = ui.BtResetX->hasFocus();
				bool b16 = ui.BtResetY->hasFocus();
				bool b17 = ui.BtResetA->hasFocus();
				bool b17_1 = ui.BtResetB->hasFocus();
				bool b17_2 = ui.BtResetC->hasFocus();

				bool b18=ui.YN_Y->hasFocus();
				bool b19=ui.close->hasFocus();
				if (b1) {
					focusNextChild();
					ui.cby->setFocus();
				}
				else if (b2) {
					focusNextChild();
					ui.cbz->setFocus();

				}
				else if (b3) {
					focusNextChild();
					ui.cba->setFocus();
				}
				else if (b4) {
					focusNextChild();
					if(!is6Axis)
						ui.lex->setFocus();
					else
						ui.cbb->setFocus();
				}
				else if (b4_1) {
					focusNextChild();
					ui.cbc->setFocus();
				}
				else if (b4_2) {
					focusNextChild();
					ui.lex->setFocus();
				}
				else if (b5) {
					focusNextChild();
					ui.ley->setFocus();
				}
				else if (b6) {
					focusNextChild();
					ui.lez->setFocus();
				}
				else if (b7) {
					focusNextChild();
					ui.lea->setFocus();
				}
				else if (b8) {
					focusNextChild();
					if (!is6Axis)
						ui.distX->setFocus();
					else
						ui.leb->setFocus();
				}
				else if (b8_1) {
					focusNextChild();
					ui.lec->setFocus();
				}
				else if (b8_2) {
					focusNextChild();
					ui.distX->setFocus();
				}
				else if (b9) {
					focusNextChild();
					ui.distY->setFocus();
				}
				else if (b10) {
					focusNextChild();
					ui.distZ->setFocus();
				}
				else if (b11) {
					focusNextChild();
					ui.dista->setFocus();
				}
				else if (b12) {
					focusNextChild();
					focusNextChild();
					if (!is6Axis)
						ui.BtResetAll->setFocus();
					else			
						ui.distb->setFocus();
				}
				else if (b12_1) {
					focusNextChild();
					ui.distc->setFocus();
				}
				else if (b12_2) {
					focusNextChild();
					ui.BtResetAll->setFocus();
				}
				else if (b13) {
					focusNextChild();
					ui.BtResetZ->setFocus();
				}
				else if (b14) {
					focusNextChild();
					ui.BtResetX->setFocus();
				}
				else if (b15) {
					focusNextChild();
					ui.BtResetY->setFocus();
				}
				else if (b16) {
					focusNextChild();
					ui.BtResetA->setFocus();
				}
				else if (b17) {
					focusNextChild();
					if (!is6Axis)
						ui.YN_Y->setFocus();
					else
						ui.BtResetB->setFocus();
				}
				else if (b17_1) {
					focusNextChild();
					ui.BtResetC->setFocus();
				}
				else if (b17_2) {
					focusNextChild();
					ui.YN_Y->setFocus();
				}
				else if (b18) {
					focusNextChild();
					ui.close->setFocus();
				}
				else if (b19) {
					focusNextChild();
					ui.cbx->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					ui.cbx->setFocus();
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


void ResetAxis::keyReleaseEvent(QKeyEvent * event)
{

	QWidget::keyReleaseEvent(event);
	
}

void ResetAxis::SetValue()
{
	ui.distX->setValidator(new QDoubleValidator());
	ui.distY->setValidator(new QDoubleValidator());
	ui.distZ->setValidator(new QDoubleValidator());
	ui.dista->setValidator(new QDoubleValidator());
	ui.distb->setValidator(new QDoubleValidator());
	ui.distc->setValidator(new QDoubleValidator());
	ui.lex->setValidator(new QDoubleValidator());
	ui.ley->setValidator(new QDoubleValidator());
	ui.lez->setValidator(new QDoubleValidator());
	ui.lea->setValidator(new QDoubleValidator());
	ui.leb->setValidator(new QDoubleValidator());
	ui.lec->setValidator(new QDoubleValidator());

	int vx = mcc->GetParameterValue(140);
	int vy = mcc->GetParameterValue(141);
	//int vz = mcc->GetParameterValue(142);
	int vz = readIni.GetZReturnSpeed().toDouble();
	int va = mcc->GetParameterValue(143);
	int vb = mcc->GetParameterValue(144);
	int vc = mcc->GetParameterValue(145);

	ui.cbx->setCurrentIndex(vx>0 ? 1 : 0);
	ui.cby->setCurrentIndex(vy>0 ? 1 : 0);
	ui.cbz->setCurrentIndex(vz>0 ? 1 : 0);
	ui.cba->setCurrentIndex(va>0 ? 1 : 0);
	ui.cbb->setCurrentIndex(vb>0 ? 1 : 0);
	ui.cbc->setCurrentIndex(vc>0 ? 1 : 0);

	ui.lex->setText(QString::number(abs(vx)));
	ui.ley->setText(QString::number(abs(vy)));
	ui.lez->setText(QString::number(abs(vz)));
	ui.lea->setText(QString::number(abs(va)));
	ui.leb->setText(QString::number(abs(vb)));
	ui.lec->setText(QString::number(abs(vc)));

	ui.distX->setText(readIni.GetXRollbackdistance());
	ui.distY->setText(readIni.GetYRollbackdistance());
	ui.distZ->setText(readIni.GetZRollbackdistance());
	ui.dista->setText(readIni.GetARollbackdistance());
	ui.distb->setText(readIni.GetBRollbackdistance());
	ui.distc->setText(readIni.GetCRollbackdistance());

}

void ResetAxis::SaveValue()
{
	float vx, vy, vz,va,vb,vc;
	vx = abs(ui.lex->text().toFloat());
	vy = abs(ui.ley->text().toFloat());
	vz = abs(ui.lez->text().toFloat());
	va = abs(ui.lea->text().toFloat());
	vb = abs(ui.leb->text().toFloat());
	vc = abs(ui.lec->text().toFloat());

	if (ui.cbx->currentIndex() == 0)
		vx = vx *(-1);
	if (ui.cby->currentIndex() == 0)
		vy = (vy) *(-1);
	if (ui.cbz->currentIndex() == 0)
		vz = (vz) *(-1);
	if (ui.cba->currentIndex() == 0)
		va = (va) *(-1);
	if (ui.cbb->currentIndex() == 0)
		vb = (vb) *(-1);
	if (ui.cbc->currentIndex() == 0)
		vc = (vc) *(-1);
	mcc->SetParameterValue(140, vx);
	mcc->SetParameterValue(141, vy);
	mcc->SetParameterValue(142, vz);
	mcc->SetParameterValue(143, va);
	mcc->SetParameterValue(144, vb);
	mcc->SetParameterValue(145, vc);
	readIni.SetZReturnSpeed(QString::number(vz));

	readIni.SetXRollbackdistance(ui.distX->text());
	readIni.SetYRollbackdistance(ui.distY->text());
	readIni.SetZRollbackdistance(ui.distZ->text());
	readIni.SetARollbackdistance(ui.dista->text());
	readIni.SetBRollbackdistance(ui.distb->text());
	readIni.SetCRollbackdistance(ui.distc->text());
}

void ResetAxis::InitKeyboardCtrl()
{
	installEventFilter(this);
	ui.cbx->installEventFilter(this);
	ui.cby->installEventFilter(this);
	ui.cbz->installEventFilter(this);
	ui.cba->installEventFilter(this);
	ui.cbb->installEventFilter(this);
	ui.cbc->installEventFilter(this);

	ui.lex->installEventFilter(this);
	ui.ley->installEventFilter(this);
	ui.lez->installEventFilter(this);
	ui.lea->installEventFilter(this);
	ui.leb->installEventFilter(this);
	ui.lec->installEventFilter(this);

	ui.distX->installEventFilter(this);
	ui.distY->installEventFilter(this);
	ui.distZ->installEventFilter(this);
	ui.dista->installEventFilter(this);
	ui.distb->installEventFilter(this);
	ui.distc->installEventFilter(this);

	ui.BtResetAll->installEventFilter(this);

	ui.BtResetZ->installEventFilter(this);
	ui.BtResetX->installEventFilter(this);
	ui.BtResetY->installEventFilter(this);
	ui.BtResetA->installEventFilter(this);
	ui.BtResetB->installEventFilter(this);
	ui.BtResetC->installEventFilter(this);
	ui.YN_Y->installEventFilter(this);
	ui.close->installEventFilter(this);
}

void ResetAxis::Init()
{
	connect(ui.seekzero0, &QRadioButton::clicked, [this]() {
		readIni.SetSeekZeroOpt(0);
	});
	connect(ui.seekzero1, &QRadioButton::clicked, [this]() {
		readIni.SetSeekZeroOpt(1);
	});
	connect(ui.seekzero2, &QRadioButton::clicked, [this]() {
		readIni.SetSeekZeroOpt(2);
	});
	switch (readIni.GetSeekZeroOpt())
	{
	case 0:
		ui.seekzero0->setChecked(1);
		break;
	case 1:
		ui.seekzero1->setChecked(1);
		break;
	case 2:
		ui.seekzero2->setChecked(1);
		break;
	}
	connect(ui.BtResetX, &QPushButton::clicked, [this]() {
		
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() == 0) {
			double zero = 0;
			mcc->SetSeekZero(0, zero);
			return;
		}
		if(!bMachineReturn)
		bMachineReturn = 11;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), ""); //回机床原点
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":X");//回机床原点:X
	});
	connect(ui.BtResetY, &QPushButton::clicked, [this]() {
		
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() == 0) {
			double zero = 0;
			mcc->SetSeekZero(1, zero);
			return;
		}
		if (!bMachineReturn)
		bMachineReturn = 12;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");//回机床原点
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":Y");//回机床原点:Y
	});
	connect(ui.BtResetZ, &QPushButton::clicked, [this]() {
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() == 0) {
			double zero =0;
			mcc->SetSeekZero(2, zero);
			return;
		}
		if (!bMachineReturn)
		bMachineReturn = 13;		
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":Z");//回机床原点:Z
	});
	connect(ui.BtResetA, &QPushButton::clicked, [this]() {
	
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() ==0) {
			double zero = 0;
			mcc->SetSeekZero(3, zero);
			return;
		}
		if (!bMachineReturn)
			bMachineReturn = 14;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78)+":A");//回机床原点:A
	});
	connect(ui.BtResetB, &QPushButton::clicked, [this]() {
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() == 0) {
			double zero = 0;
			mcc->SetSeekZero(4, zero);
			return;
		}
		if (!bMachineReturn)
			bMachineReturn = 15;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":B");//回机床原点:B
	});
	connect(ui.BtResetC, &QPushButton::clicked, [this]() {
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() == 0) {
			double zero = 0;
			mcc->SetSeekZero(5, zero);
			return;
		}
		if (!bMachineReturn)
			bMachineReturn = 16;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":C");//回机床原点:C
	});
	connect(ui.BtResetAll, &QPushButton::clicked, [this]() {
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		if (readIni.GetSeekZeroOpt() == 0) {
			double zero = 0;
			mcc->SetSeekZero(0, zero);
			mcc->SetSeekZero(1, zero);
			mcc->SetSeekZero(2, zero);
			mcc->SetSeekZero(3, zero);
			return;
		}
		if (!bMachineReturn)
		bMachineReturn = 1;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":Z-X-Y-A");//回机床原点:Z-X-Y-A
	});

	connect(ui.BtResetM, &QPushButton::clicked, [this]() {
		SaveValue();
		if (!SammonFunc::CanDoit())return;
		w->isMCode = true;
		w->MCodeName = "999";
		SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
		w->MCodeFromMDI = true;//宏代码是从TextEdit 发送的
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(78), "");
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78) + ":M999");//回机床原点M
	});

	ui.BtResetAll->setShortcut(QKeySequence("S"));
	ui.BtResetX->setShortcut(QKeySequence("X"));
	ui.BtResetY->setShortcut(QKeySequence("Y"));
	ui.BtResetZ->setShortcut(QKeySequence("Z"));
	ui.BtResetA->setShortcut(QKeySequence("A"));
	ui.BtResetB->setShortcut(QKeySequence("B"));
	ui.BtResetC->setShortcut(QKeySequence("C"));
	ui.BtResetM->setShortcut(QKeySequence("M"));
}
