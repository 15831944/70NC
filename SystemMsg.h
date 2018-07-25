#pragma once
////////////////////////////////////////////
/////±¨¾¯ÐÅÏ¢
///////////////////////////////////////////
#include <QObject>
#include <QWidget>
#include "ui_WarningMsg.h"
#include "StyleDlg.h"
class SystemMsg : public StyleWidget
{
	Q_OBJECT

public:
	SystemMsg(QWidget *parent = Q_NULLPTR);
	~SystemMsg();
	void MySetFocus();
	bool MyGetFocus();
	void ResetLanguage();
protected:	
	bool  eventFilter(QObject * obj, QEvent * event);
	void keyReleaseEvent(QKeyEvent * event);
private:
	void InitKeyboardCtrl();
	Ui::WarningMsg ui;
};
