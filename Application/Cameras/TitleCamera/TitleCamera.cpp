#include "TitleCamera.h"
#include "../../M/lowerLayer/Camera/CameraBehavior.h"
#include "../../Scenes/TitleScene/TitleScene.h"

void TitleCamera::Init(CameraPara* CameraPara_)
{
	cameraPara = CameraPara_;
}

void TitleCamera::Update()
{
	cameraPara->trans.interpolationCoe = 0.005f;

	auto c = TitleScene::c.count;

	if (c <= 0.2f)
	{
		float t = Counter::GetNormalizedCount(0.0f, 0.2f, c);

		cameraPara->trans.lookDir = fstLookDir;
		cameraPara->trans.pos = Easing::EaseOutCubic({0,0,-10.0f}, fstPos, t);
	}
	else if (c > 0.2f&& c <= 0.4f)
	{
		float t = Counter::GetNormalizedCount(0.2f, 0.4f, c);
		cameraPara->trans.lookDir = secLookDir;
		cameraPara->trans.pos = Easing::EaseOutExpo(fstPos, secPos, t);

	}

	if(c > 0.3f && c <= 0.85f)
	{
		float t = Counter::GetNormalizedCount(0.3f, 0.85f, c);

		Vector3 const moveOutDir = cameraPara->trans.lookDir * -1.0f;
		float const distance = 100.0f;
		static Vector3 const dstPos = moveOutDir * distance;
		cameraPara->trans.pos = Easing::EaseInExpo(secPos, thirdPos, t);
	}

	else if (c > 0.85f && c <= 0.95f)
	{
		cameraPara->trans.interpolationCoe = 0.0075f;

		float t = Counter::GetNormalizedCount(0.85f, 1.0f, c);

		Vector3 const moveOutDir = cameraPara->trans.lookDir * -1.0f;
		float const speed = 3.0f;
		cameraPara->trans.pos = cameraPara->trans.pos + moveOutDir * speed;
		cameraPara->trans.lookDir = { 0,1,-2 };
	}
}


void TitleCamera::Reset()
{

}
