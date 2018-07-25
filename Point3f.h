#pragma once

struct Vertex //¶¥µã½á¹¹
{
	Vertex() {}
	Vertex(float x, float y, float z)
	{
		_x = x;  _y = y;  _z = z;
	}
	float _x, _y, _z;
	static const unsigned long FVF;
};

class Point3f
{
public:
	Point3f();
	Point3f(float _x, float _y, float _z);
	int SetParam(float _x, float _y, float _z);
	inline Vertex IVertex()
	{
		return Vertex(x, y, z);
	}
private:
	float x, y, z;
};

