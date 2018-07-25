#include "SystemMsg.h"
#include"LogManager.h"
#include "commontools.h"
#include"TrLang.h"
SystemMsg::SystemMsg(QWidget *parent)
	: StyleWidget(parent)
{
	ui.setupUi(this);
	

	ui.logtableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.logtableWidget->setShowGrid(false);
	ui.logtableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.logtableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	connect(LogManager::getIns(), &LogManager::updateLog, [this](QString s1, QString s2) {
		ui.logtableWidget->insertRow(0);
		ui.logtableWidget->setItem(0, 0, new QTableWidgetItem(s1));
		ui.logtableWidget->setItem(0, 1, new QTableWidgetItem(s2));
	});
	InitKeyboardCtrl();
}

SystemMsg::~SystemMsg()
{
}

void SystemMsg::MySetFocus()
{
	ui.logtableWidget->setFocus();
}

bool SystemMsg::MyGetFocus()
{
	return ui.logtableWidget ->hasFocus()||hasFocus();
}

void SystemMsg::ResetLanguage()
{
	QStringList headers;
	headers << TrLang::Ins()->GetText(121) << TrLang::Ins()->GetText(122);
	ui.logtableWidget->setHorizontalHeaderLabels(headers);;
}

bool SystemMsg::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == this ||
		obj == ui.logtableWidget) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
			if (key_event->key() == Qt::Key_Tab)
			{
				if (hasFocus()) {
					focusNextChild();
					ui.logtableWidget->setFocus();
				}
				else
				{
					focusNextChild();
					ui.logtableWidget->setFocus();
				
				}
				return true;
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}

void SystemMsg::keyReleaseEvent(QKeyEvent * event)
{
	QTableWidget* tw = dynamic_cast<QTableWidget*>(focusWidget());
	if (tw)
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
			setFocus();
		}
	QWidget::keyReleaseEvent(event);
}

void SystemMsg::InitKeyboardCtrl()
{
	this->installEventFilter(this);
	ui.logtableWidget->installEventFilter(this);
}
