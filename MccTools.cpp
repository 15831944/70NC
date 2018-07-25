#include "MccTools.h"
#include "mccdll.h"
#include "ReadIni.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
MccTools::MccTools(QObject *parent)
	: QObject(parent)
{
}

MccTools::~MccTools()
{
}

void MccTools::SendMDI(QString str)
{
	mcc->SetFeedrateMultiple(-1);
	mcc->SendMDItext(str);
}

void MccTools::run()
{
	if (readIni.GetUseFeedrate()) {
		mcc->SetFeedrateMultiple(readIni.GetFeedrate().toInt());
	}
	else {
		mcc->SetFeedrateMultiple(-1);
	}
	mcc->SendAutoText(QString(""));
	mcc->SetAutoRunFlag(1);
}

void MccTools::setStart(int row)
{
	mcc->SetStartline(row);
	mcc->SendAutoText(QString(""));
}

void MccTools::RunStartLine(int row)
{

	mcc->ClearBuffer();
	if (readIni.GetUseFeedrate()) {
		mcc->SetFeedrateMultiple(readIni.GetFeedrate().toInt());
	}
	else {
		mcc->SetFeedrateMultiple(-1);
	}
	mcc->SetStartline(row);
	mcc->SendAutoText(QString(""));
	mcc->SetAutoRunFlag(true);
}

void MccTools::SwitchAutoMode()
{
	mcc->SendAutoText(QString(""));
}

int MccTools::workState()
{
	//	函数说明：返回运动控制卡的工作状态：0 - 等待 1 - 自动 2 - MDI 3 - 速度控制 4 - 手轮控制
	return mcc->GetWorkState();
}

bool MccTools::isIdle()
{
	return mcc->GetGmode(11).toInt()!=4;
}
