#include "PlayerAlly.h"
#include "imgui.h"
#include "../../../GameObjects/Player/Player.h"


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
	SetIdentity(Tag::kPlayerAlly);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);


}

void PlayerAlly::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

void PlayerAlly::Update()
{
	//モデルの更新処理
	model->Update();

	// 移動処理
	Move();
}

void PlayerAlly::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}


void PlayerAlly::Move()
{
	Vector3 targetPos = targetPlayer->GetAllyTargetPos(targetPlayer->GetNextEmptyAllyIndex());

	trans.pos = targetPos;
}



// エネミーとの衝突
void PlayerAlly::CollisionBackToEnemy::operator()()
{}