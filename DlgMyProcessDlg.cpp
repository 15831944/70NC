#include "DlgMyProcessDlg.h"

DlgMyProcessDlg::DlgMyProcessDlg(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setDlgName(QStringLiteral("��ʾ"));
	setWindowModality(Qt::ApplicationModal);
	setLine();
	bt.hide();
	connect(ui.pushButton, &QPushButton::clicked, [this]() {
		CancelClicked();
	});
}

DlgMyProcessDlg::~DlgMyProcessDlg()
{
}
