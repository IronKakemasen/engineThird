#include "SampleScene.h"
#include "../../engineCore/Light/DirectionalLight/DirectionalLight.h"
#include "../../engineCore/Light/PointLight/PointLight.h"


SampleScene::SampleScene()
{
	Instantiate();
	Init();
}

void SampleScene::Instantiate()
{
	pointLight = M::GetInstance()->CreatePointLight();
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
	pointLight->Init();
	dirLight->Init();

	mainCamera->Getter_Trans()->pos = { 1.3f,3.0f,-1.0f};
	mainCamera->Getter_Trans()->quaternion.axis.y = -0.45f;
	triangle->Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kPlayer));
	quad->Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kNothing));
	sPlayer->Init();
	sObj->Init();

	for (int i = 0; i < 10; ++i)
	{
		sEnemies[i]->Init();
	}

}
