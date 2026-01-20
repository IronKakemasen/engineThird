#include "PlayerTower.h"
#include "../Json/Json.h"

PlayerTower::PlayerTower()
{
	// モデルのインスタンス化
	model.reset(new PlayerTowerModel);
}

void PlayerTower::Reset()
{
	// モデルのリセット
	model->Reset();
}

void PlayerTower::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayerTower);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToEnemy.Init(this);
}

void PlayerTower::SetCollisionBackTable()
{
	// タグ：Enemyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
}

void PlayerTower::Update()
{
	//モデルの更新処理
	model->Update();
}

void PlayerTower::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

// Enemyとの衝突
void PlayerTower::CollisionBackToEnemy::operator()()
{
	// 自身の取得
	auto* PlayerTower = me;
	me->trans.rotation.y += 1.0f;
}