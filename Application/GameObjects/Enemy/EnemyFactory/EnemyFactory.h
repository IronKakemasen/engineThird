#pragma once
#include "GameObjectBehavior.h"
#include "../../../Models/EnemyFactoryModel/EnemyFactoryModel.h"

struct EnemyFactory :public GameObject
{
#pragma region 独自部位

private:


public:

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
	std::string path = "./resource/application/json/enemy/enemyFactoryData.json";

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

