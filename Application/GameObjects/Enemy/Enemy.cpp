#include "Enemy.h"
#include "imgui.h"
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Player/PlayerTower/PlayerTower.h"
#include "../../M/utilities/Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"
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

	// ポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);
	for (auto& towerObj : gameObjectManager->Find(Tag::kPlayerTower))
	{
		playerTowers.push_back(reinterpret_cast<PlayerTower*>(towerObj));
	}

	trans.interpolationCoe = 0.1f;

	// 初期化
	Reset();
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

	// 理想的な移動速度をセット
	SetIdealVelocity();

	// 移動
	trans.pos = trans.pos + velocity;
}

void Enemy::SetIdealVelocity()
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

	// 最終的に向かう方向ベクトル
	Vector3 lastDir;

	// プレイヤーが近ければプレイヤーを追う
	if (dirToPlayer.GetMagnitutde() < GameConstants::kEnemyRecognizeDistance)
	{
		lastDir = dirToPlayer.GetNormalized();
	}


	// 遠ければ最も近いタワーを追う
	else if (playerTowers.size() > 0)
	{
		// 最も近いタワーのインデックスを探す
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
		lastDir = dirToTowers[nearestTowerIndex].GetNormalized();
	}

	trans.lookDir = Easing::SLerp(trans.lookDir, lastDir, trans.interpolationCoe);

	// 移動
	velocity = Vector3(0.0f, 0.0f, 0.0f);
	velocity = trans.lookDir * speed;
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

