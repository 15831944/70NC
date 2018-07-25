#pragma once

#include "mccdll.h"
#include "readIni.h"
#define Pi 3.141592654
#define PI Pi
#define BIGSIZE 1900000
#include<QList> 
struct Point {
	double x;
	double y;
	double z;
};
struct Line {
	QList<Point> Points;
};

struct ArcData {
	double x, y, z;//中心坐标
	double sRad, rad;//起始弧，弧长
	double R;
	int flag; // in xy =0 in xz =1 in yz =2
};
struct Pos6A {
	double x;
	double y;
	double z;
	double a;
	double b;
	double c;

	bool hx = false;
	bool hy = false;
	bool hz = false;
	bool isOk() {
		return hx&&hy&&hz;
	}
	void clear() {
		x = 0;
		y = 0;
		z = 0;
		hx = false;
		hy = false;
		hz = false;
	}

};

struct DrillHoleData{
	int Type;
	
	bool isG99;
	QString X;
	QString Y;
	QString Z;
	QString R;
	QString F;
	QString P;
	QString Q;

	int isNeedStep1;//0 NO x,NO y;   1 ->has x     2 ->has y; 3 -> hasx  hasy ;

	bool hasZ = false;
	bool hasR = false;
	bool hasP = false;
	bool hasF = false;
	bool hasQ = false;
	bool isFirst = false;
	void clear(){
		isFirst = false;
		hasZ = false;
		hasR = false;
		hasP = false;
		hasF = false;
		hasQ = false;
		isG99 = false;
	}
};