#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerTowerModel/PlayerTowerModel.h"

struct PlayerTower :public GameObject
{
private:
	//使用するモデル
	std::unique_ptr<PlayerTowerModel> model;

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

	PlayerTower();
};

