#include "PlayerBullet.h"
#include "../../../GameObjects/Enemy/Enemy.h"
#include "../../../GameObjects/Enemy/EnemyTower/EnemyTower.h"
#include "../../../GameObjects/Enemy/EnemyFactory/EnemyFactory.h"
#include "../../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../../Config/InGameConfig.h"
#include "../../GameObjectManager/GameObjectManager.h"
#include "../Json/Json.h"

PlayerBullet::PlayerBullet()
{
	//モデルのインスタンス化
	model.reset(new PlayerBulletModel);

	// Jsonパスの設定
	path = "./resource/application/json/player/PlayerBulletData.json";
}

void PlayerBullet::Reset()
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

void PlayerBullet::Init()
{
	// モデルの初期化
	model->Init(&trans);

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kPlayerBullet);
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->playerBulletCollisonSize);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);

	// collisionBackToEnemyの初期化
	collisionBackToEnemy.Init(this);
	collisionBackToEnemyTower.Init(this);
	collisionBackToEnemyFactory.Init(this);
	collisionBackToAlly.Init(this);
}

void PlayerBullet::SetCollisionBackTable()
{
	SetCollisionBack(Tag::kEnemy, collisionBackToEnemy);
	SetCollisionBack(Tag::kEnemyTower, collisionBackToEnemyTower);
	SetCollisionBack(Tag::kEnemyFactory, collisionBackToEnemyFactory);
	SetCollisionBack(Tag::kPlayerAlly, collisionBackToAlly);
}

void PlayerBullet::Fire(Vector3 pos, Vector3 dir, int32_t stage)
{
	// リセット
	trans.scale = Vector3(0.5f, 0.2f, 0.5f);
	// 発射
	SetStatus(GameObjectBehavior::Status::kActive);
	// 移動方向設定
	targetDir = dir;
	// 座標設定
	trans.pos = pos;
	// 何段目の攻撃か設定
	attackStage = stage;
	// 速度反映
	defaultSpeed = inGameConfig->playerBulletSpeed;
	// 生命時間反映
	defaultLifeTime = inGameConfig->playerBulletLifeTime;
	// カウンター設定
	lifeCounter.Initialize(defaultLifeTime);
	// 攻撃力リセット
	if (stage == 0)
		attackPower = inGameConfig->playerAttack1Power;
	else if (stage == 1)
		attackPower = inGameConfig->playerAttack2Power;
	else if (stage == 2)
		attackPower = inGameConfig->playerAttack3Power;
	// 味方経由攻撃力補正値設定
	allyPowerBonus = inGameConfig->playerAllyPowerBonus;
	// 味方経由サイズ補正値設定
	allySizeBonus = inGameConfig->playerAllySizeBonus;
	// コリジョンサイズ反映
	SetCircleCollision(inGameConfig->playerBulletCollisonSize);
}

// データ保存・読み込み
void PlayerBullet::LoadData()
{
	std::string key = "/ID:" + std::to_string(ID);

}
void PlayerBullet::SaveData()
{
	std::string key = "/ID:" + std::to_string(ID);

	Json::Save(path);
}


void PlayerBullet::Update()
{
	// モデル更新
	model->Update();

	// 座標更新
	trans.pos = trans.pos + (targetDir * defaultSpeed);

	// 生命カウンター更新
	lifeCounter.Add();
	if (lifeCounter.count >= 1.0f)
	{
		// 0.1以下になるまで小さくなる
		trans.scale = trans.scale * 0.5f;
		if (trans.scale.x <= 0.1f)
		{
			SetStatus(Status::kInActive);
		}
	}
}

void PlayerBullet::Draw(Matrix4* vpMat_)
{
	//モデルの描画
	model->Draw(vpMat_);
}

void PlayerBullet::DebugDraw()
{}

// エネミーとの衝突
void PlayerBullet::CollisionBackToEnemy::operator()()
{
}
// 敵塔との衝突
void PlayerBullet::CollisionBackToEnemyTower::operator()()
{
}
// 敵工場との衝突
void PlayerBullet::CollisionBackToEnemyFactory::operator()()
{
}
// 味方との衝突
void PlayerBullet::CollisionBackToAlly::operator()()
{
	auto* ally = reinterpret_cast<PlayerAlly*>(me->Getter_ColObj());
	if (ally->formationCurrentIndex == -1) return;

	me->trans.scale = me->trans.scale + Vector3{ me->allySizeBonus, 0.0f, me->allySizeBonus };
	me->attackPower += me->allyPowerBonus;
}
