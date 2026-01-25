#include "Enemy.h"
#include "imgui.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Player/PlayerTower/PlayerTower.h"
#include "../../M/utilities/Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../Config/GameConstants.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include <array>

Enemy::Enemy()
{
	// モデルのインスタンス化
	model.reset(new EnemyModel);

	//必須でない
	auto* appearance = model->model->Getter_Appearance(0);

	appearance->metalic = 0.72f;
	appearance->roughness = 0.4f;
	appearance->color = { 255,0,0,255 };
	
	// Jsonパスの設定
	path = "./resource/application/json/enemy/enemyData.json";
}

void Enemy::Reset()
{
	//モデルのリセット（中身が書いてあれば）
	model->Reset();

	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// 初期無効化
	status = Status::kInActive;

	// データ読み込み
	LoadData();

	// 初期向きを最近のターゲット方向に設定
	LookAtTarget();
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
	collisionBackToPlayerAlly.Init(this);

	// ポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);
	for (auto& towerObj : gameObjectManager->Find(Tag::kPlayerTower))
	{
		playerTowers.push_back(reinterpret_cast<PlayerTower*>(towerObj));
	}

	trans.interpolationCoe = 0.1f;
}

void Enemy::Spawn(Vector3 pos)
{
	// 有効化
	SetStatus(Status::kActive);
	// 初期座標設定
	trans.pos = pos;
	// 体力初期化
	hp = 100.0f;
}

void Enemy::SetCollisionBackTable()
{
	// タグ：Playerと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayer, collisionBackToPlayer);
	// タグ：PlayerBulletと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerBullet, collisionBackToPlayerBullet);
	// タグ：PlayerTowerと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerTower, collisionBackToPlayerTower);
	// タグ：PlayerAllyと衝突したときのコリジョンバックを登録
	SetCollisionBack(Tag::kPlayerAlly, collisionBackToPlayerAlly);

}

// データ保存・読み込み
void Enemy::LoadData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::LoadParam(path, key + "/position", trans.pos);
	Json::LoadParam(path, key + "/speed", speed);
}
void Enemy::SaveData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::SaveParam(path, key + "/position", trans.pos);
	Json::SaveParam(path, key + "/speed", speed);
	Json::Save(path);
}

void Enemy::Update()
{
	//モデルの更新処理
	model->Update();

	// 移動処理
	MoveToTarget();

	// ノックバック処理
	MoveKnockBack();

	// 無敵時間更新
	UpdateInvincibleTime();

	Vector3 finalVelocity = moveVelocity + knockBackVelocity;
	trans.pos = trans.pos + finalVelocity;
}

void Enemy::MoveToTarget()
{
	// ターゲットまでの方向ベクトルを計算
	std::array<Vector3, GameConstants::kMaxPlayerTowers> dirToTowers{};
	for (size_t i = 0; i < playerTowers.size(); ++i)
	{
		dirToTowers[i] = Vector3(9999.9f, 9999.9f, 9999.9f);
		if (playerTowers[i]->GetStatus() == Status::kActive)
			dirToTowers[i] = playerTowers[i]->Getter_Trans()->pos - trans.pos;
	}
	Vector3 dirToPlayer = targetPlayer->Getter_Trans()->GetWorldPos() - trans.GetWorldPos();

	// 最も近いタワーを追う
	size_t nearestTowerIndex = 0;
	float nearestDistance = dirToTowers[0].GetMagnitutde();
	for (size_t i = 1; i < playerTowers.size(); ++i)
	{
		float distance = dirToTowers[i].GetMagnitutde();
		if (distance < nearestDistance)
		{
			nearestDistance = distance;
			nearestTowerIndex = i;
		}
	}
	Vector3 lastDir = dirToTowers[nearestTowerIndex].GetNormalized();

	// 補完
	trans.lookDir = Easing::SLerp(trans.lookDir, lastDir, trans.interpolationCoe);

	// エネミー ⇒ 塔　移動ベクトル
	moveVelocity = trans.lookDir.GetNormalized() * speed;
}

void Enemy::LookAtTarget()
{
	// ターゲットまでの方向ベクトルを計算
	std::array<Vector3, GameConstants::kMaxPlayerTowers> dirToTowers{};
	for (size_t i = 0; i < playerTowers.size(); ++i)
	{
		dirToTowers[i] = Vector3(9999.9f, 9999.9f, 9999.9f);
		if (playerTowers[i]->GetStatus() == Status::kActive)
			dirToTowers[i] = playerTowers[i]->Getter_Trans()->pos - trans.pos;
	}
	Vector3 dirToPlayer = targetPlayer->Getter_Trans()->GetWorldPos() - trans.GetWorldPos();

	// 最も近いタワーを追う
	size_t nearestTowerIndex = 0;
	float nearestDistance = dirToTowers[0].GetMagnitutde();
	for (size_t i = 1; i < playerTowers.size(); ++i)
	{
		float distance = dirToTowers[i].GetMagnitutde();
		if (distance < nearestDistance)
		{
			nearestDistance = distance;
			nearestTowerIndex = i;
		}
	}

	Vector3 lastDir = dirToTowers[nearestTowerIndex].GetNormalized();
	// 一直線になるのを防ぐためほんの少しだけ右回転する
	lastDir.x += 0.001f;

	trans.lookDir = lastDir;
}

void Enemy::MoveKnockBack()
{
	knockBackVelocity = knockBackVelocity * 0.9f;
}

void Enemy::KnockBack(float power)
{
	knockBackVelocity = (trans.lookDir * -1) * power * 1.0f;
}

void Enemy::UpdateInvincibleTime()
{
	if (invincibleTime > 0)
	{
		invincibleTime -= 1;
	}
}

void Enemy::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void Enemy::DebugDraw()
{
#ifdef USE_IMGUI

	std::string tag = "##speed: " + std::to_string(speed);
	ImGui::DragFloat(tag.c_str(), &speed, 0.01f, 0.0f, 10.0f);

#endif // USE_IMGUI
}

// プレイヤーとの衝突
void Enemy::CollisionBackToPlayer::operator()()
{
	//// 衝突したときの処理を書く
	//me->KnockBack(0.3f);
}

// プレイヤー弾との衝突
void Enemy::CollisionBackToPlayerBullet::operator()()
{
	if (me->invincibleTime > 0)
	{
		// 無敵時間中は何もしない
		return;
	}

	// プレイヤー弾のポインタを取得
	auto* playerBullet = reinterpret_cast<PlayerBullet*>(me->Getter_ColObj());

	// ノックバック付与
	me->KnockBack(0.02f);

	// 無敵付与
	me->invincibleTime = 20;

	// ダメージ処理
	me->hp = me->hp - playerBullet->GetAttackPower();

	// 死亡した時
	if (me->hp < 0.0f && playerBullet->GetAttackStage() == 0)
	{
		me->SetStatus(Status::kInActive);

		me->targetPlayer->SpawnAlly(me->trans.pos);
	}
}

// プレイヤータワーとの衝突
void Enemy::CollisionBackToPlayerTower::operator()()
{
	//me->KnockBack(0.1f);
}

// プレイヤー味方との衝突
void Enemy::CollisionBackToPlayerAlly::operator()()
{
	auto* playerAlly = reinterpret_cast<PlayerAlly*>(me->Getter_ColObj());

	if (playerAlly->formationCurrentIndex != -1)
	{
		me->KnockBack(1.0f);
		playerAlly->Death();
	}
}
