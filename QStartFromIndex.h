#pragma once

#include "styleDlg.h"
#include "ui_QStartFromIndex.h"
#include "CommonTools.h"
#include "QValidator"
#include"AutoWork.h"
#include "DataDefine.h"
#include "QMessageBox"
class QStartFromIndex : public StyleDlg
{
	Q_OBJECT

public:
	QString mx, my, mz;
	bool showStartLineDlg2 = false; //���Ʊ����ڵ���ʾ
	QStartFromIndex(QWidget *parent = Q_NULLPTR);
	~QStartFromIndex();
	void trantowork(AutoWork* p) { pAutoWork = p; }
	void setText(QString line) {
		ui.lineEdit->setText(line);
	}
	void ResetLanguage();
	void setText();
	bool CheckLineEdit() {


		QString str0 = QStringLiteral("��ȡ");
		QString str2 = QStringLiteral("����������ֶ���ʼ");

		QString str = "";
		if (ui.XMoveto->text().isEmpty())
			str += " X ";
		if (ui.YMoveto->text().isEmpty())
			str += " Y ";
		if (ui.ZMoveto->text().isEmpty())
			str += " Z ";
		if (str != "") {
			QMessageBox::information(0, "Error", str0 + str + str2);
			return 0;
		}
		return 1;
	
	}
	QString GetText() { return ui.lineEdit->text(); }
	void Run() {
		ui.bty->click();
	}
	bool CheckPos();
	void StartFromIdx();//ָ���мӹ�
	void InitInfo();
	void showEvent(QShowEvent *event);
	void Clear() {
		mx =my = mz = -9999;
	}
private:
	void setPos(int row);

signals:
	void StartLineSwitchT(int);
	
private:
	QString G02G03 = "";
	Ui::QStartFromIndex ui;
	QIntValidator *iv;
	QIntValidator *iv2;
	AutoWork *pAutoWork;
	QStringList ItemNumList;
	
};
