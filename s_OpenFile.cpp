#include "s_OpenFile.h"
#include "QFileDialog"
#include "QTextStream"
#include "mccdll.h"
#include "CommonTools.h"
#include "ReadIni.h"
#include"AnalysisG.h"
#include"LogManager.h"
#include"qmessagebox.h"
#include"DlgWarnMess.h"
#include"qtime"
#include "Samcon.h"
#include "ncpod.h"

extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern QString MyStyle;
extern Samcon *w;
s_OpenFile::s_OpenFile(QObject *parent)
	: QObject(parent)
{
	ProgressDialog.setStyleSheet(MyStyle);
	connect(&ProgressDialog, &DlgMyProcessDlg::CancelClicked, [this]() {
		neetBreak = true;
	});
	moveToThread(&mThread);
	PagePos << 0;
	connect(&mThread, &QThread::started, [this]() {
		QFile file(fileName);
		file.open(QIODevice::ReadOnly);
		QTextStream in(&file);	
		FileCodeCount = 0+InsertCodeInStart(1);
		int i =0+ InsertCodeInStart(1);
		while (!in.atEnd()) {
			if(!in.readLine().simplified().isEmpty())
			FileCodeCount++;
			i++;
			if (i == BIGSIZE) {
				PagePos << in.pos();
				i = 0;
			}
		}
		FileCodeCount +=  InsertCodeInEnd(1);
		mThread.quit();
	});
	connect(SammonFunc::Getins(), &SammonFunc::sendDxfStream, [this](QTextStream& stream, QString DXFname,int tt) {
		LoadDXFCode(stream, DXFname,tt);
	});
}

s_OpenFile::~s_OpenFile()
{

}

void s_OpenFile::LoadFile(AutoWork *pAutoWork, QString fn )
{
	if (fn.isEmpty()) {
		fileName = QFileDialog::getOpenFileName(0,tr("Open Config"),readIni.GetOpenRecentDir(),tr("Config Files (*.txt *.stl *.nc *tap);;All(*.*)"));
	}
	else
		fileName = fn;
	SammonFunc::Getins()->Loading = true;
	file.close();
	file.setFileName(fileName);
	if (file.open(QIODevice::ReadOnly))
	{

		mThread.start();
	
		SammonFunc::TCodeMap.clear();
		SammonFunc::Getins()->IndexRrcod = 0;
		LogManager::getIns()->appendLog(QStringLiteral("装载文件：") + fileName);
		readIni.SetOpenRecentFile(fileName);
		QStringList &slist = fileName.split('/');
		readIni.SetOpenRecentDir(fileName.left(fileName.size() - slist[slist.size() - 1].size()));	
		pAutoWork->clear();
		pAutoWork->setFileName(fileName);
	
		mcc->ClearAutoText();
		mcc->ClearBuffer();
		mcc->SetAutoRunFlag(false);
		pAnalysisG.clear();
		neetBreak = false;
		PageMaxRow = 0;
		SammonFunc::IsPause = false;
		
		in.setDevice(&file);


		int Inaccurate = file.size();
		if(Inaccurate>20*1900000) Inaccurate = 20 * 1900000;
		Inaccurate = Inaccurate /20/50;  //大约的总行数的1/50;     大约20比特 一行
		int process = Inaccurate;   //大约的总行数的1/50;
		int processIdx = 0;//百分比 序列号
		ProgressDialog.setRange(0, 100);
		ProgressDialog.show();
		QApplication::processEvents();
		QApplication::processEvents();


		QString line;
		int rowNum = 1+InsertCodeInStart();//	用于设置SammonFunc::MCodeMap 的 key

		while (!in.atEnd()&& rowNum <= BIGSIZE)
		{
			if (neetBreak) {//点击取消
				ProgressDialog.hide();;
				mcc->ClearAutoText();
				pAnalysisG.clear();
				pAutoWork->clear();
				file.close();
				SammonFunc::RunShow = 0;
				SammonFunc::PauseShow = 0;
				SammonFunc::NextShow = 0;
				SammonFunc::isLoading = 0;
				return;
			}

			if (process--==0) {
				ProgressDialog.setValue(processIdx+=2);
				process = Inaccurate;
				QApplication::processEvents();
			}
			line = in.readLine();
			if (line.simplified().isEmpty())
				continue;

			pAutoWork->TableRowList.push_back(line);
			if (!pAnalysisG.GetValidline(line, rowNum++)) {//不支持的代码  不加工//检测G代码是否有效 .插入点 加载文件显示刀路	
				ProgressDialog.hide();
				DlgWarnMess* dlg = new DlgWarnMess(pAnalysisG.errorMsg);			
				mcc->ClearAutoText();
				pAnalysisG.clear();
				pAutoWork->clear();
				SammonFunc::RunShow = 0;
				SammonFunc::PauseShow = 0;
				SammonFunc::NextShow = 0;
				SammonFunc::isLoading = 0;
				SammonFunc::Getins()->Loading = false;
				file.close();
				return;
			}	
			mcc->SendAutoText(line);
		}
		if (!in.atEnd()) {
			mcc->SendAutoText(QString("M00 M789"));
		}
		else {
			file.close();
			mcc->SendAutoText(QString("M30"));
			InsertCodeInEnd();
		}

		SammonFunc::RunShow = true;
		SammonFunc::PauseShow = 0;
		SammonFunc::NextShow = 0;
		SammonFunc::isLoading = true;
		SammonFunc::StartLine = -1;
		emit signal_fileLoad();	
		ProgressDialog.hide();

	}
	SammonFunc::Getins()->Loading = false;
}

void s_OpenFile::LoadNext()
{
	SammonFunc::Getins()->Loading = 1;
	w->getAutoWork()->clear();
	PageNum++;
	SammonFunc::Getins()->IndexRrcod = PageNum;
	PageMaxRow = PageNum*BIGSIZE;
	NcPod::getIns()->Set_SegCodeLin(0, PageNum);
	
	mcc->SetAutoRunFlag(false);
	mcc->ClearAutoText();
	mcc->ClearBuffer();

	int rowCount = 0;
	if (PageNum < FileCodeCount / BIGSIZE)
		rowCount = BIGSIZE;
	else
		rowCount = FileCodeCount%BIGSIZE;
	ProgressDialog.show();
	ProgressDialog.setRange(0, rowCount);
	ProgressDialog.hidecancel();
	QApplication::processEvents();

	int curRow = 0;
	QString line;
	int rowNum = 1;
	while (!in.atEnd() && rowNum <= BIGSIZE)
	{
		if ((rowCount / 50 > 0) && (curRow++ % (rowCount / 50) == 0)) {
			ProgressDialog.setValue(curRow++);
			QApplication::processEvents();
		}
		line = in.readLine();
		if (line.simplified().isEmpty())
			continue;

		w->getAutoWork()->TableRowList.push_back(line);
		if (!pAnalysisG.GetValidline(line, PageMaxRow+rowNum++)) {//不支持的代码  不加工//检测G代码是否有效 .插入点 加载文件显示刀路	
			ProgressDialog.hide();
			DlgWarnMess* dlg = new DlgWarnMess(pAnalysisG.errorMsg);

			mcc->ClearAutoText();
			pAnalysisG.clear();
			w->getAutoWork()->clear();
			SammonFunc::RunShow = 0;
			SammonFunc::PauseShow = 0;
			SammonFunc::NextShow = 0;
			SammonFunc::isLoading = 0;
			SammonFunc::Getins()->Loading = 0;
			return;
		}
		mcc->SendAutoText(line);
	}
	if (PageNum < FileCodeCount / BIGSIZE) {
		mcc->SendAutoText(QString("M00 M789"));
	}
	else {
		mcc->SendAutoText(QString("M30"));
		InsertCodeInEnd();
	}
	ProgressDialog.hide();
	SammonFunc::Getins()->Loading = 0;
}

void s_OpenFile::LoadFomeStartLine(int index)
{
	SammonFunc::Getins()->Loading = 1;
	ProgressDialog.show();
	QApplication::processEvents();
	QApplication::processEvents();
	w->getAutoWork()->clear();
	SammonFunc::Getins()->IndexRrcod = index;


	PageNum = index;
	PageMaxRow = PageNum*BIGSIZE;
	NcPod::getIns()->Set_SegCodeLin(0, PageNum);
	
	mcc->SetAutoRunFlag(false);
	mcc->ClearAutoText();
	mcc->ClearBuffer();

	int rowCount = 0;
	if (PageNum < FileCodeCount / BIGSIZE)
		rowCount = BIGSIZE;
	else
		rowCount = FileCodeCount%BIGSIZE;

	ProgressDialog.hidecancel();
	ProgressDialog.setRange(0, rowCount);
	QApplication::processEvents();

	int curRow = 0;
	int rowNum = 1;
	QString line;
	if (index == 0) {
		rowNum = 1 + InsertCodeInStart();
	}

	in.seek(PagePos[index]);
	while (!in.atEnd() && rowNum <= BIGSIZE)
	{
		if ((rowCount / 50 > 0) && (curRow++ % (rowCount / 50) == 0)) {
			ProgressDialog.setValue(curRow++);
			QApplication::processEvents();
		}
		line = in.readLine();
		if (line.simplified().isEmpty())
			continue;

		w->getAutoWork()->TableRowList.push_back(line);
		if (!pAnalysisG.GetValidline(line, PageMaxRow +rowNum++)) {//不支持的代码  不加工//检测G代码是否有效 .插入点 加载文件显示刀路	
			ProgressDialog.hide();
			DlgWarnMess* dlg = new DlgWarnMess(pAnalysisG.errorMsg);

			mcc->ClearAutoText();
			pAnalysisG.clear();
			w->getAutoWork()->clear();
			SammonFunc::RunShow = 0;
			SammonFunc::PauseShow = 0;
			SammonFunc::NextShow = 0;
			SammonFunc::isLoading = 0;
			SammonFunc::Getins()->Loading = 0;
			return;
		}
		mcc->SendAutoText(line);
	}
	if (PageNum < FileCodeCount / BIGSIZE) {
		mcc->SendAutoText(QString("M00 M789"));
	}
	else {
		mcc->SendAutoText(QString("M30"));
		InsertCodeInEnd();
	}
	ProgressDialog.hide();
	emit SammonFunc::Getins()->startLineloadOver();
	SammonFunc::Getins()->Loading = false;
}

void s_OpenFile::LoadDXFCode(QTextStream& stream,QString DXFname,int dxfrowsize)
{	
		ProgressDialog.show();
		QApplication::processEvents();
		QApplication::processEvents();

		FileCodeCount = dxfrowsize;

		SammonFunc::TCodeMap.clear();
		SammonFunc::Getins()->IndexRrcod = 0;
		LogManager::getIns()->appendLog(QStringLiteral("装载文件：") + DXFname);


		w->getAutoWork()->clear();
		w->getAutoWork()->setFileName(fileName);

		mcc->ClearAutoText();
		mcc->ClearBuffer();
		mcc->SetAutoRunFlag(false);
		pAnalysisG.clear();
		neetBreak = false;
		PageMaxRow = 0;

		SammonFunc::IsPause = false;
		int rowCount = 0;
		
		bool isBigFile = false;

		if (dxfrowsize >= BIGSIZE) {
			isBigFile = true;
		}

	
		int curRow = 0;

		ProgressDialog.setRange(0, rowCount);
		QApplication::processEvents();
		QString line;

		int rowNum = 1;//	用于设置SammonFunc::MCodeMap 的 key

		stream.seek(0);
		while (!stream.atEnd() && rowNum <= BIGSIZE)
		{
			if (neetBreak) {//点击取消
				ProgressDialog.hide();;
				mcc->ClearAutoText();
				pAnalysisG.clear();
				w->getAutoWork()->clear();
				file.close();
				SammonFunc::RunShow = 0;
				SammonFunc::PauseShow = 0;
				SammonFunc::NextShow = 0;
				SammonFunc::isLoading = 0;
				return;
			}

			if ((rowCount / 50 > 0) && (curRow++ % (rowCount / 50) == 0)) {
				ProgressDialog.setValue(curRow++);
				QApplication::processEvents();
			}
			line = stream.readLine();
			if (line.isEmpty())
				continue;

			w->getAutoWork()->TableRowList.push_back(line);
			mcc->SendAutoText(line);
		}
		if (isBigFile) {
			mcc->SendAutoText(QString("M00 M789"));
		}
		else {
			file.close();
	//		mcc->SendAutoText(QString("M00"));
			mcc->SendAutoText(QString("M30"));
		}
		SammonFunc::RunShow = true;
		SammonFunc::PauseShow = 0;
		SammonFunc::NextShow = 0;
		SammonFunc::isLoading = true;
		SammonFunc::StartLine = -1;
		emit signal_fileLoad();
		ProgressDialog.hide();

	
	SammonFunc::Getins()->Loading = false;


}

int s_OpenFile::InsertCodeInStart(bool GetValue)
{
	if(GetValue)
		return 0;
	mcc->SendAutoText(QString("%"));
	w->getAutoWork()->TableRowList.push_back("%");
	return 1;
}

int s_OpenFile::InsertCodeInEnd(bool GetValue)
{
	if(GetValue)
		return 0;
	//add Code
	return 0;
}
