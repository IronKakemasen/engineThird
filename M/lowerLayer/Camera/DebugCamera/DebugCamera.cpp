#include "DebugCamera.h"
#include "../../M.h"

DebugCamera::DebugCamera()
{
	para.trans.pos = { 0.0f,3.0f,-1.0f };
	para.trans.lookDir.y = -0.45f;
}


void DebugCamera::Update()
{
	SetViewProjectionMat();
	ParallelMove();
}

void DebugCamera::ParallelMove()
{
	auto* m = M::GetInstance();

	float const speed = 2.0f;
	float const deltaTime = m->GetDeltaTime();

	if (m->IsKeyPressed(KeyType::LEFT))
	{
		para.trans.pos.x -= speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::UP))
	{
		para.trans.pos.y += speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::DOWN))
	{
		para.trans.pos.y -= speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::RIGHT))
	{
		para.trans.pos.x += speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::Z))
	{
		para.trans.pos.z += speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::X))
	{
		para.trans.pos.z -= speed * deltaTime;
	}


}
