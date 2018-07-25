#include "ExternalText.h"
#include "QApplication.h"
#include "TrLang.h"
QString ExternalText::OpenSpindleMsg = QStringLiteral("���ڴ�����");
QString ExternalText::StrPause = QStringLiteral("��ͣʱ����ִ���κβ���");
QString ExternalText::GErrorCode = QStringLiteral("��%1��ָ�� %2 ����;����");
QString ExternalText::Nonsupport = QStringLiteral("��%1�в�֧�ֵ�G���룺");
QString ExternalText ::In6Pause = QStringLiteral("��ͣ,������Ļ�ź�");
//wmlabel����״̬
QString ExternalText::ZiDong = QStringLiteral("�Զ�");
QString ExternalText::ShouDong = QStringLiteral("�ֶ�");

//kzklabel ���ƿ�״̬
QString ExternalText::YunDong = QStringLiteral("�˶�");
QString ExternalText::Mang = QStringLiteral("æ");
QString ExternalText::XianWei = QStringLiteral("��λ");

QString ExternalText::KongXian = QStringLiteral("����");
QString ExternalText::CanShuCuoWu = QStringLiteral("��������");
QString ExternalText::TongXinCuoWu = QStringLiteral("ͨ�Ŵ���");
QString ExternalText::DengDai = QStringLiteral("�ȴ�");
QString ExternalText::MeiLianJieKa = QStringLiteral("�������ƿ�");
QString ExternalText::Stop = QStringLiteral("ֹͣ");
//stateLabelWarn
QString ExternalText::RenWuMeiWanCheng = QStringLiteral("��ǰ������δ���");
QString ExternalText::ChuYuXianWeiZhuangTai = QStringLiteral("������λ״̬");


QString ExternalText::XHomeEnabled = QStringLiteral("XHome����");
QString ExternalText::YHomeEnabled = QStringLiteral("YHome����");
QString ExternalText::ZHomeEnabled = QStringLiteral("ZHome����");
QString ExternalText::AHomeEnabled = QStringLiteral("AHome����");

//ToolsParam4
QString ExternalText::In6Test0 = QStringLiteral("T4�ϵ�λʹ���ź�");
 QString ExternalText::In13Test0 = QStringLiteral("T1�ϵ�λʹ���ź�");
 QString ExternalText::In14Test0 = QStringLiteral("T2�ϵ�λʹ���ź�");
 QString ExternalText::In15Test0 = QStringLiteral("T3�ϵ�λʹ���ź�");

 QString ExternalText::In6Test1 = QStringLiteral("��Ļ�ź�");
 QString ExternalText::In13Test1 = QStringLiteral("ѹ�����ؼ���ź�");
 QString ExternalText::In14Test1 = QStringLiteral("��λ�����µ�λ�ź�");
 QString ExternalText::In15Test1 = QStringLiteral("���������µ�λ�ź�");

 QString ExternalText::Out2Text1 = QStringLiteral("��ձÿ���");
 QString ExternalText::Out3Text1 = QStringLiteral("��λ���׿���");
 QString ExternalText::Out4Text1 = QStringLiteral("�������׿���");

 ////DlgRegSoft	
 QString ExternalText::ZHuCheSiXiao = QStringLiteral("���δע�ᣬ��ע��ʧЧ");
 QString ExternalText::ZHuCheDaoQi = QStringLiteral("����쵽��");

 QString ExternalText::GMode14Text0 = QStringLiteral("δע�ᣬ����ʹ��");
 QString ExternalText::GMode14Text1 = QStringLiteral("�ѽ���������һֱʹ��");
 QString ExternalText::GMode14Text3 = QStringLiteral("����ʱ�����ڼ�������¼ʱ�䣬�������ʹ��");
 QString ExternalText::GMode14Text2 = QStringLiteral("ʹ���ѳ��������������������ʹ��");
 QString ExternalText::GMode14Text4 = QStringLiteral("��ע�ᣬ��ʹ�õ�����:%1");

 QString ExternalText::ZhuZhouGuan = QStringLiteral("�����");
 QString ExternalText::ZhuZhouKai = QStringLiteral("���Ὺ");


void ExternalText::ResetLanguage()
{
	OpenSpindleMsg = TrLang::Ins()->GetText(0);
	StrPause = TrLang::Ins()->GetText(1);
	GErrorCode = TrLang::Ins()->GetText(2);
	Nonsupport = TrLang::Ins()->GetText(3);
	In6Pause = TrLang::Ins()->GetText(4);
	//wmlabel����״̬
	ZiDong = TrLang::Ins()->GetText(5);
	ShouDong = TrLang::Ins()->GetText(6);

	//kzklabel ���ƿ�״̬
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
