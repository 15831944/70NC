#pragma once

#include "ui_YesOrNo.h"
#include "styledlg.h"

class YesOrNo : public StyleDlg
{
	Q_OBJECT

public:
	YesOrNo(QString msg, QWidget *parent = Q_NULLPTR);
	~YesOrNo();

signals:
	void ChioceYes();
private:

	YesOrNo() {}
	YesOrNo(QWidget *parent = Q_NULLPTR) {}
	Ui::YesOrNo ui;
};
