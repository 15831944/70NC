#include "CommonTools.h"
#include "DataDefine.h"
#include "ReadIni.h"
#include"qDebug"
#include "stdarg.h"
#include"Samcon.h"
#include "s_OpenFile.h"
#include "ExternalText.h"
#include "LogManager.h"
extern Samcon *w;
extern ReadIni readIni;
extern mccdll::MotionControlCard* mcc;

bool SammonFunc::isNeedOpenSpindleRotat = false;
bool SammonFunc::IsPause = false;

bool SammonFunc::LastCoordinateInit = false;

bool SammonFunc::In6GuangMuXinHao = false;//In6 光幕信号

QString SammonFunc::sToolName = "";

QString SammonFunc::sMachiningSpeed = "";
SammonFunc * SammonFunc::func = NULL;
QMap<int, QString> SammonFunc::ReplaceCodeMap;
QMap<int, DrillHoleData>SammonFunc::DrillHoleMap;
QMap<int, int>SammonFunc::TCodeMap;

bool SammonFunc::XHoneEnabled;//使能标志
bool SammonFunc::YHoneEnabled;
bool SammonFunc::ZHoneEnabled;
bool SammonFunc::AHoneEnabled;
bool SammonFunc::BHoneEnabled;
bool SammonFunc::CHoneEnabled;
int  SammonFunc::iGJSpeed = 0;

bool SammonFunc::isToolSetting = false;
bool SammonFunc::isFToolSetting = false;
bool SammonFunc::RunShow = false;//开始键 状态
bool SammonFunc::PauseShow = false;// 状态
bool SammonFunc::NextShow = false;// 状态
bool SammonFunc::isLoading = false;//是否载入G代码
int SammonFunc::StartLine = -1;//急停时 行号
bool SammonFunc::NeedRunNext = 0;
bool SammonFunc::offsetSucces = false;
bool SammonFunc::isStartFormIdx = false;
bool SammonFunc::IsNumber(QString& str)
{
	if (str.size() == 0)
		return	false;
	if (str.toDouble() != 0 || (str.toDouble() == 0 && str[0] == '0'))
		return true;
	return false;
}
bool SammonFunc::CheckContains(QString line, int count, ...) {
	QString  cur = "";
	bool cons = false;
	va_list arg_ptr;
	va_start(arg_ptr, count);
	for (int i = 0; i < count; i++) {
		cur = va_arg(arg_ptr, const char*);
		cons = cons || line.contains(cur);
		if (cons) break;
	}
	va_end(arg_ptr);
	return cons;
}

void SammonFunc::SetSpeedControl_stop(bool isSimulation) {
	if (!isSimulation) {//仿真版调用这个函数 会出问题
		mcc->SetSpeedControl(0, 0);//Speed=0时，立即停止 
		mcc->SetSpeedControl(1, 0);
		mcc->SetSpeedControl(2, 0);
		mcc->SetSpeedControl(3, 0);
		mcc->SetSpeedControl(4, 0);
		mcc->SetSpeedControl(5, 0);
	}
	mcc->SetAutoRunFlag(false);
}
void SammonFunc::CheckFeedrate() {
	if (readIni.GetUseFeedrate()) {
		mcc->SetFeedrateMultiple(readIni.GetFeedrate().toInt());
	}
	else {
		mcc->SetFeedrateMultiple(-1);
	}
}

int SammonFunc::SwtichTInLine(int line) {

	int nearest = 50000000;

	QList<int>& keys = TCodeMap.keys();
	for (int i = 0; i < keys.count(); i++) {
		if (keys[i] < line) {
			if (line - keys[i] < nearest) {
				nearest = line - keys[i];
			}
		}
	}

	return TCodeMap.value(line - nearest);
}
QString SammonFunc::GetSpeed(int flag, int Axis) {
	//参数1 ： 0 默认速度，1，自动速度，2，手动步长速度，3 连续速度
	//-1 上次的速度 速度控制的速度 取不到， 自行保存；
	static QString lastValue = "";
	QString value = "";
	int ParamNum;
	if (SammonFunc::Getins()->isLowSpeed)
		ParamNum = 320;
	else
		ParamNum = 330;
	switch (flag)
	{
	case -1:
		value = lastValue;
		break;
	case 0:
		value = "2000";
		break;
	case 1:
		value = readIni.GetFeedrate();
		break;
	case 2:
		value = QString::number(mcc->GetParameterValue(ParamNum + Axis));
		break;
	case 3:
		{
		float mu1l = mcc->GetMultiple(1);//进给倍率只对
			float mul = mcc->GetMultiple(0);//进给倍率只对F 指令有效，，连续控制时  需要自己 乘以倍率
			mul /= 100;
			value = QString::number(mcc->GetParameterValue(ParamNum + Axis)*mul);
			lastValue = value;
			break;	
		}
	default:
		value = "2000";
		break;
	}
	//LogManager::getIns()->debugLog(QString("Speed: %1").arg(value));
	return value;
}
bool SammonFunc::CanDoit(bool NeedCheckPause)
{
	if (w == NULL)return false;
	if (!SammonFunc::Getins()->isRegSoft) {
		emit Getins()->updateState("", ExternalText::ZHuCheSiXiao);
		return false;
	}
	if (NeedCheckPause) {
		if (SammonFunc::IsPause) {
			emit Getins()->updateState("", ExternalText::StrPause);
			return false;
		}
	}
	if(SammonFunc::Getins()->readBit(readIni.GetTool_In_Enabled_4(),6))//判断光幕信号是否使能
	if (In6GuangMuXinHao) {
		emit Getins()->updateState("", ExternalText::In6Pause);
		return false;
	}
	if (isNeedOpenSpindleRotat) {
		emit Getins()->updateState("", ExternalText::OpenSpindleMsg);
		return false;
	}
	if (mcc->IniPnowFlg() != 0) {
		emit Getins()->updateState("", ExternalText::RenWuMeiWanCheng);
		return false;
	}
	int state = mcc->GetGmode(11).toInt();

	if (w->IsMDIRuningInItmer()) {
		emit Getins()->updateState("", ExternalText::RenWuMeiWanCheng);
		return 0;
	}
	if (state == 4)
		return true;
	else {
		if (state == 1)
			emit Getins()->updateState("", ExternalText::RenWuMeiWanCheng);
		else if (state == 2)
			emit Getins()->updateState("", ExternalText::RenWuMeiWanCheng);
		else if (state == 3)
			emit Getins()->updateState("", ExternalText::ChuYuXianWeiZhuangTai);
		else if (state == -1)
			emit Getins()->updateState("", ExternalText::MeiLianJieKa);
		else
			emit Getins()->updateState("", ExternalText::RenWuMeiWanCheng);
		return false;
	}
}

void SammonFunc::RunMCode(bool FromMDI, const char * code)
{
	if (!SammonFunc::CanDoit())return;
	w->MCodeFromMDI = FromMDI;
	w->isMCode = true;
	w->MCodeName = code;
}
