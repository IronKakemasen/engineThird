#include "RunSpeedChanger.h"
#include "../../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include "../../../../../external/imgui/imgui.h"

#include <climits> 

void RunSpeedChanger::GuiAdd_ChangeRunSpeed()
{
#ifdef USE_IMGUI

	ImGui::SliderInt("RunSpeed : ", &runSpeed, (int)RunSpeed::kStop, (int)RunSpeed::kStandared);

#endif // !USE_
}

RunSpeedChanger::RunSpeedChanger()
{
	Reset();
}

void RunSpeedChanger::Reset()
{
	runSpeed = 10;		//min = 1,default = 10 (1 = stop, )
	framCnt = 0;
}



bool RunSpeedChanger::AdjustRunSpeed()
{
	//簡易的だけども
	if (runSpeed != 10)
	{
		Benri::Min(runSpeed, (int)RunSpeed::kStop);

		framCnt++;
		Benri::AdjustMax(framCnt, INT_MAX, 0);

		if (framCnt % runSpeed == 0)
		{
			return false;
		}
	}

	return true;
}


