#pragma once

#include <QObject>
#include "datadefine.h"
////����G�����ļ�ʱ����Ҫ��ʾ�ӹ���·
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
	QString GetNumber(QString curline, char upper, char lower);//��ȡ �ַ���������֣�
	
	bool GetValidline(QString& curline,int key);
	bool NeedTr = 0; // �Ƿ���Ҫ�滻code
	bool NeedDealM = 0;// �Ƿ���Ҫ����m
	bool isM03M04 = false;//m03 05 04 ����ʱ  ������ת ��ת �ر�
	bool isM05 = false;
	bool isM07 = false;  //���� ���� ��
	bool isM08 = false;//��ȴҺ ���� ��
	bool isM09 = false;//  �ر� ���� ��ȴҺ
	QStringList ErrorGCode;;//����Ҫ֧�ֵ�G���� ���ӹ�
	QStringList TrGCode;//dll ��֧�� ��Ҫ�滻��code
	QStringList DrillHoleCode;//ת��ָ��

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
	bool IsDrillHole = false;//ת��ָ��
	ArcData curArc;

	static bool GetRealCenterPoint(double Xstart, double Ystart, double Xend, double Yend, double R, double x, double y,bool );
	static void Circle_Center(float , float , float , float , float, float &, float &, float &, float &);
	static double Y_Coordinates(double x, double y, double k, double x0);
	void clear();
	QString errorMsg;
};
