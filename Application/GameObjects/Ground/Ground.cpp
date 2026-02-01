#include "Ground.h"

//コリジョンバックテーブルを設定
void Ground::SetCollisionBackTable()
{
}



void Ground::LoadData()
{}

void Ground::SaveData()
{}

void Ground::DebugDraw()
{}

void Ground::ReplaceOnMap(const int32_t stage)
{}

void Ground::Update()
{
	//モデルの更新処理（中身を書いていれば）
	groundPlane->Update();

}

void Ground::Init()
{
	//モデルの初期化
	groundPlane->Init(&trans);
	groundPlane->model->GetAppearance(0)->color = { 255,255,255,255 };

	//identityTableにセットされている通りに、identityを定める
	//タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kNone);
	//円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	//衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

}

void Ground::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	groundPlane->Reset();
}

void Ground::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	groundPlane->Draw(vpMat_);
}


Ground::Ground()
{
	//モデルのインスタンス化
	groundPlane.reset(new GroundPlane);
}
