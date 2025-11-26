#pragma once

class RunSpeedChanger
{
	enum RunSpeed
	{
		kStop = 1,
		kHalf = 5,
		kStandared = 10
	};

	int runSpeed;		//min = 1,default = 10 (1 = stop, )
	int framCnt;

public:
	RunSpeedChanger();
	void GuiAdd_ChangeRunSpeed();
	bool AdjustRunSpeed();
	void Reset();
};

