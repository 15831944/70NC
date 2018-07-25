#include "YesOrNo.h"
#include "QDebug"
YesOrNo::YesOrNo(QString msg,  QWidget *parent)
	: StyleDlg(parent)
{

	ui.setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);
	setWindowModality(Qt::ApplicationModal);
	setDlgName(QStringLiteral("提示"));
	setLine();
	ui.YN_MSG->setText(msg);
	show();
	connect(ui.YN_Y, &QPushButton::clicked, [this]() {
		emit ChioceYes();
		close();
	});
	connect(ui.YN_N, &QPushButton::clicked, [this]() {close(); });

	setWindowTitle(QStringLiteral("提示！"));
}

YesOrNo::~YesOrNo()
{

}
