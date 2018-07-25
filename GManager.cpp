#include "GManager.h"
#include"mccdll.h"
#include"readini.h"
#include "YesOrNo.h"
#include"LogManager.h"
#include "commontools.h"
#include"Samcon.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern QString MyStyle;
GManager::GManager(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	Init();
	InitKeyboardCtrl();
	ui.tableView->setObjectName("GmanagertableView");
}

GManager::~GManager()
{
}

void GManager::MySetFocus()
{
	ui.tableView->setFocus();
}

bool GManager::MyGetFocus()
{
	bool b1 = ui.tableView->hasFocus();
	bool b2 = ui.OpenFile->hasFocus();
	bool b3 = ui.GLoad->hasFocus();
	bool b4 = ui.GUnload->hasFocus();
	bool b5 = ui.GEdit->hasFocus();
	bool b6 = ui.GDel->hasFocus();
	return b1||b2||b3||b4||b5||b6||hasFocus();
}

void GManager::setPath(QString str)
{
	// 设置model监视的目录，其下的修改会立刻signal通知view
	model.setRootPath(str);
	model.setFilter(QDir::Files);
	ui.tableView->setModel(&model);
	// 设置view显示的目录
	ui.tableView->setRootIndex(model.index(model.rootPath()));
	QString fdsfdsfsdfs = model.rootPath();
	
}

void GManager::ResetLanguage()
{
	ui.OpenFile->setText(TrLang::Ins()->GetText(104));
	ui.GLoad->setText(TrLang::Ins()->GetText(105));
	ui.GUnload->setText(TrLang::Ins()->GetText(106));
	ui.GEdit->setText(TrLang::Ins()->GetText(107));
	ui.GDel->setText(TrLang::Ins()->GetText(108));
}

bool GManager::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == this ||
		obj == ui.tableView ||
		obj == ui.OpenFile ||
		obj == ui.GLoad ||
		obj == ui.GUnload ||
		obj == ui.GEdit ||
		obj == ui.GDel) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Tab)
			{
				bool b1 = ui.tableView->hasFocus();
				bool b2 = ui.OpenFile->hasFocus();
				bool b3 = ui.GLoad->hasFocus();
				bool b4 = ui.GUnload->hasFocus();
				bool b5 = ui.GEdit->hasFocus();
				bool b6 = ui.GDel->hasFocus();
				if (b1) {
					focusNextChild();
					ui.OpenFile->setFocus();

				}
				else if (b2) {
					focusNextChild();
					ui.GLoad->setFocus();

				}
				else if (b3) {
					focusNextChild();
					ui.GUnload->setFocus();
				}
				else if (b4) {
					focusNextChild();
					ui.GEdit->setFocus();
				}
				else if (b5) {
					focusNextChild();
					ui.GDel->setFocus();
				}
				else if (b6) {
					focusNextChild();
					ui.tableView->setFocus();
				}
				else if (hasFocus()) {
					focusNextChild();
					ui.tableView->setFocus();
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

void GManager::keyReleaseEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Return) {
		QWidget* w = focusWidget();
		QPushButton* btSub = dynamic_cast<QPushButton*>(w);
		if (btSub) {
			btSub->clicked(1);
		}
	}

	QTableView* tv = dynamic_cast<QTableView*>(focusWidget());
	if (tv)
		if (event->key() == Qt::Key_Q ||
			event->key() == Qt::Key_W ||
			event->key() == Qt::Key_E ||
			event->key() == Qt::Key_A ||
			event->key() == Qt::Key_S ||
			event->key() == Qt::Key_D ||
			event->key() == Qt::Key_Z ||
			event->key() == Qt::Key_X ||
			event->key() == Qt::Key_C ||
			event->key() == Qt::Key_T ||
			event->key() == Qt::Key_G ||
			event->key() == Qt::Key_B ||
			event->key() == Qt::Key_F ||
			event->key() == Qt::Key_H) {
			ui.OpenFile->setFocus();
		}
	QWidget::keyReleaseEvent(event);
}

void GManager::Init()
{
	ui.tableView->setFocusPolicy(Qt::NoFocus);
	ui.tableView->setShowGrid(false);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->verticalHeader()->setVisible(0);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	setPath(readIni.GetOpenRecentDir());
	connect(ui.OpenFile, &QPushButton::clicked, [this]() {
		sendOpenFile();
	});
	connect(ui.GEdit, &QPushButton::clicked, [this]() {
		if (!model.isDir(ui.tableView->currentIndex())) {
			emit SammonFunc::Getins()->EditFile(model.filePath(ui.tableView->currentIndex()));
			SammonFunc::Getins()->TabIndexChang(0, 2);
			LogManager::getIns()->appendLog(QStringLiteral("编辑文件") + model.filePath(ui.tableView->currentIndex()));
		}
	});
	connect(ui.GDel, &QPushButton::clicked, [this]() {

		QString Path = model.filePath(ui.tableView->currentIndex());
		QStringList Ps = Path.split('/');
		if (!model.isDir(ui.tableView->currentIndex())) {	
			YesOrNo* yn = new YesOrNo(QStringLiteral("确定删除：%1？").arg(Ps[Ps.size() - 1]));
			yn->setStyleSheet(MyStyle);
			connect(yn, &YesOrNo::ChioceYes, [this] {
				QFile::remove(model.filePath(ui.tableView->currentIndex()));
				LogManager::getIns()->appendLog(QStringLiteral("删除文件")+ model.filePath(ui.tableView->currentIndex()));
			}); 
				
		}
	});

	connect(ui.GLoad, &QPushButton::clicked, [this]() {
		if (!model.isDir(ui.tableView->currentIndex())) {
			emit SammonFunc::Getins()->LoadFile(model.filePath(ui.tableView->currentIndex()));
			SammonFunc::Getins()->TabIndexChang(1, 0);
		}
	});
	connect(ui.tableView, &QTableView::doubleClicked, [this](const QModelIndex &index) {
		emit SammonFunc::Getins()->LoadFile(model.filePath(index));
		SammonFunc::Getins()->TabIndexChang(1, 0);
	});

	connect(ui.GUnload, &QPushButton::clicked, [this]() {		
			mcc->ClearAutoText();
			mcc->ClearBuffer();
			emit	SammonFunc::Getins()->UnloadFile();
			SammonFunc::RunShow = false;
			SammonFunc::isLoading = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = false;
			LogManager::getIns()->appendLog(QStringLiteral("卸载文件") );
	});
	
}

void GManager::InitKeyboardCtrl()
{
	this->installEventFilter(this);
	ui.OpenFile->installEventFilter(this);
	ui.GLoad->installEventFilter(this);
	ui.GUnload->installEventFilter(this);
	ui.GEdit->installEventFilter(this);
	ui.GDel->installEventFilter(this);
	ui.tableView->installEventFilter(this);
}
