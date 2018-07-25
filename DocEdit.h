#pragma once

#include <QWidget>
#include "ui_DocEdit.h"
#include "StyleDlg.h"
#include "DlgFindText.h"
class QsciScintilla;
class DocEdit : public StyleWidget
{
	Q_OBJECT

public:
	DocEdit(QWidget *parent = Q_NULLPTR);
	~DocEdit();
	void ResetLanguage();
	void EditFile(QString fn);
	void MySetFocus();
	bool MyGetFocus();
protected:
	void keyReleaseEvent(QKeyEvent * event);
	bool  eventFilter(QObject * obj, QEvent * event);
private:
	void InitUI();
	void InitKeyboardCtrl();
private:
	Ui::DocEdit ui;
	QString mfileName;
	DlgFindText DlgFind;
	QsciScintilla *textEdit;
};
