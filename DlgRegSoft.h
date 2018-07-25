#pragma once

#include <QWidget>
#include "ui_DlgRegSoft.h"
#include"styledlg.h"
//GetGmode(13)��0 - �޼�������1 - 4��DLL��2 - 6��DLL                        
//GetGmode(14)�� = 0 δע�ᣬ����ʹ��
//				= -1 �ѽ���������һֱʹ��
//			       = -3 ����ʱ�����ڼ�������¼ʱ�䣬�������ʹ��		
//				= -2 ʹ���ѳ��������������������ʹ��
//				>0 ��ע�ᣬ��ʹ�õ�����
//��λ������������ֵ����������ܽ�����Ӧ���Ƽ���
//GetGmode(15)������ʹ����������������Ч��                                                     
//GetGmode(16)���������Ļ�����                                                                         
//GetGmode(17)��д��ע���롢��ʱ���������Ƿ�ɹ�1 - �ɹ� 0 - ���ɹ�
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
