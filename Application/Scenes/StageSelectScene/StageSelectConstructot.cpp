#include "StageSelectScene.h"

StageSelectScene::StageSelectScene()
{
	selectCounter.Initialize(0.1f);
	dirLight->Getter_Para()->intensity = 4.4f;
}

void StageSelectScene::Instantiate()
{
	uiDisplayer = std::make_unique<UIDisplayer>();

	inGameController.reset(new InGameController);

	inGameConfig = std::make_unique<InGameConfig>();
	inGameConfig->Load();

	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		// 回転中心オブジェクトのインスタンス化 & IDセット
		for (size_t i = 0; i < centerObject[stageIndex].size(); ++i)
		{
			centerObject[stageIndex][i].reset(new Shikoutei);
			centerObject[stageIndex][i]->SetID(static_cast<int32_t>(i));
			centerObject[stageIndex][i]->SetInGameConfig(inGameConfig.get());
		}
		// プレイヤーのインスタンス化 & IDセット
		for (size_t i = 0; i < player[stageIndex].size(); ++i)
		{
			player[stageIndex][i].reset(new Player);
			player[stageIndex][i]->SetID(static_cast<int32_t>(i));
			player[stageIndex][i]->SetInGameConfig(inGameConfig.get());
		}
		// テスト地面のインスタンス化 & IDセット
		for (size_t i = 0; i < grounds[stageIndex].size(); ++i)
		{
			grounds[stageIndex][i].reset(new Ground);
			grounds[stageIndex][i]->SetID(static_cast<int32_t>(i));
			grounds[stageIndex][i]->SetInGameConfig(inGameConfig.get());
		}
		// プレイヤータワーのインスタンス化 & IDセット
		for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
		{
			playerTowers[stageIndex][i].reset(new PlayerTower);
			playerTowers[stageIndex][i]->SetID(static_cast<int32_t>(i));
			playerTowers[stageIndex][i]->SetInGameConfig(inGameConfig.get());
		}
		// エネミータワーのインスタンス化 & IDセット
		for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
		{
			enemyTowers[stageIndex][i].reset(new EnemyTower);
			enemyTowers[stageIndex][i]->SetID(static_cast<int32_t>(i));
			enemyTowers[stageIndex][i]->SetInGameConfig(inGameConfig.get());
		}
		// エネミーファクトリーのインスタンス化 & IDセット
		for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
		{
			enemyFactories[stageIndex][i].reset(new EnemyFactory);
			enemyFactories[stageIndex][i]->SetID(static_cast<int32_t>(i));
			enemyFactories[stageIndex][i]->SetInGameConfig(inGameConfig.get());
		}
	}
	uiDisplayer->SetInGameConfig(inGameConfig.get());

	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		for (size_t i = 0; i < centerObject[stageIndex].size(); ++i)
		{
			gameObjManager->RegisterForContainer(centerObject[stageIndex][i].get());
		}
		for (size_t i = 0; i < player[stageIndex].size(); ++i)
		{
			gameObjManager->RegisterForContainer(player[stageIndex][i].get());
		}
		for (size_t i = 0; i < grounds[stageIndex].size(); ++i)
		{
			gameObjManager->RegisterForContainer(grounds[stageIndex][i].get());
		}
		for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
		{
			gameObjManager->RegisterForContainer(playerTowers[stageIndex][i].get());
		}
		for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
		{
			gameObjManager->RegisterForContainer(enemyTowers[stageIndex][i].get());
		}
		for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
		{
			gameObjManager->RegisterForContainer(enemyFactories[stageIndex][i].get());
		}
	}
	gameObjManager->RegisterForContainer(inGameController.get());
	gameObjManager->RegisterForContainer(uiDisplayer.get());
}

void StageSelectScene::Init()
{
	mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters());

	mainCamera.cameraPara->trans.pos = Vector3(0.0f, 30.0f, -130.0f);
	mainCamera.cameraPara->trans.lookDir = Vector3(0.0f, -0.714f, 0.7f);

	Reset();
	gameObjManager->Reset();

	for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	{
		for (size_t i = 0; i < player[stageIndex].size(); ++i)
		{
			player[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			player[stageIndex][i]->trans.parent = &centerObject[stageIndex][0]->trans;
		}
		for (size_t i = 0; i < grounds[stageIndex].size(); ++i)
		{
			grounds[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			grounds[stageIndex][i]->trans.parent = &centerObject[stageIndex][0]->trans;
		}
		for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
		{
			playerTowers[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			playerTowers[stageIndex][i]->trans.parent = &centerObject[stageIndex][0]->trans;
		}
		for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
		{
			enemyTowers[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			enemyTowers[stageIndex][i]->trans.parent = &centerObject[stageIndex][0]->trans;
		}
		for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
		{
			enemyFactories[stageIndex][i]->SetStatus(GameObjectBehavior::Status::kDrawOnly);
			enemyFactories[stageIndex][i]->trans.parent = &centerObject[stageIndex][0]->trans;
		}
	}
}
