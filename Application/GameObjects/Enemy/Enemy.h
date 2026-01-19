#pragma once
#include "GameObjectBehavior.h"
#include "../../Models/EnemyModel/EnemyModel.h"

struct Enemy :public GameObject
{
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


	Enemy() {}
};

