#include "Shikoutei.h"

void Shikoutei::Update()
{
	//モデルの更新処理（中身を書いていれば）
	shikoModel->Update();

}

void Shikoutei::Init()
{
	//モデルの初期化
	shikoModel->Init(&trans);

	//identityTableにセットされている通りに、identityを定める
	//タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kShikoutei);
	//矩形コリジョンをアタッチ
	SetRectCollision(1.0f, 1.0f);
	//衝突判定をするかどうか定める
	SwitchCollisionActivation(false);

	//位置
	trans.pos.z = 2.0f;
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

//コリジョンバックを設定（後ほど）
void Shikoutei::SetCollisionBackTable()
{

}

Shikoutei::Shikoutei()
{
	//モデルのインスタンス化
	shikoModel.reset(new ShikouteiModel);
	//必須でない
	auto* appearance = shikoModel->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };

}
