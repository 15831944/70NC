#include "DlgParamNum.h"
#include "ReadIni.h"
#include"ncpod.h"
#include "TrLang.h"
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
extern int VersionType;
#include "QValidator"
DlgParamNum::DlgParamNum(QWidget *parent)
	: StyleDlg(parent)
{
	ui.setupUi(this);
	setLine();
	setAttribute(Qt::WA_DeleteOnClose, true);
	show();
	ResetLanguage();
	connect(ui.bty, &QPushButton::clicked, [this]() {	func();//close();
	});
	connect(ui.btn, &QPushButton::clicked, [this]() {close();}
	);

	ui.TiShi->setVisible(false);
	connect(ui.lineEdit, &QLineEdit::textChanged, [this]() {
		ui.TiShi->setVisible(false);
	});
	ui.lineEdit->setValidator(new QDoubleValidator());


	installEventFilter(this);
	ui.bty->installEventFilter(this);
	ui.btn->installEventFilter(this);
	ui.lineEdit->installEventFilter(this);
}

DlgParamNum::~DlgParamNum()
{
}

void DlgParamNum::ResetLanguage()
{
	setDlgName(TrLang::text(82));
	ui.label->setText(TrLang::text(322));
	ui.label_3->setText(TrLang::text(331));
	ui.label_2->setText(TrLang::text(122));
	ui.label_7->setText(TrLang::text(323));

	ui.bty->setText(TrLang::text(160));
	ui.btn->setText(TrLang::text(111));
}

bool DlgParamNum::eventFilter(QObject * obj, QEvent * event)
{
	if (obj == this ||
		obj == ui.bty ||
		obj == ui.btn ||
		obj == ui.lineEdit) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent *key_event = static_cast<QKeyEvent*>(event);
	
			if (key_event->key() == Qt::Key_Enter|| key_event->key() == Qt::Key_Return)
			{
				bool b1 = ui.bty->hasFocus();
				bool b2 = ui.btn->hasFocus();
				bool b3 = ui.lineEdit->hasFocus();
	
				if (b1||b3) {
					ui.bty->clicked();
				}
				else if (b2) {
					ui.btn->clicked();
				}	
				else
				{
		
				}
				return true;
			}
		}
	}
	return QWidget::eventFilter(obj, event);
}
void DlgParamNum::func()
{
	fun11();
	fun15();
	fun21();
	fun25();
	fun31();
}

void DlgParamNum::fun11()
{
	if (mId == ("N11002")) {
		int p = ui.lineEdit->text().toInt();
		if (p >0) {
			readIni.SetMWaitSignalItme(p);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N11012")) {
		int p = ui.lineEdit->text().toInt();
		if (0<=p&&p<=2) {
			readIni.SetStopZParam(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N11014")) {
		int v = ui.lineEdit->text().toDouble();
		if (1<=v&&v<=1000) {
			readIni.SetStopZValue(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N12001"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetSafetyHeight(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N12002"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double v = ui.lineEdit->text().toDouble();//G0速度，空程速度
			mcc->SetParameterValue(130, v);
			mcc->SetParameterValue(131, v);
			mcc->SetParameterValue(132, v);
			mcc->SetParameterValue(133, v);
			mcc->SetParameterValue(134, v);
			mcc->SetParameterValue(135, v);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == "N12003") {
		if (ui.lineEdit->text().toInt()>150&& ui.lineEdit->text().toInt()<=20000) {
			int GJspeed = ui.lineEdit->text().toInt();
			mcc->SetFeedrateMultiple(GJspeed);
			readIni.SetFeedrate(ui.lineEdit->text());
			mcc->SetParameterValue(105, (float)GJspeed*1.5);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == "N12009") {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetZCloseValue(ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N12012"))
	{
		float tt = ui.lineEdit->text().toFloat();
		if (tt >= 1.0&&tt<=20.0) {
			readIni.SetG73_d(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
}

void DlgParamNum::fun15()
{
	if (mId == ("N15001"))
	{
		if (1) {
			mcc->SetParameterValue(101, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N15002")) {
		if (1) {
			mcc->SetParameterValue(102, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N15003")) {
		if (1) {
			mcc->SetParameterValue(103, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
}

void DlgParamNum::fun21()
{
	if (mId == ("N21001"))
		{
		if (ui.lineEdit->text().toInt() >= 10 && 9999 >= ui.lineEdit->text().toInt()) {
				readIni.SetSpindleOpen(ui.lineEdit->text());
				emit ChioceYes();
				close();
			}
			else {
				ui.TiShi->setText(TrLang::text(349));
				ui.TiShi->setVisible(true);
			}
		}
	else if (mId == ("N21002")) {
		if (ui.lineEdit->text().toInt() >= 10 && 9999 >= ui.lineEdit->text().toInt()) {
			readIni.SetSpindleClose(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}

	}
	else if (mId == ("N21003")) {
		if (ui.lineEdit->text().toInt() >= 10 && 9999 >= ui.lineEdit->text().toInt()) {
			readIni.SetM07Time(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}

	}
	else if (mId == ("N21004")) {
		if (ui.lineEdit->text().toInt() >= 10 && 9999 >= ui.lineEdit->text().toInt()) {
			readIni.SetM08Time(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}

	}
	else if (mId == ("N21005")) {
		if (ui.lineEdit->text().toInt() >= 10&&9999>= ui.lineEdit->text().toInt()) {
			readIni.SetM09Time(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}

	}
	else if (mId == ("N21006")) {
		if ((ui.lineEdit->text().toInt() == 1 || ui.lineEdit->text().toInt() == 0)) {
			readIni.SetXMotorDirLevel(ui.lineEdit->text());
			NcPod::getIns()->Set_MotorDirLeve(0, 0, ui.lineEdit->text().toInt());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}

	}
	else if (mId == ("N21007")) {
		if ((ui.lineEdit->text().toInt() == 1 || ui.lineEdit->text().toInt() == 0)) {
			readIni.SetYMotorDirLevel(ui.lineEdit->text());
			NcPod::getIns()->Set_MotorDirLeve(0, 1, ui.lineEdit->text().toInt());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}

	}
	else if (mId == ("N21008")) {
		if ((ui.lineEdit->text().toInt() == 1 || ui.lineEdit->text().toInt() == 0)) {
			readIni.SetZMotorDirLevel(ui.lineEdit->text());
			NcPod::getIns()->Set_MotorDirLeve(0, 2, ui.lineEdit->text().toInt());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21009")) {
		if ((ui.lineEdit->text().toInt() == 1 || ui.lineEdit->text().toInt() == 0)) {
			readIni.SetAMotorDirLevel(ui.lineEdit->text());
			NcPod::getIns()->Set_MotorDirLeve(0, 3, ui.lineEdit->text().toInt());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21010")) {
		if ((ui.lineEdit->text().toInt() == 1 || ui.lineEdit->text().toInt() == 0)) {
			readIni.SetBMotorDirLevel(ui.lineEdit->text());
			NcPod::getIns()->Set_MotorDirLeve(0, 4, ui.lineEdit->text().toInt());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21011")) {
		if ((ui.lineEdit->text().toInt() == 1 || ui.lineEdit->text().toInt() == 0)) {
			readIni.SetCMotorDirLevel(ui.lineEdit->text());
			NcPod::getIns()->Set_MotorDirLeve(0, 5, ui.lineEdit->text().toInt());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N21012"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(320, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N21013"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(321, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N21014"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(322, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N21015"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(323, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N21016"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(324, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N21017"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(325, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21018")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(330, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21019")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(331, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21020")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(332, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21021")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ) {
			mcc->SetParameterValue(333, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21022")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(334, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21023")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(335, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21024"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double value = ui.lineEdit->text().toDouble()*mcc->GetParameterValue(110) / mcc->GetParameterValue(120);
			mcc->SetParameterValue(380, value);
			NcPod::getIns()->Set_Ac(0, 0, value);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21025"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double value = ui.lineEdit->text().toDouble()*mcc->GetParameterValue(111) / mcc->GetParameterValue(121);
			mcc->SetParameterValue(381, value);
			NcPod::getIns()->Set_Ac(0, 1, value);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21026"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double value = ui.lineEdit->text().toDouble()*mcc->GetParameterValue(112) / mcc->GetParameterValue(122);
			mcc->SetParameterValue(382, value);
			NcPod::getIns()->Set_Ac(0, 2, value);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21027"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double value = ui.lineEdit->text().toDouble()*mcc->GetParameterValue(113) / mcc->GetParameterValue(123);
			mcc->SetParameterValue(383, value);
			NcPod::getIns()->Set_Ac(0, 3, value);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21028"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double value = ui.lineEdit->text().toDouble()*mcc->GetParameterValue(114) / mcc->GetParameterValue(124);
			mcc->SetParameterValue(384, value);
			NcPod::getIns()->Set_Ac(0, 4, value);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N21029"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			double value = ui.lineEdit->text().toDouble()*mcc->GetParameterValue(115) / mcc->GetParameterValue(125);
			mcc->SetParameterValue(385, value);
			NcPod::getIns()->Set_Ac(0, 5, value);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
}

void DlgParamNum::fun25()
{
	//以下if条件 以后换成 范围判断   （QDoubleValidator 范围无效)
	if (mId == "dasadsad") {

	}
	else if (mId == ("N25001"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text()) ){
			NcPod::getIns()->Set_Steppe(0, 0, ui.lineEdit->text().toDouble());
			mcc->SetParameterValue(110, mcc->GetParameterValue(120) *ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25002")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			NcPod::getIns()->Set_Steppe(0, 1, ui.lineEdit->text().toDouble());
			mcc->SetParameterValue(111, mcc->GetParameterValue(121)* ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25003"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			NcPod::getIns()->Set_Steppe(0, 2, ui.lineEdit->text().toDouble());
			mcc->SetParameterValue(112, mcc->GetParameterValue(122) *ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25019")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			NcPod::getIns()->Set_Steppe(0, 3, ui.lineEdit->text().toDouble());
			mcc->SetParameterValue(113, mcc->GetParameterValue(123) * ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25020"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			NcPod::getIns()->Set_Steppe(0, 4, ui.lineEdit->text().toDouble());
			mcc->SetParameterValue(114, mcc->GetParameterValue(124) *ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25021")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			NcPod::getIns()->Set_Steppe(0, 5, ui.lineEdit->text().toDouble());
			mcc->SetParameterValue(115, mcc->GetParameterValue(125) * ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25007"))
	{
		int limv = ui.lineEdit->text().toInt();
		if (-9999<=limv&&limv<readIni.GetXPosPlus().toInt()) {
			readIni.SetXPosMinus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25008")) {
		int limv = ui.lineEdit->text().toInt();
		if (-9999<=limv&&limv<readIni.GetYPosPlus().toInt()) {
			readIni.SetYPosMinus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25009"))
	{
		int limv = ui.lineEdit->text().toInt();
		if (-9999<=limv&&limv<readIni.GetZPosPlus().toInt()) {
			readIni.SetZPosMinus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25010")) {
		int limv = ui.lineEdit->text().toInt();
		if (readIni.GetXPosMinus().toInt()<limv&&limv<=9999) {
			readIni.SetXPosPlus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25011"))
	{
		int limv = ui.lineEdit->text().toInt();
		if (readIni.GetYPosMinus().toInt()<limv&&limv <= 9999) {
			readIni.SetYPosPlus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25012")) {
		int limv = ui.lineEdit->text().toInt();
		if (readIni.GetZPosMinus().toInt()<limv&&limv <= 9999) {
			readIni.SetZPosPlus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25025")) {
		int limv = ui.lineEdit->text().toInt();
		if (-360 <= limv&&limv<readIni.GetAPosPlus().toInt()) {
			readIni.SetAPosMinus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25026")) {
		int limv = ui.lineEdit->text().toInt();
		if (-360 <= limv&&limv<readIni.GetBPosPlus().toInt()) {
			readIni.SetBPosMinus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25027")) {
		int limv = ui.lineEdit->text().toInt();
		if (-360 <= limv&&limv<readIni.GetCPosPlus().toInt()) {
			readIni.SetCPosMinus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25028")) {
		int limv = ui.lineEdit->text().toInt();
		if (readIni.GetAPosMinus().toInt()<limv&&limv <= 360) {
			readIni.SetAPosPlus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25029")) {
		int limv = ui.lineEdit->text().toInt();
		if (readIni.GetBPosMinus().toInt()<limv&&limv <= 360) {
			readIni.SetBPosPlus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25030")) {
		int limv = ui.lineEdit->text().toInt();
		if (readIni.GetCPosMinus().toInt()<limv&&limv <= 360) {
			readIni.SetCPosPlus(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25034")) {
		int num = ui.lineEdit->text().toInt();
		if (num==0||num==1) {
			int temp = readIni.GetPulseDirection();
			SammonFunc::Getins()->writeBit(temp, 0, num);
			readIni.SetPulseDirection(temp);
			NcPod::getIns()->Set_MotorPulsLeve(0, 0, num);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25035")) {
		int num = ui.lineEdit->text().toInt();
		if (num == 0 || num == 1) {
			int temp = readIni.GetPulseDirection();
			SammonFunc::Getins()->writeBit(temp, 1, num);
			readIni.SetPulseDirection(temp);
			NcPod::getIns()->Set_MotorPulsLeve(0, 1, num);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25036")) {
		int num = ui.lineEdit->text().toInt();
		if (num == 0 || num == 1) {
			int temp = readIni.GetPulseDirection();
			SammonFunc::Getins()->writeBit(temp, 2, num);
			readIni.SetPulseDirection(temp);
			NcPod::getIns()->Set_MotorPulsLeve(0, 2, num);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25037")) {
		int num = ui.lineEdit->text().toInt();
		if (num == 0 || num == 1) {
			int temp = readIni.GetPulseDirection();
			SammonFunc::Getins()->writeBit(temp, 3, num);
			readIni.SetPulseDirection(temp);
			NcPod::getIns()->Set_MotorPulsLeve(0, 3, num);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25038")) {
		int num = ui.lineEdit->text().toInt();
		if (num == 0 || num == 1) {
			int temp = readIni.GetPulseDirection();
			SammonFunc::Getins()->writeBit(temp, 4, num);
			readIni.SetPulseDirection(temp);
			NcPod::getIns()->Set_MotorPulsLeve(0, 4, num);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N25039")) {
		int num = ui.lineEdit->text().toInt();
		if (num == 0 || num == 1) {
			int temp = readIni.GetPulseDirection();
			SammonFunc::Getins()->writeBit(temp, 5, num);
			NcPod::getIns()->Set_MotorPulsLeve(0, 5, num);
			readIni.SetPulseDirection(temp);
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
}
void DlgParamNum::fun31()
{
	if (mId == ("N31002"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(250, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31003")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(251, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31004")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT1X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31005")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT1Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31006")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT1Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31008"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(252, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31009")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(253, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31010")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT2X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31011")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT2Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31012")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT2Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31014"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(254, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31015")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(255, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31016")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT3X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31017")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT3Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31018")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT3Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31020"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(256, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31021")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(257, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31022")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT4X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31023")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT4Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31024")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT4Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N31026"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(258, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31027")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(259, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31028")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT5X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31029")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT5Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31030")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT5Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N31032"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(260, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31033")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(261, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31034")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT6X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31035")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT6Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31036")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT6Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N31038"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(262, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31039")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(263, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31040")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT7X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31041")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT7Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31042")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT7Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	if (mId == ("N31044"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(264, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31045")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(265, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31046")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT8X(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31047")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT8Y(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31048")) {
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			readIni.SetT8Z(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31049")) {
		int flag = ui.lineEdit->text().toInt();
		bool b31049;
		QString str;
		if (VersionType == 1) {
			b31049 = (flag == 0 || flag == 1);
			str = TrLang::text(349);
		}
		else {
			b31049 = (flag == 0 || flag == 1 || flag == 2);
			str = TrLang::text(349);
		}
		
		if (b31049) {
			readIni.SetToolChangeOpt(ui.lineEdit->text());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(str);
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31050"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(266, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31051"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(268, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31052"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(270, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31053"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(272, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31054"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(274, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31055"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(276, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31056"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(278, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
	else if (mId == ("N31057"))
	{
		if (SammonFunc::IsNumber(ui.lineEdit->text())) {
			mcc->SetParameterValue(280, ui.lineEdit->text().toDouble());
			emit ChioceYes();
			close();
		}
		else {
			ui.TiShi->setText(TrLang::text(349));
			ui.TiShi->setVisible(true);
		}
	}
}
//else if (mId == ("N11001"))
//{
//	if (SammonFunc::IsNumber(ui.lineEdit->text())) {
//		emit ChioceYes();
//		close();
//	}
//	else {
//		ui.TiShi->setText(TrLang::text(349));
//		ui.TiShi->setVisible(true);
//	}
//}
//else if (mId == ("N11002")) {
//	if (SammonFunc::IsNumber(ui.lineEdit->text())) {
//		emit ChioceYes();
//		close();
//	}
//	else {
//		ui.TiShi->setText(TrLang::text(349));
//		ui.TiShi->setVisible(true);
//	}
//}
