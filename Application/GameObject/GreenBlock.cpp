#include "GreenBlock.h"
#include "../../M/lowerLayer/engineCore/Light/PointLight/PointLight.h"
#include "BlockManager.h"

void GreenBlock::Update()
{
	model->Update();
	if (uwa == Uwa::kUsing)
	{
		SwitchCollisionActivation(true);
		SetRectCollision(1, 1);

		light->Getter_Para()->isActive = true;
		light->Getter_Para()->pos = trans.GetWorldPos();
		light->Getter_Para()->pos.y -= 0.5f;

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
		light->Getter_Para()->isActive = false;

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

		light->Getter_Para()->isActive = false;
	}
}

void GreenBlock::Init()
{
	SetIdentity(kGreen);
	model->Init();
	auto* para = light->Getter_Para();
	para->color = { 0,169,104};
	para->intensity = 10;
	para->invSqrRadius = 250;

	SetRectCollision(BlockManager::kBlockSize, BlockManager::kBlockSize);
}

void GreenBlock::Reset()
{
	model->Reset();

}

void GreenBlock::Draw(Matrix4* vpMat_)
{

	model->Draw(vpMat_);

}

GreenBlock::GreenBlock()
{
	model.reset(new GreenModel);
	model->MakeAllPartsBeChildren(&trans);

}

void GreenBlock::SetCollisionBackTable()
{
	//collisionBackActivationMap[ObjectID::Tag::kGoal] = { false, collisionGoal };

}

