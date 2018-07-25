#pragma once

#include <QWidget>
#include "ui_DFX_GCode.h"
#include"CommonTools.h"
#include "StyleDlg.h"
class DXFAdapter;
class DL_Dxf;
class DFX_GCode : public StyleDlg
{
	Q_OBJECT

public:
	DFX_GCode(QWidget *parent = Q_NULLPTR);
	~DFX_GCode();
	void ResetLanguage();
	void getFileName() {}
	void slotitemChanged(QTreeWidgetItem *item, int column);
private:

	void Init();
	void InitTree();
	
	void InitData();
	QStringList GCodeList;
	void ChangeParentState(QTreeWidgetItem *item);
	void ChangeSubState(QTreeWidgetItem *item);
	Ui::DFX_GCode ui;
	DXFAdapter *Adapter;
	DL_Dxf *dxf;
};
