#pragma once

#include <QWidget>
#include "ui_GManager.h"
#include "QFileSystemModel"
#include "StyleDlg.h"
#include "TrLang.h"
class MyFileSystemModel :public QFileSystemModel {
public:
	MyFileSystemModel():QFileSystemModel() {}
protected:
	QVariant   data(const QModelIndex & item, int role)const  {
		QVariant value = QFileSystemModel::data(item, role);
		if (role == Qt::TextAlignmentRole)
			return Qt::AlignLeft;
		return value;
	}
};
class GManager : public StyleWidget
{
	Q_OBJECT

public:
	
	GManager(QWidget *parent = Q_NULLPTR);
	~GManager();
	void MySetFocus();
	bool MyGetFocus();
	void setPath(QString str);
	void ResetLanguage();
	signals:void sendOpenFile();
protected:

		bool  eventFilter(QObject * obj, QEvent * event);
	void keyReleaseEvent(QKeyEvent * event);

private:
	void Init();
	void InitKeyboardCtrl();
private:
	Ui::GManager ui;
	MyFileSystemModel model;
};
