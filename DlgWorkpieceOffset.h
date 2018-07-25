#pragma once


#include "ui_DlgWorkpieceOffset.h"
#include "styledlg.h"
class DlgWorkpieceOffset : public StyleDlg
{
	Q_OBJECT

public:
	DlgWorkpieceOffset(QWidget *parent = Q_NULLPTR);
	~DlgWorkpieceOffset();
	void ResetLanguage();
	void SetWorkpiece(int axis, double value);
	void SetWorkpiece(int);
	void SetCurrentIndex(int i) { ui.comboBox->setCurrentIndex(i); }

		void showEvent(QShowEvent *event);
private:
	void offsetChange();
	void InitOffset();
	void SaveOffset();
	
	void SetEnadble();
	
private:
	int WorkpieceIndex = -1;//Çø·Ö G54 55 56.¡£¡£¡£¡£

	Ui::DlgWorkpieceOffset ui;
};
