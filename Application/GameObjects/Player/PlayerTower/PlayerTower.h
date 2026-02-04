#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerTowerModel/PlayerTowerModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectBuilding.h"
#include "../../BuildingsManager/BuildingsManager.h"
#include "../../../Models/CircleModel/CircleModel.h"

struct PlayerTower :public GameObject, public GameObjectBuilding
{
	enum class EnemyTowerAnimationState
	{
		kIdle,
		kDamage,
		kDead,
	};

#pragma region 独自部位

private:
	////// アニメーション処理  //////
	void UpdateAnimationState();
	EnemyTowerAnimationState currentAnimationState = EnemyTowerAnimationState::kIdle;
	EnemyTowerAnimationState nextAnimationState = EnemyTowerAnimationState::kIdle;
	Counter animationCounter;

public:


#pragma endregion

#pragma region 共通部位

public:
	// データの読み込み・保存
	void LoadData() override;
	void SaveData() override;

	// マップに配置
	void ReplaceOnMap(const int32_t stage) override;

	// デバッグ描画
	void DebugDraw() override;

	// BuildingsManagerセット
	void SetBuildingsManager(BuildingsManager* manager_) override
	{
		buildingsManager = manager_;
		buildingsManager->SetPlayerTower(this);
	}

	int32_t tempStageNumber = -1;

#pragma endregion

#pragma region 基盤部位

private:

	std::unique_ptr<CircleModel> circleModel;

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToEnemy
	{
		PlayerTower* me = nullptr;
		void operator()();
		void Init(PlayerTower* object) { me = object; }
	};
	// プレイヤー弾と衝突したときのコリジョンバック
	CollisionBackToEnemy collisionBackToEnemy;

public:
	//使用するモデル
	std::unique_ptr<PlayerTowerModel> model;

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
	// HPバー表示
	virtual void DrawHpBar(Matrix4* vpMat_) override;
	//コリジョンをセットする関数
	virtual void SetCollisionBackTable()override;

	PlayerTower();

#pragma endregion
};

