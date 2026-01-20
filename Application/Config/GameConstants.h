#pragma once
#include <cstddef>

namespace GameConstants
{
	// 最大エネミー数
    inline constexpr std::size_t kMaxEnemies = 10;

	// エネミー速度
	inline constexpr float kEnemySpeed = 0.1f;

	// エネミーがプレイヤーを認知する距離
	inline constexpr float kEnemyRecognizeDistance = 20.0f;

	// プレイヤー速度
}