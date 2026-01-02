#include "DebugCamera.h"
#include "../../M.h"

DebugCamera::DebugCamera()
{
	trans.pos = { 0.0f,3.0f,-1.0f };
	trans.quaternion.axis.y = -0.45f;
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
		trans.pos.x -= speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::UP))
	{
		trans.pos.y += speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::DOWN))
	{
		trans.pos.y -= speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::RIGHT))
	{
		trans.pos.x += speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::Z))
	{
		trans.pos.z += speed * deltaTime;
	}

	if (m->IsKeyPressed(KeyType::X))
	{
		trans.pos.z -= speed * deltaTime;
	}


}
