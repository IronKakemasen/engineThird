#include "SampleScene.h"

SampleScene::SampleScene()
{
	Instantiate();
	Init();
}

void SampleScene::Instantiate()
{
	triangle.reset(new MTriangle);
	quad.reset(new MQuad);
	sPlayer.reset(new SamplePlayer);
	sObj.reset(new SampleObj);

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
	sPlayer->Init();
	sObj->Init();

	for (int i = 0; i < 10; ++i)
	{
		sEnemies[i]->Init();
	}

}
