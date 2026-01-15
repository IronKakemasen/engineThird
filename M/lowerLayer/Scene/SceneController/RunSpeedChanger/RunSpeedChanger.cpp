#include "RunSpeedChanger.h"
#include "../../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include "../../../../../external/imgui/imgui.h"

#include <climits> 

#ifdef USE_IMGUI
void RunSpeedChanger::ForDebug::GuiAdd_ChangeRunSpeed(int* runSpeed_)
{
	if (ImGui::Checkbox(" Stop", &stopButton))
	{
		*runSpeed_ = (int)RunSpeed::kStop;
		onlyOnce = true;
	}
	else
	{
		ImGui::SliderInt("RunSpeed : ", runSpeed_, (int)RunSpeed::kStop, (int)RunSpeed::kStandared);
		if (onlyOnce)
		{
			runSpeedBuffer = *runSpeed_;
			onlyOnce = false;
		}
	}

}
#endif // USE_


void RunSpeedChanger::AddDebug()
{
	forDebug.GuiAdd_ChangeRunSpeed(&runSpeed);
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


