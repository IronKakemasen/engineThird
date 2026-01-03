#include "Player.h"
#include "InGameController.h"
#include "BlockManager.h"
#include "imgui.h"

void Player::Update()
{
	model->Update();

	switch (InGameController::mode)
	{
	case InGameController::kEnter:

		break;

	case InGameController::kPlayable:

		Move();
		ClipPosition();

		break;

	case InGameController::kDeath:

		break;

	case InGameController::kClear:

		break;

	case InGameController::kResult:

		break;

	}

}

void Player::Init()
{
	SetIdentity(kPlayer);
	model->Init();

	float const blockSize = BlockManager::kBlockSize;
	float const centerXOffset =
		BlockManager::waveData[InGameController::cur_wave].startSize.x * 0.5f - blockSize * 0.5f;
	float const zStartRate = 0.2f;
	float const zOffset = 
		BlockManager::waveData[InGameController::cur_wave].startSize.y * zStartRate;
 
	trans.pos = BlockManager::kStartPos + 
		Vector3{ centerXOffset,0.56f ,zOffset };

	trans.rotation.y = 90.0f;
	angleCnt.Initialize(5.0f);

}

void Player::Reset()
{
	model->Reset();
	angleCnt.count = 0.0f;
	nextAngleY = 0.0f;
	trans.rotation.y = 90.0f;

}

void Player::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

Player::Player()
{
	model.reset(new PlayerModel);
	model->MakeAllPartsBeChildren(&trans);
}

void Player::ClipPosition()
{
	float const blockSize = BlockManager::kBlockSize;
	float const halfOfPlayerSize = playerSize * 0.5f;
	float const clipMin_X = BlockManager::kStartPos.x - playerSize * 2.0f;
	float const clipMax_X = BlockManager::kStartPos.x +
		BlockManager::waveData[InGameController::cur_wave].startSize.x - blockSize +
		playerSize * 2.0f;
	float adjust = 0.01f;

	Benri::AdjustMax(trans.pos.x, clipMax_X, clipMax_X - adjust);
	Benri::AdjustMin(trans.pos.x, clipMin_X, clipMin_X + adjust);

	float const clipMaxZ = BlockManager::kStartPos.z + 
		BlockManager::waveData[InGameController::cur_wave].startSize.y -playerSize;
	float const clipMinZ = BlockManager::kStartPos.z +
		BlockManager::mapLast - playerSize;

	Benri::AdjustMax(trans.pos.z, clipMaxZ, clipMaxZ - adjust);
	Benri::AdjustMin(trans.pos.z, clipMinZ, clipMinZ + adjust);

}

void Player::Move()
{
	auto* m = M::GetInstance();

	float const deltaTime = m->GetDeltaTime();
	bool pushed = 0;

	if (m->IsKeyPressed(KeyType::LEFT))
	{
		nextAngleY = 180.0f;
		pushed = 1;
		if (m->IsKeyPressed(KeyType::UP))
		{
			nextAngleY = 135.0f;
		}
		else if (m->IsKeyPressed(KeyType::DOWN))
		{
			nextAngleY = 225.0f;
		}
	}
	else if (m->IsKeyPressed(KeyType::RIGHT))
	{
		pushed = 1;
		nextAngleY = 0.0f;
		if (m->IsKeyPressed(KeyType::UP))
		{
			nextAngleY = 45.0f;
		}
		else if (m->IsKeyPressed(KeyType::DOWN))
		{
			nextAngleY = 315.0f;
		}
	}

	else if (m->IsKeyPressed(KeyType::UP))
	{
		nextAngleY = 90.0f;
		pushed = 1;

	}
	else if (m->IsKeyPressed(KeyType::DOWN))
	{
		nextAngleY = 270.0f;
		pushed = 1;

	}

	if (pushed && angleCnt.count>0.0f)
	{
		if (preAngleY != nextAngleY)
		{
			angleCnt.count = 0.0f;
		}
	}

	if ((int)trans.rotation.y != (int)nextAngleY)
	{
		angleCnt.Add(deltaTime);
		angleCnt.IsEnd();
		trans.rotation.y =
			Easing::EaseOutSine(trans.rotation.y, -nextAngleY, angleCnt.count);
	}
	else
	{
		angleCnt.count = 0.0f;
	}



	ImGui::Begin("ooijpp");
	ImGui::DragFloat("cnt", &angleCnt.count);
	ImGui::DragFloat("rotation", &trans.rotation.y);
	ImGui::DragFloat("nextAngleY", &nextAngleY);
	
	ImGui::End();


	
	float rad = GetRadian(nextAngleY);
	Vector3 moveDir = { cosf(rad),0.0f,sinf(rad) };

	trans.pos = trans.pos + moveDir * moveSpeed * pushed * deltaTime;

	preAngleY = nextAngleY;
}