#pragma once

#include <QDialog>
#include "ui_DlgSetSpeedAuto.h"
#include "styledlg.h"
class DlgSetSpeedAuto : public StyleDlg
{
	Q_OBJECT

public:
	DlgSetSpeedAuto(QWidget *parent = Q_NULLPTR);
	~DlgSetSpeedAuto();
	void ResetLanguage();
	signals :
	void ChioceYes();
protected:

private:

	Ui::DlgSetSpeedAuto ui;
};
