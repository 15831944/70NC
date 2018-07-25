#include "DocEdit.h"
#include "QFileDialog"
#include "QTextStream"
#include"LogManager.h"
#include <Qsci/qsciscintilla.h>
#include "qscrollbar"
#include"qtime"
#include"qDebug"
#include "CommonTools.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern QString MyStyle;
DocEdit::DocEdit(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	textEdit = new QsciScintilla;
	
	
	textEdit->horizontalScrollBar()->hide();
	ui.gridLayout->addWidget(textEdit);
	InitUI();
	DlgFind.setStyleSheet(MyStyle);
	InitKeyboardCtrl();
	connect(&DlgFind, &DlgFindText::findText, [this](QString str) {
		QString findtext = str;//获得对话框的内容  
		if (textEdit->findFirst(findtext,0,0,0,1))//bool  是否将第一个参数 解释为正则表达式  是否区分大小写，是否全字匹配，是否搜索到末尾结束
		{
			// 查找到后高亮显示  
			QPalette palette = textEdit->palette();
			palette.setColor(QPalette::Highlight, palette.color(QPalette::Active, QPalette::Highlight));
			textEdit->setPalette(palette);
			DlgFind.ShowFind(0);
		}
		else
		{
			DlgFind.ShowFind(1);
		}
		
	});
}

DocEdit::~DocEdit()
{
}

void DocEdit::ResetLanguage()
{
	ui.Save->setText(TrLang::Ins()->GetText(109));
	ui.SaveLoad->setText(TrLang::Ins()->GetText(110));
	ui.close->setText(TrLang::Ins()->GetText(111));
	DlgFind.ResetLanguage();
}

void DocEdit::EditFile(QString fileName)
{
	QTime t;
	t.start();
	QFile	file(fileName);
	ui.label->setText(fileName);
	if (file.open(QIODevice::ReadOnly))
	{
		mfileName = fileName;
		textEdit->setEnabled(1);

		QTextStream in(&file);
		textEdit->setText(in.read(10000000));
		while (!in.atEnd()) {
			QApplication::processEvents();
			textEdit->append(in.read(10000000));
		}

		file.close();
	}
	//qDebug() << t.elapsed();
}

void DocEdit::MySetFocus()
{
	if (textEdit->isEnabled())
		textEdit->setFocus();
	else
		ui.Save->setFocus();
}

bool DocEdit::MyGetFocus()
{
	bool b0 = textEdit->hasFocus();
	bool b1 = ui.Save->hasFocus();
	bool b2 = ui.SaveLoad->hasFocus();
	bool b3 = ui.close->hasFocus();
	return b0||b1||b2||b3||hasFocus();
}

void DocEdit::keyReleaseEvent(QKeyEvent * event)
{

	 if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_F) {
		 DlgFind.show();//查找
	}
	else if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_S) {
		ui.Save->click();
	}
	else if (event->key() == Qt::Key_Return) {
		QWidget* w = focusWidget();
		QPushButton* btSub = dynamic_cast<QPushButton*>(w);
		if (btSub) {
			btSub->clicked(1);
		}
	}


	QsciScintilla* te = dynamic_cast<QsciScintilla*>(focusWidget());
	if (te)return;  //防止编辑文件 触发   按键盘 点动
	QWidget::keyReleaseEvent(event);
}

bool DocEdit::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == this ||
		obj == ui.Save ||
		obj == textEdit ||
		obj == ui.SaveLoad ||
		obj == ui.close) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			 if (key_event->key() == Qt::Key_Tab)
			{
				bool b0 = textEdit->hasFocus();
				bool b1 = ui.Save->hasFocus();
				bool b2 = ui.SaveLoad->hasFocus();
				bool b3 = ui.close->hasFocus();
				if (b0) {
					focusNextChild();
					ui.Save->setFocus();
				}
				else if (b1) {
					focusNextChild();
					ui.SaveLoad->setFocus();

				}
				else if (b2) {
					focusNextChild();
					ui.close->setFocus();

				}
				else if (b3) {
					focusNextChild();
					if(textEdit->isEnabled())
						textEdit->setFocus();
					else
						ui.Save->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					if (textEdit->isEnabled())
						textEdit->setFocus();
					else
						ui.Save->setFocus();
				}
				else
				{
					focusNextChild();
				}
				return true;
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}



void DocEdit::InitUI()
{
	textEdit->setEnabled(false);
	connect(ui.Save,&QPushButton::clicked, [this]() {
		if (mfileName.isEmpty())return;
		QFile	file(mfileName);
		if (file.open(QIODevice::WriteOnly))
		{
			textEdit->write(&file);
			file.close();
		}
		LogManager::getIns()->appendLog(QStringLiteral("保存文件"));

	});
	connect(ui.close, &QPushButton::clicked, [this]() {
		if (mfileName.isEmpty())return;
		ui.label->clear();
		textEdit->clear();
		textEdit->setEnabled(false);
		mfileName.clear();
		LogManager::getIns()->appendLog(QStringLiteral("放弃修改"));
	});
	connect(ui.SaveLoad, &QPushButton::clicked, [this]() {
		//save
		if (mfileName.isEmpty())return;
		QFile	file(mfileName);
		if (file.open(QIODevice::WriteOnly))
		{
			textEdit->write(&file);
			file.close();
		}
		LogManager::getIns()->appendLog(QStringLiteral("保存文件"));
		//load
		emit SammonFunc::Getins()->LoadFile(mfileName);
	});
}

void DocEdit::InitKeyboardCtrl()
{
	installEventFilter(this);
	ui.Save->installEventFilter(this);
	ui.SaveLoad->installEventFilter(this);
	ui.close->installEventFilter(this);
	textEdit->installEventFilter(this);
}
