#include "Samcon.h"
#include <QtWidgets/QApplication>
#include "CommonTools.h"
#include "ReadIni.h"
#include"DataDefine.h"
#include "ncpod.h"
#include <QSharedMemory>
#include <PHBX.H>
#include <qwindow.h>
#include <QtPlatformHeaders/QWindowsWindowFunctions> 
#include <QDesktopWidget> 
#include "TrLang.h"

mccdll::MotionControlCard* mcc=NULL;
QString MyStyle = "";
ReadIni readIni;
int bMachineReturn = 0;//回机床原点
int bWorkpieceReturn = 0;//工件坐标会0
HWND hwnd;
Samcon* w=NULL;
bool isSimulation = 0; //是否是仿真版
int VersionType = 1;//  1标准版本,2:8排刀,4：4工序,6:开料机.
bool is6Axis = 0;//是否是6 轴  //ctrlHand.h
bool isFull = 0;//默认全屏
bool IsPC = 1;//是否在PC上运行
int VType4 = 1;//VersionType==4    0  正常4把刀， 1 推料机版本
void SetVersion() {
	int Ptype;
	NcPod::getIns()->Get_CardTyp(0, &VersionType, &Ptype);//仿真版 这句要注释
	is6Axis = Ptype == 6;

	if (VersionType == 6) VersionType = 1;
	if (VersionType ==4) {
		if (readIni.GetToolCount().toInt() > 4)
			readIni.SetToolCount(QString("4"));
		VType4 = 1;
	}
	isFull = 0;
	IsPC = 1;
	isSimulation = 0;
#ifdef  _DEBUG
	VersionType = 4;
	is6Axis = 1;
	isFull = 0;
	IsPC = 0;
	VType4 = 1;
#endif //  _DEBUG


	
}

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	//6 Axis
	QSharedMemory shared("70NC-NC2");
	if (shared.attach())
		return QMessageBox::information(0, 0, QStringLiteral("只能运行一个程序实例！！     "));
	shared.create(1);

	{
		QString path = QApplication::applicationDirPath();
		QString UnRegsvr;
		UnRegsvr = "regsvr32  /s /u ";
		UnRegsvr += '"';
		UnRegsvr += path;
		UnRegsvr += "/mccdll.dll";
		UnRegsvr += '"';

		QString Regsvr;
		Regsvr = "regsvr32  /s ";
		Regsvr += '"';
		Regsvr += path;
		Regsvr += "/mccdll.dll";
		Regsvr += '"';

		
		//先取消mccdll的注册  	
		system(UnRegsvr.toStdString().c_str());
		//再注册Mcc
		system(Regsvr.toStdString().c_str());
		//如果com初始化失败
		mcc = new mccdll::MotionControlCard;


		if (!mcc->GetComRegFlag()) {
			delete mcc;
			QFile::remove((path + "/SysPara.txt").toStdString().c_str());
			QFile::copy(path + "/SysPara.bak", path + "/SysPara.txt");
			mcc = new mccdll::MotionControlCard;
			if (!mcc->GetComRegFlag()) {
				return QMessageBox::information(0, 0, Regsvr + QStringLiteral("注册失败，请以管理员权限运行此软件 "));
			}
		}
		else {
			QFile::remove((path + "/SysPara.bak").toStdString().c_str());
			QFile::copy(path + "/SysPara.txt", path + "/SysPara.bak");
		}
	}




	SetVersion();
	TrLang::Ins();
#ifndef _DEBUG
	if (0 == mcc->GetGmode(13).toInt()) {
		QMessageBox::information(0, "Warning", TrLang::text(92), QMessageBox::Ok); //仿真版 这句要注释
		return 0; //仿真版 这句要注释
	}
#endif // !_DEBUG

	w = new Samcon;
	w->setWindowTitle("70NC-NC2");
	w->VersionConversion(is6Axis, isFull);/////////////
	hwnd = (HWND)w->winId();
	NcPod::getIns()->SetFunc();
	NcPod::getIns()->SpindleAlarm();
	////初始化 PHBX.dll	  0 - 成功,100:USB未打开,	101:USB 发送错误.102 : USB接收错误.103 : 参数错误."
	PHBX::getIns()->Xinit_f();
	int code = PHBX::getIns()->XOpen_f(hwnd);
	if (code == 0)
		PHBX::getIns()->isInitOver = true;


	w->setWindowFlags(Qt::FramelessWindowHint);

	if (isFull) {
		QWindowsWindowFunctions::setHasBorderInFullScreen(w->windowHandle(), true);//重要，解决openglwidget 全屏的bug
		w->showFullScreen();
	}
	else {
		w->show();
	}
	
	w->ResetLanguage();
	mcc->SetFeedrateMultiple(3000);
	return a.exec();
}
