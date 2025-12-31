#include "InGameScene.h"

InGameScene::InGameScene()
{
	Instantiate();
	Init();
}

void InGameScene::Instantiate()
{
	player.reset(new Player);
	blackBlock.reset(new BlackBlock);
	greenBlock.reset(new GreenBlock);
	normalBlock.reset(new NormalBlock);
	blockManager.reset(new BlockManager);
	inGameController.reset(new InGameController);
}

void InGameScene::Init()
{
	mainCamera->Getter_Trans()->pos = { 1.3f,3.0f,-1.0f };
	mainCamera->Getter_Trans()->quaternion.axis.y = -0.45f;

	gameObjManager->RegisterForContainer(
		player.get(), blackBlock.get(),
		greenBlock.get(), normalBlock.get(), blockManager.get(), 
		inGameController.get());

	gameObjManager->Init();
}
