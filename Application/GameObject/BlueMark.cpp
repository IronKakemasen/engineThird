#include "BlueMark.h"
#include "BlockManager.h"
#include "../../M/lowerLayer/engineCore/Light/PointLight/PointLight.h"
#include "GreenBlock.h"
#include "RedMark.h"

void BlueMark::ToBlock::Init(BlueMark* p_)
{
	p = p_;
}

void BlueMark::Update()
{
	model->Update();
	auto* apperance = model->model->Getter_Appearance(0);

	switch (mode)
	{
	case BlueMark::kExist:
		SwitchCollisionActivation(false);
		apperance->color = { 50,50,200,150 };

		p->Getter_Para()->isActive = true;
		p->Getter_Para()->pos = trans.GetWorldPos();
		p->Getter_Para()->pos.y += 1.75f;
		p->Getter_Para()->color = { 20,20,100};

		break;

	case BlueMark::kNotExist:
		p->Getter_Para()->isActive = false;

		SetStatus(Status::kInActive);
		SwitchCollisionActivation(false);

		break;

	case BlueMark::kActivated:

		p->Getter_Para()->isActive = true;
		p->Getter_Para()->pos = trans.GetWorldPos();
		p->Getter_Para()->pos.y += 1.75f;
		p->Getter_Para()->color = { 100,20,20};

		SwitchCollisionActivation(true);
		markingCnt.Add();
		if (markingCnt.IsEnd())
		{
			mode = kNotExist;
		}

		apperance->color = { 200,50,50,150 };

		break;
	}
}


void BlueMark::Init()
{
	SetIdentity(Tag::kBlueArea);
	model->Init();
	markingCnt.Initialize(markTime);
	p->Getter_Para()->intensity *= 0.5f;
}

void BlueMark::Reset()
{
	model->Reset();
}

void BlueMark::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
}

BlueMark::BlueMark()
{
	p = M::GetInstance()->ImportPointLight();
	SetRectCollision(BlockManager::kBlockSize * 0.2f, BlockManager::kBlockSize * 0.2f);
	model.reset(new PlaneModel);
	model->MakeAllPartsBeChildren(&trans);
	SetStatus(Status::kInActive);
	toBlock.Init(this);
}


void BlueMark::SetCollisionBackTable()
{
	collisionBackActivationMap[Tag::kNormal] = { false, toBlock };
	collisionBackActivationMap[Tag::kGreen] = { false, toBlock };
	collisionBackActivationMap[Tag::kBlack] = { false, toBlock };
}

bool BlueMark::ToBlock::operator()()
{
	if (p->markingCnt.count > 0.0f && p->markingCnt.count <= 1.0f)
	{
		for (auto* it : p->colObj)
		{
			if (it->Getter_Identity()->tag == kNormal)
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
				if (it->uwa != Uwa::kErase)
				{
					BlockManager::doVanishRow++;
				}
				it->uwa = Uwa::kErase;

			}
		}
	}

	return false;
}
