#pragma once
#include <cstddef>

#define StageCount 0

namespace GameConstants
{
	// 最大エネミー数
	inline constexpr size_t kMaxEnemies = 10;

	// 最大味方数
	inline constexpr size_t kMaxAllies = 100;

	// 最大エネミータワー数
	inline constexpr size_t kMaxEnemyTowers = 5;

	// 最大プレイヤータワー数
	inline constexpr size_t kMaxPlayerTowers = 5;

	// 最大エネミーファクトリー数
	inline constexpr size_t kMaxEnemyFactories = 10 + kMaxPlayerTowers;

	// 最大ステージ数
	inline constexpr size_t kMaxStages = 5;


	// エネミーがプレイヤーを認知する距離
	inline constexpr float kEnemyRecognizeDistance = 5.0f;

	// 味方は何フレーム遅れてついてくるか
	inline constexpr uint32_t kAllyFollowDelayFrames = 10;
}

