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
	bool CheckFinish();//���������Ƿ���ȫ���
	bool cellFInish();
	void SetMultifileTaskAutoWork(bool b);
	void showEvent(QShowEvent *event);
	bool eventFilter(QObject *obj, QEvent *eve);
signals:void MultifileTaskLoadFile(QString);

private:
	void UpdateState(int row, int all, int cur);
	bool checkTime(int row,bool update=false);//����Ƿ�ӹ����(���)��
	bool checkData();//���ڶ��� �����Ƿ�Ϸ�
	void Data_1(int row);//item->date() -1;
	bool autowork = false;
	void addItem(QString name="");
	void moveRow(QTableWidget *pTable, int nFrom, int nTo);
	void setitemflag(int row);
	void InitFlagNum();
	QString GetFileName();

	Ui::MultifileTask ui;
	QString mFilePath;
	int mFlagNum=0;//�Ѽӹ����de���row
};
