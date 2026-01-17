#include "ShikouteiScene.h"

ShikouteiScene::ShikouteiScene()
{

}

void ShikouteiScene::Instantiate()
{
	//始皇帝のインスタンス化
	shikoutei.reset(new Shikoutei);



	//ゲームオブジェクトマネージャーに登録する。登録順が処理順となる
	gameObjManager->RegisterForContainer(shikoutei.get());
}

void ShikouteiScene::Init()
{
	mainCamera.Init(cameraController->GetMainCamera()->Getter_Parameters());
	quad.Initialize(1.0f, 1.0f, {}, M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2));
	quad.appearance.cullMode = CullMode::kCullModeNone;

	sprite.Initialize(100, 100, {1000,100,0.0f},
		M::GetInstance()->GetTexIndex(TextureTag::kSouhei));

}
