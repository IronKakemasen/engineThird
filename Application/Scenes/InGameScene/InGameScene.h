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
#include "../../GameObjects/UIDisplayer/UIDisplayer.h"
#include "../../Cameras/MainCamera/MainCamera.h"
#include "../../engineCore/Light/RectLight/RectLight.h"
#include "../../Config/InGameConfig.h"
#include "../../GameObjects/Ground/Ground.h"
#include "../../GameObjects/Tenkyuu/TenkyuuClass.h"
#include "../../Models/LightModel/LightModel.h"

class InGameScene final : public Scene
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
	std::unique_ptr<Ground> ground;
	std::unique_ptr < TenkyuuClass> tenkyuuClass;

	std::string path = "./resource/application/json/ModelScene/ModelScene.json";

	std::unique_ptr<UIDisplayer> uiDisplayer;
	struct FieldLightData
	{
		int useNum = 0;
		std::vector<Vector3> dstPositions;
	};

	FieldLightData fieldLightData[InGameController::kStageNum];
	static int const kNumPLight = 9;
	PointLight* fieldpointLights[kNumPLight];
	LightModel lightModels[kNumPLight];
	float const lightHeight = 6.0f;
	PostEffectType curEffectType = PostEffectType::kNone;


	float dirLightIntensityNormal = 0.3f;
	float dirLightIntensityNeon = 0.0f;
	Vector3 dirLightDir = { 0,0,1 };
	float metalicCommonNormal = 0.72f;
	float roughnessCommonNormal = 0.4f;
	float metalicCommonNeon = 0.72f;
	float roughnessCommonNeon = 0.4f;
	float intensityCommon = 714.0f;
	float lightradiusCommon = 11.0f;
	float commonDeltaTheta = 0.0f;
	float commonDeltaTheta2 = 0.0f;

	void AdaptToPostEffect();
	void Load();
	void InputFieldLightData();
	void EnterMode();
	void PlayableMode();

public:

	static inline float metalicCommon = 0.5139999985694885f;
	static inline float roughnessCommon = 0.703000009059906f;

	InGameScene();

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

