#pragma once

#include <QObject>
#include <QString>
class TrLang : public QObject
{
	Q_OBJECT
public:
	static TrLang *Ins() {
		if (ins == NULL) {
			ins = new TrLang;
			ins->Read("data/Lang.tr");
		}
		return ins;
	}
	void setLanguageIndxe(int t) { mLanguageIndex = t; }
	QString GetText(int index) {return LangList[mLanguageIndex][index]; }
	static QString text(int index) {return  ins->GetText(index);}
	bool Read(QString);
	bool GetLanguageIndxe() { return mLanguageIndex; }
private:
	static TrLang *ins;
	int mLanguageIndex = 0;
	TrLang(QObject *parent=0);
	~TrLang();
	
	QStringList LangList[2];
};
