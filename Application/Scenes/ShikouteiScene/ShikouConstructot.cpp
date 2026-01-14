#include "ShikouteiScene.h"

ShikouteiScene::ShikouteiScene()
{

}

void ShikouteiScene::Instantiate()
{
	//至高帝のインスタンス化
	shikoutei.reset(new Shikoutei);
	// プレイヤーのインスタンス化
	player.reset(new Player);



	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	gameObjManager->RegisterForContainer(shikoutei.get());
	gameObjManager->RegisterForContainer(player.get());
}

void ShikouteiScene::Init()
{
	mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters());

}
