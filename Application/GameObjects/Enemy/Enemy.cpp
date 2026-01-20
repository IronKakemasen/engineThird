#include "Enemy.h"
#include "imgui.h"


Enemy::Enemy()
{
	// モデルのインスタンス化
	model.reset(new EnemyModel);
}

void Enemy::Reset()
{
	// モデルのリセット
	model->Reset();
}

void Enemy::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::Enemy);
	// 円形コリジョンをアタッチ
	SetCircleCollision(1.0f);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// collisionBackの初期化
	collisionBackToPlayer.Init(this);
	collisionBackToPlayerBullet.Init(this);
	collisionBackToPlayerTower.Init(this);


	trans.pos.z = 1.0f;
}

void Enemy::SetCollisionBackTable()
{
	// タグ：Playerと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::Player, collisionBackToPlayer);
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::PlayerBullet, collisionBackToPlayerBullet);
	// タグ：PlayerTowerと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::PlayerTower, collisionBackToPlayerTower);
}

void Enemy::Update()
{
	//モデルの更新処理
	model->Update();
}

void Enemy::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

// プレイヤーとの衝突
void Enemy::CollisionBackToPlayer::operator()()
{
}
// プレイヤー弾との衝突
void Enemy::CollisionBackToPlayerBullet::operator()()
{
	// 衝突したときの処理を書く
	me->SetStatus(Status::kInActive);
}
// プレイヤータワーとの衝突
void Enemy::CollisionBackToPlayerTower::operator()()
{
}

