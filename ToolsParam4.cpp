#include "ToolsParam4.h"
#include "qlineedit.h"
#include "ReadIni.h"
#include "ToolsChoice.h"
#include "Samcon.h"
#include "ExternalText.h"
#include "CommonTools.h"
#include "TrLang.h"
extern ReadIni readIni;
extern int VersionType ;
extern int VType4;
extern Samcon *w;
ToolsParam4::ToolsParam4(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	Init();
	setVType4Text();
}

ToolsParam4::~ToolsParam4()
{
}

void ToolsParam4::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(208));//µ¶¿âÆ«ÒÆÁ¿ÉèÖÃ
	ui.label_5->setText(TrLang::Ins()->GetText(187));
	ui.label_4->setText(TrLang::Ins()->GetText(188));
	ui.label_7->setText(TrLang::Ins()->GetText(189).arg("X"));
	ui.label_9->setText(TrLang::Ins()->GetText(189).arg("Y"));
	ui.label_6->setText(TrLang::Ins()->GetText(190).arg("X"));
	ui.label_8->setText(TrLang::Ins()->GetText(190).arg("Y"));
	ui.zhenkongbeng1->setText(TrLang::Ins()->GetText(191));
	ui.zhenkongbeng2->setText(TrLang::Ins()->GetText(192));
	ui.dingweiqigang1->setText(TrLang::Ins()->GetText(193));
	ui.dingweiqigang2->setText(TrLang::Ins()->GetText(194));
	ui.tuiliaoqigang1->setText(TrLang::Ins()->GetText(195));
	ui.tuiliaoqigang2->setText(TrLang::Ins()->GetText(196));
	ui.btsave->setText(TrLang::Ins()->GetText(109));
}

void ToolsParam4::setVType4Text()
{
	if (VType4 == 0) {
		ui.In6enabled->setText(ExternalText::In6Test0);
		ui.In13enabled->setText(ExternalText::In13Test0);
		ui.In14enabled->setText(ExternalText::In14Test0);
		ui.In15enabled->setText(ExternalText::In15Test0);

		ui.zhenkongbeng1->hide();
		ui.zhenkongbeng2->hide();
		ui.dingweiqigang1->hide();
		ui.dingweiqigang2->hide();
		ui.tuiliaoqigang1->hide();
		ui.tuiliaoqigang2->hide();
	
		ui.TuiLiaoStartX->hide();
		ui.TuiLiaoStartY->hide();
		ui.TuiLiaoEndX->hide();
		ui.TuiLiaoEndY->hide();

		ui.label_6->hide();
		ui.label_7->hide();
		ui.label_8->hide();
		ui.label_9->hide();
	}
	else if (VType4 == 1) {
		ui.In6enabled->setText(ExternalText::In6Test1);
		ui.In13enabled->setText(ExternalText::In13Test1);
		ui.In14enabled->setText(ExternalText::In14Test1);
		ui.In15enabled->setText(ExternalText::In15Test1);
		ui.TuiLiaoStartX->setValidator(new QDoubleValidator());
		ui.TuiLiaoStartY->setValidator(new QDoubleValidator());
		ui.TuiLiaoEndX->setValidator(new QDoubleValidator());
		ui.TuiLiaoEndY->setValidator(new QDoubleValidator());

		connect(ui.zhenkongbeng1, &QPushButton::clicked, [this]() {
			SammonFunc::Getins()->RunMCode(true, "400");
		});
		connect(ui.zhenkongbeng2, &QPushButton::clicked, [this]() {
			SammonFunc::Getins()->RunMCode(true, "401");
		});
		connect(ui.dingweiqigang1, &QPushButton::clicked, [this]() {
			SammonFunc::Getins()->RunMCode(true, "500");
		});
		connect(ui.dingweiqigang2, &QPushButton::clicked, [this]() {
			SammonFunc::Getins()->RunMCode(true, "501");
		});
		connect(ui.tuiliaoqigang1, &QPushButton::clicked, [this]() {
			SammonFunc::Getins()->RunMCode(true, "300");
		});
		connect(ui.tuiliaoqigang2, &QPushButton::clicked, [this]() {
			SammonFunc::Getins()->RunMCode(true, "301");
		});
	}
}

void ToolsParam4::hideEvent(QHideEvent * event)
{
	SaveParam();
}

void ToolsParam4::showEvent(QShowEvent * event)
{
	ShowParam();
}

void ToolsParam4::Init()
{
	//ui.tableWidget->setObjectName("IOTableWidget");
	//ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setShowGrid(1);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	QLineEdit *celledit;
	for (int i = 0; i <= 3; i++) {
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


	ui.ToolsCount->setValidator(new QIntValidator(1, 4));

	connect(ui.ToolsCount, &QLineEdit::textChanged, [this]() {
		if (ui.ToolsCount->text().toInt() == 0)return;
		for (int i=0; i <= 3; i++) {
			bool needHiden = i >= ui.ToolsCount->text().toInt();
			ui.tableWidget->setRowHidden(i, needHiden);
			dynamic_cast<ToolsChoice*>(parent())->setToolEnabled(i+1, !needHiden);
		}
	});
	connect(ui.btsave, &QPushButton::clicked, this,&ToolsParam4::SaveParam);
}

void ToolsParam4::SaveParam()
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

	readIni.SetToolCount(ui.ToolsCount->text());
	readIni.SetToolSafeZ(ui.ToolSafeZ->text());
	
	readIni.SetTool_In_Enabled_4(6, ui.In6enabled->isChecked());
	readIni.SetTool_In_Enabled_4(13, ui.In13enabled->isChecked());
	readIni.SetTool_In_Enabled_4(14, ui.In14enabled->isChecked());
	readIni.SetTool_In_Enabled_4(15, ui.In15enabled->isChecked());

	readIni.SetTuiLiaoStarX(ui.TuiLiaoStartX->text().toDouble());
	readIni.SetTuiLiaoStarY(ui.TuiLiaoStartY->text().toDouble());
	readIni.SetTuiLiaoEndX(ui.TuiLiaoEndX->text().toDouble());
	readIni.SetTuiLiaoEndY(ui.TuiLiaoEndY->text().toDouble());
}

void ToolsParam4::ShowParam()
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



	ui.ToolsCount->setText(readIni.GetToolCount());
	ui.ToolSafeZ->setText(readIni.GetToolSafeZ());

	ui.In6enabled->setChecked(readIni.GetTool_In_Enabled_4(6));
	ui.In13enabled->setChecked(readIni.GetTool_In_Enabled_4(13));
	ui.In14enabled->setChecked(readIni.GetTool_In_Enabled_4(14));
	ui.In15enabled->setChecked(readIni.GetTool_In_Enabled_4(15));
	
	ui.TuiLiaoStartX->setText(QString::number(readIni.GetTuiLiaoStarX()));
	ui.TuiLiaoStartY->setText(QString::number(readIni.GetTuiLiaoStarY()));
	ui.TuiLiaoEndX->setText(QString::number(readIni.GetTuiLiaoEndX()));
	ui.TuiLiaoEndY->setText(QString::number(readIni.GetTuiLiaoEndY()));
	
	
	
	
}


