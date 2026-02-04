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

void PlayerBullet::Fire(Vector3 pos, Vector3 dir)
{
	// リセット
	trans.scale = Vector3(0.5f, 0.2f, 0.5f);
	// マキシマイズマジック
	isMaximized = false;
	// 発射
	SetStatus(GameObjectBehavior::Status::kActive);
	// 移動方向設定
	targetDir = dir;
	// 座標設定
	trans.pos = pos;
	// 速度反映
	defaultSpeed = inGameConfig->playerBulletSpeed;
	// 寿命カウンター初期化
	lifeCounter.Initialize(inGameConfig->playerBulletLifeTime);
	// 攻撃力リセット
	attackPower = inGameConfig->playerPower;
	// コリジョンサイズ反映
	SetCircleCollision(inGameConfig->playerBulletCollisonSize);
	// 現在サイズリセット
	currentSizeBonus = 0.0f;
	//見た目用パラメーター
	model->randomRotateAddNum = Vector3{ float(rand() % 200 - 100), 
		float(rand() % 200 - 100),float(rand() % 200 - 100) }.GetNormalized();
	model->rotateSpeed = 8.0f;

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

void PlayerBullet::DrawHpBar(Matrix4* vpMat_)
{}

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
	
	// 列加入済み・ロック状態でなければ何もしない
	if (ally->GetCurrentState() != PlayerAlly::State::kFormed &&
		ally->GetCurrentState() != PlayerAlly::State::kLocked) return;

	// サイズアップ
	me->trans.scale = me->trans.scale + Vector3{ me->inGameConfig->playerAllySizeBonus, 0.0f, me->inGameConfig->playerAllySizeBonus };
	// 拡大量保存
	me->currentSizeBonus += me->inGameConfig->playerAllySizeBonus;
	// コリジョンサイズ更新
	me->SetCircleCollision(me->inGameConfig->playerBulletCollisonSize + me->currentSizeBonus);
	// 攻撃力アップ
	me->attackPower += me->inGameConfig->playerAllyPowerBonus;
	// マキシマイズマジック
	me->isMaximized = true;
	//見た目用
	me->model->rotateSpeed *= 0.85f;
}
