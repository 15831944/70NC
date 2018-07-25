#include "DXFAdapter.h"
#define PI 3.1415926

DXFAdapter::DXFAdapter()
	: DL_CreationAdapter()
{
}

DXFAdapter::~DXFAdapter()
{
}

void DXFAdapter::Func()
{
	///////////////排序  应该   让线 不再是 一条一条的直线排序，，而是一个点 一个点 的连续结构体 类似   Polylines

	QList<MyPolyline> ArcPolyline;
	QList<MyPolyline> LinePolyline;
	if (Lines.size() > 0) {
		QList<DL_LineData> TempLines = Lines;
		
	FLAG0:
		MyPolyline polyline;
		DL_LineData theLine = TempLines.takeAt(0);
		polyline.Vertexs.push_back(theLine.GetPoint1());
		polyline.Vertexs.push_back(theLine.GetPoint2());

	FLAG1:
		for (int i = 0; i < TempLines.size(); i++) {
			if (polyline.GetLastPoint() == TempLines[i].GetPoint1()) {
				polyline.Vertexs.push_back(TempLines[i].GetPoint2());
				TempLines.removeAt(i);
				goto FLAG1;
			}
			if (polyline.GetLastPoint() == TempLines[i].GetPoint2()) {
				polyline.Vertexs.push_back(TempLines[i].GetPoint1());
				TempLines.removeAt(i);
				goto FLAG1;
			}

		}
	FLAG2:
		for (int i = 0; i < TempLines.size(); i++) {
			if (polyline.GetFirstPoint() == TempLines[i].GetPoint1()) {
				polyline.Vertexs.push_front(TempLines[i].GetPoint2());
				TempLines.removeAt(i);
				goto FLAG2;
			}
			if (polyline.GetFirstPoint() == TempLines[i].GetPoint2()) {
				polyline.Vertexs.push_front(TempLines[i].GetPoint1());
				TempLines.removeAt(i);
				goto FLAG2;
			}

		}
		LinePolyline.push_back(polyline);
		if (TempLines.size() > 0) {
			goto FLAG0;
		}

	}
	////////////////////////////////////////////////////////////
	if (Arcs.size() > 0) {
		QList<DL_ArcData> TempArcs = Arcs;
	
	FLAG10:
		MyPolyline polyline;
		DL_ArcData curArc = TempArcs.takeAt(0);
		polyline.Vertexs.push_back(curArc.GetPoint1());
		polyline.Vertexs[0].Arc_cx = curArc.cx;
		polyline.Vertexs[0].Arc_cy = curArc.cy;
		polyline.Vertexs[0].Arc_cz = curArc.cz;
		polyline.Vertexs[0].isArc = true;
		polyline.Vertexs.push_back(curArc.GetPoint2());

	FLAG11:
		for (int i = 0; i < TempArcs.size(); i++) {
			if (polyline.GetLastPoint() == TempArcs[i].GetPoint1()) {					
				polyline.Vertexs[polyline.Vertexs.size() - 1].Arc_cx = TempArcs[i].cx;
				polyline.Vertexs[polyline.Vertexs.size() - 1].Arc_cy = TempArcs[i].cy;
				polyline.Vertexs[polyline.Vertexs.size() - 1].Arc_cz = TempArcs[i].cz;
				polyline.Vertexs[polyline.Vertexs.size() - 1].isArc = true;
				polyline.Vertexs.push_back(TempArcs[i].GetPoint2());
				TempArcs.removeAt(i);
				goto FLAG11;
			}
		}
	FLAG12:
		for (int i = 0; i < TempArcs.size(); i++) {
			if (polyline.GetFirstPoint() == TempArcs[i].GetPoint2()) {
				polyline.Vertexs.push_front(TempArcs[i].GetPoint1());
				polyline.Vertexs[0].Arc_cx = TempArcs[i].cx;
				polyline.Vertexs[0].Arc_cy = TempArcs[i].cy;
				polyline.Vertexs[0].Arc_cz = TempArcs[i].cz;		
				polyline.Vertexs[0].isArc = true;
				TempArcs.removeAt(i);
				goto FLAG11;
			}
		}
		ArcPolyline.push_back(polyline);
		if (TempArcs.size() > 0) {
			goto FLAG10;
		}
	}

	if (LinePolyline.size() > 0 && ArcPolyline.size() > 0) {

	Flag100:
		MyPolylines.push_back(ArcPolyline.takeAt(0));

	Flag101:
		DL_VertexData point0 = MyPolylines[MyPolylines.size() - 1].GetFirstPoint();
		DL_VertexData point1 = MyPolylines[MyPolylines.size() - 1].GetLastPoint();

		for (int i = 0; i < LinePolyline.size(); i++) {
			if (point0 == LinePolyline[i].GetFirstPoint()) {
				//起始点重合  先线，再弧 ，线逆序
				MyPolyline temp = LinePolyline.takeAt(i);
				for (int j = 0; j < temp.Vertexs.size(); j++) {
					MyPolylines[MyPolylines.size() - 1].Vertexs.push_front(temp.Vertexs[j]);
				}
				goto Flag101;
			}
			if (point0 == LinePolyline[i].GetLastPoint()) {
				// 先线，再弧
				MyPolyline temp = LinePolyline.takeAt(i);
				for (int j = temp.Vertexs.size() - 1; j >= 0; j--) {
					MyPolylines[MyPolylines.size() - 1].Vertexs.push_front(temp.Vertexs[j]);
				}
				goto Flag101;
			}
			if (point1 == LinePolyline[i].GetFirstPoint()) {
				//先弧，再线
				MyPolyline temp = LinePolyline.takeAt(i);
				for (int j = 0; j < temp.Vertexs.size(); j++) {
					MyPolylines[MyPolylines.size() - 1].Vertexs.push_back(temp.Vertexs[j]);
				}
				goto Flag101;
			}
			if (point1 == LinePolyline[i].GetLastPoint()) {
				//先弧，再线，线逆序
				MyPolyline temp = LinePolyline.takeAt(i);
				for (int j = temp.Vertexs.size() - 1; j >= 0; j--) {
					MyPolylines[MyPolylines.size() - 1].Vertexs.push_back(temp.Vertexs[j]);
				}
				goto Flag101;
			}
		}

		for (int i = 0; i < ArcPolyline.size(); i++) {
			if (point0 == ArcPolyline[i].GetLastPoint()) {
				MyPolyline temp = ArcPolyline.takeAt(i);
				MyPolylines[MyPolylines.size() - 1].Vertexs.push_front(temp.GetLastPoint());
				MyPolylines[MyPolylines.size() - 1].Vertexs.push_front(temp.GetFirstPoint());
				goto Flag101;
			}
			if (point1 == ArcPolyline[i].GetFirstPoint()) {
				MyPolyline temp = ArcPolyline.takeAt(i);
				MyPolylines[MyPolylines.size() - 1].Vertexs.push_back(temp.GetFirstPoint());
				MyPolylines[MyPolylines.size() - 1].Vertexs.push_back(temp.GetLastPoint());
				goto Flag101;
			}
		}
		while (LinePolyline.size() > 0) {
			MyPolylines.push_back(LinePolyline.takeAt(0));
		}
	}
}

void DXFAdapter::OutputGCode(QString str)
{
	
	double MaxDepth = mMaxDepth.toDouble();
	double Depth = mDepth.toDouble();
	RowCount = 0;
	if (buffer.open(QIODevice::ReadWrite|QIODevice::Truncate)) {
		out.setDevice(&buffer);
		out << "G90"<<"\n";
		RowCount++;
		if (useFileDepth) {
			Lines_ArcCreateGCode(out, MaxDepth, useFileDepth);
			CirclesCreateGCode(out, MaxDepth, useFileDepth);
			PolylinesCreateGCode(out, MaxDepth, useFileDepth);
			SplinesCreateGCode(out, MaxDepth, useFileDepth);
			EllipsesCreateGCode(out, MaxDepth, useFileDepth);
		}
		else {
			double CurDepth;
			if (!DanDuJiaGong) {//	
				for (CurDepth = Depth; CurDepth >= MaxDepth; CurDepth += Depth) {
					Lines_ArcCreateGCode(out, CurDepth, useFileDepth);
					CirclesCreateGCode(out, CurDepth, useFileDepth);
					PolylinesCreateGCode(out, CurDepth, useFileDepth);
					SplinesCreateGCode(out, CurDepth, useFileDepth);
					EllipsesCreateGCode(out, CurDepth, useFileDepth);
				}
				if (CurDepth - Depth > MaxDepth) {
					Lines_ArcCreateGCode(out, MaxDepth, useFileDepth);
					CirclesCreateGCode(out, MaxDepth, useFileDepth);
					PolylinesCreateGCode(out, MaxDepth, useFileDepth);
					SplinesCreateGCode(out, MaxDepth, useFileDepth);
					EllipsesCreateGCode(out, MaxDepth, useFileDepth);
				}
			}
			else {//一个形状加工完 在加工下一个
				for (CurDepth = Depth; CurDepth >= MaxDepth; CurDepth += Depth) {
					Lines_ArcCreateGCode(out, CurDepth, useFileDepth);
				}
				if (CurDepth - Depth > MaxDepth) {
					Lines_ArcCreateGCode(out, MaxDepth, useFileDepth);
				}
				for (CurDepth = Depth; CurDepth >= MaxDepth; CurDepth += Depth) {
					CirclesCreateGCode(out, CurDepth, useFileDepth);
				}
				if (CurDepth - Depth > MaxDepth) {
					CirclesCreateGCode(out, MaxDepth, useFileDepth);
				}
				for (CurDepth = Depth; CurDepth >= MaxDepth; CurDepth += Depth) {
					PolylinesCreateGCode(out, CurDepth, useFileDepth);
				}
				if (CurDepth - Depth > MaxDepth) {
					PolylinesCreateGCode(out, MaxDepth, useFileDepth);
				}
				for (CurDepth = Depth; CurDepth >= MaxDepth; CurDepth += Depth) {
					SplinesCreateGCode(out, CurDepth, useFileDepth);
				}
				if (CurDepth - Depth > MaxDepth) {
					SplinesCreateGCode(out, MaxDepth, useFileDepth);
				}
				for (CurDepth = Depth; CurDepth >= MaxDepth; CurDepth += Depth) {
					EllipsesCreateGCode(out, CurDepth, useFileDepth);
				}
				if (CurDepth - Depth > MaxDepth) {
					EllipsesCreateGCode(out, MaxDepth, useFileDepth);
				}
			}
		}
	}
	if (str.isEmpty())
		emit dxfsender.sendstream(out);
	else
		emit dxfsender.loadfromstream(out,RowCount);
	buffer.close();
}

//void DXFAdapter::LinesCreateGCode(QTextStream &out, double depth,bool useFlieDepth)
//{
//	if (Lines.size() > 0) {
//		for (int i = 0; i < Lines.size(); i++) {
//
//			out<< "G00 X" << Lines[i].x1 << " Y" << Lines[i].y1 <<" Z"<< UpValue << "\n";
//			if(!useFlieDepth)	out << "G00 Z" << depth << "\n";
//			else	out << "G00 Z" << Lines[i].z1 << "\n";
//			out << "G01 X" << Lines[i].x2 << " Y" << Lines[i].y2<< "\n";
//			RowCount += 3;
//		}
//	}
//}
//
//void DXFAdapter::ArcsLinesCreateGCode(QTextStream &out, double depth, bool useFlieDepth)
//{	//导出的数据 angle1 到 angle2 一定是逆时针
//	if (Arcs.size() > 0) {
//		for (int i = 0; i<Arcs.size(); i++) {
//			double x1,x2,y1,y2;
//
//			double ddd = PI*Arcs[i].angle1 / 180;
//			double cdd = cos(ddd);
//			x1 = Arcs[i].cx + Arcs[i].radius*cos(PI*Arcs[i].angle1 / 180);
//			y1 = Arcs[i].cy + Arcs[i].radius*sin(PI*Arcs[i].angle1 / 180);
//			x2 = Arcs[i].cx + Arcs[i].radius*cos(PI*Arcs[i].angle2 / 180);
//			y2 = Arcs[i].cy + Arcs[i].radius*sin(PI*Arcs[i].angle2 / 180);
//
//
//			double dx = Arcs[i].cx - x1;
//			double dy = Arcs[i].cy - y1;
//			dx = abs(dx) <= 0.0001 ? 0 : dx;
//			dy = abs(dy) <= 0.0001 ? 0 : dy;
//				out << "G00 X" << x1 << " Y" << y1 << " Z" << UpValue << "\n";
//			if (!useFlieDepth)	out << "G0 Z" << depth << "\n";
//			else	out << "G0 Z" << Arcs[i].cz << "\n";
//			out << " G03 X" << x2 << " Y" << y2 << " I" << dx << " J" << dy << "\n";
//			RowCount += 3;
//		}
//	}
//}

void DXFAdapter::Lines_ArcCreateGCode(QTextStream &, double depth, bool useFlieDepth)
{
	if (MyPolylines.size() > 0) {
		for (int i = 0; i < MyPolylines.size(); i++) {
			MyPolyline temp = MyPolylines[i];
			QList<DL_VertexData> Vertexs = MyPolylines[i].Vertexs;
			SetXYZG0(Vertexs[0].x, Vertexs[0].y, Vertexs[0].z, depth, useFlieDepth);
			for (int idx = 0; idx < Vertexs.size() - 1; idx++) {
				if (Vertexs[idx].isArc) {
					double dx = Vertexs[idx].Arc_cx - Vertexs[idx].x;
					double dy = Vertexs[idx].Arc_cy - Vertexs[idx].y;
					dx = abs(dx) <= 0.0001 ? 0 : dx;
					dy = abs(dy) <= 0.0001 ? 0 : dy;
					out << " G03 X" << Vertexs[idx + 1].x << " Y" << Vertexs[idx + 1].y << " I" << dx << " J" << dy << "\n";
					RowCount++;
							
				}
				else {
					out << "G01 X" << Vertexs[idx + 1].x << " Y" << Vertexs[idx + 1].y << "\n";
					RowCount++;
				}
			}
			SetXYZValue(Vertexs[Vertexs.size()-1].x, Vertexs[Vertexs.size() - 1].y, Vertexs[Vertexs.size() - 1].z, depth, useFlieDepth);
		}
	}
}

void DXFAdapter::CirclesCreateGCode(QTextStream &out, double depth, bool useFlieDepth)
{	
	if (Circles.size() > 0) {
		for (int i = 0; i<Circles.size(); i++) {
	
			double  I,x;
			I = Circles[i].radius;	
			x = Circles[i].cx - I;
			SetXYZG0(x, Circles[i].cy, Circles[i].cz, depth, useFlieDepth);
			out << " G02 X" << x << " Y" << Circles[i].cy << " I" << I << " J" << "0" << "\n";//G02 X_Y_I_J_
			RowCount ++;
			SetXYZValue(x, Circles[i].cy, Circles[i].cz, depth, useFlieDepth);
		}
	}
}

void DXFAdapter::PolylinesCreateGCode(QTextStream &out, double depth, bool useFlieDepth)
{	
	if (Polylines.size() > 0) {
		for (int i = 0; i < Polylines.size(); i++) {
			SetXYZG0(Polylines[i].Vertexs[0].x, Polylines[i].Vertexs[0].y, Polylines[i].Vertexs[0].z, depth, useFlieDepth);

			QList<DL_VertexData>& vertexs = Polylines[i].Vertexs;
			int flags = Polylines[i].PolylineData.flags;
			switch (flags) {
			case 0:
			case 1://闭合多线段，或在M方向闭合的多边形网格
				for (int j = 0; j < vertexs.size() - 1; j++) {
					if (vertexs[j].bulge == (double)0) {		
						out << "G01 X" <<vertexs[j + 1].x << " Y" << vertexs[j + 1].y << "\n";		
					}
					else {
						out << polylineToArc(vertexs[j].bulge, vertexs[j].x, vertexs[j].y, vertexs[j+1].x, vertexs[j+1].y);			
					}
					SetXYZValue(vertexs[j + 1].x, vertexs[j + 1].y, vertexs[j + 1].z, depth, useFlieDepth);
					RowCount++;
				}
				if (flags == 1) {//如果是封闭多线段
					if (vertexs[vertexs.size()-1].bulge == (double)0) {	//直线			
						out << "G01 X" << vertexs[0].x << " Y" << vertexs[0].y << "\n";
					}
					else {
						out << polylineToArc(vertexs[vertexs.size() - 1].bulge, vertexs[vertexs.size() - 1].x, vertexs[vertexs.size() - 1].y, vertexs[0].x, vertexs[0].y);
					}
					SetXYZValue(vertexs[0].x, vertexs[0].y, vertexs[0].z, depth, useFlieDepth);
					RowCount++;
				}
				break;
			case 2://曲线拟合添加了顶点
				break;
			case 4://添加样条曲线拟合添加了顶点
				break;
			case 8://三维多线段
				for (int j = 0; j < vertexs.size() - 1; j++) {
					out << "G01 X" << vertexs[j + 1].x << " Y" << vertexs[j + 1].y <<"Z"<< vertexs[j + 1].z << "\n";	
					RowCount++;
				}
				break;
			case 16://三维多边形网格
				break;
			case 32://N方向闭合的多边形网格
				break;
			case 64://多面网格
				break;
			case 128://不断的在此多线段顶点周围生成线性图案
				break;
			}	
		}
	}

}

void DXFAdapter::SplinesCreateGCode(QTextStream &out, double depth, bool useFlieDepth)
{
}
void DXFAdapter::EllipsesCreateGCode(QTextStream & out, double depth, bool useFlieDepth)
{
	if (Ellipses.size() > 0) {	
		for (int i = 0; i<Ellipses.size(); i++) {
	
			double start_angle, end_angle;
			start_angle = Ellipses[i].angle1;
			end_angle = Ellipses[i].angle2;

			double x, y, a, b,z;
			x = Ellipses[i].cx;
			y = Ellipses[i].cy;
			a = sqrt(Ellipses[i].mx*Ellipses[i].mx + Ellipses[i].my*Ellipses[i].my);
			b = Ellipses[i].ratio *a;
			z = Ellipses[i].cz;
			double curx, cury;
			double n = 200;

			if (start_angle < end_angle) {
				for (int j = 1; j <= n; j++) {			
					curx = x + a* cosf((end_angle - start_angle) *(j / n)+ start_angle);
					cury = y + b*sinf((end_angle - start_angle) *(j / n)+ start_angle);
					if (j == 1) {
						SetXYZG0(curx, cury, z, depth, useFlieDepth);
					}
					if (j == n) {
						SetXYZValue(curx, cury, z, depth, useFlieDepth);
					}
					out << "G01X" << curx<< " Y" << cury<<"\n";
					RowCount++;
				}
			}
		}
	}
}
QString DXFAdapter::polylineToArc(double bulge, double x1,double y1, double x2, double y2)
{
	/*AutoCAD中约定：凸度为0是直线顶点，它与下一个顶点连接为一直线；凸度不为0是圆弧顶点，它与下一个顶点连接为一圆弧；
	凸度值为负表示顺时针圆弧，凸度值为正表示逆时针圆弧；凸度绝对值小于1表示圆弧包角小于180°，凸度
	绝对值大于1表示圆弧包角大于180°。凸度与圆弧包角的关系是：圆弧包角= 4×arctan|凸度值|。*/
	double centerAngle;//包角
	centerAngle = 4 * atan(abs(bulge));

	double L; //弦长
	L = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

	double R;//圆弧半径
	R = 0.5*L / sin(0.5*centerAngle);
	if (abs(bulge) > 1) {
		R *= -1;
	}
	QString str;
	if (bulge>0)
		str = QString("") + " G03 X" + QString::number(x2) + " Y" + QString::number(y2) + " R" + QString::number(R) + "\n";
	else
		str = QString("") + " G02 X" + QString::number(x2) + " Y" + QString::number(y2) + " R" + QString::number(R) + "\n";
	return str;
}
void DXFAdapter::addLine(const DL_LineData & data)
{
	Lines.push_back(data);
}

void DXFAdapter::addArc(const DL_ArcData & data)
{
	Arcs.push_back(data);
}

void DXFAdapter::addCircle(const DL_CircleData & data)
{
	Circles.push_back(data);
}

void DXFAdapter::addPolyline(const DL_PolylineData & data)
{
	_Polyline curPolyline;
	curPolyline.PolylineData = data;
	Polylines.push_back(curPolyline);
}

void DXFAdapter::addVertex(const DL_VertexData & data)
{
	Polylines[Polylines.size() - 1].Vertexs.push_back(data);
}



void DXFAdapter::addEllipse(const DL_EllipseData &data)
{
	Ellipses.push_back(data);
}

