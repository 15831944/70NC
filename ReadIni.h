#pragma once

#include <QObject>
#include <qsettings>
#define  FILESIZE 9
class ReadIni : public QObject
{
	Q_OBJECT

public:
	ReadIni(QObject *parent = 0);
	~ReadIni();
	void sync() { Parameter_ini->sync(); }
	bool AxisFlag() { return Parameter_ini->value("Developer/AxisFlag").toBool(); }

	QString GetOpenRecentDir() {return Parameter_ini->value("OpenRecent/Dir").toString();}//最近打开文件路径
	void SetOpenRecentDir(QString value) { Parameter_ini->setValue("OpenRecent/Dir", value);}

	QString GetDXFDir() { return Parameter_ini->value("OpenRecent/DXFDir").toString(); }//最近打开dxf文件路径
	void SetDXFDir(QString value) { Parameter_ini->setValue("OpenRecent/DXFDir", value); }

	QStringList& GetOpenRecentFile() { return fileList; }//最近打开文件
	void SetOpenRecentFile(QString value);


	int GetMWaitSignalItme() { return Parameter_ini->value("Macro/MWaitSignalItme").toInt(); }//宏代码等待延时
	void SetMWaitSignalItme(int value) { Parameter_ini->setValue("Macro/MWaitSignalItme", value); }

	double GetMProbeWorkX() { return Parameter_ini->value("Macro/MProbeWorkX").toDouble(); }//宏代码 对刀位置
	void SetMProbeWorkX(int value) { Parameter_ini->setValue("Macro/MProbeWorkX", value); }
	double GetMProbeWorkY() { return Parameter_ini->value("Macro/MProbeWorkY").toDouble(); }//宏代码 对刀位置
	void SetMProbeWorkY(int value) { Parameter_ini->setValue("Macro/MProbeWorkY", value); }

	QString GetG73_d() { return Parameter_ini->value("Parameter/G73_d").toString(); }//对刀回退距离z
	void SetG73_d(QString value) { Parameter_ini->setValue("Parameter/G73_d", value); }

	bool GetXOriginLmt() { return Parameter_ini->value("OriginLmt/XOriginLmt").toBool(); }//x 轴 原点限位 使能
	void SetXOriginLmt(bool value) { Parameter_ini->setValue("OriginLmt/XOriginLmt", value); }
	bool GetYOriginLmt() { return Parameter_ini->value("OriginLmt/YOriginLmt").toBool(); }//y 轴 原点限位 使能
	void SetYOriginLmt(bool value) { Parameter_ini->setValue("OriginLmt/YOriginLmt", value); }
	bool GetZOriginLmt() { return Parameter_ini->value("OriginLmt/ZOriginLmt").toBool(); }//z 轴 原点限位 使能
	void SetZOriginLmt(bool value) { Parameter_ini->setValue("OriginLmt/ZOriginLmt", value); }

	bool GetSureMsg() { return Parameter_ini->value("Parameter/SureMsg").toBool(); }//确认消息
	void SetSureMsg(bool value) { Parameter_ini->setValue("Parameter/SureMsg", value); }

	int GetWorkpieceOffset() { return Parameter_ini->value("Parameter/WorkpieceOffset").toInt(); }//工件偏置
	void SetWorkpieceOffset(int value) { Parameter_ini->setValue("Parameter/WorkpieceOffset", value); }

	QString GetXMotorDirLevel() { return Parameter_ini->value("Parameter/XMotorDirLevel").toString(); }//轴 方向
	void SetXMotorDirLevel(QString value) { Parameter_ini->setValue("Parameter/XMotorDirLevel", value); }
	QString GetYMotorDirLevel() { return Parameter_ini->value("Parameter/YMotorDirLevel").toString(); }//轴 方向
	void SetYMotorDirLevel(QString value) { Parameter_ini->setValue("Parameter/YMotorDirLevel", value); }
	QString GetZMotorDirLevel() { return Parameter_ini->value("Parameter/ZMotorDirLevel").toString(); }//轴 方向
	void SetZMotorDirLevel(QString value) { Parameter_ini->setValue("Parameter/ZMotorDirLevel", value); }
	QString GetAMotorDirLevel() { return Parameter_ini->value("Parameter/AMotorDirLevel").toString(); }//轴 方向
	void SetAMotorDirLevel(QString value) { Parameter_ini->setValue("Parameter/AMotorDirLevel", value); }
	QString GetBMotorDirLevel() { return Parameter_ini->value("Parameter/BMotorDirLevel").toString(); }//轴 方向
	void SetBMotorDirLevel(QString value) { Parameter_ini->setValue("Parameter/BMotorDirLevel", value); }
	QString GetCMotorDirLevel() { return Parameter_ini->value("Parameter/CMotorDirLevel").toString(); }//轴 方向
	void SetCMotorDirLevel(QString value) { Parameter_ini->setValue("Parameter/CMotorDirLevel", value); }

	QString GetSpindleOpen() { return Parameter_ini->value("Parameter/SpindleOpen").toString(); }//主轴开 延时
	void SetSpindleOpen(QString value) { Parameter_ini->setValue("Parameter/SpindleOpen", value); }
	QString GetSpindleClose() { return Parameter_ini->value("Parameter/SpindleClose").toString(); }//延时
	void SetSpindleClose(QString value) { Parameter_ini->setValue("Parameter/SpindleClose", value); }
	QString GetM07Time() { return Parameter_ini->value("Parameter/M07Time").toString(); }//喷雾 风冷 打开
	void SetM07Time(QString value) { Parameter_ini->setValue("Parameter/M07Time", value); }
	QString GetM08Time() { return Parameter_ini->value("Parameter/M08Time").toString(); }//冷却液 油冷 打开
	void SetM08Time(QString value) { Parameter_ini->setValue("Parameter/M08Time", value); }
	QString GetM09Time() { return Parameter_ini->value("Parameter/M09Time").toString(); }//关闭 喷雾 冷却液
	void SetM09Time(QString value) { Parameter_ini->setValue("Parameter/M09Time", value); }

	QString GetXMachineCoordinate() { return Parameter_ini->value("MachineCoordinate/XMachineCoordinate").toString(); }//保存的机械坐标
	QString GetXWorkpieceCoordinate() { return Parameter_ini->value("WorkpieceCoordinate/XWorkpieceCoordinate").toString(); }//保存的工件坐标
	QString GetYMachineCoordinate() { return Parameter_ini->value("MachineCoordinate/YMachineCoordinate").toString(); }
	QString GetYWorkpieceCoordinate() { return Parameter_ini->value("WorkpieceCoordinate/YWorkpieceCoordinate").toString(); }
	QString GetZMachineCoordinate() { return Parameter_ini->value("MachineCoordinate/ZMachineCoordinate").toString(); }
	QString GetZWorkpieceCoordinate() { return Parameter_ini->value("WorkpieceCoordinate/ZWorkpieceCoordinate").toString(); }

	void SetXMachineCoordinate(QString value) { Parameter_ini->setValue("MachineCoordinate/XMachineCoordinate", value); }
	void SetXWorkpieceCoordinate(QString value) { Parameter_ini->setValue("WorkpieceCoordinate/XWorkpieceCoordinate", value); }
	void SetYMachineCoordinate(QString value) { Parameter_ini->setValue("MachineCoordinate/YMachineCoordinate", value); }
	void SetYWorkpieceCoordinate(QString value) { Parameter_ini->setValue("WorkpieceCoordinate/YWorkpieceCoordinate", value); }
	void SetZMachineCoordinate(QString value) { Parameter_ini->setValue("MachineCoordinate/ZMachineCoordinate", value); }
	void SetZWorkpieceCoordinate(QString value) { Parameter_ini->setValue("WorkpieceCoordinate/ZWorkpieceCoordinate", value); }

	QString GetAMachineCoordinate() { return Parameter_ini->value("MachineCoordinate/AMachineCoordinate").toString(); }
	QString GetAWorkpieceCoordinate() { return Parameter_ini->value("WorkpieceCoordinate/AWorkpieceCoordinate").toString(); }
	QString GetBMachineCoordinate() { return Parameter_ini->value("MachineCoordinate/BMachineCoordinate").toString(); }
	QString GetBWorkpieceCoordinate() { return Parameter_ini->value("WorkpieceCoordinate/BWorkpieceCoordinate").toString(); }
	QString GetCMachineCoordinate() { return Parameter_ini->value("MachineCoordinate/CMachineCoordinate").toString(); }
	QString GetCWorkpieceCoordinate() { return Parameter_ini->value("WorkpieceCoordinate/CWorkpieceCoordinate").toString(); }

	void SetAMachineCoordinate(QString value) { Parameter_ini->setValue("MachineCoordinate/AMachineCoordinate", value); }
	void SetAWorkpieceCoordinate(QString value) { Parameter_ini->setValue("WorkpieceCoordinate/AWorkpieceCoordinate", value); }
	void SetBMachineCoordinate(QString value) { Parameter_ini->setValue("MachineCoordinate/BMachineCoordinate", value); }
	void SetBWorkpieceCoordinate(QString value) { Parameter_ini->setValue("WorkpieceCoordinate/BWorkpieceCoordinate", value); }
	void SetCMachineCoordinate(QString value) { Parameter_ini->setValue("MachineCoordinate/CMachineCoordinate", value); }
	void SetCWorkpieceCoordinate(QString value) { Parameter_ini->setValue("WorkpieceCoordinate/CWorkpieceCoordinate", value); }

	//bool GetAutoVisible() { return Parameter_ini->value("Other/AutoVisible").toBool(); }//是否预载刀路
	//void SetAutoVisible(bool value) { Parameter_ini->setValue("Other/AutoVisible", value); }

	QString GetSafetyHeight() {return Parameter_ini->value("Parameter/SafetyHeight").toString();}//安全高度
	void SetSafetyHeight(QString value) { Parameter_ini->setValue("Parameter/SafetyHeight", value); }

	QString GetFeedrate() { return Parameter_ini->value("Parameter/Feedrate").toString(); }//默认进给速度
	void SetFeedrate(QString value) { Parameter_ini->setValue("Parameter/Feedrate", value); }

	bool GetUseFeedrate() { return Parameter_ini->value("Parameter/UseFeedrate").toBool(); }//是否使用默认进给速度
	void SetUseFeedrate(bool value) { Parameter_ini->setValue("Parameter/UseFeedrate", value); }

	QString GetXRollbackdistance() { return Parameter_ini->value("Parameter/XRollbackdistance").toString(); }//回退距离x
	void SetXRollbackdistance(QString value) { Parameter_ini->setValue("Parameter/XRollbackdistance", value); }

	QString GetYRollbackdistance() { return Parameter_ini->value("Parameter/YRollbackdistance").toString(); }//回退距离y
	void SetYRollbackdistance(QString value) { Parameter_ini->setValue("Parameter/YRollbackdistance", value); }

	QString GetZRollbackdistance() { return Parameter_ini->value("Parameter/ZRollbackdistance").toString(); }//回退距离z
	void SetZRollbackdistance(QString value) { Parameter_ini->setValue("Parameter/ZRollbackdistance", value); }

	QString GetARollbackdistance() { return Parameter_ini->value("Parameter/ARollbackdistance").toString(); }//回退距离z
	void SetARollbackdistance(QString value) { Parameter_ini->setValue("Parameter/ARollbackdistance", value); }

	QString GetBRollbackdistance() { return Parameter_ini->value("Parameter/BRollbackdistance").toString(); }//回退距离z
	void SetBRollbackdistance(QString value) { Parameter_ini->setValue("Parameter/BRollbackdistance", value); }

	QString GetCRollbackdistance() { return Parameter_ini->value("Parameter/CRollbackdistance").toString(); }//回退距离z
	void SetCRollbackdistance(QString value) { Parameter_ini->setValue("Parameter/CRollbackdistance", value); }

	QString GetZToolSettingdistance() { return Parameter_ini->value("Parameter/ZToolSettingdistance").toString(); }//对刀回退距离z
	void SetZToolSettingdistance(QString value) { Parameter_ini->setValue("Parameter/ZToolSettingdistance", value); }

	QString GetZToolSettingSpeed() { return Parameter_ini->value("Parameter/ZToolSettingSpeed").toString(); }//对刀速度
	void SetZToolSettingSpeed(QString value) { Parameter_ini->setValue("Parameter/ZToolSettingSpeed", value); }

	QString GetZReturnSpeed() { return Parameter_ini->value("Parameter/ZReturnSpeed").toString(); }//z回0速度
	void SetZReturnSpeed(QString value) { Parameter_ini->setValue("Parameter/ZReturnSpeed", value); }

	QString GetFixedX() { return Parameter_ini->value("Parameter/FixedX").toString(); }//X方向固定点
	void SetFixedX(QString value) { Parameter_ini->setValue("Parameter/FixedX", value); }

	QString GetFixedY() { return Parameter_ini->value("Parameter/FixedY").toString(); }//y方向固定点
	void SetFixedY(QString value) { Parameter_ini->setValue("Parameter/FixedY", value); }

	QString GetStaetZ() { return Parameter_ini->value("Parameter/StaetZ").toString(); }//Z方向起始点
	void SetStaetZ(QString value) { Parameter_ini->setValue("Parameter/StaetZ", value); }

	QString GetMinimaZ() { return Parameter_ini->value("Parameter/MinimaZ").toString(); }//Z最低点
	void SetMinimaZ(QString value) { Parameter_ini->setValue("Parameter/MinimaZ", value); }

	QString GetToolsThickness() { return Parameter_ini->value("Parameter/GetToolsThickness").toString(); }//刀块厚度
	void SetToolsThickness(QString value) { Parameter_ini->setValue("Parameter/GetToolsThickness", value); }

	bool GetIsCloseSpindle() { return Parameter_ini->value("Parameter/IsCloseSpindle").toBool(); }//停止 时主轴是否关闭
	void SetIsCloseSpindle(bool value) { Parameter_ini->setValue("Parameter/IsCloseSpindle", value); }
	bool GetIsOpenSpindle() { return Parameter_ini->value("Parameter/IsOpenSpindle").toBool(); }//主轴
	void SetIsOpenSpindle(bool value) { Parameter_ini->setValue("Parameter/IsOpenSpindle", value); }

	QString GetStopZParam() { return Parameter_ini->value("Parameter/StopZParam").toString(); }//暂停时 Z选择
	void SetStopZParam(QString value) { Parameter_ini->setValue("Parameter/StopZParam", value); }

	QString GetStopZValue() { return Parameter_ini->value("Parameter/StopZValue").toString(); }//暂停时 Z抬刀量
	void SetStopZValue(QString value) { Parameter_ini->setValue("Parameter/StopZValue", value); }

	bool GetLmtEnalbe() { return Parameter_ini->value("SoftLmt/LmtEnalbe").toBool(); }//工作台行程范围检测是否有效
	void SetLmtEnalbe(bool value) { Parameter_ini->setValue("SoftLmt/LmtEnalbe", value); }

	QString GetXPosPlus() { return Parameter_ini->value("SoftLmt/XPosPlus").toString(); }//工作台行程范围
	QString GetXPosMinus() { return Parameter_ini->value("SoftLmt/XPosMinus").toString(); }//工作台行程
	QString GetYPosPlus() { return Parameter_ini->value("SoftLmt/YPosPlus").toString(); }//工作台行程范围
	QString GetYPosMinus() { return Parameter_ini->value("SoftLmt/YPosMinus").toString(); }//工作台行程范围
	QString GetZPosPlus() { return Parameter_ini->value("SoftLmt/ZPosPlus").toString(); }//工作台行程范围
	QString GetZPosMinus() { return Parameter_ini->value("SoftLmt/ZPosMinus").toString(); }//工作台行程范围

	void SetXPosPlus(QString value) { Parameter_ini->setValue("SoftLmt/XPosPlus", value); }
	void SetXPosMinus(QString value) { Parameter_ini->setValue("SoftLmt/XPosMinus", value); }
	void SetYPosPlus(QString value) { Parameter_ini->setValue("SoftLmt/YPosPlus", value); }
	void SetYPosMinus(QString value) { Parameter_ini->setValue("SoftLmt/YPosMinus", value); }
	void SetZPosPlus(QString value) { Parameter_ini->setValue("SoftLmt/ZPosPlus", value); }
	void SetZPosMinus(QString value) { Parameter_ini->setValue("SoftLmt/ZPosMinus", value); }

	QString GetAPosPlus() { return Parameter_ini->value("SoftLmt/APosPlus").toString(); }//工作台行程范围
	QString GetAPosMinus() { return Parameter_ini->value("SoftLmt/APosMinus").toString(); }//工作台行程
	QString GetBPosPlus() { return Parameter_ini->value("SoftLmt/BPosPlus").toString(); }//工作台行程范围
	QString GetBPosMinus() { return Parameter_ini->value("SoftLmt/BPosMinus").toString(); }//工作台行程范围
	QString GetCPosPlus() { return Parameter_ini->value("SoftLmt/CPosPlus").toString(); }//工作台行程范围
	QString GetCPosMinus() { return Parameter_ini->value("SoftLmt/CPosMinus").toString(); }//工作台行程范围

	void SetAPosPlus(QString value) { Parameter_ini->setValue("SoftLmt/APosPlus", value); }
	void SetAPosMinus(QString value) { Parameter_ini->setValue("SoftLmt/APosMinus", value); }
	void SetBPosPlus(QString value) { Parameter_ini->setValue("SoftLmt/BPosPlus", value); }
	void SetBPosMinus(QString value) { Parameter_ini->setValue("SoftLmt/BPosMinus", value); }
	void SetCPosPlus(QString value) { Parameter_ini->setValue("SoftLmt/CPosPlus", value); }
	void SetCPosMinus(QString value) { Parameter_ini->setValue("SoftLmt/CPosMinus", value); }

	int GetIOinPolarity() { return Parameter_ini->value("SoftLmt/IOinPolarity").toInt(); }//io in 极性
	void SetIOinPolarity(int value) { Parameter_ini->setValue("SoftLmt/IOinPolarity", value); }
	
	int GetAxisEnabled() { return Parameter_ini->value("SoftLmt/AxisEnabled").toInt(); }//io使能
	void SetAxisEnabled(int value) { Parameter_ini->setValue("SoftLmt/AxisEnabled", value); }

	QString GetToolChangeOpt() { return Parameter_ini->value("Tools/ToolChangeOpt").toString(); }//换刀选项
	void  SetToolChangeOpt(QString value) { Parameter_ini->setValue("Tools/ToolChangeOpt", value); }

	QString GetToolInFeed() { return Parameter_ini->value("Tools/ToolInFeed").toString(); }
	void  SetToolInFeed(QString value) { Parameter_ini->setValue("Tools/ToolInFeed", value); }

	QString GetToolChangeUpZ() { return Parameter_ini->value("Tools/ToolChangeUpZ").toString(); }
	void  SetToolChangeUpZ(QString value) { Parameter_ini->setValue("Tools/ToolChangeUpZ", value); }

	QString GetToolReady() { return Parameter_ini->value("Tools/ToolReady").toString(); }
	void  SetToolReady(QString value) { Parameter_ini->setValue("Tools/ToolReady", value); }

	QString GetToolSafeZ() { return Parameter_ini->value("Tools/ToolSafeZ").toString(); }//换刀安全高度
	void  SetToolSafeZ(QString value) { Parameter_ini->setValue("Tools/ToolSafeZ", value); }

	bool GetToolIsOnY() { return Parameter_ini->value("Tools/ToolIsOnY").toBool(); }
	void  SetToolIsOnY(bool value) { Parameter_ini->setValue("Tools/ToolIsOnY", value); }

	bool GetToolIsQiGang() { return Parameter_ini->value("Tools/ToolIsQiGang").toBool(); }
	void  SetToolIsQiGang(bool value) { Parameter_ini->setValue("Tools/ToolIsQiGang", value); }

	QString GetToolCount() { return Parameter_ini->value("Tools/ToolCount").toString(); }
	void  SetToolCount(QString value) { Parameter_ini->setValue("Tools/ToolCount", value); }

	double GetZCloseValue() { return Parameter_ini->value("Tools/ZCloseValue").toDouble(); }
	void  SetZCloseValue(double value) { Parameter_ini->setValue("Tools/ZCloseValue", value); }

	int GetTool_In_Enabled_4(int pos = -1); //VersionType4;使能 位。
	void  SetTool_In_Enabled_4(int pos, int Enabled);//VersionType4;使能 位。

	int GetTool_In_Enabled_2(int pos = -1); //VersionType2;使能 位。
	void  SetTool_In_Enabled_2(int pos, int Enabled);//VersionType2;使能 位。

	QString GetT1Name() { return Parameter_ini->value("T1/Name").toString(); }//刀具名称
	void SetT1Name(QString value) { Parameter_ini->setValue("T1/Name", value); }
	QString GetT1X() { return Parameter_ini->value("T1/X").toString(); }
	void SetT1X(QString value) { Parameter_ini->setValue("T1/X", value); }
	QString GetT1Y() { return Parameter_ini->value("T1/Y").toString(); }
	void SetT1Y(QString value) { Parameter_ini->setValue("T1/Y", value); }
	QString GetT1Z() { return Parameter_ini->value("T1/Z").toString(); }
	void SetT1Z(QString value) { Parameter_ini->setValue("T1/Z", value); }

	QString GetT2Name() { return Parameter_ini->value("T2/Name").toString(); }//刀具名称
	void SetT2Name(QString value) { Parameter_ini->setValue("T2/Name", value); }
	QString GetT2X() { return Parameter_ini->value("T2/X").toString(); }
	void SetT2X(QString value) { Parameter_ini->setValue("T2/X", value); }
	QString GetT2Y() { return Parameter_ini->value("T2/Y").toString(); }
	void SetT2Y(QString value) { Parameter_ini->setValue("T2/Y", value); }
	QString GetT2Z() { return Parameter_ini->value("T2/Z").toString(); }
	void SetT2Z(QString value) { Parameter_ini->setValue("T2/Z", value); }

	QString GetT3Name() { return Parameter_ini->value("T3/Name").toString(); }//刀具名称
	void SetT3Name(QString value) { Parameter_ini->setValue("T3/Name", value); }
	QString GetT3X() { return Parameter_ini->value("T3/X").toString(); }
	void SetT3X(QString value) { Parameter_ini->setValue("T3/X", value); }
	QString GetT3Y() { return Parameter_ini->value("T3/Y").toString(); }
	void SetT3Y(QString value) { Parameter_ini->setValue("T3/Y", value); }
	QString GetT3Z() { return Parameter_ini->value("T3/Z").toString(); }
	void SetT3Z(QString value) { Parameter_ini->setValue("T3/Z", value); }

	QString GetT4Name() { return Parameter_ini->value("T4/Name").toString(); }//刀具名称
	void SetT4Name(QString value) { Parameter_ini->setValue("T4/Name", value); }
	QString GetT4X() { return Parameter_ini->value("T4/X").toString(); }
	void SetT4X(QString value) { Parameter_ini->setValue("T4/X", value); }
	QString GetT4Y() { return Parameter_ini->value("T4/Y").toString(); }
	void SetT4Y(QString value) { Parameter_ini->setValue("T4/Y", value); }
	QString GetT4Z() { return Parameter_ini->value("T4/Z").toString(); }
	void SetT4Z(QString value) { Parameter_ini->setValue("T4/Z", value); }

	QString GetT5Name() { return Parameter_ini->value("T5/Name").toString(); }//刀具名称
	void SetT5Name(QString value) { Parameter_ini->setValue("T5/Name", value); }
	QString GetT5X() { return Parameter_ini->value("T5/X").toString(); }
	void SetT5X(QString value) { Parameter_ini->setValue("T5/X", value); }
	QString GetT5Y() { return Parameter_ini->value("T5/Y").toString(); }
	void SetT5Y(QString value) { Parameter_ini->setValue("T5/Y", value); }
	QString GetT5Z() { return Parameter_ini->value("T5/Z").toString(); }
	void SetT5Z(QString value) { Parameter_ini->setValue("T5/Z", value); }

	QString GetT6Name() { return Parameter_ini->value("T6/Name").toString(); }//刀具名称
	void SetT6Name(QString value) { Parameter_ini->setValue("T6/Name", value); }
	QString GetT6X() { return Parameter_ini->value("T6/X").toString(); }
	void SetT6X(QString value) { Parameter_ini->setValue("T6/X", value); }
	QString GetT6Y() { return Parameter_ini->value("T6/Y").toString(); }
	void SetT6Y(QString value) { Parameter_ini->setValue("T6/Y", value); }
	QString GetT6Z() { return Parameter_ini->value("T6/Z").toString(); }
	void SetT6Z(QString value) { Parameter_ini->setValue("T6/Z", value); }

	QString GetT7Name() { return Parameter_ini->value("T7/Name").toString(); }//刀具名称
	void SetT7Name(QString value) { Parameter_ini->setValue("T7/Name", value); }
	QString GetT7X() { return Parameter_ini->value("T7/X").toString(); }
	void SetT7X(QString value) { Parameter_ini->setValue("T7/X", value); }
	QString GetT7Y() { return Parameter_ini->value("T7/Y").toString(); }
	void SetT7Y(QString value) { Parameter_ini->setValue("T7/Y", value); }
	QString GetT7Z() { return Parameter_ini->value("T7/Z").toString(); }
	void SetT7Z(QString value) { Parameter_ini->setValue("T7/Z", value); }

	QString GetT8Name() { return Parameter_ini->value("T8/Name").toString(); }//刀具名称
	void SetT8Name(QString value) { Parameter_ini->setValue("T8/Name", value); }
	QString GetT8X() { return Parameter_ini->value("T8/X").toString(); }
	void SetT8X(QString value) { Parameter_ini->setValue("T8/X", value); }
	QString GetT8Y() { return Parameter_ini->value("T8/Y").toString(); }
	void SetT8Y(QString value) { Parameter_ini->setValue("T8/Y", value); }
	QString GetT8Z() { return Parameter_ini->value("T8/Z").toString(); }
	void SetT8Z(QString value) { Parameter_ini->setValue("T8/Z", value); }

	QString GetT9X() { return Parameter_ini->value("T9/X").toString(); }
	void SetT9X(QString value) { Parameter_ini->setValue("T9/X", value); }
	QString GetT9Y() { return Parameter_ini->value("T9/Y").toString(); }
	void SetT9Y(QString value) { Parameter_ini->setValue("T9/Y", value); }
	QString GetT9Z() { return Parameter_ini->value("T9/Z").toString(); }
	void SetT9Z(QString value) { Parameter_ini->setValue("T9/Z", value); }

	QString GetT10X() { return Parameter_ini->value("T10/X").toString(); }
	void SetT10X(QString value) { Parameter_ini->setValue("T10/X", value); }
	QString GetT10Y() { return Parameter_ini->value("T10/Y").toString(); }
	void SetT10Y(QString value) { Parameter_ini->setValue("T10/Y", value); }
	QString GetT10Z() { return Parameter_ini->value("T10/Z").toString(); }
	void SetT10Z(QString value) { Parameter_ini->setValue("T10/Z", value); }

	QString GetT11X() { return Parameter_ini->value("T11/X").toString(); }
	void SetT11X(QString value) { Parameter_ini->setValue("T11/X", value); }
	QString GetT11Y() { return Parameter_ini->value("T11/Y").toString(); }
	void SetT11Y(QString value) { Parameter_ini->setValue("T11/Y", value); }
	QString GetT11Z() { return Parameter_ini->value("T11/Z").toString(); }
	void SetT11Z(QString value) { Parameter_ini->setValue("T11/Z", value); }

	QString GetT12X() { return Parameter_ini->value("T12/X").toString(); }
	void SetT12X(QString value) { Parameter_ini->setValue("T12/X", value); }
	QString GetT12Y() { return Parameter_ini->value("T12/Y").toString(); }
	void SetT12Y(QString value) { Parameter_ini->setValue("T12/Y", value); }
	QString GetT12Z() { return Parameter_ini->value("T12/Z").toString(); }
	void SetT12Z(QString value) { Parameter_ini->setValue("T12/Z", value); }

	QString GetT13X() { return Parameter_ini->value("T13/X").toString(); }
	void SetT13X(QString value) { Parameter_ini->setValue("T13/X", value); }
	QString GetT13Y() { return Parameter_ini->value("T13/Y").toString(); }
	void SetT13Y(QString value) { Parameter_ini->setValue("T13/Y", value); }
	QString GetT13Z() { return Parameter_ini->value("T13/Z").toString(); }
	void SetT13Z(QString value) { Parameter_ini->setValue("T13/Z", value); }

	QString GetT14X() { return Parameter_ini->value("T14/X").toString(); }
	void SetT14X(QString value) { Parameter_ini->setValue("T14/X", value); }
	QString GetT14Y() { return Parameter_ini->value("T14/Y").toString(); }
	void SetT14Y(QString value) { Parameter_ini->setValue("T14/Y", value); }
	QString GetT14Z() { return Parameter_ini->value("T14/Z").toString(); }
	void SetT14Z(QString value) { Parameter_ini->setValue("T14/Z", value); }

	QString GetT15X() { return Parameter_ini->value("T15/X").toString(); }
	void SetT15X(QString value) { Parameter_ini->setValue("T15/X", value); }
	QString GetT15Y() { return Parameter_ini->value("T15/Y").toString(); }
	void SetT15Y(QString value) { Parameter_ini->setValue("T15/Y", value); }
	QString GetT15Z() { return Parameter_ini->value("T15/Z").toString(); }
	void SetT15Z(QString value) { Parameter_ini->setValue("T15/Z", value); }

	QString GetT16X() { return Parameter_ini->value("T16/X").toString(); }
	void SetT16X(QString value) { Parameter_ini->setValue("T16/X", value); }
	QString GetT16Y() { return Parameter_ini->value("T16/Y").toString(); }
	void SetT16Y(QString value) { Parameter_ini->setValue("T16/Y", value); }
	QString GetT16Z() { return Parameter_ini->value("T16/Z").toString(); }
	void SetT16Z(QString value) { Parameter_ini->setValue("T16/Z", value); }

	int GetTool() { return Parameter_ini->value("Parameter/tool").toInt(); }//保存刀具号
	void SetTool(int value) { Parameter_ini->setValue("Parameter/tool", value); }


	int GetSeekZeroOpt() { return Parameter_ini->value("Parameter/SeekZeroOpt").toInt(); }//回0选项
	void SetSeekZeroOpt(int value) { Parameter_ini->setValue("Parameter/SeekZeroOpt", value); }


	double GetTuiLiaoStarX() { return Parameter_ini->value("VType4/TuiLiaoStarX").toDouble(); }//推料起始点
	void SetTuiLiaoStarX(double value) { Parameter_ini->setValue("VType4/TuiLiaoStarX", value); }
	double GetTuiLiaoStarY() { return Parameter_ini->value("VType4/TuiLiaoStarY").toDouble(); }//推料起始点
	void SetTuiLiaoStarY(double value) { Parameter_ini->setValue("VType4/TuiLiaoStarY", value); }


	double GetTuiLiaoEndX() { return Parameter_ini->value("VType4/TuiLiaoEndX").toDouble(); }//推料结束点
	void SetTuiLiaoEndX(double value) { Parameter_ini->setValue("VType4/TuiLiaoEndX", value); }
	double GetTuiLiaoEndY() { return Parameter_ini->value("VType4/TuiLiaoEndY").toDouble(); }//推料结束点
	void SetTuiLiaoEndY(double value) { Parameter_ini->setValue("VType4/TuiLiaoEndY", value); }

	int GetPulseDirection() { return Parameter_ini->value("Parameter/PulseDirection").toInt(); }
	void SetPulseDirection(int value) { Parameter_ini->setValue("Parameter/PulseDirection", value); }
private:
	void LoadFileList();
	void SaveFileList();
private:
	QSettings*	Parameter_ini;
	QStringList	fileList;
};
