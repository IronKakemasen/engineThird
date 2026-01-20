#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerAllyModel/PlayerAllyModel.h"

struct Player;

struct PlayerAlly :public GameObject
{
public:
	void SetTargetPlayer(Player* player_) { targetPlayer = player_; };


private:
	Player* targetPlayer = nullptr;

	void Move();

private:
	// 使用するモデル
	std::unique_ptr<PlayerAllyModel> model;

	//コリジョンバック用の関数オブジェクト
	struct CollisionBackToEnemy
	{
		PlayerAlly* me = nullptr;
		void operator()();
		void Init(PlayerAlly* object) { me = object; }
	};
	// Enemyと衝突したときのコリジョンバック
	CollisionBackToEnemy collisionBackToEnemy;


	void SaveData();

	float frameCount = 0;

	Vector3 translate = { 0.0f,0.0f,0.0f };
	Vector3 velocity = { 0.0f,0.0f,0.0f };
	Vector3 acceleration = { 0.0f,0.0f,0.0f };

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


	PlayerAlly();
};

