#include "StageSelectScene.h"
#include "../../utilities/Json/Json.h"

StageSelectScene::StageSelectScene()
{

}

void StageSelectScene::Instantiate()
{
	//inGameController.reset(new InGameController);

	//// resource/application/json 以下データをロード
	//Json::LoadAll("./resource/application/json/");

	//inGameConfig = std::make_unique<InGameConfig>();
	//inGameConfig->Load();

	//for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	//{
	//	// プレイヤーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < player[stageIndex].size(); ++i)
	//	{
	//		player[stageIndex][i].reset(new Player);
	//		player[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		player[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// テスト地面のインスタンス化 & IDセット
	//	for (size_t i = 0; i < shikouteis[stageIndex].size(); ++i)
	//	{
	//		shikouteis[stageIndex][i].reset(new Shikoutei);
	//		shikouteis[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		shikouteis[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// プレイヤータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
	//	{
	//		playerTowers[stageIndex][i].reset(new PlayerTower);
	//		playerTowers[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		playerTowers[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// プレイヤーアリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < allies[stageIndex].size(); ++i)
	//	{
	//		allies[stageIndex][i].reset(new PlayerAlly);
	//		allies[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		allies[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// プレイヤーバレットのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerBullets[stageIndex].size(); ++i)
	//	{
	//		playerBullets[stageIndex][i].reset(new PlayerBullet);
	//		playerBullets[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		playerBullets[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// エネミーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemies[stageIndex].size(); ++i)
	//	{
	//		enemies[stageIndex][i].reset(new Enemy);
	//		enemies[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		enemies[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// エネミータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
	//	{
	//		enemyTowers[stageIndex][i].reset(new EnemyTower);
	//		enemyTowers[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		enemyTowers[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//	// エネミーファクトリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
	//	{
	//		enemyFactories[stageIndex][i].reset(new EnemyFactory);
	//		enemyFactories[stageIndex][i]->SetID(static_cast<int32_t>(i));
	//		enemyFactories[stageIndex][i]->SetInGameConfig(inGameConfig.get());
	//	}
	//}

	//gameObjManager->RegisterForContainer(inGameController.get());
}

void StageSelectScene::Init()
{
	//mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters(),
	//	inGameController.get(), player[0][0].get());

	//for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	//{
	//	// プレイヤーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < player[stageIndex].size(); ++i)
	//	{
	//		player[stageIndex][i]->Init();
	//	}
	//	// テスト地面のインスタンス化 & IDセット
	//	for (size_t i = 0; i < shikouteis[stageIndex].size(); ++i)
	//	{
	//		shikouteis[stageIndex][i]->Init();
	//	}
	//	// プレイヤータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
	//	{
	//		playerTowers[stageIndex][i]->Init();
	//	}
	//	// プレイヤーアリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < allies[stageIndex].size(); ++i)
	//	{
	//		allies[stageIndex][i]->Init();
	//	}
	//	// プレイヤーバレットのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerBullets[stageIndex].size(); ++i)
	//	{
	//		playerBullets[stageIndex][i]->Init();
	//	}
	//	// エネミーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemies[stageIndex].size(); ++i)
	//	{
	//		enemies[stageIndex][i]->Init();
	//	}
	//	// エネミータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
	//	{
	//		enemyTowers[stageIndex][i]->Init();
	//	}
	//	// エネミーファクトリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
	//	{
	//		enemyFactories[stageIndex][i]->Init();
	//	}
	//}

	//for (size_t stageIndex = 0; stageIndex < GameConstants::kMaxStages; ++stageIndex)
	//{
	//	// プレイヤーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < player[stageIndex].size(); ++i)
	//	{
	//		player[stageIndex][i]->Reset();
	//	}
	//	// テスト地面のインスタンス化 & IDセット
	//	for (size_t i = 0; i < shikouteis[stageIndex].size(); ++i)
	//	{
	//		shikouteis[stageIndex][i]->Reset();
	//	}
	//	// プレイヤータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerTowers[stageIndex].size(); ++i)
	//	{
	//		playerTowers[stageIndex][i]->Reset();
	//	}
	//	// プレイヤーアリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < allies[stageIndex].size(); ++i)
	//	{
	//		allies[stageIndex][i]->Reset();
	//	}
	//	// プレイヤーバレットのインスタンス化 & IDセット
	//	for (size_t i = 0; i < playerBullets[stageIndex].size(); ++i)
	//	{
	//		playerBullets[stageIndex][i]->Reset();
	//	}
	//	// エネミーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemies[stageIndex].size(); ++i)
	//	{
	//		enemies[stageIndex][i]->Reset();
	//	}
	//	// エネミータワーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyTowers[stageIndex].size(); ++i)
	//	{
	//		enemyTowers[stageIndex][i]->Reset();
	//	}
	//	// エネミーファクトリーのインスタンス化 & IDセット
	//	for (size_t i = 0; i < enemyFactories[stageIndex].size(); ++i)
	//	{
	//		enemyFactories[stageIndex][i]->Reset();
	//	}
	//}
}
