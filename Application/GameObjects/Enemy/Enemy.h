#pragma once
#include "GameObjectBehavior.h"
#include "../../GameObjects/ObjectParent/GameObjectEntity.h"
#include "../../Models/EnemyModel/EnemyModel.h"
#include "../../Config/GameConstants.h"
#include <span>

struct Player;
struct PlayerTower;

struct Enemy :public GameObject , public GameObjectEntity
{
#pragma region 独自部位

private:
	// ターゲット方向に移動
	void MoveToTarget();

	// ノックバック方向に移動
	void MoveKnockBack();

	// ノックバック関数(float power:ノックバックの強さ)
	void KnockBack(float power);

	// 最終的な速度
	Vector3 velocity{};
	// ノックバック用速度
	Vector3 knockBackVelocity{};
	// 移動速度
	Vector3 moveVelocity{};

	float speed = 0.05f;

	// 参照ポインタ
	std::vector<PlayerTower*> playerTowers{};
	Player* targetPlayer = nullptr;

public:
	// ポインタのセット
	void SetTargetTower(PlayerTower* tower) { playerTowers.push_back(tower); };
	void SetTargetPlayer(Player* player_) { targetPlayer = player_; };

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
	// 使用するモデル
	std::unique_ptr<EnemyModel> model;

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayer
	{
		Enemy* me = nullptr;
		void operator()();
		void Init(Enemy* object) { me = object; }
	};
	// playerと衝突したときのコリジョンバック
	CollisionBackToPlayer collisionBackToPlayer;
	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayerBullet
	{
		Enemy* me = nullptr;
		void operator()();
		void Init(Enemy* object) { me = object; }
	};
	// playerBulletと衝突したときのコリジョンバック
	CollisionBackToPlayerBullet collisionBackToPlayerBullet;
	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayerTower
	{
		Enemy* me = nullptr;
		void operator()();
		void Init(Enemy* object) { me = object; }
	};
	// playerTowerと衝突したときのコリジョンバック
	CollisionBackToPlayerTower collisionBackToPlayerTower;
	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayerAlly
	{
		Enemy* me = nullptr;
		void operator()();
		void Init(Enemy* object) { me = object; }
	};
	// playerAllyと衝突したときのコリジョンバック
	CollisionBackToPlayerAlly collisionBackToPlayerAlly;

public:
	//↓ゲームオブジェクトマネージャーに登録すれば呼び出す必要なし↓
	// 更新処理 (GameObject::StateがinActiveの場合は呼び出されない)
	virtual void Update()override;
	// 初期化処理
	virtual void Init() override;
	// リセット処理（ゲームループ等シーンのリセットに呼び出す）
	virtual void Reset() override;
	// 描画処理.StateがinActiveの場合は呼び出されない
	virtual void Draw(Matrix4* vpMat_)override;
	// コリジョンをセットする関数
	virtual void SetCollisionBackTable()override;


	Enemy();

#pragma endregion
};

