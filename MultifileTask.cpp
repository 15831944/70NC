#include "MultifileTask.h"
#include <QMimeData>
#include "DataDefine.h"
#include <QFileDialog>
#include <QLineEdit>
#include "ReadIni.h"
#include "Samcon.h"
#include "s_OpenFile.h"
#include"CommonTools.h"
#include"TrLang.h"
extern ReadIni readIni;
extern Samcon *w;
#define ItemRole 100
MultifileTask::MultifileTask(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	ui.MultifileTaskTable->viewport()->installEventFilter(this);
	////拖放使能  
	ui.MultifileTaskTable->setDragDropMode(QAbstractItemView::DragDrop);
	ui.MultifileTaskTable->setDragEnabled(true);
	ui.MultifileTaskTable->setAcceptDrops(true);
	ui.MultifileTaskTable->setSelectionBehavior(QAbstractItemView::SelectRows);        //以行为单位  
	//ui.MultifileTaskTable->setEditTriggers(QAbstractItemView::NoEditTriggers);        //不能编辑行内容  
	ui.MultifileTaskTable->setShowGrid(false);
	//ui.MultifileTaskTable->verticalHeader()->setVisible(0);
	ui.MultifileTaskTable->setColumnWidth(0, 240);
	ui.MultifileTaskTable->setColumnWidth(1, 40);
	ui.MultifileTaskTable->setColumnWidth(2, 95);
	

	connect(ui.addfile, &QPushButton::clicked, [this]() {
		mFilePath = QFileDialog::getOpenFileName(0, tr("Open Config"), readIni.GetOpenRecentDir(), tr("Config Files (*.txt *.stl *.nc *tap);;All(*.*)"));
		if (mFilePath.isEmpty())return;
		addItem(mFilePath);
	});

	connect(ui.delfile, &QPushButton::clicked, [this]() {
		ui.MultifileTaskTable->removeRow(ui.MultifileTaskTable->currentRow());
		if (mFlagNum >= ui.MultifileTaskTable->currentRow())
			mFlagNum--;
	});
	SetMultifileTaskAutoWork(0);
	connect(ui.autowork, &QPushButton::clicked, [this]() {
		if (!checkData()||ui.MultifileTaskTable->rowCount()==0) {
			return;
		}
		if (ui.MultifileTaskTable->item(ui.MultifileTaskTable->rowCount() - 1, 2)->text() == TrLang::Ins()->GetText(226))//完成
			return;
		SetMultifileTaskAutoWork(!autowork);
		if (!autowork)return;
		InitFlagNum();
		if (mcc->GetGmode(11).toInt()!=4)return;
		if (w->IsMDIRuningInItmer())return;
		if (!CheckFinish()) {
			RunMultifileTask();
		}
	});

}

MultifileTask::~MultifileTask()
{
}

void MultifileTask::ResetLanguage()
{
	setDlgName(TrLang::Ins()->GetText(80));//排程加工
	QStringList headers;
	headers << TrLang::Ins()->GetText(230) << TrLang::Ins()->GetText(231) << TrLang::Ins()->GetText(232);
	ui.MultifileTaskTable->setHorizontalHeaderLabels(headers);

	ui.addfile->setText(TrLang::Ins()->GetText(233));
	ui.delfile->setText(TrLang::Ins()->GetText(108));
	ui.autowork->setText(TrLang::Ins()->GetText(86));

	if (autowork)
		ui.label->setText(TrLang::Ins()->GetText(227));//当前：开	
	else 
		ui.label->setText(TrLang::Ins()->GetText(228));//当前：关
}

void MultifileTask::showEvent(QShowEvent * event)
{
	QWidget::showEvent(event);
}

bool MultifileTask::eventFilter(QObject *obj, QEvent *eve)
{
	if (obj == ui.MultifileTaskTable->viewport())
	{
		if (eve->type() == QEvent::Drop)
		{
			const QMimeData *mime = ((QDropEvent*)eve)->mimeData();
			QByteArray encodedata = mime->data("application/x-qabstractitemmodeldatalist");
			if (encodedata.isEmpty())
			{
				return false;
			}
			QDataStream stream(&encodedata, QIODevice::ReadOnly);
			while (!stream.atEnd())
			{
				int row, col;
				QMap<int, QVariant> roleDataMap;
				///拖的row和col  
				stream >> row >> col >> roleDataMap;
				QTableWidgetItem* pDropItem = ui.MultifileTaskTable->itemAt(((QDropEvent*)eve)->pos());
				if (!pDropItem)
				{
					return true;
				}

				//放的row  
				if (pDropItem->row() == row)
				{
					return true;
				}
				if(pDropItem->data(ItemRole).toInt ()!=1)
					moveRow(ui.MultifileTaskTable,row, pDropItem->row());
				return true;    //不要交给系统处理，否则他会给你新增一行  
			}
		}
		else
		{
			return QWidget::eventFilter(obj, eve);
		}
	}
	return QWidget::eventFilter(obj, eve);
}
void MultifileTask::UpdateState(int row,int textTime,int DataTime)
{
	QString str1;
	str1 = TrLang::Ins()->GetText(225).arg(DataTime).arg(textTime);//正在加工%1/%2
	ui.MultifileTaskTable->item(row, 2)->setText(str1);
	setitemflag(row);
}
bool MultifileTask::CheckFinish()
{
	if (checkTime(mFlagNum)) {
		if (ui.MultifileTaskTable->rowCount() == mFlagNum + 1) {
			SetMultifileTaskAutoWork(false);	
			return true;
		}
		else {
			
			Data_1(mFlagNum+1);
		}
	}
	else {
		Data_1(mFlagNum );
	}
	return false;
}
void MultifileTask::RunMultifileTask()
{
	QString filename = GetFileName();
	checkTime(mFlagNum, 1);
	if (SammonFunc::isLoading) {
		if (w->getFileName()== filename) {
			emit MultifileTaskLoadFile("");
		}
		else {
			emit MultifileTaskLoadFile(filename);
		}
	}
	else {
		emit MultifileTaskLoadFile(filename);
	}
}
bool MultifileTask::checkTime(int row,bool ud)
{
	QTableWidgetItem * item = ui.MultifileTaskTable->item(row, 1);
	int textTime = item->text().toInt();
	int DataTime = item->data(ItemRole).toInt();
	if(ud)
		UpdateState(row, textTime, textTime-DataTime);
	if (DataTime == 0) 
		return true;
	return false;
}
bool MultifileTask::checkData()
{
	QString Text;
	int TextInt; 
	QTableWidgetItem *item;
	bool  b;
	for (int i = 0; i < ui.MultifileTaskTable->rowCount(); i++) {
		item = ui.MultifileTaskTable->item(i, 1);
		Text = item->text();
		TextInt = Text.toInt(&b);
		if (b) {
			item->setData(ItemRole, TextInt);
		}
		else {
			return false;
		}

	}
	return 1;
}
void MultifileTask::Data_1(int row)
{
	QTableWidgetItem * item = ui.MultifileTaskTable->item(row, 1);
	int idata = item->data(ItemRole).toInt();
	item->setData(ItemRole, idata - 1);
	if(idata==1)
		ui.MultifileTaskTable->item(row, 0)->setData(ItemRole, 1);//加工完成标记
	int textTime = item->text().toInt();
	UpdateState(row, textTime, textTime - idata + 1);
}
bool MultifileTask::cellFInish()
{
	for (int i = 0; i < ui.MultifileTaskTable->rowCount(); i++) {
		if (ui.MultifileTaskTable->item(i, 0)->data(ItemRole).toInt() == 1) {
			ui.MultifileTaskTable->item(i, 2)->setText(TrLang::Ins()->GetText(226));// 完成
		}
	}
	return 1;
}

void MultifileTask::SetMultifileTaskAutoWork(bool b)
{
	if (b) {	
		ui.label->setText(TrLang::Ins()->GetText(227));//当前：开
		ui.autowork->setText(TrLang::Ins()->GetText(229));//取消任务
	}
	else {
		ui.label->setText(TrLang::Ins()->GetText(228));//当前：关
		ui.autowork->setText(TrLang::Ins()->GetText(86));//开始
	}
	autowork = b;
	ui.addfile->setEnabled(!b);
	ui.delfile->setEnabled(!b);
}

void MultifileTask::addItem(QString name )
{
	ui.MultifileTaskTable->insertRow(ui.MultifileTaskTable->rowCount());
	ui.MultifileTaskTable->setRowHeight(ui.MultifileTaskTable->rowCount() - 1, 20);

	QTableWidgetItem* itme0 = new QTableWidgetItem(name);
	QTableWidgetItem* item1 = new QTableWidgetItem("1");
	QTableWidgetItem* item2 = new QTableWidgetItem(TrLang::Ins()->GetText(13));//等待

	ui.MultifileTaskTable->setItem(ui.MultifileTaskTable->rowCount() - 1, 0, itme0);
	ui.MultifileTaskTable->setItem(ui.MultifileTaskTable->rowCount() - 1, 1, item1);
	ui.MultifileTaskTable->setItem(ui.MultifileTaskTable->rowCount() - 1, 2, item2);


	itme0->setFlags(itme0->flags() & (~Qt::ItemIsEditable));
	item2->setFlags(item2->flags() & (~Qt::ItemIsEditable));
}
void MultifileTask::moveRow(QTableWidget *pTable, int nFrom, int nTo)
{
	if (pTable == NULL) return;
	pTable->setFocus();
	if (nFrom == nTo) return;
	if (nFrom < 0 || nTo < 0) return;
	int nRowCount = pTable->rowCount();
	if (nFrom >= nRowCount || nTo > nRowCount) return;
	if (nTo < nFrom) nFrom++;
	pTable->insertRow(nTo);
	pTable->setRowHeight(nTo,20);
	int nCol = pTable->columnCount();
	for (int i = 0; i<nCol; i++) {
		pTable->setItem(nTo, i, pTable->takeItem(nFrom, i));
	}
	if (nFrom < nTo) nTo--;
	pTable->removeRow(nFrom);
	pTable->selectRow(nTo);
}

void MultifileTask::setitemflag(int row)
{
	if (ui.MultifileTaskTable->rowCount() - 1 < row)
		return;
	QTableWidgetItem * item0 = ui.MultifileTaskTable->item(row, 0);
	QTableWidgetItem * item1 = ui.MultifileTaskTable->item(row, 1);
	QTableWidgetItem * item2 = ui.MultifileTaskTable->item(row, 2);
	//item0->setFlags(item0->flags() & (~Qt::ItemIsEnabled));
	item1->setFlags(item1->flags() & (~Qt::ItemIsEnabled));
	//item2->setFlags(item2->flags() & (~Qt::ItemIsEnabled));

	mFlagNum = row;
}

void MultifileTask::InitFlagNum()
{
	for (int i = 0; i < ui.MultifileTaskTable->rowCount(); i++) {
		if (ui.MultifileTaskTable->item(i, 0)->data(ItemRole).toInt() != 1) {
			mFlagNum = i;
			return;
		}
	}
}

QString MultifileTask::GetFileName()
{	
	return ui.MultifileTaskTable->item(mFlagNum, 0)->text();
}
