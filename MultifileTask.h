#pragma once

#include <QWidget>
#include "ui_MultifileTask.h"
#include"styledlg.h"

class MultifileTask : public StyleDlg
{
	Q_OBJECT

public:
	MultifileTask(QWidget *parent = Q_NULLPTR);
	~MultifileTask();
	void ResetLanguage();
	QString GetCurtimeStr() {return ui.MultifileTaskTable->item(mFlagNum, 2)->text(); }
	void RunMultifileTask();
	bool  GetMultifileTaskAutoWork() { return autowork; }
	bool CheckFinish();//检测多任务是否完全完成
	bool cellFInish();
	void SetMultifileTaskAutoWork(bool b);
	void showEvent(QShowEvent *event);
	bool eventFilter(QObject *obj, QEvent *eve);
signals:void MultifileTaskLoadFile(QString);

private:
	void UpdateState(int row, int all, int cur);
	bool checkTime(int row,bool update=false);//检测是否加工完成(多次)，
	bool checkData();//检测第二列 数据是否合法
	void Data_1(int row);//item->date() -1;
	bool autowork = false;
	void addItem(QString name="");
	void moveRow(QTableWidget *pTable, int nFrom, int nTo);
	void setitemflag(int row);
	void InitFlagNum();
	QString GetFileName();

	Ui::MultifileTask ui;
	QString mFilePath;
	int mFlagNum=0;//已加工完成de最大row
};
