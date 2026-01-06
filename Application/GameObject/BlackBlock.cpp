#include "BlackBlock.h"
#include "BlockManager.h"

void BlackBlock::Update()
{
	model->Update();

	if (uwa == Uwa::kUsing)
	{
		SwitchCollisionActivation(true);

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

}

void BlackBlock::SetCollisionBackTable()
{

}