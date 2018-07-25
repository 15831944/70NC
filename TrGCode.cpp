#include "TrGCode.h"
#include "QString"
#include "Samcon.h"
#include "CommonTools.h"
#include "ReadIni.h"
#include "ncpod.h"
#include "LogManager.h"
#include "MccTools.h"
extern Samcon* w;
extern mccdll::MotionControlCard* mcc;
extern ReadIni readIni;
TrGCode::TrGCode()
{
}


TrGCode::~TrGCode()
{
}
void TrGCode::DoDrillHoleCodeG81() {
	static bool RunOver = true;
	static bool DoStep1Over = false;
	static bool DoStep2Over = false;
	static bool DoStep3Over = false;
	static bool DoStep4Over = false;

	static bool IsStepInit = false;

	static QString step1 = "";
	static QString step2 = "";
	static QString step3 = "";
	static QString step4 = "";
	static int i = 0;
	if (isG81) {

		if (!IsStepInit) {
			if (mcc->IniPnowFlg() != 0)return;
			double curZ = mcc->GetWorkpieceCoordinate(2);

			if (mDrillHoleData.isNeedStep1 == 0) {
				DoStep1Over = true;
				step1 = "";
			}
			else if (mDrillHoleData.isNeedStep1 == 1) {
				step1 = "G00X" + mDrillHoleData.X;
			}
			else if (mDrillHoleData.isNeedStep1 == 2) {
				step1 = "G00Y" + mDrillHoleData.Y;
			}
			else if (mDrillHoleData.isNeedStep1 == 3) {
				step1 = "G00X" + mDrillHoleData.X + "Y" + mDrillHoleData.Y;
			}

			step2 = "G00Z" + mDrillHoleData.R;
			step3 = "G01Z" + mDrillHoleData.Z + "F" + mDrillHoleData.F;
			if (mDrillHoleData.isG99)
				step4 = step2;
			else
				step4 = "G00Z" + QString::number(curZ);
			IsStepInit = true;
			RunOver = false;
		}


		i++;
		if (i < 10)
			return;

		if (!DoStep1Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step1);
			DoStep1Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step1:" + step1);
			return;
		}

		if (DoStep1Over && !DoStep2Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step2);
			DoStep2Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step2:" + step2);
			return;
		}

		if (DoStep1Over && DoStep2Over && !DoStep3Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step3);
			DoStep3Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step3:" + step3);
			return;
		}

		if (DoStep1Over && DoStep2Over &&DoStep3Over && !DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step4);
			DoStep4Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step4:"+ step4);
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			IsStepInit = false;
			DoStep1Over = false;
			DoStep2Over = false;
			DoStep3Over = false;
			DoStep4Over = false;
			i = 0;
			isG81 = false;

			mcc->SendAutoText(QString(""));
			int startline = w->mCurRow + 1;
			mcc->SetStartline(startline);
			mcc->ClearBuffer();
			mcc->SetAutoRunFlag(true);
			RunOver = true;
			//LogManager::getIns()->appendLog("over");
			SammonFunc::CheckFeedrate();
		}

	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow;
			RunOver = true;
		}
		IsStepInit = false;
		DoStep1Over = false;
		DoStep2Over = false;
		DoStep3Over = false;
		DoStep4Over = false;
		i = 0;
	}
}
void TrGCode::DoDrillHoleCodeG82()
{
	static bool RunOver = true;
	static bool DoStep1Over = false;
	static bool DoStep2Over = false;
	static bool DoStep3Over = false;
	static bool DoStep4Over = false;
	static bool DoStep5Over = false;
	static bool IsStepInit = false;

	static QString step1 = "";
	static QString step2 = "";
	static QString step3 = "";
	static QString step4 = "";
	static QString step5 = "";
	static int i = 0;
	if (isG82) {

		if (!IsStepInit) {
			if (mcc->IniPnowFlg() != 0)return;
			double curZ = mcc->GetWorkpieceCoordinate(2);

			if (mDrillHoleData.isNeedStep1 == 0) {
				DoStep1Over = true;
				step1 = "";
			}
			else if (mDrillHoleData.isNeedStep1 == 1) {
				step1 = "G00X" + mDrillHoleData.X;
			}
			else if (mDrillHoleData.isNeedStep1 == 2) {
				step1 = "G00Y" + mDrillHoleData.Y;
			}
			else if (mDrillHoleData.isNeedStep1 == 3) {
				step1 = "G00X" + mDrillHoleData.X + "Y" + mDrillHoleData.Y;
			}

			step2 = "G00Z" + mDrillHoleData.R;
			step3 = "G01Z" + mDrillHoleData.Z + "F" + mDrillHoleData.F;
			float fp = mDrillHoleData.P.toDouble();
			step4 = "G04P" + QString::number(fp);//mcc 里面延时一部分时间 。本地延时500毫秒 防止G04 后执行mcc 错误
			if (mDrillHoleData.isG99)
				step5 = step2;
			else
				step5 = "G00Z" + QString::number(curZ);
			IsStepInit = true;
			RunOver = false;
		}


		i++;
		if (i < 10)
			return;

		if (!DoStep1Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step1);
			DoStep1Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step1:" + step1);
			return;
		}

		if (DoStep1Over && !DoStep2Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step2);
			DoStep2Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step2:" + step2);
			return;
		}

		if (DoStep1Over && DoStep2Over && !DoStep3Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step3);
			DoStep3Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step3:" + step3);
			return;
		}

		if (DoStep1Over && DoStep2Over &&DoStep3Over && !DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step4);
			DoStep4Over = true;
			i = -mDrillHoleData.P.toDouble() / 50;
			//	LogManager::getIns()->appendLog("step4:"+ step4);
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over && !DoStep5Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step5);
			DoStep5Over = true;
			i = 0;

			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over&& DoStep5Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			IsStepInit = false;
			DoStep1Over = false;
			DoStep2Over = false;
			DoStep3Over = false;
			DoStep4Over = false;
			DoStep5Over = false;
			i = 0;
			isG82 = false;

			mcc->SendAutoText(QString(""));
			int startline = w->mCurRow + 1;
			mcc->SetStartline(startline);
			mcc->ClearBuffer();
			mcc->SetAutoRunFlag(true);
			RunOver = true;
			//	LogManager::getIns()->appendLog("over");
			SammonFunc::CheckFeedrate();
		}

	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow;
			RunOver = true;
		}
		IsStepInit = false;
		DoStep1Over = false;
		DoStep2Over = false;
		DoStep3Over = false;
		DoStep4Over = false;
		DoStep5Over = false;
		i = 0;
	}
}
void TrGCode::DoDrillHoleCodeG73() {
	static bool RunOver = true;
	static bool DoStep1Over = false;
	static bool DoStep2Over = false;
	static bool DoStep3Over = false;
	static bool DoStep4Over = false;

	static bool IsStepInit = false;


	static QString step1 = "";
	static QString step2 = "";
	static QStringList step3;
	static QString step4 = "";
	static int i = 0;
	if (isG73) {


		if (!IsStepInit) {
			if (mcc->IniPnowFlg() != 0)return;
			double curZ = mcc->GetWorkpieceCoordinate(2);

			if (mDrillHoleData.isNeedStep1 == 0) {
				DoStep1Over = true;
				step1 = "";
			}
			else if (mDrillHoleData.isNeedStep1 == 1) {
				step1 = "G00X" + mDrillHoleData.X;
			}
			else if (mDrillHoleData.isNeedStep1 == 2) {
				step1 = "G00Y" + mDrillHoleData.Y;
			}
			else if (mDrillHoleData.isNeedStep1 == 3) {
				step1 = "G00X" + mDrillHoleData.X + "Y" + mDrillHoleData.Y;
			}

			step2 = "G00Z" + mDrillHoleData.R;
			//计算  第3不 需要 回退 进给的 所有G代码
			float QValue = mDrillHoleData.R.toFloat();
			float ZValue = mDrillHoleData.Z.toFloat();
			int i = 0;
			float QStep = mDrillHoleData.Q.toFloat();;
			while (1) {
				QValue -= QStep;
				if (QValue <= ZValue)
					break;
				i++;
			}
			step3.clear();

			for (int idx = 1; idx <= i; idx++) {
				float curQ = mDrillHoleData.R.toFloat() - QStep*idx;
				float cur_d = curQ + readIni.GetG73_d().toFloat();
				step3.push_back("G01Z" + QString::number(curQ) + "F" + mDrillHoleData.F);
				step3.push_back("G00Z" + QString::number(cur_d));
			}
			step3.push_back("G01Z" + mDrillHoleData.Z + "F" + mDrillHoleData.F);

			if (mDrillHoleData.isG99)
				step4 = step2;
			else
				step4 = "G00Z" + QString::number(curZ);

			IsStepInit = true;
			RunOver = false;
		}


		i++;
		if (i < 10)
			return;

		if (!DoStep1Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step1);
			DoStep1Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step1:" + step1);
			return;
		}

		if (DoStep1Over && !DoStep2Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step2);
			DoStep2Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step2:" + step2);
			return;
		}

		if (DoStep1Over && DoStep2Over && !DoStep3Over&&mcc->GetGmode(11).toInt() == 4 && step3.size()>0 && mcc->IniPnowFlg() == 0) {
			//	LogManager::getIns()->appendLog("step3:" + step3[0]);			
			if (step3.size() == 1)
				DoStep3Over = true;
			MccTools::SendMDI(step3.takeAt(0));
			i = 0;
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && !DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step4);
			DoStep4Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step4:" + step4);
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			IsStepInit = false;
			DoStep1Over = false;
			DoStep2Over = false;
			DoStep3Over = false;
			DoStep4Over = false;
			i = 0;
			isG73 = false;

			mcc->SendAutoText(QString(""));
			int startline = w->mCurRow + 1;
			mcc->SetStartline(startline);
			mcc->ClearBuffer();
			mcc->SetAutoRunFlag(true);
			RunOver = true;
			//LogManager::getIns()->appendLog("over");
			SammonFunc::CheckFeedrate();
		}

	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow;
			RunOver = true;
		}
		IsStepInit = false;
		DoStep1Over = false;
		DoStep2Over = false;
		DoStep3Over = false;
		DoStep4Over = false;
		i = 0;
	}
}
void TrGCode::DoDrillHoleCodeG85() {
	static bool RunOver = true;
	static bool DoStep1Over = false;
	static bool DoStep2Over = false;
	static bool DoStep3Over = false;
	static bool DoStep4Over = false;

	static bool IsStepInit = false;

	static QString step1 = "";
	static QString step2 = "";
	static QString step3 = "";
	static QString step4 = "";
	static int i = 0;
	if (isG85) {

		if (!IsStepInit) {
			if (mcc->IniPnowFlg() != 0)return;
			double curZ = mcc->GetWorkpieceCoordinate(2);

			if (mDrillHoleData.isNeedStep1 == 0) {
				DoStep1Over = true;
				step1 = "";
			}
			else if (mDrillHoleData.isNeedStep1 == 1) {
				step1 = "G00X" + mDrillHoleData.X;
			}
			else if (mDrillHoleData.isNeedStep1 == 2) {
				step1 = "G00Y" + mDrillHoleData.Y;
			}
			else if (mDrillHoleData.isNeedStep1 == 3) {
				step1 = "G00X" + mDrillHoleData.X + "Y" + mDrillHoleData.Y;
			}

			step2 = "G00Z" + mDrillHoleData.R;
			step3 = "G01Z" + mDrillHoleData.Z + "F" + mDrillHoleData.F;
			if (mDrillHoleData.isG99)
				step4 = "G01Z" + mDrillHoleData.R + "F" + mDrillHoleData.F;
			else
				step4 = "G01Z" + QString::number(curZ) + "F" + mDrillHoleData.F;
			IsStepInit = true;
			RunOver = false;
		}


		i++;
		if (i < 10)
			return;

		if (!DoStep1Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step1);
			DoStep1Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step1:" + step1);
			return;
		}

		if (DoStep1Over && !DoStep2Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step2);
			DoStep2Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step2:" + step2);
			return;
		}

		if (DoStep1Over && DoStep2Over && !DoStep3Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step3);
			DoStep3Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step3:" + step3);
			return;
		}

		if (DoStep1Over && DoStep2Over &&DoStep3Over && !DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step4);
			DoStep4Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step4:" + step4);
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			IsStepInit = false;
			DoStep1Over = false;
			DoStep2Over = false;
			DoStep3Over = false;
			DoStep4Over = false;
			i = 0;
			isG85 = false;

			mcc->SendAutoText(QString(""));
			int startline = w->mCurRow + 1;
			mcc->SetStartline(startline);
			mcc->ClearBuffer();
			mcc->SetAutoRunFlag(true);
			RunOver = true;
			//LogManager::getIns()->appendLog("over");
			SammonFunc::CheckFeedrate();
		}

	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow;
			RunOver = true;
		}
		IsStepInit = false;
		DoStep1Over = false;
		DoStep2Over = false;
		DoStep3Over = false;
		DoStep4Over = false;
		i = 0;
	}
}
void TrGCode::DoDrillHoleCodeG86() {
	static bool RunOver = true;
	static bool DoStep1Over = false;
	static bool DoStep2Over = false;
	static bool DoStep3Over = false;
	static bool DoStep4Over = false;

	static bool IsStepInit = false;

	static QString step1 = "";
	static QString step2 = "";
	static QString step3 = "";
	static QString step4 = "";
	static int i = 0;
	if (isG86) {

		if (!IsStepInit) {
			if (mcc->IniPnowFlg() != 0)return;
			double curZ = mcc->GetWorkpieceCoordinate(2);

			if (mDrillHoleData.isNeedStep1 == 0) {
				DoStep1Over = true;
				step1 = "";
			}
			else if (mDrillHoleData.isNeedStep1 == 1) {
				step1 = "G00X" + mDrillHoleData.X;
			}
			else if (mDrillHoleData.isNeedStep1 == 2) {
				step1 = "G00Y" + mDrillHoleData.Y;
			}
			else if (mDrillHoleData.isNeedStep1 == 3) {
				step1 = "G00X" + mDrillHoleData.X + "Y" + mDrillHoleData.Y;
			}

			step2 = "G00Z" + mDrillHoleData.R;
			step3 = "G01Z" + mDrillHoleData.Z + "F" + mDrillHoleData.F;
			if (mDrillHoleData.isG99)
				step4 = step2;
			else
				step4 = "G00Z" + QString::number(curZ);
			IsStepInit = true;
			RunOver = false;
		}


		i++;
		if (i < 10)
			return;

		if (!DoStep1Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step1);
			DoStep1Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step1:" + step1);
			return;
		}

		if (DoStep1Over && !DoStep2Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step2);
			DoStep2Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step2:" + step2);
			return;
		}

		if (DoStep1Over && DoStep2Over && !DoStep3Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step3);
			DoStep3Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step3:" + step3);
			return;
		}

		if (DoStep1Over && DoStep2Over &&DoStep3Over && !DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			w->stopSpindleRotate = mcc->GetSpindleInformation(0)*mcc->GetSpindleInformation(1);
			mcc->SetSpindleRotate(0);
			MccTools::SendMDI(step4);
			DoStep4Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step4:"+ step4);
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			IsStepInit = false;
			DoStep1Over = false;
			DoStep2Over = false;
			DoStep3Over = false;
			DoStep4Over = false;
			i = 0;
			isG86 = false;

			mcc->SendAutoText(QString(""));
			int startline = w->mCurRow + 1;
			mcc->SetStartline(startline);
			mcc->ClearBuffer();
			mcc->SetAutoRunFlag(true);
			RunOver = true;
			//LogManager::getIns()->appendLog("over");
			SammonFunc::CheckFeedrate();
		}

	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow;
			RunOver = true;
		}
		IsStepInit = false;
		DoStep1Over = false;
		DoStep2Over = false;
		DoStep3Over = false;
		DoStep4Over = false;
		i = 0;
	}
}
void TrGCode::DoDrillHoleCodeG89() {
	static bool RunOver = true;
	static bool DoStep1Over = false;
	static bool DoStep2Over = false;
	static bool DoStep3Over = false;
	static bool DoStep4Over = false;
	static bool DoStep5Over = false;
	static bool IsStepInit = false;

	static QString step1 = "";
	static QString step2 = "";
	static QString step3 = "";
	static QString step4 = "";
	static QString step5 = "";
	static int i = 0;
	if (isG89) {

		if (!IsStepInit) {
			if (mcc->IniPnowFlg() != 0)return;
			double curZ = mcc->GetWorkpieceCoordinate(2);

			if (mDrillHoleData.isNeedStep1 == 0) {
				DoStep1Over = true;
				step1 = "";
			}
			else if (mDrillHoleData.isNeedStep1 == 1) {
				step1 = "G00X" + mDrillHoleData.X;
			}
			else if (mDrillHoleData.isNeedStep1 == 2) {
				step1 = "G00Y" + mDrillHoleData.Y;
			}
			else if (mDrillHoleData.isNeedStep1 == 3) {
				step1 = "G00X" + mDrillHoleData.X + "Y" + mDrillHoleData.Y;
			}

			step2 = "G00Z" + mDrillHoleData.R;
			step3 = "G01Z" + mDrillHoleData.Z + "F" + mDrillHoleData.F;
			float fp = mDrillHoleData.P.toDouble();
			step4 = "G04P" + QString::number(fp);//mcc 里面延时一部分时间 。本地延时500毫秒 防止G04 后执行mcc 错误
			if (mDrillHoleData.isG99)
				step5 = "G01Z" + mDrillHoleData.R + "F" + mDrillHoleData.F;
			else
				step5 = "G01Z" + QString::number(curZ) + "F" + mDrillHoleData.F;

			IsStepInit = true;
			RunOver = false;
		}


		i++;
		if (i < 10)
			return;

		if (!DoStep1Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step1);
			DoStep1Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step1:" + step1);
			return;
		}

		if (DoStep1Over && !DoStep2Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step2);
			DoStep2Over = true;
			i = 0;
			//	LogManager::getIns()->appendLog("step2:" + step2);
			return;
		}

		if (DoStep1Over && DoStep2Over && !DoStep3Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step3);
			DoStep3Over = true;
			i = 0;
			//LogManager::getIns()->appendLog("step3:" + step3);
			return;
		}

		if (DoStep1Over && DoStep2Over &&DoStep3Over && !DoStep4Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step4);
			DoStep4Over = true;
			i = -mDrillHoleData.P.toDouble() / 50;
			//	LogManager::getIns()->appendLog("step4:"+ step4);
			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over && !DoStep5Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			MccTools::SendMDI(step5);
			DoStep5Over = true;
			i = 0;

			return;
		}
		if (DoStep1Over && DoStep2Over &&DoStep3Over && DoStep4Over&& DoStep5Over&&mcc->GetGmode(11).toInt() == 4 && mcc->IniPnowFlg() == 0) {
			IsStepInit = false;
			DoStep1Over = false;
			DoStep2Over = false;
			DoStep3Over = false;
			DoStep4Over = false;
			DoStep5Over = false;
			i = 0;
			isG89 = false;

			mcc->SendAutoText(QString(""));
			int startline = w->mCurRow + 1;
			mcc->SetStartline(startline);
			mcc->ClearBuffer();
			mcc->SetAutoRunFlag(true);
			RunOver = true;
			//LogManager::getIns()->appendLog("over");
			SammonFunc::CheckFeedrate();
		}

	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow;
			RunOver = true;
		}
		IsStepInit = false;
		DoStep1Over = false;
		DoStep2Over = false;
		DoStep3Over = false;
		DoStep4Over = false;
		DoStep5Over = false;
		i = 0;
	}
}

void TrGCode::DoG31()
{
	static bool DoStep1Over = false;
	static int i = 0;
	static bool RunOver = true;
	static bool sendMDI = false;
	if (isG31 != -1) {
		if (!sendMDI) {
			mcc->SendMDItext(QString("M11"));
			sendMDI = true;
		
			return;
		}
		if (DoStep1Over)
			mcc->SetIniPnowFlg(2);
		if (i++ <= 3) 	return;
		i = 0;
		if (mcc->IniPnowFlg() == 0 && mcc->GetGmode(11).toInt() == 4 && !DoStep1Over) {
			double mc = mcc->GetParameterValue(110 + isG31) / mcc->GetParameterValue(120 + isG31);
			mcc->SetIniPnowFlg(2);
			double mcood = mcc->GetMachineCoordinate(isG31);
			double wcood = mcc->GetWorkpieceCoordinate(isG31);
			double MCoord = mcood - wcood + G31Coord.toDouble();
			double Zzuididian = MCoord*mc;
			double returnLength = 0;
			bool hasF = false;
			double fspeed = G31FSpeed.toDouble(&hasF);
			if (hasF)
				NcPod::getIns()->Set_MoveSpee(0, isG31, fspeed*mc / 60.0);
			else
				NcPod::getIns()->Set_MoveSpee(0, isG31, 500 * mc / 60.0);
			NcPod::getIns()->setHomeTyp(0, 2);//二次回原点
			

			NcPod::getIns()->SignalMov(0, isG31, 4, Zzuididian, returnLength*mc, 0);
			w->homeLmtFlag = isG31;
			DoStep1Over = true;
			RunOver = false;
			i = 0; 
			LogManager::getIns()->debugLog(QString("Zzuididian:1%").arg(Zzuididian));
			LogManager::getIns()->debugLog(QString("lenth:1%").arg(returnLength));
			return;
		}

		if (mcc->GetGmode(11).toInt() == 4 && DoStep1Over) {
			//LogManager::getIns()->appendLog("*****************finish");
			RunOver = true;
			mcc->SetIniPnowFlg(0);
			if (SammonFunc::Getins()->readBit(SammonFunc::Getins()->needRunNext, 0)) {
				mcc->SendAutoText(QString(""));
				int startline = w->mCurRow + 1;
				mcc->SetStartline(startline);
				mcc->ClearBuffer();
				mcc->SetAutoRunFlag(true);
				SammonFunc::Getins()->writeBit(SammonFunc::Getins()->needRunNext, 0, 0);
			}
			isG31 = -1;
			i = 0;
		}
	}
	else {
		if (RunOver == false) {
			SammonFunc::RunShow = false;
			SammonFunc::PauseShow = false;
			SammonFunc::NextShow = true;
			SammonFunc::StartLine = w->mCurRow + 1;
			RunOver = true;
		}
		DoStep1Over = false;
		sendMDI = false;
		i = 0;
	}
}