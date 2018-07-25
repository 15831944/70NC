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
	static QString GetNumber(QString curline, char upper, char lower) {//��ȡ �ַ���������֣�
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
	int needRunNext = 0;//G31 ��0λ ��isMCode ��һλ
	int readBit(int num,int bitNum) {//���ұ�Ϊ ��0λ,����0��1
		return num&(1 << bitNum);
	}
	void writeBit(int& num,int bitNum,int value) {//���ұ�Ϊ ��0λ��д0��1
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
	static bool CanDoit(bool NeedCheckPause = true);//�ж��ܷ�ִ��ָ����Ƿ��ڿ��У�
	static bool CheckContains(QString line, int count, ...);//�жϸ����ַ����Ƿ���������ַ���
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
	static QString GetSpeed(int flag,int Axis = 0);//����1 ��0 Ĭ���ٶȣ�1���Զ��ٶȣ�2���ֶ��ٶȣ�

	static bool isNeedOpenSpindleRotat ;//�ϵ����� ������ �ж�
	static  int GJSpeed() { return iGJSpeed; }//�����ٶȱ���
	static void SetGJSpeed(int i) { iGJSpeed = i; }
	static bool IsPause;
	bool isLowSpeed = true;
	static bool In6GuangMuXinHao;//In6 ��Ļ�ź�
	static bool XHoneEnabled;//ʹ�ܱ�־
	static bool YHoneEnabled;
	static bool ZHoneEnabled;
	static bool AHoneEnabled;
	static bool BHoneEnabled;
	static bool CHoneEnabled;
	static bool bNeedClear;
	static bool isToolSetting;//�̶��Ե�
	static bool isFToolSetting;//�����Ե�
	static bool RunShow ;//��ʼ�� ״̬
	static bool PauseShow;// ״̬
	static bool NextShow;// ״̬
	static bool isLoading;//�Ƿ�����G����
	
	static int StartLine;//��ͣʱ �к�,,
	static bool NeedRunNext;//M00ͣ��ʱ��Ncpod ������к��� ��ǰ�У����ϵ����� �ؼ������� M00����ʱ��Ҫִ����һ��
	static bool offsetSucces;//�ж����õ�ģʽ �Ƿ�ɹ�
	static bool isStartFormIdx;
	static QMap<int, QString> ReplaceCodeMap; //����G���룬M���� �滻
	static QMap<int, DrillHoleData>DrillHoleMap;//����G���루ת�ף� �滻
	static QMap<int, int> TCodeMap; //����
	static QString sToolName;//��������

	static bool LastCoordinateInit;//��ʼ���ϴ��������

	bool Loading = false;// �Ƿ���������
	bool isRegSoft = true;

	bool autoToolSetting = false;

signals:	void sendDxfStream(QTextStream&,QString, int);
signals:	void ZhuCheKuaiDaoQi(QString);
signals:void updateState(QString, QString);//�ı�״̬�ı�

signals:void TabIndexChang(int,int);//�ı��ֶ��ٶ�
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
	static int iGJSpeed;//j�����ٶȱ���
	SammonFunc() {}
	~SammonFunc() {}
	SammonFunc(const SammonFunc &) {}
	SammonFunc & operator = (const SammonFunc &) {}
};

