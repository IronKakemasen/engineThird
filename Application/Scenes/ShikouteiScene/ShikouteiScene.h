#pragma once
#include "SceneBehavior.h"
#include <array>
#include <vector>
#include "../../Config/GameConstants.h"
#include "../../GameObjects/Shikoutei/Shikoutei.h"
#include "../../GameObjects/ExampleTyan/ExampleTyan.h"

#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Player/PlayerTower/PlayerTower.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../GameObjects/Enemy/Enemy.h"
#include "../../GameObjects/Enemy/EnemyTower/EnemyTower.h"
#include "../../GameObjects/Enemy/EnemyFactory/EnemyFactory.h"
#include "../../GameObjects/InGameController/InGameController.h"
#include "../../Cameras/MainCamera/MainCamera.h"
#include "../../engineCore/Light/RectLight/RectLight.h"
#include "../../Config/InGameConfig.h"

class ShikouteiScene final : public Scene
{
	//そのシーンのカメラのトランスフォームをいただく
	MainCamera mainCamera;

	//使用するゲームオブジェクト
	std::unique_ptr<Player> player;
	std::array<std::unique_ptr<PlayerTower>, GameConstants::kMaxPlayerTowers> playerTowers;
	std::array<std::unique_ptr<PlayerAlly>, GameConstants::kMaxAllies> allies;
	std::array<std::unique_ptr<Enemy>, GameConstants::kMaxEnemies> enemies;
	std::array<std::unique_ptr<EnemyTower>, GameConstants::kMaxEnemyTowers> enemyTowers;
	std::array<std::unique_ptr<EnemyFactory>, GameConstants::kMaxEnemyFactories> enemyFactories;
	std::array<std::unique_ptr<PlayerBullet>, GameConstants::kMaxPlayerBullets> playerBullets;
	std::unique_ptr<InGameController> inGameController;
	std::unique_ptr<InGameConfig> inGameConfig;

	MQuad quad;
	Sprite sprite;
	Sprite atlasNumber;

	void AdaptToPostEffect();

public:
	ShikouteiScene();

	//↓呼び出す必要なし。↓
	//更新処理
	virtual void Update() override;
	//描画処理
	virtual void Draw() override;
	//リセット処理。
	virtual void Reset() override;
	//デバッグ処理。各シーンのImGui表示はここで。
	virtual void Debug() override;
	//インスタンス化処理を書く場所
	virtual void Instantiate() override;
	//初期化処理を書く場所
	virtual void Init() override;

};

