#pragma once
#include "GameObjectBehavior.h"
#include "../../GameObjects/ObjectParent/GameObjectBuilding.h"
#include "../../Models/Shikoutei/ShikouteiModel.h"


struct Shikoutei :public GameObject, public GameObjectBuilding
{
private:
	//使用するモデル
	std::unique_ptr<ShikouteiModel> shikoModel;

	void LoadData() override;
	void SaveData() override;
	void DebugDraw() override;


public:
	void ReplaceOnMap(const int32_t stage) override;
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

	Shikoutei();
};

