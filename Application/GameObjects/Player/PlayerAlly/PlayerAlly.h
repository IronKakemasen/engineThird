#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerAllyModel/PlayerAllyModel.h"

struct Player;

struct PlayerAlly :public GameObject
{
#pragma region 独自部位

private:
	Player* targetPlayer = nullptr;

	void Move();

public:
	void SetTargetPlayer(Player* player_) { targetPlayer = player_; };

#pragma	endregion

#pragma region 共通部位

public:
	// データの読み込み・保存
	void LoadData();
	void SaveData();

	// IDのセット
	void SetID(int32_t id_) { ID = id_; }

	// デバッグ描画
	void DebugDraw();

private:
	// ID
	int32_t ID = -1;

	// Json保存パス
	std::string path = "./resource/application/json/player/playerAllyData.json";

#pragma endregion

#pragma region 基盤部位

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

#pragma endregion
};

