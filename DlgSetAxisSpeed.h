#pragma once

#include <QDialog>
#include "ui_DlgSetAxisSpeed.h"
#include "styledlg.h"
class DlgSetAxisSpeed : public StyleDlg
{
	Q_OBJECT

public:
	DlgSetAxisSpeed(QWidget *QDialog = Q_NULLPTR);
	~DlgSetAxisSpeed();
	QString GetText() { return ui.lineEdit->text(); }
	void ResetLanguage();
signals:
	void ChioceYes();
private:

	Ui::DlgSetAxisSpeed ui;
};
