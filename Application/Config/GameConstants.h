#pragma once
#include <cstddef>

namespace GameConstants
{
	// 最大エネミー数
	inline constexpr size_t kMaxEnemies = 10;

	// 最大味方数
	inline constexpr size_t kMaxAllies = 100;

	// 最大エネミータワー数
	inline constexpr size_t kMaxEnemyTowers = 2;

	// 最大エネミーファクトリー数
	inline constexpr size_t kMaxEnemyFactories = 2;

	// 最大プレイヤータワー数
	inline constexpr size_t kMaxPlayerTowers = 2;

	// エネミーがプレイヤーを認知する距離
	inline constexpr float kEnemyRecognizeDistance = 5.0f;

	// 味方は何フレーム遅れてついてくるか
	inline constexpr uint32_t kAllyFollowDelayFrames = 10;

	// 一旦ステージ１固定
	inline constexpr size_t kStageNumber = 1;
}

