#pragma once

#include <QDialog>
#include "ui_DlgSetParameter.h"
#include "styledlg.h"
enum ParamType
{//User_用户参数；Manufacturer_厂商参数
	User_CaoZ,//操作参数   、、用户参数
	Manufacturer_CaoZ,//厂商参数
	User_GeiJZ,//进给轴
	Manufacturer_GeiJZ,//厂商参数
	User_IO, //输入输出
	Manufacturer_IO,//厂商参数
	User_Tool,//刀具参数
	Manufacturer_Tool,//厂商参数
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
