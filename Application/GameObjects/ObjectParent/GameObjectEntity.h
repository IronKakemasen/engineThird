#pragma once
#include <string>
#include <cstdint>
#include "Sprite.h"
#include "../../M/utilities/benriTemplateFunc/benriTempFunc.h"
#include "../../lowerLayer/math/vector/vector.h"
#include "../../Config/InGameConfig.h"

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

	// inGameConfigセット
	virtual void SetInGameConfig(const InGameConfig* config_) { inGameConfig = config_; }

	// HPバー表示
	virtual void DrawHpBar(Matrix4* vpMat_) = 0;

	// Jsonパス
	std::string path;

	float GetHP() const { return hp; }

protected:

	// inGameController参照ポインタ
	InGameController* inGameController = nullptr;


	// ID
	int32_t ID = -1;

	// HP
	float hp = 100.0f;
	std::unique_ptr<Sprite> HPBarBackSprite;
	std::unique_ptr<Sprite> HPBarSprite;

	const InGameConfig* inGameConfig = nullptr;
};

