#include "DlgWorkpieceOffset.h"
#include "ReadIni.h"
#include "mccdll.h"
#include "CommonTools.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
DlgWorkpieceOffset::DlgWorkpieceOffset(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	connect(ui.bty, &QPushButton::clicked, [this]() {
		SaveOffset();
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {
		close();
	});

	typedef void(QComboBox::*QComboBoxtypedef)(int);
	QComboBoxtypedef func = &QComboBox::currentIndexChanged;
	ui.comboBox->setCurrentIndex(-1);
	connect(ui.comboBox, func, [this](int index) {
		SammonFunc::offsetSucces = true;
		WorkpieceIndex = index;
		offsetChange();
	});
	WorkpieceIndex = readIni.GetWorkpieceOffset();
	InitOffset();
	
	SetEnadble();

}

DlgWorkpieceOffset::~DlgWorkpieceOffset()
{

}

void DlgWorkpieceOffset::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(211)); ;
	ui.label_7->setText(TrLang::Ins()->GetText(210));
}

void DlgWorkpieceOffset::showEvent(QShowEvent * event)
{
	int i;
	if (WorkpieceIndex == 0) {
		 i = 150;
		ui.G54->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G54_2->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G54_3->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G54_4->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G54_5->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G54_6->setText(QString::number(mcc->GetParameterValue(i++)));
	}
	else if (WorkpieceIndex == 1) {
		i = 160;
		ui.G55->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G55_2->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G55_3->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G55_4->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G55_5->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G55_6->setText(QString::number(mcc->GetParameterValue(i++)));
	}
	else if (WorkpieceIndex == 2) {
		i = 170;
		ui.G56->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G56_2->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G56_3->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G56_4->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G56_5->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G56_6->setText(QString::number(mcc->GetParameterValue(i++)));
	}
	else if (WorkpieceIndex ==3) {
		i = 180;
		ui.G57->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G57_2->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G57_3->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G57_4->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G57_5->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G57_6->setText(QString::number(mcc->GetParameterValue(i++)));
	}
	else if (WorkpieceIndex == 4) {
		i = 190;
		ui.G58->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G58_2->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G58_3->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G58_4->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G58_5->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G58_6->setText(QString::number(mcc->GetParameterValue(i++)));
	}
	else if (WorkpieceIndex == 5) {
		i = 200;
		ui.G59->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G59_2->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G59_3->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G59_4->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G59_5->setText(QString::number(mcc->GetParameterValue(i++)));
		ui.G59_6->setText(QString::number(mcc->GetParameterValue(i++)));
	}
}

void DlgWorkpieceOffset::offsetChange()
{
	readIni.SetWorkpieceOffset(WorkpieceIndex);
	SaveOffset();
	SetEnadble();
}

void DlgWorkpieceOffset::InitOffset() {//初始化显示偏执
	int i = 150;
	ui.G54->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G54_2->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G54_3->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G54_4->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G54_5->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G54_6->setText(QString::number(mcc->GetParameterValue(i++)));
	i = 160;
	ui.G55->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G55_2->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G55_3->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G55_4->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G55_5->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G55_6->setText(QString::number(mcc->GetParameterValue(i++)));
	i = 170;
	ui.G56->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G56_2->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G56_3->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G56_4->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G56_5->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G56_6->setText(QString::number(mcc->GetParameterValue(i++)));
	i = 180;
	ui.G57->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G57_2->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G57_3->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G57_4->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G57_5->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G57_6->setText(QString::number(mcc->GetParameterValue(i++)));
	i = 190;
	ui.G58->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G58_2->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G58_3->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G58_4->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G58_5->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G58_6->setText(QString::number(mcc->GetParameterValue(i++)));
	i = 200;
	ui.G59->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G59_2->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G59_3->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G59_4->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G59_5->setText(QString::number(mcc->GetParameterValue(i++)));
	ui.G59_6->setText(QString::number(mcc->GetParameterValue(i++)));
	SetWorkpiece(WorkpieceIndex);
}
void DlgWorkpieceOffset::SetWorkpiece(int)//修改偏执后 更新工件坐标
{
	int i;
	if (WorkpieceIndex == 0)
		i = 150;
	else if (WorkpieceIndex == 1)
		i = 160;
	else if (WorkpieceIndex == 2)
		i = 170;
	else if (WorkpieceIndex == 3)
		i = 180;
	else if (WorkpieceIndex == 4)
		i = 190;
	else if (WorkpieceIndex == 5)
		i = 200;
	int dasd = mcc->GetMachineCoordinate(0);
	int d1asd = mcc->GetMachineCoordinate(1);
	int d2asd = mcc->GetMachineCoordinate(2);
	int d3asd = mcc->GetMachineCoordinate(3);
	int da4sd = mcc->GetMachineCoordinate(4);
	int da5sd = mcc->GetMachineCoordinate(5);
	double x =mcc->GetMachineCoordinate(0)- mcc->GetParameterValue(i++);
	double y = mcc->GetMachineCoordinate(1) - mcc->GetParameterValue(i++);
	double z = mcc->GetMachineCoordinate(2) - mcc->GetParameterValue(i++);
	double a = mcc->GetMachineCoordinate(3) - mcc->GetParameterValue(i++);
	double b = mcc->GetMachineCoordinate(4) - mcc->GetParameterValue(i++);
	double c = mcc->GetMachineCoordinate(5) - mcc->GetParameterValue(i++);

	mcc->SetSeekZero(12, x);
	mcc->SetSeekZero(13, y);
	mcc->SetSeekZero(14, z);
	mcc->SetSeekZero(15, a);
	mcc->SetSeekZero(16, b);
	mcc->SetSeekZero(17, c);

}
void DlgWorkpieceOffset::SetEnadble()
{
	ui.groupBox->setEnabled(0);
	ui.groupBox_2->setEnabled(0);
	ui.groupBox_3->setEnabled(0);
	ui.groupBox_4->setEnabled(0);
	ui.groupBox_5->setEnabled(0);
	ui.groupBox_6->setEnabled(0);
	if(WorkpieceIndex==0)
		ui.groupBox->setEnabled(1);
	else if (WorkpieceIndex == 1)
		ui.groupBox_2->setEnabled(1);
	else if (WorkpieceIndex == 2)
		ui.groupBox_3->setEnabled(1);
	else if (WorkpieceIndex == 3)
		ui.groupBox_4->setEnabled(1);
	else if (WorkpieceIndex == 4)
		ui.groupBox_5->setEnabled(1);
	else if (WorkpieceIndex == 5)
		ui.groupBox_6->setEnabled(1);
}
void DlgWorkpieceOffset::SetWorkpiece( int axis,double value)//修改工件坐标后 更新偏执
{
	int i;
	if (WorkpieceIndex == 0)
		i = 150+axis;
	else if (WorkpieceIndex == 1)
		i = 160 + axis;
	else if (WorkpieceIndex == 2)
		i = 170 + axis;
	else if (WorkpieceIndex == 3)
		i = 180 + axis;
	else if (WorkpieceIndex == 4)
		i = 190 + axis;
	else if (WorkpieceIndex == 5)
		i = 200 + axis;
	mcc->SetParameterValue(i, value);	
}
void DlgWorkpieceOffset::SaveOffset() {//保存偏执
	int i;
	if (WorkpieceIndex == 0) {
		i = 150;
		mcc->SetParameterValue(i++, ui.G54->text().toDouble());
		mcc->SetParameterValue(i++, ui.G54_2->text().toDouble());
		mcc->SetParameterValue(i++, ui.G54_3->text().toDouble());
		mcc->SetParameterValue(i++, ui.G54_4->text().toDouble());
		mcc->SetParameterValue(i++, ui.G54_5->text().toDouble());
		mcc->SetParameterValue(i++, ui.G54_6->text().toDouble());
	}
	else if (WorkpieceIndex == 1) {
		i = 160;
		mcc->SetParameterValue(i++, ui.G55->text().toDouble());
		mcc->SetParameterValue(i++, ui.G55_2->text().toDouble());
		mcc->SetParameterValue(i++, ui.G55_3->text().toDouble());
		mcc->SetParameterValue(i++, ui.G55_4->text().toDouble());
		mcc->SetParameterValue(i++, ui.G55_5->text().toDouble());
		mcc->SetParameterValue(i++, ui.G55_6->text().toDouble());
	}
	else if (WorkpieceIndex == 2) {
		i = 170;
		mcc->SetParameterValue(i++, ui.G56->text().toDouble());
		mcc->SetParameterValue(i++, ui.G56_2->text().toDouble());
		mcc->SetParameterValue(i++, ui.G56_3->text().toDouble());
		mcc->SetParameterValue(i++, ui.G56_4->text().toDouble());
		mcc->SetParameterValue(i++, ui.G56_5->text().toDouble());
		mcc->SetParameterValue(i++, ui.G56_6->text().toDouble());
	}
	else if (WorkpieceIndex == 3) {
		i = 180;
		mcc->SetParameterValue(i++, ui.G57->text().toDouble());
		mcc->SetParameterValue(i++, ui.G57_2->text().toDouble());
		mcc->SetParameterValue(i++, ui.G57_3->text().toDouble());
		mcc->SetParameterValue(i++, ui.G57_4->text().toDouble());
		mcc->SetParameterValue(i++, ui.G57_5->text().toDouble());
		mcc->SetParameterValue(i++, ui.G57_6->text().toDouble());
	}
	else if (WorkpieceIndex == 4) {
		i = 190;
		mcc->SetParameterValue(i++, ui.G58->text().toDouble());
		mcc->SetParameterValue(i++, ui.G58_2->text().toDouble());
		mcc->SetParameterValue(i++, ui.G58_3->text().toDouble());
		mcc->SetParameterValue(i++, ui.G58_4->text().toDouble());
		mcc->SetParameterValue(i++, ui.G58_5->text().toDouble());
		mcc->SetParameterValue(i++, ui.G58_6->text().toDouble());
	}
	else if (WorkpieceIndex == 5) {
		i = 200;
		mcc->SetParameterValue(i++, ui.G59->text().toDouble());
		mcc->SetParameterValue(i++, ui.G59_2->text().toDouble());
		mcc->SetParameterValue(i++, ui.G59_3->text().toDouble());
		mcc->SetParameterValue(i++, ui.G59_4->text().toDouble());
		mcc->SetParameterValue(i++, ui.G59_5->text().toDouble());
		mcc->SetParameterValue(i++, ui.G59_6->text().toDouble());
	}
	SetWorkpiece(WorkpieceIndex);
}
