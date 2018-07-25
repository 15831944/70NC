#pragma once
#include "QObject"

class ExternalText :public QObject {

public:
	//wmlabel¹¤×÷×´Ì¬
	static QString ZiDong;
	static QString ShouDong;

	//kzklabel ¿ØÖÆ¿¨×´Ì¬
	static QString YunDong;
	static QString Mang;
	static QString XianWei;
	static QString KongXian;
	static QString CanShuCuoWu;
	static QString TongXinCuoWu;
	static QString DengDai;
	static QString MeiLianJieKa;
	static QString Stop;
	//stateLabelWarn
	static QString RenWuMeiWanCheng;
	static QString ChuYuXianWeiZhuangTai;

	static QString XHomeEnabled;
	static QString YHomeEnabled;
	static QString ZHomeEnabled;
	static QString AHomeEnabled;

	static QString OpenSpindleMsg;
	static QString StrPause;
	static QString GErrorCode;
	static QString Nonsupport;
	static QString In6Pause;
	//ToolsParam4
	static QString In6Test0;
	static QString In13Test0;
	static QString In14Test0;
	static QString In15Test0;

	static QString In6Test1;
	static QString In13Test1;
	static QString In14Test1;
	static QString In15Test1;

	static QString Out2Text1;
	static QString Out3Text1;
	static QString Out4Text1;

	////DlgRegSoft
	static QString ZHuCheSiXiao;
	static  QString ZHuCheDaoQi;

	static QString GMode14Text0;
	static QString GMode14Text1;
	static QString GMode14Text2;
	static QString GMode14Text3;
	static QString GMode14Text4;

	static QString ZhuZhouKai;
	static QString ZhuZhouGuan;
//////
	static void ResetLanguage();

private:
	ExternalText() {}
	~ExternalText() {}
};