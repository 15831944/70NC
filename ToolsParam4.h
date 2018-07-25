#pragma once


#include "ui_ToolsParam4.h"
#include "StyleDlg.h"
class ToolsParam4 : public StyleDlg
{
	Q_OBJECT

public:
	ToolsParam4(QWidget *parent = Q_NULLPTR);
	~ToolsParam4();
	void ResetLanguage();
		void 	hideEvent(QHideEvent *event);
	void 	showEvent(QShowEvent *event);
private:
	Ui::ToolsParam4 ui;

	void Init();
	void SaveParam();
	void ShowParam();
	void setVType4Text();
};
