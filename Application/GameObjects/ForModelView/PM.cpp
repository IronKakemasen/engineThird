#include "PM.h"
#include "../../M/lowerLayer/engineCore/Light/RectLight/RectLight.h"
#include "../../M/lowerLayer/engineCore/Light/PointLight/PointLight.h"


void PM::Update()
{
	auto* para = rectLight->Getter_Para();
	para->pos = trans.GetWorldPos();
	para->pos.y = 3.0f;
	auto* m = M::GetInstance();
	if (m->IsKeyPressed(KeyType::A))
	{
		trans.pos.x -= 0.25f;
	}
	if (m->IsKeyPressed(KeyType::W))
	{
		trans.pos.z += 0.25f;
	}
	if (m->IsKeyPressed(KeyType::D))
	{
		trans.pos.x += 0.25f;
	}
	if (m->IsKeyPressed(KeyType::S))
	{
		trans.pos.z -= 0.25f;
	}

}

void PM::Init()
{
	// モデルの初期化
	model->Init(&trans);

}

void PM::Reset()
{

}
void PM::Draw(Matrix4* vpMat_)
{
	model->Draw(vpMat_);
	auto* para = rectLight->Getter_Para();

	M::GetInstance()->DrawEllipseWireFrame(para->pos, 0.5f, { 90,0,0 },
		{ 255,255,255,255 }, vpMat_);

}
void PM::SetCollisionBackTable()
{

}

PM::PM()
{
	model.reset(new PlayerModel);
	rectLight = M::GetInstance()->ImportRectLight();
	rectLight->Getter_Para()->isActive = 0;
	*rectLight->GetLookDirection() = { 0,-1,0.01f };
}
