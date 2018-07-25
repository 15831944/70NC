#pragma once

#include <QDialog>
#include "ui_PasswordDlg.h"
#include"styledlg.h"
enum PassWordFlag {
	NonePwd  = 0,
	DeveLoperPwd = 1

};
class PasswordDlg : public StyleDlg
{
	Q_OBJECT

public:
	PasswordDlg(int flag, QString leabel,QWidget *parent = Q_NULLPTR);
	~PasswordDlg();
	void show(int flag,QString leabel);

	
signals:void ChioceYes();

protected:
	bool eventFilter(QObject * obj, QEvent * event);
private:	
	QString sDevelopPwd = "123456";
	PassWordFlag PwdFlag = NonePwd;

	Ui::PasswordDlg ui;
};
