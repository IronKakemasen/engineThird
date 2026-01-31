#include "InGameScene.h"

InGameScene::InGameScene()
{

}

void InGameScene::InputFieldLightData()
{
	for (int i = 0; i < kNumPLight; ++i)
	{
		fieldpointLights[i] = M::GetInstance()->ImportPointLight();
		fieldpointLights[i]->Getter_Para()->color = { 20,255,20};
	}

	//STAGE1
	//int const stage1 = 5;
	//fieldLightData[0].dstPositions.resize(stage1);
	//fieldLightData[0].useNum = stage1;
	//for (int i = 0; i < stage1; ++i)
	//{
	//	fieldLightData[0].dstPositions[i] = { 0.0f,5.0f  ,(float)i * 10.0f };
	//}
	int const stage1 = 9;
	float const width1 = 10.0f;
	fieldLightData[0].dstPositions.resize(stage1);
	fieldLightData[0].useNum = stage1;
	fieldLightData[0].dstPositions[0] = { 0,lightHeight,0 };
	int k = 1;
	for (int i = 1; i < stage1; i += 4, ++k)
	{
		float offset = width1 * k;

		if (k == 1)
		{
			fieldLightData[0].dstPositions[i] =		{ 0.0f , lightHeight   ,offset * 1.25f };
			fieldLightData[0].dstPositions[i + 1] = { offset*1.25f  ,lightHeight   ,0.0f};
			fieldLightData[0].dstPositions[i + 2] = { 0.0f ,lightHeight   ,-offset * 1.25f };
			fieldLightData[0].dstPositions[i + 3] = { -offset * 1.25f,lightHeight ,0.0f};
		}
		else
		{
			fieldLightData[0].dstPositions[i] = { -offset ,lightHeight   ,offset };
			fieldLightData[0].dstPositions[i + 1] = { offset  ,lightHeight ,offset };
			fieldLightData[0].dstPositions[i + 2] = { offset  ,lightHeight ,-offset };
			fieldLightData[0].dstPositions[i + 3] = { -offset,lightHeight ,-offset };
		}
	}



	//STAGE2
	int const stage2 = 9;
	float const width2 = 10.0f;
	fieldLightData[1].dstPositions.resize(stage2);
	fieldLightData[1].useNum = stage2;
	fieldLightData[1].dstPositions[0] = { 0,lightHeight,0 };
	k = 1;
	for (int i = 1; i < stage2; i+=4,++k)
	{
		float offset = width2 * k;

		if (k == 1)
		{
			fieldLightData[1].dstPositions[i] = { 0.0f , lightHeight   ,offset };
			fieldLightData[1].dstPositions[i + 1] = { offset  ,lightHeight   ,0.0f };
			fieldLightData[1].dstPositions[i + 2] = { 0.0f ,lightHeight  ,-offset };
			fieldLightData[1].dstPositions[i + 3] = { -offset,lightHeight  ,0.0f };
		}
		else
		{
			fieldLightData[1].dstPositions[i] = { -offset , lightHeight  ,offset };
			fieldLightData[1].dstPositions[i + 1] = { offset  ,lightHeight  ,offset };
			fieldLightData[1].dstPositions[i + 2] = { offset  ,lightHeight  ,-offset };
			fieldLightData[1].dstPositions[i + 3] = { -offset,lightHeight  ,-offset };
		}
	}

	//STAGE3
	int const stage3 = 9;
	float const width3 = 10.0f;
	fieldLightData[2].dstPositions.resize(stage3);
	fieldLightData[2].useNum = stage3;
	k = 1;
	fieldLightData[2].dstPositions[0] = { 0,lightHeight,0 };
	for (int i = 1; i < stage3; i += 4, ++k)
	{
		float offset = width3 * k;
		if (k == 1)
		{
			fieldLightData[2].dstPositions[i] = { 0.0f , lightHeight  ,offset };
			fieldLightData[2].dstPositions[i + 1] = { offset  ,lightHeight  ,0.0f };
			fieldLightData[2].dstPositions[i + 2] = { 0.0f ,lightHeight ,-offset };
			fieldLightData[2].dstPositions[i + 3] = { -offset,lightHeight ,0.0f };
		}
		else
		{
			fieldLightData[2].dstPositions[i] = { -offset ,lightHeight ,offset };
			fieldLightData[2].dstPositions[i + 1] = { offset  ,lightHeight ,offset };
			fieldLightData[2].dstPositions[i + 2] = { offset  ,lightHeight ,-offset };
			fieldLightData[2].dstPositions[i + 3] = { -offset,lightHeight ,-offset };
		}

	}
}

void InGameScene::Instantiate()
{
	Load();
	dirLight->Getter_Para()->pos = { 1.0f,0.1f,0.0f };
	ground.reset(new Ground);
	uiDisplayer = std::make_unique<UIDisplayer>();

	inGameController.reset(new InGameController);
	inGameConfig = std::make_unique<InGameConfig>();
	inGameConfig->Load();

	tenkyuuClass.reset(new TenkyuuClass);

	// プレイヤーのインスタンス化 & IDセット
	player.reset(new Player);
	player->SetID(0);
	player->SetInGameConfig(inGameConfig.get());
	// プレイヤータワーのインスタンス化 & IDセット
	for (size_t i = 0; i < playerTowers.size(); ++i)
	{
		playerTowers[i].reset(new PlayerTower);
		playerTowers[i]->SetID(static_cast<int32_t>(i));
		playerTowers[i]->SetInGameConfig(inGameConfig.get());
	}
	// プレイヤーアリーのインスタンス化 & IDセット
	for (size_t i = 0; i < allies.size(); ++i)
	{
		allies[i].reset(new PlayerAlly);
		allies[i]->SetID(static_cast<int32_t>(i));
		allies[i]->SetInGameConfig(inGameConfig.get());
	}
	// プレイヤーバレットのインスタンス化 & IDセット
	for (size_t i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i].reset(new PlayerBullet);
		playerBullets[i]->SetID(static_cast<int32_t>(i));
		playerBullets[i]->SetInGameConfig(inGameConfig.get());
	}
	// エネミーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		enemies[i].reset(new Enemy);
		enemies[i]->SetID(static_cast<int32_t>(i));
		enemies[i]->SetInGameConfig(inGameConfig.get());
	}
	// エネミータワーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemyTowers.size(); ++i)
	{
		enemyTowers[i].reset(new EnemyTower);
		enemyTowers[i]->SetID(static_cast<int32_t>(i));
		enemyTowers[i]->SetInGameConfig(inGameConfig.get());
	}
	// エネミーファクトリーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemyFactories.size(); ++i)
	{
		enemyFactories[i].reset(new EnemyFactory);
		enemyFactories[i]->SetID(static_cast<int32_t>(i));
		enemyFactories[i]->SetInGameConfig(inGameConfig.get());
	}

	//八神ライト
	InputFieldLightData();


	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	gameObjManager->RegisterForContainer(player.get());
	gameObjManager->RegisterForContainer(
		inGameController.get(), ground.get(), tenkyuuClass.get());
	for (auto& enemyInstance : enemies)
		gameObjManager->RegisterForContainer(enemyInstance.get());
	for (auto& ally : allies)
		gameObjManager->RegisterForContainer(ally.get());
	for (auto& playerBullet : playerBullets)
		gameObjManager->RegisterForContainer(playerBullet.get());
	for (auto& playerTower : playerTowers)
		gameObjManager->RegisterForContainer(playerTower.get());
	for (auto& enemyTower : enemyTowers)
		gameObjManager->RegisterForContainer(enemyTower.get());
	for (auto& enemyFactory : enemyFactories)
		gameObjManager->RegisterForContainer(enemyFactory.get());


	// ポインタを渡す
	for (auto& enemyInstance : enemies)
	{
		enemyInstance->SetTargetPlayer(player.get());
		for (auto& playerTower : playerTowers)
			enemyInstance->SetTargetTower(playerTower.get());
	}

	for (auto& ally : allies)
	{
		player->SetAllies(ally.get());
	}

	for (auto& bullet : playerBullets)
	{
		player->SetBullets(bullet.get());
	}
}

void InGameScene::Init()
{

	mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters(),
		inGameController.get(), player.get());

	for (int i = 0; i < kNumPLight; ++i)
	{
		lightModels[i].Init(nullptr);
	}
}

