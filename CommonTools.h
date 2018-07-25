#pragma once
#include"QPainter "
#include "mccdll.h"
#include "QMouseEvent"
#include <QMap>
#include <QTextStream>
#include"mccdll.h"

extern mccdll::MotionControlCard* mcc;
struct  DrillHoleData;

class SammonFunc :public QObject {
	Q_OBJECT
public:
	static void release() { delete func; }
	static QString GetNumber(QString curline, char upper, char lower) {//获取 字符后面的数字；
		QString Code = "";
		for (QString::Iterator it = curline.begin(); it != curline.end(); it++) {
			if (*it == upper || *it == lower) {
				int i = 0;
				while (++i) {
					if ((*(it + i) < '0' || *(it + i) > '9') && !(*(it + i) == '.' || *(it + i) == ' ' || *(it + i) == '-') || (it + i) == curline.end()) {
						return Code;
					}
					else {
						Code += *(it + i);
					}
				}
			}
		}
		return Code;
	}
	static SammonFunc* Getins() {
		if (func == NULL)
			func = new SammonFunc;
		return func;
	}
	int needRunNext = 0;//G31 第0位 ；isMCode 第一位
	int readBit(int num,int bitNum) {//最右边为 第0位,返回0或1
		return num&(1 << bitNum);
	}
	void writeBit(int& num,int bitNum,int value) {//最右边为 第0位，写0或1
		if (num&(1 << bitNum) ){
			if (value == 0) {
				num -= (1 << bitNum);
			}
		}
		else {
			if (value)
				num += (1 << bitNum);
		}
	}
	void RunMCode(bool FromMDI, const char* code);
	QString getAxis(int a) {
		QString str;
		switch (a)
		{
		case 0 :
			str = "X";	break;
		case 1:
			str = "Y";	break;
		case 2:
			str = "Z";	break;
		case 3:
			str = "A";	break;
		case 4:
			str = "B";	break;
		case 5:
			str = "C";
			break;
		}
		return str;
	}
	static bool CanDoit(bool NeedCheckPause = true);//判断能否执行指令（卡是否处于空闲）
	static bool CheckContains(QString line, int count, ...);//判断给定字符串是否包含给定字符串
	static void SetSpeedControl_stop(bool isSimulation=false);
	static void CheckFeedrate();
	static int SwtichTInLine(int line);
	static void fillBackground(QWidget *widget, QColor color)
	{
		widget->setAutoFillBackground(true);
		QPalette palette;
		palette.setColor(QPalette::Background, color);
		//palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background.png")));
		widget->setPalette(palette);
	}
	static QString msToDate(int t) {
		t = t / 1000;
		int hour = t / 60 / 60;
		int min = t / 60 % 60;
		int sec = t % 60;
		char buff[20];
		sprintf(buff, "%02d:%02d:%02d", hour,min,sec);
		return buff;
	}
	static bool IsNumber(QString& str);
	static QString GetSpeed(int flag,int Axis = 0);//参数1 ：0 默认速度，1，自动速度，2，手动速度，

	static bool isNeedOpenSpindleRotat ;//断点续传 打开主轴 判断
	static  int GJSpeed() { return iGJSpeed; }//进给速度倍率
	static void SetGJSpeed(int i) { iGJSpeed = i; }
	static bool IsPause;
	bool isLowSpeed = true;
	static bool In6GuangMuXinHao;//In6 光幕信号
	static bool XHoneEnabled;//使能标志
	static bool YHoneEnabled;
	static bool ZHoneEnabled;
	static bool AHoneEnabled;
	static bool BHoneEnabled;
	static bool CHoneEnabled;
	static bool bNeedClear;
	static bool isToolSetting;//固定对刀
	static bool isFToolSetting;//浮动对刀
	static bool RunShow ;//开始键 状态
	static bool PauseShow;// 状态
	static bool NextShow;// 状态
	static bool isLoading;//是否载入G代码
	
	static int StartLine;//急停时 行号,,
	static bool NeedRunNext;//M00停下时，Ncpod 缓存的行号是 当前行，，断点续传 回继续这行 M00，此时需要执行下一行
	static bool offsetSucces;//判断设置的模式 是否成功
	static bool isStartFormIdx;
	static QMap<int, QString> ReplaceCodeMap; //特殊G代码，M代码 替换
	static QMap<int, DrillHoleData>DrillHoleMap;//特殊G代码（转孔） 替换
	static QMap<int, int> TCodeMap; //缓存
	static QString sToolName;//刀具名称

	static bool LastCoordinateInit;//初始化上次坐标点标记

	bool Loading = false;// 是否正在载入
	bool isRegSoft = true;

	bool autoToolSetting = false;

signals:	void sendDxfStream(QTextStream&,QString, int);
signals:	void ZhuCheKuaiDaoQi(QString);
signals:void updateState(QString, QString);//改变状态文本

signals:void TabIndexChang(int,int);//改变手动速度
signals:void SendShowGCodeGLWidget();
signals:	void EditFile(QString FileName);
signals:	void LoadFile(QString FileName);
signals:	void UnloadFile();
signals:	void startLineloadOver();
signals:	void ResetIOText();
public:int IndexRrcod = 0;
private:
	static QString sMachiningSpeed;
	static SammonFunc* func;
	static int iGJSpeed;//j进给速度倍率
	SammonFunc() {}
	~SammonFunc() {}
	SammonFunc(const SammonFunc &) {}
	SammonFunc & operator = (const SammonFunc &) {}
};

