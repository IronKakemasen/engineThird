#pragma once
#include <string>

class InGameConfig
{
public:
	InGameConfig();
	~InGameConfig();

	void Load();
	void Save();

	void DebugDraw();


	// プレイヤーの最大HP
	float playerMaxHP = 100.0f;
	// プレイヤーのタワーの最大HP
	float playerTowerMaxHP = 200.0f;
	// 敵の最大HP
	float enemyMaxHP = 100.0f;
	// 敵のタワーの最大HP
	float enemyTowerMaxHP = 200.0f;
	// 敵の工場の最大HP
	float enemyFactoryMaxHP = 300.0f;
	// 弾の生命時間
	float playerBulletLifeTime = 3.0f;
	

	// プレイヤーの移動速度
	float playerSpeed = 0.1f;
	// 敵の移動速度
	float enemySpeed = 0.05f;
	// 弾の速度
	float playerBulletSpeed = 0.3f;
	

	// プレイヤーのデフォルト攻撃力
	float playerAttack1Power = 5.0f;
	float playerAttack2Power = 20.0f;
	float playerAttack3Power = 30.0f;
	// 味方を経由するごとに増える攻撃力補正値
	float playerAllyPowerBonus = 2.0f;
	// 味方を経由するごとに増えるサイズ補正値
	float playerAllySizeBonus = 0.1f;
	// 敵の攻撃力
	float enemyAttackPower = 5.0f;


	// 敵の生成間隔
	float enemySpawnInterval = 5.0f;
	// 敵の味方と当たった時のノックバック力
	float enemyKnockBackPowerToAlly = 2.0f;
	// 敵の弾と当たった時のノックバック力
	float enemyKnockBackPowerToBullet1 = 0.1f;
	float enemyKnockBackPowerToBullet2 = 1.0f;
	float enemyKnockBackPowerToBullet3 = 1.5f;
	// 敵のプレイヤータワーと当たった時のノックバック力
	float enemyKnockBackPowerToPlayerTower = 0.5f;


	// ally - ally 間の遅延フレーム数
	int32_t allyToAllyDelayFrames = 30;
	// player - ally 間の遅延フレーム数
	int32_t playerToAllyDelayFrames = 30;

	// プレイヤーの攻撃ゲージ回復速度
	float playerAttackGaugeRecoverSpeed = 0.02f;

	// プレイヤーのゲージ回復インターバル
	float playerAttackGaugeRecoverInterval = 0.5f;

private:
	std::string path = "./resource/application/json/config/inGameConfig.json";

};

