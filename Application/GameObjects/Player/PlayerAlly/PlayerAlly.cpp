#include "PlayerAlly.h"
#include "imgui.h"


PlayerAlly::PlayerAlly()
{
	// モデルのインスタンス化
	model.reset(new PlayerAllyModel);
}

void PlayerAlly::Reset()
{
	// モデルのリセット
	model->Reset();
}

void PlayerAlly::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::PlayerAlly);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);


	trans.pos.z = 1.0f;
}

void PlayerAlly::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::Enemy, collisionBackToEnemy);
}

void PlayerAlly::Update()
{
	//モデルの更新処理
	model->Update();
}

void PlayerAlly::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

// エネミーとの衝突
void PlayerAlly::CollisionBackToEnemy::operator()()
{}