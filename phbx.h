#pragma once
#include "QWINDOWDEFS_WIN.H"
#include "QLibrary"
typedef void(__stdcall*Xinit)();
typedef long(__stdcall*XOpen)(HWND);
typedef long(__stdcall*XSendOutput)(uchar*, uchar*);
typedef long(__stdcall*XGetInput)(char*, char*);
typedef long(__stdcall*XClose)();
class PHBX
{
public:
	static PHBX* getIns() {
		if (ins == NULL) {
			lib = new QLibrary("PHBX.dll");
			ins = new PHBX();
			
		}
		return ins;
	}
	static void release() {
		if (ins) {
			uchar buff[2] = { 0x00,0x00 };
			uchar size = 2;
			ins->XSendOutput_f(buff,&size);
			ins->XClose_f();
			delete ins;
			delete lib;
		}
	}
	Xinit  Xinit_f = (Xinit)lib->resolve("Xinit");
	XOpen    XOpen_f = (XOpen)lib->resolve("XOpen");
	XSendOutput    XSendOutput_f = (XSendOutput)lib->resolve("XSendOutput");
	XGetInput    XGetInput_f = (XGetInput)lib->resolve("XSendOutput");
	XClose  XClose_f = (XClose)lib->resolve("XClose");
	bool isInitOver = false;
private:
	
	static PHBX* ins;
	static QLibrary* lib;
	PHBX();
	~PHBX();
};

