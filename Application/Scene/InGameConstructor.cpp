#include "InGameScene.h"

InGameScene::InGameScene()
{
	Instantiate();
	Init();
}

void InGameScene::Instantiate()
{
	player.reset(new Player);
	inGameController.reset(new InGameController);
	blockManager.reset(new BlockManager);

	for (int i = 0; i < BlockManager::kNumGreenBlock; ++i)
	{
		auto* green = greenBlocks.emplace_back(std::make_unique<GreenBlock>()).get();

		blockManager->SetGreenBlock(green);
		green->light = M::GetInstance()->ImportPointLight();
	}

	for (int i = 0; i < BlockManager::kNumBlackBlock; ++i)
	{
		auto* black = blackBlocks.emplace_back(std::make_unique<BlackBlock>()).get();
		blockManager->SetBlackBlock(black);
	}

	for (int i = 0; i < BlockManager::kNumNormalBlock; ++i)
	{
		auto* normal = normalBlocks.emplace_back(std::make_unique<NormalBlock>()).get();
		blockManager->SetNormalBlock(normal);
	}

	for (int i = 0; i < 3; ++i)
	{
		pointLights[i] = M::GetInstance()->ImportPointLight();
	}

}

void InGameScene::Init()
{
	cameraController->Getter_DebugCamera()->Getter_Parameters()->trans.pos =
	{ 100,105,100 };

	for (int i = 0; i < BlockManager::kNumGreenBlock; ++i)
	{
		gameObjManager->RegisterForContainer(greenBlocks[i].get());
	}

	for (int i = 0; i < BlockManager::kNumBlackBlock; ++i)
	{
		gameObjManager->RegisterForContainer(blackBlocks[i].get());
	}

	for (int i = 0; i < BlockManager::kNumNormalBlock; ++i)
	{
		gameObjManager->RegisterForContainer(normalBlocks[i].get());
	}

	gameObjManager->RegisterForContainer(inGameController.get(),
		blockManager.get(), player.get());

	gameObjManager->Init();

	camera.Init(cameraController->GetUsingCamera()->Getter_Parameters(),
		&player->Getter_Trans()->pos);
}
