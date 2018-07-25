#pragma once

#include <QWidget>
#include "ui_DlgMachToInternalIncr.h"
#include"styledlg.h"
class DlgMachToInternalIncr : public StyleDlg
{
	Q_OBJECT

public:
	DlgMachToInternalIncr(QWidget *parent = Q_NULLPTR);
	~DlgMachToInternalIncr();
	void ResetLanguage();
private:

	void Init();
	bool isEmpty() {
		return ui.lineEdit_luoju->text().isEmpty() || ui.lineEdit_bujingjiao->text().isEmpty() || ui.lineEdit_xifen->text().isEmpty() || ui.lineEdit_jiansubi->text().isEmpty();
	}
	void JiSuanMaiChongDangLiang();
	Ui::DlgMachToInternalIncr ui;
};
