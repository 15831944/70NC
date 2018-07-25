#pragma once

#include <QObject>
#include "datadefine.h"
////加载G代码文件时，需要显示加工刀路
#include <QTextStream>
class AnalysisG : public QObject
{
	Q_OBJECT

public:
	AnalysisG(QObject *parent = 0);
	~AnalysisG();
	void InsertPoint(QString);
	void InsertLine(QString curline);
	void InsertArc(QString curline);
	void InsertArcR(QString curline);
	void InsertArcIJK(QString curline);
	bool InsertDrillHoleData(int key,QString curline);
	QString GetNumber(QString curline, char upper, char lower);//获取 字符后面的数字；
	
	bool GetValidline(QString& curline,int key);
	bool NeedTr = 0; // 是否需要替换code
	bool NeedDealM = 0;// 是否需要处理m
	bool isM03M04 = false;//m03 05 04 加延时  主轴正转 反转 关闭
	bool isM05 = false;
	bool isM07 = false;  //喷雾 风冷 打开
	bool isM08 = false;//冷却液 油冷 打开
	bool isM09 = false;//  关闭 喷雾 冷却液
	QStringList ErrorGCode;;//不需要支持的G代码 不加工
	QStringList TrGCode;//dll 不支持 需要替换的code
	QStringList DrillHoleCode;//转孔指令

	QStringList TrMCode;
	QStringList NeedDealMCode;

	void ShowGCode(QStringList&  List);
	void ShowGCode(QTextStream& stream);
	DrillHoleData mData;
	float x = 0;
	float y = 0;
	float z = 0;
	bool LastisArc = false;
	bool LastisG0 = true;
	bool isG0 = false;
	bool IsArc = false;
	bool IsAbsolute = true;
	bool IsG02 = true;
	int ArcFlag = 0; //0,G17 ; 1 G18 ; 2 G19
	bool HasR = false;
	bool IsDrillHole = false;//转孔指令
	ArcData curArc;

	static bool GetRealCenterPoint(double Xstart, double Ystart, double Xend, double Yend, double R, double x, double y,bool );
	static void Circle_Center(float , float , float , float , float, float &, float &, float &, float &);
	static double Y_Coordinates(double x, double y, double k, double x0);
	void clear();
	QString errorMsg;
};
