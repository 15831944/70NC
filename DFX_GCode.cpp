#include "DFX_GCode.h"
#include<QFileDialog>
#include "DXFAdapter.h"
#include "dl_dxf.h"
#include "qValidator.h"
#include "s_OpenFile.h"
#include "AnalysisG.h"
#include<QTextStream>
#include <CommonTools.h>
#include <QElapsedTimer>
#include "ReadIni.h"
#include "TrLang.h"
extern ReadIni readIni;
DFX_GCode::DFX_GCode(QWidget *parent)
	: StyleDlg(parent)
	{
	ui.setupUi(this);
	Adapter = new DXFAdapter;
	dxf = new DL_Dxf();
	setAttribute(Qt::WA_DeleteOnClose, true);

	setLine();

	show();
	Init();
	ResetLanguage();
}

DFX_GCode::~DFX_GCode()
{

}

void DFX_GCode::ResetLanguage()
{
	setDlgName(TrLang::text(77));
	ui.label->setText(TrLang::text(354));
	ui.label_2->setText(TrLang::text(355));
	ui.label_4->setText(TrLang::text(356));
	ui.UseFileDepth->setText(TrLang::text(357));
	ui.dandujiagong->setText(TrLang::text(358));
	ui.XuanZheDfx->setText(TrLang::text(359));
	ui.Yanlan->setText(TrLang::text(362));
	ui.Zhuangzai->setText(TrLang::text(363));

	ui.tabWidget->setTabText(0, TrLang::text(360));
	ui.tabWidget->setTabText(1, TrLang::text(361));
}

void DFX_GCode::Init()
{
	ui.ZValue->setValidator(new QDoubleValidator());
#ifndef _DEBUG
	ui.Test->hide();
#endif // !_DEBUG

	connect(ui.Test, &QPushButton::clicked, [this]() {
		ui.tableWidget->setRowCount(0);
		ui.tableWidget->clearContents();
	});
	connect(ui.XuanZheDfx, &QPushButton::clicked, [this]() {
		disconnect(ui.treeWidget, &QTreeWidget::itemChanged, this, &DFX_GCode::slotitemChanged);
		Adapter->clear();
		QString fileName = QFileDialog::getOpenFileName(0, tr("Open Config"), readIni.GetDXFDir(), tr("Config Files (*.dxf);;All(*.*)"));
		if (fileName.isEmpty())return;
		ui.lineEdit_Dfx->setText(fileName);

		QStringList &slist = fileName.split('/');
		readIni.SetDXFDir(fileName.left(fileName.size() - slist[slist.size() - 1].size()));

		if (dxf->in(std::string((const char *)ui.lineEdit_Dfx->text().toLocal8Bit()), Adapter)) {
			ui.tableWidget->setRowCount(0);
			ui.tableWidget->clearContents();
			InitTree();
			Adapter->Func();
		}
		ui.openGLWidget->reset();
	});

	connect(ui.Yanlan, &QPushButton::clicked, [this]() {//‘§¿¿G¥˙¬Î
		if (ui.lineEdit_Dfx->text().isEmpty())return;
	
		ui.tableWidget->setRowCount(0);
		ui.tableWidget->clearContents();
		Adapter->mMaxDepth = ui.ZDepth->text();
		Adapter->mDepth = ui.ZDepth2->text();
		Adapter->SetUpValue(ui.ZValue->text());
		Adapter->useFileDepth = ui.UseFileDepth->isChecked();
		Adapter->DanDuJiaGong = ui.dandujiagong->isChecked();
		Adapter->OutputGCode();
	});	

	connect(ui.Zhuangzai, &QPushButton::clicked, [this]() {//◊∞‘ÿ
		if(ui.lineEdit_Dfx->text().isEmpty())return;
		Adapter->mMaxDepth = ui.ZDepth->text();
		Adapter->mDepth = ui.ZDepth2->text();
		Adapter->SetUpValue(ui.ZValue->text());
		Adapter->useFileDepth = ui.UseFileDepth->isChecked();
		Adapter->DanDuJiaGong = ui.dandujiagong->isChecked();
		Adapter->OutputGCode("sadasd");
	});

	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setColumnWidth(0, 80);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
	ui.tableWidget->setShowGrid(false);

	ui.treeWidget->setHeaderLabel(QStringLiteral("Ω⁄µ„"));
	ui.treeWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(&Adapter->dxfsender, &DXFSender::sendstream, [this](QTextStream& stream) {
		stream.seek(0);
		int row = 0;
		while (!stream.atEnd()) {
			ui.tableWidget->insertRow(row);
			ui.tableWidget->setRowHeight(row,20);
			ui.tableWidget->setItem(row++, 0, new QTableWidgetItem(stream.readLine()));
		}
		
	});
	connect(&Adapter->dxfsender, &DXFSender::loadfromstream, [this](QTextStream& stream,int tt) {
		emit	SammonFunc::Getins()->sendDxfStream(stream, ui.lineEdit_Dfx->text(),tt);
	});
}
void DFX_GCode::ChangeParentState(QTreeWidgetItem *item) {
	QTreeWidgetItem* parent = item->parent();
	Qt::CheckState  state = item->checkState(0);

	for (int i = 0; i < parent->childCount(); i++) {
		if (state != parent->child(i)->checkState(0)) {
			parent->setCheckState(0, Qt::PartiallyChecked);
			return;
		}
	}
	parent->setCheckState(0, state);
}
void DFX_GCode::ChangeSubState(QTreeWidgetItem *item) {
	Qt::CheckState  state = item->checkState(0);

	for (int i = 0; i < item->childCount(); i++) {
		item->child(i)->setCheckState(0, state);
	}

}

void DFX_GCode::InitTree()
{
	
	ui.treeWidget->clear();
	

	if (Adapter->Lines.size()) {
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(QString("Lines")));
		item->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		item->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
		ui.treeWidget->addTopLevelItem(item);
		QTreeWidgetItem* cell;
		for (int i = 0; i < Adapter->Lines.size(); i++) {
			cell = new QTreeWidgetItem(item, QStringList(QString::number(i)));
			cell->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			cell->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
			ui.treeWidget->addTopLevelItem(cell);
		}
	}
	if (Adapter->Arcs.size()) {
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(QString("Arcs")));
		item->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		item->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
		ui.treeWidget->addTopLevelItem(item);
		QTreeWidgetItem* cell;
		for (int i = 0; i < Adapter->Arcs.size(); i++) {
			cell = new QTreeWidgetItem(item, QStringList(QString::number(i)));
			cell->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			cell->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
			ui.treeWidget->addTopLevelItem(cell);
		}
	}
	if (Adapter->Circles.size()) {
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(QString("Circles")));
		item->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		item->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
		ui.treeWidget->addTopLevelItem(item);
		QTreeWidgetItem* cell;
		for (int i = 0; i < Adapter->Circles.size(); i++) {
			cell = new QTreeWidgetItem(item, QStringList(QString::number(i)));
			cell->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			cell->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
			ui.treeWidget->addTopLevelItem(cell);
		}
	}
	if (Adapter->Polylines.size()) {
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(QString("Polylines"))); 
		item->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		item->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
		ui.treeWidget->addTopLevelItem(item);
		QTreeWidgetItem* cell;
		for (int i = 0; i < Adapter->Polylines.size(); i++) {
			cell = new QTreeWidgetItem(item, QStringList(QString::number(i)));
			cell->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			cell->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
			ui.treeWidget->addTopLevelItem(cell);
		}
	}
	if (Adapter->Ellipses.size()) {
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(QString("Ellipses"))); 
		item->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		item->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
		ui.treeWidget->addTopLevelItem(item);
		QTreeWidgetItem* cell;
		for (int i = 0; i < Adapter->Ellipses.size(); i++) {
			cell = new QTreeWidgetItem(item, QStringList(QString::number(i)));
			cell->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			cell->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
			ui.treeWidget->addTopLevelItem(cell);
		}
	}
	if (Adapter->Splines.size()) {
		QTreeWidgetItem* item = new QTreeWidgetItem(QStringList(QString("Splines"))); 
		item->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
		item->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
		ui.treeWidget->addTopLevelItem(item);
		QTreeWidgetItem* cell;
		for (int i = 0; i < Adapter->Splines.size(); i++) {
			cell = new QTreeWidgetItem(item, QStringList(QString::number(i)));
			cell->setFlags(Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
			cell->setCheckState(0, Qt::Checked);   //∏¥—°øÚ
			ui.treeWidget->addTopLevelItem(cell);
		}
	}
	InitData();
}


void XYR_GetArc(double x1,double y1,double x2,double y2,double r,bool cw,double& cx,double& cy,double& start,double& length) {
	float cx1, cx2, cy1, cy2;
	AnalysisG::Circle_Center(x1, y1, x2, y2, r, cx1, cy1, cx2, cy2);

	if (cx1 == cx2&&cy1 == cy2) {
		cx = cx1;
		cy = cy1;
	}
	else if (AnalysisG::GetRealCenterPoint(x1, y1, x2, y2, r, cx1, cy1, cw)) {
		cx = cx1;
		cy = cy1;
	}
	else {
		cx = cx2;
		cy = cy2;
	}

	float s, e;
	s = atan2f(y1 - cy, x1 - cx);
	e = atan2f(y2 - cy, x2 - cx);

	float rMax, rMin;
	if (abs(s - e) > Pi) {
		rMax = abs(s - e);
		rMin = PI * 2 - rMax;
	}
	else {
		rMin = abs(s - e);
		rMax = PI * 2 - rMin;
	}
	if (cw) 
		start = e;
	else
		start = s;
	if (r > 0)
		length = rMin;
	else
		length = rMax;
}
void DFX_GCode::InitData()
{
	ui.openGLWidget->mDataSection.clear();
	ui.openGLWidget->mData.clear();
		
	DataSection ds;

	if (Adapter->Lines.size()) {
		QList <QTreeWidgetItem*> list = ui.treeWidget->findItems(QString("Lines"), Qt::MatchFixedString);
		QTreeWidgetItem *item =   list[0];
		if (item->checkState(0) != Qt::Unchecked) {
			ds.pos = 0, ds.size = 2;
			for (int i = 0; i < Adapter->Lines.size(); i++) {
				if (item->child(i)->checkState(0) == Qt::Checked) {
					ui.openGLWidget->mData.push_back(Adapter->Lines[i].x1);
					ui.openGLWidget->mData.push_back(Adapter->Lines[i].y1);
					ui.openGLWidget->mData.push_back(Adapter->Lines[i].z1);
					ui.openGLWidget->mData.push_back(Adapter->Lines[i].x2);
					ui.openGLWidget->mData.push_back(Adapter->Lines[i].y2);
					ui.openGLWidget->mData.push_back(Adapter->Lines[i].z2);
									
					////////////push back
					ui.openGLWidget->mDataSection.push_back(ds);
					ds.pos += ds.size;
				}
			}
		}
	}

	if (Adapter->Arcs.size()) {//Œ¥≤‚ ‘
		QList <QTreeWidgetItem*> list = ui.treeWidget->findItems(QString("Arcs"), Qt::MatchFixedString);
		QTreeWidgetItem *item = list[0];
		if (item->checkState(0) != Qt::Unchecked) {
			double tempx, tempy, tempz;
			ds.size = 50;
			for (int i = 0; i < Adapter->Arcs.size(); i++) {
				if (item->child(i)->checkState(0) == Qt::Checked) {					
					double x1, x2, y1, y2;
					x1 = Adapter->Arcs[i].cx + Adapter->Arcs[i].radius*cos(PI*Adapter->Arcs[i].angle1 / 180);
					y1 = Adapter->Arcs[i].cy + Adapter->Arcs[i].radius*sin(PI*Adapter->Arcs[i].angle1 / 180);
					x2 = Adapter->Arcs[i].cx + Adapter->Arcs[i].radius*cos(PI*Adapter->Arcs[i].angle2 / 180);
					y2 = Adapter->Arcs[i].cy + Adapter->Arcs[i].radius*sin(PI*Adapter->Arcs[i].angle2 / 180);
					x1 = abs(x1) <= 0.00001 ? 0 : x1;
					y1 = abs(y1) <= 0.00001 ? 0 : y1;
					x2 = abs(x2) <= 0.00001 ? 0 : x2;
					y2 = abs(y2) <= 0.00001 ? 0 : y2;

					double I = Adapter->Arcs[i].cx - x1, J = Adapter->Arcs[i].cy - y1;
					double R = sqrt(I*I + J*J);

					double s, e;
					s = atan2f(y1 - Adapter->Arcs[i].cy, x1 - Adapter->Arcs[i].cx);
					e = atan2f(y2 - Adapter->Arcs[i].cy, x2 - Adapter->Arcs[i].cx);
					double start, length;
					if (s == e) {
						length = 2 * Pi;
						start = e;
					}
					else {
						float t = s - e;
						if (t > 0) {
							start = s;
							length = 2 * PI - t;
						}
						else {
							start = s;
							length = -t;
						}
					}
					for (int k = 1, n = 50; k <= n; ++k) {
						tempx = Adapter->Arcs[i].cx + abs(R)* cos(length / n*k + start);
						tempy = Adapter->Arcs[i].cy + abs(R) * sin(length / n*k + start);
						tempz = Adapter->Arcs[i].cz;
						ui.openGLWidget->mData.push_back(tempx);
						ui.openGLWidget->mData.push_back(tempy);
						ui.openGLWidget->mData.push_back(tempz);
					}
					////////////push back
					ui.openGLWidget->mDataSection.push_back(ds);
					ds.pos += ds.size;
				}
			}
		}
	}

	if (Adapter->Circles.size()) {
		QList <QTreeWidgetItem*> list = ui.treeWidget->findItems(QString("Circles"), Qt::MatchFixedString);
		QTreeWidgetItem *item = list[0];
		if (item->checkState(0) != Qt::Unchecked) {
			double tempx, tempy, tempz;
			ds.size = 50;
			for (int i = 0; i < Adapter->Circles.size(); i++) {
				if (item->child(i)->checkState(0) == Qt::Checked) {
					for (int k = 1, n = 50, R = 0.1; k <= n; ++k) {
						tempx = Adapter->Circles[i].cx + Adapter->Circles[i].radius* cos(2 * PI / n*k);
						tempy = Adapter->Circles[i].cy + Adapter->Circles[i].radius * sin(2 * PI / n*k);
						tempz = Adapter->Circles[i].cz;
						ui.openGLWidget->mData.push_back(tempx);
						ui.openGLWidget->mData.push_back(tempy);
						ui.openGLWidget->mData.push_back(tempz);

					}
					////////////push back	
					ui.openGLWidget->mDataSection.push_back(ds);
					ds.pos += ds.size;
				}
			}
		}
	}

	if (Adapter->Polylines.size()) {
		
		QList <QTreeWidgetItem*> list = ui.treeWidget->findItems(QString("Polylines"), Qt::MatchFixedString);
		QTreeWidgetItem *item = list[0];
		if (item->checkState(0) != Qt::Unchecked) {
			for (int i = 0; i < Adapter->Polylines.size(); i++) {
				if (item->child(i)->checkState(0) == Qt::Checked) {
					QList<DL_VertexData>& vertexs = Adapter->Polylines[i].Vertexs;
					ds.size = 0;
					double tempx, tempy, tempz;
					bool  curbulge = false;
					bool	 NextBulge = false;
					bool LastBulge = true;
					int flags = Adapter->Polylines[i].PolylineData.flags;
					int ttt = 0;

					switch (flags)
					{
					case 0:
					case 1:
						if (flags == 1) {
							vertexs.push_back(vertexs[0]);
						}
						
						for (int j = 0; j < vertexs.size() - 1; j++) {
							curbulge = vertexs[j].bulge == (double)0;
							if (!curbulge) {
								ds.size = 0;
								for (int K = ttt; K <= j; K++) {
									ui.openGLWidget->mData.push_back(vertexs[K].x);
									ui.openGLWidget->mData.push_back(vertexs[K].y);
									ui.openGLWidget->mData.push_back(vertexs[K].z);
									ds.size += 1;
								}
								if (ds.size) {
									ui.openGLWidget->mDataSection.push_back(ds);
									ds.pos += ds.size;
								}

								ttt = j+1;


								//push back µ±«∞

								ds.size = 50;

								double x1, x2, y1, y2, bulge;
								x1 = vertexs[j].x, y1 = vertexs[j].y, x2 = vertexs[j + 1].x, y2 = vertexs[j + 1].y, bulge = vertexs[j].bulge;
								double centerAngle;//∞¸Ω«
								centerAngle = 4 * atan(abs(bulge));
								double L; //œ“≥§
								L = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));

								double R;//‘≤ª°∞Îæ∂
								R = 0.5*L / sin(0.5*centerAngle);
								if (abs(bulge) > 1) {
									R *= -1;
								}
								bool isCW;
								if (bulge > 0)
									isCW = false;
								else
									isCW = true;
								double cx, cy, start, lenth;
								XYR_GetArc(x1, y1, x2, y2, R, isCW, cx, cy, start, lenth);
								for (int k = 1, n = 50; k <= n; ++k) {
									tempx = cx + abs(R)* cos(lenth / n*k + start);
									tempy = cy + abs(R) * sin(lenth / n*k + start);
									tempz = vertexs[j].z;
									ui.openGLWidget->mData.push_back(tempx);
									ui.openGLWidget->mData.push_back(tempy);
									ui.openGLWidget->mData.push_back(tempz);
								}
								ui.openGLWidget->mDataSection.push_back(ds);
								ds.pos += ds.size;
								continue;
							}

							if (j == vertexs.size() - 2) {
								ds.size = 0;
								for (int K = ttt; K <= vertexs.size() - 1; K++) {
									ui.openGLWidget->mData.push_back(vertexs[K].x);
									ui.openGLWidget->mData.push_back(vertexs[K].y);
									ui.openGLWidget->mData.push_back(vertexs[K].z);
									ds.size += 1;
								}
								if (ds.size) {
									ui.openGLWidget->mDataSection.push_back(ds);
									ds.pos += ds.size;
								}

							}

						}

					default:
						break;
					}
					//////////push back	
				}
			}
		}
	}

	if (Adapter->Ellipses.size()) {
		QList <QTreeWidgetItem*> list = ui.treeWidget->findItems(QString("Ellipses"), Qt::MatchFixedString);
		QTreeWidgetItem *item = list[0];
		ds.size = 200;
		if (item->checkState(0) != Qt::Unchecked) {
			for (int i = 0; i < Adapter->Ellipses.size(); i++) {
				if (item->child(i)->checkState(0) == Qt::Checked) {

					double start_angle, end_angle;
					start_angle = Adapter->Ellipses[i].angle1;
					end_angle = Adapter->Ellipses[i].angle2;

					double x, y, a, b;
					x = Adapter->Ellipses[i].cx;
					y = Adapter->Ellipses[i].cy;
					a = sqrt(Adapter->Ellipses[i].mx*Adapter->Ellipses[i].mx + Adapter->Ellipses[i].my*Adapter->Ellipses[i].my);
					b = Adapter->Ellipses[i].ratio *a;

					double curx, cury;
					double n = 200;

					if (start_angle < end_angle) {
						for (int j = 1; j <= n; j++) {
							curx = x + a* cosf(2 * PI*(j / n)*(end_angle - start_angle) + start_angle);
							cury = y + b*sinf(2 * PI*(j / n)*(end_angle - start_angle) + start_angle);
							ui.openGLWidget->mData.push_back(curx);
							ui.openGLWidget->mData.push_back(cury);
							ui.openGLWidget->mData.push_back(Adapter->Ellipses[i].cz);
						}
					}

					////////////push back	
					ui.openGLWidget->mDataSection.push_back(ds);
					ds.pos += ds.size;
				}
			}
		}
	}

	if (Adapter->Splines.size()) {
		QList <QTreeWidgetItem*> list = ui.treeWidget->findItems(QString("Splines"), Qt::MatchFixedString);
		QTreeWidgetItem *item = list[0];
		if (item->checkState(0) != Qt::Unchecked) {
			for (int i = 0; i < Adapter->Splines.size(); i++) {
				if (item->child(i)->checkState(0) == Qt::Checked) {


					////////////push back	
				}
			}
		}
	}

	/////bind data
	ui.openGLWidget->BindData();
	connect(ui.treeWidget, &QTreeWidget::itemChanged, this, &DFX_GCode::slotitemChanged);
}
void DFX_GCode::slotitemChanged(QTreeWidgetItem *item, int column) {
	disconnect(ui.treeWidget, &QTreeWidget::itemChanged,this, &DFX_GCode::slotitemChanged);
	if (item->parent() == NULL)
		ChangeSubState(item);
	else
		ChangeParentState(item);
	InitData();
}

