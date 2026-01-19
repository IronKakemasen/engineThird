#pragma once
#include "GameObjectBehavior.h"
#include "../../Models/Shikoutei/ShikouteiModel.h"

struct Player :public GameObject
{
private:
	// 使用するモデル
	std::unique_ptr<ShikouteiModel> playerModel;

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


	Player();
};

