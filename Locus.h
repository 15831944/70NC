#pragma once

#include <QOpenGLWidget>
#include "ui_Locus.h"
#include "AnalysisG.h"
////////////////////////////////////////////
/////自动加工轨迹
///////////////////////////////////////////
#include "datadefine.h"

class ReadSTLFile;
class Locus : public QOpenGLWidget
{
	Q_OBJECT

public:
	Locus(QWidget *parent = Q_NULLPTR);
	~Locus();
	void MySetFocus();
	bool MyGetFocus();
	void ResetLanguage();
	void UpdateAxis(float x=0,float y=0,float z=0) {//自动加工时 显示刀路
		
		int i = dxs.size() - 1;
		if (i>=0)
		{
			if (dxs[i] == x&&dys[i] == y&&dzs[i] == z)
				return;
		}	
		dxs.push_back(x);
		dys.push_back(y);
		dzs.push_back(z);
		update();
	
	}

	void clear() {
		dxs.clear();
		dys.clear();
		dzs.clear();

		update();
	}
	QPushButton* GetShowBt() { return ui.locusneedshow; }
protected:
	void paintGL();
	void initializeGL();
	void resizeGL(int w,int h);
	void mousePressEvent(QMouseEvent *event) ;
	void mouseMoveEvent(QMouseEvent *event) ;
	void wheelEvent(QWheelEvent *event);
	bool  eventFilter(QObject * obj, QEvent * event);

private:
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void drawDynamicLocus();
	void drawXYZ();
	void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N);
	void InitKeyboardCtrl();
private:
	Ui::Locus ui;
	QPoint m_lastPos;
	ReadSTLFile*			pflie;

	int m_xRot;
	int m_yRot;
	int m_zRot;
	float m_scaled;
	float x_pos;
	float y_pos;
	

/////动态刀路
	QList<float> dxs, dys, dzs;
};
