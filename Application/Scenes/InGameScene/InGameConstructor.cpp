#include "InGameScene.h"
#include "../../Systems/DamageDisplay/DamageDisplay.h"
#include "../../Systems/DeathParticle/DeathParticle.h"


InGameScene::InGameScene()
{
	for (int i = 0; i < kNumPLight; ++i)
	{
		fieldpointLights[i] = M::GetInstance()->ImportPointLight();
	}
	auto* m = M::GetInstance();

}

void InGameScene::InputFieldLightData()
{

	
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

	// 建物オブジェクトマネージャーのインスタンス化
	buildingsManager = std::make_unique<BuildingsManager>();
	buildingsManager->SetInGameConfig(inGameConfig.get());
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
		playerTowers[i]->SetBuildingsManager(buildingsManager.get());
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
		enemyTowers[i]->SetBuildingsManager(buildingsManager.get());
	}
	// エネミーファクトリーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemyFactories.size(); ++i)
	{
		enemyFactories[i].reset(new EnemyFactory);
		enemyFactories[i]->SetID(static_cast<int32_t>(i));
		enemyFactories[i]->SetInGameConfig(inGameConfig.get());
		enemyFactories[i]->SetBuildingsManager(buildingsManager.get());
	}
	uiDisplayer->SetInGameConfig(inGameConfig.get());

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
	gameObjManager->RegisterForContainer(buildingsManager.get());
	gameObjManager->RegisterForContainer(uiDisplayer.get(), &uIObject);


	// ポインタを渡す
	for (auto& enemyInstance : enemies)
	{
		enemyInstance->SetTargetPlayer(player.get());
		for (auto& playerTower : playerTowers)
			enemyInstance->SetTargetTower(playerTower.get());
	}

	for (auto& ally : allies)
		player->SetAllies(ally.get());

	for (auto& bullet : playerBullets)
		player->SetBullets(bullet.get());

	DeathParticle::Get()->Init(gameObjManager.get());

	player->SetGround(ground.get());
}

void InGameScene::Init()
{
	mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters(),
		inGameController.get(), player.get());

	for (int i = 0; i < kNumPLight; ++i)
	{
		lightModels[i].Init(nullptr);
	}

	DamageDisplay::Get()->Init(&cameraController->GetMainCamera()->vpMat);
}

