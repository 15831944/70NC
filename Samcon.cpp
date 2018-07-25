#include "Samcon.h"
#include "QIcon"
#include "Locus.h"
#include "IOSet.h"
#include "SystemMsg.h"
#include "ctrlHand.h"
#include "YesOrNo.h"
#include "DocEdit.h"
#include "QDebug"
#include "QFile"
#include <QtPlatformHeaders/QWindowsWindowFunctions> 
#include <QDesktopWidget> 
#include "QMessageBox"
#include "QAxObject"
#include "QVariant"
#include "DlgSetAxisSpeed.h"
#include "DlgSetParameter.h"
#include "DlgSetAxisSpeed.h"
#include "ResetAxis.h"
#include "s_OpenFile.h"
#include "AutoWork.h"
#include"qdatetime"
#include "DlgSetSpeedAuto.h"
#include "ToolSetting.h"
#include "ReadIni.h"
#include "QStartFromIndex.h"
#include "GManager.h"
#include"ncpod.h"
#include "LogManager.h"
#include "DlgWorkpieceOffset.h"
#include"ToolsChoice.h"
#include"PasswordDlg.h"
#include "phbx.h"
#include"qmenu.h"
#include <Qsci/qsciscintilla.h>
#include "TrGCode.h"
#include"MultifileTask.h"
#include "ExternalText.h"
#include "DlgRegSoft.h"
#include "DlgMachToInternalIncr.h"
#include "DlgHelp.h"
#include "DFX_GCode.h"
#include"myopenglwidget.h"
#include "QuicklySettings.h"
#include "TrLang.h"
#include "MccTools.h"
extern mccdll::MotionControlCard* mcc;
extern QString MyStyle;
extern ReadIni readIni;
extern int bWorkpieceReturn;
extern int bMachineReturn;
extern bool isSimulation;
extern int VersionType;
extern bool IsPC;
bool PushRun = false;
Samcon::Samcon(QWidget *parent)
	: QMainWindow(parent), myProcess(new QProcess)
{
	ui.setupUi(this);

	Init(); 

	/////无边框 初始化
	ui.sizeBt->setVisible(IsPC);
	connect(ui.sizeBt, &QPushButton::clicked, [this] {

		if (isFull) {
			
			showNormal();
		}
		else {
			QWindowsWindowFunctions::setHasBorderInFullScreen(windowHandle(), true);//重要，解决openglwidget 全屏的bug
			showFullScreen();
		}
		isFull = !isFull;
	});
	connect(ui.closebt, &QPushButton::clicked, [this] {
		m_timer.stop();
		readIni.sync();
		pResetAxis->hide();
		myProcess->close();
		mcc->SaveParameterValue();

		SammonFunc::release();
		LogManager::release();
		NcPod::release();
		PHBX::release();

		close();
	});

	isLeftPressDown = false;
	this->dir = NONE;
	centralWidget()->setMouseTracking(true);
	this->setMouseTracking(true);// 追踪鼠标	
}

Samcon::~Samcon()
{

}

void Samcon::ResetLanguage()
{	
	ExternalText::ResetLanguage();
	int i = 42;
	ui.fileBt->setText(TrLang::Ins()->GetText(i++));
	ui.OpBt->setText(TrLang::Ins()->GetText(i++));
	ui.ParamBt->setText(TrLang::Ins()->GetText(i++));
	ui.wmlabel->setText(TrLang::Ins()->GetText(i++));
	ui.kzklabel->setText(TrLang::Ins()->GetText(i++));
	//ui.tabTR->setTabText(0, TrLang::Ins()->GetText(i++));//47
//	ui.tabTR->setTabText(1, TrLang::Ins()->GetText(i++));//48
//	ui.tabTR->setTabText(2, TrLang::Ins()->GetText(i++));//49
//	ui.tabTR->setTabText(3, TrLang::Ins()->GetText(i++));//50
	ui.groupBoxAxis->setTitle(TrLang::text(48));
	ui.groupBoxSpindle->setTitle(TrLang::text(49));
	ui.tabTR->setTabText(0, TrLang::text(59));
	ui.tabTR->setTabText(1, TrLang::text(60));
	ui.tabTR->setTabText(2, TrLang::text(371));
	ui.tabTR->setTabText(3, TrLang::text(61));
	ui.tabTR->setTabText(4, TrLang::text(62));
	ui.tabTR->setTabText(5, TrLang::text(50));

	i += 4;
	ui.label_12->setText(TrLang::Ins()->GetText(i++));
	ui.label_13->setText(TrLang::Ins()->GetText(i++));
	ui.label_14->setText(TrLang::Ins()->GetText(i++));
	ui.tabLeft->setTabText(0, TrLang::Ins()->GetText(i++));
	ui.tabLeft->setTabText(1, TrLang::Ins()->GetText(i++));
	ui.tabLeft->setTabText(2, TrLang::Ins()->GetText(i++));
	ui.tabLeft->setTabText(3, TrLang::Ins()->GetText(i++));
	ui.tabLeft->setTabText(4, TrLang::Ins()->GetText(i++));
	//ui.tabRight->setTabText(0, TrLang::Ins()->GetText(i++));//59
	//ui.tabRight->setTabText(1, TrLang::Ins()->GetText(i++));
	//ui.tabRight->setTabText(2, TrLang::Ins()->GetText(i++));
	//ui.tabRight->setTabText(3, TrLang::Ins()->GetText(i++));//62

	i += 4;
	ui.label->setText(TrLang::Ins()->GetText(i++));
	ui.label_4->setText(TrLang::Ins()->GetText(i));
	ui.label_2->setText(TrLang::Ins()->GetText(i++));
	ui.label_16->setText(TrLang::Ins()->GetText(i++));
	ui.label_17->setText(TrLang::Ins()->GetText(i++));
	ui.label_3->setText(TrLang::Ins()->GetText(i++));

	ui.label_5->setText(TrLang::Ins()->GetText(i++));
	ui.label_6->setText(TrLang::Ins()->GetText(i++));
	ui.label_7->setText(TrLang::Ins()->GetText(i++));
	ui.label_9->setText(TrLang::Ins()->GetText(i++));
	ui.label_8->setText(TrLang::Ins()->GetText(i++));
	AcLoadG->setText(TrLang::Ins()->GetText(i++));
	RecentG->setTitle(TrLang::Ins()->GetText(i++));
	AcStart->setText(TrLang::Ins()->GetText(i++));
	AcRunDraw->setText(TrLang::Ins()->GetText(i++));
	AcDxf->setText(TrLang::Ins()->GetText(i++));

	AcResetAxis->setText(TrLang::Ins()->GetText(i++));
	AcWpOffset->setText(TrLang::Ins()->GetText(i++));
	AcMultifileTask->setText(TrLang::Ins()->GetText(i++));
	Acmaichongdangliang->setText(TrLang::Ins()->GetText(i++));
	AcDlgSetParameter->setText(TrLang::Ins()->GetText(i++));
	settings->setText(TrLang::Ins()->GetText(i++));
	AcHelp->setText(TrLang::text(370));
	ui.ToolOpen->setToolTip(TrLang::Ins()->GetText(73));
	ui.ToolReturnW->setToolTip(TrLang::Ins()->GetText(84));
	ui.ToolStartFrom->setToolTip(TrLang::Ins()->GetText(85));
	ui.ToolRun->setToolTip(TrLang::Ins()->GetText(86));
	ui.ToolPause->setToolTip(TrLang::Ins()->GetText(87));
	ui.ToolNext->setToolTip(TrLang::Ins()->GetText(88));
	ui.ToolStop->setToolTip(ExternalText::Stop);
	ui.ToolRestart->setToolTip(TrLang::Ins()->GetText(89));
	ui.ToolReset->setToolTip(TrLang::Ins()->GetText(90));
	AcLangMenu->setTitle(TrLang::text(364));

	strstateLabelFlag = TrLang::text(6);
	//pLocus->ResetLanguage();
	pGManager->ResetLanguage();
	pIO->ResetLanguage();
	pDocEdit->ResetLanguage();
	pSystemMsg->ResetLanguage();
	pCtrlHand->ResetLanguage();
	pToolSetting->ResetLanguage();
	pToolsChoice->ResetLanguage();
	pDlgWorkpieceOffset->ResetLanguage();
	pResetAxis->ResetLanguage();
	pMultifileTask->ResetLanguage();
	pDlgMachToInternalIncr->ResetLanguage();
	pQuicklySettings->ResetLanguage();
	pDlgSetParameter->ResetLanguage();
	pQStartFromIndex->ResetLanguage();
	pDlgSetAxisSpeed->ResetLanguage();
	pDlgSetSpeedAuto->ResetLanguage();
}

void Samcon::InitTimer()
{
	NcPod::getIns()->OpenPadDevci(0);
	
	connect(&m_timer, &QTimer::timeout, [this]() {
		//qDebug()<< mcc->GetCodeLength();
		//pDlgRegSoft->TimeCheckReg();
		if (!showState())return;//工具栏显示 运动卡状态		//断点续传 打开主轴 延时
#ifndef _DEBUG
		pLocus->GetShowBt()->setVisible(SammonFunc::isLoading&& mcc->GetGmode(11).toInt() == 4);
#endif // _DEBUG
		showInfo();//当前行号 加工时间 等信息
		FixFeedrateMultiple();
		MySpeedCtrlSud();
		if (OpenSpindleRotat())//判断是否 需要打开主轴
			MySpeedCtrlPlus();//自动加工 开始 继续是 慢慢提速
		SetLastCoordinate();//初始化上次保存的坐标点
		WorkpieceReturn();//工件坐标回0；
		pResetAxis->MachineReturn();//回机床	
		pToolSetting->zToolSetting();//对刀
		pToolSetting->zFToolSetting();
		pIO->showIconOut();//IO  in
		pIO->showIconIn();//IO  out	
		showAxis();// 更新坐标轴显示  刀路
		pQStartFromIndex->StartFromIdx();//起始行开始
		pIO->timerIn11Run();//in11 start
		sendStopZMDI();//暂停时Z抬刀量
		CheckOffsetChange();//偏执
		SpindleRotate();//主轴
		GetYiTiJiKey();//一体机按键获取
		NcPod::getIns()->SetHomeLmt();
		RunMulitifile();
		CheckAuto();
		pTrGCode->DoDrillHoleCodeG81();
		pTrGCode->DoDrillHoleCodeG82();
		pTrGCode->DoDrillHoleCodeG73();
		pTrGCode->DoDrillHoleCodeG85();
		pTrGCode->DoDrillHoleCodeG86();
		pTrGCode->DoDrillHoleCodeG89();
		pTrGCode->DoG31();
		pToolSetting->DoMAutoToolSetting();
		DoMCode();
	});
	m_timer.start(50);

}

void Samcon::LoadStyleSheet(QString str /*= ""*/)
{
	QString fileName;
	if (!str.isEmpty())
		fileName = str;
	else
		fileName = "./style.qss";
	QFile file(fileName);
	if (file.open(QFile::ReadOnly))
	{
		MyStyle = QLatin1String(file.readAll());
		setStyleSheet(MyStyle);
		file.close();
	}
	else
	{
		QMessageBox::information(NULL, "warning", "Reading style.qss failure");
	}
}

void Samcon::VersionConversion(bool is6Axis, bool isFull)
{
	ui.label_22->setVisible(is6Axis);
	ui.label_b->setVisible(is6Axis);
	ui.BTB->setVisible(is6Axis);
	ui.label_24->setVisible(is6Axis);
	ui.label_c->setVisible(is6Axis);
	ui.BTC->setVisible(is6Axis);
	pCtrlHand->VersionConversion(is6Axis);
	pResetAxis->VersionConversion(is6Axis);



	this->is6Aixs = is6Aixs;
	this->isFull = isFull;
	BSize = 9;
}

void Samcon::ncpodRewind()
{
	if (!SammonFunc::isLoading)
		return;
	if (!SammonFunc::CanDoit())return;
	pAutoWork->UpdataText(1);
	int i = 1;
	mcc->SetStartline(i);
	mcc->ClearBuffer();
	mcc->SendAutoText(QString(""));
	SammonFunc::StartLine = -1;
	SammonFunc::RunShow = true;
	SammonFunc::PauseShow = 0;
	SammonFunc::NextShow = 0;
}

double Samcon::ncpodSindleoverride()
{
	double Muitiple = ui.ScrollBar_ZZKZ->value() / 100.0f;
	return mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1)*Muitiple;
}

void Samcon::ncpodSet818(double GJspeed)
{

	mcc->SetFeedrateMultiple(GJspeed);//设置进给速度
	readIni.SetFeedrate(QString::number(GJspeed));
	mcc->SetParameterValue(105, (float)GJspeed*1.5);
	ui.BtSetSpeed->setText(QString::number(GJspeed));

}

void Samcon::setWorkcoodr(int axis, double value)
{
	if (!SammonFunc::CanDoit())return;
	//mcc->GetGmode(11).toInt();
	mcc->SetSeekZero(axis, value);
	double fsdfsdfsd = mcc->GetMachineCoordinate(axis - 12);
	pDlgWorkpieceOffset->SetWorkpiece(axis-12, mcc->GetMachineCoordinate(axis - 12) - value);
	LogManager::getIns()->appendLog(TrLang::Ins()->GetText(97) + SammonFunc::Getins()->getAxis(axis - 12)+QString("  %1").arg(value));//清除工件坐标：
}

void Samcon::ignoreToolChange(int tt)
{
	pToolsChoice->ignoreToolChange(tt);
	pToolsChoice->setToolChecked(tt);
}

QStartFromIndex* Samcon::GetStartLineDlg()
{
	return pQStartFromIndex;
}

void Samcon::mousePressEvent(QMouseEvent * event)
{
	if (isFull)return;
	switch (event->button()) {
	case Qt::LeftButton:
		isLeftPressDown = true;
		if (dir != NONE) {
			this->mouseGrabber();
		}
		else {
			if (ui.toolBar->geometry().contains(event->globalPos() - this->frameGeometry().topLeft())) {
				dragPosition = event->globalPos() - this->frameGeometry().topLeft();
				mDragTitle = true;
			}
		}
		break;
	case Qt::RightButton:
		//this->close();
		break;
	default:
		QMainWindow::mousePressEvent(event);
	}

	event->ignore();
}

void Samcon::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton) {
		isLeftPressDown = false;
		mDragTitle = false;
		if (dir != NONE) {
			this->releaseMouse();
			this->setCursor(QCursor(Qt::ArrowCursor));
		}
	}
	QMainWindow::mouseReleaseEvent(event);
}

void Samcon::mouseMoveEvent(QMouseEvent * event)
{
	QPoint gloPoint = event->globalPos();
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	if (!isLeftPressDown) {
		this->region(gloPoint);
	}
	else {

		if (dir != NONE) {
			QRect rMove(tl, rb);

			switch (dir) {
			case LEFT:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				break;
			case RIGHT:
				rMove.setWidth(gloPoint.x() - tl.x());
				break;
			case UP:
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case DOWN:
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case LEFTTOP:
				if (rb.x() - gloPoint.x() <= this->minimumWidth())
					rMove.setX(tl.x());
				else
					rMove.setX(gloPoint.x());
				if (rb.y() - gloPoint.y() <= this->minimumHeight())
					rMove.setY(tl.y());
				else
					rMove.setY(gloPoint.y());
				break;
			case RIGHTTOP:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setY(gloPoint.y());
				break;
			case LEFTBOTTOM:
				rMove.setX(gloPoint.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			case RIGHTBOTTOM:
				rMove.setWidth(gloPoint.x() - tl.x());
				rMove.setHeight(gloPoint.y() - tl.y());
				break;
			default:
				break;
			}
			this->setGeometry(rMove);
		}
		else {
			if (mDragTitle)
				move(event->globalPos() - dragPosition);
			event->accept();
		}
	}
	QMainWindow::mouseMoveEvent(event);
}

void Samcon::paintEvent(QPaintEvent * event)
{
	

	QPainterPath path;
	path.setFillRule(Qt::WindingFill);
	path.addRect(BSize, BSize, this->width() - BSize*2, this->height() - BSize*2);

	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing, true);
	painter.fillPath(path, QBrush(Qt::white));

	QColor color(0, 0, 123, 50);//边框颜色

	for (int i = 0; i < BSize; i++)
	{
		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRect(BSize - i, BSize - i, this->width() - (BSize - i) * 2, this->height() - (BSize - i) * 2);
		color.setAlpha(150 - qSqrt(i) * 50);
		painter.setPen(color);
		painter.drawPath(path);
	}
}

void Samcon::OpenFile()
{
	pMultifileTask->SetMultifileTaskAutoWork(0);
	pOpenFile->LoadFile(pAutoWork);
	
}

bool  Samcon::OpenSpindleRotat() {
	//断点续传 打开主轴 延时
	static bool once = false;
	if (SammonFunc::isNeedOpenSpindleRotat) {
		
		if (!once) {
			if (stopSpindleRotate == 0) {
				mcc->SetSpindleRotate(mcc->GetParameterValue(106));
			}
			else {
				mcc->SetSpindleRotate(stopSpindleRotate);
				//stopSpindleRotate = 0;
			}
			once = true;
		}
			
		strstateLabelWarn = ExternalText::OpenSpindleMsg;
		int tt  = readIni.GetSpindleOpen().toInt();
		static int dt = 0;
		dt += 50;
		if (dt < tt) {	
			return 0;
		}
		dt = 0;		
		SammonFunc::isNeedOpenSpindleRotat = false;
		//return 1;
	}
	else {
		once = false;
	}
	return 1;
}

void Samcon::FixFeedrateMultiple() {
	if (fixFeedrateMultiple) {
		static int i = 0;
		if (i < 10) {
			i++;
			if(i==5)
				mcc->SetFeedrateMultiple(ui.ScrollBar_GJSD->value());
			return;
		}
		i = 0;
		fixFeedrateMultiple = !fixFeedrateMultiple;	
	}
}

void Samcon::Init()
{
	InitOther();
	InitMenu();	
	InitToolBar();
	InitGroup1();
	InitGroup2();
	InitGroup3();
	InitGroup4();
	InitTabLeft();
	InitTabRight();
	InitTimer();	
}

void Samcon::InitOther()
{
	LoadStyleSheet();

	pDlgSetAxisSpeed = new DlgSetAxisSpeed(this);
	pDlgSetSpeedAuto = new	DlgSetSpeedAuto(this);
	pDlgSetParameter = new DlgSetParameter(this);
	pToolsChoice = new ToolsChoice;
	pResetAxis = new ResetAxis(this);
#ifndef _DEBUG
	pResetAxis->show();
#endif // !_DEBUG
	pOpenFile = new s_OpenFile();
	pAutoWork = new AutoWork;
	pToolSetting = new ToolSetting(this);
	pQStartFromIndex = new QStartFromIndex(this);
	pQStartFromIndex->trantowork(pAutoWork);
	pGManager = new	GManager(this);
	pLocus = new Locus();
	pIO = new IOSet;
	pSystemMsg = new SystemMsg;
	pDocEdit = new DocEdit;
	pCtrlHand = new ctrlHand(this);
	pDlgWorkpieceOffset = new DlgWorkpieceOffset(this);
	pQuicklySettings = new QuicklySettings(this);
	pTrGCode = new TrGCode;
	pMultifileTask = new MultifileTask(this);
	//pDlgRegSoft = new DlgRegSoft(this);
	pDlgMachToInternalIncr = new DlgMachToInternalIncr(this);
	connect(SammonFunc::Getins(), &SammonFunc::EditFile, [this](QString str) {//文件编辑
		pDocEdit->EditFile(str);
	});
	connect(SammonFunc::Getins(), &SammonFunc::LoadFile, [this](QString str) {//文件装载
		pMultifileTask->SetMultifileTaskAutoWork(0);
		pOpenFile->LoadFile(pAutoWork, str);
	});
	connect(SammonFunc::Getins(), &SammonFunc::UnloadFile, [this]() {//文件卸载
		pMultifileTask->SetMultifileTaskAutoWork(0);
		pAutoWork->clear();
	});

	connect(SammonFunc::Getins(), &SammonFunc::TabIndexChang, [this] (int flag,int idx){
		if (flag == 1)
			ui.tabRight->setCurrentIndex(idx);
		else
			ui.tabLeft->setCurrentIndex(idx);
	});
	connect(SammonFunc::Getins(), &SammonFunc::SendShowGCodeGLWidget, [this]() {
		pOpenFile->pAnalysisG.ShowGCode(pAutoWork->TableRowList);
		MyOpenGLWidget * w = new MyOpenGLWidget();
		w->show();
		w->reset();
		w->reset();
		w->reset();
	});

	connect(pQStartFromIndex, &QStartFromIndex::StartLineSwitchT, pToolsChoice, &ToolsChoice::setToolChecked);
	connect(pMultifileTask, &MultifileTask::MultifileTaskLoadFile, this,[this](QString flileName) {
		if (flileName.isEmpty()) {

		}
		else {
			pOpenFile->LoadFile(pAutoWork, flileName);
		}
		bRunMultifile = true;
		pAutoWork->setPaiChengCiShu(TrLang::Ins()->GetText(98) +pMultifileTask->GetCurtimeStr().right(3));//加工次数
	});

	connect(SammonFunc::Getins(), &SammonFunc::ZhuCheKuaiDaoQi, [this](QString str) {//注册快到期
		ui.MLabel->setText(str);
	});
}

void Samcon::InitMenu()
{
	menuAuto = new QMenu(QStringLiteral("文件(F)"), this);
	connect(ui.fileBt, &QPushButton::clicked, [this] {
		menuAuto->show();
		int x = 0;
		int y = ui.fileBt->height();
		QPoint p(x, y);
		p = ui.fileBt->mapToGlobal(p);
		menuAuto->move(p);
	});



	AcLoadG = new QAction(0);//载入G代码
	menuAuto->addAction(AcLoadG);
	connect(AcLoadG, &QAction::triggered, [this](bool b) {
		OpenFile();
	});

	 RecentG = new QMenu(0);//最近加工文件
	menuAuto->addMenu(RecentG);
	for (int i = 0; i <FILESIZE ; i++) {
		QString str = readIni.GetOpenRecentFile()[i];
		if (str.isEmpty())
			continue;
		QAction*  Ac = new QAction(str, 0);
		RecentG->addAction(Ac);
		connect(Ac, &QAction::triggered, [this,str](bool b) {
			pOpenFile->LoadFile(pAutoWork, str);
		});
	}
	menuAuto->addSeparator();
	
	AcStart = new QAction(0);//高级开始
	menuAuto->addAction(AcStart);
	connect(AcStart, &QAction::triggered, [this](bool b) {
		pQStartFromIndex->show();
	});
	AcRunDraw = new QAction(0);//VB脚本编辑
	menuAuto->addAction(AcRunDraw);
	
	connect(AcRunDraw, &QAction::triggered, [this](bool b) {
		myProcess->start("./draw.exe");
	});

	 AcDxf = new QAction(0);//DXF转G代码
	menuAuto->addAction(AcDxf);
	connect(AcDxf, &QAction::triggered, [this](bool b) {
		DFX_GCode * dlg = new DFX_GCode(this);
	});

	AcLangMenu = new QMenu("Language");
	QAction *LangCn = new QAction(QStringLiteral("中文"), 0);
	QAction *LangEn = new QAction("English", 0);
	menuAuto->addMenu(AcLangMenu);
	AcLangMenu->addAction(LangCn);
	AcLangMenu->addAction(LangEn);
	connect(LangCn, &QAction::triggered, [this](bool b) {
		TrLang::Ins()->setLanguageIndxe(0);
		ResetLanguage();
	});
	connect(LangEn, &QAction::triggered, [this](bool b) {
		TrLang::Ins()->setLanguageIndxe(1);
		ResetLanguage();
	});

	AcHelp = new QAction(0);
	menuAuto->addAction(AcHelp);
	connect(AcHelp, &QAction::triggered, [this](bool istriggered) {
		DlgHelp  *dlg = new  DlgHelp(this);
		dlg->show();
	});
	///////////////////////////////////////////////////////////////
	menuHM = new QMenu();
	connect(ui.OpBt, &QPushButton::clicked, [this] {
		menuHM->show();
		int x = 0;
		int y = ui.OpBt->height();
		QPoint p(x, y);
		p = ui.OpBt->mapToGlobal(p);
		menuHM->move(p);
	});
	 AcResetAxis = new QAction(0);//回机床原点
	menuHM->addAction(AcResetAxis);
	connect(AcResetAxis, &QAction::triggered, [this](bool b) {
		pResetAxis->show();

	});

	AcWpOffset = new QAction(0);//工件偏执
	menuHM->addAction(AcWpOffset);
	connect(AcWpOffset, &QAction::triggered, [this](bool b) {
		pDlgWorkpieceOffset->show();
	});

	AcMultifileTask = new QAction(0); //排程加工
	menuHM->addAction(AcMultifileTask);
	connect(AcMultifileTask, &QAction::triggered, [this](bool b) {
		pMultifileTask->show();
	});

	Acmaichongdangliang = new QAction(0);//脉冲当量计算
	menuHM->addAction(Acmaichongdangliang);
	connect(Acmaichongdangliang, &QAction::triggered, [this](bool b) {
		pDlgMachToInternalIncr->show();
	});
	if (VersionType == 4) {
		QAction* AcSPindleUp = new QAction(QStringLiteral("主轴抬起"),0);
		menuHM->addAction(AcSPindleUp);
		connect(AcSPindleUp, &QAction::triggered, [this](bool b) {
			isMCode = true;
			MCodeName = "6";
			MCodeFromMDI = true;
			NcPod::getIns()->newT = 6;
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
		});

		QAction* AcSpindleDown = new QAction(QStringLiteral("主轴下降"),0);
		menuHM->addAction(AcSpindleDown);
		connect(AcSpindleDown, &QAction::triggered, [this](bool b) {
			isMCode = true;
			MCodeName = "6";
			MCodeFromMDI = true;
			NcPod::getIns()->newT = 5;
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
		});
	}
	//////////////////////////////////////////////////////////////////////////
	menuParam = new QMenu();
	connect(ui.ParamBt, &QPushButton::clicked, [this] {
		menuParam->show();
		int x = 0;
		int y = ui.ParamBt->height();
		QPoint p(x, y);
		p = ui.ParamBt->mapToGlobal(p);
		menuParam->move(p);
	});

	 AcDlgSetParameter = new QAction(0);//设置参数
	menuParam->addAction(AcDlgSetParameter);
	connect(AcDlgSetParameter, &QAction::triggered, [this](bool b) {
		pDlgSetParameter->show();
	});
	connect(pDlgSetParameter, &DlgSetParameter::updateText, [this]() {
		if (ui.tabRight->currentIndex() == 0) 
			ui.BtSetSpeed->setText(readIni.GetFeedrate());
		
	});
	 settings = new QAction(0);//快速参数设置
	menuParam->addAction(settings);
	connect(settings, &QAction::triggered, [this](bool b) {
		pQuicklySettings->show();
	});

//	menuAasist = new QMenu("hellp");
//	
//	connect(ui.HelpBt, &QPushButton::clicked, [this] {
//		menuAasist->show();
//		int x = 0;
//		int y = ui.HelpBt->height();
//		QPoint p(x, y);
//		p = ui.HelpBt->mapToGlobal(p);
//		menuAasist->move(p);
//	});

//
//	QAction * AcReg = new QAction(QStringLiteral("注册"), 0);
//	//menuAasist->addAction(AcReg);
//	connect(AcReg, &QAction::triggered, [this](bool istriggered) {
//		pDlgRegSoft->show();
//	});
}

void Samcon::InitToolBar()
{
	QAction* AcOpen = new QAction(0);
	
	connect(ui.ToolOpen, &QPushButton::clicked,[this, AcOpen]() {
		AcOpen->trigger();
	});
	connect(AcOpen, &QAction::triggered, [this](bool b) {
		OpenFile();
	});
	connect(pGManager, &GManager::sendOpenFile, [this]() {
		OpenFile();
	});
	//////////////////////////////////////
	AcReturn = new QAction(0 );//回工件原点
	connect(ui.ToolReturnW, &QPushButton::clicked, [this]() {
		AcReturn->trigger();
	});
	connect(AcReturn, &QAction::triggered, [this](bool b) {	
		if (!SammonFunc::CanDoit())return;
		if (mcc->GetWorkpieceCoordinate(2) > readIni.GetSafetyHeight().toInt()) 
			bWorkpieceReturn = 1;	
		else
			bWorkpieceReturn = 2;
		strstateLabelFlag = TrLang::Ins()->GetText(78);
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(78));//回机床原点
	});
	/////////////////////////
	QAction* AcSetStartRow = new QAction(0);
	connect(ui.ToolStartFrom, &QPushButton::clicked, [this, AcSetStartRow]() {
		AcSetStartRow->trigger();
	});
	connect(AcSetStartRow, &QAction::triggered, [this](bool b) {
		pQStartFromIndex->show();
	});
	///////////////////////////////

	AcPlay = new QAction(0);
	connect(ui.ToolRun, &QPushButton::clicked, [this]() {
		AcPlay->trigger();
	});
	connect(AcPlay, &QAction::triggered, [this](bool b) {
		if (!SammonFunc::isLoading)return;
		if (!SammonFunc::CanDoit())return;

		int i = 1;
		mcc->ClearBuffer();
		mcc->SetStartline(i);
		mcc->SendAutoText(QString(""));
		m_runTime.restart();
		m_PassTime = 0;
		strstateLabelFlag = ExternalText::ZiDong;
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(99));//自动加工开始
		SammonFunc::RunShow = false;
		SammonFunc::PauseShow = true;
		SammonFunc::NextShow = 0;
		pQStartFromIndex->showStartLineDlg2 = false;
		isSpeedNeedPlus = true;
		RunOverFlag = false;
		RunFlagTime = 0;
		SammonFunc::CheckFeedrate();
	});
	connect(pOpenFile, &s_OpenFile::signal_fileLoad, [this]() {
		AcPlay->setEnabled(true);
		pLocus->clear();
		pGManager->setPath(readIni.GetOpenRecentDir());
		pAutoWork->resetlh();
		pAutoWork->UpdataText(1);
	});
/////////////////////////////////////////////////
	AcPause = new QAction(0);
	connect(ui.ToolPause, &QPushButton::clicked, [this]() {
		AcPause->trigger();
	});
	connect(AcPause, &QAction::triggered, [this](bool b) {
		if (!SammonFunc::isLoading)return;
		if (mcc->GetWorkState() == 1) {
			SammonFunc::IsPause = true;
			isSpeedNeedSud = true;
		}
		needShowStartLine = false;
		if (pTrGCode->isG81|| pTrGCode->isG82|| pTrGCode->isG73|| pTrGCode->isG85|| pTrGCode->isG86|| pTrGCode->isG89|| pTrGCode->isG31!=-1||isMCode) {//停止、M00处理特殊G代码时 暂停   需要显示起始行 回到正确位置
			if (pTrGCode->isG31 != -1)	NcPod::getIns()->StopPMov(0, pTrGCode->isG31);
			pTrGCode->isG81 = false;
			pTrGCode->isG82 = false;
			pTrGCode->isG73 = false;
			pTrGCode->isG85 = false;
			pTrGCode->isG86 = false;
			pTrGCode->isG89 = false;
			if (isMCode) {
				isMCode = false;
				NcPod::getIns()->StopMacr(0);
				if (MCodeName == "6")
				ignoreToolChange(readIni.GetTool());
			}
			pTrGCode->isG31 = -1;
			SammonFunc::SetSpeedControl_stop(isSimulation);
			needShowStartLine = true;
		}
		strstateLabelFlag = TrLang::Ins()->GetText(87);//暂停
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(87));
		SammonFunc::RunShow = 0;
		SammonFunc::PauseShow = 0;
		SammonFunc::NextShow = 1;
	});
	///////////////////////////////////////////
	AcNext = new QAction(0);//断点继续
	connect(ui.ToolNext, &QPushButton::clicked, [this]() {
		AcNext->trigger();
	});
	connect(AcNext, &QAction::triggered, [this](bool b) {
		if (!SammonFunc::isLoading)return;
		if (stopZflag == true)return;	
		if (!SammonFunc::CanDoit(false))return;
		if (needShowStartLine) {
			pQStartFromIndex->showStartLineDlg2 = pQStartFromIndex->CheckPos();
			if (!pQStartFromIndex->showStartLineDlg2) {
				pQStartFromIndex->show();
				return;
			}
			else {//（不存在的M代码）在同一行 第二次 停下时  由于 之前  执行过 startLine  所以pQStartFromIndex->CheckPos 一定会返回true
				//  所以 就会直接 run   但是 SammonFunc::StartLine  却等于-1.。  就会出错
				if (SammonFunc::StartLine == -1) {
					if (SammonFunc::NeedRunNext)
						SammonFunc::StartLine = mCurRow + 1;
					else
						SammonFunc::StartLine = mCurRow;
					SammonFunc::NeedRunNext = false;
				}
				pQStartFromIndex->showStartLineDlg2 = false;
				mcc->SendAutoText(QString(""));//加工时 停下    如果 执行 mid  需要 设置行号
				mcc->ClearBuffer();
			}
		
		}
		if (SammonFunc::StartLine != -1) {
			MccTools::setStart(SammonFunc::StartLine);
			SammonFunc::StartLine = -1;
		}
		SammonFunc::IsPause = false;
		isSpeedNeedPlus = true;	
		if (ui.btzzkg->text() == TrLang::Ins()->GetText(40) &&readIni.GetIsOpenSpindle()) {
			SammonFunc::isNeedOpenSpindleRotat = true;
		}			
		strstateLabelFlag =ExternalText::ZiDong;
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(88));//断点继续
		SammonFunc::PauseShow = 1;
		SammonFunc::NextShow = 0;
		needShowStartLine = false;
		RunOverFlag = false;
		SammonFunc::CheckFeedrate();
	});
////////////////////////////////////////////////////////停止
	AcStop = new QAction(0);//停止
	connect(ui.ToolStop, &QPushButton::clicked, [this]() {
		AcStop->trigger();
	});
	connect(AcStop, &QAction::triggered, [this]() {
		if (SammonFunc::isToolSetting || SammonFunc::isFToolSetting)
			NcPod::getIns()->StopPMov(0, 2);
		if(pTrGCode->isG31==-1)
			NcPod::getIns()->StopPMov(0, pTrGCode->isG31);
	
		if (mcc->GetWorkState() == 1&& MccTools::isIdle()) {
			SammonFunc::PauseShow = 0;
			SammonFunc::NextShow = 1;
			isSpeedNeedSud = true;
			
		}
		else {	
			SammonFunc::SetSpeedControl_stop(isSimulation);
		}
		pTrGCode->isG81 = false;
		pTrGCode->isG82 = false;
		pTrGCode->isG73 = false;
		pTrGCode->isG85 = false;
		pTrGCode->isG86= false;
		pTrGCode->isG89 = false;
		pTrGCode->isG31 = -1;
		SammonFunc::Getins()->autoToolSetting = false;
		pQStartFromIndex->showStartLineDlg2 = false;

		StopMCode();
		needShowStartLine = true;
		SammonFunc::IsPause = false;
		stopZflag = !stopZflag;		//修改 回到安全高度

		if (readIni.GetIsCloseSpindle()) {	 
			stopSpindleRotate= mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1);
			mcc->SetSpindleRotate(0);
		}
		strstateLabelFlag = ExternalText::Stop;
		LogManager::getIns()->appendLog(ExternalText::Stop);
		
		pIO->CloseOut5();
		bMachineReturn = 0;//停止机械回0
		SammonFunc::isStartFormIdx = false;//停止指定行加工
		SammonFunc::isToolSetting = false;//停止对刀
		SammonFunc::isFToolSetting = false;	
	});
//////////////////////////////////////////////////
	AcRestart = new QAction(0);//重新加工
	connect(ui.ToolRestart, &QPushButton::clicked, [this]() {
		AcRestart->trigger();
	});
	connect(AcRestart, &QAction::triggered, [this](bool b) {
		//MccTools::SendMDI(QString(""));
		if (!SammonFunc::CanDoit())return;
		if (pOpenFile->PageNum != 0) {
			pOpenFile->LoadFomeStartLine(0);
		}
		pAutoWork->resetlh();
		isSpeedNeedPlus = true;
		strstateLabelFlag = ExternalText::ZiDong;
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(89));//重新加工
		mcc->ClearBuffer();
		mcc->SendAutoText(QString(""));
		int i = 1;
		mcc->SetStartline(i);

		SammonFunc::RunShow = 0;
		SammonFunc::PauseShow = 1;
		SammonFunc::NextShow = 0;
		m_runTime.restart();
		m_PassTime = 0;
		RunFlagTime = 0;
		RunOverFlag = false;
		SammonFunc::CheckFeedrate();
	});
	///////////////////////////////////////////////////
	AcReset = new QAction(0);//复位
	connect(ui.ToolReset, &QPushButton::clicked, [this]() {
		AcReset->trigger();
	});
	connect(AcReset, &QAction::triggered, [this](bool b) {
		NcPod::getIns()->OpenMotoionDevci(0);
		NcPod::getIns()->UnlimtSigna(0, 1);
		SammonFunc::Getins()->autoToolSetting = false;

		if (mcc->GetGmode(11).toInt() == -1) {
			mcc->Ini_card();
		}


		if (SammonFunc::isToolSetting || SammonFunc::isFToolSetting)
			NcPod::getIns()->StopPMov(0, 2);
		SammonFunc::SetSpeedControl_stop(isSimulation);

		bMachineReturn = 0;//停止机械回0
		SammonFunc::isStartFormIdx = false;//停止指定行加工
		SammonFunc::isToolSetting = false;//停止对刀
		SammonFunc::isFToolSetting = false;
		pQStartFromIndex->showStartLineDlg2 = false;
		pTrGCode->isG81 = false;
		pTrGCode->isG82 = false;
		pTrGCode->isG73 = false;
		pTrGCode->isG85 = false;
		pTrGCode->isG86 = false;
		pTrGCode->isG89 = false;
		stopZflag = false;
		pTrGCode->isG31 = -1;
		SammonFunc::Getins()->autoToolSetting = false;
		StopMCode();
		mcc->ClearBuffer();
		needShowStartLine = 1;
		SammonFunc::NextShow = false;
		SammonFunc::PauseShow = false;

		pIO->CloseOut5();
		strstateLabelFlag = TrLang::Ins()->GetText(90);//复位
		LogManager::getIns()->appendLog(TrLang::Ins()->GetText(90));
	});
	connect(SammonFunc::Getins(), &SammonFunc::updateState, [this](QString s1, QString s2) {
		if (!s1.isEmpty())
			strstateLabelFlag = s1;
		if (!s2.isEmpty())
			strstateLabelWarn = s2;
	});
}

void Samcon::InitGroup1()
{
	connect(ui.BTX, &QPushButton::clicked, [this]() {
		if (!readIni.GetSureMsg()) {
			setWorkcoodr(12, 0);
			return;
		}
		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(367));//是否清除工件坐标
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			setWorkcoodr(12, 0);
		});	
	});
	connect(ui.BTY, &QPushButton::clicked, [this]() {
		if (!readIni.GetSureMsg()) {
			setWorkcoodr(13, 0);
			return;
		}
		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(367));
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			setWorkcoodr(13, 0);
		});
	});
	connect(ui.BTZ, &QPushButton::clicked, [this]() {
		if (!readIni.GetSureMsg()) {
			setWorkcoodr(14, 0);
			return;
		}
		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(367));
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			setWorkcoodr(14, 0);
		});
	});
	connect(ui.BTA, &QPushButton::clicked, [this]() {
		if (!readIni.GetSureMsg()) {
			setWorkcoodr(15, 0);
			return;
		}
		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(367));
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			setWorkcoodr(15, 0);
		});
	});
	connect(ui.BTB, &QPushButton::clicked, [this]() {
		if (!readIni.GetSureMsg()) {
			setWorkcoodr(16, 0);
			return;
		}
		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(367));
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			setWorkcoodr(16, 0);
		});
	});
	connect(ui.BTC, &QPushButton::clicked, [this]() {
		if (!readIni.GetSureMsg()) {
			setWorkcoodr(17, 0);
			return;
		}
		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(367));
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			setWorkcoodr(17, 0);
		});
	});
}

void Samcon::InitGroup2()
{
	ui.ScrollBar_GJSD->setRange(0, 150);
	connect(ui.ScrollBar_GJSD, &QScrollBar::valueChanged, ui.label_gjsd, [=]() {
		ui.label_gjsd->setText(QString("%1 %").arg(ui.ScrollBar_GJSD->value()));
		SammonFunc::SetGJSpeed(ui.ScrollBar_GJSD->value());
		mcc->SetFeedrateMultiple(ui.ScrollBar_GJSD->value());
	});
	ui.ScrollBar_GJSD->setValue(100);
	ui.ScrollBar_GJSD->triggerAction(QAbstractSlider::SliderMove);

	connect(ui.BtSetSpeed, &QPushButton::clicked, [this]() {
		pDlgSetSpeedAuto->show();
	});

	char buff[20] = {};
	sprintf(buff, "%.3f", mcc->GetParameterValue(320));
	ui.BtSetSpeed->setText(buff);


	connect(pDlgSetSpeedAuto, &DlgSetSpeedAuto::ChioceYes, [this] {
		ui.BtSetSpeed->setText(readIni.GetFeedrate());
	});

	connect(ui.btclearcount, &QPushButton::clicked, [this]() {
#ifdef _DEBUG

#endif // _DEBUG

		YesOrNo* yn = new YesOrNo(TrLang::Ins()->GetText(91));
		yn->setStyleSheet(MyStyle);
		connect(yn, &YesOrNo::ChioceYes, [this] {
			mFinish = 0;
			ui.btclearcount->setText(QString::number(mFinish));
#ifdef  _DEBUG


#endif //  _DEBUG

		});
	});
	ui.BtSetSpeed->setText(readIni.GetFeedrate());
}

void Samcon::InitGroup3()
{

	ui.ScrollBar_ZZKZ->setRange(0, 100);
	connect(ui.ScrollBar_ZZKZ, &QScrollBar::valueChanged, ui.label_gjsd, [=]() {
		ui.label_zzkz->setText(QString("%1 %").arg(ui.ScrollBar_ZZKZ->value()));
		mcc->SetSpindleMultiple(ui.ScrollBar_ZZKZ->value());
	});
	ui.ScrollBar_ZZKZ->setValue(100);
	ui.label_zzkz->setText(QString("%1 %").arg(ui.ScrollBar_ZZKZ->value()));

	connect(ui.btsdz2, &QPushButton::clicked, [this]() {
		pDlgSetAxisSpeed->show();
	});

	connect(ui.btzzkg, &QPushButton::clicked, [this]() {

		if (ui.btzzkg->text() == ExternalText::ZhuZhouGuan)
		{
			ui.btzzkg->setText(ExternalText::ZhuZhouKai);
			//mcc->SetSpindleRotate(readIni.GetSpindleSpeed().toInt());
			mcc->SetSpindleRotate(mcc->GetParameterValue(106));
		}
		else
		{
			ui.btzzkg->setText(ExternalText::ZhuZhouGuan);
			mcc->SetSpindleRotate(0);
		}
	});

	connect(pDlgSetAxisSpeed, &DlgSetAxisSpeed::ChioceYes, [this] {
		ui.btsdz2->setText(pDlgSetAxisSpeed->GetText());
		if (ui.btzzkg->text() == TrLang::Ins()->GetText(41)) {
			//mcc->SetSpindleRotate(readIni.GetSpindleSpeed().toInt());
			mcc->SetSpindleRotate(mcc->GetParameterValue(106));
		}			
	});
	//ui.btsdz2->setText(readIni.GetSpindleSpeed());
	ui.btsdz2->setText(QString::number(mcc->GetParameterValue(106)));
}

void Samcon::InitGroup4()
{

}

void Samcon::InitTabLeft()
{
	ui.tabLeft->addTab(pLocus, QStringLiteral("加工轨迹"));
	ui.tabLeft->addTab(pGManager, QStringLiteral(" 程序管理 "));
	ui.tabLeft->addTab(pDocEdit, QStringLiteral("程序编辑"));
	ui.tabLeft->addTab(pSystemMsg, QStringLiteral("系统日志"));
	ui.tabLeft->addTab(pIO, QStringLiteral("输入输出"));
	connect(ui.tabLeft, &QTabWidget::currentChanged, [this](int index) {
		SetLeftSubWidgetFocus();
	});
}

void Samcon::InitTabRight()
{
	QTabBar* tb = ui.tabTR->tabBar();
	tb->addTab("手动");
	tb->addTab("速度");
	tb->addTab("对刀");
	tb->addTab("选刀");
	tb->addTab("信息");
	connect(ui.tabTR, &QTabWidget::currentChanged, [this](int index) {
		ui.tabRight->setCurrentIndex(index);
	});

	ui.tabRight->insertTab(0, pAutoWork, "");
	ui.tabRight->insertTab(1, pCtrlHand, "");
	ui.tabRight->insertTab(3, pToolSetting, "");
	ui.tabRight->insertTab(4, pToolsChoice, "");
	connect(ui.tabRight, &QTabWidget::currentChanged, [this](int index) {
		SetRightSubWidgetFocus();
	});
	//ui.tabRight->setCurrentIndex(1);

	ui.tabRight->tabBar()->hide();
}

bool Samcon::SetLastCoordinate()
{
	if (!SammonFunc::LastCoordinateInit) {
		//AcReset->triggered();
		NcPod::getIns()->OpenMotoionDevci(0);
		NcPod::getIns()->UnlimtSigna(0, 1);
		if (mcc->GetGmode(11).toInt() == 4) {
			double str;
			str = readIni.GetXMachineCoordinate().toDouble();
			mcc->SetSeekZero(0, str);
			str = readIni.GetYMachineCoordinate().toDouble();
			mcc->SetSeekZero(1, str);
			str = readIni.GetZMachineCoordinate().toDouble();
			mcc->SetSeekZero(2, str);
			str = readIni.GetAMachineCoordinate().toDouble();
			mcc->SetSeekZero(3, str);
			str = readIni.GetBMachineCoordinate().toDouble();
			mcc->SetSeekZero(4, str);
			str = readIni.GetCMachineCoordinate().toDouble();
			mcc->SetSeekZero(5, str);

	/*		str = readIni.GetXWorkpieceCoordinate().toDouble();
			mcc->SetSeekZero(12, str);
			str = readIni.GetYWorkpieceCoordinate().toDouble();
			mcc->SetSeekZero(13, str);
			str = readIni.GetZWorkpieceCoordinate().toDouble();
			mcc->SetSeekZero(14, str);
			str = readIni.GetAWorkpieceCoordinate().toDouble();
			mcc->SetSeekZero(15, str);
			str = readIni.GetBWorkpieceCoordinate().toDouble();
			mcc->SetSeekZero(16, str);
			str = readIni.GetCWorkpieceCoordinate().toDouble();
			mcc->SetSeekZero(17, str);*/
			SammonFunc::LastCoordinateInit = true;
			MccTools::SendMDI(QString(""));
		}	
	}
	return SammonFunc::LastCoordinateInit;
}

void Samcon::SaveLastCoordinate()
{
	if (!SammonFunc::LastCoordinateInit)return;
	QString fdsf = ui.label_x->text();
	readIni.SetXMachineCoordinate(ui.label_x->text());
	readIni.SetYMachineCoordinate(ui.label_y->text());
	readIni.SetZMachineCoordinate(ui.label_z->text());
	readIni.SetAMachineCoordinate(ui.label_a->text());
	readIni.SetBMachineCoordinate(ui.label_b->text());
	readIni.SetCMachineCoordinate(ui.label_c->text());
	
}

bool Samcon::IsMDIRuningInItmer()
{
	bool bbb = pTrGCode->isG81 || pTrGCode->isG82 || pTrGCode->isG73 || pTrGCode->isG85 || pTrGCode->isG86 || pTrGCode->isG89 || pTrGCode->isG31 != -1 || bWorkpieceReturn != 0 || bMachineReturn != 0 || SammonFunc::isToolSetting || SammonFunc::isFToolSetting ||stopZflag|| SammonFunc::isStartFormIdx;
	return bbb;
}

QString Samcon::getFileName()
{
	return pOpenFile->getFileName(); 
}

void Samcon::keyPressEvent(QKeyEvent * event)
{
	if (!pCtrlHand->MyGetFocus())
		pCtrlHand->keyPressEvent(event);
	
}

void Samcon::keyReleaseEvent(QKeyEvent * event)
{
	if(!pCtrlHand->MyGetFocus())
		pCtrlHand->keyReleaseEvent(event);

}

void Samcon::closeEvent(QCloseEvent * event)
{
	SaveLastCoordinate();
	readIni.sync();
	QMainWindow::closeEvent(event);

}

void Samcon::resizeEvent(QResizeEvent * event)
{
	int px = (height() - 580) / 20;
	px = px >= 0 ? px : 0; 
	px = px <= 10 ? px : 10;
	int _h = 15 + px;//15~25

	QString str = "QTabBar::tab{height:%1}";
	str = str.arg(_h);
	ui.tabLeft->setStyleSheet(str);
	ui.tabRight->setStyleSheet(str);
	ui.tabTR->setStyleSheet(str);

	QMainWindow::resizeEvent(event);	
}

bool Samcon::nativeEvent(const QByteArray & eventType, void * message, long * result)
{
	
	if (eventType == "windows_generic_MSG")
	{

		PMSG msg = (PMSG)message;

		if (msg->message == WM_USER + 177)
		{
			PHBX::getIns()->isInitOver = true;
			static int LastKey1 = 0;
			int key1 =msg-> lParam & 0xff;
			int key2 = msg->lParam >> 8;
			int key3 = (msg->lParam >> 24) & 0xff;//无效
			int key4 = (msg->lParam >> 16) & 0xff;//无效
			if (LastKey1 ==0&&key1!=0) {//第一次按下
				LastKey1 = key1;
				DealHandwheel(key1, key2, 1);
			}
			else if(LastKey1 !=0){
				if (LastKey1 == key1) {//按住不放
					DealHandwheel(LastKey1, key2);
				}
				else {//松开
					DealHandwheel(LastKey1, key2, 0);
					LastKey1 = 0;
					aspeed = 0;
				}
			}
			return 1;
			//mWheel->keyPressTask(msg->wParam, msg->lParam);
		}
		else if (msg->message == WM_USER + 178)
		{
			return 0;
		}
		else if (msg->message == WM_USER + 277)
		{
			auto wp  = (short)msg->wParam;
			NcPod::getIns()->_DoButton(wp);
		//	qDebug() << "*******************************debug:277"<<"do";
		}
		else if (msg->message == WM_USER + 278) {
			int dot;
			//auto value = NcPod::getIns()->GetSetDroValu(&dot);
			//double d = (QString::number(value) + '.' + QString::number(dot)).toDouble();
			auto wp = (short)msg->wParam;
			auto lp = (double*)msg->lParam;

	
			NcPod::getIns()->_SetDRO(wp, *lp);
			NcPod::getIns()->SetFunRetur(1, 0);
		//	qDebug() << "********************************debug:278"<<" set";
		}
		else if (msg->message == WM_USER + 279) {
			auto wp = (short)msg->wParam;	
			auto value = NcPod::getIns()->_GetDRO(wp);		
			NcPod::getIns()->SetFunRetur(value,0 )  ;
		//	qDebug() << "***************************debug:279" << " get "<<value;
		}
		else if (msg->message == WM_USER + 280) {
			char wp[50] = {0};
			int  lp = (int)msg->lParam;
			NcPod::getIns()->GetGodeCm(wp, lp);
			//strcpy(wp, (char*)msg->wParam);
			QString str = wp;
			str = str.left(lp);

			NcPod::getIns()->_Code(str.toStdString().c_str());	
			NcPod::getIns()->SetFunRetur(1, 500);
		//	qDebug() << "*****************************debug:280" << " code " << str;
		}
		else if (msg->message == WM_USER + 281) {
			char wp[50] = { 0 };
			int  lp = (int)msg->lParam;
			NcPod::getIns()->GetGodeCm(wp, lp);
			
			QString str = QString::fromLocal8Bit(wp);
			str = str.left(lp);
			NcPod::getIns()->SetFunRetur(1, 500);
			ui.MLabel->setText(str);
		//	qDebug() << "*********************************************debug:281" << " str " << str;
		}
	}
	return false;
}

void Samcon::changeEvent(QEvent * event)
{
	//qDebug() << event->type();
	//if (event->type() == QEvent::WinIdChange)
	//	qDebug() << "WinIdChange";
}

void Samcon::region(const QPoint & cursorGlobalPoint)
{
	// 获取窗体在屏幕上的位置区域，tl为topleft点，rb为rightbottom点
	QRect rect = this->rect();
	QPoint tl = mapToGlobal(rect.topLeft());
	QPoint rb = mapToGlobal(rect.bottomRight());

	int x = cursorGlobalPoint.x();
	int y = cursorGlobalPoint.y();

	if (tl.x() + PADDING >= x && tl.x() <= x && tl.y() + PADDING >= y && tl.y() <= y) {
		// 左上角
		dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置鼠标形状
	}
	else if (x >= rb.x() - PADDING && x <= rb.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		// 右下角
		dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x() && y >= rb.y() - PADDING && y <= rb.y()) {
		//左下角
		dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING && y >= tl.y() && y <= tl.y() + PADDING) {
		// 右上角
		dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (x <= tl.x() + PADDING && x >= tl.x()) {
		// 左边
		dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (x <= rb.x() && x >= rb.x() - PADDING) {
		// 右边
		dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if (y >= tl.y() && y <= tl.y() + PADDING) {
		// 上边
		dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if (y <= rb.y() && y >= rb.y() - PADDING) {
		// 下边
		dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else {
		// 默认
		dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

void Samcon::StopMCode()
{
	if (isMCode) {


		isMCode = false;
		NcPod::getIns()->StopMacr(0);//停止宏代码
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message = WM_PAINT)//清除消息队列
			{
				::DispatchMessage(&msg);
			}
		}

		if (MCodeName == "6")
			ignoreToolChange(readIni.GetTool());
	}
}

void Samcon::SetRightSubWidgetFocus()
{
	QWidget* w = ui.tabRight->currentWidget();
	if (dynamic_cast<ctrlHand*>(w))
		dynamic_cast<ctrlHand*>(w)->MySetFocus();
	else if (dynamic_cast<ToolsChoice*>(w))
		dynamic_cast<ToolsChoice*>(w)->MySetFocus();
	else if (dynamic_cast<ToolSetting*>(w))
		dynamic_cast<ToolSetting*>(w)->MySetFocus();
	else if (dynamic_cast<AutoWork*>(w))
		dynamic_cast<AutoWork*>(w)->MySetFocus();
}

void Samcon::SetLeftSubWidgetFocus()
{
	QWidget* w = ui.tabLeft->currentWidget();
	if (dynamic_cast<Locus *> (w))
		dynamic_cast<Locus*>(w)->MySetFocus();
	else if (dynamic_cast<GManager*>(w))
		dynamic_cast<GManager*>(w)->MySetFocus();
	else if (dynamic_cast<DocEdit*>(w))
		dynamic_cast<DocEdit*>(w)->MySetFocus();
	else if (dynamic_cast<IOSet*>(w))
		dynamic_cast<IOSet*>(w)->MySetFocus();
	else if (dynamic_cast<SystemMsg*>(w))
		dynamic_cast<SystemMsg*>(w)->MySetFocus();
}

bool Samcon::GetRightSubWidgetFocus()
{
	QWidget* w = ui.tabRight->currentWidget();
	if (dynamic_cast<ctrlHand*>(w))
		return dynamic_cast<ctrlHand*>(w)->MyGetFocus();
	else if (dynamic_cast<ToolsChoice*>(w))
		return dynamic_cast<ToolsChoice*>(w)->MyGetFocus();
	else if (dynamic_cast<ToolSetting*>(w))
		return dynamic_cast<ToolSetting*>(w)->MyGetFocus();
	else if (dynamic_cast<AutoWork*>(w))
		return dynamic_cast<AutoWork*>(w)->MyGetFocus();
}

bool Samcon::GetLeftSubWidgetFocus()
{
	QWidget* w = ui.tabLeft->currentWidget();
	if (dynamic_cast<Locus *> (w))
		return dynamic_cast<Locus*>(w)->MyGetFocus();
	else if (dynamic_cast<GManager*>(w))
		return dynamic_cast<GManager*>(w)->MyGetFocus();
	else if (dynamic_cast<DocEdit*>(w))
		return dynamic_cast<DocEdit*>(w)->MyGetFocus();
	else if (dynamic_cast<IOSet*>(w))
		return dynamic_cast<IOSet*>(w)->MyGetFocus();
	else if (dynamic_cast<SystemMsg*>(w))
		return dynamic_cast<SystemMsg*>(w)->MyGetFocus();
}

void Samcon::showAxis()
{
	char  str[20] = {};

	sprintf(str, "%.3f", mcc->GetMachineCoordinate(0));
	ui.label_x->setText(str);
	sprintf(str, "%.3f", mcc->GetMachineCoordinate(1));
	ui.label_y->setText(str);
	sprintf(str, "%.3f", mcc->GetMachineCoordinate(2));
	ui.label_z->setText(str);
	sprintf(str, "%.3f", mcc->GetMachineCoordinate(3));
	ui.label_a->setText(str);
	sprintf(str, "%.3f", mcc->GetMachineCoordinate(4));
	ui.label_b->setText(str);
	sprintf(str, "%.3f", mcc->GetMachineCoordinate(5));
	ui.label_c->setText(str);

	static double dx = 0;
	static double dy = 0;
	static double dz = 0;
	dx = mcc->GetWorkpieceCoordinate(0);
	dy = mcc->GetWorkpieceCoordinate(1);
	dz = mcc->GetWorkpieceCoordinate(2);
	sprintf(str, "%.3f", dx);
	ui.BTX->setText(str);
	sprintf(str, "%.3f", dy);
	ui.BTY->setText(str);
	sprintf(str, "%.3f", dz);
	ui.BTZ->setText(str);
	sprintf(str, "%.3f", mcc->GetWorkpieceCoordinate(3));
	ui.BTA->setText(str);
	sprintf(str, "%.3f", mcc->GetWorkpieceCoordinate(4));
	ui.BTB->setText(str);
	sprintf(str, "%.3f", mcc->GetWorkpieceCoordinate(5));
	ui.BTC->setText(str);
	static bool bbb = 0;
	if(bbb)
		pLocus->UpdateAxis(dx, dy, dz);  //动态绘制刀路
	bbb = !bbb;

}

bool Samcon::showState()
{

	static QTime *t =NULL;
	ui.stateLabel->setText(strstateLabel);
	ui.stateLabelFlag->setText(strstateLabelFlag);
	ui.stateLabelWarn->setText(strstateLabelWarn);
	if (t == NULL) {
		t = new QTime;
		t->start();
		//strstateLabelFlag = ExternalText::ShouDong;
	}
	else {
		if (t->elapsed() < 1000) {
			//return;
		}	
		else {
			t->restart();
			strstateLabelWarn = "";
		}
	}
	
	int st = mcc->GetGmode(11).toInt();

	static  bool doStop = false;
	if (st != 3)
		doStop = false;

	if (st == 1)
	{
		strstateLabel = ExternalText::YunDong;
	}
	else if (st == 2) {
		strstateLabel = ExternalText::Mang;
	}
	else if (st == 3) {
		if (!doStop) {

			if (SammonFunc::isToolSetting || SammonFunc::isFToolSetting)
				NcPod::getIns()->StopPMov(0, 2);
			SammonFunc::SetSpeedControl_stop(isSimulation);

			strstateLabelFlag = ExternalText::Stop;
			LogManager::getIns()->appendLog(ExternalText::Stop);
			
			bMachineReturn = 0;//停止机械回0
			SammonFunc::isStartFormIdx = false;//停止指定行加工
			SammonFunc::isToolSetting = false;//停止对刀
			SammonFunc::isFToolSetting = false;
			pQStartFromIndex->showStartLineDlg2 = false;
			pTrGCode->isG81 = false;
			pTrGCode->isG82 = false;
			pTrGCode->isG73 = false;
			pTrGCode->isG85 = false;
			pTrGCode->isG86 = false;
			pTrGCode->isG89 = false;
			stopZflag = false;		
			pTrGCode->isG31 = -1;
			SammonFunc::Getins()->autoToolSetting = false;
			StopMCode();
			mcc->ClearBuffer();
			needShowStartLine = 1;
			SammonFunc::NextShow = false;
			SammonFunc::PauseShow = false;
			pIO->CloseOut5();
			doStop = true;
		}
		strstateLabel = ExternalText::XianWei;
				
	}
	else if (st == 4) {
		strstateLabel = ExternalText::KongXian;
	}
	else if (st == 5) {
		strstateLabel = ExternalText::CanShuCuoWu;
	}
	else if (st == 6) {
		strstateLabel = ExternalText::TongXinCuoWu;
	}
	else if (st == 7) {
		strstateLabel = ExternalText::DengDai;
	}
	else if (st == -1)
	{
		strstateLabel = ExternalText::MeiLianJieKa;
		return false;
	}

	if (0 == mcc->GetGmode(13).toInt()&& !isSimulation) {
		strstateLabel = TrLang::Ins()->GetText(92);//请插入加密狗
#ifndef _DEBUG
		QMessageBox::information(0, "Warning", TrLang::text(92), QMessageBox::Ok);
		close();
#endif // !_DEBUG
	}

	return true;
}


void Samcon::showInfo()
{

	QString& line =  mcc->GetCodeRunNow(mCurRow);//行号


	if (SammonFunc::isLoading&&mcc->GetWorkState()==1&&mcc->AutoRunFlag()) {		
		
		int tsize = ui.label_CurCode->width() / 15;
		ui.label_CurCode->setText(line.left(tsize)); 

		ui.label_time->setText(SammonFunc::msToDate(m_runTime.elapsed() + m_PassTime));//加工时间
		int mm = qRound((float)mCurRow / mcc->GetCodeLength() * 100);
		ui.label_process->setText(QString("%1 %").arg(mm));//完成百分比
		static int m = 0;
		if (m != mm&&mm!=0){
			m = mm;
			QDateTime tt;
			static int time_t = QDateTime::currentDateTime().toTime_t();
			int pass_t = (m_runTime.elapsed() /1000+ m_PassTime)* 100/mm;
			tt.setTime_t(time_t + pass_t);
			ui.label_startTime->setText(tt.toString("HH:mm"));
		}

	}
	static int rc = -1;
	if (mCurRow != 0 && rc != mCurRow) {
		pAutoWork->UpdataText(mCurRow);
		ui.label_row->setText(QString::number(mCurRow + pOpenFile->PageMaxRow));
		rc = mCurRow;
	}
	if (mcc->GetGmode(11).toInt() == 1 && mcc->GetActualF(0) == 0)
		ui.label_sjz1->setText(SammonFunc::GetSpeed(-1));
	else
		ui.label_sjz1->setText(QString::number(mcc->GetActualF(0)));//速度实际值
	ui.label_toolId->setText(SammonFunc::sToolName);//当前刀具号
}

void Samcon::WorkpieceReturn()
{
	static int i = 0;
	static bool step1over = false;
	static bool step2over = false;
	if (bWorkpieceReturn) {
		if (i++ <= 3)return;	
	}i = 0;
	if (bWorkpieceReturn == 1) {//XY->Z
		if ( mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4&& !step1over&&!step2over) {
			QString str = "";
			str = str + "G1G90X" + "0" + "Y" + "0" + "F" + SammonFunc::GetSpeed(1);
			MccTools::SendMDI(str);
			step1over = true;
			return;
		}
		if ( mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4&& step1over&&!step2over)
		{
			QString str = "";
			str = str + "G90Z" + readIni.GetSafetyHeight() + "F" + SammonFunc::GetSpeed(0);
			MccTools::SendMDI(str);	
			step2over = true;
			return;
		}
		if (step1over&&step2over) {
			bWorkpieceReturn = 0;
			return;
		}

	}
	else if (bWorkpieceReturn == 2) {//Z->XY
		if ( mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !step1over && !step2over) {
			QString str = "";
			str = str + "G1G90Z" + readIni.GetSafetyHeight() + "F" + SammonFunc::GetSpeed(0);
			MccTools::SendMDI(str);
			step1over = true;
			return;
		}
		 if ( mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && step1over && !step2over)
		{
			QString str = "";
			str = str + "G90X" + "0" + "Y" + "0" + "F" + SammonFunc::GetSpeed(1);
			MccTools::SendMDI(str);
			step2over = true;
			return;
		}
		if (step1over&&step2over) {
			bWorkpieceReturn = 0;
			return;
		}
	}
	else {
		i = 0;
		step1over = false;
		step2over = false;
	}

}

void Samcon::sendStopZMDI()
{
	static int i = 0;
	static bool send = false;
	if (stopZflag) {
		if (readIni.GetStopZParam().toInt()==0) {
			stopZflag = false;
			return;
		}
		if (fixFeedrateMultiple || isSpeedNeedSud)return;
		if (i++ < 3)return;
		i = 0;

		if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4&& !send) {
			QString str = "";
			if (readIni.GetStopZParam().toInt() == 2) {
				float a = readIni.GetStopZValue().toFloat() + mcc->GetWorkpieceCoordinate(2);
				str = str + "G1G90Z" + QString::number(a) + "F" + SammonFunc::GetSpeed(0);
			}
			else {
				str = str + "G1G90Z" + readIni.GetSafetyHeight() + "F" + SammonFunc::GetSpeed(0);
			}
			MccTools::SendMDI(str);
			send = true;
			return;
			
		}
		if (send&&mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {
			stopZflag = false;
		}
	}
	else {
		i = 0;
		send = false;
	}
}

void Samcon::CheckOffsetChange()
{
	static int i = 0;
	if (!SammonFunc::LastCoordinateInit) {
		return;
	}
	if (i++ <= 20)return;
	i = 0;
	QString str = mcc->GetGmode(5);
	static int index = -1;
	if (str == "G54")
		index = 0;
	else 	if (str == "G55")
		index = 1;
	else 	if (str == "G56")
		index = 2;
	else 	if (str == "G57")
		index = 3;
	else 	if (str == "G58")
		index = 4;
	else 	if (str == "G59")
		index = 5;


	static bool isInitOffSet = false;//软件错误退出时 坐标回乱，、、这样保证 偏执正确
	if (!isInitOffSet) {
		pDlgWorkpieceOffset->SetCurrentIndex(readIni.GetWorkpieceOffset());
		isInitOffSet = true;
	}


	if (SammonFunc::offsetSucces) {	
		QString  _str;
		int idx = readIni.GetWorkpieceOffset();
		if (idx == 0)
			_str = "G54";
		else if (idx == 1)
			_str = "G55";
		else if (idx ==2)
			_str = "G56";
		else if (idx == 3)
			_str = "G57";
		else if (idx == 4)
			_str = "G58";
		else if (idx == 5)
			_str = "G59";
		if (index != idx) {
			MccTools::SendMDI(_str);
			return;
		}
		else {
			SammonFunc::offsetSucces = false;
		}
	}


	if (index != readIni.GetWorkpieceOffset())//代码中 修改偏执后 ，，更新偏执
		pDlgWorkpieceOffset->SetCurrentIndex(index);
}

void Samcon::SpindleRotate()
{

	bool isOpne = mcc->GetSpindleInformation(0);
	if (isOpne) {
		ui.btzzkg->setText(ExternalText::ZhuZhouKai);
		double Muitiple = ui.ScrollBar_ZZKZ->value() / 100.0f;
		double value = mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1)*Muitiple;	
		ui.label_sjz2->setText(QString::number((int)value));//zhu zhou实际值	
	}
	else {
		ui.btzzkg->setText(ExternalText::ZhuZhouGuan);
		ui.label_sjz2->setText("0");//zhu zhou实际值

	}
}

void Samcon::DealHandwheel(int key1, int key2, bool isHandwheelPressed)
{
	if (key1 == 0)
		return;
	if (key1 >= 11 && key1 <= 28) {
		pCtrlHand->DealHandwheel(key1, key2, isHandwheelPressed);

	}
	else if (key1 >= 1 && key1 <= 10) {
		if (isHandwheelPressed) {

		}
		else {
			if (key1 == 1) {
				AcStop->triggered();
			}
			else if (key1 == 2) {
				if(ui.ToolPause->isEnabled())
					AcPause->triggered();
			}
			else if (key1 == 3) {
				if (ui.ToolNext->isEnabled())
					AcNext->triggered();
			}
			else if (key1 == 4) {
				if (ui.ToolRun->isEnabled())
					AcPlay->triggered();
			}
			else if (key1 == 5) {
				ui.btzzkg->clicked();
			}
			else if (key1 == 6) {
				
				ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() + 1);
			}
			else if (key1 == 7) {
				ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() - 1);
			}
			else if (key1 == 8) {
				ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() + 1);
			}
			else if (key1 == 9) {
				ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() - 1);
			}
			else if (key1 == 10) {
				stopZflag = true;
			}

		}
	}
}

void Samcon::DealHandwheel(int key1, int key2)
{
	if (key1 == 6) {
		aspeed++;
		ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() + aspeed);
	}
	if (key1 == 7) {
		aspeed++;
		ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() - aspeed);
	}
	else if (key1 == 8) {
		aspeed++;
		ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() + aspeed);
	}
	else if (key1 == 9) {
		aspeed++;
		ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() - aspeed);
	}
}

void Samcon::GetYiTiJiKey()
{
	static int LastKey2 = 0;
	static int LastKey1 = 0;
	int key = 0;

	NcPod::getIns()->ReadPadKe(0, &key);
	
	if (key == 0) {
		LastKey2 = 0;
		LastKey1 = 0;
		return;
	}
	char key1, key2, key3, key4;
	key1 = key & 0xff;
	key2 = key >> 8;
	key3 = key >> 16;
	key4 = key >> 24;

	//LogManager::getIns()->appendLog(QString("key1: %1").arg((int)key1));
	//LogManager::getIns()->appendLog(QString("key1: %1").arg((int)key1));

	DealYiTiJiKey3_4(key3, key4);

	if (key1 == 28) {//按下Fn
		if (LastKey2 == 0 && key2 != 0) {//第一次按下
			LastKey2 = key2;			
			DealYiTiJiKey(key1, key2, true);
		}
		else if (LastKey2 != 0) {
			if (LastKey2 == key2) {//按住不放 

			}
			else {//松开key2   即 (LastKey2!=0&&key2==0)
				DealYiTiJiKey(key1, LastKey2, 0);
				LastKey2 = 0;
			}
		}
	}
	else {//不按Fn
		if (LastKey1 == 0) {//第一次按下
			LastKey1 = key1;
			DealYiTiJiKey1(key1, key2, true);
		}
		else if (LastKey1!=0) {
			if (LastKey1 == key1) {//按住不放 
				DealYiTiJiKey(key1, key2);
			}
			else {//松开key1   即 (LastKey1!=0&&key1==0)
				DealYiTiJiKey1(LastKey1, key2, false);
				LastKey1 = 0;
				YTJspeed = 0;
			}
		}
	}
}

void Samcon::MySpeedCtrlSud()
{
	if (!isSpeedNeedSud)
		return;
	isSpeedNeedPlus = false;

	int value = mcc->GetMultiple(0);
	//qDebug() << value;
	if(value>2)
		mcc->SetFeedrateMultiple(value/2);
	else {
		if (SammonFunc::IsPause) {
			mcc->SetAutoRunFlag(false);
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;		
		}
		else {
			mcc->SetAutoRunFlag(false);
		}
		fixFeedrateMultiple = 1;
		if(SammonFunc::StartLine==-1)
			SammonFunc::StartLine = NcPod::getIns()->Get_CodeLin(0)-SammonFunc::Getins()->IndexRrcod*BIGSIZE;
		isSpeedNeedSud = false;
	}
}

void Samcon::MySpeedCtrlPlus()
{
	if (isSpeedNeedPlus) {
		if (SammonFunc::isNeedOpenSpindleRotat)
			return;
		isSpeedNeedSud = false;
		int value = mcc->GetMultiple(0);
	//	qDebug() << value;
		if (mcc->GetMultiple(0) == ui.ScrollBar_GJSD->value()) {
			mcc->SetFeedrateMultiple(0);
			return;
		}
		if (value == 0) {
			MccTools::run();
			PushRun = true;
		}
		if(value+5<ui.ScrollBar_GJSD->value())
			mcc->SetFeedrateMultiple(value + 5);
		else {
			mcc->SetFeedrateMultiple(ui.ScrollBar_GJSD->value());
			isSpeedNeedPlus = false;
		}
	}
}

void Samcon::DealYiTiJiKey(int key1, int key2, bool isHandwheelPressed)
{
	if (isHandwheelPressed) {

	}
	else {
		if (key2 == 4) {
			ui.BTX->clicked();
		}
		else if (key2 == 5) {
			if (!ui.BTA->isHidden())
				ui.BTA->clicked();
		}
		else if (key2 == 11) {
			ui.BTY->clicked();
		}
		else if (key2 == 12) {
			if (!ui.BTB->isHidden())
				ui.BTB->clicked();
		}
		else if (key2 == 18) {
			ui.BTZ->clicked();
		}
		else if (key2 == 19) {
			if (!ui.BTC->isHidden())
				ui.BTC->clicked();
		}
		else if (key2 == 23) {
			if (AcReturn->isEnabled())
				AcReturn->triggered();
		}
		else if (key2 == 25) {
			pResetAxis->show();
		}
		else if (key2 == 26) {
			stopZflag = true;
		}
	}
}

void Samcon::DealYiTiJiKey1(int key1, int key2, bool isHandwheelPressed)
{
	if (isHandwheelPressed) {
		
	}
	else {
		if (key1 == 1) {
			AcStop->triggered();
		}
		else if (key1 == 8) {
			if (ui.ToolPause->isEnabled())
				AcPause->triggered();
		}
		else if (key1 == 15) {
			if (ui.ToolNext->isEnabled())
				AcNext->triggered();
		}
		else if (key1 == 22) {
			if (ui.ToolRun->isEnabled())
				AcPlay->triggered();
		}
		else if (key1 == 2) {
			if (!SammonFunc::isLoading)
				return;
			if (!SammonFunc::CanDoit())return;
			pAutoWork->UpdataText(1);
			int i = 1;
			mcc->SetStartline(i);
			mcc->ClearBuffer();
			mcc->SendAutoText(QString(""));
			SammonFunc::StartLine = -1;
			SammonFunc::RunShow = true;
			SammonFunc::PauseShow = 0;
			SammonFunc::NextShow = 0;
		}
		else if (key1 == 9) {

		}
		else if (key1 == 16) {
			ui.btzzkg->clicked();
		}

		else if (key1 == 3) {
			ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() + 1);
		}
		else if (key1 == 10) {
			ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() - 1);
		}
		else if (key1 == 17) {
			ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() + 1);
		}
		else if (key1 == 24) {
			ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() - 1);
		}
		else if (key1 == 6) {

		}
		else if (key1 == 13) {

		}
		else if (key1 == 20) {

		}
		else if (key1 == 27) {

		}
		else if (key1 == 7) {
			//if (!GetLeftSubWidgetFocus()) {
			//	SetLeftSubWidgetFocus();
			//}
			//else {
			//	int idx = ui.tabLeft->currentIndex();
			//	int count = ui.tabLeft->count();
			//	if (idx < count - 1 && idx >= 0) {
			//		ui.tabLeft->setCurrentIndex(idx + 1);
			//	}
			//	else if (idx == count - 1) {
			//		ui.tabLeft->setCurrentIndex(0);
			//	}
			//}
		}
		else if (key1 == 14) {
			//if (!GetRightSubWidgetFocus()) {
			//	SetRightSubWidgetFocus();
			//}
			//else {
			//	int idx = ui.tabRight->currentIndex();
			//	int count = ui.tabRight->count();
			//	if (idx < count - 1 && idx >= 0) {
			//		ui.tabRight->setCurrentIndex(idx + 1);	
			//	}
			//	else if (idx == count - 1) {		
			//		ui.tabRight->setCurrentIndex(0);
			//	}
			//}
		}
		else if (key1 == 21) {

		}
	}
}

void Samcon::DealYiTiJiKey(int key1, int key2)
{
	if (key1 == 3) {
		YTJspeed++;
		ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() + YTJspeed);
	}
	else if (key1 == 10) {
		YTJspeed++;
		ui.ScrollBar_GJSD->setValue(ui.ScrollBar_GJSD->value() - YTJspeed);
	}
	else if (key1 == 17) {
		YTJspeed++;
		ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() + YTJspeed);
	}
	else if (key1 == 24) {
		YTJspeed++;
		ui.ScrollBar_ZZKZ->setValue(ui.ScrollBar_ZZKZ->value() - YTJspeed);
	}
}

void Samcon::DealYiTiJiKey3_4(int key3, int key4)
{
	//key4 left value 6 17 18 19 20 21 22
	//key3 right value 13 14 15 16 26 27 28
	static int LastKey3 = 0;
	static int LastKey4 = 0;
	if (key3 != LastKey3) {
		LastKey3 = key3;
		switch (LastKey3)
		{
		case 13:
			ui.tabRight->setCurrentIndex(0);
			break;
		case 14:
			ui.tabRight->setCurrentIndex(1);
			break;
		case 15:
			ui.tabRight->setCurrentIndex(2);
			break;
		case 16:
			ui.tabRight->setCurrentIndex(3);
			break;
		case 26:
			break;
		case 27:
			break;
		case 28:
			break;
		}
	}
	if (key4 != LastKey4) {
		LastKey4 = key4;
		switch (LastKey4)
		{
		case 6:
			ui.tabLeft->setCurrentIndex(0);
			break;
		case 17:
			ui.tabLeft->setCurrentIndex(1);
			break;
		case 18:
			ui.tabLeft->setCurrentIndex(2);
			break;
		case 19:
			ui.tabLeft->setCurrentIndex(3);
			break;
		case 20:
			ui.tabLeft->setCurrentIndex(4);
			break;
		case 21:
			break;
		case 22:
			break;
		}
	}
}

void Samcon::DoMCode()
{
	static int i = 0;
	static bool RunMCode = false;
	static bool RunOver = true;
	if (isMCode) {

		if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !RunMCode) {
			QString workDir = QCoreApplication::applicationDirPath();
			if (VersionType == 2) {
				workDir += "/Macro2/m%1.m1s";
			}
			else if (VersionType == 4) {
				workDir += "/Macro4/m%1.m1s";
			}
			else if (VersionType == 6) {
				workDir += "/Macro6/m%1.m1s";
			}
			else {
				workDir += "/Macro/m%1.m1s";
			}
			
			QString fileName = workDir.arg(MCodeName);
			QFileInfo info(fileName);
			if (!info.isFile()) {
				LogManager::getIns()->appendLog(TrLang::Ins()->GetText(94) + fileName);//宏代码不存在：
				isMCode = false;
				if (!MCodeFromMDI) {
					needShowStartLine = true;
					SammonFunc::NeedRunNext = true;
				}
				return;
			}
			NcPod::getIns()->RunMacr(0, fileName.toStdString().c_str());
			//NcPod::getIns()->SetFunRetur(1, 500);
			RunMCode = true;
			RunOver = false;
			LogManager::getIns()->appendLog(TrLang::Ins()->GetText(95) + MCodeName);//执行宏代码：M
			return;
		}
		if (i++ < 3) {
			return;
		}
		i = 0;

		if (!RunMCode || bMachineReturn != 0 || pTrGCode->isG31 != -1) {
			NcPod::getIns()->SetFunRetur(1, 500);
			return;
		}//一些指令 可能分成好几步，，中间会有idle状态。必须等该指令完全执行完 再 run next

		if (NcPod::getIns()->MacroIsRunin(0)) {//宏代码文件未执行完
			if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4) {//执行下一条
				//NcPod::getIns()->SetFunRetur(1, 0);
				//LogManager::getIns()->appendLog("run Next");
			}
			else {//这条未执行完
				NcPod::getIns()->SetFunRetur(1, 500);
			}
		}
		else {
			RunOver = true;
			LogManager::getIns()->appendLog(TrLang::Ins()->GetText(96) + MCodeName);//宏代码运行结束
		}
		if (RunOver) {
			RunMCode = false;
			RunOver = false;
			isMCode = false;

			if (SammonFunc::Getins()->readBit(SammonFunc::Getins()->needRunNext, 1)) {
				SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 0);
				if (readIni.GetToolChangeOpt().toInt() == 1&& isTCodeFlag_1) {
					if (mCurRow == pAutoWork->TableRowList.size()) {
						goto FLAG1; //换刀在文本最后一行,  程序自己加了一行 M30  直接跳转M30
					}

					needShowStartLine = true;
					SammonFunc::NeedRunNext = true;
					isTCodeFlag_1 = false;
					SammonFunc::RunShow = 0;
					SammonFunc::PauseShow = 0;
					SammonFunc::NextShow = 1;
					return;
				}
				else if (readIni.GetToolChangeOpt().toInt() == 2 && isTCodeFlag_1) {
					if (mCurRow == pAutoWork->TableRowList.size()) {
						goto FLAG1; //换刀在文本最后一行,  程序自己加了一行 M30  直接跳转M30
					}
					mcc->ClearBuffer();
					MccTools::setStart(mCurRow + 1);
					SammonFunc::isNeedOpenSpindleRotat = true;
					isSpeedNeedPlus = true;
					return;
				}
				FLAG1:
				MccTools::RunStartLine(mCurRow + 1);
			}
		}
	}
	else {
		i = 0;
		isTCodeFlag_1 = false;
		RunMCode = false;
		if (RunOver == false) {
			RunOver = true;
		}
	}
}

bool RunM47 = false;
void Samcon::DealTrGCode()
{
	if (SammonFunc::ReplaceCodeMap.keys().contains(pOpenFile->PageMaxRow + mCurRow)) {
		LogManager::getIns()->debugLog("In MCode");
		QString& curline = SammonFunc::ReplaceCodeMap[pOpenFile->PageMaxRow + mCurRow];
		MCodeFromMDI = false;
		if (curline.contains("M") || curline.contains("m")) {
			QString MCode = SammonFunc::GetNumber(curline, 'M', 'm');
			if (MCode.toInt() >= 100) {
				isMCode = true;
				MCodeName = MCode;
				SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 1);
				return;
			}
			else if (MCode.toInt() == 47) {

				if (pOpenFile->PageNum != 0) {
					pOpenFile->LoadFomeStartLine(0);
				}
				pAutoWork->resetlh();
				mcc->ClearBuffer();
				int temprow = 1;
				mcc->SetStartline(temprow);
				RunM47 = true;
				mFinish++;
				LogManager::getIns()->appendLog(TrLang::Ins()->GetText(93));//自动加工完成
			

				bool InMap = SammonFunc::ReplaceCodeMap.keys().contains(pOpenFile->PageMaxRow + 1) || SammonFunc::DrillHoleMap.keys().contains(pOpenFile->PageMaxRow + 1);
				if (InMap) {		
					//第一行  手动换刀 Ncpod 返回的 行号 是错的
				}
				else {			
					isSpeedNeedPlus = true;//特殊处理 第一行就是宏代码  第一行 就是宏代码 ，宏代码控制中 会自行Run
				}
			}
		}
		if (curline.contains("G") || curline.contains("g")) {
			QString GCode = SammonFunc::GetNumber(curline, 'G', 'g');
			if (GCode.toInt() == 31) {
				QString Code = SammonFunc::GetNumber(curline, 'X', 'x');
				if (!Code.isEmpty()) {
					pTrGCode->isG31 = 0;
					pTrGCode->G31Coord = Code;
				}
				Code = SammonFunc::GetNumber(curline, 'Y', 'y');
				if (!Code.isEmpty()) {
					pTrGCode->isG31 = 1;
					pTrGCode->G31Coord = Code;
				}
				Code = SammonFunc::GetNumber(curline, 'Z', 'z');
				if (!Code.isEmpty()) {
					pTrGCode->isG31 = 2;
					pTrGCode->G31Coord = Code;
				}
				Code = SammonFunc::GetNumber(curline, 'F', 'f');
				if (!Code.isEmpty()) {
					pTrGCode->G31FSpeed = Code;
				}
				if (pTrGCode->isG31 != -1) {
					SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 0, 1);
					return;
				}

			}
		}
		if (curline.contains("T") || curline.contains("t")) {
			QString newT = SammonFunc::GetNumber(curline, 'T', 't');

			if (VersionType == 1) {

				ignoreToolChange(newT.toInt());
				if (readIni.GetToolChangeOpt().toInt() == 0) {
					int row = mCurRow + 1;
					mcc->SetStartline(row);
					isSpeedNeedPlus = true;
					return;
				}
				else if (readIni.GetToolChangeOpt().toInt() == 1) {
					needShowStartLine = true;
					SammonFunc::NeedRunNext = true;
					stopSpindleRotate = mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1);//换刀时  关闭主轴。保存当前主轴速度，换完后 需要恢复
					mcc->SetSpindleRotate(0);
					return;//行号加1
				}

			}
			else if (VersionType == 2) {
				if (newT.toInt() == readIni.GetTool() || newT.toInt() < 1 || newT.toInt() > readIni.GetToolCount().toInt()) {
					int row = mCurRow + 1;	
					mcc->SetStartline(row);	
					isSpeedNeedPlus = true;
					return;
				}
				if (readIni.GetToolChangeOpt().toInt() == 0) {
					ignoreToolChange(newT.toInt());
					int row = mCurRow + 1;
					mcc->SetStartline(row);
					isSpeedNeedPlus = true;
					return;
				}
				stopSpindleRotate = mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1);//换刀时  关闭主轴。保存当前主轴速度，换完后 需要恢复
				mcc->SetSpindleRotate(0);
				
				isTCodeFlag_1 = true;
				isMCode = true;

				if (readIni.GetToolIsQiGang()) {
					MCodeName = "6q";
				}
				else {
					MCodeName = "6p";
				}

				NcPod::getIns()->newT = newT.toInt();
				SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 1);
				return;
			}
			else if (VersionType == 4) {
				if (newT.toInt() == 5 || newT.toInt() == 6) {

				}
				else if (newT.toInt() == readIni.GetTool() || newT.toInt() < 1 || newT.toInt() > readIni.GetToolCount().toInt()) {
					int row = mCurRow + 1;
					mcc->SetStartline(row);
					isSpeedNeedPlus = true;
					return;
				}

				if (readIni.GetToolChangeOpt().toInt() == 0) {
					ignoreToolChange(newT.toInt());
					int row = mCurRow + 1;
					mcc->SetStartline(row);
					isSpeedNeedPlus = true;
					return;
				}
				stopSpindleRotate = mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1);//换刀时  关闭主轴。保存当前主轴速度，换完后 需要恢复
				mcc->SetSpindleRotate(0);
	
				isTCodeFlag_1 = true;
				isMCode = true;
				MCodeName = "6";
				NcPod::getIns()->newT = newT.toInt();
				SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 1, 1);
				return;
			}
		}
	}
	else if (SammonFunc::DrillHoleMap.keys().contains(pOpenFile->PageMaxRow + mCurRow)) {
		pTrGCode->mDrillHoleData = SammonFunc::DrillHoleMap[pOpenFile->PageMaxRow + mCurRow];
		int Type = pTrGCode->mDrillHoleData.Type;
		switch (Type)
		{
		case 81:
			pTrGCode->isG81 = true;
			break;
		case 82:
			pTrGCode->isG82 = true;
			break;
		case 73:
		case 83:
			pTrGCode->isG73 = true;
			break;
		case 85:
			pTrGCode->isG85 = true;
			break;
		case 86:
			pTrGCode->isG86 = true;
			break;
		case 89:
			pTrGCode->isG89 = true;
			break;
		}
	}
}

void Samcon::CheckAuto()
{
	static int TimeCtrl = 0;
	if (isSpeedNeedPlus) {
		TimeCtrl = 10;
	}
	if (TimeCtrl) {
		TimeCtrl--;
		return;
	}
	ui.btclearcount->setText(QString::number(mFinish));
	ui.ToolRun->setEnabled(SammonFunc::RunShow);
	ui.ToolPause->setEnabled(SammonFunc::PauseShow);
	ui.ToolNext->setEnabled(SammonFunc::NextShow);
	ui.ToolRestart->setEnabled(SammonFunc::isLoading);
	static bool YunXinGuo = false;
	static int lastRow = -1;
	if (!SammonFunc::isLoading) {//未装载文件
		lastRow = -1;
		SammonFunc::RunShow = SammonFunc::NextShow = SammonFunc::PauseShow = 0;
		return;
	}

	static int OnceFlag = -1; //控制每个逻辑 只进入一次
	if (MccTools::isIdle() && MccTools::workState() == 1) {//自动加工中
		SammonFunc::RunShow = 0;
		SammonFunc::PauseShow = 1;
		SammonFunc::NextShow = 0;
		YunXinGuo = true;
		OnceFlag = -1;
		if (mCurRow != 1) {
			PushRun = false;
		}
		return;
	}

	///////////////////y以下代码 处理 自动加工中 停下的情况
	//  1  加工完成
	// 2. 遇到M00
	// 3. 遇到M00 执行宏
	// 4。 M00M789
	//暂停 停止
	QString& line = mcc->GetCodeRunNow(mCurRow);//行号
	if (line == "M00 M789") {
		pOpenFile->LoadNext();
		MccTools::RunStartLine();
		return;
	}
	

	bool InMap = SammonFunc::ReplaceCodeMap.keys().contains(pOpenFile->PageMaxRow + mCurRow) || SammonFunc::DrillHoleMap.keys().contains(pOpenFile->PageMaxRow + mCurRow);
	if (strstateLabelFlag == ExternalText::ZiDong) {

		if ((InMap&&mCurRow != 1) || (InMap&&mCurRow == 1 && PushRun)|| (mCurRow == 1&&InMap&&RunM47 )) {//宏代码 或其他 复杂指令   M30 后 会 回到 第一行 双层判断 保证 不再次执行M代码
			if (RunM47) {
				RunM47 = false;
				OnceFlag = -1;
			}
			if (OnceFlag == 0) {
				if (!isMCode) {//这个if 分支 主要是解决  手动换刀完成，，next 为灰色
					SammonFunc::PauseShow = 0;
					SammonFunc::NextShow = 1;
					
				}
				OnceFlag = 0;
				return;
			}
			OnceFlag = 0;
			SammonFunc::RunShow = 0;
			SammonFunc::PauseShow = 1;
			SammonFunc::NextShow = 0;
			DealTrGCode();
			TimeCtrl = 10;//此处 加定时器时间限制，因为 如果Map里面有 M47  运行 M47时 会 回到第一行，，可能会进入 加工完成条件。。
		}
		else {//  加工完成，或其他原因 停了
			if (mCurRow == 1) {
			
				if (YunXinGuo) {//加工完成  

					if (OnceFlag == 1)return;
					OnceFlag = 1;
					mFinish++;
					LogManager::getIns()->appendLog(TrLang::Ins()->GetText(93));//自动加工完成
					if (readIni.GetIsCloseSpindle())
						mcc->SetSpindleRotate(0);
				
					pMultifileTask->cellFInish();
					if (pMultifileTask->GetMultifileTaskAutoWork()) {
						if (!pMultifileTask->CheckFinish())
							pMultifileTask->RunMultifileTask();
					}
					SammonFunc::RunShow = 1;
					SammonFunc::PauseShow = 0;
					SammonFunc::NextShow = 0;
					YunXinGuo = false;
					mcc->SetAutoRunFlag(false);
				}
				else {//刚装载玩文件
					if (OnceFlag == 2)return;
					OnceFlag = 2;
					SammonFunc::RunShow = 1;
					SammonFunc::PauseShow = 0;
					SammonFunc::NextShow = 0;
					mcc->SetAutoRunFlag(false);
				}
			}
			else {

				SammonFunc::RunShow = 0;
				SammonFunc::PauseShow = 0;
				SammonFunc::NextShow = 1;
			}

		}
	}
	else {
		YunXinGuo = false;
		SammonFunc::PauseShow = 0;
		if(!SammonFunc::RunShow)
			SammonFunc::NextShow = 1;
	}
	lastRow = mCurRow;

}


