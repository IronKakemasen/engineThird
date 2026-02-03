#include "DeathParticle.h"
#include "../../M/lowerLayer/GameObjectManager/GameObjectManager.h"

DeathParticleObject::DeathParticleObject()
{
	for (int i = 0; i < kMax; ++i)
	{
		auto& t = triangles.emplace_back(std::make_unique<Trianglele>());
		t->pulseDir = { float(rand() % 200 - 100) *0.01f , float(rand() % 200 - 100) * 0.01f,
		float(rand() % 200 - 100) * 0.01f };

		float sizeX = 0.2f + float(rand() % 100) * 0.01f;
		float sizeY = 0.2f + float(rand() % 100) * 0.01f;

		t->mTriangle.Initialize(sizeX, sizeY, {},
			M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2));
	}

}

void DeathParticleObject::Update()
{
	static float const gravityScale = -9.8f;

	for (auto& t : triangles)
	{
		if (!t->isActive) continue;

		t->mTriangle.appearance.trans.pos =
			t->mTriangle.appearance.trans.pos + t->velocity;

		t->mTriangle.appearance.trans.rotation =
			t->mTriangle.appearance.trans.rotation + t->velocity;

		t->velocity.y += gravityScale;

		t->mTriangle.appearance.color.w -= 0.1f;

		if (Benri::Min(t->mTriangle.appearance.color.w, 0.0f))
		{
			t->isActive = false;
		}
	}

}

//初期化処理
void DeathParticleObject::Init()
{

}

//描画処理.StateがinActiveの場合は呼び出されない
void DeathParticleObject::Draw(Matrix4* vpMat_)
{
	for (auto& t : triangles)
	{
		if (!t->isActive) continue;

		t->mTriangle.Draw(vpMat_);
	}

}

DeathParticle* DeathParticle::Get()
{
	static DeathParticle deathParticle;

	return &deathParticle;
}

void DeathParticle::Activate(Vector3 world_, int num_, float power_,float scale_, Vector3 color_)
{
	int no = 0;

	for (auto& t : deathParticleObject.triangles)
	{
		if (t->isActive) return;

		t->isActive = true;

		t->mTriangle.appearance.trans.pos = world_;
		t->mTriangle.appearance.trans.scale = 
			t->mTriangle.appearance.trans.scale * scale_;
		t->mTriangle.appearance.color = { color_.x,color_.y,color_.z,255 };
		t->velocity = t->pulseDir * power_;
		
		if (no >= num_)
		{
			break;
		}
		no++;
	}


}

void DeathParticle::Init(GameObjectManager* gameObjectManager_)
{
	//gameObjectManager_->RegisterForContainer(&deathParticleObject);
}

void DeathParticle::Update()
{
	deathParticleObject.Update();
}

void DeathParticle::Draw(Matrix4* vpMat_)
{
	deathParticleObject.Draw(vpMat_);
}
