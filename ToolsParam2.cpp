#include "ToolsParam2.h"
#include "qlineedit.h"
#include "ReadIni.h"
#include "ncpod.h"
#include "ToolsChoice.h"
#include "CommonTools.h"
#include "TrLang.h"
extern ReadIni readIni;
extern int VersionType ;
ToolsParam2::ToolsParam2(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();

	Init();
	NcPod::getIns()->SpindleAlarmV2(ui.RbQIGang->isChecked(),!ui.In7enabled->isChecked());
}

ToolsParam2::~ToolsParam2()
{
}

void ToolsParam2::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(209));//
	ui.In13enabled->setText(TrLang::Ins()->GetText(197));
	ui.In14enabled->setText(TrLang::Ins()->GetText(198));
	ui.RbQIGang->setText(TrLang::Ins()->GetText(199));
	ui.RbPaiDao->setText(TrLang::Ins()->GetText(200));
	ui.In15enabled->setText(TrLang::Ins()->GetText(201));
	ui.In6enabled->setText(TrLang::Ins()->GetText(202));
	ui.In7enabled->setText(TrLang::Ins()->GetText(207));
	ui.label_5->setText(TrLang::Ins()->GetText(187));
	ui.label_4->setText(TrLang::Ins()->GetText(188));
	ui.label->setText(TrLang::Ins()->GetText(205));
	ui.label_3->setText(TrLang::Ins()->GetText(207));
	ui.label_2->setText(TrLang::Ins()->GetText(206));
	ui.RbToolX->setText(TrLang::Ins()->GetText(204).arg("X"));
	ui.RbToolY->setText(TrLang::Ins()->GetText(204).arg("Y"));
	ui.btsave->setText(TrLang::Ins()->GetText(109));
}

void ToolsParam2::hideEvent(QHideEvent * event)
{
	SaveParam();
}

void ToolsParam2::showEvent(QShowEvent * event)
{
	ShowParam();
}

void ToolsParam2::Init()
{
	//ui.tableWidget->setObjectName("IOTableWidget");
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setShowGrid(1);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	QLineEdit *celledit;
	for (int i = 0; i <= 15; i++) {
		ui.tableWidget->setRowHeight(i, 20);
		celledit = new QLineEdit;
		celledit->setAlignment(Qt::AlignCenter);
		celledit->setValidator(new QDoubleValidator());
		celledit->setObjectName("NoLineEditStayle");
		ui.tableWidget->setCellWidget(i, 0, celledit);
		celledit = new QLineEdit;
		celledit->setAlignment(Qt::AlignCenter);
		celledit->setValidator(new QDoubleValidator());
		celledit->setObjectName("NoLineEditStayle");
		ui.tableWidget->setCellWidget(i, 1, celledit);
		celledit = new QLineEdit;
		celledit->setAlignment(Qt::AlignCenter);
		celledit->setObjectName("NoLineEditStayle");
		celledit->setValidator(new QDoubleValidator());
		ui.tableWidget->setCellWidget(i, 2, celledit);
	}
	
	ui.ToolsCount->setValidator(new QIntValidator(1, 16));

	connect(ui.ToolsCount, &QLineEdit::textChanged, [this]() {
		if (ui.ToolsCount->text().toInt() == 0)return;
		for (int i=0; i <= 15; i++) {
			bool needHiden = i >= ui.ToolsCount->text().toInt();
			ui.tableWidget->setRowHidden(i, needHiden);
			dynamic_cast<ToolsChoice*>(parent())->setToolEnabled(i+1, !needHiden);
		}
	});
	connect(ui.RbQIGang, &QRadioButton::toggled,[this](bool b) {	
		ui.In6enabled->setVisible(b);
		ui.In7enabled->setVisible(b);

		//ui.label->setVisible(!b);
		ui.label_2->setVisible(!b);
		ui.label_3->setVisible(!b);

		ui.ToolReady->setVisible(!b);
		//ui.ToolInFeed->setVisible(!b);
		ui.ToolChangeUpZ->setVisible(!b);
		readIni.SetToolIsQiGang(b);
		emit SammonFunc::Getins()->ResetIOText();
	});

	connect(ui.In7enabled, &QRadioButton::toggled, [this](bool b) {

		readIni.SetTool_In_Enabled_2(7, ui.In7enabled->isChecked());
		emit SammonFunc::Getins()->ResetIOText();
	});

	connect(ui.btsave, &QPushButton::clicked, this,&ToolsParam2::SaveParam);
}

void ToolsParam2::SaveParam()
{

	int i = 0;

	readIni.SetT1X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT1Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT1Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT2X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT2Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT2Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT3X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT3Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT3Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT4X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT4Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT4Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT5X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT5Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT5Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT6X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT6Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT6Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT7X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT7Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT7Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT8X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT8Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT8Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT9X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT9Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT9Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT10X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT10Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT10Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT11X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT11Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT11Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT12X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT12Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT12Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT13X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT13Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT13Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT14X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT14Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT14Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT15X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT15Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT15Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetT16X(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->text());
	readIni.SetT16Y(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->text());
	readIni.SetT16Z(dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->text());

	readIni.SetToolCount(ui.ToolsCount->text());
	readIni.SetToolInFeed(ui.ToolInFeed->text());
	readIni.SetToolChangeUpZ(ui.ToolChangeUpZ->text());
	readIni.SetToolReady(ui.ToolReady->text());
	readIni.SetToolSafeZ(ui.ToolSafeZ->text());
	readIni.SetToolIsOnY(ui.RbToolY->isChecked());

	readIni.SetTool_In_Enabled_2(6, ui.In6enabled->isChecked());
	readIni.SetTool_In_Enabled_2(7, ui.In7enabled->isChecked());
	readIni.SetTool_In_Enabled_2(13, ui.In13enabled->isChecked());
	readIni.SetTool_In_Enabled_2(14, ui.In14enabled->isChecked());
	readIni.SetTool_In_Enabled_2(15, ui.In15enabled->isChecked());
	//readIni.SetToolIsQiGang(ui.RbQIGang->isChecked());

	NcPod::getIns()->SpindleAlarmV2(ui.RbQIGang->isChecked(), !ui.In7enabled->isChecked());

}

void ToolsParam2::ShowParam()
{
	int i = 0;
	
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT1X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT1Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT1Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT2X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT2Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT2Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT3X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT3Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT3Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT4X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT4Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT4Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT5X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT5Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT5Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT6X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT6Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT6Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT7X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT7Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT7Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT8X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT8Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT8Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT9X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT9Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT9Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT10X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT10Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT10Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT11X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT11Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT11Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT12X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT12Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT12Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT13X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT13Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT13Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT14X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT14Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT14Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT15X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT15Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT15Z());

	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 0))->setText(readIni.GetT16X());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i, 1))->setText(readIni.GetT16Y());
	dynamic_cast<QLineEdit*>(ui.tableWidget->cellWidget(i++, 2))->setText(readIni.GetT16Z());

	ui.ToolsCount->setText(readIni.GetToolCount());
	ui.ToolInFeed->setText(readIni.GetToolInFeed());
	ui.ToolChangeUpZ->setText(readIni.GetToolChangeUpZ());
	ui.ToolReady->setText(readIni.GetToolReady());
	ui.ToolSafeZ->setText(readIni.GetToolSafeZ());

	if (readIni.GetToolIsOnY()) {
		ui.RbToolY->setChecked(1);
	}
	else {
		ui.RbToolX->setChecked(1);
	}

	if (readIni.GetToolIsQiGang()) {
		ui.RbQIGang->setChecked(1);
	}
	else {
		ui.RbQIGang->toggle();
		ui.RbPaiDao->setChecked(1);
	}


	ui.In6enabled->setChecked(readIni.GetTool_In_Enabled_2(6));
	ui.In7enabled->setChecked(readIni.GetTool_In_Enabled_2(7));
	ui.In13enabled->setChecked(readIni.GetTool_In_Enabled_2(13));
	ui.In14enabled->setChecked(readIni.GetTool_In_Enabled_2(14));
	ui.In15enabled->setChecked(readIni.GetTool_In_Enabled_2(15));

}
