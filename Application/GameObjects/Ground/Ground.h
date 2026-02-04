#pragma once
#include "GameObjectBehavior.h"
#include "../../Models/GroundPlane/GroundPlane.h"
#include "../../GameObjects/ObjectParent/GameObjectBuilding.h"

struct Ground :public GameObject, public GameObjectBuilding
{
private:

	void LoadData()override;
	void SaveData()override;
	int32_t tempStageNumber = -1;


public:
	void DebugDraw()override;

	//使用するモデル
	std::unique_ptr<GroundPlane> groundPlane;
	void ReplaceOnMap(const int32_t stage)override;


	void ClampPosition(Vector3& worldPos_)
	{
		Vector3 clampMin = { -30.0f * trans.scale.x,0,-30.0f * trans.scale.z };
		Vector3 clampMax = { 30.0f * trans.scale.x,0,30.0f * trans.scale.z };

		float const adjust = 0.1f;
		Benri::AdjustMin(worldPos_.x, clampMin.x, clampMin.x + adjust);
		Benri::AdjustMax(worldPos_.x, clampMax.x, clampMax.x - adjust);

		Benri::AdjustMin(worldPos_.z, clampMin.z, clampMin.z + adjust);
		Benri::AdjustMax(worldPos_.z, clampMax.z, clampMax.z - adjust);
	}

	// inGameController参照ポインタ
	InGameController* inGameController = nullptr;


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

	Ground();
};

