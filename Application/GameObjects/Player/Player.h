#pragma once
#include "GameObjectBehavior.h"
#include "../../Models/PlayerModel/PlayerModel.h"
#include "../../Config/GameConstants.h"
#include <array>

struct Player :public GameObject
{

private:
	// 移動処理
	void Move();
	bool isMoving = false;
	// 座標保存処理
	void SavePos();


	// 味方の存在フラグ[最大味方数]
	std::array<bool, GameConstants::kMaxAllies> allyExistenceFlags = {};
	// 自身の座標履歴[最大味方数 * 味方追従遅延フレーム数]
	std::array<Vector3, GameConstants::kMaxAllies* GameConstants::kAllyFollowDelayFrames> posHistory = {};
	size_t headIndex = 0;

	uint32_t emptyAllyIndex = 0;

public:
	Vector3 GetAllyTargetPos(size_t allyIndex);
	uint32_t GetNextEmptyAllyIndex();

private:
	// 使用するモデル
	std::unique_ptr<PlayerModel> model;

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToEnemy
	{
		Player* me = nullptr;
		void operator()();
		void Init(Player* object) { me = object; }
	};
	// Enemyと衝突したときのコリジョンバック
	CollisionBackToEnemy collisionBackToEnemy;


	void SaveData();

	float frameCount = 0;

public:
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


	Player();
};

