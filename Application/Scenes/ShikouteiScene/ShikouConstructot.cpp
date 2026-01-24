#include "ShikouteiScene.h"
#include "../../utilities/Json/Json.h"

ShikouteiScene::ShikouteiScene()
{

}

void ShikouteiScene::Instantiate()
{
	inGameController.reset(new InGameController);

	// プレイヤーのインスタンス化 & IDセット
	player.reset(new Player);
	player->SetID(0);
	// プレイヤータワーのインスタンス化 & IDセット
	for (size_t i = 0; i < playerTowers.size(); ++i)
	{
		playerTowers[i].reset(new PlayerTower);
		playerTowers[i]->SetID(static_cast<int32_t>(i));
	}
	// プレイヤーアリーのインスタンス化 & IDセット
	for (size_t i = 0; i < allies.size(); ++i)
	{
		allies[i].reset(new PlayerAlly);
		allies[i]->SetID(static_cast<int32_t>(i));
	}
	// プレイヤーバレットのインスタンス化 & IDセット
	for (size_t i = 0; i < playerBullets.size(); ++i)
	{
		playerBullets[i].reset(new PlayerBullet);
		playerBullets[i]->SetID(static_cast<int32_t>(i));
	}
	// エネミーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemies.size(); ++i)
	{
		enemies[i].reset(new Enemy);
		enemies[i]->SetID(static_cast<int32_t>(i));
	}
	// エネミータワーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemyTowers.size(); ++i)
	{
		enemyTowers[i].reset(new EnemyTower);
		enemyTowers[i]->SetID(static_cast<int32_t>(i));
	}
	// エネミーファクトリーのインスタンス化 & IDセット
	for (size_t i = 0; i < enemyFactories.size(); ++i)
	{
		enemyFactories[i].reset(new EnemyFactory);
		enemyFactories[i]->SetID(static_cast<int32_t>(i));
	}

	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	gameObjManager->RegisterForContainer(player.get(), inGameController.get());
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

void ShikouteiScene::Init()
{
	mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters());
	
	//矩形の初期化
	quad.Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2));
	//両面描画にする
	quad.appearance.cullMode = CullMode::kCullModeNone;

	//スプライトの初期化
	sprite.Initialize(100, 100, {1000,100,0.0f},
		M::GetInstance()->GetTexIndex(TextureTag::kSouhei));

	//アトラススプライトの初期化
	atlasNumber.Initialize(48, 48, { 1000,200,0.0f },
		M::GetInstance()->GetTexIndex(TextureTag::kAtlasNumbers));
	//アトラス画像に対応させる
	atlasNumber.ToAtlas(10);
	
	// resource/application/json からデータをロード
	Json::LoadAll("./resource/application/json/");

}
