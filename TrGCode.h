#pragma once
#include "datadefine.h"
class TrGCode
{
public:
	TrGCode();
	~TrGCode();
	void DoDrillHoleCodeG81();
	void DoDrillHoleCodeG82();
	void DoDrillHoleCodeG73();
	void DoDrillHoleCodeG85();
	void DoDrillHoleCodeG86();
	void DoDrillHoleCodeG89();
	void DoG31();


	bool isG81 = false;
	bool isG82 = false;
	bool isG73 = false;
	bool isG85 = false;
	bool isG86 = false;
	bool isG89 = false;
	DrillHoleData   mDrillHoleData;
	int isG31 = -1;
	QString G31Coord = "";
	QString G31FSpeed = "";
};

