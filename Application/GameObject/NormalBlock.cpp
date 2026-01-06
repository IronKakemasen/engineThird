#include "NormalBlock.h"
#include "BlockManager.h"

void NormalBlock::Update()
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
				uwa = Uwa::kFall;
				BlockManager::numFall++;
				status = Status::kInActive;
			}
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

}


void NormalBlock::SetCollisionBackTable()
{

}
