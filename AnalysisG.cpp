
#include "AnalysisG.h"
#include "QFile"
#include "QTextStream"
#include "QList"
#include"CommonTools.h"
#include "qDebug"
#include "ExternalText.h"
//G17 XY
//G18 XZ
//G19 YZ
//x指向右
//y指向上
//z指向屏幕到外

//g17 g02对应坐标轴 顺序为： x向右  y向上 顺时针
//g18 g02				 x向右  z向下（x向上 z向右） 顺时针
//g19 g02				y向上  z向左 顺时针
#define NotNum(i) ((curline[i]== " ") || (0x41 <=  curline[i] &&  curline[i] <= 0x5A) || (0x61 <=  curline[i] &&  curline[i] <= 0x7A)) 
extern ReadIni readIni;
QList<Line>vLines;
QList<ArcData> Arcs;
AnalysisG::AnalysisG(QObject *parent)
	: QObject(parent)
{
	//不支持的G代码不加工.  需要支持的要 转换
	ErrorGCode << "10" << "12" << "13" << "28.1" << "30" << "52" << "61" << "64" << "68" << "69" << "92.1" << "92.2" << "92.3" << "93" << "94" << "95" << "41" << "42" << "20" << "15" << " 16" << "84" << "74" << "76" << "87" << "70" << "71";
	//需要转换的G代码
	TrGCode << "31";
	//转孔指令，转换
	DrillHoleCode << "80" << "81" << "82" << "73" << "85" << "86" << "89" << "83";
	//不支持的m代码忽略.  需要支持的要停下来处理
	NeedDealMCode << "47";// << "30";
}

AnalysisG::~AnalysisG()
{
}

bool AnalysisG::GetRealCenterPoint(double Xstart, double Ystart, double Xend, double Yend, double R, double x, double y,bool isG2) {
	//参数 圆弧起点坐标，圆弧中点坐标，半径 圆心，

	double _x, _y;//圆弧起点坐标相对于圆心对称的点
	_x = 2 * x - Xstart;
	_y = 2 * y - Ystart;
	if (isG2) {
		if (Xstart == x) {
			bool b1 = Yend < Ystart&&Xend < Xstart;
			bool b2 = Yend > Ystart&&Xend > Xstart;
			bool b3 = Yend < Ystart&&Xend > Xstart;
			bool b4 = Yend > Ystart&&Xend < Xstart;
			if (b1) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b2) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b3) {
				if (R < 0) {
					return 1;
				}
			}
			else if (b4) {
				if (R < 0) {
					return 1;
				}
			}
		}
		if (Ystart == y) {
			bool b1 = Xend < Xstart&&Yend>Ystart;
			bool b2 = Xend > Xstart&&Ystart > Yend;
			bool b3 = Xend < Xstart&&Yend < Ystart;
			bool b4 = Xend > Xstart&&Ystart < Yend;
			if (b1) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b2) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b1) {
				if (R < 0) {
					return 1;
				}
			}
			else if (b4) {
				if (R < 0) {
					return 1;
				}
			}
		}
		//圆弧起点 在第 一象限
		if (Xstart - x > 0 && Ystart - y > 0) {
			if (_x < Xend&&Ystart > Yend) {//满足此条件则弧度<=180
				if (R > 0) {
					return 1;
				}
			}
			else if (_y<Yend&&Xstart>Xend) {
				if (R < 0) {
					return 1;
				}
			}
		}
		//圆弧起点 在第 二象限
		if (Xstart - x< 0 && Ystart - y> 0) {
			if (Xstart < Xend&& _y < Yend) {//满足此条件则弧度<=180  
				if (R > 0) {
					return 1;
				}
			}
			else if (Ystart>Yend&&_x>Xend) {
				if (R < 0) {
					return 1;
				}
			}
		}
		//圆弧起点 在第 三象限
		if (Xstart - x <0 && Ystart - y < 0) {
			if (Ystart < Yend&&_x > Xend) {//满足此条件则弧度<=180  
				if (R > 0) {
					return 1;
				}
			}
			else if (Xstart<Xend&&_y>Yend) {
				if (R < 0) {
					return 1;
				}
			}
		}
		//圆弧起点 在第 四象限
		if (Xstart - x> 0 && Ystart - y< 0) {
			if (Xstart > Xend&&_y >= Yend) {//满足此条件则弧度<=180  
				if (R > 0) {
					return 1;
				}
			}
			else if (Ystart<Yend&&_x<Xend) {
				if (R < 0) {
					return 1;
				}
			}
		}
	}
	else {
		if (Xstart == x) {
			bool b1 = Yend < Ystart&&Xend < Xstart;
			bool b2 = Yend > Ystart&&Xend > Xstart;
			bool b3 = Yend < Ystart&&Xend > Xstart;
			bool b4 = Yend > Ystart&&Xend < Xstart;
			if (b1) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b2) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b3) {
				if (R < 0) {
					return 1;
				}
			}
			else if (b4) {
				if (R < 0) {
					return 1;
				}
			}
		}
		if (Ystart == y) {
			bool b1 = Xend < Xstart&&Yend>Ystart;
			bool b2 = Xend > Xstart&&Ystart > Yend;
			bool b3 = Xend < Xstart&&Yend < Ystart;
			bool b4 = Xend > Xstart&&Ystart < Yend;
			if (b1) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b2) {
				if (R > 0) {
					return 1;
				}
			}
			else if (b1) {
				if (R < 0) {
					return 1;
				}
			}
			else if (b4) {
				if (R < 0) {
					return 1;
				}
			}
		}
		if (Xstart - x> 0 && Ystart - y > 0) {
			if (Xstart >= Xend&&_y < Yend) {//满足此条件则弧度<=180
				if (R > 0) {
					return 1;
				}
			}
			else if (_x<Xend&&Ystart>Yend) {
				if (R < 0) {
					return 1;
				}
			}
		}
		if (Xstart - x< 0 && Ystart - y > 0) {
			if (Ystart > Yend&&_x > Xend) {
				if (R > 0) {
					return 1;
				}
			}
			else if (_y<Yend&&Xstart<Xend) {
				if (R < 0) {
					return 1;
				}
			}
		}
		if (Xstart - x < 0 && Ystart - y< 0) {
			if (Xstart < Xend&&_y > Yend) {
				if (R > 0) {
					return 1;
				}
			}
			else if (Ystart<Yend&&_x>Xend) {
				if (R < 0) {
					return 1;
				}
			}
		}
		if (Xstart - x > 0 && Ystart - y< 0) {
			if (Ystart < Yend&&_x < Xend) {
				if (R > 0) {
					return 1;
				}
			}
			else if (_y>Yend&&Xstart>Xend) {
				if (R < 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}

void AnalysisG::Circle_Center(float x1, float y1, float x2, float y2, float dRadius, float &cx0, float &cy0, float &cx1, float &cy1)
{//参数说明 传入 圆上 两点 （x1，y1）,(x2,y2)和 半径 ; 传出参数 两个圆心;

	double k = 0.0, k_verticle = 0.0;
	double mid_x = 0.0, mid_y = 0.0;
	double a = 1.0;
	double b = 1.0;
	double c = 1.0;
	Point center1, center2;
	k = (y2 - y1) / (x2 - x1);
	if (k == 0)
	{
		center1.x = (x1 + x2) / 2.0;
		center2.x = (x1 + x2) / 2.0;
		double temp = abs(dRadius * dRadius - (x1 - x2) * (x1 - x2) / 4.0);
		center1.y = y1 + sqrt(temp);
		center2.y = y2 - sqrt(temp);
	}
	else
	{
		k_verticle = -1.0 / k;
		mid_x = (x1 + x2) / 2.0;
		mid_y = (y1 + y2) / 2.0;
		a = 1.0 + k_verticle * k_verticle;
		b = -2 * mid_x - k_verticle * k_verticle * (x1 + x2);
		c = mid_x * mid_x + k_verticle * k_verticle * (x1 + x2) * (x1 + x2) / 4.0 -
			(dRadius * dRadius - ((mid_x - x1) * (mid_x - x1) + (mid_y - y1) * (mid_y - y1)));

		double temp = abs(b * b - 4 * a * c);
		center1.x = (-1.0 * b + sqrt(temp)) / (2 * a);
		center2.x = (-1.0 * b - sqrt(temp)) / (2 * a);
		center1.y = Y_Coordinates(mid_x, mid_y, k_verticle, center1.x);
		center2.y = Y_Coordinates(mid_x, mid_y, k_verticle, center2.x);
	}

	cx0 = center1.x;
	cy0 = center1.y;

	cx1 = center2.x;
	cy1 = center2.y;
	qDebug() << "p1" << cx0 << "    " << cy0 << endl;  //圆心可能 有两个
	qDebug() << "p2" << cx1 << "    " << cy1 << endl;
}

double AnalysisG::Y_Coordinates(double x, double y, double k, double x0)
{
	return k * x0 - k * x + y;
}
void AnalysisG::clear()
{
	vLines.clear();
	x = 0;
	y = 0;
	z = 0;
	IsArc = false;
	IsAbsolute = true;
	IsG02 = true;
	HasR = false;
	Arcs.clear();

	mData.clear();
	IsDrillHole = false;
	SammonFunc::ReplaceCodeMap.clear();
	SammonFunc::DrillHoleMap.clear();
}
void AnalysisG::InsertPoint(QString curline)
{
	if (!IsArc) {
		InsertLine(curline);
	}
	else {
		InsertArc(curline);
	}
}

void AnalysisG::InsertLine(QString curline)
{
	if ((!isG0&&LastisG0) || LastisArc) {
		Point point;
		point.x = x;
		point.y = y;
		point.z = z;
		Line line;
		line.Points.push_back(point);
		vLines.push_back(line);
	}
	QString curNum;

	int flag = 0;
	bool hasNum = false;
	curNum = SammonFunc::GetNumber(curline, 'X', 'x');
	if (!curNum.isEmpty()) {
		if (IsAbsolute)
			x = curNum.toDouble();
		else
			x += curNum.toDouble();
		flag--;
		hasNum = true;
	}
	curNum = SammonFunc::GetNumber(curline, 'Y', 'y');
	if (!curNum.isEmpty()) {
		if (IsAbsolute)
			y = curNum.toDouble();
		else
			y += curNum.toDouble();
		flag--;
		hasNum = true;
	}
	curNum = SammonFunc::GetNumber(curline, 'Z', 'z');
	if (!curNum.isEmpty()) {
		if (IsAbsolute)
			z = curNum.toDouble();
		else
			z += curNum.toDouble();
		flag--;
		hasNum = true;
	}
	if (!hasNum)return;

	if (isG0)
		return;
	else {
		Point point;
		point.x = x;
		point.y = y;
		point.z = z;
		if (vLines.size())
			vLines[vLines.size() - 1].Points.push_back(point);
		else {
			Line line;
			vLines.push_back(line);
			vLines[vLines.size() - 1].Points.push_back(point);
		}
	}



	//if (flag) {
	//	XX.push_back(x);
	//	YY.push_back(y);
	//	ZZ.push_back(z);
	//}

}

void AnalysisG::InsertArc(QString curline)
{
	if (curline.contains("R") || curline.contains("r")) {
		InsertArcR(curline);
	}
	else
		InsertArcIJK(curline);

}

void AnalysisG::InsertArcR(QString curline)
{

	bool hX = false;
	bool hY = false;
	bool hZ = false;

	float R = 0;

	float sX = 0;//起点坐标
	float sY = 0;
	float sZ = 0;

	sX = x;
	sY = y;
	sZ = z;
	int flag = -1;
	QString temp = SammonFunc::GetNumber(curline, 'x', 'X');
	if (!temp.isEmpty()) {
		if (IsAbsolute) {
			x = temp.toFloat();
		}
		else {
			x += temp.toFloat();
		}

		hX = true;
		flag = 1;
	}
	//if (curline.contains("X") || curline.contains("x"))
	//{

	//	int a = -1;
	//	for (int i = 0; i < curline.size(); i++) {
	//		if (curline[i] == 'X' || curline[i] == 'x')
	//		{
	//			a = i + 1;
	//			continue;
	//		}
	//		if (a != -1) {
	//			if (((curline[i] <'0' || curline[i] >'9') && !(curline[i] == '.' || curline[i] == '-')) || i == curline.size() - 1)
	//			{
	//				if (IsAbsolute) {
	//					x = curline.mid(a, i - a).toFloat();
	//				}
	//				else {
	//					x += curline.mid(a, i - a).toFloat();
	//				}

	//				hX = true;
	//				flag = 1;
	//				break;
	//			}
	//		}

	//	}
	//}
	temp = SammonFunc::GetNumber(curline, 'y', 'Y');
	if (!temp.isEmpty()) {
		if (IsAbsolute) {
			y = temp.toFloat();
		}
		else {
			y += temp.toFloat();
		}
		hY = true;
		flag = 1;
	}
	//if (curline.contains("Y") || curline.contains("y"))
	//{
	//	int a = -1;
	//	for (int i = 0; i < curline.size(); i++) {
	//		if (curline[i] == 'Y' || curline[i] == 'y')
	//		{
	//			a = i + 1;
	//			continue;
	//		}
	//		if (a != -1) {
	//			if (((curline[i] <'0' || curline[i] >'9') && !(curline[i] == '.' || curline[i] == '-')) || i == curline.size() - 1)
	//			{
	//				if (IsAbsolute) {
	//					y = curline.mid(a, i - a).toFloat();
	//				}
	//				else {
	//					y += curline.mid(a, i - a).toFloat();
	//				}
	//				hY = true;
	//				flag = 1;
	//				break;
	//			}
	//		}

	//	}
	//}
	temp = SammonFunc::GetNumber(curline, 'z', 'Z');
	if (!temp.isEmpty()) {
		if (IsAbsolute) {
			z = temp.toFloat();
		}
		else {
			z += temp.toFloat();
		}
		hZ = true;
		flag = 1;
	}
	//if (curline.contains("Z") || curline.contains("z"))
	//{
	//	int a = -1;
	//	for (int i = 0; i < curline.size(); i++) {
	//		if (curline[i] == 'Z' || curline[i] == 'z')
	//		{
	//			a = i + 1;
	//			continue;
	//		}
	//		if (a != -1) {

	//			if (((curline[i] <'0' || curline[i] >'9') && !(curline[i] == '.' || curline[i] == '-')) || i == curline.size() - 1)
	//			{
	//				if (IsAbsolute) {
	//					z = curline.mid(a, i - a).toFloat();
	//				}
	//				else {
	//					z += curline.mid(a, i - a).toFloat();
	//				}
	//				hZ = true;
	//				flag = 1;
	//				break;
	//			}
	//		}

	//	}
	//}
	temp = SammonFunc::GetNumber(curline, 'r', 'R');
	if (!temp.isEmpty()) {
		R = temp.toFloat();
		HasR = true;
		flag = 1;
	}
	//if (curline.contains("R") || curline.contains("r")) {//R为工件单边R弧的半径。R为带符号，“+”表示圆弧角小于180度;“-”表示圆弧角大于180度。其中“+”可以省略。	
	//	int a = -1;
	//	for (int i = 0; i < curline.size(); i++) {
	//		if (curline[i] == 'R' || curline[i] == 'r')
	//		{
	//			a = i + 1;
	//			continue;
	//		}
	//		if (a != -1) {

	//			if (((curline[i] <'0' || curline[i] >'9') && !(curline[i] == '.' || curline[i] == '-')) || i == curline.size() - 1)
	//			{
	//				if (i == curline.size() - 1)
	//					R = curline.mid(a, i - a + 1).toFloat();
	//				else
	//					R = curline.mid(a, i - a).toFloat();
	//				HasR = true;
	//				flag = 1;
	//				break;
	//			}
	//		}

	//	}
	//}
	if (!hZ)
	{
		float x1, x2, y1, y2;
		Circle_Center(sX, sY, x, y, R, x1, y1, x2, y2);
		bool bG02 = IsG02;
		if (x1 == x2&&y1 == y2) {
			curArc.x = x1;
			curArc.y = y1;
			curArc.z = z;
		}
		else if (GetRealCenterPoint(sX, sY, x, y, R, x1, y1, bG02)) {
			curArc.x = x1;
			curArc.y = y1;
			curArc.z = z;
		}
		else {
			curArc.x = x2;
			curArc.y = y2;
			curArc.z = z;
		}

		float s, e;
		s = atan2f(sY - curArc.y, sX - curArc.x);
		e = atan2f(y - curArc.y, x - curArc.x);

		float rMax, rMin;

		if (abs(s - e) > Pi) {
			rMax = abs(s - e);
			rMin = PI * 2 - rMax;
		}
		else {
			rMin = abs(s - e);
			rMax = PI * 2 - rMin;
		}


		if (IsG02)
			curArc.sRad = e;
		else
			curArc.sRad = s;

		if (R > 0)
			curArc.rad = rMin;
		else
			curArc.rad = rMax;

		curArc.flag = 0;
		curArc.R = abs(R);
		if (flag != -1)
			Arcs.push_back(curArc);
	}

}

void AnalysisG::InsertArcIJK(QString curline)// I\J\K 等于 圆心相应坐标减去起始点相应坐标 
{
	bool hX = false;
	bool hY = false;
	bool hZ = false;

	float I = 0;
	float J = 0;
	float K = 0;
	float R = 0;

	float sX = 0;//起点坐标
	float sY = 0;
	float sZ = 0;

	float ArcX = 0;//圆心坐标
	float ArcY = 0;
	float ArcZ = 0;

	float  radian = 0;//弧度
	float  sradian = 0;//起点弧度

	sX = x;
	sY = y;
	sZ = z;
	int flag = -1;
	
	QString temp = SammonFunc::GetNumber(curline, 'x', 'X');
	if (!temp.isEmpty()) {
		if (IsAbsolute) {
			x = temp.toFloat();
		}
		else {
			x += temp.toFloat();
		}
		hX = true;
		flag = 1;
	}

	temp = SammonFunc::GetNumber(curline, 'y', 'Y');
	if (!temp.isEmpty()) {
		if (IsAbsolute) {
			y = temp.toFloat();
		}
		else {
			y += temp.toFloat();
		}
		hY = true;
		flag = 1;
	}

	temp = SammonFunc::GetNumber(curline, 'z', 'Z');
	if (!temp.isEmpty()) {
		if (IsAbsolute) {
			z = temp.toFloat();
		}
		else {
			z += temp.toFloat();
		}
		hZ= true;
		flag = 1;
	}
	if (flag == -1)return;

	temp = SammonFunc::GetNumber(curline, 'i', 'I');
	if (!temp.isEmpty()) {
		I = temp.toFloat();
		ArcX = I + sX;
	}
	
	temp = SammonFunc::GetNumber(curline, 'j', 'J');
	if (!temp.isEmpty()) {
		J = temp.toFloat();
		ArcY = sY + J;
	}

	temp = SammonFunc::GetNumber(curline, 'k', 'K');
	if (!temp.isEmpty()) {
		K = temp.toFloat();
		ArcZ = sZ + K;
	}
	if (ArcFlag==0)
	{
		//两点求弧度  arctan[(y2-y1)/(x2-x1)]
		R = sqrt(I*I + J*J);

		float s, e;
		s = atan2f(sY - ArcY, sX - ArcX);
		e = atan2f(y - ArcY, x - ArcX);

		if (s == e) {
			radian = 2 * Pi;
			sradian = e;
		}
		else {
			float t = s - e;
			if (t > 0) {
				if (IsG02) {
					sradian = s;
					radian = -t;
				}
				else {
					sradian = s;
					radian = 2 * PI - t;
				}
			}
			else {
				if (IsG02) {
					sradian = s;
					radian = -(2 * Pi + t);
				}
				else {
					sradian = s;
					radian = -t;
				}
			}
		}
		curArc.x = ArcX;
		curArc.y = ArcY;
		curArc.z = z;
		curArc.sRad = sradian;
		curArc.rad = radian;
		curArc.flag = 0;
		curArc.R = R;
		Arcs.push_back(curArc);
	}
	else if (ArcFlag==2)//未测试
	{
		R = sqrt(J*J + K*K);
		float s, e;
		//s = atan2f(sY - ArcY, sZ - ArcZ );
		//e = atan2f(y - ArcY, z - ArcZ);

		s = atan2f(sZ - ArcZ, sY - ArcY);
		e = atan2f(z - ArcZ, y - ArcY);

		if (s == e) {
			radian = 2 * Pi;
			sradian = e;
		}
		else {
			float t = s - e;
			if (t > 0) {
				if (IsG02) {
					sradian = s;
					radian = -t;
				}
				else {
					sradian = s;
					radian = 2 * PI - t;
				}
			}
			else {
				if (IsG02) {
					sradian = s;
					radian = -(2 * Pi + t);
				}
				else {
					sradian = s;
					radian = -t;
				}
			}
		}
		curArc.x = x;
		curArc.y = ArcY;
		curArc.z = ArcZ;
		curArc.R = R;
		curArc.sRad = sradian;
		curArc.rad = radian;
		curArc.flag = 2;
		Arcs.push_back(curArc);
	}
	else {// X Z 平面
		R = sqrt(I*I + K*K);
		float s, e;
		s = atan2f(sZ - ArcZ, sX - ArcX);
		e = atan2f(z - ArcZ, x - ArcX);

		if (s == e) {
			radian = 2 * Pi;
			sradian = e;
		}
		else {
			float t = s - e;
			if (t > 0) {
				if (IsG02) {
					sradian = s;
					radian = 2 * PI - t;//和XY平面是反的？
				}
				else {
					sradian = s;
					radian = -t;
				}
			}
			else {
				if (IsG02) {
					sradian = s;
					radian = -t;

				}
				else {
					sradian = s;
					radian = -(2 * Pi + t);
				}
			}
		}
		curArc.x = ArcX;
		curArc.y = y;
		curArc.z = ArcZ;
		curArc.R = R;
		curArc.sRad = sradian;
		curArc.rad = radian;
		curArc.flag = 1;
		Arcs.push_back(curArc);

	}

}

bool AnalysisG::InsertDrillHoleData(int key, QString curline)
{
	bool ReturnValue = true;
	bool hasX = false;//x , y为 初始位置，可以没有（如果本来就已经在这个位置）
	bool hasY = false;

	if (curline.contains("G99")) {//返回哪个平面
		mData.isG99 = true;
		curline.replace("G99", "");
	}
	if (curline.contains("G98")) {
		mData.isG99 = false;
		curline.replace("G98", "");
	}
	QString fType = GetNumber(curline, 'G', 'g');//转孔类型
	if (!fType.isEmpty()) {
		mData.Type = fType.toInt();
	}

	QString strX = GetNumber(curline, 'X', 'x');//x轴 是否需要运动
	if (!strX.isEmpty()) {
		mData.X = strX;
		hasX = true;
	}


	QString strY = GetNumber(curline, 'Y', 'y');//y轴 是否需要运动
	if (!strY.isEmpty()) {
		mData.Y = strY;
		hasY = true;
	}
	if (hasX&&hasY)
		mData.isNeedStep1 = 3;
	else if (hasX && !hasY)
		mData.isNeedStep1 = 1;
	else if (!hasX && hasY)
		mData.isNeedStep1 = 2;
	else
		mData.isNeedStep1 = 0;

	QString strZ = GetNumber(curline, 'Z', 'z');//z轴 转孔深度  
	if (!strZ.isEmpty()) {
		mData.Z = strZ;
		mData.hasZ = true;
	}

	QString strR = GetNumber(curline, 'R', 'r');//z轴 参考面位置
	if (!strR.isEmpty()) {
		mData.R = strR;
		mData.hasR = true;
	}

	QString strF = GetNumber(curline, 'F', 'f');//z轴 转孔进给
	if (!strF.isEmpty()) {
		mData.F = strF;
		mData.hasF = true;
	}

	QString strP = GetNumber(curline, 'P', 'p');//孔低 暂停时间
	if (!strP.isEmpty()) {
		mData.P = strP;
		mData.hasP = true;
	}

	QString strQ = GetNumber(curline, 'Q', 'q');//每次进给速度
	if (!strQ.isEmpty()) {
		mData.Q = strQ;
		mData.hasQ = true;
	}
	if (!mData.isFirst) {
		switch (mData.Type)
		{
		case 81:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G81 (G99) X__ Y__ Z__ R__ F__";
			break;
		case 82:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF&&mData.hasP;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G82 (G99) X__ Y__ Z__ R__P__ F__";
			break;
		case 73:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF&&mData.hasQ;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G73 (G99) X__ Y__ Z__ R__Q__ F__";
			break;
		case 83:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF&&mData.hasQ;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G83 (G99) X__ Y__ Z__ R__Q__ F__";
			break;
		case 85:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G85 (G99) X__ Y__ Z__ R__ F__";
			break;
		case 86:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G86 (G99) X__ Y__ Z__ R__ F__";
			break;
		case 89:
			mData.isFirst = true;
			ReturnValue = mData.hasZ&&mData.hasR&&mData.hasF&&mData.hasP;
			if (!ReturnValue)
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G89 (G99) X__ Y__ Z__ R__P__ F__";
			break;

		}
	}
	SammonFunc::DrillHoleMap.insert(key, mData);
	return ReturnValue;
}

QString AnalysisG::GetNumber(QString curline, char upper, char lower)//获取 字符后面的数字；
{
	QString Code = "";
	for (QString::Iterator it = curline.begin(); it != curline.end(); it++) {
		if (*it == upper || *it == lower) {
			int i = 0;
			while (++i) {
				if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == ' ' || *(it + i) == '-') || (it + i) == curline.end()) {
					return Code;
				}
				else {
					Code += *(it + i);
				}
			}
		}
	}
	return Code;
}

bool AnalysisG::GetValidline(QString & curline, int key)
{
	for (QString::Iterator it = curline.begin(); it != curline.end(); it++) {
		if (*it == 'G' || *it == 'g') {
			QString GCode;
			int i = 0;
			while (++i) {
				if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == '-') || (it + i) == curline.end()) {
					break;
				}
				else {
					GCode += *(it + i);
				}
			}
			if (ErrorGCode.contains(GCode)) {//判断 是否是有效
				curline = *it + GCode;
				errorMsg = ExternalText::Nonsupport.arg(key) + curline;
				return false;
			}
			else if (GCode == "43" && !(curline.contains('H') || curline.contains('h'))) {//判断 G43指令是否正确
				curline = *it + GCode;
				errorMsg = ExternalText::GErrorCode.arg(key).arg(curline) + "G43H1";
				return false;
			}
			else if (GCode == "21") {
				curline = "G04P10";
				return 1;
			}
			else if (TrGCode.contains(GCode)) {//判断 是否需要转换
				NeedTr = true;
			}
			else if (DrillHoleCode.contains(GCode)) {//判断 是否包含转孔指令
				if (GCode == "80") {
					//curline = "M999";
					IsDrillHole = false;
					mData.clear();
					return 1;
				}
				else {
					if (GCode.toInt() != mData.Type)
						mData.clear();
					IsDrillHole = true;
				}
			}
		}

		else if (*it == 'M' || *it == 'm') {
			QString MCode;
			int i = 0;
			while (++i) {
				if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == '-') || (it + i) == curline.end()) {
					break;
				}
				else {
					MCode += *(it + i);
				}
			}
			if (MCode.toInt() == 3 || MCode.toInt() == 4) {
				if (!SammonFunc::CheckContains(curline, 2, "S", "s")) {
					isM03M04 = true;
				}
				if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
					isM03M04 = true;
			}
			else if (MCode.toInt() == 5) {
				if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
					isM05 = true;
			}
			else if (MCode.toInt() == 7) {
				if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
					isM07 = true;
			}
			else if (MCode.toInt() == 8) {
				if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
					isM08 = true;
			}
			else if (MCode.toInt() == 9) {
				if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
					isM09 = true;
			}

			if (NeedDealMCode.contains(MCode) || MCode.toInt() >= 100) {//判断 是否特殊处理
				NeedDealM = true;
			}
		}
		else if (*it == 'T' || *it == 't') {
			QString TCode;
			int i = 0;
			while (++i) {
				if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == '-') || (it + i) == curline.end()) {
					break;
				}
				else {
					TCode += *(it + i);
				}
			}
			if (TCode.toInt() >= 1 && TCode.toInt() <= 16) {
				if (readIni.GetToolChangeOpt().toInt() != 0) {
					NeedDealM = true;
					SammonFunc::TCodeMap.insert(key, TCode.toInt());
				}
				else {
					curline = "%";
					return 1;
				}
			}
		}

	}
	if (IsDrillHole) {
		if (!InsertDrillHoleData(key, curline))return 0;
		curline = "M00";
		return 1;
	}
	if (isM03M04) {

		if (!SammonFunc::CheckContains(curline, 2, "S", "s")) {
			QString str = "S";
			str += QString::number(mcc->GetParameterValue(106));
			curline += str;
		}
		if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p")) {
			curline += "G04P" + readIni.GetSpindleOpen();
		}
		isM03M04 = false;
	}
	else if (isM05) {
		if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
		curline += "G04P" + readIni.GetSpindleClose();
		isM05 = false;
	}
	else if (isM07) {
		if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
		curline += "G04P" + readIni.GetM07Time();
		isM07 = false;
	}
	else if (isM08) {
		if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
		curline += "G04P" + readIni.GetM08Time();
		isM08 = false;
	}
	else if (isM09) {
		if (!SammonFunc::CheckContains(curline, 4, "X", "x", "P", "p"))
		curline += "G04P" + readIni.GetM09Time();
		isM09 = false;
	}
	if (NeedTr) {
		//处理需要特殊处理的G代码 暂时全部替换M00
		SammonFunc::ReplaceCodeMap.insert(key, curline);
		curline = "M00";
		NeedTr = false;
		return true;
	}
	if (NeedDealM) {
		//处理需要特殊处理的M代码 暂时全部替换M00
		SammonFunc::ReplaceCodeMap.insert(key, curline);
		curline = "M00";
		NeedDealM = false;
		return true;
	}
	return true;
}

void AnalysisG::ShowGCode(QStringList&  List)
{
	clear();
	foreach(QString curline, List) {
		for (QString::Iterator it = curline.begin(); it != curline.end(); it++) {
			if (*it == 'G' || *it == 'g') {
				QString GCode;
				int i = 0;
				while (++i) {
					if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == '-') || (it + i) == curline.end()) {
						break;
					}
					else {
						GCode += *(it + i);
					}
				}
				if (GCode == "0" || GCode == "1" || GCode == "00" || GCode == "01") {	//判断 是否是圆弧
					LastisArc = IsArc;
					LastisG0 = isG0;

					IsArc = false;
					if (GCode.toInt() == 0)
						isG0 = true;
					else
						isG0 = false;


				}
				else if (GCode == "02" || GCode == "2") {
					IsArc = true;
					IsG02 = true;
				}
				else if (GCode == "03" || GCode == "3") {
					IsArc = true;
					IsG02 = false;
				}
				else if (GCode == "90")	//判断 是否是绝对增量
					IsAbsolute = true;
				else if (GCode == "91")
					IsAbsolute = false;
				else if (GCode == "17") {
					ArcFlag = 0;
				}
				else if (GCode == "18") {
					ArcFlag = 1;
				}
				else if (GCode == "19") {
					ArcFlag = 2;
				}
			}
		}
		InsertPoint(curline);
	}
}

void AnalysisG::ShowGCode(QTextStream & stream)
{
	QString curline;
	while (!stream.atEnd()) {
		curline = stream.readLine();
		for (QString::Iterator it = curline.begin(); it != curline.end(); it++) {
			if (*it == 'G' || *it == 'g') {
				QString GCode;
				int i = 0;
				while (++i) {
					if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == '-') || (it + i) == curline.end()) {
						break;
					}
					else {
						GCode += *(it + i);
					}
				}
				if (GCode == "0" || GCode == "1" || GCode == "00" || GCode == "01") {	//判断 是否是圆弧
					LastisArc = IsArc;
					LastisG0 = isG0;

					IsArc = false;
					if (GCode.toInt() == 0)
						isG0 = true;
					else
						isG0 = false;


				}
				else if (GCode == "02" || GCode == "2") {
					IsArc = true;
					IsG02 = true;
				}
				else if (GCode == "03" || GCode == "3") {
					IsArc = true;
					IsG02 = false;
				}
				else if (GCode == "90")	//判断 是否是绝对增量
					IsAbsolute = true;
				else if (GCode == "91")
					IsAbsolute = false;
				else if (GCode == "17") {
					ArcFlag = 0;
				}
				else if (GCode == "18") {
					ArcFlag = 1;
				}
				else if (GCode == "19") {
					ArcFlag = 2;
				}
			}
		}
		InsertPoint(curline);
	}
}