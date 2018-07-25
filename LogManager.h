#pragma once

#include <QObject>
#include "QFile"
#include "QTime"
#include "QTextStream.h"
class LogManager : public QObject
{
	Q_OBJECT

public:
	static void release() {	delete logm;	}
	static LogManager* getIns() {
		if (!logm)
			logm = new LogManager();		
		return logm;
	}
	void appendLog(QString log);
	void debugLog(QString log);
private:
	static LogManager* logm;
	LogManager(QObject *parent = 0);
	~LogManager();
	QFile logFile;
	QTextStream outstream;

signals: void updateLog(QString, QString);
};