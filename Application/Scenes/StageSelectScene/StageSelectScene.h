#pragma once
#include "SceneBehavior.h"
#include <array>
#include <vector>
#include "../../Config/GameConstants.h"

#include "../../GameObjects/Player/Player.h"
#include "../../GameObjects/Ground/Ground.h"
#include "../../GameObjects/Player/PlayerTower/PlayerTower.h"
#include "../../GameObjects/Player/PlayerAlly/PlayerAlly.h"
#include "../../GameObjects/Player/PlayerBullet/PlayerBullet.h"
#include "../../GameObjects/Enemy/Enemy.h"
#include "../../GameObjects/Enemy/EnemyTower/EnemyTower.h"
#include "../../GameObjects/Enemy/EnemyFactory/EnemyFactory.h"
#include "../../GameObjects/Shikoutei/Shikoutei.h"
#include "../../GameObjects/InGameController/InGameController.h"
#include "../../Cameras/StageCamera/StageCamera.h"
#include "../../engineCore/Light/RectLight/RectLight.h"
#include "../../Config/InGameConfig.h"

class StageSelectScene final : public Scene
{
	//そのシーンのカメラのトランスフォームをいただく
	StageCamera mainCamera;

	//使用するゲームオブジェクト
	std::array<std::array<std::unique_ptr<Shikoutei>, 1>, GameConstants::kMaxStages> centerObject;
	std::array<std::array<std::unique_ptr<Player>, 1>, GameConstants::kMaxStages> player;
	std::array<std::array<std::unique_ptr<PlayerTower>, GameConstants::kMaxPlayerTowers>, GameConstants::kMaxStages> playerTowers;
	std::array<std::array<std::unique_ptr<EnemyTower>, GameConstants::kMaxEnemyTowers>, GameConstants::kMaxStages> enemyTowers;
	std::array<std::array<std::unique_ptr<EnemyFactory>, GameConstants::kMaxEnemyFactories>, GameConstants::kMaxStages> enemyFactories;
	std::array<std::array<std::unique_ptr<Ground>, 1>, GameConstants::kMaxStages> grounds;
	std::unique_ptr<InGameController> inGameController;
	std::unique_ptr<InGameConfig> inGameConfig;

	float baseCenterRotateY = 0.0f;
	const float stagePerYRotate = (360.0f / float(GameConstants::kMaxStages));
	Counter selectCounter;

	// イージング用
	float startRotateY = 0.0f;
	float targetRotateY = 0.0f;

	void AdaptToPostEffect();

	// 選択ステージ変更
	void UpdateStageSelectRotation();

	// ステージ決定
	void DecideStage();
	bool selected = false;

	// 決定後演出
	void UpdateAfterDecideStage();
	Counter afterDecideCounter;

public:
	StageSelectScene();

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

