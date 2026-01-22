#pragma once
#include <string>
#include <cstdint>

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

protected:
	// ID
	int32_t ID = -1;

	// Jsonパス
	std::string path;
};

