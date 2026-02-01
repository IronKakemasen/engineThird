#include "Shikoutei.h"

//コリジョンバックテーブルを設定
void Shikoutei::SetCollisionBackTable()
{
}

void Shikoutei::LoadData()
{}

void Shikoutei::SaveData()
{}

void Shikoutei::DebugDraw()
{}

void Shikoutei::ReplaceOnMap(const int32_t stage)
{}

void Shikoutei::Update()
{
	//モデルの更新処理（中身を書いていれば）
}

void Shikoutei::Init()
{
	//モデルの初期化
	shikoModel->Init(&trans);

	//円形コリジョンをアタッチ
	SetCircleCollision(1.0f);

	//衝突判定をするかどうか定める
	SwitchCollisionActivation(false);
}

void Shikoutei::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	shikoModel->Reset();
}

void Shikoutei::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	shikoModel->Draw(vpMat_);
}


Shikoutei::Shikoutei()
{
	//モデルのインスタンス化
	shikoModel.reset(new ShikouteiModel);
	//必須でない
	auto* appearance = shikoModel->model->GetAppearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };
}