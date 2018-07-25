#pragma once

#include <QWidget>
#include "ui_DlgHelp.h"
#include"styledlg.h"
class DlgHelp : public StyleDlg
{
	Q_OBJECT

public:
	DlgHelp(QWidget *parent = Q_NULLPTR);
	~DlgHelp();

private:

	void Init();
	Ui::DlgHelp ui;
};
