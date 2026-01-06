#include "InGameCamera.h"
#include "./GameObject/InGameController.h"
#include "../M/lowerLayer/Camera/CameraBehavior.h"
#include "./GameObject/BlockManager.h"

void InGameCamera::Enter()
{
	float stZ = BlockManager::kStartPos.z + 
		BlockManager::waveData[InGameController::cur_wave].startSize.y + 1.0f;
	Vector3  stPos = { 104.6f,102.0f,stZ };
	float t = InGameController::cur_cnt;

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
	else
	{
		cameraPara->trans.pos.y = stPos.y;
		cameraPara->trans.pos.x = stPos.x;
	}

	if (t >= 0.485f)
	{
		cameraPara->trans.interpolationCoe = 0.001f + 0.01f * t * t;
		cameraPara->trans.lookDir = lastDir;
	}
	else
	{
		cameraPara->trans.interpolationCoe = 1.0f;
		cameraPara->trans.lookDir = fstLook;
	}
}

void InGameCamera::WhenPerfect()
{

}

void InGameCamera::Playable()
{
	if (BlockManager::addCnt.count <= 0.0f || BlockManager::addCnt.count >= 0.95f)
	{
		cameraPara->trans.interpolationCoe = 0.02f;

		Vector3 const folowPos = *playerPos + adjustPos;
		float const centerX = BlockManager::waveData[InGameController::cur_wave].startSize.x *
			0.5f - BlockManager::kBlockSize * 0.5f + 100.0f;

		float const playerDeltaPosX = playerPos->x - centerX;
		float rate = 0.0f;
		if (playerDeltaPosX != 0.0f)
		{
			float const max = 4.25f;
			rate = -playerDeltaPosX / max;
		}

		Vector3 sayuu = Vector3{ 2,0,0 } *rate;
		Vector3 const lookDir = ((*playerPos + adjustDir + sayuu) -
			cameraPara->trans.pos).GetNormalized();

		cameraPara->trans.lookDir = lookDir;
		cameraPara->trans.pos = folowPos;
	}
	else if (BlockManager::addCnt.count > 0.0f && BlockManager::addCnt.count < 0.85f)
	{
		cameraPara->trans.interpolationCoe = 1.0f;

		cameraPara->trans.pos = BlockManager::kStartPos +
			Vector3{ 5.0f, 3.0f ,(BlockManager::mapLast + 1.0f) * BlockManager::kBlockSize };
		cameraPara->trans.lookDir = { -0.416f,-0.526f,-0.742f };


	}
	else if (BlockManager::addCnt.count >= 0.85f&& BlockManager::addCnt.count < 0.95f)
	{
		cameraPara->trans.interpolationCoe = 1.0f;

		Vector3 const folowPos = *playerPos + adjustPos;
		float const centerX = BlockManager::waveData[InGameController::cur_wave].startSize.x *
			0.5f - BlockManager::kBlockSize * 0.5f + 100.0f;

		float const playerDeltaPosX = playerPos->x - centerX;
		float rate = 0.0f;
		if (playerDeltaPosX != 0.0f)
		{
			float const max = 4.25f;
			rate = -playerDeltaPosX / max;
		}

		Vector3 sayuu = Vector3{ 2,0,0 } *rate;
		Vector3 const lookDir = ((*playerPos + adjustDir + sayuu) -
			cameraPara->trans.pos).GetNormalized();

		cameraPara->trans.lookDir = lookDir;
		cameraPara->trans.pos = folowPos;
	}
}


void InGameCamera::Init(CameraPara* cameraPara_, Vector3* playerPos_)
{
	cameraPara = cameraPara_;
	playerPos = playerPos_;
	cameraPara->trans.lookDir = fstLook;
	cameraPara->trans.RotateUpdate();
	cameraPara->trans.interpolationCoe = 0.1f;
	perfectCnt.Initialize(2.0f);
}

void InGameCamera::Reset()
{
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