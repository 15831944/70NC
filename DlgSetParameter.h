#pragma once

#include <QDialog>
#include "ui_DlgSetParameter.h"
#include "styledlg.h"
enum ParamType
{//User_�û�������Manufacturer_���̲���
	User_CaoZ,//��������   �����û�����
	Manufacturer_CaoZ,//���̲���
	User_GeiJZ,//������
	Manufacturer_GeiJZ,//���̲���
	User_IO, //�������
	Manufacturer_IO,//���̲���
	User_Tool,//���߲���
	Manufacturer_Tool,//���̲���
	User_ALL,
	Manufacturer_All,
};

enum ParamValueType {
	_NOV = 0,
	_NUM,
	_String,

};
class DlgSetParameter : public StyleDlg
{
	Q_OBJECT

public:
	DlgSetParameter(QWidget *parent = Q_NULLPTR);
	~DlgSetParameter();
	void ResetLanguage();
	void showEvent(QShowEvent *event);
	void hideEvent(QHideEvent *hideEvent);
private:
	void InitUi();
	void filterRule();
	void InitTable();
	void InitParam();
	void rowN11();
	void rowN15();
	void rowN21();
	void rowN25();
	void rowN31();
	
	void ShowICon();
	void filterUser(ParamType t);
	void filterManufacturer(ParamType user, ParamType fact);
	void filterAll(ParamType type);
	void setSoftLm();

signals:
	void updateText();
private:

	QPushButton* curPushButton=0;
	QRadioButton* curRadioButton =0;
	int mRow = 0;
	QFont mFont;
	QFont mFont2;
	Ui::SetParameter ui;
};
