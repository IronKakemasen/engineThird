#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerAllyModel/PlayerAllyModel.h"
#include "../../../Models/SphereModel/SphereModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectEntity.h"

struct Player;

struct PlayerAlly :public GameObject, public GameObjectEntity
{
#pragma region 独自部位

	enum class State
	{
		// 列非加入
		kUnformed,
		// 列加入済み
		kFormed,
		// ロック状態
		kLocked,
		// 死亡爆発
		kDeathBoom,
		// 死亡状態
		kDead,
		// 初期状態
		kNone
	};

private:
	Player* targetPlayer = nullptr;

	// 列に向かって進む
	void MoveToPlayer();
	// 追従する
	void FollowPlayer();
	// その場で待機する
	void LockPosition();
	// 死亡爆発
	void DeathBoom();
	// 死亡処理
	void Death();

	// 死亡後判定を受けてからn秒後に消滅するカウンター
	Counter deathCounter;

	State currentState = State::kNone;
	State nextState = State::kNone;

public:
	// 自分はプレイヤーから何フレーム遅れているか(-1なら列未加入)
	int32_t formationCurrentIndex = -1;

	State GetCurrentState() const { return currentState; }

	void Spawn(Vector3 pos);

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
		PlayerAlly* me = nullptr;
		void operator()();
		void Init(PlayerAlly* object) { me = object; }
	};
	// Enemyと衝突したときのコリジョンバック
	CollisionBackToEnemy collisionBackToEnemy;
	struct CollisionBackToPlayerBullet
	{
		PlayerAlly* me = nullptr;
		void operator()();
		void Init(PlayerAlly* object) { me = object; }
	};
	// PlayerBulletと衝突したときのコリジョンバック
	CollisionBackToPlayerBullet collisionBackToPlayerBullet;
	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayer
	{
		PlayerAlly* me = nullptr;
		void operator()();
		void Init(PlayerAlly* object) { me = object; }
	};
	// Enemyと衝突したときのコリジョンバック
	CollisionBackToPlayer collisionBackToPlayer;

public:
	// 使用するモデル
	std::unique_ptr<PlayerAllyModel> model;
	std::unique_ptr<SphereModel> boomModel;

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


	PlayerAlly();

#pragma endregion
};

