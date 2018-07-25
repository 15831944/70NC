#include "LogManager.h"
#include"QDir"
#include<QCoreApplication>
LogManager*LogManager::logm = NULL;

LogManager::LogManager(QObject *parent)
	:outstream(&logFile), QObject(parent)
{
	//QDir dir(".");
	//if (!dir.exists("log")) {
	//	dir.mkpath("log");
	//}
	//QString  fileName = "./log/";
	//fileName += QDateTime::currentDateTime().toString("yyyy-MM-dd  HH-mm-ss");
	//fileName += ".txt";
	QString  fileName = "./log.txt";
	logFile.setFileName(fileName);
	logFile.open(QIODevice::Append);

	if (logFile.size() > 1024 * 1024){
		logFile.resize(0);
	}

}

LogManager::~LogManager()
{
	logFile.close();
}

void LogManager::debugLog(QString log) {
#ifdef  _DEBUG 
	QString str = QDateTime::currentDateTime().toString("yyyy/MM/dd HH-mm-ss   ");
	outstream << str;
	outstream << " : ";
	outstream << log << endl;;
	emit updateLog(str, log);
#endif
}

void LogManager::appendLog(QString log)
{
//#ifndef  _DEBUG 
	QString str = QDateTime::currentDateTime().toString("yyyy/MM/dd HH-mm-ss   ");
	outstream << str;
	outstream << " : ";
	outstream << log << endl;;
	emit updateLog(str, log);
//#endif
}
