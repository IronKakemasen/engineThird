#pragma once
#include "SceneBehavior.h"
#include "../../GameObjects/ForModelView/PM.h"
#include "../../GameObjects/ForModelView/groundM.h"
#include "../../M/utilities/Json/Json.h"
#include "../../Models/EnemyModel/EnemyModel.h"
#include "../../Models/Tenkyu/Tenkyu.h"
#include "../../Models/PlayerAllyModel/PlayerAllyModel.h"
#include "../../Models/PlayerTowerModel/PlayerTowerModel.h"
#include "../../Models/EnemyTowerModel/EnemyTowerModel.h"
#include "../../Models/EnemyFactoryModel/EnemyFactoryModel.h"

class ModelScene final : public Scene
{
	PM p;
	groundM gm;
	EnemyModel enemyModel;
	Tenkyu tenkyu;
	PlayerAllyModel playerAllyModel;
	PlayerTowerModel playerTowerModel;
	EnemyTowerModel enemyTowerModel;
	EnemyFactoryModel enemyFactoryModel;

	std::string path = "./resource/application/json/ModelScene/ModelScene.json";

	float dirLightIntensityNormal = 0.0f;
	float dirLightIntensityNeon = 0.0f;
	Vector3 dirLightDir = {0,0,1};
	float metalicCommonNormal = 0.72f;
	float roughnessCommonNormal = 0.4f;
	float metalicCommonNeon = 0.72f;
	float roughnessCommonNeon = 0.4f;


	void Save();
	void Load();

public:
	ModelScene();

	void AdaptToPostEffect();

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

