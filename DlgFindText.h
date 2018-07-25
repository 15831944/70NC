#pragma once

#include <QDialog>
#include "ui_DlgFindText.h"
#include"styledlg.h"
class DlgFindText : public StyleDlg
{
	Q_OBJECT

public:
	DlgFindText(QWidget *parent = Q_NULLPTR);
	~DlgFindText();
	void ShowFind(bool b){ ui.TiShi->setVisible(b); }
	void ResetLanguage();
signals:void findText(QString);
protected:
	void	showEvent(QShowEvent *e);
private:
	Ui::DlgFindText ui;
};
