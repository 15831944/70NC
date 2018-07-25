#include "ctrlHand.h"
#include "qdebug"
#include "YesOrNo.h"
#include "DlgCustomDlg.h"
#include "QShortcut"
#include "QKeyEvent"
#include "PHBX.h"
#include"LogManager.h"
#include "ncpod.h"
#include "CommonTools.h"
#include "TrLang.h"
#include "MccTools.h"
extern mccdll::MotionControlCard* mcc;
extern QString MyStyle;
extern bool isSimulation;
extern bool IsPC;
ctrlHand::ctrlHand(QWidget *parent)
	: StyleWidget(parent), CustomStep(15),step(0)
{
	ui.setupUi(this);
	InitUI();
	InitKeyboardCtrl();
	setBtnText();
	DurTime.restart();

	//if (DurTime.elapsed() < 500)return;
	//else DurTime.restart();
}

ctrlHand::~ctrlHand()
{
	
}

void ctrlHand::ResetLanguage()
{
	ui.groupBox->setTitle(TrLang::Ins()->GetText(163));
	ui.rbLX->setText(TrLang::Ins()->GetText(164));
	ui.rbh->setText(TrLang::Ins()->GetText(165));
	ui.rbl->setText(TrLang::Ins()->GetText(166));
	ui.btCustom->setText(TrLang::Ins()->GetText(167));
	
}

void ctrlHand::MySetFocus()
{
	ui.Aadd->setFocus();
}

bool ctrlHand::MyGetFocus()
{
	bool b1 = ui.Badd->hasFocus() || ui.Bsub->hasFocus() || ui.Cadd->hasFocus() || ui.Csub->hasFocus() || ui.Aadd->hasFocus() || ui.Asub->hasFocus() || ui.Xadd->hasFocus() || ui.Xsub->hasFocus() || ui.Yadd->hasFocus() || ui.Ysub->hasFocus() || ui.Zadd->hasFocus() || ui.Zsub->hasFocus();
	
	bool b2 = ui.rbLX->hasFocus() || ui.rbV3->hasFocus() || ui.rbV4->hasFocus() || ui.rbV5->hasFocus() || ui.rbV6->hasFocus() || ui.rbV7->hasFocus() || ui.rbV9->hasFocus();
	bool b3 = ui.rbh->hasFocus() || ui.rbl->hasFocus();
	bool b4 = ui.btCustom->hasFocus();
	return b1||b2||b3||b4||hasFocus();
}

void ctrlHand::keyPressEvent(QKeyEvent * event)
{
	if (!isPressed) {
		if (event->key() == Qt::Key_D) {
			ui.Xadd->animateClick(3600000);
			isPressed = true;
		}else if (event->key() == Qt::Key_W)
		{
			ui.Yadd->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_E)
		{
			ui.Zadd->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_A)
		{
			ui.Xsub->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_X)
		{
			ui.Ysub->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_Z)
		{
			ui.Zsub->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_Q)
		{
			ui.Aadd->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_T)
		{
			ui.Badd->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_H)
		{
			ui.Cadd->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_C)
		{
			ui.Asub->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_B)
		{
			ui.Bsub->animateClick(3600000);
			isPressed = true;
		}
		else if (event->key() == Qt::Key_F)
		{
			ui.Csub->animateClick(3600000);
			isPressed = true;
		}		
	}
	QWidget::keyPressEvent(event);
}

void ctrlHand::keyReleaseEvent(QKeyEvent *event)
{	
	isPressed = false;
	if (event->key() == Qt::Key_D) {
		ui.Xadd->animateClick(0);
	}
	else if (event->key() == Qt::Key_W)
	{
		ui.Yadd->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_E)
	{
		ui.Zadd->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_A)
	{
		ui.Xsub->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_X)
	{
		ui.Ysub->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_Z)
	{
		ui.Zsub->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_Q)
	{
		ui.Aadd->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_T)
	{
		ui.Badd->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_H)
	{
		ui.Cadd->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_C)
	{
		ui.Asub->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_B)
	{
		
		ui.Bsub->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_F)
	{
		ui.Csub->animateClick(0);
		
	}
	else if (event->key() == Qt::Key_S)
	{
		if (ui.rbl->isChecked()) {
			ui.rbh->setChecked(1);
		}
		else {
			ui.rbl->setChecked(1);
		}
	}
	else  if (event->key() == Qt::Key_G)
	{
		if (ui.rbLX->isChecked()) {
			ui.rb001->setChecked(1);
		}
		else if (ui.rb001->isChecked()) {
			ui.rbV3->setChecked(1);
		}
		else if (ui.rbV3->isChecked()) {
			ui.rbV4->setChecked(1);
		}
		else if (ui.rbV4->isChecked()) {
			ui.rbV5->setChecked(1);
		}
		else if (ui.rbV5->isChecked()) {
			ui.rbV6->setChecked(1);
		}
		else if (ui.rbV6->isChecked()) {
			ui.rbV7->setChecked(1);
		}
		else if (ui.rbV7->isChecked()) {
			ui.rbV9->setChecked(1);
		}
		else if (ui.rbV9->isChecked()) {
			ui.rbLX->setChecked(1);
		}

	}else if (event->key() == Qt::Key_Return) {
		QWidget* w = focusWidget();
		QPushButton* btSub = dynamic_cast<QPushButton*>(w);
		QRadioButton* rbSub = dynamic_cast<QRadioButton*>(w);
		if (btSub==ui.btCustom) {
			btSub->clicked(1);
			//btSub->setChecked(!btSub->isChecked());
		}
		else if (rbSub) {
			rbSub->setChecked(true);
		}
	}
	QWidget::keyReleaseEvent(event);
}

bool ctrlHand::eventFilter(QObject * obj, QEvent * event)
{
	if (obj==this||
		obj == ui.Xadd ||
		obj == ui.Xsub ||
		obj == ui.Yadd ||
		obj == ui.Ysub ||
		obj == ui.Zadd ||
		obj == ui.Zsub ||
		obj == ui.Aadd ||
		obj == ui.Asub ||
		obj == ui.Badd ||
		obj == ui.Bsub ||
		obj == ui.Cadd ||
		obj == ui.Csub ||
		obj == ui.rbh ||
		obj == ui.rbl ||
		obj == ui.rbLX ||
		obj == ui.rb001 ||
		obj == ui.rbV3 ||
		obj == ui.rbV4 ||
		obj == ui.rbV5 ||
		obj == ui.rbV6 ||
		obj == ui.rbV7 ||
		obj == ui.rbV9 ||
		obj == ui.btCustom) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.Badd->hasFocus() || ui.Bsub->hasFocus() || ui.Cadd->hasFocus() || ui.Csub->hasFocus() || ui.Aadd->hasFocus() || ui.Asub->hasFocus() || ui.Xadd->hasFocus() || ui.Xsub->hasFocus() || ui.Yadd->hasFocus() || ui.Ysub->hasFocus() || ui.Zadd->hasFocus() || ui.Zsub->hasFocus();
				bool b2 = ui.rbLX->hasFocus() || ui.rbV3->hasFocus() || ui.rbV4->hasFocus() || ui.rbV5->hasFocus() || ui.rbV6->hasFocus() || ui.rbV7->hasFocus() || ui.rbV9->hasFocus() ||ui.rb001->hasFocus();;
				bool b3 = ui.rbh->hasFocus() || ui.rbl->hasFocus();
				bool b4 = ui.btCustom->hasFocus();
				if (b1) {
					focusNextChild();
					ui.rbLX->setFocus();

				}
				else if (b2) {
					focusNextChild();
					ui.rbh->setFocus();
				
				}
				else if (b3) {
					focusNextChild();
					ui.btCustom->setFocus();
				}
				else if (b4) {
					focusNextChild();
					ui.Aadd->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					ui.Aadd->setFocus();
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

void ctrlHand::DealHandwheel(int key1, int key2,bool isHandwheelPressed)
{
	if (isHandwheelPressed) {
		if (key1== 16) {
			ui.Xadd->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 12)
		{
			ui.Yadd->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1==13)
		{
			ui.Zadd->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 14)
		{
			ui.Xsub->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 18)
		{
			ui.Ysub->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 17)
		{
			ui.Zsub->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1==11)
		{
			ui.Aadd->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 21)
		{
			ui.Badd->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 25)
		{
			ui.Cadd->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 19)
		{
			ui.Asub->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 27)
		{
			ui.Bsub->animateClick(3600000);
			//isPressed = true;
		}
		else if (key1== 23)
		{
			ui.Csub->animateClick(3600000);
			//isPressed = true;
		}
	}
	else {
		if (key1 == 16) {
			ui.Xadd->animateClick(0);
		}
		else if (key1 == 12)
		{
			ui.Yadd->animateClick(0);

		}
		else if (key1 == 13)
		{
			ui.Zadd->animateClick(0);

		}
		else if (key1 == 14)
		{
			ui.Xsub->animateClick(0);

		}
		else if (key1 == 18)
		{
			ui.Ysub->animateClick(0);

		}
		else if (key1 == 17)
		{
			ui.Zsub->animateClick(0);

		}
		else if (key1 == 11)
		{
			ui.Aadd->animateClick(0);

		}
		else if (key1 == 21)
		{
			ui.Badd->animateClick(0);

		}
		else if (key1 == 25)
		{
			ui.Cadd->animateClick(0);

		}
		else if (key1 == 19)
		{
			ui.Asub->animateClick(0);

		}
		else if (key1 == 27)
		{

			ui.Bsub->animateClick(0);

		}
		else if (key1 == 23)
		{
			ui.Csub->animateClick(0);

		}
		else if (key1 == 15)
		{
			if (ui.rbl->isChecked()) {
				ui.rbh->setChecked(1);						
			}
			else {
				ui.rbl->setChecked(1);
			}
		}
		else  if (key1 == 24)
		{
			if (ui.rbLX->isChecked()) {
				ui.rbV9->setChecked(1);
			}
			else {
				ui.rbLX->setChecked(1);
			}
		}
		else  if (key1 == 20)
		{
			if (ui.rbLX->isChecked()) {
				ui.rb001->setChecked(1);
			}
			else if (ui.rb001->isChecked()) {
				ui.rbV3->setChecked(1);
			}
			else if(ui.rbV3->isChecked() ){
				ui.rbV4->setChecked(1);
			}
			else if (ui.rbV4->isChecked()) {
				ui.rbV5->setChecked(1);
			}
			else if (ui.rbV5->isChecked()) {
				ui.rbV6->setChecked(1);
			}
			else if (ui.rbV6->isChecked()) {
				ui.rbV7->setChecked(1);
			}
			else if (ui.rbV7->isChecked()) {
				ui.rbV9->setChecked(1);
			}
			else if (ui.rbV9->isChecked()) {
				ui.rb001->setChecked(1);
			}
		}
		else  if (key1 == 22)
		{
			if (ui.rbLX->isChecked()) {
				ui.rbV9->setChecked(1);
			}
			else if (ui.rbV9->isChecked()) {
				ui.rbV7->setChecked(1);
			}
			else if (ui.rbV7->isChecked()) {
				ui.rbV6->setChecked(1);
			}
			else if (ui.rbV6->isChecked()) {
				ui.rbV5->setChecked(1);
			}
			else if (ui.rbV5->isChecked()) {
				ui.rbV4->setChecked(1);
			}
			else if (ui.rbV4->isChecked()) {
				ui.rbV3->setChecked(1);
			}
			else if (ui.rbV3->isChecked()) {
				ui.rb001->setChecked(1);
			}
			else if (ui.rb001->isChecked()) {
				ui.rbV9->setChecked(1);
			}
		}
		else if (key1 == 26)
		{
			ui.rbV3->setChecked(1);
		}
		else if (key1 == 28)
		{
			ui.rbV5->setChecked(1);
		}
	}
}

void ctrlHand::NcPodMove(int i, int axis, QString s)
{
	SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(6), "");//手动
	if (ui.rbLX->isChecked())
	{
		if (!SammonFunc::CanDoit())return;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(6), "");//手动
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(161) + s);//连续运动
		isLxRuning = true;//?????????

		double speed = SammonFunc::GetSpeed(3, axis).toDouble() / 60 * mcc->GetParameterValue(100);
		speed = speed*mcc->GetParameterValue(110 + axis) / mcc->GetParameterValue(120 + axis);
		mcc->SetSpeedControl(axis, (int)speed*i);
	}
	else {
		if (!SammonFunc::CanDoit())return;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(6), "");//手动
		QString str = "";
		char  buff[20] = {};
		if (mcc->GetGmode(7) == "G90") {

			sprintf(buff, "%.3f", mcc->GetWorkpieceCoordinate(axis) + step*i);
			str = str + "G01" + s + buff + "F" + SammonFunc::GetSpeed(2, axis);
		}
		else {
			str = str + "G01" + s + QString::number(step*i) + "F" + SammonFunc::GetSpeed(2,axis);
		}
		MccTools::SendMDI(str);
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(162) + str);//点动步长
	}
}

void ctrlHand::showEvent(QShowEvent * event)
{
	
	int size = ui.rbLX->height() / 4;
	size = size > 10 ? size : 10;
	size = size < 20 ? size : 20;

	//////////////////////////
	QString style = "\
		QRadioButton::indicator{\
			width: %1px;\
			height: %2px;\
		}";
	style = style.arg(size).arg(size);

	ui.rbLX->setStyleSheet(style);
	ui.rb001->setStyleSheet(style);
	ui.rbV3->setStyleSheet(style);
	ui.rbV4->setStyleSheet(style);
	ui.rbV5->setStyleSheet(style);
	ui.rbV6->setStyleSheet(style);
	ui.rbV7->setStyleSheet(style);
	ui.rbV9->setStyleSheet(style);

	QString style2 = "\
		QRadioButton::indicator{\
			width: %1px;\
			height: %2px;\
		}";
	style2 = style.arg(size).arg(size);
	ui.rbh->setStyleSheet(style2);
	ui.rbl->setStyleSheet(style2);

	if (IsPC) {
		int hsp, vsp;
		hsp = ui.Xadd->size().width() / 6;
		vsp = ui.Xadd->size().height() / 6;

		ui.gridLayout_4->setHorizontalSpacing(hsp);
		ui.gridLayout_3->setHorizontalSpacing(hsp);
		ui.gridLayout_4->setVerticalSpacing(vsp);
		ui.gridLayout_3->setVerticalSpacing(vsp);
		ui.gridLayout_4->setMargin(hsp);
		ui.gridLayout_3->setMargin(hsp);
	}
	QWidget::showEvent(event);
}

void ctrlHand::resizeEvent(QResizeEvent * event)
{
	int size = ui.rbLX->height() / 4;
	size = size > 10 ? size : 10;
	size = size < 20 ? size : 20;

	//////////////////////////
	QString style = "\
		QRadioButton::indicator{\
			width: %1px;\
			height: %2px;\
		}";
	style = style.arg(size).arg(size);

	ui.rbLX->setStyleSheet(style);
	ui.rb001->setStyleSheet(style);
	ui.rbV3->setStyleSheet(style);
	ui.rbV4->setStyleSheet(style);
	ui.rbV5->setStyleSheet(style);
	ui.rbV6->setStyleSheet(style);
	ui.rbV7->setStyleSheet(style);
	ui.rbV9->setStyleSheet(style);

	QString style2 = "\
		QRadioButton::indicator{\
			width: %1px;\
			height: %2px;\
		}";
	style2 = style.arg(size).arg(size);
	ui.rbh->setStyleSheet(style2);
	ui.rbl->setStyleSheet(style2);

	if (IsPC) {
		int hsp, vsp;
		hsp = ui.Xadd->size().width() / 6;
		vsp = ui.Xadd->size().height() / 6;

		ui.gridLayout_4->setHorizontalSpacing(hsp);
		ui.gridLayout_3->setHorizontalSpacing(hsp);
		ui.gridLayout_4->setVerticalSpacing(vsp);
		ui.gridLayout_3->setVerticalSpacing(vsp);
		ui.gridLayout_4->setMargin(hsp);
		ui.gridLayout_3->setMargin(hsp);
	}

	
	
	QWidget::resizeEvent(event);
}

void ctrlHand::AddStep(int i, int axis,QString s)//i 方向 ：-1，1；axis 轴号：0-5；s 轴名 ：X,Y,Z,A,B,C
{
	if (ui.rbLX->isChecked())
	{
		if (!SammonFunc::CanDoit())return;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(6), "");//手动
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(161) +s);//连续运动
		isLxRuning = true;
		if (isSimulation) {
			DoSimSpeedCtrl(i, axis, s);
			return;
		}
		double speed = SammonFunc::GetSpeed(3, axis).toDouble() / 60 * mcc->GetParameterValue(100);
		speed = speed*mcc->GetParameterValue(110+axis) / mcc->GetParameterValue(120+axis);
		mcc->SetSpeedControl(axis, (int)speed*i);
	}
}

void ctrlHand::SudStep(int i, int axis, QString s)//-1\1   0-6       XYZABC
{

	if (ui.rbLX->isChecked())
	{
		
		if (!isLxRuning)return; isLxRuning = false;
		mcc->SetAutoRunFlag(false);
		if (isSimulation) {
			mcc->SetAutoRunFlag(false);
			return;
		}
		mcc->CancelSpeedControl(axis);
		mcc->SetIniPnowFlg(0);
	}
	else {
		if (DurTime.elapsed() < 500)return;
		else DurTime.restart();
		if (!SammonFunc::CanDoit())return;
		SammonFunc::Getins()->updateState(TrLang::Ins()->GetText(6), "");//手动
		QString str = "";
		char  buff[20] = {};
		if (mcc->GetGmode(7) == "G90") {

			sprintf(buff, "%.3f", mcc->GetWorkpieceCoordinate(axis) + step*i);
			str = str + "G01" + s + buff + "F" + SammonFunc::GetSpeed(2, axis);
		}
		else {
			str = str + "G01"+s + QString::number(step*i) + "F" + SammonFunc::GetSpeed(2,axis);
		}
		MccTools::SendMDI(str);
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(162) + str);//点动步长
	}
}

void ctrlHand::InitUI()
{
	pDlgCustomDlg = new DlgCustomDlg;
	pDlgCustomDlg->setStyleSheet(MyStyle);
	InitXYZ();
	InitStep();
	connect(ui.btCustom, &QPushButton::clicked, [this](bool b) {
		pDlgCustomDlg->show();
	});
	connect(pDlgCustomDlg, &DlgCustomDlg::ChioceYes, [this]() {
		CustomStep = pDlgCustomDlg->Text().toDouble();
		ui.rbV9->setText(pDlgCustomDlg->Text() + "mm");
		ui.rbV9->setChecked(1);
		ui.rbV9->toggled(1);
	});
	connect(ui.rbh, &QRadioButton::toggled, [this](bool isCHecked) {
		if (!isCHecked)
			return;
		SammonFunc::Getins()->isLowSpeed = false;
		SetLEDDate();
	});
	connect(ui.rbl, &QRadioButton::toggled, [this](bool isCHecked) {
		if (!isCHecked)
			return;
		SammonFunc::Getins()->isLowSpeed = true;
		SetLEDDate();
	});
	ui.rbl->setChecked(true);
	ui.btCustom->setCheckable(1);
}

void ctrlHand::InitXYZ()
{
	connect(ui.Xadd, &QPushButton::pressed, [this]() {
		AddStep(1, 0,"X");
	});
	connect(ui.Xadd, &QPushButton::released, [this]() {	
		SudStep(1, 0, "X");
	});
	connect(ui.Xsub, &QPushButton::pressed, [this]() {
		AddStep(-1, 0, "X");
	});
	connect(ui.Xsub, &QPushButton::released, [this]() {
		SudStep(-1, 0, "X");
	});
	connect(ui.Yadd, &QPushButton::pressed, [this]() {
		AddStep(1, 1, "Y");
	});
	connect(ui.Yadd, &QPushButton::released, [this]() {
		SudStep(1, 1, "Y");
	});
	connect(ui.Ysub, &QPushButton::pressed, [this]() {
		AddStep(-1, 1, "Y");
	});
	connect(ui.Ysub, &QPushButton::released, [this]() {
		SudStep(-1, 1, "Y");
	});
	connect(ui.Zadd, &QPushButton::pressed, [this]() {
		AddStep(1, 2, "Z");
	});
	connect(ui.Zadd, &QPushButton::released, [this]() {
		SudStep(1, 2, "Z");
	});
	connect(ui.Zsub, &QPushButton::pressed, [this]() {
		AddStep(-1, 2, "Z");
	});
	connect(ui.Zsub, &QPushButton::released, [this]() {
		SudStep(-1, 2, "Z");
	});
	connect(ui.Aadd, &QPushButton::pressed, [this]() {
		AddStep(1, 3, "A");
	});
	connect(ui.Aadd, &QPushButton::released, [this]() {
		SudStep(1, 3, "A");
	});
	connect(ui.Asub, &QPushButton::pressed, [this]() {
		AddStep(-1, 3, "A");
	});
	connect(ui.Asub, &QPushButton::released, [this]() {
		SudStep(-1, 3, "A");
	});
	connect(ui.Badd, &QPushButton::pressed, [this]() {
		AddStep(1, 4, "B");
	});
	connect(ui.Badd, &QPushButton::released, [this]() {
		SudStep(1, 4, "B");
	});
	connect(ui.Bsub, &QPushButton::pressed, [this]() {
		AddStep(-1, 4, "B");
	});
	connect(ui.Bsub, &QPushButton::released, [this]() {
		SudStep(-1, 4, "B");
	});
	connect(ui.Cadd, &QPushButton::pressed, [this]() {
		AddStep(1, 5, "C");
	});
	connect(ui.Cadd, &QPushButton::released, [this]() {
		SudStep(1, 5, "C");
	});
	connect(ui.Csub, &QPushButton::pressed, [this]() {
		AddStep(-1, 5, "C");
	});
	connect(ui.Csub, &QPushButton::released, [this]() {
		SudStep(-1, 5, "C");
	});
}

void ctrlHand::InitStep()
{
	ui.rbLX->setChecked(true);
	connect(ui.rbLX, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = 0;

		SetLEDDate();
	});
	connect(ui.rbV3, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = 0.1;
	
		SetLEDDate();
	});
	connect(ui.rb001, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = 0.01;
	
		SetLEDDate();
	});
	connect(ui.rbV4, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = 0.5;
		
		SetLEDDate();
	});
	connect(ui.rbV5, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = 1;
		SetLEDDate();
	});
	connect(ui.rbV6, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step =5;
		SetLEDDate();
	});
	connect(ui.rbV7, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = 10;
		SetLEDDate();
	});
	connect(ui.rbV9, &QRadioButton::toggled, [this](bool isTrue) {
		if (!isTrue)return;
		step = CustomStep;
		SetLEDDate();
	});
	
}

void ctrlHand::setBtnText()
{
	return;
	ui.Xadd->setURText("D");
	ui.Yadd->setURText("W");
	ui.Zadd->setURText("E");
	ui.Xsub->setURText("A");
	ui.Ysub->setURText("X");
	ui.Zsub->setURText("Z");
	ui.Aadd->setURText("Q");
	ui.Badd->setURText("T");
	ui.Cadd->setURText("H");
	ui.Asub->setURText("C");
	ui.Bsub->setURText("B");
	ui.Csub->setURText("F");
}

void ctrlHand::InitKeyboardCtrl(){
	installEventFilter(this);
	ui.Xadd->installEventFilter(this);
	ui.Xsub->installEventFilter(this);
	ui.Yadd->installEventFilter(this);
	ui.Ysub->installEventFilter(this);
	ui.Zadd->installEventFilter(this);
	ui.Zsub->installEventFilter(this);
	ui.Aadd->installEventFilter(this);
	ui.Asub->installEventFilter(this);
	ui.Badd->installEventFilter(this);
	ui.Bsub->installEventFilter(this);
	ui.Cadd->installEventFilter(this);
	ui.Csub->installEventFilter(this);
	ui.rbh->installEventFilter(this);
	ui.rbl->installEventFilter(this);
	ui.rbLX->installEventFilter(this);
	ui.rb001->installEventFilter(this);
	ui.rbV3->installEventFilter(this);
	ui.rbV4->installEventFilter(this);
	ui.rbV5->installEventFilter(this);
	ui.rbV6->installEventFilter(this);
	ui.rbV7->installEventFilter(this);
	ui.rbV9->installEventFilter(this);
	ui.btCustom->installEventFilter(this);
}

void ctrlHand::SetLEDDate()
{
	if (!PHBX::getIns()->isInitOver) {
		return;
	}
	uchar LEDDate[2] = { 0 };
	uchar  LEDDateSize = 2;
	uchar LXLight = 0;
	if (ui.rbLX->isChecked()) {
		LEDDate[0] = 0;
		LXLight = 0x16;
	}
	else if (ui.rb001->isChecked()) {
		LEDDate[0] =0x01+0x80;
	}
	else if (ui.rbV3->isChecked()) {
		LEDDate[0] = 0x02 + 0x80;
	}
	else if (ui.rbV4->isChecked()) {
		LEDDate[0] = 0x04 + 0x80;
	}
	else if (ui.rbV5->isChecked()) {
		LEDDate[0] = 0x08 + 0x80;
	}
	else if (ui.rbV6->isChecked()) {
		LEDDate[0] = 0x10 + 0x80;
	}
	else if (ui.rbV7->isChecked()) {
		LEDDate[0] = 0x20 + 0x80;
	}
	else if (ui.rbV9->isChecked()) {
		LEDDate[0] = 0x40 + 0x80;
	}
	if (ui.rbh->isChecked())
		LEDDate[1] = 0x40+ LXLight;
	else
		LEDDate[1] = 0x80+ LXLight;	
	PHBX::getIns()->XSendOutput_f(LEDDate, &LEDDateSize);
}

void ctrlHand::DoSimSpeedCtrl(int direction, int AxisNum, QString Axis)
{
	QString str = "";
	int Step = 99999* direction;
	char  buff[20] = {};
	if (mcc->GetGmode(7) == "G90") {

		sprintf(buff, "%.3f", mcc->GetWorkpieceCoordinate(0) + Step);
		str = str + "G01" +Axis+ buff + "F" + SammonFunc::GetSpeed(2, AxisNum);
	}
	else {
		str = str + "G01"+ Axis + QString::number(Step) + "F" + SammonFunc::GetSpeed(2, AxisNum);
	}
	MccTools::SendMDI(str);
	mcc->SetAutoRunFlag(1);
}
