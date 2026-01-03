#include "InGameCamera.h"
#include "./GameObject/InGameController.h"
#include "../M/lowerLayer/Camera/CameraBehavior.h"
#include "./GameObject/BlockManager.h"

void InGameCamera::Enter()
{
	float t = InGameController::cur_cnt;
	cameraPara->trans.interpolationCoe = 0.001f +0.01f * t*t;

	Vector3 const lastDir = 
		(*playerPos + adjustDir - cameraPara->trans.pos).GetNormalized();
	Vector3 const lastPos = *playerPos + adjustPos;
	cameraPara->trans.pos.z =
		Easing::EaseOutSine(stPos.z, lastPos.z, t);

	if (t >= 0.5f)
	{
		float tt = Counter::GetNormalizedCount(0.5f, 1.0f, t);
		cameraPara->trans.pos.y =
			Easing::Lerp(stPos.y, lastPos.y, tt);
		cameraPara->trans.pos.x =
			Easing::Lerp(stPos.x, lastPos.x, tt);
	}

	if (t >= 0.475f)
	{
		cameraPara->trans.lookDir = lastDir;
	}
}

void InGameCamera::Playable()
{
	cameraPara->trans.interpolationCoe = 0.02f;

	Vector3 const folowPos = *playerPos + adjustPos;
	float const centerX = BlockManager::waveData[InGameController::cur_wave].startSize.x *
		0.5f - BlockManager::kBlockSize * 0.5f + 100.0f;

	float const playerDeltaPosX = playerPos->x - centerX;
	float rate = 0.0f;
	if (playerDeltaPosX != 0.0f)
	{
		float const max = 4.0f;
		rate = -playerDeltaPosX / max;
	}

	Vector3 sayuu = Vector3{ 2,0,0 } * rate;
	Vector3 const lookDir = ((*playerPos + adjustDir + sayuu) -
		cameraPara->trans.pos).GetNormalized();


	cameraPara->trans.lookDir = lookDir;
	cameraPara->trans.pos = folowPos;
}


void InGameCamera::Init(CameraPara* cameraPara_, Vector3* playerPos_)
{
	cameraPara = cameraPara_;
	playerPos = playerPos_;
	cameraPara->trans.pos = stPos;
	cameraPara->trans.lookDir = fstLook;
	cameraPara->trans.RotateUpdate();
	cameraPara->trans.interpolationCoe = 0.1f;

}

void InGameCamera::Reset()
{
	cameraPara->trans.pos = stPos;
	cameraPara->trans.lookDir = fstLook;
}

void InGameCamera::Update()
{
	switch (InGameController::mode)
	{
	case InGameController::kEnter:
		
		Enter();

		break;

	case InGameController::kPlayable:
		Playable();
		break;

	case InGameController::kDeath:

		break;

	case InGameController::kClear:

		break;

	case InGameController::kResult:

		break;

	}

}