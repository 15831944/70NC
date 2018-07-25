#include "DXFOpenGLWidget.h"
#include <QMouseEvent>
#include <QCoreApplication>
#define PI 3.14159
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


DXFOpenGLWidget::DXFOpenGLWidget(QWidget *parent)
	: QOpenGLWidget(parent)
{
	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;
	m_scaled = 1;
	x_pos = 0;
	y_pos = 0;
	ui.setupUi(this);
	m_core = QCoreApplication::arguments().contains(QStringLiteral("--coreprofile"));
	connect(&timer, &QTimer::timeout, [this]() {
		if (!BindValue) {
			BindData();
		}
	});
	timer.start();
}

DXFOpenGLWidget::~DXFOpenGLWidget()
{
}

void DXFOpenGLWidget::BindData()
{

	BindValue = m_LinesBffer.bind();
	if (!BindValue) {
		return;
	}
	m_LinesBffer.allocate(mData.constData(), (mData.size()) * sizeof(GLfloat));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	m_LinesBffer.release(QOpenGLBuffer::VertexBuffer);
	update();
}

void DXFOpenGLWidget::reset()
{	
	if (mData.size() < 2)return;
	m_xRot = 0;
	m_yRot = 0;
	m_zRot = 0;
	x_pos = -mData[0];
	y_pos = -mData[1];
	double s = x_pos*x_pos + y_pos*y_pos;
	if (s != (double)0)
		m_scaled = 1 / sqrt(s);
	else
		m_scaled = 1;
	update();

}

void DXFOpenGLWidget::initializeGL()
{
	
		initializeOpenGLFunctions();
		glClearColor(0, 0, 0, 0);//改变窗口的背景颜色  

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

	
		m_LinesBffer.create();
		m_LinesBffer.bind();
		m_LinesBffer.allocate(mData.constData(), (mData.size()) * sizeof(GLfloat));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
		m_LinesBffer.release();

		m_camera.setToIdentity();
		m_camera.translate(0, 0, -3);

		m_program1->setUniformValue(m_lightPosLoc1, QVector3D(0, 0, 70));
		m_program1->release();

}

void DXFOpenGLWidget::resizeGL(int w, int h)
{
	m_projection.setToIdentity();
	m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);

}

void DXFOpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawXYZ();

	m_world.setToIdentity();
	m_world.rotate(m_xRot / 16, 1.0, 0.0, 0.0);
	m_world.rotate(m_yRot / 16, 0.0, 1.0, 0.0);
	m_world.rotate(m_zRot / 16, 0.0, 0.0, 1.0);

	m_world.scale(m_scaled, m_scaled, m_scaled);
	m_world.translate(x_pos, y_pos, 0);


	m_program1->bind();
	m_program1->setUniformValue(m_projMatrixLoc1, m_projection);
	m_program1->setUniformValue(m_mvMatrixLoc1, m_camera * m_world);

	//glDrawArrays(GL_LINE_STRIP, 0, mData.size()/3);

	for (int i = 0; i < mDataSection.size(); i++) {
		glDrawArrays(GL_LINE_STRIP, mDataSection[i].pos, mDataSection[i].size);
	}

	m_program1->release();
}

double step = 0.1;
void DXFOpenGLWidget::mousePressEvent(QMouseEvent * event)
{
	m_lastPos = event->pos();
	step = 0.02;
}

void DXFOpenGLWidget::mouseMoveEvent(QMouseEvent * event)
{

	int dx = event->x() - m_lastPos.x();
	int dy = event->y() - m_lastPos.y();

	if (event->buttons() & Qt::LeftButton) {
		setXRotation(m_xRot + 8 * dy);
		setYRotation(m_yRot + 8 * dx);
		setZRotation(m_zRot + 8 * dx);
	
	}
	else if (event->buttons() & Qt::RightButton) {
		step += 0.02;
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

void DXFOpenGLWidget::wheelEvent(QWheelEvent * event)
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

void DXFOpenGLWidget::setXRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_xRot) {
		m_xRot = angle;
		update();
	}
}
void DXFOpenGLWidget::setYRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_yRot) {
		m_yRot = angle;
		update();
	}
}
void DXFOpenGLWidget::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != m_zRot) {
		m_zRot = angle;
		update();
	}
}

void DXFOpenGLWidget::drawXYZ()
{
	glLoadIdentity();
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
}
//球心坐标为（x，y，z），球的半径为radius，M，N分别表示球体的横纵向被分成多少份  

void DXFOpenGLWidget::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N)
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