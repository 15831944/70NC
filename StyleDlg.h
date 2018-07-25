#pragma once

#include <QWidget>

#include "QMouseEvent"
#include"QPainter "
#include "QStyleOption"
#include "qlabel.h"
#include "qpushbutton.h"
class StyleWidget : public QWidget {
	Q_OBJECT
public:
	StyleWidget(QWidget *parent = Q_NULLPTR) {}
	~StyleWidget() {}
protected:
	void paintEvent(QPaintEvent*) {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}
};

class StyleDlg : public QWidget
{
	Q_OBJECT

public:
	StyleDlg(QWidget *parent = Q_NULLPTR);
	~StyleDlg();
protected:
	void paintEvent(QPaintEvent*) {
		QStyleOption opt;
		opt.init(this);
		QPainter p(this);
		style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	}
	QPoint m_Press, m_Move;
	bool leftBtnClk = false;
	void mousePressEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton &&
			label.frameRect().contains(event->globalPos() - this->frameGeometry().topLeft())) {
			m_Press = event->globalPos();
			leftBtnClk = true;
		}
		event->ignore();
	}
	void mouseReleaseEvent(QMouseEvent *event)
	{
		if (event->button() == Qt::LeftButton) {

			leftBtnClk = false;
		}
		event->ignore();
	}
	void mouseMoveEvent(QMouseEvent *event)
	{
		if (leftBtnClk) {

			m_Move = event->globalPos();
			this->move(this->pos() + m_Move - m_Press);
			m_Press = m_Move;
		}
		event->ignore();
	}

	void setLine() {
		
			int h = height(); 
			int w = width(); 
			label.setGeometry(0, 0, w, 30);
			bt.setGeometry(w - 26, 4, 22, 20);
			QFrame* v1 = new QFrame(this); 
			v1->setGeometry(QRect(0, 0, 2, h)); 
			v1->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);")); 
			v1->setFrameShape(QFrame::VLine); 
			v1->setFrameShadow(QFrame::Sunken); 
			QFrame* v2 = new QFrame(this); 
			v2->setGeometry(QRect(w - 2, 0, 2, h)); 
			v2->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);")); 
			v2->setFrameShape(QFrame::VLine); 
			v2->setFrameShadow(QFrame::Sunken); 
			QFrame* h1 = new QFrame(this); 
			h1->setGeometry(QRect(0, h - 2, w, 2)); 
			h1->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);")); 
			h1->setFrameShape(QFrame::VLine); 
			h1->setFrameShadow(QFrame::Sunken); 
			label.setParent(this);
			bt.setParent(this);
	}
	QLabel label;
	QPushButton bt;
	void setDlgName(QString str) {
		label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		label.setText(str); }
};
