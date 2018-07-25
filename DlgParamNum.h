#pragma once

#include <QDialog>
#include "ui_DlgParamNum.h"
#include"CommonTools.h"
#include "styledlg.h"
class DlgParamNum : public StyleDlg
{
	Q_OBJECT

public:
	DlgParamNum(QWidget *parent = Q_NULLPTR);
	~DlgParamNum();
	void ResetLanguage();
	void setText(QString id, QString value,QString s1,QString s2,QString s3) {
		ui.lineEdit->setText(value); 
		ui.label_name->setText(s1);
		ui.label_danwei->setText(s2);
		ui.label_shuom->setText(s3);
		mId = id;
	}
	QString Text() {
		return ui.lineEdit->text();
	}
	void SheZhiMaiChongDangLiang(double value, int axis);
	bool eventFilter(QObject * obj, QEvent * event);
private:
	void func();
	void fun11();
	void fun15();
	void fun21();
	void fun25();
	void fun31();
signals:
	void ChioceYes();
private:

	Ui::DlgParamNum ui;
	QString mId;
};
