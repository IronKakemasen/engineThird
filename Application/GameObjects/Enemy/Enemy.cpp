#include "Enemy.h"
#include "imgui.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Player/PlayerTower/PlayerTower.h"

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
	SetIdentity(Tag::kEnemy);
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
	SetCollisionBack(Tag::kPlayer, collisionBackToPlayer);
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
	// タグ：PlayerTowerと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerTower, collisionBackToPlayerTower);
}

void Enemy::Update()
{
	// 自身の位置を取得
	Vector3 myPos = trans.pos;
	// ターゲットの位置を取得
	Vector3 towerPos = targetTower->Getter_Trans()->pos;
	Vector3 playerPos = targetPlayer->Getter_Trans()->pos;
	// ターゲットまでの方向ベクトルを計算
	Vector3 dirToTower = towerPos - myPos;
	Vector3 dirToPlayer = playerPos - myPos;
	// 最終的に向かう方向ベクトル
	Vector3 finalDir = {};

	if (dirToPlayer.GetMagnitutde() < GameConstants::kEnemyRecognizeDistance)
	{
		finalDir = dirToPlayer.GetNormalized();
	}
	else
	{
		finalDir = dirToTower.GetNormalized();
	}

	// 移動
	trans.pos = trans.pos + finalDir * GameConstants::kEnemySpeed;

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

