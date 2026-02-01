#pragma once
#include <string>
#include <cstdint>
#include <array>
#include "../../Config/GameConstants.h"

class InGameConfig;
struct InGameController;

struct GameObjectBuilding
{
public:
	// データの読み込み・保存
	virtual void LoadData() = 0;
	virtual void SaveData() = 0;

	// マップ上に配置
	virtual void ReplaceOnMap(const int32_t stage) = 0;

	// IDのセット
	virtual void SetID(int32_t id_) { ID = id_; }

	// デバッグ描画
	virtual void DebugDraw() = 0;

	virtual void SetInGameConfig(const InGameConfig* config_) { inGameConfig = config_; }

	// Jsonパス
	std::string path;

	// inGameController参照ポインタ
	InGameController* inGameController = nullptr;


	float GetHP() const { return hp; }

protected:
	// ID
	int32_t ID = -1;

	// ステージごとのActive数
	int32_t stageActiveCounts = 0;

	// HP
	float hp = 100.0f;

	const InGameConfig* inGameConfig = nullptr;
};
