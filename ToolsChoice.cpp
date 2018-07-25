#include "ToolsChoice.h"
#include"mccdll.h"
#include "ReadIni.h"
#include "DlgWarnMess.h"
#include "Samcon.h"
#include"ncpod.h"
#include "ToolsParam2.h"
#include "trgcode.h"
#include "ToolsParam4.h"
#include"LogManager.h"
#include "commontools.h"
#include "TrLang.h"
#include "MccTools.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern Samcon *w;
extern int VersionType;
extern int VType4;
ToolsChoice::ToolsChoice(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	if (VersionType == 2) {
		pToolsParam2 = new ToolsParam2(this);
		connect(ui.btToolsParam, &QPushButton::clicked, [this]() {
			pToolsParam2->show();
		});
	}
	else  if(VersionType == 4){
		pToolsParam4 = new ToolsParam4(this);
		connect(ui.btToolsParam, &QPushButton::clicked, [this]() {
			pToolsParam4->show();
		});
	}
	if(VType4 != 1|| VersionType!=4)
		ui.ZiDongTuiLiao->hide();

	Init();
	InitKeyboardCtrl();
	if (VersionType == 1|| VersionType == 6) {
		ui.btToolsParam->setVisible(0);
		ui.autoTool->setVisible(0);
		ui.groupBox_2->setVisible(0);
	
	}
	else if (VersionType == 4) {
		ui.TOOL5->hide();
		ui.TOOL6->hide();
		ui.TOOL7->hide();
		ui.TOOL8->hide();
		ui.TOOL9->hide();
		ui.TOOL10->hide();
		ui.TOOL11->hide();
		ui.TOOL12->hide();
		ui.TOOL13->hide();
		ui.TOOL14->hide();
		ui.TOOL15->hide();
		ui.TOOL16->hide();
	}
	int tc = readIni.GetToolCount().toInt();
	for (int i = 1; i <= 16; i++) {
		bool b = i <= tc;
		setToolEnabled(i, b);
	}
	connect(ui.autoTool, &QPushButton::clicked, [this]() {
		w->MCodeFromMDI = true;
		SammonFunc::Getins()->autoToolSetting = true;
	});
	connect(ui.ZiDongTuiLiao, &QPushButton::clicked, [this]() {
		SammonFunc::Getins()->RunMCode(true, "302");	
	});
}

ToolsChoice::~ToolsChoice()
{
}

void ToolsChoice::ResetLanguage()
{
	ui.groupBox_2->setTitle(TrLang::Ins()->GetText(62));
	ui.ZiDongTuiLiao->setText(TrLang::Ins()->GetText(184));
	ui.autoTool->setText(TrLang::Ins()->GetText(185));
	ui.btToolsParam->setText(TrLang::Ins()->GetText(186));
	ui.CMDOK->setText(TrLang::Ins()->GetText(160));
	if (pToolsParam2) 	pToolsParam2->ResetLanguage();
	if (pToolsParam4)pToolsParam4->ResetLanguage();
}

void ToolsChoice::MySetFocus()
{
	ui.TOOL1->setFocus();
}

bool ToolsChoice::MyGetFocus()
{
	bool b1 = ui.TOOL1->hasFocus() || ui.TOOL2->hasFocus() || ui.TOOL3->hasFocus() || ui.TOOL4->hasFocus() || ui.TOOL5->hasFocus() || ui.TOOL6->hasFocus() || ui.TOOL7->hasFocus() || ui.TOOL8->hasFocus();
	bool b2 = ui.lineEditCMD->hasFocus();
	bool b3 = ui.CMDOK->hasFocus();
	return b1||b2||b3||hasFocus();
}

void ToolsChoice::Init()
{
	connect(ui.TOOL1, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T1";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL2, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T2";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL3, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T3";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL4, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T4";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL5, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T5";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL6, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T6";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL7, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T7";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL8, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T8";
			DoMCode(MDI);
		}
	});

	connect(ui.TOOL9, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T9";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL10, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T10";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL11, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T11";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL12, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T12";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL13, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T13";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL14, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T14";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL15, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T15";
			DoMCode(MDI);
		}
	});
	connect(ui.TOOL16, &QRadioButton::toggled, [this](bool istoggled) {
		if (istoggled) {
			QString MDI = "T16";
			DoMCode(MDI);
		}
	});
	connect(ui.CMDOK, &QPushButton::clicked, [this](bool b) {	
		if (!SammonFunc::CanDoit())return;
		QString curline = ui.lineEditCMD->text();
		if (curline.isEmpty())return;
		if (curline.contains("G31") || curline.contains("g31")) {
			QString Code = SammonFunc::GetNumber(curline, 'X', 'x');
			if (!Code.isEmpty()) {
				w->pTrGCode->isG31 = 0;
				w->pTrGCode->G31Coord = Code;
			}
			Code = SammonFunc::GetNumber(curline, 'Y', 'y');
			if (!Code.isEmpty()) {
				w->pTrGCode->isG31 = 1;
				w->pTrGCode->G31Coord = Code;
			}
			Code = SammonFunc::GetNumber(curline, 'Z', 'z');
			if (!Code.isEmpty()) {
				w->pTrGCode->isG31 = 2;
				w->pTrGCode->G31Coord = Code;
			}
			Code = SammonFunc::GetNumber(curline, 'F', 'f');
			if (!Code.isEmpty()) {
				w->pTrGCode->G31FSpeed = Code;
			}
			if (w->pTrGCode->isG31 != -1) {
				SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 0, 0);
				LogManager::getIns()->appendLog(ui.lineEditCMD->text());
			}
			else {
				
			}
			return;
		}
		if (DoMCode(curline)) return;
		if ((curline.contains("G43") || curline.contains("g43")) && !(curline.contains("h") || curline.contains("H"))) {
			DlgWarnMess* dlg = new DlgWarnMess(TrLang::Ins()->GetText(183)+"G43");//G43 指令有误
			return;
		}
		MccTools::SendMDI(ui.lineEditCMD->text());
		LogManager::getIns()->appendLog("MDI:"+ ui.lineEditCMD->text());
	});
	ui.lineEditCMD->setPlaceholderText(TrLang::Ins()->GetText(182));//执行G代码指令
	setToolChecked(readIni.GetTool());
	ignoreToolChange(readIni.GetTool());
}

void ToolsChoice::setToolEnabled(int no, bool en)
{
	switch (no)
	{
	case 1:
		ui.TOOL1->setVisible(en);
		break;
	case 2:
		ui.TOOL2->setVisible(en);
		break;
	case 3:
		ui.TOOL3->setVisible(en);
		break;
	case 4:
		ui.TOOL4->setVisible(en);
		break;
	case 5:
		ui.TOOL5->setVisible(en);
		break;
	case 6:
		ui.TOOL6->setVisible(en);
		break;
	case 7:
		ui.TOOL7->setVisible(en);
		break;
	case 8:
		ui.TOOL8->setVisible(en);
		break;
	case 9:
		ui.TOOL9->setVisible(en);
		break;
	case 10:
		ui.TOOL10->setVisible(en);
		break;
	case 11:
		ui.TOOL11->setVisible(en);
		break;
	case 12:
		ui.TOOL12->setVisible(en);
		break;
	case 13:
		ui.TOOL13->setVisible(en);
		break;
	case 14:
		ui.TOOL14->setVisible(en);
		break;
	case 15:
		ui.TOOL15->setVisible(en);
		break;
	case 16:
		ui.TOOL16->setVisible(en);
		break;
	}
}

void ToolsChoice::setToolChecked(int no)
{
	switch (no)
	{
	case 1:
		ui.TOOL1->setChecked(1);
		break;
	case 2:
		ui.TOOL2->setChecked(1);
		break;
	case 3:
		ui.TOOL3->setChecked(1);
		break;
	case 4:
		ui.TOOL4->setChecked(1);
		break;
	case 5:
		ui.TOOL5->setChecked(1);
		break;
	case 6:
		ui.TOOL6->setChecked(1);
		break;
	case 7:
		ui.TOOL7->setChecked(1);
		break;
	case 8:
		ui.TOOL8->setChecked(1);
		break;
	case 9:
		ui.TOOL9->setChecked(1);
		break;
	case 10:
		ui.TOOL10->setChecked(1);
		break;
	case 11:
		ui.TOOL11->setChecked(1);
		break;
	case 12:
		ui.TOOL12->setChecked(1);
		break;
	case 13:
		ui.TOOL13->setChecked(1);
		break;
	case 14:
		ui.TOOL14->setChecked(1);
		break;
	case 15:
		ui.TOOL15->setChecked(1);
		break;
	case 16:
		ui.TOOL16->setChecked(1);
		break;
	}
	

}

bool ToolsChoice::DoMCode(QString curline)
{
	if (!SammonFunc::CanDoit())return 1;
	if (w->isMCode)return true;
	w->MCodeFromMDI = true;//宏代码是从TextEdit 发送的
	if (curline.contains("M") || curline.contains("m")) {
		QString MCode = SammonFunc::GetNumber(curline, 'M', 'm');
		if (MCode.toInt() >= 100) {
			w->isMCode = true;
			w->MCodeName = MCode;
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
			return true;
		}
	}
	 if (curline.contains("T") || curline.contains("t")) {
		int newT = SammonFunc::GetNumber(curline, 'T', 't').toInt();

		if (readIni.GetToolChangeOpt().toInt() == 0) {
			ignoreToolChange(newT);
			return true;
		}
		if (VersionType == 1) {
			ignoreToolChange(newT);
			return true;
		}
		else if (VersionType == 2) {
			if (newT == readIni.GetTool() || newT < 1 || newT>readIni.GetToolCount().toInt()) {
				return true;
			}
			w->isMCode = true;
			if (readIni.GetToolIsQiGang()) {
				w->MCodeName = "6q";
			}
			else {
				w->MCodeName = "6p";
			}
			NcPod::getIns()->newT = newT;
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
			return true;
		}
		else if (VersionType == 4) {
			if (newT == 5 || newT == 6) {

			}
			else if (newT == readIni.GetTool() || newT < 1 || newT>readIni.GetToolCount().toInt()) {
				return true;
			}
			w->isMCode = true;
			w->MCodeName = "6";
			NcPod::getIns()->newT = newT;
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
			return true;
		}
		

	}
	return false;
}

void ToolsChoice::keyReleaseEvent(QKeyEvent * event)
{
	QObject* w = focusWidget();
	QRadioButton* rb = dynamic_cast<QRadioButton*>(w);
	QLineEdit* le = dynamic_cast<QLineEdit*>(w);
	QPushButton *pb = dynamic_cast<QPushButton*>(w);
	if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
		if (rb) {
			rb->setChecked(true);
		}
		else if (le || pb) {
			ui.CMDOK->clicked();

		}
	}
	if (le)return; //防止写mdi 触发   按键盘 点动
	QWidget::keyReleaseEvent(event);
}

bool ToolsChoice::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == this ||
		obj == ui.TOOL1 ||
		obj == ui.TOOL2 ||
		obj == ui.TOOL3 ||
		obj == ui.TOOL4 || obj == ui.TOOL5 ||
		obj == ui.TOOL6 ||
		obj == ui.TOOL7 ||
		obj == ui.TOOL8 ||
		obj == ui.lineEditCMD ||
		obj == ui.CMDOK) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.TOOL1->hasFocus() || ui.TOOL2->hasFocus() || ui.TOOL3->hasFocus() || ui.TOOL4->hasFocus() || ui.TOOL5->hasFocus() || ui.TOOL6->hasFocus() || ui.TOOL7->hasFocus() || ui.TOOL8->hasFocus();
				bool b2 = ui.lineEditCMD->hasFocus();
				bool b3 = ui.CMDOK->hasFocus();
				if (b1) {
					focusNextChild();
					ui.lineEditCMD->setFocus();
				}
				else if (b2) {
					focusNextChild();
					ui.CMDOK->setFocus();
				}
				else if (b3) {
					focusNextChild();
					ui.TOOL1->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					ui.TOOL1->setFocus();
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

void ToolsChoice::InitKeyboardCtrl()
{
	installEventFilter(this);
	ui.TOOL1->installEventFilter(this);
	ui.TOOL2->installEventFilter(this);
	ui.TOOL3->installEventFilter(this);
	ui.TOOL4->installEventFilter(this);
	ui.TOOL5->installEventFilter(this);
	ui.TOOL6->installEventFilter(this);
	ui.TOOL7->installEventFilter(this);
	ui.TOOL8->installEventFilter(this);
	ui.lineEditCMD->installEventFilter(this);
	ui.CMDOK->installEventFilter(this);
}

void ToolsChoice::ignoreToolChange(int tt)
{
	readIni.SetTool(tt);
	SammonFunc::sToolName = QString("T%1").arg(tt);
}
