#include "TitleScene.h"

TitleScene::TitleScene()
{
	pLights[0] = M::GetInstance()->ImportPointLight();
	pLights[1] = M::GetInstance()->ImportPointLight();
	dirLight->Getter_Para()->intensity = 4.0f;
	dirLight->Getter_Para()->pos = {1,1,1};

}

void TitleScene::Instantiate()
{
	forTitleScene.reset(new ForTitleScene);
	gameObjManager->RegisterForContainer(forTitleScene.get());
}

void TitleScene::Init()
{
	for (int i = 0; i < 2; ++i)
	{
		auto* para = pLights[i]->Getter_Para();
		para->isActive = 1;
		para->intensity = 20000;
		para->invSqrRadius = 800;
	}

	pLights[0]->Getter_Para()->pos = {0,8,16};
	pLights[0]->Getter_Para()->color = { 100,151,233};
	pLights[1]->Getter_Para()->pos = { 0,4,23 };
	pLights[1]->Getter_Para()->color = { 50,50,135};
	titleCamera.Init(cameraController->GetMainCamera()->Getter_Parameters());

	c.Initialize(10.0f);
}
