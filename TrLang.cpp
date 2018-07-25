#include "TrLang.h"
#include "qfile.h"
#include "QTextStream"
TrLang * TrLang:: ins=NULL;
TrLang::TrLang(QObject *parent)
	: QObject(parent)
{
}

TrLang::~TrLang()
{
}

bool TrLang::Read(QString filename)
{
	LangList[0].clear();
	LangList[1].clear();
	QFile file(filename);
	if (file.open(QIODevice::ReadOnly))
	{
		QTextStream in(&file);
		while (!in.atEnd()) {
			LangList[0] << in.readLine();
			LangList[1] << in.readLine();
		}
		return true;
	}
	return false;
}
