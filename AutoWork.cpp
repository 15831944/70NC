#include "AutoWork.h"
#include <QTextLayout>
#include <qdebug>
#include <QTextBlock>
#include"CommonTools.h"
#include "QModelIndex"
#include "Samcon.h"
#include "s_OpenFile.h"
extern Samcon* w;
AutoWork::AutoWork(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	InitTabel();
}

AutoWork::~AutoWork()
{
}

void AutoWork::MySetFocus()
{
	setFocus();
}

bool AutoWork::MyGetFocus()
{
	return hasFocus();
}

void AutoWork::UpdataText(int row)
{
	if (row - 1 - l_flag < ui.AutoWorkTableWidget->rowCount()) {
		ui.AutoWorkTableWidget->setCurrentCell(row - 1-l_flag, 1);
	}
	if (l_flag > row) {
		l_flag = 0;
		h_flag = 0;
	}
	if (h_flag > row)
		return;

	int l = 0, h = 0;
	
	if (row > 50)
		l = row -50;
	else
		l =  0;
	if (row + 50 < TableRowList.size())
		h = row+50;
	else
		h = row+TableRowList.size() - row;
	l_flag = l;
	h_flag = h;
	UpdateTableByRow(row, l, h);
	//ui.AutoWorkTableWidget->setCurrentCell(row - 1, 1);

}

void AutoWork::clear()
{
	
		curRow = 0;
		h_flag = 0;
		l_flag = 0;
		TableRowList.clear();
		ui.label->clear();
		ui.AutoWorkTableWidget->setRowCount(0);
		ui.AutoWorkTableWidget->clearContents();
		SammonFunc::Getins()->IndexRrcod = 0;
	
}

void AutoWork::UpdateTableByRow(int row, int rowsub, int rowplus)
{
	if (rowplus <rowsub)
		return;
	ui.AutoWorkTableWidget->setRowCount(0);
	ui.AutoWorkTableWidget->clearContents();
	
	int r = 0;
	for (int i = rowsub; i < rowplus; i++) {
	
		ui.AutoWorkTableWidget->insertRow(r);
		ui.AutoWorkTableWidget->setItem(r, 0, new QTableWidgetItem(QString::number(i+1+w->getOpenFile()->PageMaxRow)));
		ui.AutoWorkTableWidget->setItem(r++, 1, new QTableWidgetItem(TableRowList[i]));
	}
	if (row - 1 - l_flag < ui.AutoWorkTableWidget->rowCount()) {
		ui.AutoWorkTableWidget->setCurrentCell(row - 1 - l_flag, 1);
	}
}

void AutoWork::InitTabel()
{
	ui.AutoWorkTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.AutoWorkTableWidget->setColumnWidth(0, 80);
	ui.AutoWorkTableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.AutoWorkTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.AutoWorkTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.AutoWorkTableWidget->setShowGrid(false);
}

