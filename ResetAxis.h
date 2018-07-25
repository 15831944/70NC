#pragma once

#include <QDialog>
#include "ui_ResetAxis.h"
#include "StyleDlg.h"
class ResetAxis : public StyleDlg
{
	Q_OBJECT

public:
	ResetAxis(QWidget *parent = Q_NULLPTR);
	~ResetAxis();
	void ResetLanguage();
	void SHowTiShi();
	void VersionConversion(bool is6Axis) {
		this->is6Axis = is6Axis;
		if (!is6Axis) {
			ui.label_23->setVisible(0);
			ui.label_24->setVisible(0);
			ui.label_25->setVisible(0);
			ui.label_26->setVisible(0);
			ui.label_27->setVisible(0);
			ui.label_28->setVisible(0);
			ui.label_29->setVisible(0);
			ui.label_30->setVisible(0);
			ui.label_31->setVisible(0);
			ui.label_32->setVisible(0);
			
			ui.leb->setVisible(0);
			ui.lec->setVisible(0);
			ui.cbb->setVisible(0);
			ui.cbc->setVisible(0);

			ui.distb->setVisible(0);
			ui.distc->setVisible(0);

			ui.BtResetB->setVisible(0);
			ui.BtResetC->setVisible(0);

			ui.groupBox_2->resize(161, 141);
			ui.groupBox_3->resize(161, 141);
			ui.groupBox_4->resize(161, 141);
		}
	}
	void ncpodRefer(int num);
	void MachineReturn();

	void	showEvent(QShowEvent *event);
	bool  eventFilter(QObject * obj, QEvent * event);
	void keyReleaseEvent(QKeyEvent *event);

private:
	void returnAxis(int MachineReturn, int returnAxis, int nextMachineReturn, double returnLen, int clearAxis);
	void Init();
	void SetValue();
	void SaveValue();
	void InitKeyboardCtrl();

private:
	Ui::ResetAxis ui;
	bool is6Axis =1;
};
