#include "DlgSetParameter.h"

#define PARAMROLE  1357
#include "DlgParamNum.h"
#include "DlgParamString.h"
#include "ReadIni.h"
#include"ncpod.h"
#include "LogManager.h"
#include"PasswordDlg.h"
#include "TrLang.h"
extern QString MyStyle;
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern int VersionType;
DlgSetParameter::DlgSetParameter(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	InitUi();

//	InitTable();

//	filterRule();
	InitParam();
}

DlgSetParameter::~DlgSetParameter()
{
}

void DlgSetParameter::ResetLanguage()
{
	setDlgName(TrLang::text(82));
	mRow = 0;
	hide();
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->clear();
	InitTable();
	filterRule();
	ui.lineEdit->setPlaceholderText(TrLang::text(325));
	ui.rbUser->setText(TrLang::text(326));
	ui.rbManufacturer->setText(TrLang::text(327));
	ui.btParamCaoz->setText(TrLang::text(328));
	ui.btParamGeiJZ->setText(TrLang::text(329));
	ui.btParamTool->setText(TrLang::text(365));
	ui.btParamAll->setText(TrLang::text(330));
	ui.btSearch->setText(TrLang::text(119));
	ui.btClose->setText(TrLang::text(222));
	QStringList lables;
	lables << TrLang::text(332) << TrLang::text(322) << TrLang::text(323) << TrLang::text(331)<<  TrLang::text(324) << TrLang::text(122);
	ui.tableWidget->setHorizontalHeaderLabels(lables);
}

void DlgSetParameter::showEvent(QShowEvent * event)
{
	for (int i = 0; i < ui.tableWidget->rowCount(); i++) {
		if (ui.tableWidget->item(i, 0)->text() == "N12002") {			
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(130)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N12003") {
			ui.tableWidget->item(i, 2)->setText(readIni.GetFeedrate());
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31002") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(250)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31008") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(252)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31014") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(254)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31020") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(256)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31026") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(258)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31032") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(260)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31038") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(262)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31044") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(264)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31050") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(266)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31051") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(268)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31052") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(270)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31053") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(272)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31054") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(274)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31055") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(276)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31056") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(278)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N31057") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(280)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N25001") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(110) / mcc->GetParameterValue(120)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N25002") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(111) / mcc->GetParameterValue(121)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N25003") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(112) / mcc->GetParameterValue(122)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N25019") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(113) / mcc->GetParameterValue(123)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N25020") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(114) / mcc->GetParameterValue(124)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N25021") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(115) / mcc->GetParameterValue(125)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21012") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(320)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21013") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(321)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21014") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(322)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21015") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(323)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21016") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(324)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21017") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(325)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21018") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(330)));
			
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21019") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(331)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21020") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(332)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21021") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(333)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21022") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(334))); 
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21023") {
			ui.tableWidget->item(i, 2)->setText(QString::number(mcc->GetParameterValue(335)));
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21024") {
			char str[20] = {};
			sprintf(str, "%.3f", mcc->GetParameterValue(380) / (mcc->GetParameterValue(110) / mcc->GetParameterValue(120)));
			ui.tableWidget->item(i, 2)->setText(str);
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21025") {
			char str[20] = {};
			sprintf(str, "%.3f", mcc->GetParameterValue(381) / (mcc->GetParameterValue(111) / mcc->GetParameterValue(121)));
			ui.tableWidget->item(i, 2)->setText(str);
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21026") {
			char str[20] = {};
			sprintf(str, "%.3f", mcc->GetParameterValue(382) / (mcc->GetParameterValue(112) / mcc->GetParameterValue(122)));
			ui.tableWidget->item(i, 2)->setText(str);
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21027") {
			char str[20] = {};
			sprintf(str, "%.3f", mcc->GetParameterValue(38) / (mcc->GetParameterValue(113) / mcc->GetParameterValue(123)));
			ui.tableWidget->item(i, 2)->setText(str);
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21028") {
			char str[20] = {};
			sprintf(str, "%.3f", mcc->GetParameterValue(384) / (mcc->GetParameterValue(114) / mcc->GetParameterValue(124)));
			ui.tableWidget->item(i, 2)->setText(str);
		}
		else if (ui.tableWidget->item(i, 0)->text() == "N21029") {
			char str[20] = {};
			sprintf(str, "%.3f", mcc->GetParameterValue(385) / (mcc->GetParameterValue(115) / mcc->GetParameterValue(125)));
			ui.tableWidget->item(i, 2)->setText(str);
		}

	}
}

void DlgSetParameter::hideEvent(QHideEvent * hideEvent)
{
	mcc->SaveParameterValue();
	readIni.sync();
}

void DlgSetParameter::InitUi()
{	
	setLine();

	ui.tableWidget->setObjectName("ParameterTableWidget");

	connect(ui.btClose, &QPushButton::clicked, [this]() {close(); });
	connect(ui.DlgC, &QPushButton::clicked, [this]() {close();});
	connect(ui.tableWidget, &QTableWidget::cellDoubleClicked, [this](int row, int col) {

		if (ui.tableWidget->item(row, 2)->data(PARAMROLE).toInt() == _NUM)
		{
			DlgParamNum * dpn = new DlgParamNum(this);
			QString& id = ui.tableWidget->item(row, 0)->text();
			QString& value = ui.tableWidget->item(row, 2)->text();
			QString& s1 = ui.tableWidget->item(row, 1)->text();
			QString &s2 = ui.tableWidget->item(row, 3)->text();
			QString& s3 = ui.tableWidget->item(row, 5)->text();
			dpn->setText(id,value, s1, s2, s3);
			connect(dpn, &DlgParamNum::ChioceYes, [this,dpn]() {			
				ui.tableWidget->item(ui.tableWidget->currentRow(), 2)->setText(dpn->Text());
				QString id = ui.tableWidget->item(ui.tableWidget->currentRow(), 0)->text();
				LogManager::getIns()->appendLog(TrLang::text(321) + id);
				if( id == ("N11001")|| id == ("N12003")) {
					emit updateText();
				}
				if (id == ("N25007")|| id == ("N25008") || id == ("N25009") || 
					id == ("N25025") || id == ("N25026") || id == ("N25027") || 
					(id == ("N25010") || id == ("N25011") || id == ("N25012") ||
						id == ("N25028") || id == ("N25029") || id == ("N25030") )) {
					setSoftLm();
				}
			});

		}
		else if (ui.tableWidget->item(row, 2)->data(PARAMROLE).toInt() == _String)
		{		
			DlgParamString*dps = new DlgParamString(this); 
			QString& id = ui.tableWidget->item(row, 0)->text();
			QString &value = ui.tableWidget->item(row, 2)->text();
			QString &s1 = ui.tableWidget->item(row, 1)->text();
			QString &s2 = ui.tableWidget->item(row, 5)->text();
			dps->setText(id,value, s1, s2);
			connect(dps, &DlgParamString::ChioceYes, [this,dps,id]() {	
				ui.tableWidget->item(ui.tableWidget->currentRow(), 2)->setText(dps->Text());
				LogManager::getIns()->appendLog(TrLang::text(321) + id);
			});		
		}
	});
	connect(ui.tableWidget, &QTableWidget::cellClicked, [this](int row, int col) {
		ui.textBrowser->clear();
		if (ui.tableWidget->item(row, 2)->data(PARAMROLE).toInt() == _NOV)
			return;
		ui.textBrowser->append(TrLang::text(322)+":" +ui.tableWidget->item(row, 1)->text());
		ui.textBrowser->append(TrLang::text(323) + ":" +ui.tableWidget->item(row, 2)->text()+" "+ ui.tableWidget->item(row, 3)->text());
		ui.textBrowser->append(TrLang::text(324) + ":" +ui.tableWidget->item(row, 4)->text());
		ui.textBrowser->append(TrLang::text(122) + ":" +ui.tableWidget->item(row, 5)->text());
	});

	
	connect(ui.rbUser, &QPushButton::clicked, [this]() {
		curRadioButton = ui.rbUser;
		filterRule();

	});
	connect(ui.rbManufacturer, &QPushButton::clicked, [this]() {
		PasswordDlg* psd = new  PasswordDlg(1, TrLang::text(156));//请输入开发商密码

		connect(psd, &PasswordDlg::ChioceYes, [this]() {
			curRadioButton = ui.rbManufacturer;
			filterRule();
		});
	});

	connect(ui.btParamAll, &QPushButton::clicked, [this]() {
		curPushButton = ui.btParamAll;
		filterRule();
	});

	connect(ui.btParamCaoz, &QPushButton::clicked, [this]() {
		curPushButton = ui.btParamCaoz;
		filterRule();

	});
	connect(ui.btParamGeiJZ, &QPushButton::clicked, [this]() {
		curPushButton = ui.btParamGeiJZ;
		filterRule();
	});
	connect(ui.btParamTool, &QPushButton::clicked, [this]() {
		curPushButton = ui.btParamTool;
		filterRule();
	});
	ui.btParamIO->setVisible(0);

	connect(ui.btSearch, &QPushButton::clicked, [this]() {
		QString str = ui.lineEdit->text();
		int rowCount = ui.tableWidget->rowCount();
		static int curI = 0;
		for (int i = curI; i < rowCount; i++)
		{
			if ((ui.tableWidget->item(i, 0)->text().contains(str)|| ui.tableWidget->item(i, 1)->text().contains(str))&& !ui.tableWidget->isRowHidden(i))
			{
				ui.tableWidget->setCurrentCell(i, 0);
				curI = i+1;
				return;
			}
		}
		curI = 0;
	});

	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setColumnWidth(0, 100);
	ui.tableWidget->setColumnWidth(1, 140);
	ui.tableWidget->setColumnWidth(2, 80);
	ui.tableWidget->setColumnWidth(3, 80);
	ui.tableWidget->setColumnWidth(4, 100);
	ui.tableWidget->setColumnWidth(5, 300);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setShowGrid(false);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	mFont.setBold(true);
	mFont.setPixelSize(12);
	mFont.setUnderline(true);

	mFont2.setBold(true);
	mFont2.setPixelSize(12);
	
	ui.rbUser->setChecked(true);
	curRadioButton = ui.rbUser;
	curPushButton = ui.btParamAll;

}

void DlgSetParameter::filterRule()
{		
	if (curRadioButton == ui.rbUser) {
		if (curPushButton == ui.btParamAll)
		{
			filterAll(User_ALL);
		}
		else	if (curPushButton == ui.btParamCaoz) {
			filterUser(User_CaoZ);
		}
		else if (curPushButton == ui.btParamGeiJZ) {
			filterUser(User_GeiJZ);
		}
		else if (curPushButton == ui.btParamTool) {
			filterUser(User_Tool);
		}

	}
	else if (curRadioButton == ui.rbManufacturer)
	{
		if (curPushButton == ui.btParamAll)
		{
			filterAll(Manufacturer_All);
		}
		else if (curPushButton == ui.btParamCaoz) {
			filterManufacturer(Manufacturer_CaoZ,User_CaoZ);
		}
		else if (curPushButton == ui.btParamGeiJZ) {
			filterManufacturer(Manufacturer_GeiJZ,User_GeiJZ);
		}
		else if (curPushButton == ui.btParamTool) {
			filterManufacturer(Manufacturer_Tool, User_Tool);
		}
	}
}

void DlgSetParameter::ShowICon()
{
	ui.btParamAll->setIcon(QIcon());
	ui.btParamCaoz->setIcon(QIcon());
	ui.btParamGeiJZ->setIcon(QIcon());
	ui.btParamTool->setIcon(QIcon());
	curPushButton->setIcon(QIcon(":/icon/000.png"));
}

void DlgSetParameter::filterUser(ParamType type)
{
	int rowCount = ui.tableWidget->rowCount();
	ShowICon();
	for (int i = 0; i < rowCount; i++)
	{
		if (ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == type)
		{
			ui.tableWidget->setRowHidden(i, false);
		}
		else {
			ui.tableWidget->setRowHidden(i, true);
		}
	}
}

void DlgSetParameter::filterManufacturer(ParamType fact, ParamType user)
{
	int rowCount = ui.tableWidget->rowCount();
	ShowICon();
	for (int i = 0; i < rowCount; i++)
	{
		if (/*ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == user|| */ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == fact)
		{
			ui.tableWidget->setRowHidden(i, false);
		}
		else {
			ui.tableWidget->setRowHidden(i, true);
		}
	}
}

void DlgSetParameter::filterAll(ParamType type)
{
	int rowCount = ui.tableWidget->rowCount();
	ShowICon();
	if (type == User_ALL) {
		for (int i = 0; i < rowCount; i++)
		{
			if (ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_CaoZ ||
				ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_GeiJZ || 
				ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_IO||
				ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_Tool
				){
				ui.tableWidget->setRowHidden(i, false);
			}
			else {
				ui.tableWidget->setRowHidden(i, true);
			}
		}
	}
	else {
		for (int i = 0; i < rowCount; i++)
		{
			if (ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_CaoZ ||
				ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_GeiJZ ||
				ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_IO ||
				ui.tableWidget->item(i, 0)->data(PARAMROLE).toInt() == User_Tool
				) {
				ui.tableWidget->setRowHidden(i, true);
			}
			else {
				ui.tableWidget->setRowHidden(i, false);
			}
		}
	}
}

void DlgSetParameter::setSoftLm()
{
	bool s_sle = readIni.GetLmtEnalbe();
	NcPod::getIns()->Set_SoftLmtEnalb(0, s_sle);
	int mcx = (int)(mcc->GetParameterValue(110) / mcc->GetParameterValue(120));
	int mcy = (int)(mcc->GetParameterValue(111) / mcc->GetParameterValue(121));
	int mcz = (int)(mcc->GetParameterValue(112) / mcc->GetParameterValue(122));
	int mca = (int)(mcc->GetParameterValue(113) / mcc->GetParameterValue(123));
	int mcb = (int)(mcc->GetParameterValue(114) / mcc->GetParameterValue(124));
	int mcC = (int)(mcc->GetParameterValue(115) / mcc->GetParameterValue(125));
	NcPod::getIns()->SetSoftLm(0, 0, readIni.GetXPosPlus().toInt()*mcx, readIni.GetXPosMinus().toInt()*mcx);
	NcPod::getIns()->SetSoftLm(0, 1, readIni.GetYPosPlus().toInt()*mcy, readIni.GetYPosMinus().toInt()*mcy);
	NcPod::getIns()->SetSoftLm(0, 2, readIni.GetZPosPlus().toInt()*mcz, readIni.GetZPosMinus().toInt()*mcz);

	NcPod::getIns()->SetSoftLm(0, 3, readIni.GetAPosPlus().toInt()*mca, readIni.GetAPosMinus().toInt()*mca);
	NcPod::getIns()->SetSoftLm(0, 4, readIni.GetBPosPlus().toInt()*mcb, readIni.GetBPosMinus().toInt()*mcb);
	NcPod::getIns()->SetSoftLm(0, 5, readIni.GetCPosPlus().toInt()*mcC, readIni.GetCPosMinus().toInt()*mcC);

	NcPod::getIns()->SetHomeLmt(true);
}

void DlgSetParameter::rowN11() {

	QTableWidgetItem* item = new QTableWidgetItem(TrLang::text(43));// 操作
	item->setFont(mFont);
	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 25);
	ui.tableWidget->setItem(mRow, 0, item);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_CaoZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N11002"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(248)));//宏代码延时
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString("%1").arg(readIni.GetMWaitSignalItme())));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("s"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));//立即生效
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(249)));//宏代码等待IO信号触发的延时时间,单位：秒
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N11003"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(253)));//确认提示
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetSureMsg() ? TrLang::text(246) : TrLang::text(247)));//是     否
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem());
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(250)));//是否弹出确认窗口，例如：清除工件坐标是否弹出确认操作
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N12001"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(251)));//安全高度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetSafetyHeight()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(252)));//相对于工件坐标零点计算，系统认为在此高度上水平运动是安全的。在执行回零点操作和断点继续操作时使用，设定范围：[5，500]mm
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N12002"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(254)));//空行速度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(("5000")));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(255)));//刀具G0空行时的速度
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N12003"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(256)));//默认进给速度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetFeedrate()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(257)));//自动加工时，系统默认的进给速度，设定范围(150，20000]mm/min
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N12004"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(258)));//使用默认进给速度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetUseFeedrate() ? TrLang::text(246):TrLang::text(247)));//是  否
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(259)));//是否如果使用默认的进给速度。合法值：“是”,使用默认的进给速度,加工文件中指定的速度将无效；“否”，使用加工文件中指定的速度
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N12009"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(260)));//对刀接近位置
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(readIni.GetZCloseValue())));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(261)));//对刀Z方向接近位置
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N12012"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(262)));//G73退刀量
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetG73_d()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(263)));//G73高速深孔钻循环指令,退刀量。设定范围[1，20]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	QTableWidgetItem* item13 = new QTableWidgetItem(TrLang::text(15));//停止
	item13->setFont(mFont);
	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 25);
	ui.tableWidget->setItem(mRow, 0, item13);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_CaoZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N11012"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(264)));//停止时动作参数选择
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetStopZParam()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(265)));//停止时是否抬到安全高度,合法值：“0”，保持不动；“1”，抬到安全高度；“2”，抬到设置的提刀量高度
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N11014"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(266)));//停止时Z轴提刀量
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetStopZValue()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(267)));//刀具停止加工时，刀具沿Z方向向上抬刀运行的相对高度，设定范围[1，1000]mm
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N11015"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(268)));//停止或加工完成时是否关闭主轴
	QString IsCloseSpindle = readIni.GetIsCloseSpindle() ? TrLang::text(246):TrLang::text(247);//是") : ("否
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(IsCloseSpindle));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem());
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(269)));//停止加工时，是否关闭主轴；“是”关闭，“否”不关闭；
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N11016"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(270)));//断点续传是否自动打开主轴
	QString IsOpenSpindle = readIni.GetIsOpenSpindle() ? TrLang::text(246):TrLang::text(247);
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(IsOpenSpindle));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem());
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(271)));//断点续传是否自动打开主轴；“是”打开，“否”不打开；
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_CaoZ);
}
void DlgSetParameter::rowN15()
{
	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N15001"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(272)));//插补最大直线加速度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(101))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(273)));//插补最大直线加速度,初始值0.01
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N15002"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(274))); //插补直线加加速度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(102))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(275)));//插补直线加加速度，初始值0.001
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_CaoZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N15003"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(276)));//插补拐点精度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(103))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(277)));//插补拐点精度要求，其值与拐点加速度相关，初始值0.001
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_CaoZ);
}
void DlgSetParameter::rowN25() {
	//ID 21 end;


	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem * itemmcdl = new  QTableWidgetItem(TrLang::text(278));//脉冲当量
	itemmcdl->setFont(mFont);
	ui.tableWidget->setItem(mRow, 0, itemmcdl);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25001"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("X")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(110) / mcc->GetParameterValue(120))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/p "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(279)));//电机每移动1mm，产生的脉冲数
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);


	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25002"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Y")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(111) / mcc->GetParameterValue(121))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/p "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(279)));//电机每移动1mm，产生的脉冲数
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25003"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Z")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(112) / mcc->GetParameterValue(122))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/p "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(279)));//电机每移动1mm，产生的脉冲数
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);


	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25019"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("A")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(113) / mcc->GetParameterValue(123))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/p "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(280)));//电机每转动一度，产生的脉冲数
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);


	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25020"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("B")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(114) / mcc->GetParameterValue(124))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/p "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(280)));//电机每移动1mm，产生的脉冲数
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);


	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25021"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("C")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(115) / mcc->GetParameterValue(125))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/p "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(280)));//电机每移动1mm，产生的脉冲数
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem* itemMcfx = new QTableWidgetItem(TrLang::text(368));//脉冲方向
	itemMcfx->setFont(mFont);
	ui.tableWidget->setItem(mRow, 0, itemMcfx);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25034"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem("X"));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(SammonFunc::Getins()->readBit(readIni.GetPulseDirection(), 0) ? "1":"0"));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(369)));// 0 负方向  1 正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25035"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem("Y"));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(SammonFunc::Getins()->readBit(readIni.GetPulseDirection(), 1) ? "1" : "0"));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(369)));// 0 负方向  1 正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25036"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem("Z"));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(SammonFunc::Getins()->readBit(readIni.GetPulseDirection(), 2) ? "1" : "0"));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(369)));// 0 负方向  1 正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25037"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem("A"));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(SammonFunc::Getins()->readBit(readIni.GetPulseDirection(), 3) ? "1" : "0"));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(369)));// 0 负方向  1 正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25038"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem("B"));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(SammonFunc::Getins()->readBit(readIni.GetPulseDirection(), 4) ? "1" : "0"));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(369)));// 0 负方向  1 正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25039"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem("C"));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(SammonFunc::Getins()->readBit(readIni.GetPulseDirection(), 5) ? "1" : "0"));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(369)));// 0 负方向  1 正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem* itemgztfw = new QTableWidgetItem(TrLang::text(281));//工作台行程范围检测有效
	itemgztfw->setFont(mFont);
	ui.tableWidget->setItem(mRow, 0, itemgztfw);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25004"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(282)));//软限位
	bool s_sle = readIni.GetLmtEnalbe();
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(s_sle ? TrLang::text(246):TrLang::text(247)));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(283)));//工作台行程范围检测有效。“是”，有效；“否”，无效
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemgztxx = new QTableWidgetItem(TrLang::text(284));//工作台行程下限(机械坐标)
	itemgztxx->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemgztxx);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25007"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("X")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetXPosMinus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(285)));//
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25008"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Y")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetYPosMinus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(285)));//指定机械坐标在各轴方向上的下限，设定范围[-9999，工作台行程上限]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25009"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Z")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetZPosMinus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(285)));//指定机械坐标在各轴方向上的下限，设定范围[-9999，工作台行程上限
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25025"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("A")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetAPosMinus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("degrees "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(286)));//指定机械坐标在各轴方向上的下限，设定范围[-360，工作台行程上限]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25026"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("B")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetBPosMinus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("degrees "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(286)));//指定机械坐标在各轴方向上的下限，设定范围[-360，工作台行程上限]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25027"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("C")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetCPosMinus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("degrees "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(286)));//指定机械坐标在各轴方向上的下限，设定范围[-360，工作台行程上限]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem* gztsx = new QTableWidgetItem(TrLang::text(287));//工作台行程上限(机械坐标)
	gztsx->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, gztsx);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25010"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("X")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetXPosPlus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(288)));//指定机械坐标在各轴方向上的上限，设定范围[工作台行程下限，9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25011"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Y")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetYPosPlus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(288)));//指定机械坐标在各轴方向上的上限，设定范围[工作台行程下限，9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25012"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Z")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetZPosPlus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(288)));//指定机械坐标在各轴方向上的上限，设定范围[工作台行程下限，9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25028"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("A")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetAPosPlus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("degrees "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(289)));//指定机械坐标在各轴方向上的上限，设定范围[工作台行程下限，360]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25029"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("B")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetBPosPlus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("degrees "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(289)));//指定机械坐标在各轴方向上的上限，设定范围[工作台行程下限，360]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25030"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("C")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetCPosPlus()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("degrees "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(289)));//指定机械坐标在各轴方向上的上限，设定范围[工作台行程下限，360]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemydxw = new QTableWidgetItem(TrLang::text(290));//原点作为限位是否有效
	itemydxw->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemydxw);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25031"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("X"))); 
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetXOriginLmt() ? TrLang::text(246):TrLang::text(247)));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(291).arg("X")));//X轴原点作为限位是否使能，是：使能；否：无效
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25032"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Y")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetYOriginLmt() ? TrLang::text(246):TrLang::text(247)));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(291).arg("Y"))); //Y轴原点作为限位是否使能，是：使能；否：无效
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N25033"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Z")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetZOriginLmt() ? TrLang::text(246):TrLang::text(247)));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(281).arg("Z")));//Z轴原点作为限位是否使能，是：使能；否：无效
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _String);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, Manufacturer_GeiJZ);
}
void DlgSetParameter::rowN21() {

	QTableWidgetItem* item21 = new QTableWidgetItem(TrLang::text(292));//主轴参数
	item21->setFont(mFont);
	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 25);
	ui.tableWidget->setItem(mRow, 0, item21);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21001"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(293)));//主轴启动延时
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetSpindleOpen()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("ms"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(294)));//主轴接收到启动命令后的延迟时间,设定范围[10,9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21002"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(295)));//主轴停止延时
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetSpindleClose()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("ms"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(296)));//主轴接收到关闭命令后的延迟时间,设定范围[10,9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21003"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(297)));//风冷、雾冷打开延时
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetM07Time()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("ms"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(298)));//风冷、雾冷打开延时，设定范围[10,9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21004"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(299)));//冷却液、油液打开延时
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetM08Time()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("ms"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(300)));//冷却液、油冷打开延时,,设定范围[10,9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21005"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(301)));//关闭冷却、喷雾延时
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetM09Time()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("ms"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(302)));//关闭冷却、喷雾延时,设定范围[10,9999]
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *gztfw = new QTableWidgetItem(TrLang::text(303));//进给轴方向
	gztfw->setFont(mFont);
	ui.tableWidget->setItem(mRow, 0, gztfw);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_GeiJZ);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21006"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("X")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetXMotorDirLevel()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(304).arg("X")));//设置X轴方向，有效值0负方向，1正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21007"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Y")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetYMotorDirLevel()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(304).arg("Y")));//设置Y轴方向，有效值0负方向，1正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21008"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("Z")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetZMotorDirLevel()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(304).arg("Z")));//设置Z轴方向，有效值0负方向，1正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21009"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("A")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetAMotorDirLevel()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(304).arg("A")));//设置A轴方向，有效值0负方向，1正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21010"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("B")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetBMotorDirLevel()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(304).arg("B")));//设置B轴方向，有效值0负方向，1正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21011"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(("C")));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetCMotorDirLevel()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(304).arg("C")));//设置C轴方向，有效值0负方向，1正方向
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	NcPod::getIns()->Set_MotorDirLeve(0, 0, readIni.GetXMotorDirLevel().toInt());
	NcPod::getIns()->Set_MotorDirLeve(0, 1, readIni.GetYMotorDirLevel().toInt());
	NcPod::getIns()->Set_MotorDirLeve(0, 2, readIni.GetZMotorDirLevel().toInt());
	NcPod::getIns()->Set_MotorDirLeve(0, 3, readIni.GetAMotorDirLevel().toInt());
	NcPod::getIns()->Set_MotorDirLeve(0, 4, readIni.GetZMotorDirLevel().toInt());
	NcPod::getIns()->Set_MotorDirLeve(0, 5, readIni.GetAMotorDirLevel().toInt());
	{
		QTableWidgetItem* item21 = new QTableWidgetItem(TrLang::text(305));//进给轴速度
		item21->setFont(mFont);
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 25);
		ui.tableWidget->setItem(mRow, 0, item21);
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
		ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_GeiJZ);
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
		ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
		ui.tableWidget->setSpan(mRow++, 0, 1, 6);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21012"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(306).arg("X")));//X轴手动低速
		char buffN11001[20] = {};
		sprintf(buffN11001, "%.3f", mcc->GetParameterValue(320));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11001));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(307).arg("X"))); //X轴手动模式下的默认速度，设定范围[起跳速度，手动高速]mm / min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21013"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(306).arg("Y")));//Y轴手动低速
		char buffN11001[20] = {};
		sprintf(buffN11001, "%.3f", mcc->GetParameterValue(321));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11001));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(307).arg("Y")));//Y轴手动模式下的默认速度，设定范围[起跳速度，手动高速]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21014"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(306).arg("Z")));//Z轴手动低速
		char buffN11001[20] = {};
		sprintf(buffN11001, "%.3f", mcc->GetParameterValue(322));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11001));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(307).arg("Z")));//Z轴手动模式下的默认速度，设定范围[起跳速度，手动高速]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21015"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(306).arg("A")));//A轴手动低速
		char buffN11001[20] = {};
		sprintf(buffN11001, "%.3f", mcc->GetParameterValue(323));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11001));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(307).arg("A")));//A轴手动模式下的默认速度，设定范围[起跳速度，手动高速]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21016"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(306).arg("B")));//B轴手动低速
		char buffN11001[20] = {};
		sprintf(buffN11001, "%.3f", mcc->GetParameterValue(324));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11001));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(307).arg("B")));//B轴手动模式下的默认速度，设定范围[起跳速度，手动高速]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21017"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(306).arg("C")));//C轴手动低速
		char buffN11001[20] = {};
		sprintf(buffN11001, "%.3f", mcc->GetParameterValue(325));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11001));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(307).arg("C")));//C轴手动模式下的默认速度，设定范围[起跳速度，手动高速]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21018"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(308).arg("X")));//X轴手动高速
		char buffN11002[20] = {};
		sprintf(buffN11002, "%.3f", mcc->GetParameterValue(330));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11002));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(309).arg("X")));//X轴手动模式下的高速运行速度，设定范围[手动低速，30000]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21019"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(308).arg("Y")));//Y轴手动高速
		char buffN11002[20] = {};
		sprintf(buffN11002, "%.3f", mcc->GetParameterValue(331));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11002));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(309).arg("Y")));//Y轴手动模式下的高速运行速度，设定范围[手动低速，30000]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21020"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(308).arg("Z")));//Z轴手动高速
		char buffN11002[20] = {};
		sprintf(buffN11002, "%.3f", mcc->GetParameterValue(332));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11002));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(309).arg("Z")));//Z轴手动模式下的高速运行速度，设定范围[手动低速，30000]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21021"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(308).arg("A")));//A轴手动高速
		char buffN11002[20] = {};
		sprintf(buffN11002, "%.3f", mcc->GetParameterValue(333));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11002));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(309).arg("A")));//A轴手动模式下的高速运行速度，设定范围[手动低速，30000]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21022"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(308).arg("B")));//B轴手动高速
		char buffN11002[20] = {};
		sprintf(buffN11002, "%.3f", mcc->GetParameterValue(334));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11002));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(309).arg("B")));//B轴手动模式下的高速运行速度，设定范围[手动低速，30000]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21023"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(308).arg("C")));//C轴手动高速
		char buffN11002[20] = {};
		sprintf(buffN11002, "%.3f", mcc->GetParameterValue(335));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN11002));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/min"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(309).arg("C")));//C轴手动模式下的高速运行速度，设定范围[手动低速，30000]mm/min
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
	{
		QTableWidgetItem* item21 = new QTableWidgetItem(TrLang::text(310));//进给轴加速度
		item21->setFont(mFont);
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 25);
		ui.tableWidget->setItem(mRow, 0, item21);
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
		ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_GeiJZ);
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
		ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
		ui.tableWidget->setSpan(mRow++, 0, 1, 6);
	}
	{
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21024"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(311).arg("X")));//X轴手动加速度
		char buffN12010[20] = {};
		sprintf(buffN12010, "%.3f", mcc->GetParameterValue(380) / (mcc->GetParameterValue(110) / mcc->GetParameterValue(120)));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN12010));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/s^2"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(312).arg("X")));//X轴手动加速度，设定范围[1，3000]mm/s^2
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	} {
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21025"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(311).arg("Y")));//Y轴手动加速度
		char buffN12010[20] = {};
		sprintf(buffN12010, "%.3f", mcc->GetParameterValue(381) / (mcc->GetParameterValue(111) / mcc->GetParameterValue(121)));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN12010));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/s^2"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(312).arg("Y")));//X轴手动加速度，设定范围[1，3000]mm/s^2
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	} {
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21026"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(311).arg("Z")));//Z轴手动加速度
		char buffN12010[20] = {};
		sprintf(buffN12010, "%.3f", mcc->GetParameterValue(382) / (mcc->GetParameterValue(112) / mcc->GetParameterValue(122)));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN12010));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/s^2"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(312).arg("Z")));//Z轴手动加速度，设定范围[1，3000]mm/s^2
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	} {
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21027"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(311).arg("A")));//A轴手动加速度
		char buffN12010[20] = {};
		sprintf(buffN12010, "%.3f", mcc->GetParameterValue(383) / (mcc->GetParameterValue(113) / mcc->GetParameterValue(123)));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN12010));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/s^2"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(312).arg("A")));//A轴手动加速度，设定范围[1，3000]mm/s^2
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	} {
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21028"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(311).arg("B")));//B轴手动加速度
		char buffN12010[20] = {};
		sprintf(buffN12010, "%.3f", mcc->GetParameterValue(384) / (mcc->GetParameterValue(114) / mcc->GetParameterValue(124)));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN12010));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/s^2"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(312).arg("B")));//B轴手动加速度，设定范围[1，3000]mm/s^2
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	} {
		ui.tableWidget->insertRow(mRow);
		ui.tableWidget->setRowHeight(mRow, 20);
		ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N21029"));
		ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(311).arg("C")));//C轴手动加速度
		char buffN12010[20] = {};
		sprintf(buffN12010, "%.3f", mcc->GetParameterValue(385) / (mcc->GetParameterValue(115) / mcc->GetParameterValue(125)));
		ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(buffN12010));
		ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm/s^2"));
		ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(312).arg("C")));//C轴手动加速度，设定范围[1，3000]mm/s^2
		ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
		ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_GeiJZ);
	}
}
void DlgSetParameter::rowN31() {
	QTableWidgetItem* item31 = new QTableWidgetItem(TrLang::text(186));//刀具参数
	item31->setFont(mFont);
	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 25);
	ui.tableWidget->setItem(mRow, 0, item31);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31049"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(318)));//换刀选项
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(readIni.GetToolChangeOpt()));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(""));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));

	if(VersionType==1)
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(319)));//设置范围：0、1;  0:忽略换刀指令;  1:手动换刀
	else
		ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(320)));//设置范围：0、1、2;  0:忽略换刀指令;  1:手动换刀; 2:自动换刀
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20); 
	QTableWidgetItem *itemdj1 = new QTableWidgetItem(TrLang::text(315).arg(1));//刀具1
	itemdj1->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj1);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31002"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));//长度
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(250))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245))); 
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(1)));//01 号刀具“长度”补偿值，单位mm
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj2 = new QTableWidgetItem(TrLang::text(315).arg(2));//刀具2
	itemdj2->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj2);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31008"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(252))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(2)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj3 = new QTableWidgetItem(TrLang::text(315).arg(3)); 
	itemdj3->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj3);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31014"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(254))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(3)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj4 = new QTableWidgetItem(TrLang::text(315).arg(4));
	itemdj4->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj4);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31020"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(256))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(4)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj5 = new QTableWidgetItem(TrLang::text(315).arg(5));
	itemdj5->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj5);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31026"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(258))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(5)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj6 = new QTableWidgetItem(TrLang::text(315).arg(6));
	itemdj6->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj6);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31032"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(260))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(6)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);
	
	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj7 = new QTableWidgetItem(TrLang::text(315).arg(7));
	itemdj7->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj7);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31038"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(262))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(7)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj8 = new QTableWidgetItem(TrLang::text(315).arg(8));
	itemdj8->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj8);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31044"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(264))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(8)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj9 = new QTableWidgetItem(TrLang::text(315).arg(9));
	itemdj9->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj9);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31050"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(266))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(9)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj10 = new QTableWidgetItem(TrLang::text(315).arg(10));
	itemdj10->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj10);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31051"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(268))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(10)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj11 = new QTableWidgetItem(TrLang::text(315).arg(11));
	itemdj11->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj11);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31052"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(270))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(11)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj12 = new QTableWidgetItem(TrLang::text(315).arg(12));
	itemdj12->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj12);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31053"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(272))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(12)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj13= new QTableWidgetItem(TrLang::text(315).arg(13));
	itemdj13->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj13);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31054"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(274))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(13)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj14 = new QTableWidgetItem(TrLang::text(315).arg(14));
	itemdj14->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj14);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31055"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(276))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(14)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj15 = new QTableWidgetItem(TrLang::text(315).arg(15));
	itemdj15->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj15);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31056"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(278))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(15)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	QTableWidgetItem *itemdj16 = new QTableWidgetItem(TrLang::text(315).arg(16));
	itemdj16->setFont(mFont2);
	ui.tableWidget->setItem(mRow, 0, itemdj16);
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(" "));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(" "));
	ui.tableWidget->item(mRow, 0)->setData(PARAMROLE, User_Tool);
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NOV);
	ui.tableWidget->item(mRow, 0)->setFlags(ui.tableWidget->item(mRow, 0)->flags()&~Qt::ItemIsSelectable);
	ui.tableWidget->setSpan(mRow++, 0, 1, 6);

	ui.tableWidget->insertRow(mRow);
	ui.tableWidget->setRowHeight(mRow, 20);
	ui.tableWidget->setItem(mRow, 0, new QTableWidgetItem("N31057"));
	ui.tableWidget->setItem(mRow, 1, new QTableWidgetItem(TrLang::text(316)));
	ui.tableWidget->setItem(mRow, 2, new QTableWidgetItem(QString::number(mcc->GetParameterValue(280))));
	ui.tableWidget->setItem(mRow, 3, new QTableWidgetItem("mm"));
	ui.tableWidget->setItem(mRow, 4, new QTableWidgetItem(TrLang::text(245)));
	ui.tableWidget->setItem(mRow, 5, new QTableWidgetItem(TrLang::text(317).arg(16)));
	ui.tableWidget->item(mRow, 2)->setData(PARAMROLE, _NUM);
	ui.tableWidget->item(mRow++, 0)->setData(PARAMROLE, User_Tool);
}
void DlgSetParameter::InitTable()
{
	rowN11();
	rowN15();
	rowN21();
	rowN25();
	rowN31();
}

void DlgSetParameter::InitParam()
{

	int temp = readIni.GetPulseDirection();
	int num = SammonFunc::Getins()->readBit(temp, 0);
	NcPod::getIns()->Set_MotorPulsLeve(0, 0, num);
	num = SammonFunc::Getins()->readBit(temp, 1);
	NcPod::getIns()->Set_MotorPulsLeve(0, 1, num);
	num = SammonFunc::Getins()->readBit(temp, 2);
	NcPod::getIns()->Set_MotorPulsLeve(0, 2, num);
	num = SammonFunc::Getins()->readBit(temp,3);
	NcPod::getIns()->Set_MotorPulsLeve(0, 3, num);
	num = SammonFunc::Getins()->readBit(temp, 4);
	NcPod::getIns()->Set_MotorPulsLeve(0, 4, num);
	num = SammonFunc::Getins()->readBit(temp, 5);
	NcPod::getIns()->Set_MotorPulsLeve(0, 5, num);


	NcPod::getIns()->Set_Steppe(0, 5, mcc->GetParameterValue(115) / mcc->GetParameterValue(125));
	NcPod::getIns()->Set_Steppe(0, 4, mcc->GetParameterValue(114) / mcc->GetParameterValue(124));
	NcPod::getIns()->Set_Steppe(0, 3, mcc->GetParameterValue(113) / mcc->GetParameterValue(123));
	NcPod::getIns()->Set_Steppe(0, 2, mcc->GetParameterValue(112) / mcc->GetParameterValue(122));
	NcPod::getIns()->Set_Steppe(0, 1, mcc->GetParameterValue(111) / mcc->GetParameterValue(121));
	NcPod::getIns()->Set_Steppe(0, 0, mcc->GetParameterValue(110) / mcc->GetParameterValue(120));
	setSoftLm();

	int PulseDirection = readIni.GetPulseDirection();
	for (int i = 0; i <= 5; i++) {	
		int num = SammonFunc::Getins()->readBit(PulseDirection, i);
		NcPod::getIns()->Set_MotorPulsLeve(0, i, num);
	}
}
