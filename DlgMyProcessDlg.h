#pragma once

#include <QWidget>
#include "ui_DlgMyProcessDlg.h"
#include"qdebug"
#include"qthread"
#include "styledlg.h"

class DlgMyProcessDlg : public StyleDlg
{
	Q_OBJECT

public:
	DlgMyProcessDlg(QWidget *parent = Q_NULLPTR);
	~DlgMyProcessDlg();
	void setRange(int s, int e) {
		ui.progressBar->setRange(s, e);
	}
	void setValue(int v) {
		ui.progressBar->setValue(v);	}
	void _show() {
		show();
	}
	void _hide() {
		hide();
	}
	void hidecancel() {
		ui.pushButton->hide();
	}

	void showEvent(QShowEvent *event) {
		ui.progressBar->setValue(0);
	}
signals:void CancelClicked();

	
		 
private:

	Ui::DlgMyProcessDlg ui;
};
