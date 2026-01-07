#include "RedMark.h"
#include "BlockManager.h"
#include "../../M/lowerLayer/engineCore/Light/PointLight/PointLight.h"
#include "GreenBlock.h"

void RedMark::Update()
{
	model->Update();
	auto* apperance = model->model->Getter_Appearance(0);

	switch (mode)
	{
	case RedMark::kExist:
		SwitchCollisionActivation(false);
		apperance->color = { 0,169,104 ,20};

		p->Getter_Para()->isActive = true;
		p->Getter_Para()->pos = trans.GetWorldPos();
		p->Getter_Para()->pos.y += 1.5f;
		p->Getter_Para()->color = { 0, 85,54};

		break;

	case RedMark::kNotExist:
		p->Getter_Para()->isActive = false;

		SetStatus(Status::kInActive);
		SwitchCollisionActivation(false);

		break;

	case RedMark::kActivated:

		p->Getter_Para()->isActive = true;
		p->Getter_Para()->pos = trans.GetWorldPos();
		p->Getter_Para()->pos.y += 1.5f;
		p->Getter_Para()->color = { 100,20,20 };

		SwitchCollisionActivation(true);
		markingCnt.Add();
		if (markingCnt.IsEnd())
		{
			mode = kNotExist;
		}

		apperance->color = { 200,50,50,100 };

		break;
	}

}

void RedMark::Init()
{
	SetIdentity(Tag::kGreenArea);
	model->Init();
	markingCnt.Initialize(0.25f);
	toBlock.Init(this);
}

void RedMark::ToBlock::Init(RedMark* p_)
{
	p = p_;
}

void RedMark::Reset()
{
	model->Reset();
}

void RedMark::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

RedMark::RedMark()
{
	SetRectCollision(BlockManager::kBlockSize * 2.25f, BlockManager::kBlockSize* 2.25f);
	model.reset(new KiiroModel);
	model->MakeAllPartsBeChildren(&trans);
	SetStatus(Status::kInActive);
	p = M::GetInstance()->ImportPointLight();
	p->Getter_Para()->invSqrRadius = 1000;
	p->Getter_Para()->intensity = 50;

}


void RedMark::SetCollisionBackTable()
{
	collisionBackActivationMap[Tag::kNormal] = { false, toBlock };
	collisionBackActivationMap[Tag::kGreen] = { false, toBlock };
	collisionBackActivationMap[Tag::kBlack] = { false, toBlock };

}

bool RedMark::ToBlock::operator()()
{
	if (p->markingCnt.count > 0.0f && p->markingCnt.count <= 0.75f)
	{
		for (auto* it : p->colObj)
		{
			if (it->uwa != Uwa::kUsing) continue;

			if (it->Getter_Identity()->tag == kNormal )
			{
				it->uwa = Uwa::kErase;
			}
			else if (it->Getter_Identity()->tag == kGreen)
			{
				it->uwa = Uwa::kErase;
				auto* a = reinterpret_cast<GreenBlock*>(it);
				a->redMark->mode = RedMark::kExist;
				a->redMark->Getter_Trans()->pos = a->Getter_Trans()->pos;
				a->redMark->Getter_Trans()->pos.x = floor(a->Getter_Trans()->pos.x) + 0.5f;
				a->redMark->Getter_Trans()->pos.z = floor(a->Getter_Trans()->pos.z) + 0.5f;

				a->redMark->Getter_Trans()->pos.y -= 0.5f;
				a->redMark->SetStatus(Status::kActive);
				a->light->Getter_Para()->isActive = false;
			}
			else if (it->Getter_Identity()->tag == kBlack)
			{
				BlockManager::doVanishRow++;
				it->uwa = Uwa::kErase;

			}
			else if (p->markingCnt.count > 0.75f)
			{
				return false;
			}

		}
	}

	return true;
}