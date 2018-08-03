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
int bMachineReturn = 0;//�ػ���ԭ��
int bWorkpieceReturn = 0;//���������0
HWND hwnd;
Samcon* w=NULL;
bool isSimulation = 0; //�Ƿ��Ƿ����
int VersionType = 1;//  1��׼�汾,2:8�ŵ�,4��4����,6:���ϻ�.
bool is6Axis = 0;//�Ƿ���6 ��  //ctrlHand.h
bool isFull = 0;//Ĭ��ȫ��
bool IsPC = 1;//�Ƿ���PC������
int VType4 = 1;//VersionType==4    0  ����4�ѵ��� 1 ���ϻ��汾
void SetVersion() {
	int Ptype;
	NcPod::getIns()->Get_CardTyp(0, &VersionType, &Ptype);//����� ���Ҫע��
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
		return QMessageBox::information(0, 0, QStringLiteral("ֻ������һ������ʵ������     "));
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

		
		//��ȡ��mccdll��ע��  	
		system(UnRegsvr.toStdString().c_str());
		//��ע��Mcc
		system(Regsvr.toStdString().c_str());
		//���com��ʼ��ʧ��
		mcc = new mccdll::MotionControlCard;


		if (!mcc->GetComRegFlag()) {
			delete mcc;
			QFile::remove((path + "/SysPara.txt").toStdString().c_str());
			QFile::copy(path + "/SysPara.bak", path + "/SysPara.txt");
			mcc = new mccdll::MotionControlCard;
			if (!mcc->GetComRegFlag()) {
				return QMessageBox::information(0, 0, Regsvr + QStringLiteral("ע��ʧ�ܣ����Թ���ԱȨ�����д���� "));
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
		QMessageBox::information(0, "Warning", TrLang::text(92), QMessageBox::Ok); //����� ���Ҫע��
		return 0; //����� ���Ҫע��
	}
#endif // !_DEBUG

	w = new Samcon;
	w->setWindowTitle("70NC-NC2");
	w->VersionConversion(is6Axis, isFull);/////////////
	hwnd = (HWND)w->winId();
	NcPod::getIns()->SetFunc();
	NcPod::getIns()->SpindleAlarm();
	////��ʼ�� PHBX.dll	  0 - �ɹ�,100:USBδ��,	101:USB ���ʹ���.102 : USB���մ���.103 : ��������."
	PHBX::getIns()->Xinit_f();
	int code = PHBX::getIns()->XOpen_f(hwnd);
	if (code == 0)
		PHBX::getIns()->isInitOver = true;


	w->setWindowFlags(Qt::FramelessWindowHint);

	if (isFull) {
		QWindowsWindowFunctions::setHasBorderInFullScreen(w->windowHandle(), true);//��Ҫ�����openglwidget ȫ����bug
		w->showFullScreen();
	}
	else {
		w->show();
	}
	
	w->ResetLanguage();
	mcc->SetFeedrateMultiple(3000);
	return a.exec();
}
