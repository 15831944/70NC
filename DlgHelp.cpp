#include "DlgHelp.h"
#include "qfile.h"
#include "QTextStream.h"
#include <qlabel.h>
#include<QGridLayout>
DlgHelp::DlgHelp(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setDlgName(QStringLiteral("°ïÖú"));
	setAttribute(Qt::WA_DeleteOnClose, true);
	setLine();
	Init();
	
}

DlgHelp::~DlgHelp()
{
}

void DlgHelp::Init()
{
	QFile file("./readme.txt");
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	int i = 0;
	QWidget *w = new QWidget;
	QGridLayout * layout = new QGridLayout;
	w->setLayout(layout);
	int j = 0;
	while (!in.atEnd()) {
		QLabel *lb = new QLabel(w);
		lb->setText(in.readLine());
		layout->addWidget(lb, j++, 0);
	}
	ui.scrollArea->setWidget(w);
}
