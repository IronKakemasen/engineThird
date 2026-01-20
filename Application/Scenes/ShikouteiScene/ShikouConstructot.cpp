#include "ShikouteiScene.h"

ShikouteiScene::ShikouteiScene()
{

}

void ShikouteiScene::Instantiate()
{
	// プレイヤーのインスタンス化
	player.reset(new Player);
	// プレイヤータワーのインスタンス化
	playerTower.reset(new PlayerTower);
	// エネミーのインスタンス化
	for (auto& enemyInstance : enemies)
	{
		enemyInstance.reset(new Enemy);
	}
	// エネミータワーのインスタンス化
	enemyTower.reset(new EnemyTower);
	// エネミーファクトリーのインスタンス化
	enemyFactory.reset(new EnemyFactory);

	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	gameObjManager->RegisterForContainer(player.get());
	for (auto& enemyInstance : enemies)
	{
		gameObjManager->RegisterForContainer(enemyInstance.get());
	}
	gameObjManager->RegisterForContainer(playerTower.get());
	gameObjManager->RegisterForContainer(enemyTower.get());
	gameObjManager->RegisterForContainer(enemyFactory.get());
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
	
}
