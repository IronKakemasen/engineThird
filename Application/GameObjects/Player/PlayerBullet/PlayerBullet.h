#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerBulletModel/PlayerBulletModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectBuilding.h"

struct Enemy;
struct EnemyTower;
struct EnemyFactory;
struct PlayerAlly;

struct PlayerBullet :public GameObject, public GameObjectBuilding
{
#pragma region 独自部位

private:
	Vector3 targetDir = {};
	float defaultSpeed = 0.1f;

	// 生命カウンター(0になると急激に小さくなり始める)
	Counter lifeCounter;

	// 攻撃力
	float attackPower = 0.0f;
	float currentSizeBonus = 0.0f;


public:

	// 味方を経由して強化済か
	bool isMaximized = false;

	// 発射  (pos : 発射位置, dir : 発射方向)
	void Fire(Vector3 pos, Vector3 dir);

	float GetAttackPower() const { return attackPower; }

#pragma	endregion

#pragma region 共通部位

public:
	// データの読み込み・保存
	void LoadData() override;
	void SaveData() override;

	// デバッグ描画
	void DebugDraw() override;

#pragma endregion

#pragma region 基盤部位

private:

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToEnemy
	{
		PlayerBullet* me = nullptr;
		void operator()();
		void Init(PlayerBullet* object) { me = object; }
	};
	// 敵と衝突したときのコリジョンバック
	CollisionBackToEnemy collisionBackToEnemy;
	struct CollisionBackToEnemyTower
	{
		PlayerBullet* me = nullptr;
		void operator()();
		void Init(PlayerBullet* object) { me = object; }
	};
	// 敵塔と衝突したときのコリジョンバック
	CollisionBackToEnemyTower collisionBackToEnemyTower;
	struct CollisionBackToEnemyFactory
	{
		PlayerBullet* me = nullptr;
		void operator()();
		void Init(PlayerBullet* object) { me = object; }
	};
	// 敵工場と衝突したときのコリジョンバック
	CollisionBackToEnemyFactory collisionBackToEnemyFactory;
	struct CollisionBackToAlly
	{
		PlayerBullet* me = nullptr;
		void operator()();
		void Init(PlayerBullet* object) { me = object; }
	};
	// 味方と衝突したときのコリジョンバック
	CollisionBackToAlly collisionBackToAlly;

public:

	//使用するモデル
	std::unique_ptr<PlayerBulletModel> model;

	//↓ゲームオブジェクトマネージャーに登録すれば呼び出す必要なし↓
	// 更新処理。
	// GameObject::StateがinActiveの場合は呼び出されない
	virtual void Update()override;
	//初期化処理
	virtual void Init() override;
	//リセット処理（ゲームループ等シーンのリセットに呼び出す）
	virtual void Reset() override;
	//描画処理.StateがinActiveの場合は呼び出されない
	virtual void Draw(Matrix4* vpMat_)override;
	//コリジョンをセットする関数
	virtual void SetCollisionBackTable()override;

	PlayerBullet();

#pragma endregion

};

