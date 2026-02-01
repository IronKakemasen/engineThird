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

	/////////////// controller ///////////////
	float deadZone = 0.3f;				// コントローラーのデッドゾーン

	/////////////// collisonSize  ///////////////
	float playerCollisonSize = 1.0f;			// プレイヤー
	float playerTowerCollisonSize = 1.0f;		// プレイヤータワー
	float playerBulletCollisonSize = 1.0f;		// プレイヤー弾
	float playerAllyCollisonSize = 1.0f;		// プレイヤー味方
	float enemyCollisonSize = 1.0f;				// 敵
	float enemyTowerCollisonSize = 1.0f;		// 敵タワー
	float enemyFactoryCollisonSize = 1.0f;		// 敵工場

	//////////////////  MaxHP  //////////////////
	float playerMaxHP = 100.0f;			// プレイヤー
	float playerTowerMaxHP = 200.0f;	// プレイヤータワー
	float enemyMaxHP = 100.0f;			// 敵
	float enemyTowerMaxHP = 200.0f;		// 敵タワー
	float enemyFactoryMaxHP = 300.0f;	// 敵工場
	float playerBulletLifeTime = 3.0f;	// 弾の生命時間
	

	//////////////////  Speed  //////////////////
	float playerSpeed = 0.1f;			// プレイヤー
	float enemySpeed = 0.05f;			// 敵
	float playerBulletSpeed = 0.3f;		// プレイヤーの弾
	float playerAllySpeed = 1.5f;		// 味方(プレイヤー速度×playerAllySpeed)(列非加入時)
	

	//////////////////  Power  //////////////////
	float playerPower = 5.0f;			// プレイヤーの基本攻撃力
	float playerAllyPowerBonus = 2.0f;	// 味方を経由するごとに増える攻撃力補正値
	float playerAllySizeBonus = 0.1f;	// 味方を経由するごとに増えるサイズ補正値
	float enemyAttackPower = 5.0f;		// 敵の攻撃力

	////////////////// AutSpawn  ////////////////
	float enemySpawnInterval = 5.0f;	// 敵のスポーン間隔
	float playerAllySpawnInterval = 1.0f;// 味方のスポーン間隔
	float enemyFactoryRespawnInterval = 10.0f;	// エネミーファクトリーのリスポーン間隔
	int32_t maxAllyCount = 10;      // 最大味方数

	/////////////  KnockBack  ////////////////
	float enemyKnockBackPowerToAlly = 2.0f;		// [敵 - 味方]衝突で 敵が受けるノックバック力
	float enemyKnockBackPowerToPlayer = 0.0f;	// [敵 - プレイヤー]衝突で 敵が受けるノックバック力
	float enemyKnockBackPowerToBullet = 0.1f;	// [敵 - プレイヤー弾]衝突で 敵が受けるノックバック力
	float enemyKnockBackPowerToPlayerTower = 0.5f;// [敵 - プレイヤータワー]衝突で 敵が受けるノックバック力
	float enemyKnockBackPowerOfSpawn = 2.0f;	// スポーン時向いている方向*-1方向にノックバックさせる力
	float enemyKnockBackRandomAngleOfSpawn = 10.0f;// スポーン時ノックバックのランダム角度

	//////////////  Distance  ////////////////
	int32_t allyToAllyDelayFrames = 30;		// ally - ally 間の遅延フレーム数
	int32_t playerToAllyDelayFrames = 30;	// player - ally 間の遅延フレーム数

	/////////////  AttackGauge  ///////////////
	float playerAttackInterval = 0.5f;	// プレイヤー攻撃ゲージ回復インターバル

	////////////// Separate   //////////////
	int32_t judgeSinglePressFrame = 10;		// 単押し判定時間(フレーム数)
	// 何フレームで選択しおわるか
	int32_t separateCompleteFrame = 120;	// 選択完了までのフレーム数

private:
	std::string path = "./resource/application/json/config/inGameConfig.json";

};

