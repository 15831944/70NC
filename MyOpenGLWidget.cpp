#include "MyOpenGLWidget.h"
#include <QMouseEvent>
#include <QCoreApplication>
#include "DataDefine.h"

extern QList<Line>vLines;
extern QList<ArcData> Arcs;

static const char *vertexShaderSourceCore =
"#version 150\n"
"in vec4 vertex;\n"
"in vec3 normal;\n"
"out vec3 vert;\n"
"out vec3 vertNormal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   vertNormal = normalMatrix * normal;\n"
"   gl_Position = projMatrix * mvMatrix * vertex;\n"
"}\n";
static const char *vertexShaderSource =
"attribute vec4 vertex;\n"
"attribute vec3 normal;\n"
"varying vec3 vert;\n"
"varying vec3 vertNormal;\n"
"uniform mat4 projMatrix;\n"
"uniform mat4 mvMatrix;\n"
"uniform mat3 normalMatrix;\n"
"void main() {\n"
"   vert = vertex.xyz;\n"
"   vertNormal = normalMatrix * normal;\n"
"   gl_Position = projMatrix * mvMatrix * vertex;\n"
"}\n";
static const char *fragmentShaderSourceCore =
"#version 150\n"
"in highp vec3 vert;\n"
"in highp vec3 vertNormal;\n"
"out highp vec4 fragColor;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(0, 1, 1);\n"
"   highp vec3 col = clamp(color * 0.7 + color * 0.2 * NL, 0.0, 1.0);\n"
"   fragColor = vec4(col, 1.0);\n"
"}\n";
static const char *fragmentShaderSource =
"varying highp vec3 vert;\n"
"varying highp vec3 vertNormal;\n"
"uniform highp vec3 lightPos;\n"
"void main() {\n"
"   highp vec3 L = normalize(lightPos - vert);\n"
"   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
"   highp vec3 color = vec3(0, 1, 1);\n"
"   highp vec3 col = clamp(color * 0.7 + color * 0.2 * NL, 0.0, 1.0);\n"
"   gl_FragColor = vec4(col, 1.0);\n"
"}\n";


MyOpenGLWidget::MyOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	m_xRot =0 ;
	m_yRot =0 ;
	m_zRot = 0;
	m_scaled = 1;
	x_pos = 0;
	y_pos = 0;
	ui.setupUi(this);
	m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
	setWindowTitle("Show");
	setAttribute(Qt::WA_DeleteOnClose, true);
}

MyOpenGLWidget::~MyOpenGLWidget()
{
	Arcs.clear();
	vLines.clear();
}

void MyOpenGLWidget::reset()
{
	if (m_data.size() < 6)return;
	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;
	x_pos = 0;
	y_pos = 0;
	for (int i = 2; i < m_data.size(); i += 3) {
		x_pos = -m_data[i-2];
		y_pos = -m_data[i-1];
		if (abs(x_pos - 0) < 0.001||abs(y_pos - 0)<0.001) {
			continue;
		}
		else {
			break;
		}
	}
	
	double s = x_pos*x_pos + y_pos*y_pos;
	if (s != (double)0)
		m_scaled = 1 / sqrt(s);
	else
		m_scaled = 1;
	update();


}

void MyOpenGLWidget::initializeGL()
{
		
		initializeOpenGLFunctions();
		glClearColor(0.0, 0.0, 0.0, 0);//改变窗口的背景颜色  

		glClearDepth(1.0);//设置深度缓存  
		glEnable(GL_DEPTH_RANGE);//允许深度测试  
		glDepthFunc(GL_LEQUAL);//设置深度测试类型  
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正 
	
		m_program1 = new QOpenGLShaderProgram;
		m_program1->addShaderFromSourceCode(QOpenGLShader::Vertex, m_core ? vertexShaderSourceCore : vertexShaderSource);
		m_program1->addShaderFromSourceCode(QOpenGLShader::Fragment, m_core ? fragmentShaderSourceCore : fragmentShaderSource);
		m_program1->bindAttributeLocation("vertex", 0);
		m_program1->bindAttributeLocation("normal", 1);

		m_program1->link();
		m_program1->bind();
		m_projMatrixLoc1 = m_program1->uniformLocation("projMatrix");
		m_mvMatrixLoc1 = m_program1->uniformLocation("mvMatrix");
		m_lightPosLoc1 = m_program1->uniformLocation("lightPos");

		m_data.clear();
		double tempx, tempy, tempz;
		for (int i = 0; i < vLines.size(); i++) {
			for (int j = 0; j < vLines[i].Points.size(); j++) {
				int fsdfsd = vLines[i].Points[j].x;
				m_data.push_back(vLines[i].Points[j].x);
				m_data.push_back(vLines[i].Points[j].y);
				m_data.push_back(vLines[i].Points[j].z);

			}
		}

		for (int idx = 0; idx < Arcs.size(); idx++) {
			for (int i = 1, n = 50, R = 0.1; i <= n ; ++i) {
				if (Arcs[idx].flag == 0) {
					tempx = Arcs[idx].x + Arcs[idx].R* cos(Arcs[idx].rad / n*i + Arcs[idx].sRad);
					tempy = Arcs[idx].y + Arcs[idx].R * sin(Arcs[idx].rad / n*i + Arcs[idx].sRad);
					tempz = Arcs[idx].z;
				}
				else if (Arcs[idx].flag == 1) {
					tempx = Arcs[idx].x + Arcs[idx].R* cos(Arcs[idx].rad / n*i + Arcs[idx].sRad);
					tempy = Arcs[idx].y;
					tempz = Arcs[idx].z + Arcs[idx].R * sin(Arcs[idx].rad / n*i + Arcs[idx].sRad);
				}
				else {
					tempx = Arcs[idx].x;
					tempy = Arcs[idx].y + Arcs[idx].R* cos(Arcs[idx].rad / n*i + Arcs[idx].sRad);
					tempz = Arcs[idx].z + Arcs[idx].R * sin(Arcs[idx].rad / n*i + Arcs[idx].sRad);
				}
				m_data.push_back(tempx);
				m_data.push_back(tempy);
				m_data.push_back(tempz);
			}
		}

		m_LinesBffer.create();
		m_LinesBffer.bind();
		m_LinesBffer.allocate(m_data.constData(), (m_data.size())* sizeof(GLfloat));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		m_LinesBffer.release();
	

		m_camera.setToIdentity();
		m_camera.translate(0, 0, -3);

		m_program1->setUniformValue(m_lightPosLoc1, QVector3D(0, 0, 70));
		m_program1->release();

}

void MyOpenGLWidget::resizeGL(int w, int h)
{
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

}

void MyOpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//drawXYZ();

	m_program1->bind();	
	m_world.setToIdentity();
	m_world.rotate(m_xRot / 16, 1.0, 0.0, 0.0);
	m_world.rotate(m_yRot / 16, 0.0, 1.0, 0.0);
	m_world.rotate(m_zRot / 16, 0.0, 0.0, 1.0);
	m_world.scale(m_scaled, m_scaled, m_scaled);
	m_world.translate(x_pos, y_pos, 0);
	
	m_program1->setUniformValue(m_projMatrixLoc1, m_projection);
	m_program1->setUniformValue(m_mvMatrixLoc1, m_camera * m_world);

	int start = 0;
	int size = 0;
//	glDrawArrays(GL_LINE_STRIP, 0, m_data.size()/3);

	for (int i = 0; i < vLines.size(); i++) {
		size = vLines[i].Points.size() ;
		glDrawArrays(GL_LINE_STRIP, start, size );
		start += size;
	}
	size = 50;
	for (int idx = 0; idx < Arcs.size(); idx++){
		glDrawArrays(GL_LINE_STRIP, start, size);
		start += size;
	}

	m_program1->release();
	

}

void MyOpenGLWidget::mousePressEvent(QMouseEvent * event)
{
	m_lastPos = event->pos();
	step = 0.01;
}

void MyOpenGLWidget::mouseMoveEvent(QMouseEvent * event)
{

	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();
	step += 0.01;
	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
		setZRotation(m_zRot + 8 * dx);
	
	}
	else if (event->buttons() & Qt::RightButton) {
		if (event->x()> m_lastPos.x())
		{
			x_pos += step;
		}
		if (event->x() <m_lastPos.x())
		{
			x_pos -= step;
		}
		if (event->y() < m_lastPos.y())
		{
			y_pos += step;
		}
		if (event->y() >m_lastPos.y())
		{
			y_pos -= step;
		}
		update();
	}

	m_lastPos = event->pos();
}

void MyOpenGLWidget::wheelEvent(QWheelEvent * event)
{
	if (event->delta() > 0) {
		m_scaled += m_scaled / 4.f;
	}
	else {
		m_scaled -= m_scaled / 4.f;;//缩小
	}
	update();
}

static void qNormalizeAngle(int &angle)
{
	while (angle < 0)
		angle += 360 * 16;
	while (angle > 360 * 16)
		angle -= 360 * 16;
}

void MyOpenGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		update();
	}
}
void MyOpenGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		update();
	}
}
void MyOpenGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		update();
	}
}

void MyOpenGLWidget::drawXYZ()
{
	glLoadIdentity();
	if (width() <= height())
		glOrtho(-1, 1, -(GLfloat)height() / (GLfloat)width(), (GLfloat)height() / (GLfloat)width(), -10, 10);
	else
		glOrtho(-(GLfloat)width() / (GLfloat)height(), (GLfloat)width() / (GLfloat)height(), -1, 1, -10, 10);


	glTranslatef(-0.9, -0.9, 0);
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
	glPushMatrix();
}
//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份  
void MyOpenGLWidget::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
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