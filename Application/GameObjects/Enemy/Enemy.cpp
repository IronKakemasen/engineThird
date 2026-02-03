#include "Enemy.h"
#include "imgui.h"
#include <array>
#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Player/PlayerTower/PlayerTower.h"
#include "../../M/utilities/Json/Json.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../../Config/GameConstants.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../Config/InGameConfig.h"
#include "../../Systems/DamageDisplay/DamageDisplay.h"
#include "../../Scenes/InGameScene/InGameScene.h"
#include "../../M/utilities/vectorAndMatrix/vectorAndMatrix.h"

Enemy::Enemy()
{
	// モデルのインスタンス化
	model.reset(new EnemyModel);

	// HPバーのスプライト初期化
	HPBarBackSprite = std::make_unique<Sprite>();
	HPBarBackSprite->Initialize(50.0f, 10.0f,
			{ },
			M::GetInstance()->GetTexIndex(TextureTag::kWhite2x2),
			{ 100,100,255,255 });

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
	for (auto* it : model->models)
	{
		it->GetAppearance(0)->metalic = InGameScene::metalicCommon;
		it->GetAppearance(0)->roughness = InGameScene::roughnessCommon;
	}

	// identityTableにセットされている通りに、identityを定める
	// タグ、名前、衝突判定マスキング
	SetIdentity(Tag::kEnemy);
	// 円形コリジョンをアタッチ
	SetCircleCollision(inGameConfig->enemyCollisonSize);
	// 衝突判定をするかどうか定める
	SwitchCollisionActivation(true);

	// inGameControllerポインタ取得
	inGameController = reinterpret_cast<InGameController*>(gameObjectManager->Find(Tag::kInGameController)[0]);
	// プレイヤーポインタ取得
	targetPlayer = reinterpret_cast<Player*>(gameObjectManager->Find(Tag::kPlayer)[0]);
	// タワーポインタ取得
	for (auto& towerObj : gameObjectManager->Find(Tag::kPlayerTower))
	{
		playerTowers.push_back(reinterpret_cast<PlayerTower*>(towerObj));
	}

	// collisionBackの初期化
	collisionBackToPlayer.Init(this);
	collisionBackToPlayerBullet.Init(this);
	collisionBackToPlayerTower.Init(this);
	collisionBackToPlayerAlly.Init(this);

	// 補完係数設定
	trans.interpolationCoe = 0.1f;
}

void Enemy::AddHitBullet(PlayerBullet* bullet)
{
	hitBullets.push_back(bullet);
}

bool Enemy::IsInHitBulletList(PlayerBullet* bullet)
{
	for (auto& hitBullet : hitBullets)
	{
		if (hitBullet == bullet)
		{
			return true;
		}
	}
	return false;
}

void Enemy::Spawn(Vector3 pos)
{
	// 有効化
	SetStatus(Status::kActive);
	
	// 初期座標設定
	trans.pos = pos;
	
	// 体力初期化
	hp = inGameConfig->enemyMaxHP;

	// 初期向きを最近のターゲット方向に設定
	LookAtTarget();

	// アニメーション状態初期化
	nextAnimationState = EnemyAnimationState::kMove;

	// 後ろ方向きにノックバック
	Vector3 knickBackDir = trans.lookDir * -1.0f;
	Vector2 knickBackDir2D = Vector2(knickBackDir.x, knickBackDir.z).GetNormalized();
	// inGameConfig->enemyKnockBackRandomAngleOfSpawnの範囲で左右にランダム回転
	float maxAngle = inGameConfig->enemyKnockBackRandomAngleOfSpawn;
	float theta = ((rand() / float(RAND_MAX)) * maxAngle - (maxAngle / 2.0f)) * (3.1415f / 180.0f);
	//float theta = ((rand() / float(RAND_MAX)) * maxAngle - (maxAngle / 2.0f)) * 3.1415f;
	knickBackDir2D = Vector2(
		knickBackDir2D.x * cosf(theta) - knickBackDir2D.y * sinf(theta),
		knickBackDir2D.x * sinf(theta) + knickBackDir2D.y * cosf(theta)
	);
	knickBackDir = Vector3(knickBackDir2D.x, 0.0f, knickBackDir2D.y);
	KnockBack(knickBackDir, inGameConfig->enemyKnockBackPowerOfSpawn);

	// コリジョンサイズ設定
	SetCircleCollision(inGameConfig->enemyCollisonSize);
}

float Enemy::GetAttackPower()
{
	return inGameConfig->enemyAttackPower;
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
}
void Enemy::SaveData()
{
}

void Enemy::Update()
{
	//モデルの更新処理
	model->Update(int(currentAnimationState), animationCounter.count);

	// アニメーション更新
	UpdateAnimationState();

	// 移動処理
	MoveToTarget();

	// ノックバック処理
	MoveKnockBack();

	// 衝突弾リスト更新
	UpdateHitBullets();

	Vector3 finalVelocity = moveVelocity + knockBackVelocity;
	trans.pos = trans.pos + finalVelocity;
}

void Enemy::UpdateAnimationState()
{
	// 状態が変化したらカウンター初期化
	if (nextAnimationState != currentAnimationState)
	{
		switch (nextAnimationState)
		{
		case Enemy::EnemyAnimationState::kMove:
			animationCounter.Initialize(5.0f);
			break;
		case Enemy::EnemyAnimationState::kDead:
			animationCounter.Initialize(1.0f);
			break;
		default:
			break;
		}
		currentAnimationState = nextAnimationState;
	}

	animationCounter.Add();

	if (animationCounter.count >= 1.0f)
	{
		switch (currentAnimationState)
		{
		case Enemy::EnemyAnimationState::kMove:
			break;
		case Enemy::EnemyAnimationState::kDead:
			SetStatus(Status::kInActive);
			break;
		default:
			break;
		}
	}
}

void Enemy::MoveToTarget()
{
	if (currentAnimationState != EnemyAnimationState::kMove)
	{
		moveVelocity = Vector3(0.0f, 0.0f, 0.0f);
		return;
	}

	// ターゲットまでの方向ベクトルを計算
	std::array<Vector3, GameConstants::kMaxPlayerTowers> dirToTowers{};
	for (size_t i = 0; i < playerTowers.size(); ++i)
	{
		dirToTowers[i] = Vector3(0.0f, 0.0f, 9999.9f);
		if (playerTowers[i]->GetStatus() == Status::kActive)
		{
			dirToTowers[i] = playerTowers[i]->Getter_Trans()->pos - trans.pos;

		}
	}
  
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
	if (nearestTowerIndex < 0 || nearestTowerIndex >= playerTowers.size())
	{
		return;
	}
	Vector3 lastDir = dirToTowers[nearestTowerIndex].GetNormalized();

	// 補完
	trans.lookDir = Easing::SLerp(trans.lookDir, lastDir, trans.interpolationCoe);

	// エネミー ⇒ 塔　移動ベクトル
	moveVelocity = trans.lookDir.GetNormalized() * inGameConfig->enemySpeed;
}

void Enemy::LookAtTarget()
{
	if (currentAnimationState != EnemyAnimationState::kMove) return;

	// ターゲットまでの方向ベクトルを計算
	std::array<Vector3, GameConstants::kMaxPlayerTowers> dirToTowers{};
	for (size_t i = 0; i < GameConstants::kMaxPlayerTowers; ++i)
	{
		dirToTowers[i] = Vector3(9999.9f, 9999.9f, 9999.9f);
		if (playerTowers[i]->GetStatus() == Status::kActive)
			dirToTowers[i] = playerTowers[i]->Getter_Trans()->pos - trans.pos;
	}
	Vector3 dirToPlayer = targetPlayer->Getter_Trans()->GetWorldPos() - trans.GetWorldPos();

	// 最も近いタワーを追う
	size_t nearestTowerIndex = 0;
	float nearestDistance = dirToTowers[0].GetMagnitutde();
	for (size_t i = 1; i < GameConstants::kMaxPlayerTowers; ++i)
	{
		float distance = dirToTowers[i].GetMagnitutde();
		if (distance < nearestDistance)
		{
			nearestDistance = distance;
			nearestTowerIndex = i;
		}
	}
	if (nearestTowerIndex < 0 || nearestTowerIndex >= playerTowers.size())
	{
		return;
	}
	Vector3 lastDir = dirToTowers[nearestTowerIndex].GetNormalized();
	// ランダムに回転
	lastDir.x += ((rand() / float(RAND_MAX)) * 0.4f - 0.2f);

	trans.lookDir = lastDir;
}

void Enemy::MoveKnockBack()
{
	knockBackVelocity = knockBackVelocity * inGameConfig->enemyKnockBackDampingRate;
}

void Enemy::KnockBack(Vector3 dir, float power)
{
	// dir を 2D化して正規化
	Vector2 dir2D(dir.x, dir.z);
	if (dir2D.GetMagnitutde() <= 0.0001f) return;
	dir2D = dir2D.GetNormalized();

	// 見た目の向きもノックバック方向に合わせる
	//trans.lookDir = Vector3(dir2D.x, 0.0f, dir2D.y);

	// ノックバック
	knockBackVelocity = Vector3(dir2D.x, 0.0f, dir2D.y) * power;

	//Vector2 randomRotateVec = Vector2(dir.x, dir.z);
	//float deg = (rand() / float(RAND_MAX)) * 20.0f - 10.0f; // -2° ～ +2°
	//float theta = deg * (3.1415f / 180.0f);
	//randomRotateVec = Vector2(
	//	dir.x * cosf(theta) - dir.z * sinf(theta),
	//	dir.x * sinf(theta) + dir.z * cosf(theta)
	//).GetNormalized();
	//trans.lookDir = Vector3(randomRotateVec.x, 0.0f, randomRotateVec.y);
	// 
	//knockBackVelocity = (trans.lookDir * -1) * power * 1.0f;

	//Vector2 randomRotateVec = Vector2(trans.lookDir.x, trans.lookDir.z);
	//float deg = (rand() / float(RAND_MAX)) * 20.0f - 10.0f; // -2° ～ +2°
	//float theta = deg * (3.1415f / 180.0f);
	//randomRotateVec = Vector2(
	//	trans.lookDir.x * cosf(theta) - trans.lookDir.z * sinf(theta),
	//	trans.lookDir.x * sinf(theta) + trans.lookDir.z * cosf(theta)
	//).GetNormalized();
	//trans.lookDir = Vector3(randomRotateVec.x, 0.0f, randomRotateVec.y);
	//
	//knockBackVelocity = (trans.lookDir * -1) * power * 1.0f;
}

void Enemy::UpdateHitBullets()
{
	for (size_t i = 0; i < hitBullets.size(); ++i)
	{
		if (hitBullets[i]->GetStatus() == Status::kInActive)
		{
			hitBullets.erase(hitBullets.begin() + i);
			--i;
		}
	}
}


void Enemy::Draw(Matrix4* vpMat_)
{
	// モデルの描画
	model->Draw(vpMat_);
}

void Enemy::DrawHpBar(Matrix4* vpMat_)
{
	Matrix4 orth = Get_Orthographic3D(0.0f, CommonV::kWindow_W, 0.0f, CommonV::kWindow_H);
	Vector2 pos = ConvertToScreen(trans.GetWorldPos(), *vpMat_);

	HPBarBackSprite->GetAppearance()->trans.pos = Vector3(pos.x, pos.y + 50.0f, 0.0f);
	HPBarBackSprite->Draw(&orth);
}

void Enemy::DebugDraw(){}

// プレイヤーとの衝突
void Enemy::CollisionBackToPlayer::operator()()
{
	//auto* player = reinterpret_cast<Player*>(me->Getter_ColObj());
	//
	//// 後ろ方向きにノックバック
	//Vector3 knickBackDir = me->trans.lookDir * -1.0f;
	//Vector2 knickBackDir2D = Vector2(knickBackDir.x, knickBackDir.z).GetNormalized();
	//// inGameConfig->enemyKnockBackRandomAngleOfSpawnの範囲で左右にランダム回転
	//float maxAngle = 30.0f;
	//float theta = ((rand() / float(RAND_MAX)) * maxAngle - (maxAngle / 2.0f)) * (3.1415f / 180.0f);
	//knickBackDir2D = Vector2(
	//	knickBackDir2D.x * cosf(theta) - knickBackDir2D.y * sinf(theta),
	//	knickBackDir2D.x * sinf(theta) + knickBackDir2D.y * cosf(theta)
	//);
	//knickBackDir = Vector3(knickBackDir2D.x, 0.0f, knickBackDir2D.y);
	//
	//// ノックバック付与
	//me->KnockBack(knickBackDir, me->inGameConfig->enemyKnockBackPowerToPlayer);
}

// プレイヤー弾との衝突
void Enemy::CollisionBackToPlayerBullet::operator()()
{
	auto* bullet = reinterpret_cast<PlayerBullet*>(me->Getter_ColObj());

	// 既に衝突済みなら何もしない
	if (me->IsInHitBulletList(bullet)) return;

	// 既に死んでいるなら何もしない
	if (me->hp <= 0.0f) return;

	// 衝突リストに追加
	me->AddHitBullet(bullet);

	// ノックバック方向計算
	Vector3 knickBackDir = me->trans.lookDir * -1.0f;
	Vector2 knickBackDir2D = Vector2(knickBackDir.x, knickBackDir.z).GetNormalized();
	// inGameConfig->enemyKnockBackRandomAngleOfSpawnの範囲で左右にランダム回転
	float maxAngle = 30.0f;
	float theta = ((rand() / float(RAND_MAX)) * maxAngle - (maxAngle / 2.0f)) * (3.1415f / 180.0f);
	knickBackDir2D = Vector2(
		knickBackDir2D.x * cosf(theta) - knickBackDir2D.y * sinf(theta),
		knickBackDir2D.x * sinf(theta) + knickBackDir2D.y * cosf(theta)
	);
	knickBackDir = Vector3(knickBackDir2D.x, 0.0f, knickBackDir2D.y);

	// ノックバック付与
	me->KnockBack(knickBackDir, me->inGameConfig->enemyKnockBackPowerToBullet);

	// ダメージ表示
	DamageDisplay::Get()->Activate(bullet->GetAttackPower(), me->Getter_Trans()->GetWorldPos(),
		1.0f, { 255,255,0 });

	// ダメージ処理
	me->hp = me->hp - bullet->GetAttackPower();
	// 死亡した時
	if (me->hp <= 0.0f)
	{
		//me->SetStatus(Status::kInActive);
		me->nextAnimationState = Enemy::EnemyAnimationState::kDead;

		//if (bullet->isMaximized == true)
			me->targetPlayer->SpawnAlly(me->trans.pos);
	}
}

// プレイヤータワーとの衝突
void Enemy::CollisionBackToPlayerTower::operator()()
{
	auto* playerTower = reinterpret_cast<PlayerTower*>(me->Getter_ColObj());


	// ノックバック方向計算
	Vector3 knickBackDir = me->trans.lookDir * -1.0f;
	Vector2 knickBackDir2D = Vector2(knickBackDir.x, knickBackDir.z).GetNormalized();
	// inGameConfig->enemyKnockBackRandomAngleOfSpawnの範囲で左右にランダム回転
	float maxAngle = 30.0f;
	float theta = ((rand() / float(RAND_MAX)) * maxAngle - (maxAngle / 2.0f)) * (3.1415f / 180.0f);
	knickBackDir2D = Vector2(
		knickBackDir2D.x * cosf(theta) - knickBackDir2D.y * sinf(theta),
		knickBackDir2D.x * sinf(theta) + knickBackDir2D.y * cosf(theta)
	);
	knickBackDir = Vector3(knickBackDir2D.x, 0.0f, knickBackDir2D.y);

	// ノックバック付与
	me->KnockBack(knickBackDir, me->inGameConfig->enemyKnockBackPowerToPlayerTower);
}

// プレイヤー味方との衝突
void Enemy::CollisionBackToPlayerAlly::operator()()
{
	if (me->currentAnimationState != EnemyAnimationState::kMove) return;

	auto* playerAlly = reinterpret_cast<PlayerAlly*>(me->Getter_ColObj());

	if (playerAlly->GetCurrentState() == PlayerAlly::State::kLocked || 
		playerAlly->GetCurrentState() == PlayerAlly::State::kFormed ||
		playerAlly->GetCurrentState() == PlayerAlly::State::kDeathBoom)
	{
		// ノックバック方向計算
	// ノックバック方向計算
		Vector3 knickBackDir = me->trans.lookDir * -1.0f;
		Vector2 knickBackDir2D = Vector2(knickBackDir.x, knickBackDir.z).GetNormalized();
		// inGameConfig->enemyKnockBackRandomAngleOfSpawnの範囲で左右にランダム回転
		float maxAngle = 30.0f;
		float theta = ((rand() / float(RAND_MAX)) * maxAngle - (maxAngle / 2.0f)) * (3.1415f / 180.0f);
		knickBackDir2D = Vector2(
			knickBackDir2D.x * cosf(theta) - knickBackDir2D.y * sinf(theta),
			knickBackDir2D.x * sinf(theta) + knickBackDir2D.y * cosf(theta)
		);
		knickBackDir = Vector3(knickBackDir2D.x, 0.0f, knickBackDir2D.y);

		// ノックバック付与
		me->KnockBack(knickBackDir, me->inGameConfig->enemyKnockBackPowerToAlly);
	}
}
