#pragma once
#include <string>
#include <cstdint>
#include "../../M/utilities/benriTemplateFunc/benriTempFunc.h"
#include "../../lowerLayer/math/vector/vector.h"

class InGameConfig;
struct InGameController;

struct GameObjectEntity
{
public:
	// データの読み込み・保存
	virtual void LoadData() = 0;
	virtual void SaveData() = 0;

	// IDのセット
	virtual void SetID(int32_t id_) { ID = id_; }

	// デバッグ描画
	virtual void DebugDraw() = 0;

	virtual void SetInGameConfig(const InGameConfig* config_) { inGameConfig = config_; }

	// Jsonパス
	std::string path;

	float GetHP() const { return hp; }

protected:

	// inGameController参照ポインタ
	InGameController* inGameController = nullptr;

	inline void ClampPosition(Vector3& worldPos_)
	{
		Vector3 clampMin = { -30,0,-30 };
		Vector3 clampMax = { 30,0,30 };

		float const adjust = 0.1f;
		Benri::AdjustMin(worldPos_.x, clampMin.x, clampMin.x + adjust);
		Benri::AdjustMax(worldPos_.x, clampMax.x, clampMax.x - adjust);

		Benri::AdjustMin(worldPos_.z, clampMin.z, clampMin.z + adjust);
		Benri::AdjustMax(worldPos_.z, clampMax.z, clampMax.z - adjust);

	}

	// ID
	int32_t ID = -1;

	// HP
	float hp = 100.0f;

	const InGameConfig* inGameConfig = nullptr;
};

