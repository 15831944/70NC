#pragma once

#include <QWidget>
#include "ui_QuicklySettings.h"
#include "styledlg.h"
class QuicklySettings : public StyleDlg
{
	Q_OBJECT

public:
	QuicklySettings(QWidget *parent = Q_NULLPTR);
	~QuicklySettings();
	void ResetLanguage();
protected:
	void showEvent(QShowEvent *event) { ui.stackedWidget->setCurrentIndex(0); }
private:
	void InitValue();
	void SaveValue();
	void setHideButton();
private:
	Ui::QuicklySettings ui;
};
