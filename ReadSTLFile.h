#pragma once
#include<vector>
#include"Point3f.h"
using namespace std;

class ReadSTLFile
{
public:
	bool ReadFile(const char *cfilename);
	int NumTri();
	vector<Point3f>& PointList();
	vector<vector<Point3f>>& GetGeometrys() {return geometrys;}
private:
	vector<Point3f> pointList;
	vector<vector<Point3f>> geometrys;

	unsigned int unTriangles;
	bool ReadASCII(const char *cfilename);
	bool ReadBinary(const char *cfilename);

	char* memwriter;
	int cpyint(const char*& p);
	float cpyfloat(const char*& p);
};