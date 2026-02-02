#include "DamageDisplay.h"
#include "../../M.h"

DamageDisplay::DamageNum::DamageNum()
{
	isActive = false;
	onesPlace = 0;
	tensPlace = 0;
	cnt.Initialize(1.5f);

}

void DamageDisplay::DamageNum::Set(float num_, Vector3 world_)
{
	onesPlace = (int)num_ % 10;
	tensPlace = (int)(num_ / 10) % 10;

	Vector2 conv = ConvertToScreen(world_);

	o.Initialize(100, 100, { conv.x - 100,conv.y,0.0f },
		M::GetInstance()->GetTexIndex(TextureTag::kNumbers1000x100));
	if (tensPlace > 0)
	{
		t.Initialize(100, 100, { conv.x,conv.y,0.0f },
			M::GetInstance()->GetTexIndex(TextureTag::kNumbers1000x100));
	}

	isActive = true;
}

void DamageDisplay::DamageNum::Update()
{
	if (!isActive) return;

}