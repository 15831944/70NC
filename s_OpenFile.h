#pragma once

#include <QObject>
#include <QPlainTextEdit>
#include "AutoWork.h"
#include "AnalysisG.h"
#include"qthread.h"
#include "DlgMyProcessDlg.h"
#include "QThread"
#include <qtextstream.h>
//////读取G代码文件
class s_OpenFile : public QObject
{
	Q_OBJECT

public:
	s_OpenFile(QObject *parent = 0);
	~s_OpenFile();
	void LoadFile(AutoWork *, QString fn="");
	void LoadNext();
	void LoadFomeStartLine(int row);

	void LoadDXFCode(QTextStream& stream, QString DXFname, int);
	AnalysisG pAnalysisG;
	int PageMaxRow = 0;//每段 最大 行号
	int PageNum = 0;//段号
	int FileCodeCount = 0;//总行数
	int InsertCodeInStart(bool GetValue=false);
	int InsertCodeInEnd(bool GetValue=false);
	QList<int> PagePos;//每段的文件位置指针
	QString getFileName() { return fileName; }
signals:	void signal_fileLoad();
signals:	void SendValue(int);
signals:	void SendRange(int,int);
	
private:
	DlgMyProcessDlg ProgressDialog;
	bool isNew = true;
	QString fileName;
	QFile	file;
	QTextStream in;
	bool neetBreak = false;
	QThread mThread;
	
};
