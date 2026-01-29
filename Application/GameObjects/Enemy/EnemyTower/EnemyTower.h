#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/EnemyTowerModel/EnemyTowerModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectBuilding.h"

struct PlayerBullet;

struct EnemyTower :public GameObject, public GameObjectBuilding
{
#pragma region 独自部位

private:
	// 衝突弾リスト更新
	void UpdateHitBullets();
	// そのターンで衝突した弾のリスト（多重衝突防止用）
	std::vector<PlayerBullet*> hitBullets{};

public:

	// 衝突した弾をリストに追加
	void AddHitBullet(PlayerBullet* bullet);
	// その弾が既に衝突リストにあるか
	bool IsInHitBulletList(PlayerBullet* bullet);

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
	struct CollisionBackToPlayerBullet
	{
		EnemyTower* me = nullptr;
		void operator()();
		void Init(EnemyTower* object) { me = object; }
	};
	// プレイヤー弾と衝突したときのコリジョンバック
	CollisionBackToPlayerBullet collisionBackToPlayerBullet;

public:
	//使用するモデル
	std::unique_ptr<EnemyTowerModel> model;

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

	EnemyTower();

#pragma endregion

};

