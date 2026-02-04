#include "DamageDisplay.h"
#include "../../M.h"
#include "../../M/utilities/Easing/EasingFunctions.h"

DamageDisplay::DamageNum::DamageNum()
{
	isActive = false;
	onesPlace = 0;
	tensPlace = 0;
	cnt.Initialize(2.0f);

}

void DamageDisplay::DamageNum::Set(float num_, Vector3 world_, float scale_, Vector3 color_)
{
	onesPlace = (int)num_ % 10;
	tensPlace = (int)(num_ / 10);
	if (tensPlace != 0)
	{
		tensPlace %= 10;
	} 
	
	cnt.count = 0.0f;
	scale = scale_;

	world = world_;
	Vector2 conv = ConvertToScreen(world_, *vpMat);

	o.Initialize(defaultSize.x * scale_, defaultSize.y * scale_, { conv.x,conv.y,0.0f },
		M::GetInstance()->GetTexIndex(TextureTag::kNumbers1000x100), { color_.x, color_.y, color_.z, 255.0f });
	o.ToAtlas(10);
	o.ChangeAtlasIndex(float(onesPlace));

	if (tensPlace > 0)
	{
		t.Initialize(defaultSize.x * scale_, defaultSize.y * scale_, { conv.x + defaultSize.x * scale_ ,conv.y,0.0f },
			M::GetInstance()->GetTexIndex(TextureTag::kNumbers1000x100), { color_.x, color_.y, color_.z, 255.0f });
		t.ToAtlas(10);
		t.ChangeAtlasIndex(float(tensPlace));
	}

	isActive = true;
}

void DamageDisplay::DamageNum::Update()
{
	if (!isActive) return;
	float const kMoveHeight = -200.0f;

	moveOffset.y = Easing::EaseOutCubic(0.0f, kMoveHeight, cnt.count);
	Vector2 conv = ConvertToScreen(world, *vpMat);


	o.GetAppearance()->trans.pos = Vector3{ conv.x,conv.y,0.0f } + moveOffset;
	o.GetAppearance()->color.w = Easing::EaseInExpo(255.0f, 0.0f, cnt.count);
	o.Update();

	if (tensPlace > 0)
	{
		float const adjust = 0.65f;
		t.GetAppearance()->trans.pos = 
			Vector3{ conv.x - defaultSize.x * scale * adjust   ,conv.y,0.0f } + moveOffset;
		t.GetAppearance()->color.w = Easing::EaseInExpo(255.0f, 0.0f, cnt.count);
		t.Update();
	}


	cnt.Add();
	if (cnt.IsEnd())
	{
		isActive = false;
	}
}

void DamageDisplay::DamageNum::Draw(Matrix4* pMat_)
{
	if (!isActive) return;

	o.Draw(pMat_);
	if (tensPlace > 0)
	{
		t.Draw(pMat_);
	}
}

DamageDisplay::DamageDisplay()
{
	damageNumSprites.resize(kMaxGenerate);
}

DamageDisplay* DamageDisplay::Get()
{
	static DamageDisplay damageDisplay;
	return &damageDisplay;
}

void DamageDisplay::Activate(float num_, Vector3 world_, float scale_, Vector3 color_)
{
	for (auto& it : damageNumSprites)
	{
		if (it.isActive) continue;

		it.Set(num_, world_, scale_, color_);
		break;
	}
}

void DamageDisplay::Update()
{
	for (auto& it : damageNumSprites)
	{
		it.Update();
	}
}

void DamageDisplay::Draw(Matrix4* pMat_)
{
	
	for (auto& it : damageNumSprites)
	{
		if (!it.isActive) return;
		it.Draw(pMat_);
	}

}

void DamageDisplay::DamageNum::Init(Matrix4* vpMat_)
{
	vpMat = vpMat_;
}

void DamageDisplay::Init(Matrix4* vpMat_)
{
	for (auto& it : damageNumSprites)
	{
		it.Init(vpMat_);
	}

}

