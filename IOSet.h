#pragma once
////////////////////////////////////////////
/////�������
///////////////////////////////////////////
#include <QObject>
#include <QWidget>
#include "ui_IOSet.h"
#include "StyleDlg.h"

//int Set_IoIn_Mode(int cardno, int ioin, int mode, int logic, int Enalbe)
//���ܣ�
//�趨IO�����źŵĴ���ģʽ.ÿ��IO���иߵ����ֵ�ƽ, �н�ֹ����ʹ��״̬������Ϊ��ͣ����ͨ��IO.
//������
//cardno ����
//ioin   �� 0 - 31��IO
//mode �� IOģʽ�����¼���,
//0ͨ��IO��, ���ź���Чʱ, ������ֹͣ, ֻ�ǰѴ��źŴ���ϵͳ.
//1:��Ϊ��λ�ź�, x����λ��2��y����λ, ��6 : c����λ.
//- 1 : ��Ϊ��λ�ź�, x����λ�� - 2��y����λ����. - 6 : c����λ.
//����λ�źŴ���ʱ, �����Զ�ֹͣ, ��ʱ������LMTLOCK��λ״̬.��״ֻ̬���ڽ��յ�UnlimtSignal��������ȡ��.
//16��Estop ��ͣ�ź�.(����ֹͣ�������˶�), ��IO����Ϊ��ͣIO.
//Logic��0���͵�ƽ��Ч��1���ߵ�ƽ��Ч
//Enabel : 1ʹ��, 0��ֹ
//	Ĭ��ģʽΪ��ͨ��IO���͵�ƽ��Ч.
//	����ֵ0����ȷ�����������󷵻ش���


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
	bool CheckToolSetting();//�Ե��Ƿ��ֹ
	int GetTriggered(int signalNum);
	void CheckHome();//��0�Ƿ��ֹ
	void CancelAll() {
		ui.CancelAllTest->click();
	}//ȡ��ȫ������
	void In6Trigger(bool isTriggered);
	void In11Trigger(bool isTriggered);
	void In12Trigger(bool isTriggered);
	void CloseOut5();//ֱ�ŵ� Type==2 ���װ汾 ֹͣ ��λʱ Ҫ�ر�����˿ڣ����� ��Σ��
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
	int isTest = 0;//��λ��0û���ԣ�1����
	int OutFlag = 0;//����ʱ ���浱ǰ���״̬
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
