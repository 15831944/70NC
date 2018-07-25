#pragma once

#include <QWidget>
#include "ui_AutoWork.h"
#include <QLabel>
#include "StyleDlg.h"
#include "DataDefine.h"
class AutoWork : public StyleWidget
{
	Q_OBJECT

public:
	AutoWork(QWidget *parent = Q_NULLPTR);
	~AutoWork();
	void MySetFocus();
	bool MyGetFocus();
	void setPaiChengCiShu(QString str) { ui.paichengsichu->setText(str); }
	void setText(QString str) {
		ui.AutoWorkTableWidget->insertRow(curRow);
		ui.AutoWorkTableWidget->setItem(curRow, 0, new QTableWidgetItem(QString::number(curRow+1)));
		ui.AutoWorkTableWidget->setItem(curRow++, 1, new QTableWidgetItem(str));
	}
	QString GetFileName() { return ui.label->text(); }
	void setFileName(QString str) {	ui.label->setText(str);}
	void UpdataText(int i);
	void clear();
	QTableWidget* getTableWidget() {
		return ui.AutoWorkTableWidget;
	}
	QString GetLastLine(){//获取列表显示的最后一行指令
		int rowCount = ui.AutoWorkTableWidget->rowCount();
		if (rowCount > 0)
			return ui.AutoWorkTableWidget->item(rowCount - 1, 1)->text();
		else
			return "null"; 
	}
	bool CheckContains(QString str1, QString str2) {
		int rowCount = ui.AutoWorkTableWidget->rowCount();
		if (rowCount > 0) {
			QString str = ui.AutoWorkTableWidget->item(rowCount - 1, 1)->text();
			if (str == str1 || str == str2)
				return 1;
		}
		if (rowCount > 1) {
			QString str = ui.AutoWorkTableWidget->item(rowCount - 2, 1)->text();
			if (str == str1 || str == str2)
				return 1;
		}
		if (rowCount > 2) {
			QString str = ui.AutoWorkTableWidget->item(rowCount - 3, 1)->text();
			if (str == str1 || str == str2)
				return 1;
		}
		return 0;
	}
	void UpdateTableByRow(int row, int rowsub=49, int rowplus=50);
	int GetLastRowItem0() {
		int rowCount = ui.AutoWorkTableWidget->rowCount();
		if (rowCount > 0) {
			QString str = ui.AutoWorkTableWidget->item(rowCount - 1, 0)->text();
			return str.toInt();
		}
	}
	int GetStartRowItem0() {
		int rowCount = ui.AutoWorkTableWidget->rowCount();
		if (rowCount > 0) {
			QString str = ui.AutoWorkTableWidget->item(0, 0)->text();
			return str.toInt();
		}
	}
	QStringList TableRowList;
	QString  TableList[BIGSIZE];

	void resetlh() {
		h_flag = l_flag = 0;
	}
private:
	Ui::AutoWork ui;
	void InitTabel();
	int curRow =0;
	 int  h_flag = 0;
	 int l_flag = 0;
};
