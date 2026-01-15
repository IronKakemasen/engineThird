#include "RunSpeedChanger.h"
#include "../../../../utilities/benriTemplateFunc/benriTempFunc.h"
#include "../../../../../external/imgui/imgui.h"
#include <climits> 

#ifdef USE_IMGUI
void RunSpeedChanger::ForDebug::GuiAdd_ChangeRunSpeed(int* runSpeed_)
{
	ImGui::Checkbox(" Stop", &stopButton);

	if (stopButton)
	{
		*runSpeed_ = (int)RunSpeed::kStop;
		onlyOnce = true;
		ImGui::Text("STOPTYUU");
	}
	else
	{
		if (onlyOnce)
		{
			*runSpeed_ = runSpeedBuffer;
			onlyOnce = false;
			return;
		}
		runSpeedBuffer = *runSpeed_;
		ImGui::SliderInt("RunSpeed : ", runSpeed_, (int)RunSpeed::kStop, (int)RunSpeed::kStandared);
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


