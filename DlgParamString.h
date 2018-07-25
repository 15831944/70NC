#pragma once

#include <QDialog>
#include "ui_DlgParamString.h"
#include"CommonTools.h"
#include"styledlg.h"
class DlgParamString : public StyleDlg
{
	Q_OBJECT
public:
	DlgParamString(QWidget *parent = Q_NULLPTR);
	~DlgParamString();
	void ResetLanguage();
	void setText(QString id,QString value,QString s1,QString s2) {
		if (value == QStringLiteral("ÊÇ"))
		{
			ui.rb_Y->setChecked(true);
			ui.rb_N->setChecked(false);
		}
		else {
			ui.rb_Y->setChecked(0);
			ui.rb_N->setChecked(1);
		}
		ui.textBrowser->append(s1);
		ui.textBrowser->append(s2);
		mId = id;
	}
	QString Text() {
		if (ui.rb_Y->isChecked())
		{
			return QStringLiteral("ÊÇ");
		}
		else
		{
			return QStringLiteral("·ñ");
		}
	}

private:
	void func();
signals :
	void ChioceYes();
private:

	Ui::DlgParamString ui;
	QString mId;
};
