#pragma once

#include <QWidget>
//#include "ui_ctrlHand6.h"
//#include "ui_ctrlHand4.h"
#include "ui_ctrlHand.h"
#include "StyleDlg.h"
#include <QTime> 
#include "StyleDlg.h"
class DlgCustomDlg;
class ctrlHand : public StyleWidget
{
	Q_OBJECT

public:
	ctrlHand(QWidget *parent = Q_NULLPTR);
	~ctrlHand();
	void ResetLanguage();
	void MySetFocus();
	bool MyGetFocus();
	void VersionConversion(bool is6Axis){
		this->is6Axis = is6Axis;
		ui.Badd->setVisible(is6Axis);
		ui.Bsub->setVisible(is6Axis);
		ui.Csub->setVisible(is6Axis);
		ui.Cadd->setVisible(is6Axis);
		if (!is6Axis) {
			ui.gridLayout_step2->addWidget(ui.rbLX, 0, 0);
			ui.gridLayout_step2->addWidget(ui.rb001, 1, 0);
			ui.gridLayout_step2->addWidget(ui.rbV3, 2, 0);
			ui.gridLayout_step2->addWidget(ui.rbV4, 3, 0);
			ui.gridLayout_step2->addWidget(ui.rbV5, 4, 0);
			ui.gridLayout_step2->addWidget(ui.rbV6, 5, 0);
			ui.gridLayout_step2->addWidget(ui.rbV7, 6, 0);
			ui.gridLayout_step2->addWidget(ui.rbV9, 7, 0);
		}
		
	}
	void keyPressEvent(QKeyEvent * event);
	void keyReleaseEvent(QKeyEvent *event);
	bool  eventFilter(QObject * obj, QEvent * event);
	void DealHandwheel(int key1, int key2, bool isHandwheelPressed);
	double GetStep() { return step; }
	void NcPodMove(int i, int axis, QString s);

protected:
	void showEvent(QShowEvent *event);
	void resizeEvent(QResizeEvent *event);
private:
	void reinitsize() {

	}
	void AddStep(int i, int axis,QString s);
	void SudStep(int i, int axis, QString s);
	void InitShortCuts();
	void InitUI();
	void InitXYZ();
	void InitStep();
	void setBtnText();
	void InitKeyboardCtrl();
	void SetLEDDate();
	void DoSimSpeedCtrl(int direction, int AxisNum,QString Axis);
private:
	Ui::ctrlHand ui;
	DlgCustomDlg* pDlgCustomDlg;
	double step;
	double CustomStep;
	bool isPressed = false;
	bool is6Axis;
	int originalW = 83;
	int originalH = 53;
	int originalSpace = 6;
	bool isLxRuning = false;
	QTime DurTime;
};
