#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/EnemyFactoryModel/EnemyFactoryModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectBuilding.h"

struct Enemy;

struct EnemyFactory :public GameObject, public GameObjectBuilding
{
#pragma region 独自部位

private:

	// 参照ポインタ
	std::vector<Enemy*> enemies{};

	Counter timer;

	float spawnInterval = 20.0f;

public:

	void SpawnEnemy();

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
	//使用するモデル
	std::unique_ptr<EnemyFactoryModel> model;

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToPlayerBullet
	{
		EnemyFactory* me = nullptr;
		void operator()();
		void Init(EnemyFactory* object) { me = object; }
	};
	// プレイヤー弾と衝突したときのコリジョンバック
	CollisionBackToPlayerBullet collisionBackToPlayerBullet;

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

	EnemyFactory();

#pragma endregion
};

