#include "QStartFromIndex.h"
#include"ReadIni.h"
#include "Ncpod.h"
#include "Samcon.h"
#include"s_OpenFile.h"
#include "CommonTools.h"
#include"TrLang.h"
#include<QList>
#include "MccTools.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern Samcon* w;
#include "LogManager.h"

QStartFromIndex::QStartFromIndex(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	//ui.XMoveto->setEnabled(0);
	//ui.YMoveto->setEnabled(0);
	//ui.ZMoveto->setEnabled(0);
	ui.Shight->setEnabled(0);
	iv = new QIntValidator();
	iv2 = new QIntValidator();
	ui.lineEdit->setValidator(iv);
	typedef void(QComboBox::*QComboBoxtypedef)(int);
	QComboBoxtypedef func = &QComboBox::currentIndexChanged;

	connect(ui.XMoveto, &QLineEdit::textChanged, [this]() {
		mx = ui.XMoveto->text();
	});
	connect(ui.YMoveto, &QLineEdit::textChanged, [this]() {
		my = ui.YMoveto->text();
	});
	connect(ui.ZMoveto, &QLineEdit::textChanged, [this]() {
		mz = ui.ZMoveto->text();
	});
	connect(ui.sure, &QPushButton::clicked, [this]() {

		if (ui.comboBox->currentIndex() == SammonFunc::Getins()->IndexRrcod)
			return;
		SammonFunc::Getins()->IndexRrcod = ui.comboBox->currentIndex();//删掉这句，，程序崩溃~~~~	
		w->getOpenFile()->LoadFomeStartLine(ui.comboBox->currentIndex());
	});
	connect(SammonFunc::Getins(), &SammonFunc::startLineloadOver, [this]() {
		iv->setRange(0, ItemNumList[ui.comboBox->currentIndex()].toInt());
		ui.lineEdit->setText(QString::number(SammonFunc::Getins()->IndexRrcod*BIGSIZE + 1));
		ui.lineEdit->setPlaceholderText(TrLang::text(337).arg(BIGSIZE*SammonFunc::Getins()->IndexRrcod).arg(ItemNumList[SammonFunc::Getins()->IndexRrcod]));//范围%1-%2     
	});
	connect(ui.bty, &QPushButton::clicked, [this]() {
		//if (!SammonFunc::CanDoit(0))return;
		int num = ui.lineEdit->text().toInt();
		if (num - ui.comboBox->currentIndex() * BIGSIZE <= 0) {
			QMessageBox::information(0, "Error", TrLang::text(339));//输入的行号不正确
			return;
		}
	
		if (ui.XMoveto->text().isEmpty() || ui.YMoveto->text().isEmpty() || ui.ZMoveto->text().isEmpty()) {
			QString str;
			QString str2 = TrLang::text(340);//获取%1坐标错误，请手动输入
			if (ui.XMoveto->text().isEmpty())
				str += " X ";
			if (ui.YMoveto->text().isEmpty())
				str += " Y ";
			if (ui.ZMoveto->text().isEmpty())
				str += " Z ";
			QMessageBox::information(0, "Error", str2.arg(str));
			return;
		}
		if (!ui.switchT->text().isEmpty()) {
			int tNo = SammonFunc::GetNumber(ui.switchT->text(), 't', 'T').toInt();
			emit StartLineSwitchT(tNo);
		}
		
		G02G03 = "";
		int tempRow = ui.lineEdit->text().toInt() - 1 - ui.comboBox->currentIndex() * BIGSIZE;
		QString tempLine = pAutoWork->TableRowList[tempRow];
		if (SammonFunc::CheckContains(tempLine, 8, "i", "I", "j", "J", "k", "K", "r", "R")) {
			if (tempLine.contains("G02") || tempLine.contains("G2"))
				G02G03 = "G02";
			if (tempLine.contains("G03") || tempLine.contains("G3"))
				G02G03 = "G03";
			if (G02G03.isEmpty()) {
				QMessageBox::information(0, "Error", TrLang::text(366));
				return;
			}
		}

	
		SammonFunc::StartLine = num- SammonFunc::Getins()->IndexRrcod*BIGSIZE;
		SammonFunc::isStartFormIdx = true;
		LogManager::getIns()->appendLog(TrLang::text(341).arg(num));//正在准备从 %1 行加工
		close();
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {
		close();
	});

	connect(ui.lineEdit, &QLineEdit::textChanged, [this](QString str) {
		
		mx = my = mz = "";
		int num = str.toInt();
		if (num <= ui.comboBox->currentIndex() * BIGSIZE||num> ItemNumList[ui.comboBox->currentIndex()].toInt())
			return;

		pAutoWork->resetlh();
		pAutoWork->UpdataText(num-ui.comboBox->currentIndex ()*BIGSIZE);
		setPos(num - 2- ui.comboBox->currentIndex() * BIGSIZE);//下标0开始 -1，退一行 -1
		if (!mx.isEmpty())
			ui.XMoveto->setText(mx);
		else
			ui.XMoveto->clear();
		if (!my.isEmpty())
			ui.YMoveto->setText(my);
		else
			ui.YMoveto->clear();
		if (!mz.isEmpty())
			ui.ZMoveto->setText(mz);
		else
			ui.ZMoveto->clear();

		int TCode = SammonFunc::SwtichTInLine(num);
		if(TCode)
			ui.switchT->setText(QString("T%1").arg(TCode));
		else
			ui.switchT->clear();
	});
}

QStartFromIndex::~QStartFromIndex()
{
}

void QStartFromIndex::ResetLanguage()
{
	setDlgName(TrLang::text(75));
	ui.sure->setText(TrLang::text(160));
	ui.btn->setText(TrLang::text(111));
	ui.bty->setText(TrLang::text(86));
	ui.unloadlab->setText(TrLang::text(342));
	ui.label_7->setText(TrLang::text(343));
	ui.label_8->setText(TrLang::text(344));
	ui.label->setText(TrLang::text(345));
	ui.label_5->setText(TrLang::text(346));
	ui.label_9->setText(TrLang::text(347));
	ui.label_6->setText(TrLang::text(348));
	ui.switchT->setPlaceholderText(TrLang::text(338));//未找到换刀指令
}

void QStartFromIndex::setText()
{
	ui.lineEdit->setText(QString::number(w->isMCode + ui.comboBox->currentIndex()));
}

bool QStartFromIndex::CheckPos()//检测点是否相同
{
	double x, y, z;
	x = mcc->GetWorkpieceCoordinate(0);
	y = mcc->GetWorkpieceCoordinate(1);
	z = mcc->GetWorkpieceCoordinate(2);



	double a = mcc->GetParameterValue(110) / mcc->GetParameterValue(120);
	double b = mcc->GetParameterValue(111) / mcc->GetParameterValue(121);
	double c = mcc->GetParameterValue(112) / mcc->GetParameterValue(122);

	bool bx = 1/a >= abs(x - mx.toDouble());
	bool by = 1/b >= abs(y - my.toDouble());
	bool bz =1/c >= abs(z - mz.toDouble());
#ifdef _DEBUG
	qDebug() << "1/a:"<<1 / a;
	qDebug() << "abs" << abs(x - mx.toDouble());
	qDebug() << "1/b:" << 1 / b;
	qDebug() << "abs" << abs(y - my.toDouble());
	qDebug() << "1/c:" << 1 / c;
	qDebug() << "abs" << abs(z - mz.toDouble());
#endif // DEBUG

	if (bx&&by&&bz)
		return 1;

	
	int cod = ui.lineEdit->text().toInt();
	if (cod == 0)return false;
	if (cod >= 0 && cod <= pAutoWork->TableRowList.size() - 1) {
		ui.lineEdit->setText(QString::number(cod));
		ui.lineEdit->textChanged(QString::number(cod));//这里会更新 3 个 lineEdit 的值
	}
	else {
		ui.lineEdit->setText(QString::number(0));
		ui.lineEdit->textChanged(QString::number(0));
	}

	 bx = 1 / a >= abs(x - mx.toDouble());
	 by = 1 / b >= abs(y - my.toDouble());
	 bz = 1 / c >= abs(z - mz.toDouble());
#ifdef _DEBUG
	 qDebug() << "1/a:" << 1 / a;
	 qDebug() << "abs" << abs(x - mx.toDouble());
	 qDebug() << "1/b:" << 1 / b;
	 qDebug() << "abs" << abs(y - my.toDouble());
	 qDebug() << "1/c:" << 1 / c;
	 qDebug() << "abs" << abs(z - mz.toDouble());
#endif // DEBUG
	 if (bx&&by&&bz)
		 return 1;

	return 0;
}

void QStartFromIndex::showEvent(QShowEvent * event)
{
	InitInfo();
	ui.bty->setFocus();
	QWidget::showEvent(event);
}

void QStartFromIndex::setPos(int row)
{
	if (row < 0)return;
	int	num = 0;
	for (int i = row; i < pAutoWork->TableRowList.size()&&i>= num; i--) {
		QString  curline = pAutoWork->TableRowList[i];
		if (mx.isEmpty())mx = SammonFunc::GetNumber(curline, 'x', 'X');
		if (my.isEmpty())my = SammonFunc::GetNumber(curline, 'y', 'Y');
		if (mz.isEmpty())mz = SammonFunc::GetNumber(curline, 'z', 'Z');
		if (!mx.isEmpty() && !my.isEmpty() && !my.isEmpty())
			break;		
	}
}

void QStartFromIndex::StartFromIdx()
{
	static int i = 0;
	static bool SaveZ = false;
	static bool MoveZ = false;
	static bool MoveXY = false;
	if (w->isMCode)return;
	if (SammonFunc::isStartFormIdx) {
		if (i++ <= 3)return;
		i = 0;
		QString str = "";
		if (!SaveZ&&mcc->GetWorkpieceCoordinate(2) >= readIni.GetSafetyHeight().toDouble()) {
			SaveZ = true;
			LogManager::getIns()->debugLog(QString("0:%1").arg("start"));
		}
		if (!SaveZ &&mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {
			str = str + "G01G90Z" + readIni.GetSafetyHeight() + "F" + SammonFunc::GetSpeed(0);
			SaveZ = true;
			MccTools::SendMDI(str);
			LogManager::getIns()->debugLog(QString("1:%1").arg(str));
			return;
		}
		if (SaveZ && !MoveXY && !MoveZ &&mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {
			str += "G01G90X" + mx + "Y" + my + "F" + SammonFunc::GetSpeed(1);
			MoveXY = true;
			MccTools::SendMDI(str);
			LogManager::getIns()->debugLog(QString("2:%1").arg(str));
			return;
		}
		if (SaveZ&&MoveXY && !MoveZ&&mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {
			str += "G01G90Z" + mz + "F" + SammonFunc::GetSpeed(0);
			MoveZ = true;
			MccTools::SendMDI(str);
			LogManager::getIns()->debugLog(QString("3:%1").arg(str));
			return;
		}
		if (SaveZ&&MoveXY&&MoveZ) {
			SammonFunc::isStartFormIdx = false;
			showStartLineDlg2 = true;
			SammonFunc::RunShow = false;
			SammonFunc::NextShow = true;
			LogManager::getIns()->debugLog(QString("4:%1").arg("over"));
			if (!G02G03.isEmpty()) {
				mcc->SendAutoText(G02G03);
			}
		}
	}
	else {
		i = 0;
		SaveZ = false;
		MoveZ = false;
		MoveXY = false;
	}
}

void QStartFromIndex::InitInfo()
{
	int tt = w->getOpenFile()->FileCodeCount / BIGSIZE;
	ui.comboBox->clear();
	ItemNumList.clear();
	for (int i = 0; i <= tt; i++) {
		int num1 = 0, num2 = 0;
		num1 = i * BIGSIZE + 1;
		if (i != tt)
			num2 = (i + 1) * BIGSIZE;
		else {
			num2 = w->getOpenFile()->FileCodeCount;
		}
		ItemNumList << QString::number(num2);
		QString str = TrLang::text(337).arg(num1).arg(num2); //范围: % 1 - % 2
		ui.comboBox->addItem(str);
	}
	ui.comboBox->setCurrentIndex(SammonFunc::Getins()->IndexRrcod);
	iv->setRange(0, ItemNumList[ui.comboBox->currentIndex()].toInt());

	ui.XMoveto->clear();
	ui.YMoveto->clear();
	ui.ZMoveto->clear();
	if (!SammonFunc::isLoading) {
		ui.lineEdit->setEnabled(0);
		ui.unloadlab->setVisible(1);
	}
	else {
		ui.unloadlab->setVisible(0);
		ui.lineEdit->setEnabled(1);
		SammonFunc::Getins()->TabIndexChang(1, 0);
	}
	int cod = NcPod::getIns()->Get_CodeLin(0);
	if (SammonFunc::NeedRunNext&&SammonFunc::ReplaceCodeMap.keys().contains(cod)) {
		SammonFunc::NeedRunNext = false;
		cod++;
	}
	ui.lastLine->setText(QString::number(cod));

	if (cod >= 0 && cod <= ItemNumList[ui.comboBox->currentIndex()].toInt() - 1) {
		ui.lineEdit->setText(QString::number(cod));
		ui.lineEdit->textChanged(QString::number(cod));
	}
	else {
		ui.lineEdit->clear();
		//ui.lineEdit->setText(QString::number(0));
		//ui.lineEdit->textChanged(QString::number(0));
	}
	ui.lineEdit->setPlaceholderText(TrLang::text(337).arg(BIGSIZE*SammonFunc::Getins()->IndexRrcod).arg(ItemNumList[SammonFunc::Getins()->IndexRrcod]));//范围%1-%2
	ui.Shight->setText(readIni.GetSafetyHeight());
}
