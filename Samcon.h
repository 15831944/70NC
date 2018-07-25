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
/////������
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

	bool isLeftPressDown;  // �ж�����Ƿ���
	QPoint dragPosition;   // �����ƶ��϶�ʱ��Ҫ��ס�ĵ� 
	Direction dir;        // ���ڴ�С�ı�ʱ����¼�ı䷽��
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

	bool RunNext();//���ļ�װ����һ��
	void sendStopZMDI();//��ͣʱZ̧��

	void CheckOffsetChange();//ƫִ�ı�

	void SpindleRotate();//����
	void DealHandwheel(int key1,int key2,bool isHandwheelPressed);//���ְ���
	void DealHandwheel(int key1, int key2);//���ְ���,��ס����
	void DealYiTiJiKey(int key1, int key2, bool isHandwheelPressed);//����һ���  (ͬʱ��ס������,Fn(key1)+Key2)
	void DealYiTiJiKey1(int, int, bool isHandwheelPressed);//����һ��� Key1
	void DealYiTiJiKey(int,int);//����һ��� ���� ��ס����  Fn
	void DealYiTiJiKey3_4(int, int);//����һ��� ���� ��ס����  Fn
	void GetYiTiJiKey();//��ȡ����
	void MySpeedCtrlSud();//��ͣʱ ��������
	void MySpeedCtrlPlus();
	void DealTrGCode();
	void FixFeedrateMultiple(); //���ٺ�ָ�����
	bool OpenSpindleRotat();//�ϵ����� ������ ��ʱ
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

	QTimer			m_timer; //��ʱ��
	QTime           m_runTime; //�ӹ���ʼʱ��
	
	int				m_PassTime=0;//�Ѽӹ�ʱ��
	int			mFinish = 0;//�Ѽӹ� ������
	
	bool			stopZflag =false;//ֹͣʱ Z ̧����־
	
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
	QAction*		AcReturn;//�ع���ԭ��



	int aspeed = 0;//���� Feed+ -��Spindle+ -  ��ס�����ٶȵ��ڣ�
	int YTJspeed = 0;//һ��� Feed+ -��Spindle+ -  ��ס�����ٶȵ��ڣ�
	bool is6Aixs = false;
	bool isFull = false;
	bool isSpeedNeedSud = false;
	bool isSpeedNeedPlus = false;
	bool fixFeedrateMultiple = false;


	bool needShowStartLine = false;
	int RunFlagTime = 0;//����״̬��Ϣ ʱ����������
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
	int	mCurRow = -1;//��ǰ�к�
	int	stopSpindleRotate = 0;//ֹͣʱ �����ٶ�
	int homeLmtFlag = -1;
	bool isMCode = false;
	bool isTCodeFlag_1 = false;
	QString MCodeName = "";
	bool MCodeFromMDI = false;

	TrGCode* pTrGCode;
	int BSize = 5;//�߿�ߴ� ��margin�й�
};
