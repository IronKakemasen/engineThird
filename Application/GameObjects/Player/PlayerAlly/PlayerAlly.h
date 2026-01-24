#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/PlayerAllyModel/PlayerAllyModel.h"
#include "../../../GameObjects/ObjectParent/GameObjectEntity.h"

struct Player;

struct PlayerAlly :public GameObject, public GameObjectEntity
{
#pragma region 独自部位

private:
	Player* targetPlayer = nullptr;

	void Move();

	float speed = 0.05f;

public:
	// 自分は列の何番目か(-1の時はまだたどり着いていない)
	int32_t formationCurrentIndex = -1;
	// 自分は列の何番目を目指すか
	int32_t formationTargetIndex = -1;

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
	struct CollisionBackToPlayerBullet
	{
		PlayerAlly* me = nullptr;
		void operator()();
		void Init(PlayerAlly* object) { me = object; }
	};
	// PlayerBulletと衝突したときのコリジョンバック
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


	PlayerAlly();

#pragma endregion
};

