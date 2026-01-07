#include "BlackBlock.h"
#include "BlockManager.h"

void BlackBlock::Update()
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
				uwa = Uwa::kErase;
				status = Status::kInActive;
			}
		}
	}
	else if (uwa == Uwa::kErase)
	{
		float t = 4.5f * 0.016666666f ;
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
}

void BlackBlock::Init()
{
	SetIdentity(kBlack);
	model->Init();
}

void BlackBlock::Reset()
{
	model->Reset();

}

void BlackBlock::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

BlackBlock::BlackBlock()
{
	model.reset(new BlackModel);
	model->MakeAllPartsBeChildren(&trans);
	SetRectCollision(BlockManager::kBlockSize, BlockManager::kBlockSize);

}

void BlackBlock::SetCollisionBackTable()
{

}