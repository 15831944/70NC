#pragma once

#include <QWidget>
#include "ui_ToolSetting.h"
#include "StyleDlg.h"
class ToolSetting : public StyleWidget
{
	Q_OBJECT

public:
	ToolSetting(QWidget *parent = Q_NULLPTR);
	~ToolSetting();
	void ResetLanguage();
	void MySetFocus();
	bool MyGetFocus();
	void zFToolSetting();
	void zToolSetting();
	void DoMAutoToolSetting();
protected:

	void resizeEvent(QResizeEvent *event);
	bool  eventFilter(QObject * obj, QEvent * event);
	void keyReleaseEvent(QKeyEvent *event);
	void showEvent(QShowEvent *event);
private:
	void init();
	void save();
	void InitKeyboardCtrl();
	//void GetTool
private:
	Ui::ToolSetting ui;
};
