#include "ExternalText.h"
#include "QApplication.h"
#include "TrLang.h"
QString ExternalText::OpenSpindleMsg = QStringLiteral("正在打开主轴");
QString ExternalText::StrPause = QStringLiteral("暂停时不能执行任何操作");
QString ExternalText::GErrorCode = QStringLiteral("第%1行指令 %2 有误;例：");
QString ExternalText::Nonsupport = QStringLiteral("第%1行不支持的G代码：");
QString ExternalText ::In6Pause = QStringLiteral("暂停,触发光幕信号");
//wmlabel工作状态
QString ExternalText::ZiDong = QStringLiteral("自动");
QString ExternalText::ShouDong = QStringLiteral("手动");

//kzklabel 控制卡状态
QString ExternalText::YunDong = QStringLiteral("运动");
QString ExternalText::Mang = QStringLiteral("忙");
QString ExternalText::XianWei = QStringLiteral("限位");

QString ExternalText::KongXian = QStringLiteral("空闲");
QString ExternalText::CanShuCuoWu = QStringLiteral("参数错误");
QString ExternalText::TongXinCuoWu = QStringLiteral("通信错误");
QString ExternalText::DengDai = QStringLiteral("等待");
QString ExternalText::MeiLianJieKa = QStringLiteral("请插入控制卡");
QString ExternalText::Stop = QStringLiteral("停止");
//stateLabelWarn
QString ExternalText::RenWuMeiWanCheng = QStringLiteral("当前任务尚未完成");
QString ExternalText::ChuYuXianWeiZhuangTai = QStringLiteral("处于限位状态");


QString ExternalText::XHomeEnabled = QStringLiteral("XHome禁用");
QString ExternalText::YHomeEnabled = QStringLiteral("YHome禁用");
QString ExternalText::ZHomeEnabled = QStringLiteral("ZHome禁用");
QString ExternalText::AHomeEnabled = QStringLiteral("AHome禁用");

//ToolsParam4
QString ExternalText::In6Test0 = QStringLiteral("T4上到位使能信号");
 QString ExternalText::In13Test0 = QStringLiteral("T1上到位使能信号");
 QString ExternalText::In14Test0 = QStringLiteral("T2上到位使能信号");
 QString ExternalText::In15Test0 = QStringLiteral("T3上到位使能信号");

 QString ExternalText::In6Test1 = QStringLiteral("光幕信号");
 QString ExternalText::In13Test1 = QStringLiteral("压力开关检测信号");
 QString ExternalText::In14Test1 = QStringLiteral("定位气缸下到位信号");
 QString ExternalText::In15Test1 = QStringLiteral("推料气缸下到位信号");

 QString ExternalText::Out2Text1 = QStringLiteral("真空泵控制");
 QString ExternalText::Out3Text1 = QStringLiteral("定位气缸控制");
 QString ExternalText::Out4Text1 = QStringLiteral("退料气缸控制");

 ////DlgRegSoft	
 QString ExternalText::ZHuCheSiXiao = QStringLiteral("软件未注册，或注册失效");
 QString ExternalText::ZHuCheDaoQi = QStringLiteral("软件快到期");

 QString ExternalText::GMode14Text0 = QStringLiteral("未注册，不能使用");
 QString ExternalText::GMode14Text1 = QStringLiteral("已解锁，可以一直使用");
 QString ExternalText::GMode14Text3 = QStringLiteral("电脑时间早于加密锁记录时间，软件不能使用");
 QString ExternalText::GMode14Text2 = QStringLiteral("使用已超过允许天数，软件不能使用");
 QString ExternalText::GMode14Text4 = QStringLiteral("已注册，已使用的天数:%1");

 QString ExternalText::ZhuZhouGuan = QStringLiteral("主轴关");
 QString ExternalText::ZhuZhouKai = QStringLiteral("主轴开");


void ExternalText::ResetLanguage()
{
	OpenSpindleMsg = TrLang::Ins()->GetText(0);
	StrPause = TrLang::Ins()->GetText(1);
	GErrorCode = TrLang::Ins()->GetText(2);
	Nonsupport = TrLang::Ins()->GetText(3);
	In6Pause = TrLang::Ins()->GetText(4);
	//wmlabel工作状态
	ZiDong = TrLang::Ins()->GetText(5);
	ShouDong = TrLang::Ins()->GetText(6);

	//kzklabel 控制卡状态
	YunDong = TrLang::Ins()->GetText(7);
	Mang = TrLang::Ins()->GetText(8);
	XianWei = TrLang::Ins()->GetText(9);

	KongXian = TrLang::Ins()->GetText(10);
	CanShuCuoWu = TrLang::Ins()->GetText(11);
	TongXinCuoWu = TrLang::Ins()->GetText(12);
	DengDai = TrLang::Ins()->GetText(13);
	MeiLianJieKa = TrLang::Ins()->GetText(14);
	Stop = TrLang::Ins()->GetText(15);
	//stateLabelWarn
	RenWuMeiWanCheng = TrLang::Ins()->GetText(16);
	ChuYuXianWeiZhuangTai = TrLang::Ins()->GetText(17);


	XHomeEnabled = TrLang::Ins()->GetText(18);
	YHomeEnabled = TrLang::Ins()->GetText(19);
	ZHomeEnabled = TrLang::Ins()->GetText(20);
	AHomeEnabled = TrLang::Ins()->GetText(21);

	//ToolsParam4
	In6Test0 = TrLang::Ins()->GetText(22);
	In13Test0 = TrLang::Ins()->GetText(23);
	In14Test0 = TrLang::Ins()->GetText(24);
	In15Test0 = TrLang::Ins()->GetText(25);

	In6Test1 = TrLang::Ins()->GetText(26);
	In13Test1 = TrLang::Ins()->GetText(27);
	In14Test1 = TrLang::Ins()->GetText(28);
	In15Test1 = TrLang::Ins()->GetText(29);

	Out2Text1 = TrLang::Ins()->GetText(30);
	Out3Text1 = TrLang::Ins()->GetText(31);
	Out4Text1 = TrLang::Ins()->GetText(32);

	////DlgRegSoft	
	ZHuCheSiXiao = TrLang::Ins()->GetText(33);
	ZHuCheDaoQi = TrLang::Ins()->GetText(34);

	GMode14Text0 = TrLang::Ins()->GetText(35);
	GMode14Text1 = TrLang::Ins()->GetText(36);
	GMode14Text2 = TrLang::Ins()->GetText(37);
	GMode14Text4 = TrLang::Ins()->GetText(38);

	ZhuZhouGuan = TrLang::Ins()->GetText(40);
	ZhuZhouKai = TrLang::Ins()->GetText(41);

}
