#include "DlgCustomDlg.h"
#include "CommonTools.h"
DlgCustomDlg::DlgCustomDlg(QDialog *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
 
	setDlgName(QStringLiteral("自定义步长"));
	setLine();
	ui.TiShi->setVisible(0);	
 	connect(ui.bty, &QPushButton::clicked, [this]() {
 
 
 		if (SammonFunc::IsNumber(ui.lineEdit->text()))
 		{
 			emit ChioceYes();
 			close();
 		}
 		else {
 			ui.TiShi->setVisible(true);
 		}
 
 	});
 	connect(ui.btn, &QPushButton::clicked, [this]() {
 
 		close();
 	}
 	);

	connect(ui.lineEdit, &QLineEdit::textChanged, [this]() {ui.TiShi->setVisible(false); });
}

DlgCustomDlg::~DlgCustomDlg()
{
}
void DlgCustomDlg::showEvent(QShowEvent * e)
{
	ui.lineEdit->setFocus();
}
