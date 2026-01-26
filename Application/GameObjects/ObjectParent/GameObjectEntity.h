#pragma once
#include <string>
#include <cstdint>

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

	// inGameController参照ポインタ
	InGameController* inGameController = nullptr;

protected:
	// ID
	int32_t ID = -1;

	// HP
	float hp = 100.0f;

	const InGameConfig* inGameConfig = nullptr;
};

