#pragma once

#include <DL_CreationAdapter.h>
#include <QList>
#include <QTextStream>
#include <QFile>
#include<qbuffer.h>
struct _Polyline
{
	_Polyline() :PolylineData(0,0,0,0,0){}
	DL_PolylineData PolylineData;
	QList<DL_VertexData> Vertexs;
};

struct MyPolyline {
	QList<DL_VertexData> Vertexs;
	DL_VertexData GetFirstPoint() {
		return Vertexs[0];
	}
	DL_VertexData GetLastPoint() {
		return Vertexs[Vertexs.size()-1];
	}
};


class DXFSender :public QObject {
	Q_OBJECT
public: 
	signals : void sendstream(QTextStream&);
	 signals: void loadfromstream(QTextStream&,int);
};

class DXFAdapter : public DL_CreationAdapter
{
	
public:
	DXFAdapter();
	~DXFAdapter();
	void Func();
	void OutputGCode(QString str="");
	void SetUpValue(QString s) { UpValue = s; }
	QTextStream& GetOutputSteam() { return out; }
	void clear() {
		Lines.clear();
		 Arcs.clear();
		 Circles.clear();
		 Polylines.clear();
		 Splines.clear();
		Ellipses.clear();
		MyPolylines.clear();
	}
	void SetXYZG0(double x, double y, double z,double depth,bool usefiledepth) {
		bool b1 = abs(x - curX) <= 0.0001;
		bool b2 = abs(y - curY) <= 0.0001;
		bool b3 = abs(z - curZ) <= 0.0001;


		if (b1&&b2&&b3) {

		}
		else {
			if (useFileDepth) {
				out << "G00 X" << x << " Y" << y << " Z" << UpValue << "\n";
				out << "G00 Z" <<z << "\n";
				RowCount += 2;
			}
			else {
				out << "G00 X" << x << " Y" << y << " Z" << UpValue << "\n";
				out << "G00 Z" << depth << "\n";
				RowCount += 2;
			}
		}
	}
	void SetXYZValue(double x, double y, double z, double depth, bool usefiledepth) {
		curX = x;
		curY = y;
		if (usefiledepth) {
			curZ = z;
		}
		else
		{
			curZ = depth;
		}
	}
private:
	//void LinesCreateGCode(QTextStream&,double depth, bool useFlieDepth);//Lines 数据生成G代码
	//void ArcsLinesCreateGCode(QTextStream&, double depth, bool useFlieDepth);
	void Lines_ArcCreateGCode(QTextStream&, double depth, bool useFlieDepth);
	void CirclesCreateGCode(QTextStream&, double depth, bool useFlieDepth);
	void PolylinesCreateGCode(QTextStream&, double depth, bool useFlieDepth);
	void SplinesCreateGCode(QTextStream&, double depth, bool useFlieDepth);
	void EllipsesCreateGCode(QTextStream&out, double depth, bool useFlieDepth);
	QString polylineToArc(double bulge, double x1, double y1, double x2, double y2);

	virtual void addLine(const DL_LineData& data);
	virtual void addArc(const DL_ArcData& data);
	virtual void addCircle(const DL_CircleData& data);
	virtual void addPolyline(const DL_PolylineData& data);//Polyline的顶点数据 在Vertex 中
	virtual void addVertex(const DL_VertexData& data);//Polyline的顶点数据 在Vertex 中
	virtual void addEllipse(const DL_EllipseData&);

	//virtual void add3dFace(const DL_3dFaceData& data);

public:
	
	QList<MyPolyline>MyPolylines;//将连续的线段 或者弧 转化为 Polyline 
	QList<DL_LineData> Lines;
	QList<DL_ArcData> Arcs;
	QList<DL_CircleData> Circles;
	QList<_Polyline> Polylines;
	QList<DL_SplineData> Splines;
	QList<DL_EllipseData>Ellipses;
	QString UpValue = "10";//z 抬刀高度
	QString mMaxDepth="-1"; //加工深度
	QString mDepth="-1"; //每次加工量
	bool useFileDepth = false;
	bool DanDuJiaGong = false;
	int RowCount =0;
	int idx = 0;
	QTextStream out;
	QBuffer buffer;
	DXFSender dxfsender;
private:
	double curX = 0, curY = 0, curZ = 0;
};
