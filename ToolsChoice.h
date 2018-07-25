#pragma once

#include <QWidget>
#include "ui_ToolsChoice.h"
#include "StyleDlg.h"
class ToolsParam2;
class ToolsParam4;
class ToolsChoice : public StyleWidget
{
	Q_OBJECT

public:
	ToolsChoice(QWidget *parent = Q_NULLPTR);
	~ToolsChoice();
	void ResetLanguage();
	void MySetFocus();
	bool MyGetFocus();
	void Init();
	void setToolEnabled(int no,bool en);
	void setToolChecked(int no);
	bool DoMCode(QString curline);
	void ignoreToolChange(int tt);

protected:

	void keyReleaseEvent(QKeyEvent *event);
	bool  eventFilter(QObject * obj, QEvent * event);
	void resizeEvent(QResizeEvent *event) {
		int size = ui.TOOL1->height() / 3;
		QString style = "\
		QRadioButton::indicator{\
			width: %1px;\
			height: %2px;\
		}";

		size = size > 10 ? size : 10;
		size = size < 20 ? size : 20;

		style = style.arg(size).arg(size);

		ui.TOOL1->setStyleSheet(style);
		ui.TOOL2->setStyleSheet(style);
		ui.TOOL3->setStyleSheet(style);
		ui.TOOL4->setStyleSheet(style);
		ui.TOOL5->setStyleSheet(style);
		ui.TOOL6->setStyleSheet(style);
		ui.TOOL7->setStyleSheet(style);
		ui.TOOL8->setStyleSheet(style);
		ui.TOOL9->setStyleSheet(style);
		ui.TOOL10->setStyleSheet(style);
		ui.TOOL11->setStyleSheet(style);
		ui.TOOL12->setStyleSheet(style);
		ui.TOOL13->setStyleSheet(style);
		ui.TOOL14->setStyleSheet(style);
		ui.TOOL15->setStyleSheet(style);
		ui.TOOL16->setStyleSheet(style);
		QWidget::resizeEvent(event);
	}
	void showEvent(QShowEvent *event) {
		int size = ui.TOOL1->height() / 3;
		QString style = "\
		QRadioButton::indicator{\
			width: %1px;\
			height: %2px;\
		}";

		size = size > 10 ? size : 10;
		size = size < 20 ? size : 20;

		style = style.arg(size).arg(size);

		ui.TOOL1->setStyleSheet(style);
		ui.TOOL2->setStyleSheet(style);
		ui.TOOL3->setStyleSheet(style);
		ui.TOOL4->setStyleSheet(style);
		ui.TOOL5->setStyleSheet(style);
		ui.TOOL6->setStyleSheet(style);
		ui.TOOL7->setStyleSheet(style);
		ui.TOOL8->setStyleSheet(style);
		ui.TOOL9->setStyleSheet(style);
		ui.TOOL10->setStyleSheet(style);
		ui.TOOL11->setStyleSheet(style);
		ui.TOOL12->setStyleSheet(style);
		ui.TOOL13->setStyleSheet(style);
		ui.TOOL14->setStyleSheet(style);
		ui.TOOL15->setStyleSheet(style);
		ui.TOOL16->setStyleSheet(style);
		QWidget::showEvent(event);
	}

private:
	void CheckLine(QString curline);
	void InitKeyboardCtrl();
	Ui::ToolsChoice ui;
	
	ToolsParam2	*pToolsParam2=NULL;
	ToolsParam4	*pToolsParam4=NULL;
};
