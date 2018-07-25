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
	//	����˵���������˶����ƿ��Ĺ���״̬��0 - �ȴ� 1 - �Զ� 2 - MDI 3 - �ٶȿ��� 4 - ���ֿ���
	return mcc->GetWorkState();
}

bool MccTools::isIdle()
{
	return mcc->GetGmode(11).toInt()!=4;
}
