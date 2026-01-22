#include "InGameController.h"
#include "GameObjectManager.h"
#include "../../GameObjects/Player/Player.h"


//コリジョンバックテーブルを設定
void InGameController::SetCollisionBackTable()
{

}

void InGameController::Update()
{
	//モデルの更新処理（中身を書いていれば）
	model->Update();
	//player->trans.pos.y = 3.0f;

}

void InGameController::Init()
{
	//モデルの初期化
	model->Init(&trans);

	//プレイヤーの挿入
	std::vector<GameObject*> objContainer = gameObjectManager->Find(Tag::kPlayer);
	player = reinterpret_cast<Player*>(objContainer[0]);


	//位置
	trans.pos.z = 4.0f;
}

void InGameController::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();
}

void InGameController::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
}


InGameController::InGameController()
{
	//モデルのインスタンス化
	model.reset(new PlayerModel);
}
