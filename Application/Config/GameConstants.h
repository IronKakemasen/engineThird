#pragma once
#include <cstddef>

namespace GameConstants
{
	// 最大エネミー数
	inline constexpr size_t kMaxEnemies = 100;

	// 最大味方数
	inline constexpr size_t kMaxAllies = 100;

	// 最大エネミータワー数
	inline constexpr size_t kMaxEnemyTowers = 5;

	// 最大プレイヤータワー数
	inline constexpr size_t kMaxPlayerTowers = 5;

	// 最大エネミーファクトリー数
	inline constexpr size_t kMaxEnemyFactories = 10 + kMaxPlayerTowers;

	// 最大弾丸数
	inline constexpr size_t kMaxPlayerBullets = 12;

	// 最大ステージ数
	inline constexpr size_t kMaxStages = 5;

	// 味方は何フレーム遅れてついてくるか の MAX
	inline constexpr uint32_t kAllyFollowDelayFramesMax = 120;
}

