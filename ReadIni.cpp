#include "ReadIni.h"
#include"CommonTools.h"
ReadIni::ReadIni(QObject *parent)
	: QObject(parent)
{

	Parameter_ini = new QSettings("Parameter.ini", QSettings::IniFormat);
	LoadFileList();
}

ReadIni::~ReadIni()
{
	delete Parameter_ini;
}

void ReadIni::SetOpenRecentFile(QString value)
{
	if (fileList.contains(value))
	{
		for (int i = 0; i < FILESIZE; i++) {
			if (fileList[i] == value) {
				fileList.move(i, 0);
			}
		}

	}
	else {
		fileList.push_front(value);
		fileList.pop_back();
	}
	SaveFileList();
}

int ReadIni::GetTool_In_Enabled_4(int pos)
{
	int value = Parameter_ini->value("Tools/Tool_In_Enabled_4").toInt();
	if (pos == -1)
		return value;
	else
		return  SammonFunc::Getins()->readBit(value, pos);
}
void ReadIni::SetTool_In_Enabled_4(int pos, int Enabled)
{
	int value = GetTool_In_Enabled_4();
	SammonFunc::Getins()->writeBit(value, pos, Enabled);
	Parameter_ini->setValue("Tools/Tool_In_Enabled_4", value);
}

int ReadIni::GetTool_In_Enabled_2(int pos)
{
	int value = Parameter_ini->value("Tools/Tool_In_Enabled_2").toInt();
	if (pos == -1)
		return value;
	else
		return  SammonFunc::Getins()->readBit(value, pos);
}
void ReadIni::SetTool_In_Enabled_2(int pos, int Enabled)
{
	int value = GetTool_In_Enabled_2();
	SammonFunc::Getins()->writeBit(value, pos, Enabled);
	Parameter_ini->setValue("Tools/Tool_In_Enabled_2", value);
}


void ReadIni::LoadFileList()
{
	QString s, str;
	for (int i = 1; i <= FILESIZE; i++) {
		str = QString("OpenRecent/File%1").arg(i);
		s = Parameter_ini->value(str).toString();
		fileList.push_back(s);
	}
}

void ReadIni::SaveFileList()
{
	QString str;
	for (int i = 1; i <= FILESIZE; i++) {
		str = QString("OpenRecent/File%1").arg(i);
		Parameter_ini->setValue(str, fileList[i-1]);
	}
}
