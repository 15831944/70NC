#pragma once

#include <QWidget>
#include "ui_DlgRegSoft.h"
#include"styledlg.h"
//GetGmode(13)：0 - 无加密锁，1 - 4轴DLL，2 - 6轴DLL                        
//GetGmode(14)： = 0 未注册，不能使用
//				= -1 已解锁，可以一直使用
//			       = -3 电脑时间早于加密锁记录时间，软件不能使用		
//				= -2 使用已超过允许天数，软件不能使用
//				>0 已注册，已使用的天数
//上位机软件根据这个值，对软件功能进行相应限制即可
//GetGmode(15)：允许使用天数（解锁后无效）                                                     
//GetGmode(16)：加密锁的机器码                                                                         
//GetGmode(17)：写入注册码、延时码或解锁码是否成功1 - 成功 0 - 不成功
class DlgRegSoft : public StyleDlg
{
	Q_OBJECT

public:
	DlgRegSoft(QWidget *parent = Q_NULLPTR);
	~DlgRegSoft();
	
	void TimeCheckReg();


	void showEvent(QShowEvent *e) {
		LoadData();
		showData();
		QWidget::showEvent(e);
	}
private:

	void Init();
	void LoadData();
	void showData();

	Ui::DlgRegSoft ui;
	QString GMode13Value;
	QString GMode14Value;
	QString GMode15Value;
	QString GMode16Value;

};
