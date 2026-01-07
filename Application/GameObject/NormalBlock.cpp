#include "NormalBlock.h"
#include "BlockManager.h"

void NormalBlock::Update()
{
	model->Update();
	if (uwa == Uwa::kUsing)
	{
		SwitchCollisionActivation(true);
		SetRectCollision(1, 1);

		if (BlockManager::IsFall(trans.pos.z))
		{
			trans.pos.y -= 6.0f * 0.0166666f;
			if (trans.pos.y <= 90.0f)
			{
				uwa = Uwa::kFall;
				BlockManager::numFall++;
				status = Status::kInActive;
			}
		}
	}
	else if (uwa == Uwa::kErase)
	{
		float t = 4.5f * 0.016666666f * 0.5f;
		trans.scale.x -= t;
		trans.scale.y -= t;
		trans.scale.z -= t;

		Benri::Min(trans.scale.x, 0.0f);
		Benri::Min(trans.scale.y, 0.0f);
		if (Benri::Min(trans.scale.z, 0.0f))
		{
			SetStatus(Status::kInActive);
		}
	}

	else
	{
		SwitchCollisionActivation(false);
	}

	if (rakka && forAddition)
	{
		trans.pos.y -= 6.0f * 0.0166666f;
		if (trans.pos.y <= 90.0f)
		{
			rakka = false;
			status = Status::kInActive;
		}

	}

}

void NormalBlock::Init()
{
	SetIdentity(kNormal);
	model->Init();

}

void NormalBlock::Reset()
{
	model->Reset();

}

void NormalBlock::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

NormalBlock::NormalBlock()
{
	model.reset(new NormalModel);
	model->MakeAllPartsBeChildren(&trans);
	SetRectCollision(BlockManager::kBlockSize, BlockManager::kBlockSize);

}


void NormalBlock::SetCollisionBackTable()
{

}
