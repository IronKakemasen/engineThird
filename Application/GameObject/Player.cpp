#include "Player.h"
#include "InGameController.h"
#include "BlockManager.h"
//#include "imgui.h"
#include "BlueMark.h"
#include "RedMark.h"


bool Player::IsDeath()
{
	float const clipMaxZ = BlockManager::kStartPos.z +
		BlockManager::waveData[InGameController::cur_wave].startSize.y - 1.0f * 0.5f - playerSize;
	float const clipMinZ = BlockManager::kStartPos.z +
		(BlockManager::mapLast - 1.0f * 0.5f) + playerSize * 0.5f;

	if (trans.pos.z < clipMinZ-0.2f)
	{
		return true;
	}

	return false;
}

void Player::Update()
{
	model->Update();

	switch (InGameController::mode)
	{
	case InGameController::kEnter:
		SetStart();
		break;

	case InGameController::kPlayable:

		SwitchCollisionActivation(true);
		if (IsDeath())
		{
			InGameController::mode = InGameController::Mode::kDeath;
			return;
		}

		Move();
		ClipPosition();
		Mark();
		ActivateAllMidori();

		break;

	case InGameController::kDeath:
		trans.pos.y -= 10.0f * 0.01666666f;


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
	SetRectCollision(playerSize, playerSize);
	toBlock.Init(this);
}

void Player::ActivateAllMidori()
{
	if (M::GetInstance()->IsKeyTriggered(KeyType::X))
	{
		for (auto* it : redMarks)
		{
			if (it->mode != RedMark::kExist) continue;
			it->mode = RedMark::kActivated;
		}
	}
}

void Player::Mark()
{
	if (M::GetInstance()->IsKeyTriggered(KeyType::Z))
	{
		if (blueMark->mode == BlueMark::kNotExist)
		{
			PutMark();
		}
		else if (blueMark->mode == BlueMark::kExist)
		{
			ActivateMark();
		}
	}

}

void Player::PutMark()
{
	auto* pos = &blueMark->Getter_Trans()->pos;
	*pos = trans.pos;
	pos->x = floor(pos->x) + 0.5f;
	pos->z = floor(pos->z) + 0.5f;

	pos->y -= 0.1f;
	blueMark->mode = BlueMark::Mode::kExist;
	blueMark->SetStatus(Status::kActive);
}

void Player::ActivateMark()
{
	blueMark->mode = BlueMark::Mode::kActivated;
	blueMark->markingCnt.count = 0.0f;
}


void Player::SetStart()
{
	float const blockSize = BlockManager::kBlockSize;
	float const centerXOffset =
		BlockManager::waveData[InGameController::cur_wave].startSize.x * 0.5f - blockSize * 0.5f;
	float const zStartRate = 0.3f;
	float const zOffset =
		BlockManager::waveData[InGameController::cur_wave].startSize.y * zStartRate;

	trans.pos = BlockManager::kStartPos +
		Vector3{ centerXOffset,0.6f ,zOffset };

	trans.rotation.y = 90.0f;
	angleCnt.Initialize(5.0f);

	for (auto* i : redMarks)
	{
		i->mode = RedMark::kNotExist;
		i->markingCnt.count = 0.0f;
	}

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
	SetRectCollision(BlockManager::kBlockSize, BlockManager::kBlockSize);

}

void Player::ToBlock::Init(Player* p_)
{
	p = p_;
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
		BlockManager::waveData[InGameController::cur_wave].startSize.y - blockSize * 0.5f - playerSize;
	float const clipMinZ = BlockManager::kStartPos.z +
		(BlockManager::mapLast - blockSize * 0.5f) + playerSize * 0.5f;

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



	//ImGui::Begin("ooijpp");
	//ImGui::DragFloat("cnt", &angleCnt.count);
	//ImGui::DragFloat("rotation", &trans.rotation.y);
	//ImGui::DragFloat("nextAngleY", &nextAngleY);
	//
	//ImGui::End();


	
	float rad = GetRadian(nextAngleY);
	Vector3 moveDir = { cosf(rad),0.0f,sinf(rad) };

	trans.pos = trans.pos + moveDir * moveSpeed * pushed * deltaTime;

	preAngleY = nextAngleY;
}

void Player::SetCollisionBackTable()
{
	collisionBackActivationMap[Tag::kNormal] = { false, toBlock };
	collisionBackActivationMap[Tag::kGreen] = { false, toBlock };
	collisionBackActivationMap[Tag::kBlack] = { false, toBlock };

}

bool Player::ToBlock::operator()()
{
	for (auto* it : p->colObj)
	{
		Vector3 push = GetCollisionPushback(*p->Getter_Rect(),
			*it->Getter_Rect(),
			p->Getter_Trans()->GetWorldPos(), it->Getter_Trans()->GetWorldPos());

		p->Getter_Trans()->pos.x += push.x;
		p->Getter_Trans()->pos.z += push.z;
	}


	return true;
}

Vector3 GetCollisionPushback(const Rect& dynamicRect, const Rect& staticRect,
	Vector3 c1_,Vector3 c2_)
{
	// 初期化
	Vector3 pushVector;

	// 1. 各矩形の中心間の距離を計算
	Vector3 dif = c1_ - c2_;
	float dx = dif.x;
	float dy = dif.z;

	// 2. 矩形の幅・高さの合計（半分）を計算
	float combinedHalfWidth = ((dynamicRect.right - dynamicRect.left) +
		(staticRect.right - staticRect.left)) * 0.5f;

	float combinedHalfHeight = ((dynamicRect.top - dynamicRect.bottom) +
		(staticRect.top - staticRect.bottom)) * 0.5f;

	// 重なり量（貫通深度）を算出
	float overlapX = combinedHalfWidth - std::abs(dx);
	float overlapY = combinedHalfHeight - std::abs(dy);

	// 4. 重なりが浅い方の軸を選んで押し戻しベクトルを設定
	// (浅い方に押し出すのが最も自然に見えるため)
	if (overlapX < overlapY) {
		// X軸方向に押し戻す
		// dx > 0 なら dynamicRect は右側にいるので、右(+x)に押し出す
		pushVector.x = (dx > 0) ? overlapX : -overlapX;
		pushVector.z = 0.0f;
	}
	else {
		// Y軸方向に押し戻す
		// dy > 0 なら dynamicRect は下にいるので、下(+y)に押し出す
		pushVector.x = 0.0f;
		pushVector.z = (dy > 0) ? overlapY : -overlapY;
	}

	return pushVector; 
}
