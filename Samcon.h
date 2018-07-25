#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Samcon.h"
#include "QAction"
#include "qtimer.h"
#include"qtime"
#include <QTranslator>
#include "DataDefine.h"
#include"QPainter"
#include<QtMath>
#include"QMouseEvent"
#include "QProcess"
////////////////////////////////////////////
/////主窗口
///////////////////////////////////////////
#define PADDING 2
enum Direction { UP = 0, DOWN = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
class s_OpenFile;
class AutoWork;
class Locus;
class ResetAxis;
class IOSet;
class SystemMsg;
class ctrlHand;
class DocEdit;
class DlgSetParameter;
class DlgSetAxisSpeed;
class DlgSetSpeedAuto;
class ToolSetting;
class QStartFromIndex;
class GManager;
class DlgWorkpieceOffset;
class ToolsChoice;
class TrGCode;
class MultifileTask;
class DlgRegSoft;
class DlgMachToInternalIncr;
class QuicklySettings;
class Samcon : public QMainWindow
{
	Q_OBJECT

public:
	Samcon(QWidget *parent = Q_NULLPTR);
	~Samcon();
	void ResetLanguage();
	void LoadStyleSheet(QString str = "");
	void SaveLastCoordinate();
	bool IsMDIRuningInItmer();
	QString getFileName();

	IOSet* GetIO() { return pIO; }
	void VersionConversion(bool is6Axis, bool isYTJ = false);

	ctrlHand* getCtrlHand() { return pCtrlHand; }
	void ncpodStart() {	if(ui.ToolRun->isEnabled())ui.ToolRun->click(); }
	void ncpodPause() { if (ui.ToolPause->isEnabled()) ui.ToolPause->click(); }
	void ncpodRewind();
	void ncpodStop() { if (ui.ToolStop->isEnabled())ui.ToolStop->click(); }
	void ncpodReset() { if (ui.ToolReset->isEnabled()) ui.ToolReset->click(); }
	ResetAxis* getResetAxis() { return pResetAxis; }
	void ncpodSpindleCW() {
		ui.btzzkg->click();
	}
	double ncpodSindleoverride();
	double ncpodFeedrateoverride() {
		return ui.label_sjz1->text().toDouble();
	}
	double ncpodFeedrate() {
		return ui.BtSetSpeed->text().toDouble();	
	}
	void ncpodSet818(double GJspeed);
	void setWorkcoodr(int axis, double value);
	void SetFeedrate(int value) {
		ui.ScrollBar_GJSD->setValue(value);
	}
	void SetSpindle(int value) {
		ui.ScrollBar_ZZKZ->setValue(value);
	}

	AutoWork* getAutoWork() { return pAutoWork; }
	s_OpenFile* getOpenFile() { return pOpenFile; }

	void ignoreToolChange(int tt);
	bool isNeedShowStartLineDlg() { return needShowStartLine; }
	QStartFromIndex* GetStartLineDlg();
	
protected:
	QPoint m_Press, m_Move;
	bool leftBtnClk = false;
	bool mDragTitle = false;
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
	void closeEvent(QCloseEvent *event);
	void resizeEvent(QResizeEvent *event);
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	void changeEvent(QEvent *);
private:

	bool isLeftPressDown;  // 判断左键是否按下
	QPoint dragPosition;   // 窗口移动拖动时需要记住的点 
	Direction dir;        // 窗口大小改变时，记录改变方向
	void region(const QPoint &cursorGlobalPoint);
	void StopMCode();
	void SetRightSubWidgetFocus();
	void SetLeftSubWidgetFocus();
	bool GetRightSubWidgetFocus();
	bool GetLeftSubWidgetFocus();
	void OpenFile();

	void InitTimer();
	void Init();
	void InitOther();
	void InitMenu();
	void InitToolBar();
	void InitGroup1();
	void InitGroup2();
	void InitGroup3();
	void InitGroup4();
	
	void InitTabLeft();
	void InitTabRight();
	bool SetLastCoordinate();
	void showAxis();
	bool showState();
	void showInfo();
	void UpdatePlayToolsEnabled();
	void WorkpieceReturn();

	bool RunNext();//大文件装载下一段
	void sendStopZMDI();//暂停时Z抬刀

	void CheckOffsetChange();//偏执改变

	void SpindleRotate();//主轴
	void DealHandwheel(int key1,int key2,bool isHandwheelPressed);//手轮按键
	void DealHandwheel(int key1, int key2);//手轮按键,按住不放
	void DealYiTiJiKey(int key1, int key2, bool isHandwheelPressed);//处理一体机  (同时按住两个键,Fn(key1)+Key2)
	void DealYiTiJiKey1(int, int, bool isHandwheelPressed);//处理一体机 Key1
	void DealYiTiJiKey(int,int);//处理一体机 按键 按住不放  Fn
	void DealYiTiJiKey3_4(int, int);//处理一体机 按键 按住不放  Fn
	void GetYiTiJiKey();//获取按键
	void MySpeedCtrlSud();//暂停时 给个减速
	void MySpeedCtrlPlus();
	void DealTrGCode();
	void FixFeedrateMultiple(); //减速后恢复进给
	bool OpenSpindleRotat();//断点续传 打开主轴 延时
	void DoMCode();
	void RunMulitifile() {
		if (!bRunMultifile)return;
		static int i = 0;
		if (i++ < 20)
			return;
		i = 0;
		AcPlay->trigger();
		bRunMultifile = false;
	}
	void CheckAuto();

private:

	QProcess *myProcess = 0;

	QTimer			m_timer; //定时器
	QTime           m_runTime; //加工开始时间
	
	int				m_PassTime=0;//已加工时间
	int			mFinish = 0;//已加工 工件数
	
	bool			stopZflag =false;//停止时 Z 抬刀标志
	
	Locus*			pLocus;
	IOSet*			pIO;
	SystemMsg*		pSystemMsg;
	ctrlHand*		pCtrlHand;
	DocEdit*		pDocEdit;
	DlgSetParameter* pDlgSetParameter;
	DlgSetAxisSpeed* pDlgSetAxisSpeed;
	DlgSetSpeedAuto*	pDlgSetSpeedAuto;
	ResetAxis*		pResetAxis;
	s_OpenFile*		pOpenFile;
	AutoWork*		pAutoWork;
	ToolSetting*	pToolSetting;
	QStartFromIndex*	pQStartFromIndex;
	ToolsChoice*		pToolsChoice;
	MultifileTask*		pMultifileTask;
	GManager*		pGManager;
	DlgRegSoft*		pDlgRegSoft;
	DlgMachToInternalIncr*           pDlgMachToInternalIncr;
	QuicklySettings* pQuicklySettings;
	//QAction*		pOpenFileAc;
	QMenu* menuAuto;
	QMenu* menuHM;
	QMenu* menuParam;
	QMenu* menuWnd;
	QMenu* menuSpeed;
	QMenu* menuAasist;
	QMenu *AcLangMenu;

	QAction*  AcResetAxis;
	QAction *AcWpOffset;
	QAction *AcMultifileTask;
	QAction *Acmaichongdangliang;
	QAction*  AcLoadG;
	QMenu* RecentG;
	QAction*  AcStart;
	QAction* AcRunDraw;
	QAction* AcDxf;
	QAction * AcDlgSetParameter;
	QAction * settings;
	QAction * AcHelp;
	QAction*		AcPause;
	QAction*		AcReset;
	QAction*		AcRestart;
	QAction*		AcReturn;//回工件原点



	int aspeed = 0;//手轮 Feed+ -，Spindle+ -  按住不放速度调节；
	int YTJspeed = 0;//一体机 Feed+ -，Spindle+ -  按住不放速度调节；
	bool is6Aixs = false;
	bool isFull = false;
	bool isSpeedNeedSud = false;
	bool isSpeedNeedPlus = false;
	bool fixFeedrateMultiple = false;


	bool needShowStartLine = false;
	int RunFlagTime = 0;//更新状态信息 时间间隔。。。
	bool bRunMultifile = false;
	bool RunOverFlag = false;
public:
	Ui::SamconClass ui;
	QAction*		AcStop;	
	QAction*		AcPlay;
	QAction*		AcNext;
	DlgWorkpieceOffset* pDlgWorkpieceOffset;
	QString			strstateLabel;
	QString			strstateLabelFlag;
	QString			strstateLabelWarn;
	int	mCurRow = -1;//当前行号
	int	stopSpindleRotate = 0;//停止时 主轴速度
	int homeLmtFlag = -1;
	bool isMCode = false;
	bool isTCodeFlag_1 = false;
	QString MCodeName = "";
	bool MCodeFromMDI = false;

	TrGCode* pTrGCode;
	int BSize = 5;//边框尺寸 和margin有关
};
