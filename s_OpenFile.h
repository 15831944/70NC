#pragma once

#include <QObject>
#include <QPlainTextEdit>
#include "AutoWork.h"
#include "AnalysisG.h"
#include"qthread.h"
#include "DlgMyProcessDlg.h"
#include "QThread"
#include <qtextstream.h>
//////��ȡG�����ļ�
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
	int PageMaxRow = 0;//ÿ�� ��� �к�
	int PageNum = 0;//�κ�
	int FileCodeCount = 0;//������
	int InsertCodeInStart(bool GetValue=false);
	int InsertCodeInEnd(bool GetValue=false);
	QList<int> PagePos;//ÿ�ε��ļ�λ��ָ��
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
