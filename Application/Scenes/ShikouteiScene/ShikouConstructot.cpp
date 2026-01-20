#include "ShikouteiScene.h"
#include "../../utilities/Json/Json.h"

ShikouteiScene::ShikouteiScene()
{

}

void ShikouteiScene::Instantiate()
{
	// プレイヤーのインスタンス化
	player.reset(new Player);
	// プレイヤータワーのインスタンス化
	for (auto& playerTower : playerTowers)
		playerTower.reset(new PlayerTower);
	// プレイヤーアリーのインスタンス化
	for (auto& ally : allies)
		ally.reset(new PlayerAlly);
	// エネミーのインスタンス化
	for (auto& enemyInstance : enemies)
		enemyInstance.reset(new Enemy);
	// エネミータワーのインスタンス化
	for (auto& enemyTower : enemyTowers)
		enemyTower.reset(new EnemyTower);
	// エネミーファクトリーのインスタンス化
	for (auto& enemyFactory : enemyFactories)
		enemyFactory.reset(new EnemyFactory);


	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	gameObjManager->RegisterForContainer(player.get());
	for (auto& enemyInstance : enemies)
		gameObjManager->RegisterForContainer(enemyInstance.get());
	for (auto& ally : allies)
		gameObjManager->RegisterForContainer(ally.get());
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
		enemyInstance->SetTargetTower(playerTower.get());
	}

	for (auto& ally : allies)
	{
		ally->SetTargetPlayer(player.get());
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
