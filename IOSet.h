#pragma once
////////////////////////////////////////////
/////输入输出
///////////////////////////////////////////
#include <QObject>
#include <QWidget>
#include "ui_IOSet.h"
#include "StyleDlg.h"

//int Set_IoIn_Mode(int cardno, int ioin, int mode, int logic, int Enalbe)
//功能：
//设定IO输入信号的触发模式.每个IO口有高低两种电平, 有禁止或者使用状态，有作为急停或者通用IO.
//参数：
//cardno 卡号
//ioin   ： 0 - 31个IO
//mode ： IO模式有以下几种,
//0通用IO口, 当信号有效时, 卡不会停止, 只是把此信号传给系统.
//1:作为限位信号, x正限位，2：y正限位, …6 : c正限位.
//- 1 : 作为限位信号, x负限位， - 2：y负限位……. - 6 : c负限位.
//当限位信号触发时, 卡会自动停止, 此时卡处于LMTLOCK限位状态.此状态只有在接收到UnlimtSignal命令后才能取消.
//16：Estop 急停信号.(立即停止所有轴运动), 此IO口作为急停IO.
//Logic：0：低电平有效；1：高电平有效
//Enabel : 1使能, 0禁止
//	默认模式为：通用IO，低电平有效.
//	返回值0：正确，其它见错误返回代码


class IOSet : public StyleWidget
{
	Q_OBJECT

public:
	IOSet(QWidget *parent = Q_NULLPTR);
	~IOSet();
	void ResetLanguage();
	void MySetFocus();
	bool MyGetFocus();
	void showIconIn();
	void showIconOut();
	bool CheckToolSetting();//对刀是否禁止
	int GetTriggered(int signalNum);
	void CheckHome();//回0是否禁止
	void CancelAll() {
		ui.CancelAllTest->click();
	}//取消全部测试
	void In6Trigger(bool isTriggered);
	void In11Trigger(bool isTriggered);
	void In12Trigger(bool isTriggered);
	void CloseOut5();//直排刀 Type==2 气缸版本 停止 复位时 要关闭这个端口，否则 很危险
	void  timerIn11Run();
	void ResetItemText();
protected:
	
		bool  eventFilter(QObject * obj, QEvent * event);
	void keyReleaseEvent(QKeyEvent *event);
private:
	void InitUI();
	void InitButton();
	void changeEnabled();
	void UpdataPolarity();	
	void InitKeyboardCtrl();
	void In11Run();
private:
	int isTest = 0;//按位，0没测试，1测试
	int OutFlag = 0;//测试时 保存当前输出状态
	bool bIn11Run = false;
	Ui::IOSet ui;
	QIcon IconRed;
	QIcon IconGreen;
	QIcon IconYes;
	QIcon IconNo;
	QIcon IconTRed;
	QIcon IconTGreen;
	void InitTable();
	int InIndex = 0;
	QTableWidgetItem * InItem[17];
	QTableWidgetItem * OutItem[17];
};
