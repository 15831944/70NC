#pragma once

#include <QObject>

class MccTools : public QObject
{
	Q_OBJECT

public:
	MccTools(QObject *parent);
	~MccTools();
	static void SendMDI(QString str);
	static void run();
	static void setStart(int row = 1);
	static void RunStartLine(int row = 1);
	static void SwitchAutoMode();
	static int workState();
	static bool isIdle();
};
