#pragma once
#include <cstddef>

namespace GameConstants
{
	// 最大エネミー数
	inline constexpr size_t kMaxEnemies = 10;

	// 最大味方数
	inline constexpr size_t kMaxAllies = 10;

	// 最大エネミータワー数
	inline constexpr size_t kMaxEnemyTowers = 2;

	// 最大エネミーファクトリー数
	inline constexpr size_t kMaxEnemyFactories = 2;

	// 最大プレイヤータワー数
	inline constexpr size_t kMaxPlayerTowers = 2;

	// エネミー速度
	inline constexpr float kEnemySpeed = 0.1f;

	// エネミーがプレイヤーを認知する距離
	inline constexpr float kEnemyRecognizeDistance = 5.0f;

	// プレイヤー速度
	inline constexpr float kPlayerSpeed = 0.2f;

	// 味方は何フレーム遅れてついてくるか
	inline constexpr uint32_t kAllyFollowDelayFrames = 10;
}