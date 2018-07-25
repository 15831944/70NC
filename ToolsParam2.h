#pragma once


#include "ui_ToolsParam2.h"
#include "styledlg.h"
class ToolsParam2 : public StyleDlg
{
	Q_OBJECT

public:
	ToolsParam2(QWidget *parent = Q_NULLPTR);
	~ToolsParam2();
	void ResetLanguage();
		void 	hideEvent(QHideEvent *event);
	void 	showEvent(QShowEvent *event);
private:
	Ui::ToolsParam2 ui;

		void Init();
	void SaveParam();
	void ShowParam();
};
