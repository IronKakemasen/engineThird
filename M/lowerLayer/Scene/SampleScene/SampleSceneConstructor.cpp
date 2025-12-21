#include "SampleScene.h"
#include "../../engineCore/Render/CommonDrawingSystem/CommonDrawSystem.h"

SampleScene::SampleScene()
{
	Instantiate();
	Init();
}

void SampleScene::Instantiate()
{
	model = M::GetInstance()->CreateModel("./M/resource/preset/model/Ground/Ground.obj");
	triangle.reset(new MTriangle);
	quad.reset(new MQuad);
	particles.reset(new TestParticle);
	sPlayer.reset(new SamplePlayer);
	for (int i = 0; i < 10; ++i)
	{
		sEnemies.emplace_back(std::make_unique<SampleEnemy>());
	}

}

void SampleScene::Init()
{
	mainCamera->trans.translate = { 0.0f,0.0f,-3.0f };
	triangle->Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kPlayer));
	quad->Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kNothing));
	particles->Init();
	sPlayer->Init();
	for (int i = 0; i < 10; ++i)
	{
		sEnemies[i]->Init();
	}

	RegisterForDrawExecutor(quad.get());

}
