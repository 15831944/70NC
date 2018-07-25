#include "IOSet.h"
#include "ncpod.h"
#include "ReadIni.h"
#include "PasswordDlg.h"
#include "YesOrNo.h"
#include "samcon.h"
#include "LogManager.h"
#include "QStartFromIndex.h"
#include "ExternalText.h"
#include "commontools.h"
#include "TrLang.h"
extern ReadIni readIni;
extern Samcon *w;
#define IOROLE  1314
extern mccdll::MotionControlCard* mcc;
extern QString MyStyle;
extern int VersionType;
extern int VType4;
IOSet::IOSet(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	IconRed = QIcon(":/iconred");
	IconGreen = QIcon(":/icongreen");
	IconTRed = QIcon(":/Tred");
	IconTGreen = QIcon(":/Tgreen");

	IconYes = QIcon(":/enabled_yse");
	IconNo = QIcon(":/enabled_no");
	InitUI();
	InitTable();
	UpdataPolarity();
	InitKeyboardCtrl();
	connect(SammonFunc::Getins(), &SammonFunc::ResetIOText, this, &IOSet::ResetItemText);
	
}

IOSet::~IOSet()
{
}

void IOSet::ResetLanguage()
{
	if(TrLang::Ins()->GetLanguageIndxe())
		ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	else
		ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.TestOn->setText(TrLang::Ins()->GetText(112));
	ui.TestOff->setText(TrLang::Ins()->GetText(113));
	ui.CancelTest->setText(TrLang::Ins()->GetText(114));
	ui.CancelAllTest->setText(TrLang::Ins()->GetText(115));
	ui.TestEnabled->setText(TrLang::Ins()->GetText(116));
	ui.ChangePolarity->setText(TrLang::Ins()->GetText(117));
	QStringList headers;
	headers << TrLang::Ins()->GetText(123) << TrLang::Ins()->GetText(124) << TrLang::Ins()->GetText(125) << TrLang::Ins()->GetText(126) << TrLang::Ins()->GetText(122);
	ui.tableWidget->setHorizontalHeaderLabels(headers);
	InItem[0]->setText(TrLang::Ins()->GetText(127));//输入端口
	InItem[1]->setText(TrLang::Ins()->GetText(128));//X轴原点限位
	InItem[2]->setText(TrLang::Ins()->GetText(129)); //Y轴原点限位
	InItem[3]->setText(TrLang::Ins()->GetText(130));//Z轴原点限位
	InItem[4]->setText(TrLang::Ins()->GetText(131));//A轴原点限位
	InItem[5]->setText(TrLang::Ins()->GetText(132));//对刀
	InItem[6]->setText(TrLang::Ins()->GetText(133));//
	QString  s7;
	if (VersionType == 4) {
		if (VType4 == 1) {
			s7 = ExternalText::In6Test1;
		}
		else if (VType4 == 0) {
			s7 = ExternalText::In6Test0;
		}
	}
	else {
		s7 = TrLang::Ins()->GetText(134);//B轴原点限位
	}
	InItem[7]->setText(s7);
	QString  s8;
	if (VersionType == 2) {
		s8 = TrLang::Ins()->GetText(137) + "/" + TrLang::Ins()->GetText(136); //主轴报警/气缸输入
	}
	else if (VersionType == 4) {
		s8 = TrLang::Ins()->GetText(136);//("主轴报警");
	}
	else {

		s8 = TrLang::Ins()->GetText(135);//("C轴原点限位");
	}
	InItem[8]->setText(s8);
	InItem[9]->setText(TrLang::Ins()->GetText(138));//X轴限位
	InItem[10]->setText(TrLang::Ins()->GetText(139));//Y轴限位
	InItem[11]->setText(TrLang::Ins()->GetText(140));//Z轴限位
	InItem[12]->setText(TrLang::Ins()->GetText(141));//运行
	InItem[13]->setText(TrLang::Ins()->GetText(15));//停止
	QString  s14;
	if (VersionType == 2) {
		s14 = TrLang::Ins()->GetText(142);//8排刀松刀信号
	}
	else if (VersionType == 4) {
		if (VType4 == 1) {
			s14 = ExternalText::In13Test1;
		}
		else if (VType4 == 0) {
			s14 = ExternalText::In13Test0;
		}
	}
	else {
		s14 = TrLang::Ins()->GetText(136);
	}
	InItem[14]->setText(s14);
	QString  s15;
	if (VersionType == 2) {
		s15 = TrLang::Ins()->GetText(143);//8排刀夹刀信号
	}
	else if (VersionType == 4) {
		if (VType4 == 1) {
			s15 = ExternalText::In14Test1;
		}
		else if (VType4 == 0) {
			s15 = ExternalText::In14Test0;
		}
	}
	else {
		s15 = TrLang::Ins()->GetText(144);//备用
	}
	InItem[15]->setText(s15);
	QString  s16;
	if (VersionType == 2) {
		s16 = TrLang::Ins()->GetText(145);//8排刀防尘罩上到位信号
	}
	else if (VersionType == 4) {
		if (VType4 == 1) {
			s16 = ExternalText::In15Test1;
		}
		else if (VType4 == 0) {
			s16 = ExternalText::In15Test0;
		}
	}
	else {
		s16 = TrLang::Ins()->GetText(144);//备用
	}
	InItem[16]->setText(s16);

	OutItem[0]->setText(TrLang::Ins()->GetText(146)); //输出端口
	OutItem[1]->setText(TrLang::Ins()->GetText(147));//主轴正转
	QString  o2;
	if (VersionType == 2) {
		o2 = TrLang::Ins()->GetText(148); //主轴反转

	}
	else if (VersionType == 4) {
		if (VType4 == 1) {
			o2 = ExternalText::Out2Text1;
		}
		else if (VType4 == 0) {
			o2 = TrLang::Ins()->GetText(148);//主轴反转
		}
	}
	else {
		o2 = TrLang::Ins()->GetText(148);//主轴反转
	}
	OutItem[2]->setText(o2);
	QString  o3;
	if (VersionType == 2) {
		o3 = TrLang::Ins()->GetText(149);//喷雾、风冷打开

	}
	else if (VersionType == 4) {
		if (VType4 == 1) {
			o3 = ExternalText::Out3Text1;
		}
		else if (VType4 == 0) {
			o3 = TrLang::Ins()->GetText(149);//喷雾、风冷打开
		}
	}
	else {
		o3 = TrLang::Ins()->GetText(149);//喷雾、风冷打开
	}
	OutItem[3]->setText(o3);
	QString  o4;
	if (VersionType == 2) {
		o4 = TrLang::Ins()->GetText(150);//冷却液、油冷打开

	}
	else if (VersionType == 4) {
		if (VType4 == 1) {
			o4 = ExternalText::Out4Text1;
		}
		else if (VType4 == 0) {
			o4 = TrLang::Ins()->GetText(150);//冷却液、油冷打开
		}
	}
	else {
		o4 = TrLang::Ins()->GetText(150);//冷却液、油冷打开
	}
	OutItem[4]->setText(o4);
	QString  o5;
	if (VersionType == 2) {
		if (readIni.GetToolIsQiGang())
			o5 = TrLang::Ins()->GetText(151);//气缸控制
		else
			o5 = TrLang::Ins()->GetText(154).arg(5);//扩展输出5
	}
	else if (VersionType == 4) {
		o5 = TrLang::Ins()->GetText(152).arg(1);//T1刀控制
	}
	else {
		o5 = TrLang::Ins()->GetText(154).arg(5); //扩展输出5
	}
	OutItem[5]->setText(o5);
	QString  o6;
	if (VersionType == 2) {
		o6 = TrLang::Ins()->GetText(153);//防尘罩控制
	}
	else if (VersionType == 4) {
		o6 = TrLang::Ins()->GetText(152).arg(2);//T2刀控制
	}
	else {
		o6 = TrLang::Ins()->GetText(154).arg(6);//扩展输出6
	}
	OutItem[6]->setText(o6);
	QString  o7;
	if (VersionType == 2) {
		o7 = TrLang::Ins()->GetText(155);//松夹刀控制
	}
	else if (VersionType == 4) {
		o7 = TrLang::Ins()->GetText(152).arg(3);//T3刀控制
	}
	else {
		o7 = TrLang::Ins()->GetText(154).arg(7);//扩展输出7
	}
	OutItem[7]->setText(o7);
	QString  o8;
	if (VersionType == 2) {
		o8 = TrLang::Ins()->GetText(154).arg(8);//扩展输出8
	}
	else if (VersionType == 4) {
		o8 = TrLang::Ins()->GetText(152).arg(4);//T4刀控制
	}
	else {
		o8 = TrLang::Ins()->GetText(154).arg(8);//扩展输出8
	}

	OutItem[8]->setText(o8);
	ResetItemText();
}

void IOSet::MySetFocus()
{
	ui.tableWidget->setFocus();
}

void IOSet::In11Run()
{
	if (w->ui.ToolRun->isEnabled()) {
		w->AcPlay->trigger();

	}
	else if (w->ui.ToolNext->isEnabled()) {
		if (!w->isNeedShowStartLineDlg()) {
			w->AcNext->trigger();
		}
		else {
			if (!w->GetStartLineDlg()->CheckPos()) {
				w->GetStartLineDlg()->InitInfo();

				if (w->GetStartLineDlg()->GetText() == "") {
					w->GetStartLineDlg()->setText();
					if (!w->GetStartLineDlg()->CheckLineEdit())
						return;
					w->GetStartLineDlg()->Run();
					bIn11Run = true;
				}
				else {
					if (!w->GetStartLineDlg()->CheckLineEdit())
						return;
					w->GetStartLineDlg()->Run();
					bIn11Run = true;
				}
			}
			else {
				bIn11Run = true;

			}
		}
	}
}

void IOSet::In6Trigger(bool isTriggered)
{
	if (VersionType != 4 || VType4 != 1)return;
	int en = readIni.GetAxisEnabled();
	if (!SammonFunc::Getins()->readBit(en, 6)) {
		goto OVRE;
	}
	static bool Do = false;
	if (isTriggered) {
		if (!Do) {
			SammonFunc::In6GuangMuXinHao = true;
			SammonFunc::SetSpeedControl_stop();
			Do = true;
		}
	}
	else {
	OVRE:
		SammonFunc::In6GuangMuXinHao = 0;
		Do = false;
	}
}

void IOSet::In11Trigger(bool isTriggered)
{
	int en = readIni.GetAxisEnabled();
	if (!SammonFunc::Getins()->readBit(en, 6)) {
		goto OVRE;
	}
	static bool Do = false;

	if (isTriggered) {
		if (!Do) {
			In11Run();
			Do = true;
		}
	}
	else {
	OVRE:
		Do = false;
	}
}

void IOSet::In12Trigger(bool isTriggered)
{
	static bool Do = false;
	int en = readIni.GetAxisEnabled();
	if (!SammonFunc::Getins()->readBit(en, 6)) {
		goto OVRE;
	}
	if (isTriggered) {
		if (!Do) {
			if (!SammonFunc::Getins()->readBit(en, 12))return;
			w->AcStop->trigger();
			Do = true;
		}
	}
	else {
	OVRE:
		Do = false;
	}
}

void IOSet::CloseOut5() {
	if (VersionType == 2 && readIni.GetToolIsQiGang()) {
		NcPod::getIns()->Write_Bi(0, 5, 1);
	}
}

void IOSet::timerIn11Run()
{
	if (bIn11Run) {
		if (SammonFunc::isStartFormIdx)
			return;
		static int i = 0;
		if (i++ < 3)return;
		i = 0;
		if (mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			w->AcNext->trigger();
			bIn11Run = false;
		}

	}
}

void IOSet::ResetItemText()
{
	for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
		if (VersionType == 2) {
			if (ui.tableWidget->item(i, 0)->text() == "In7") {
				if (readIni.GetToolIsQiGang()) {
					if (readIni.GetTool_In_Enabled_2(7))
						ui.tableWidget->item(i, 4)->setText(TrLang::Ins()->GetText(137));//气缸输入
					else
						ui.tableWidget->item(i, 4)->setText(TrLang::Ins()->GetText(136));//主轴报警
				}
				else
					ui.tableWidget->item(i, 4)->setText(TrLang::Ins()->GetText(136));//主轴报警
			}
			if (ui.tableWidget->item(i, 0)->text() == "Out5") {
				if (readIni.GetToolIsQiGang())
					ui.tableWidget->item(i, 4)->setText(TrLang::Ins()->GetText(151));//气缸控制
				else
					ui.tableWidget->item(i, 4)->setText(TrLang::Ins()->GetText(154).arg(5));//扩展输出5
			}
		}
	}
}

bool IOSet::eventFilter(QObject * obj, QEvent * event)
{

	if (obj == this ||
		obj == ui.tableWidget ||
		obj == ui.TestOn ||
		obj == ui.TestOff ||
		obj == ui.CancelTest || obj == ui.CancelAllTest ||
		obj == ui.TestEnabled ||
		obj == ui.ChangePolarity) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);

			if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.tableWidget->hasFocus();
				bool b2 = ui.TestOn->hasFocus();
				bool b3 = ui.TestOff->hasFocus();
				bool b4 = ui.CancelTest->hasFocus();
				bool b5 = ui.CancelAllTest->hasFocus();
				bool b6 = ui.TestEnabled->hasFocus();
				bool b7 = ui.ChangePolarity->hasFocus();
				if (b1) {
					focusNextChild();
					ui.TestOn->setFocus();
				}
				else if (b2) {
					focusNextChild();
					ui.TestOff->setFocus();

				}
				else if (b3) {
					focusNextChild();
					ui.CancelTest->setFocus();
				}
				else if (b4) {
					focusNextChild();
					ui.CancelAllTest->setFocus();
				}
				else if (b5) {
					focusNextChild();
					ui.TestEnabled->setFocus();
				}
				else if (b6) {
					focusNextChild();
					ui.ChangePolarity->setFocus();
				}
				else if (b7) {
					focusNextChild();
					ui.tableWidget->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					ui.tableWidget->setFocus();
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

void IOSet::keyReleaseEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Return) {
		QWidget* w = focusWidget();
		QPushButton* btSub = dynamic_cast<QPushButton*>(w);
		if (btSub) {
			btSub->clicked(1);
		}
	}
	QTableWidget* tw = dynamic_cast<QTableWidget*>(focusWidget());
	if (tw)
		if (event->key() == Qt::Key_Q ||
			event->key() == Qt::Key_W ||
			event->key() == Qt::Key_E ||
			event->key() == Qt::Key_A ||
			event->key() == Qt::Key_S ||
			event->key() == Qt::Key_D ||
			event->key() == Qt::Key_Z ||
			event->key() == Qt::Key_X ||
			event->key() == Qt::Key_C ||
			event->key() == Qt::Key_T ||
			event->key() == Qt::Key_G ||
			event->key() == Qt::Key_B ||
			event->key() == Qt::Key_F ||
			event->key() == Qt::Key_H) {
			ui.TestOn->setFocus();
		}
	QWidget::keyReleaseEvent(event);
}

void IOSet::InitUI()
{
	ui.tableWidget->setObjectName("IOTableWidget");
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setShowGrid(0);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	InitButton();
}
bool IOSet::MyGetFocus()
{
	bool b1 = ui.tableWidget->hasFocus();
	bool b2 = ui.TestOn->hasFocus();
	bool b3 = ui.TestOff->hasFocus();
	bool b4 = ui.CancelTest->hasFocus();
	bool b5 = ui.CancelAllTest->hasFocus();
	bool b6 = ui.TestEnabled->hasFocus();
	bool b7 = ui.ChangePolarity->hasFocus();
	return b1 || b2 || b3 || b4 || b5 || b6 || b7 || hasFocus();
}
void IOSet::showIconIn()
{
	int flag = NcPod::getIns()->Read_Bi(0, 0);
	static bool Do11 = false;
	static bool Do12 = false;
	static bool Do6 = false;
	for (int i = 0; i <= 15; i++) {
		if (flag&(1 << i)) {
			if (ui.tableWidget->item(i + 1, 1)->text() == "P") {
				ui.tableWidget->item(i + 1, 0)->setIcon(IconGreen);
				if (i == 6) In6Trigger(0);
				if (i == 11) In11Trigger(1);
				if (i == 12) In12Trigger(1);
			}
			else {
				ui.tableWidget->item(i + 1, 0)->setIcon(IconRed);
				if (i == 6) In6Trigger(1);
				if (i == 11) In11Trigger(0);
				if (i == 12) In12Trigger(0);
			}
		}
		else {
			if (ui.tableWidget->item(i + 1, 1)->text() == "N") {
				ui.tableWidget->item(i + 1, 0)->setIcon(IconGreen);
				if (i == 6) In6Trigger(0);
				if (i == 11) In11Trigger(1);
				if (i == 12) In12Trigger(1);
			}
			else {
				ui.tableWidget->item(i + 1, 0)->setIcon(IconRed);
				if (i == 6) In6Trigger(1);
				if (i == 11) In11Trigger(0);
				if (i == 12) In12Trigger(0);
			}

		}
		ui.tableWidget->item(i + 1, 2)->setText(QString::number(flag&(1 << i) ? 1 : 0));
	}
}
void IOSet::showIconOut()
{
	int flag = -1;
	NcPod::getIns()->ReadOutput(0, &flag);
	for (int i = 0; i <= 7; i++) {
		bool is1 = flag&(1 << i);
		if (isTest&(1 << i)) {//该项在测试
			if (is1)
				ui.tableWidget->item(i + InIndex + 1, 0)->setIcon(IconTRed);
			else
				ui.tableWidget->item(i + InIndex + 1, 0)->setIcon(IconTGreen);
		}
		else {
			if (is1)
				ui.tableWidget->item(i + InIndex + 1, 0)->setIcon(IconRed);
			else
				ui.tableWidget->item(i + InIndex + 1, 0)->setIcon(IconGreen);
		}
		ui.tableWidget->item(i + InIndex + 1, 2)->setText(QString::number(is1 ? 1 : 0));
	}
}
bool IOSet::CheckToolSetting() {
	int enabled = readIni.GetAxisEnabled();
	if (enabled&(1 << 4))
		return true;
	else
		return false;
}
int IOSet::GetTriggered(int signalNum)
{

	return (NcPod::getIns()->Read_Bi(0, signalNum));
}
void IOSet::CheckHome()
{

	int enabled = readIni.GetAxisEnabled();
	int enabledflag;
	if (enabled&(1 << 0))
		SammonFunc::XHoneEnabled = true;
	else
		SammonFunc::XHoneEnabled = false;

	if (enabled&(1 << 1))
		SammonFunc::YHoneEnabled = true;
	else
		SammonFunc::YHoneEnabled = false;

	if (enabled&(1 << 2))
		SammonFunc::ZHoneEnabled = true;
	else
		SammonFunc::ZHoneEnabled = false;

	if (enabled&(1 << 3))
		SammonFunc::AHoneEnabled = true;
	else
		SammonFunc::AHoneEnabled = false;

	if (enabled&(1 << 13))
		SammonFunc::BHoneEnabled = true;
	else
		SammonFunc::BHoneEnabled = false;

	if (enabled&(1 << 14))
		SammonFunc::CHoneEnabled = true;
	else
		SammonFunc::CHoneEnabled = false;
}
void IOSet::InitButton()
{//输入0-15，输出 1-8，0是全部
//输出 测试功能，，输入 使能、极性 修改功能
	connect(ui.TestOn, &QPushButton::clicked, [this]() {
		if (mcc->GetGmode(11).toInt() == 3)return;
		int row = ui.tableWidget->currentRow();
		if (row > InIndex) {
			int signalnum = ui.tableWidget->item(row, 0)->data(IOROLE).toInt();
			if (isTest == 0)
				NcPod::getIns()->ReadOutput(0, &OutFlag);//开始测试 ，保存状态
			isTest = isTest | (1 << (signalnum - 1));
			NcPod::getIns()->Write_Bi(0, signalnum, 0);
		}
	});
	connect(ui.TestOff, &QPushButton::clicked, [this]() {
		if (mcc->GetGmode(11).toInt() == 3)return;
		int row = ui.tableWidget->currentRow();
		if (row > InIndex) {
			int signalnum = ui.tableWidget->item(row, 0)->data(IOROLE).toInt();
			if (isTest == 0)
				NcPod::getIns()->ReadOutput(0, &OutFlag);//开始测试 ，保存状态
			isTest = isTest | (1 << (signalnum - 1));
			NcPod::getIns()->Write_Bi(0, signalnum, 1);
		}
	});
	connect(ui.CancelTest, &QPushButton::clicked, [this]() {
		if (mcc->GetGmode(11).toInt() == 3)return;
		int row = ui.tableWidget->currentRow();
		if (row > InIndex) {
			int signalnum = ui.tableWidget->item(row, 0)->data(IOROLE).toInt();
			isTest = isTest & (~(1 << (signalnum - 1)));
			if (isTest == 0) {
				for (int i = 0; i <= 7; i++) {

					NcPod::getIns()->Write_Bi(0, i + 1, OutFlag&(1 << i));
				}
			}
		}
	});
	connect(ui.CancelAllTest, &QPushButton::clicked, [this]() {
		if (mcc->GetGmode(11).toInt() == 3)return;
		if (isTest == 0)
			return;
		isTest = 0;
		for (int i = 0; i <= 7; i++) {
			NcPod::getIns()->Write_Bi(0, i + 1, OutFlag&(1 << i));
		}
	});



	connect(ui.TestEnabled, &QPushButton::clicked, [this]() {
		int row = ui.tableWidget->currentRow();
		if (row > 0 && row < InIndex) {
			PasswordDlg * psd = new PasswordDlg(1, TrLang::Ins()->GetText(156));//请输入开发商密码
			connect(psd, &PasswordDlg::ChioceYes, [this]() {
				changeEnabled();
			});
		}

	});
	connect(ui.ChangePolarity, &QPushButton::clicked, [this]() {
		int row = ui.tableWidget->currentRow();
		if (row > 0 && row < InIndex) {
			PasswordDlg * psd = new PasswordDlg(1, TrLang::Ins()->GetText(156));//请输入开发商密码
			connect(psd, &PasswordDlg::ChioceYes, [this]() {
				int row = ui.tableWidget->currentRow();
				if (row > 0 && row < InIndex) {
					int signalnum = ui.tableWidget->item(row, 0)->data(IOROLE).toInt();
					int polarity = readIni.GetIOinPolarity();
					int polarityflagflag = (polarity&(1 << row - 1)) ? 0 : 1;

					int InEnabled = readIni.GetAxisEnabled();
					int InEnabledflag = (InEnabled&(1 << row - 1)) ? 1 : 0;

					QString str = polarityflagflag ? "P" : "N";
					if (signalnum == 5) {
						NcPod::getIns()->Set_IoIn_Mod(0, signalnum, 16, polarityflagflag, InEnabledflag);
					}
					else if (signalnum >= 8 && signalnum <= 10) {
						int LmtNum;

						if (signalnum == 8)
							LmtNum = 1;
						else if (signalnum == 9)
							LmtNum = 2;
						else if (signalnum == 10)
							LmtNum = 3;

						NcPod::getIns()->Set_IoIn_Mod(0, signalnum, LmtNum, polarityflagflag, InEnabledflag);
					}
					else
						NcPod::getIns()->Set_IoIn_Mod(0, signalnum, 0, polarityflagflag, InEnabledflag);
					ui.tableWidget->item(row, 1)->setText(str);
					readIni.SetIOinPolarity(polarity ^ (1 << row - 1));
					LogManager::getIns()->appendLog(TrLang::Ins()->GetText(157) + QString::number(signalnum));//修改输入极性：
				}
			});
		}
	});

	ui.TestOn->IsIOSet = 1;
	ui.TestOff->IsIOSet = 1;
	ui.CancelTest->IsIOSet = 1;
	ui.CancelAllTest->IsIOSet = 1;
	ui.TestEnabled->IsIOSet = 1;
	ui.ChangePolarity->IsIOSet = 1;
}

void IOSet::changeEnabled()
{
	int row = ui.tableWidget->currentRow();

	int signalnum = ui.tableWidget->item(row, 0)->data(IOROLE).toInt();
	int polarity = readIni.GetIOinPolarity();
	int polarityflag = (polarity&(1 << row - 1)) ? 1 : 0;

	int InEnabled = readIni.GetAxisEnabled();
	int InEnabledflag = (InEnabled&(1 << row - 1)) ? 0 : 1;
	if (signalnum == 5) {
		NcPod::getIns()->Set_IoIn_Mod(0, signalnum, 16, polarityflag, InEnabledflag);
	}
	else if (signalnum >= 8 && signalnum <= 10) {
		if (!InEnabledflag) {
			NcPod::getIns()->OpenMotoionDevci(0);
			NcPod::getIns()->UnlimtSigna(0, 1);
		}
		int LmtNum;
		if (signalnum == 8)
			LmtNum = 1;
		else if (signalnum == 9)
			LmtNum = 2;
		else if (signalnum == 10)
			LmtNum = 3;


		NcPod::getIns()->Set_IoIn_Mod(0, signalnum, LmtNum, polarityflag, InEnabledflag);
	}
	else
		NcPod::getIns()->Set_IoIn_Mod(0, signalnum, 0, polarityflag, InEnabledflag);
	ui.tableWidget->item(row, 3)->setIcon(InEnabledflag ? IconYes : IconNo);
	readIni.SetAxisEnabled(InEnabled ^ (1 << row - 1));
	LogManager::getIns()->appendLog(TrLang::Ins()->GetText(158) + QString::number(signalnum));//修改输入使能：

}
void IOSet::UpdataPolarity()
{
	int Polarity = readIni.GetIOinPolarity();
	int enabled = readIni.GetAxisEnabled();
	int Polarityflag;
	QString str;
	int enabledflag;
	for (int i = 0; i <= 15; i++) {
		int signalnum = ui.tableWidget->item(i + 1, 0)->data(IOROLE).toInt();
		Polarityflag = Polarity&(1 << i) ? 1 : 0;
		enabledflag = enabled&(1 << i) ? 1 : 0;
		str = Polarity&(1 << i) ? "P" : "N";
		if (signalnum == 5) {
			NcPod::getIns()->Set_IoIn_Mod(0, signalnum, 16, Polarityflag, enabledflag);
		}
		else if ((signalnum <= 10 & signalnum >= 8)) {

			int LmtNum;
			if (signalnum == 8)
				LmtNum = 1;
			else if (signalnum == 9)
				LmtNum = 2;
			else if (signalnum == 10)
				LmtNum = 3;

			NcPod::getIns()->Set_IoIn_Mod(0, signalnum, LmtNum, Polarityflag, enabledflag);

		}
		else
			NcPod::getIns()->Set_IoIn_Mod(0, signalnum, 0, Polarityflag, enabledflag);
		if (!enabledflag) {
			ui.tableWidget->item(i + 1, 3)->setIcon(IconNo);
		}
		ui.tableWidget->item(i + 1, 1)->setText(str);
	}
}

void IOSet::InitKeyboardCtrl()
{
	installEventFilter(this);
	ui.tableWidget->installEventFilter(this);
	ui.TestOn->installEventFilter(this);
	ui.TestOff->installEventFilter(this);
	ui.CancelTest->installEventFilter(this);
	ui.CancelAllTest->installEventFilter(this);
	ui.TestEnabled->installEventFilter(this);
	ui.ChangePolarity->installEventFilter(this);
}

void IOSet::InitTable()
{
	QFont font;
	font.setBold(true);
	font.setPixelSize(12);
	//font.setUnderline(true);

	int row = 0;

	InItem[0] = new QTableWidgetItem("");//输入端口
	InItem[0]->setFont(font);
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 25);
	ui.tableWidget->setItem(row, 0, InItem[0]);
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem(""));
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem(""));
	ui.tableWidget->item(row, 0)->setFlags(ui.tableWidget->item(row, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(row++, 0, 1, 5);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In0"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 1 - 1);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[1] = new QTableWidgetItem("");//X轴原点限位
	ui.tableWidget->setItem(row++, 4, InItem[1]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In1"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 2 - 1);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[2] = new QTableWidgetItem(""); //Y轴原点限位
	ui.tableWidget->setItem(row++, 4, InItem[2]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In2"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 3 - 1);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[3] = new QTableWidgetItem("");//Z轴原点限位
	ui.tableWidget->setItem(row++, 4, InItem[3]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In3"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 4 - 1);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[4] = new QTableWidgetItem("");//A轴原点限位
	ui.tableWidget->setItem(row++, 4, InItem[4]);



	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In4"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 4);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[5] = new QTableWidgetItem("");//对刀
	ui.tableWidget->setItem(row++, 4, InItem[5]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In5"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 7 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[6] = new QTableWidgetItem("");//
	ui.tableWidget->setItem(row++, 4, InItem[6]);


	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In6"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 8 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[7] = new QTableWidgetItem("");
	ui.tableWidget->setItem(row++, 4, InItem[7]);



	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In7"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 9 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[8] = new QTableWidgetItem("");
	ui.tableWidget->setItem(row++, 4, InItem[8]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In8"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 10 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[9] = new QTableWidgetItem("");//X轴限位
	ui.tableWidget->setItem(row++, 4, InItem[9]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In9"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 11 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[10] = new QTableWidgetItem("");//Y轴限位
	ui.tableWidget->setItem(row++, 4, InItem[10]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In10"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 12 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[11] = new QTableWidgetItem("");//Z轴限位
	ui.tableWidget->setItem(row++, 4, InItem[11]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In11"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 13 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[12] = new QTableWidgetItem("");//运行
	ui.tableWidget->setItem(row++, 4, InItem[12]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In12"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 14 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[13] = new QTableWidgetItem("");//停止
	ui.tableWidget->setItem(row++, 4, InItem[13]);


	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In13"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 15 - 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[14] = new QTableWidgetItem("");
	ui.tableWidget->setItem(row++, 4, InItem[14]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In14"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 14);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[15] = new QTableWidgetItem("");
	ui.tableWidget->setItem(row++, 4, InItem[15]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "In15"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 15);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	InItem[16] = new QTableWidgetItem("");
	ui.tableWidget->setItem(row++, 4, InItem[16]);

	InIndex = row;
	/////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////
	OutItem[0] = new QTableWidgetItem("");//输出端口
	OutItem[1] = new QTableWidgetItem("");//主轴正转
	OutItem[2] = new QTableWidgetItem("");
	OutItem[3] = new QTableWidgetItem("");
	OutItem[4] = new QTableWidgetItem("");
	OutItem[5] = new QTableWidgetItem("");
	OutItem[6] = new QTableWidgetItem("");
	OutItem[7] = new QTableWidgetItem("");
	OutItem[8] = new QTableWidgetItem("");

	OutItem[0]->setFont(font);
	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 25);
	ui.tableWidget->setItem(row, 0, OutItem[0]);
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem(""));
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem(""));
	ui.tableWidget->item(row, 0)->setFlags(ui.tableWidget->item(row, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(row++, 0, 1, 5);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out1"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 1);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[1]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out2"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 2);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[2]);


	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out3"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 3);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[3]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out4"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 4);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[4]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out5"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 5);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[5]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out6"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 6);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[6]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out7"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 7);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[7]);

	ui.tableWidget->insertRow(row);
	ui.tableWidget->setRowHeight(row, 20);
	ui.tableWidget->setItem(row, 0, new QTableWidgetItem(IconRed, "Out8"));
	ui.tableWidget->setItem(row, 1, new QTableWidgetItem("N"));
	ui.tableWidget->item(row, 0)->setData(IOROLE, 8);
	ui.tableWidget->setItem(row, 2, new QTableWidgetItem("")); ui.tableWidget->setItem(row, 3, new QTableWidgetItem(IconYes, ""));
	ui.tableWidget->setItem(row++, 4, OutItem[8]);

}