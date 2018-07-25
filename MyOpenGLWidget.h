#pragma once

#include <QOpenGLWidget>
#include "ui_MyOpenGLWidget.h"
#include <QOpenGLFunctions>
#include<QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
class MyOpenGLWidget : public QOpenGLWidget,protected QOpenGLFunctions{

	Q_OBJECT

public:
	MyOpenGLWidget(QWidget *parent = Q_NULLPTR);
	~MyOpenGLWidget();
	void reset();
protected:
	void initializeGL();
	void resizeGL(int w, int h);
	void paintGL();

	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent * event);
private:
	void InitProgram();
	void setXRotation(int angle);
	void setYRotation(int angle);
	void setZRotation(int angle);
	void drawXYZ();
	void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N);
private:
	Ui::MyOpenGLWidget ui;

	QOpenGLShaderProgram *m_program1;
	QOpenGLBuffer m_LinesBffer;
	QOpenGLBuffer m_ColorBffer;
	QMatrix4x4 m_projection;
	QMatrix4x4 m_camera;
	QMatrix4x4 m_world;

	bool m_core;

	int m_projMatrixLoc1;
	int m_mvMatrixLoc1;
	int m_lightPosLoc1;


	QVector<GLfloat> m_data;

	QPoint m_lastPos;
	int m_xRot;
	int m_yRot;
	int m_zRot;
	float m_scaled;
	float x_pos;
	float y_pos;
	double step = 0.01;
};
