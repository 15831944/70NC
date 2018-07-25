#include"ncpod.h"
#include"ReadIni.h"
#include "QModelIndex "
#include"CommonTools.h"
#include "samcon.h"
#include "ctrlhand.h"
#include "ResetAxis.h"
#include "TrGCode.h"
#include "LogManager.h"
#include "MccTools.h"
extern ReadIni readIni;
NcPod* NcPod::ncpod =NULL;
QLibrary*  NcPod::lib = NULL;
extern HWND hwnd;
extern Samcon *w;
extern int VersionType;
void  __stdcall NcPod:: _DoButton(short type) {
	int Feedvalue = mcc->GetMultiple(0);
	int Spindlevalue = mcc->GetSpindleInformation(3);//主轴倍率
	switch (type)
	{
	case 108://0-150
		if (Feedvalue + 5 >= 0 && Feedvalue + 5 <= 150)
			w->SetFeedrate(Feedvalue + 5);
		else
			w->SetFeedrate(150);
		break;
	case 109:	
		if (Feedvalue - 5 >= 0 && Feedvalue - 5 <= 150)
			w->SetFeedrate(Feedvalue - 5);
		else
			w->SetFeedrate(0);
		break;
	case 307:
		w->getCtrlHand()->NcPodMove(1,0,"X");
		break;
	case 308:
		w->getCtrlHand()->NcPodMove(-1, 0, "X");
		break;
	case 309:
		w->getCtrlHand()->NcPodMove(1, 1, "Y");
		break;
	case 310:
		w->getCtrlHand()->NcPodMove(-1, 1, "Y");
		break;
	case 311:
		w->getCtrlHand()->NcPodMove(1, 2, "Z");
		break;
	case 312:
		w->getCtrlHand()->NcPodMove(-1, 2, "Y");
		break;
	case 1000:
		w->ncpodStart();
		break;
	case 1001:
		w->ncpodPause();
		break;
	case 1002:
		w->ncpodRewind();
		break;
	case 1003:
		w->ncpodStop();
		break;
	case 1021:
		w->ncpodReset();
		break;
	case 1022:
		w->getResetAxis()->ncpodRefer(0); 
		break;
	case 1023:
		w->getResetAxis()->ncpodRefer(1);
		break;
	case 1024:
		w->getResetAxis()->ncpodRefer(2); 
		break;
	case 1025:
		w->getResetAxis()->ncpodRefer(3);
		break;
	case 1026:
		w->getResetAxis()->ncpodRefer(4);
		break;
	case 1027:
		w->getResetAxis()->ncpodRefer(5); 
		break;
	case 163://0-100
		if (Spindlevalue + 5 >= 0 && Spindlevalue + 5 <= 100)
			w->SetSpindle(Spindlevalue + 5);
		else
			w->SetSpindle(100);
		break;
	case 164:
		if (Spindlevalue - 5 >= 0 && Spindlevalue - 5 <= 100)
			w->SetSpindle(Spindlevalue - 5);
		else
			w->SetSpindle(0);
		break;
	case 110:
		w->ncpodSpindleCW();
		break;
	}
}
void NcPod::SpindleAlarm()
{
	if (VersionType == 1)
		NcPod::getIns()->Set_IoIn_Mod(0, 13, 6, 0, 1);
	else if (VersionType == 2) {
		//NcPod::getIns()->Set_IoIn_Mod(0, 7, 6, 0, 1);
	}
	else if (VersionType == 4) {
		NcPod::getIns()->Set_IoIn_Mod(0, 7, 6, 0, 1);
	}
	else {
		NcPod::getIns()->Set_IoIn_Mod(0, 13, 6, 0, 1);
	}

}
void NcPod::SpindleAlarmV2(bool isQIgang,bool en)
{
	if(isQIgang)
		NcPod::getIns()->Set_IoIn_Mod(0, 7, 6, 0, en);
	else
		NcPod::getIns()->Set_IoIn_Mod(0, 7, 6, 0, 1);
}
void  __stdcall NcPod::_SetDRO(short type, double value) {

	switch (type)
	{
	case 74:
		
		break;
	case 83:
		mcc->SetSeekZero(0, value);
		break;
	case 84:
		mcc->SetSeekZero(1, value); 
		break;
	case 85:
		mcc->SetSeekZero(2, value); 
		break;
	case 86:
		mcc->SetSeekZero(3, value); 
		break;
	case 87:
		mcc->SetSeekZero(4, value); 
		break;
	case 88:
		mcc->SetSeekZero(5, value); 
		break;
	case 821:
		break;
	case 800:
		w->setWorkcoodr(12, value);
		break;
	case 801:
		w->setWorkcoodr(13, value);
		break;
	case 802:
		w->setWorkcoodr(14, value);
		break;
	case 803:
		w->setWorkcoodr(15, value);
		break;
	case 804:
		w->setWorkcoodr(16, value);
		break;
	case 805:
		w->setWorkcoodr(17, value);
		break;
	case 818:
		w->ncpodSet818(value);
		break;
	case 1001:
		readIni.SetToolsThickness(QString::number(value));
		break;
	case 819:
		//不支持， 用code 
		break;
	case 820://不支持， 用code 
		break;
	case 1200://不支持
		break;
	case 1201:
		w->ignoreToolChange(newT);
		break;
	case 1202:
		break;
	case 1210:
		readIni.SetMProbeWorkX(value);
		break;
	case 1211:
		readIni.SetMProbeWorkY(value);
		break;
	case 1221://T9刀长
		mcc->SetParameterValue(266, value);
		break;
	case 1222://T10刀长
		mcc->SetParameterValue(268, value);
		break;
	case 1223://T11刀长
		mcc->SetParameterValue(270, value);
		break;
	case 1224://T12刀长
		mcc->SetParameterValue(272, value);
		break;
	case 1225://T13刀长
		mcc->SetParameterValue(274, value);
		break;
	case 1226://T14刀长
		mcc->SetParameterValue(276, value);
		break;
	case 1227://T15刀长
		mcc->SetParameterValue(278, value);
		break;
	case 1228://T16刀长
		mcc->SetParameterValue(280, value);
		break;
	case 1321:
		mcc->SetParameterValue(250, value);//T1刀长
		break;
	case 1322:
		mcc->SetParameterValue(252, value);
		break;
	case 1323:
		mcc->SetParameterValue(254, value);
		break;
	case 1324:
		mcc->SetParameterValue(256, value);
		break;
	case 1325:
		mcc->SetParameterValue(258, value);
		break;
	case 1326:
		mcc->SetParameterValue(260, value);
		break;
	case 1327:
		mcc->SetParameterValue(262, value);
		break;
	case 1328:
		mcc->SetParameterValue(264, value);
		break;
	case 1334:
		break;
	case 1335:
		break;
	case 1336:
		break;
	}
	
	mcc->SaveParameterValue();
}
double  __stdcall NcPod::_GetDRO(short type) {
	
	double value = -11.11;
	switch (type)
	{
	case 74:
		value = w->ncpodSindleoverride();//主轴设定值
		break;
	case 83:
		value = mcc->GetWorkpieceCoordinate(0);
		break;
	case 84:
		value = mcc->GetWorkpieceCoordinate(1);
		break;
	case 85:
		value = mcc->GetWorkpieceCoordinate(2);
		break;
	case 86:
		value = mcc->GetWorkpieceCoordinate(3);
		break;
	case 87:
		value = mcc->GetWorkpieceCoordinate(4);
		break;
	case 88:
		value = mcc->GetWorkpieceCoordinate(5);
		break;
	case 821:
		value = w->ncpodFeedrateoverride();
		break;
	case 800:
		value = mcc->GetWorkpieceCoordinate(0);
		break;
	case 801:
		value = mcc->GetWorkpieceCoordinate(1);
		break;
	case 802:
		value = mcc->GetWorkpieceCoordinate(2);
		break;
	case 803:
		value = mcc->GetWorkpieceCoordinate(3);
		break;
	case 804:
		value = mcc->GetWorkpieceCoordinate(4);
		break;
	case 805:
		value = mcc->GetWorkpieceCoordinate(5);
		break;
	case 818:
		value = w->ncpodFeedrate();
		break;
	case 1001:	
		value = readIni.GetToolsThickness().toDouble();
		break;
	case 819:
		if (mcc->GetGmode(1) == "G00")
			value = 0;
		else if (mcc->GetGmode(1) == "G01")
			value = 1;
		break;
	case 820:
		if (mcc->GetGmode(1) == "G90")
			value = 90;
		else if (mcc->GetGmode(1) == "G91")
			value = 91;
		break;
	case 1200:
		value = readIni.GetTool();
		break;
	case 1201:
		value = newT;
		break;
	case 1202:
	{
		//RUN:1,Pause:2,Idle:0
		if (w->MCodeFromMDI)
			value = 0;
		else
			value = 1;
		if (SammonFunc::IsPause)
			value = 2;
	}
		break;
	case 1204:
		value = readIni.GetZCloseValue();
		break;
	case 1205:
		value = readIni.GetTuiLiaoStarX();
		break;
	case 1206:
		value = readIni.GetTuiLiaoStarY();
		break;
	case 1207:
		value = readIni.GetTuiLiaoEndX();
		break;
	case 1208:
		value = readIni.GetTuiLiaoEndY();
		break;
	case 1209:
		value = readIni.GetMWaitSignalItme() >= 1 ? readIni.GetMWaitSignalItme() : 1;
		break;
	case 1210:
		value = readIni.GetMProbeWorkX();
		break;
	case 1211:
		value = readIni.GetMProbeWorkY();
		break;
	case 1221://T9刀长
		value = mcc->GetParameterValue(266);
		break;
	case 1222://T10刀长
		value = mcc->GetParameterValue(268);
		break;
	case 1223://T11刀长
		value = mcc->GetParameterValue(270);
		break;
	case 1224://T12刀长
		value = mcc->GetParameterValue(272);
		break;
	case 1225://T13刀长
		value = mcc->GetParameterValue(274);
		break;
	case 1226://T14刀长
		value = mcc->GetParameterValue(276);
		break;
	case 1227://T15刀长
		value = mcc->GetParameterValue(278);
		break;
	case 1228://T16刀长
		value = mcc->GetParameterValue(280);
		break;
	case 1321:
		value = mcc->GetParameterValue(250);
		break;
	case 1322:
		value = mcc->GetParameterValue(252);
		break;
	case 1323:
		value = mcc->GetParameterValue(254);
		break;
	case 1324:
		value = mcc->GetParameterValue(256);
		break;
	case 1325:
		value = mcc->GetParameterValue(258);
		break;
	case 1326:
		value = mcc->GetParameterValue(260);
		break;
	case 1327:
		value = mcc->GetParameterValue(262);
		break;
	case 1328:
		value = mcc->GetParameterValue(264);
		break;
	case 1334:
		value = readIni.GetFixedX().toDouble();
		break;
	case 1335:
		value = readIni.GetFixedY().toDouble();
		break;
	case 1336:
		value = readIni.GetZToolSettingSpeed().toDouble();
		break;
	case 1337:
		value = readIni.GetStaetZ().toDouble();
		break;
	case 1300:
		if (VersionType > 1) {
			value = readIni.GetT1X().toDouble();
		}
		break;
	case 1301:
		if (VersionType > 1) {
			value = readIni.GetT1Y().toDouble();
		}
		break;
	case 1302:
		if (VersionType > 1) {
			value = readIni.GetT1Z().toDouble();
		}
		break;
	case 1303:
		if (VersionType > 1) {
			value = readIni.GetT2X().toDouble();
		}
		break;
	case 1304:
		if (VersionType > 1) {
			value = readIni.GetT2Y().toDouble();
		}
		break;
	case 1305:
		if (VersionType > 1) {
			value = readIni.GetT2Z().toDouble();
		}
		break;
	case 1306:
		if (VersionType > 1) {
			value = readIni.GetT3X().toDouble();
		}
		break;
	case 1307:
		if (VersionType > 1) {
			value = readIni.GetT3Y().toDouble();
		}
		break;
	case 1308:
		if (VersionType > 1) {
			value = readIni.GetT3Z().toDouble();
		}
		break;
	case 1309:
		if (VersionType > 1) {
			value = readIni.GetT4X().toDouble();
		}
		break;
	case 1310:		
		if (VersionType > 1) {
		value = readIni.GetT4Y().toDouble();
		}
		break;
	case 1311:
		if (VersionType > 1) {
			value = readIni.GetT4Z().toDouble();
		}
		break;
	case 1312:
		if (VersionType > 1&& VersionType !=4) {
			value = readIni.GetT5X().toDouble();
		}
		break;
	case 1313:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT5Y().toDouble();
		}
		break;
	case 1314:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT5Z().toDouble();
		}
		break;
	case 1315:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT6X().toDouble();
		}
		break;
	case 1316:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT6Y().toDouble();
		}
		break;
	case 1317:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT6Z().toDouble();
		}
		break;
	case 1318:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT7X().toDouble();
		}
		break;
	case 1319:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT7Y().toDouble();
		}
		break;
	case 1320:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT7Z().toDouble();
		}
		break;
	case 1340:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT8X().toDouble();
		}
		break;
	case 1341:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT8Y().toDouble();
		}
		break;
	case 1342:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetT8Z().toDouble();
		}
		break;
	case 1330:
		if (VersionType > 1) {
			value = readIni.GetToolCount().toDouble();
		}
		break;
	case 1331:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetToolReady().toDouble();
		}
		break;
	case 1332:
		if (VersionType > 1 && VersionType != 4) {
			if (readIni.GetToolIsOnY())
				value = 2;
			else
				value = 1;
		}
		break;
	case 1333:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetToolInFeed().toDouble();
		}
		break;
	case 1338:
		if (VersionType > 1) {
			value = readIni.GetToolSafeZ().toDouble();
		}
		break;
	case 1339:
		if (VersionType > 1 && VersionType != 4) {
			value = readIni.GetToolChangeUpZ().toDouble();
		}
		break;
	case 1343:
		value = readIni.GetT9X().toDouble();
		break;
	case 1344:
		value = readIni.GetT9Y().toDouble();
		break;
	case 1345:
		value = readIni.GetT9Z().toDouble();
		break;
	case 1346:
		value = readIni.GetT10X().toDouble();
		break;
	case 1347:
		value = readIni.GetT10Y().toDouble();
		break;
	case 1348:
		value = readIni.GetT10Z().toDouble();
		break;
	case 1349:
		value = readIni.GetT11X().toDouble();
		break;
	case 1350:
		value = readIni.GetT11Y().toDouble();
		break;
	case 1351:
		value = readIni.GetT11Z().toDouble();
		break;
	case 1352:
		value = readIni.GetT12X().toDouble();
		break;
	case 1353:
		value = readIni.GetT12Y().toDouble();
		break;
	case 1354:
		value = readIni.GetT12Z().toDouble();
		break;
	case 1355:
		value = readIni.GetT13X().toDouble();
		break;
	case 1356:
		value = readIni.GetT13Y().toDouble();
		break;
	case 1357:
		value = readIni.GetT13Z().toDouble();
		break;
	case 1358:
		value = readIni.GetT14X().toDouble();
		break;
	case 1359:
		value = readIni.GetT14Y().toDouble();
		break;
	case 1360:
		value = readIni.GetT14Z().toDouble();
		break;
	case 1361:
		value = readIni.GetT15X().toDouble();
		break;
	case 1362:
		value = readIni.GetT15Y().toDouble();
		break;
	case 1363:
		value = readIni.GetT15Z().toDouble();
		break;
	case 1364:
		value = readIni.GetT16X().toDouble();
		break;
	case 1365:
		value = readIni.GetT16Y().toDouble();
		break;
	case 1366:
		value = readIni.GetT16Z().toDouble();
		break;
	case 1203:
		if (VersionType == 2)
			value = readIni.GetTool_In_Enabled_2(-1);
		else if (VersionType == 4)
			value = readIni.GetTool_In_Enabled_4(-1);
	}
	return value;
}
void __stdcall  NcPod:: _Code(const char* mdi) {
	
	QString curline(mdi);
	LogManager::getIns()->appendLog("code:"+curline);
	if (curline.contains("G31") || curline.contains("g31")) {
		QString Code = SammonFunc::GetNumber(curline, 'X', 'x');
		if (!Code.isEmpty()) {
			w->pTrGCode->isG31 = 0;
			w->pTrGCode->G31Coord = Code;
		}
		Code = SammonFunc::GetNumber(curline, 'Y', 'y');
		if (!Code.isEmpty()) {
			w->pTrGCode->isG31 = 1;
			w->pTrGCode->G31Coord = Code;
		}
		Code = SammonFunc::GetNumber(curline, 'Z', 'z');
		if (!Code.isEmpty()) {
			w->pTrGCode->isG31 = 2;
			w->pTrGCode->G31Coord = Code;
		}
		Code = SammonFunc::GetNumber(curline, 'F', 'f');
		if (!Code.isEmpty()) {
			w->pTrGCode->G31FSpeed = Code;
		}
		if (w->pTrGCode->isG31 != -1) {
			SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 0, 0);
		}
		else {
			
		}
		return;
	}
	MccTools::SendMDI(curline);
}
void NcPod::SetHomeLmt(bool isInit)
{
	if (isInit) {
		NcPod::getIns()->SetHomeLmtE(0, 0, 0, readIni.GetXOriginLmt());
		NcPod::getIns()->SetHomeLmtE(0, 1, 1, readIni.GetYOriginLmt());
		NcPod::getIns()->SetHomeLmtE(0, 2, 2, readIni.GetZOriginLmt());
		return;
	}
	int homeLmtFlag = w->homeLmtFlag;
	if (homeLmtFlag == -1)return;

	if (w->IsMDIRuningInItmer())return;
	if (mcc->IniPnowFlg() != 0 || mcc->GetGmode(11).toInt() != 4)
		return;
	static int i = 0;
	if (i++ <= 3)
		return;
	i = 0;

	
	switch (homeLmtFlag)
	{
	case 0:
		NcPod::getIns()->SetHomeLmtE(0, 0, 0, readIni.GetXOriginLmt());
		w->homeLmtFlag = -1;
		break;
	case 1:
		NcPod::getIns()->SetHomeLmtE(0, 1, 1, readIni.GetYOriginLmt());
		w->homeLmtFlag = -1;
		break;
	case 2:
		NcPod::getIns()->SetHomeLmtE(0, 2, 2, readIni.GetZOriginLmt());
		w->homeLmtFlag = -1;
		break;
	}
	
	
	
}

void NcPod::SetFunc()
{
	SetFunDoButto(&NcPod::_DoButton);
	SetFunSetDR(&NcPod::_SetDRO);
	SetFunGetDR(hwnd, &NcPod:: _GetDRO);
	SetFunCod(&NcPod::_Code);
}

NcPod::NcPod()
{
}

NcPod::~NcPod()
{
}
