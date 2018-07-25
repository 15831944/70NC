#pragma once
#include "qwindowdefs_win.h"
class NcPod;
typedef int (__stdcall*  XHCmcc_Initial)(int cardno);
typedef int (__stdcall*  Get_Lib_Version)(int cardno);
typedef int (__stdcall*  Set_Pulse_Mode)(int cardno,int value);
typedef int (__stdcall*  Set_Acc)(int cardno,int axis,double value);
typedef int (__stdcall*  Set_StartV)(int cardno,int axis,long value);
typedef int (__stdcall*  Set_MoveSpeed)(int cardno,int axis,double value);
typedef int (__stdcall*  PMove)(int cardno,int axis,int pulse);
typedef int (__stdcall*   StopPMove) (int cardno,int axis);
typedef int (__stdcall*  Sudden_Stop)(int cardno,int axis);
typedef int (__stdcall*   SignalMove)(int cardno,int axis,int Signalio,int lmtpulse,int aftermove,int LmtEn);
typedef int (__stdcall*   Set_Command_Pos)(int cardno,int axis,int abspos);
typedef int (__stdcall*   Get_Command_Pos)(int cardno,int axis,int *pos);
typedef int (__stdcall*   Get_Status)(int cardno,int axis,int *value);
typedef int (__stdcall*   Start_FifoMove)(int cardno);//auto fill and run;
typedef int (__stdcall*   Stop_FifoMove)(int cardno);
typedef int (__stdcall*   Write_Bit)(int cardno,int number,int value);
typedef int (__stdcall*   Get_CodeLine)(int cardno);
typedef int (__stdcall*    Read_Bit)(int cardno,int number);
typedef int (__stdcall*   Set_IoIn_Mode)(int cardno, int ioin, int mode, int logic,int Enalbe);
typedef int (__stdcall*   UnlimtSignal)(int cardnum,int signalnum);
typedef int (__stdcall*   Set_Spindle_Speed) (int cardno,int maxspeed, int currentspeed,int mode);
typedef int (__stdcall*   Fifo_InP_Command)(int cardno,int ComNum,int Para0,int Para1,int Para2,int Para3,int Para4,int Para5,int Para6);
typedef int (__stdcall*   Read_Fifo_State)(int cardno,int *buflength,int* emptylength);
typedef int (__stdcall*   Reset_Fifo)(int cardno);
typedef int (__stdcall*   StopPlug)(int cardno);
typedef int (__stdcall*   SetSoftLmt)(int cardno,int axis,int  absposplus,int  absposminus);
typedef int (__stdcall*  OpenMotoionDevcie)(int cardno );
typedef int (__stdcall*   CloseMotoionDevcie)(int cardno );
typedef int (__stdcall*  Set_Stepper)(int cardno,int axis,double value);
typedef int (__stdcall*   Set_SoftLmtEnalbe)(int cardno,int enalbe);
typedef int (__stdcall*   CloseSpindle)(int cardno);
typedef int (__stdcall*  OpenSpindle)(int cardno,int fwd);
typedef int (__stdcall*   Set_MotorDirLevel)(int cardno,int axis,int Level);
typedef int (__stdcall*  Set_MotorPulsLevel)(int cardno,int axis,int Level);
typedef int (__stdcall*   Set_SpindPulsPerRotate)(int cardno,int sPulsPerRotate);
 typedef int (__stdcall*   GetCardIp)(int cardno,int *icarip);
 typedef int (__stdcall*   SetCardIp)(int cardno,int icarip);
 typedef int (__stdcall*   ReadOutputIo)(int cardno,int *GetIo);
 //2017/6/5

 typedef int(__stdcall*  IsActiveInput)(int cardno, int ionumber);
 typedef void(__stdcall NcPod::*DoButton) (short);
 typedef void (__stdcall NcPod::*SetDRO) (short, double);
 typedef double(__stdcall NcPod::*GetDRO) (short);
 typedef void(__stdcall NcPod::*Code) (const char*);

 typedef void(__stdcall*SetFunDoButton) (DoButton);
 typedef void(__stdcall *SetFunSetDRO) (SetDRO);
 typedef void(__stdcall *SetFunGetDRO) (HWND ,GetDRO);
 typedef void(__stdcall *SetFunCode) (Code);
 typedef void(__stdcall *SetFunReturn) (double,int);
 //2017/7/19
 typedef void(__stdcall *ReadPadKey) (int , int *);
 typedef void(__stdcall *OpenPadDevcie) (int);
 typedef void(__stdcall *ClosePadDevcie) (int);

 //2017-8-16
 typedef void(__stdcall *SetHomeLmtEn) (int,int,int,int);
 typedef int(__stdcall *GetSetDroValue) (int *);
 
 typedef int(__stdcall *Get_SegCodeLine)(int cardno, int *bcodeline, int *tcodeline);
 typedef int(__stdcall *Set_SegCodeLine)(int cardno, int segnum);
 typedef int(__stdcall *GetGodeCmd)(char *strcmd, char length);

 typedef int(__stdcall *RunMacro)(int cardno, const char * macfile);
 typedef int(__stdcall *StopMacro)(int cardno) ;
 typedef int(__stdcall *MacroIsRuning)(int cardno);

 typedef int(__stdcall *setHomeType)(int stoptype, int movetype);
 typedef int(__stdcall *Get_CardType)(int cardno, int *pclass, int *ptype);

 enum NcPodErrorCode {
	 NOETH = -1, //没有连接硬件（以太网卡）
	 OK, //正常
	 DEVICEMV, //设备正在移动
	 DEVICEBUSY, //设备忙
	 LMTLOCK, //设备处于限位状态
	 DEVICEIDLE, //设备处于空闲状态
	 PARAERR,// 参数错误
	 COMERR, //通信错误
 };




#include"qlibrary.h"
#include"qmessagebox.h"
#include "qdebug"
#include "QObject"
  class NcPod {

  public :
	  static void release() {
	
		  ncpod->StopPlu(0);

		  delete lib;
		  delete ncpod;
		
		  
	  }
	  static NcPod* getIns(bool isSimulation =false) {
		  if (ncpod == NULL) {
		
				  lib = new QLibrary("NcPod.dll");
			  ncpod = new NcPod;		  
			  if (!lib->load()) {
				  QMessageBox::information(0, "error", "NcPod.dll err");
			//	  exit(0);
			 }

		  }
		  return ncpod;
	  }

	static void Init() {

		if (getIns()->XHCmcc_Initia(0) != OK) {
			if (getIns()->OpenMotoionDevci(0) != OK) {
				//qDebug() << "Motion card is ok";
			}
			else {
				QMessageBox::information(0, "error", "plerse insert card");
			//	exit(0);
			}
		}
		else {
		//	qDebug() << "Motion card is ok";
		}
	}
	void SetHomeLmt(bool isInit=false);
	void SetFunc();
	SetSoftLmt           SetSoftLm = (SetSoftLmt)lib->resolve("SetSoftLmt");
	XHCmcc_Initial    XHCmcc_Initia=  (XHCmcc_Initial)lib->resolve("XHCmcc_Initial");
	Get_Lib_Version   Get_Lib_Versio=  (Get_Lib_Version)lib->resolve("Get_Lib_Version");
	Set_Pulse_Mode    Set_Pulse_Mod=  (Set_Pulse_Mode)lib->resolve("Set_Pulse_Mode");
	Set_Acc           Set_Ac=  (Set_Acc)lib->resolve("Set_Acc");
	Set_StartV         Set_Start=  (Set_StartV)lib->resolve("Set_StartV");
	Set_MoveSpeed      Set_MoveSpee=  (Set_MoveSpeed)lib->resolve("Set_MoveSpeed");
	PMove              PMov=  (PMove)lib->resolve("PMove");
	StopPMove          StopPMov=  (StopPMove)lib->resolve("StopPMove");
	Sudden_Stop       Sudden_Sto=  (Sudden_Stop)lib->resolve("Sudden_Stop");
	SignalMove         SignalMov=  (SignalMove)lib->resolve("SignalMove");
	Set_Command_Pos        Set_Command_Po=  (Set_Command_Pos)lib->resolve("Set_Command_Pos");
	Get_Command_Pos    Get_Command_Po=  (Get_Command_Pos)lib->resolve("Get_Command_Pos");
	Get_Status          Get_Statu=  (Get_Status)lib->resolve("Get_Status");
	Start_FifoMove      Start_FifoMov=  (Start_FifoMove)lib->resolve("Start_FifoMove");
	Stop_FifoMove       Stop_FifoMov=  (Stop_FifoMove)lib->resolve("Stop_FifoMove");
	Write_Bit           Write_Bi=  (Write_Bit)lib->resolve("Write_Bit");
	Get_CodeLine        Get_CodeLin=  (Get_CodeLine)lib->resolve("Get_CodeLine");
	Read_Bit             Read_Bi=  (Read_Bit)lib->resolve("Read_Bit");
	Set_IoIn_Mode        Set_IoIn_Mod=  (Set_IoIn_Mode)lib->resolve("Set_IoIn_Mode");
	UnlimtSignal        UnlimtSigna=  (UnlimtSignal)lib->resolve("UnlimtSignal");
	Set_Spindle_Speed   Set_Spindle_Spee=  (Set_Spindle_Speed)lib->resolve("Set_Spindle_Speed");
	Fifo_InP_Command     Fifo_InP_Comman=  (Fifo_InP_Command)lib->resolve("Fifo_InP_Command");
	Read_Fifo_State     Read_Fifo_Stat=  (Read_Fifo_State)lib->resolve("Read_Fifo_State");
	Reset_Fifo           Reset_Fif=  (Reset_Fifo)lib->resolve("Reset_Fifo");
	StopPlug             StopPlu=  (StopPlug)lib->resolve("StopPlug");

	OpenMotoionDevcie     OpenMotoionDevci=  (OpenMotoionDevcie)lib->resolve("OpenMotoionDevcie");
	CloseMotoionDevcie   CloseMotoionDevci=  (CloseMotoionDevcie)lib->resolve("CloseMotoionDevcie");
	Set_Stepper           Set_Steppe=  (Set_Stepper)lib->resolve("Set_Stepper");
	Set_SoftLmtEnalbe     Set_SoftLmtEnalb=  (Set_SoftLmtEnalbe)lib->resolve("Set_SoftLmtEnalbe");
	CloseSpindle          CloseSpindl=  (CloseSpindle)lib->resolve("CloseSpindle");
	OpenSpindle            OpenSpindl=  (OpenSpindle)lib->resolve("OpenSpindle");
	Set_MotorDirLevel     Set_MotorDirLeve=  (Set_MotorDirLevel)lib->resolve("Set_MotorDirLevel");
	Set_MotorPulsLevel     Set_MotorPulsLeve=  (Set_MotorPulsLevel)lib->resolve("Set_MotorPulsLevel");
	Set_SpindPulsPerRotate  Set_SpindPulsPerRotat=  (Set_SpindPulsPerRotate)lib->resolve("Set_SpindPulsPerRotate");
	GetCardIp               GetCardIp1=  (GetCardIp)lib->resolve("GetCardIp");
	SetCardIp               SetCardIp1=  (SetCardIp)lib->resolve("SetCardIp");
	ReadOutputIo             ReadOutput=  (ReadOutputIo)lib->resolve("ReadOutputIo");
	//2017/6/5
	IsActiveInput            Isactive = (IsActiveInput)lib->resolve("IsActiveInput");


	SetFunDoButton	SetFunDoButto = (SetFunDoButton)lib->resolve("SetFunDoButton");
	SetFunSetDRO		SetFunSetDR = (SetFunSetDRO)lib->resolve("SetFunSetDRO");
	SetFunGetDRO		SetFunGetDR = (SetFunGetDRO)lib->resolve("SetFunGetDRO");
	SetFunCode		SetFunCod = (SetFunCode)lib->resolve("SetFunCode");
	SetFunReturn		SetFunRetur = (SetFunReturn)lib->resolve("SetFunReturn");
	//2017/7/19
	ReadPadKey		ReadPadKe = (ReadPadKey)lib->resolve("ReadPadKey");
	OpenPadDevcie	OpenPadDevci = (OpenPadDevcie)lib->resolve("OpenPadDevcie");
	ClosePadDevcie	ClosePadDevci = (ClosePadDevcie)lib->resolve("ClosePadDevcie");
	//2017-8-16
	SetHomeLmtEn	SetHomeLmtE=(SetHomeLmtEn)lib->resolve("SetHomeLmtEn");
	GetSetDroValue	GetSetDroValu = (GetSetDroValue)lib->resolve("GetSetDroValue");

	Get_SegCodeLine	Get_SegCodeLin = (Get_SegCodeLine)lib->resolve("Get_SegCodeLine");
	Set_SegCodeLine	Set_SegCodeLin = (Set_SegCodeLine)lib->resolve("Set_SegCodeLine");

	GetGodeCmd	GetGodeCm = (GetGodeCmd)lib->resolve("GetGodeCmd");

	RunMacro	RunMacr = (RunMacro)lib->resolve("RunMacro");
	StopMacro	StopMacr = (StopMacro)lib->resolve("StopMacro");
	MacroIsRuning	MacroIsRunin = (MacroIsRuning)lib->resolve("MacroIsRuning");
	setHomeType	setHomeTyp = (setHomeType)lib->resolve("setHomeType");

	Get_CardType	Get_CardTyp = (Get_CardType)lib->resolve("Get_CardType");
	
	
	void _stdcall _SetDRO(short type, double value);
	double _stdcall  _GetDRO(short type);
	void   _stdcall _Code(const char* mdi);
	void _stdcall   _DoButton(short type);
	void SpindleAlarm(); //主轴报警
	void SpindleAlarmV2(bool isQIgang, bool en);//VersionType == 2 主轴报警;
	





	int		TimePlus = 0;//控制延时，seekZero 延时 会长点
	int  newT = 1;//缓存新的刀具号。。
  private:
	
	  static NcPod* ncpod;
	  static QLibrary* lib;
	  NcPod();  
	  ~NcPod();
	
  };