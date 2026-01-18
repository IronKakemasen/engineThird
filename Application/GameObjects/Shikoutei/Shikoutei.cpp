#include "Shikoutei.h"

//コリジョンバックテーブルを設定
void Shikoutei::SetCollisionBackTable()
{
	//タグ：kExampleと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kExample, collisionBackToTheFuture);
}

void Shikoutei::CollisionBackToTheFuture::operator()()
{
	//衝突したときの処理を書く
	//衝突相手
	auto* opponent = shikoutei->Getter_ColObj();
	opponent->trans.rotation.x += 1.0f;
}

void Shikoutei::CollisionBackToTheFuture::Init(Shikoutei* shikoutei_)
{
	shikoutei = shikoutei_;
}


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
	//円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	//衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	//位置
	trans.pos.z = 1.0f;

	//CollisionBackToTheFutureの初期化
	collisionBackToTheFuture.Init(this);
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
}
