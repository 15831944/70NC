#pragma once

#include <QDialog>
#include "ui_DlgCustomDlg.h"
#include"styledlg.h"
class DlgCustomDlg : public StyleDlg
{
	Q_OBJECT

public:
	DlgCustomDlg(QDialog *parent = Q_NULLPTR);
	~DlgCustomDlg();

	QString Text() {
		return ui.lineEdit->text();
	}

	void showEvent(QShowEvent * e);
signals :
	void ChioceYes();
private:

	Ui::DlgCustomDlg ui;
};
