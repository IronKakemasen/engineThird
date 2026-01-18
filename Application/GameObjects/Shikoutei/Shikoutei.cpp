#include "Shikoutei.h"

void Shikoutei::Update()
{
	//モデルの更新処理（中身を書いていれば）
	shikoModel->Update();
	static Counter c(1.0f);

	c.Add();
	if (c.IsEnd())
	{
		trans.pos.z += 1.0f;
	}

}

void Shikoutei::Init()
{
	//モデルの初期化
	shikoModel->Init(&trans);

	//identityTableにセットされている通りに、identityを定める
	//タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kShikoutei);
	//矩形コリジョンをアタッチ
	SetRectCollision(1.0, 1.0f);
	//円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
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
}
