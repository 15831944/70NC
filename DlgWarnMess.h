#pragma once

#include <QWidget>
#include "ui_DlgWarnMess.h"
#include"styledlg.h"
class DlgWarnMess : public StyleDlg
{
	Q_OBJECT

public:
	DlgWarnMess(QString str,QWidget *parent = Q_NULLPTR);
	~DlgWarnMess();
	void ResetLanguage();
		void	keyReleaseEvent(QKeyEvent *event);
private:
	Ui::DlgWarnMess ui;

};
