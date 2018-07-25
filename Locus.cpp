#include "Locus.h"
#include "QPainter"
#include "ReadSTLFile.h"
#include "QMouseEvent"
#include "QMessageBox"
#include "QDebug"
#include"qpushbutton.h"
#include"readIni.h"
#include"CommonTools.h"
#include "TrLang.h"
extern ReadIni readIni;
Locus::Locus(QWidget *parent)
	: QOpenGLWidget(parent), m_scaled(0.01), x_pos(0), y_pos(0)
{
	ui.setupUi(this);
	//pflie = new ReadSTLFile;
	//if (!pflie->ReadFile("E:\\samples\\SampleScene.stl")) {
	//	qDebug() << QStringLiteral("读取STL文件失败");
	//	return;
	//}
	/////////////////////测试
	InitKeyboardCtrl();

	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;

	
	connect(ui.locusneedshow, &QPushButton::clicked, [this]() {	
		emit 	SammonFunc::Getins()->SendShowGCodeGLWidget();
	});

	connect(ui.lreset, &QPushButton::clicked, [this]() {
		m_xRot = 0;
		m_yRot = 0;
		m_zRot = 0;
		m_scaled = 0.01;
		x_pos = 0;
		y_pos = 0;
		update();

	});	
	connect(ui.roomin, &QPushButton::clicked, [this]() {
		m_scaled -= m_scaled / 4.f;;//缩小
		update();
	});
	connect(ui.roomout, &QPushButton::clicked, [this]() {
		m_scaled += m_scaled / 4.f;
		update();
	});
	ui.lreset->setCheckable(1);
	ui.lreset->setCheckable(1);
	ui.lreset->setCheckable(1);
}

Locus::~Locus()
{
}

void Locus::MySetFocus()
{
	ui.lreset->setFocus();
}

bool Locus::MyGetFocus()
{
	bool b1 = ui.lreset->hasFocus();
	bool b2 = ui.roomin->hasFocus();
	bool b3 = ui.roomout->hasFocus();
	return b1||b2||b3||hasFocus();
}

void Locus::ResetLanguage()
{
	
		ui.lreset->setText(TrLang::Ins()->GetText(100));
		ui.roomin->setText(TrLang::Ins()->GetText(101));
		ui.roomout->setText(TrLang::Ins()->GetText(102));
		ui.locusneedshow->setText(TrLang::Ins()->GetText(103));
	
}

void Locus::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glTranslated(-0.9, -0.85, 0.0f);
	if (width() <= height())
		glOrtho(-1, 1, -(GLfloat)height() / (GLfloat)width(), (GLfloat)height() / (GLfloat)width(), -10, 10);
	else
		glOrtho(-(GLfloat)width() / (GLfloat)height(), (GLfloat)width() / (GLfloat)height(), -1, 1, -10, 10);
	glPushMatrix();
	glLoadIdentity();
	if (width() <= height())
		glOrtho(-1, 1, -(GLfloat)height() / (GLfloat)width(), (GLfloat)height() / (GLfloat)width(), -10, 10);
	else
		glOrtho(-(GLfloat)width() / (GLfloat)height(), (GLfloat)width() / (GLfloat)height(), -1, 1, -10, 10);

	//vector<vector<Point3f>>& geos = pflie->GetGeometrys();  //显示STL文件
	//for (int i=0;i<	geos.size();i++) {
	//	glBegin(GL_LINE_LOOP);
	//	 for (int j = 0; j < geos[i].size(); j++)
	//	 		
	//	 {
	//		 glColor3f(0.0f, 1.0f, 1.0f);
	//		 glVertex3f(geos[i].at(j).IVertex()._x, geos[i].at(j).IVertex()._y, geos[i].at(j).IVertex()._z);
	//	 }
	//	 glEnd();
	//}

	glTranslated(x_pos, y_pos, 0.0f);
	glRotatef(m_xRot / 16, 1.0, 0.0, 0.0);
	glRotatef(m_yRot / 16, 0.0, 1.0, 0.0);
	glRotatef(m_zRot / 16, 0.0, 0.0, 1.0);
	glScaled(m_scaled, m_scaled, m_scaled);


	//预显示显示刀路
	//drawLocus();
	
	//动态刀路
	drawDynamicLocus();

	glPopMatrix();
	//绘制坐标轴
	drawXYZ();
	
}

void Locus::initializeGL()
{
	
	glShadeModel(GL_SMOOTH);//设置
	glClearColor(0.0, 0.0, 0.0, 0);//改变窗口的背景颜色  
	glClearDepth(1.0);//设置深度缓存  
	glEnable(GL_DEPTH_RANGE);//允许深度测试  
	glDepthFunc(GL_LEQUAL);//设置深度测试类型  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正 

	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);  // Antialias the lines  
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
}

void Locus::resizeGL(int w, int h)
{

}

void Locus::mousePressEvent(QMouseEvent *event)
{
	m_lastPos = event->pos();
}

void Locus::mouseMoveEvent(QMouseEvent *event)
{
	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
		//setZRotation(m_zRot + 8 * dx);
		
	}
	else if (event->buttons() & Qt::RightButton) {
		//setXRotation(m_xRot + 8 * dy);
		//setZRotation(m_zRot + 8 * dx);
	if (event->x()> m_lastPos.x())
		{
			x_pos += 0.02;
		}
		if (event->x() <m_lastPos.x())
		{
			x_pos -= 0.02;
		}
		if (event->y() < m_lastPos.y())
		{
			y_pos += 0.02;
		}
		if (event->y() >m_lastPos.y())
		{
			y_pos -= 0.02;
		}



		update();
	}

	m_lastPos = event->pos();
}

void Locus::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0) {
		m_scaled += m_scaled / 4.f;
	}
	else {
		m_scaled -= m_scaled / 4.f;;//缩小
	}
	update();
}

bool Locus::eventFilter(QObject * obj, QEvent * event)
{

	if (obj == this ||obj == ui.lreset ||obj == ui.roomin ||obj == ui.roomout){
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Return) {
				QWidget* w = focusWidget();
				QPushButton* btSub = dynamic_cast<QPushButton*>(w);
				if (btSub) {
					btSub->clicked(1);
				}
			}
			else if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.lreset->hasFocus();
				bool b2 = ui.roomin->hasFocus();
				bool b3 = ui.roomout->hasFocus();
				if (b1) {
					focusNextChild();
					ui.roomin->setFocus();

				}
				else if (b2) {
					focusNextChild();
					ui.roomout->setFocus();

				}
				else if (b3) {
					focusNextChild();
					ui.lreset->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					ui.lreset->setFocus();
				}
				else
				{
					focusNextChild();
				}
				return true;
			}
		}
	}
	return QOpenGLWidget::eventFilter(obj, event);
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}
void Locus::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		
		update();
	}
}

void Locus::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		
		update();
	}
}

void Locus::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		
		update();
	}
}

void Locus::drawDynamicLocus()
{

	glColor3f(0, 1, 1);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < dxs.size(); i++)
	{
		glVertex3f(dxs[i], dys[i], dzs[i]);
	}
	glEnd();

	glColor3f(1, 0,0);
	int i = dxs.size() - 1;
	if (i<=0)
		return;
	glBegin(GL_LINE_STRIP);
	
	glVertex3f(dxs[i]-20000, dys[i], dzs[i]);
	glVertex3f(dxs[i] + 20000, dys[i], dzs[i]);
	glEnd();
	glBegin(GL_LINE_STRIP);

	glVertex3f(dxs[i] , dys[i] - 20000, dzs[i]);
	glVertex3f(dxs[i], dys[i] + 20000, dzs[i]);
	glEnd();

}
void Locus::drawXYZ()
{
	glRotatef(m_xRot / 16, 1.0, 0.0, 0.0);
	glRotatef(m_yRot / 16, 0.0, 1.0, 0.0);
	glRotatef(m_zRot / 16, 0.0, 0.0, 1.0);

	//X
	glLineWidth(2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0.1, 0, 0);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.125, 0.025, 0);
	glVertex3f(0.165, -0.025, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.125, -0.025, 0);
	glVertex3f(0.165, 0.025, 0);
	glEnd();
	//Y
	glLineWidth(2);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.1, 0);
	glEnd();
	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0, 0.150, 0);
	glVertex3f(0, 0.125, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0.150, 0);
	glVertex3f(-0.02, 0.175, 0);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0.150, 0);
	glVertex3f(0.02, 0.175, 0);
	glEnd();
	//Z
	glLineWidth(2);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.1);
	glEnd();
	glLineWidth(1);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.02, 0.025, 0.125);
	glVertex3f(-0.02, 0.025, 0.125);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(-0.02, -0.025, 0.125);
	glVertex3f(0.02, -0.025, 0.125);
	glEnd();
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.02, 0.025, 0.125);
	glVertex3f(-0.02, -0.025, 0.125);
	glEnd();
	glColor3f(0.5, 0.5, 0.5);
	drawSphere(0, 0, 0, 0.01, 10, 10);
}
//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份  
void Locus::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
{
	float step_z = PI / M;
	float step_xy = 2 * PI / N;
	float x[4], y[4], z[4];

	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glBegin(GL_QUADS);
	for (i = 0; i<M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j<N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);

			x[2] = radius*sin(angle_z + step_z)*cos(angle_xy + step_xy);
			y[2] = radius*sin(angle_z + step_z)*sin(angle_xy + step_xy);
			z[2] = radius*cos(angle_z + step_z);

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);

			for (int k = 0; k<4; k++)
			{
				glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
			}
		}
	}
	glEnd();
}

void Locus::InitKeyboardCtrl()
{
	this->installEventFilter(this);
	ui.lreset->installEventFilter(this);
	ui.roomin->installEventFilter(this);
	ui.roomout->installEventFilter(this);
}
