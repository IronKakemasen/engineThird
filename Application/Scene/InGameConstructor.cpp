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
		auto* black = blackBlocks.emplace_back(std::make_unique<BlackBlock>()).get();
		auto* green = greenBlocks.emplace_back(std::make_unique<GreenBlock>()).get();
		blockManager->SetBlackBlock(black);
		blockManager->SetGreenBlock(green);
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

	gameObjManager->RegisterForContainer(player.get(), blockManager.get(),
		inGameController.get());

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

	gameObjManager->Init();
	camera.Init(cameraController->GetUsingCamera()->Getter_Parameters(),
		&player->Getter_Trans()->pos);
}
