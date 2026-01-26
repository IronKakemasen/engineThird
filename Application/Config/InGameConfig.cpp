#include "InGameConfig.h"
#include "../../utilities/Json/Json.h"
#include "imgui.h"

InGameConfig::InGameConfig()
{}

InGameConfig::~InGameConfig()
{}

void InGameConfig::Load()
{
	Json::LoadParam(path, "/player/MaxHP", playerMaxHP);
	Json::LoadParam(path, "/playerTower/MaxHP", playerTowerMaxHP);
	Json::LoadParam(path, "/enemy/MaxHP", enemyMaxHP);
	Json::LoadParam(path, "/enemyFactory/MaxHP", enemyFactoryMaxHP);
	Json::LoadParam(path, "/enemyTower/MaxHP", enemyTowerMaxHP);

	Json::LoadParam(path, "/player/defaultAttackPower", playerDefaultAttackPower);
	Json::LoadParam(path, "/player/allyPowerBonus", playerAllyPowerBonus);
	Json::LoadParam(path, "/player/allySizeBonus", playerAllySizeBonus);
	Json::LoadParam(path, "/enemy/defaultAttackPower", enemyAttackPower);

	Json::LoadParam(path, "/player/speed", playerSpeed);
	Json::LoadParam(path, "/enemy/speed", enemySpeed);

	Json::LoadParam(path, "/enemy/spawnInterval", enemySpawnInterval);
	Json::LoadParam(path, "/enemy/knockBackPowerToAlly", enemyKnockBackPowerToAlly);

	Json::LoadParam(path, "/player/allyDelayFrames", allyDelayFrames);
	Json::LoadParam(path, "/player/attackGaugeRecoverSpeed", playerAttackGaugeRecoverSpeed);
	Json::LoadParam(path, "/player/attackGaugeRecoverInterval", playerAttackGaugeRecoverInterval);
}

void InGameConfig::Save()
{
	Json::SaveParam(path, "/player/MaxHP", playerMaxHP);
	Json::SaveParam(path, "/playerTower/MaxHP", playerTowerMaxHP);
	Json::SaveParam(path, "/enemy/MaxHP", enemyMaxHP);
	Json::SaveParam(path, "/enemyFactory/MaxHP", enemyFactoryMaxHP);
	Json::SaveParam(path, "/enemyTower/MaxHP", enemyTowerMaxHP);

	Json::SaveParam(path, "/player/defaultAttackPower", playerDefaultAttackPower);
	Json::SaveParam(path, "/player/allyPowerBonus", playerAllyPowerBonus);
	Json::SaveParam(path, "/player/allySizeBonus", playerAllySizeBonus);
	Json::SaveParam(path, "/enemy/defaultAttackPower", enemyAttackPower);

	Json::SaveParam(path, "/player/speed", playerSpeed);
	Json::SaveParam(path, "/enemy/speed", enemySpeed);

	Json::SaveParam(path, "/enemy/spawnInterval", enemySpawnInterval);
	Json::SaveParam(path, "/enemy/knockBackPowerToAlly", enemyKnockBackPowerToAlly);

	Json::SaveParam(path, "/player/allyDelayFrames", allyDelayFrames);
	Json::SaveParam(path, "/player/attackGaugeRecoverSpeed", playerAttackGaugeRecoverSpeed);
	Json::SaveParam(path, "/player/attackGaugeRecoverInterval", playerAttackGaugeRecoverInterval);

	Json::Save(path);
}

void InGameConfig::DebugDraw()
{
	ImGui::Begin("InGameConfig");

	ImGui::PushItemWidth(150.0f);

	if (ImGui::Button("Save Config"))
	{
		Save();
	}

	ImGui::Text("---------------------------------------------\n");
	ImGui::DragFloat("Player	MaxHP", &playerMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("PTower	MaxHP", &playerTowerMaxHP, 1.0f, 0.0f, 200.0f);
	ImGui::DragFloat("Enemy		MaxHP", &enemyMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("EFactory	MaxHP", &enemyFactoryMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::DragFloat("ETower	MaxHP", &enemyTowerMaxHP, 1.0f, 0.0f, 100.0f);
	ImGui::Text("---------------------------------------------\n");
	ImGui::DragFloat("Player	attackPower", &playerDefaultAttackPower, 0.1f, 0.0f, 50.0f);
	ImGui::DragFloat("Player	allyPowerBonus", &playerAllyPowerBonus, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Player	allySizeBonus", &playerAllySizeBonus, 0.01f, 0.0f, 10.0f);
	ImGui::DragFloat("Enemy		attackPower", &enemyAttackPower, 0.1f, 0.0f, 50.0f);
	ImGui::Text("---------------------------------------------\n");
	ImGui::DragFloat("Player	speed", &playerSpeed, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Enemy		speed", &enemySpeed, 0.01f, 0.0f, 1.0f);
	ImGui::Text("---------------------------------------------\n");
	ImGui::DragFloat("Enemy		spawnInterval", &enemySpawnInterval, 0.1f, 0.0f, 20.0f);
	ImGui::DragFloat("Enemy		knockBackPowerToAlly", &enemyKnockBackPowerToAlly, 0.1f, 0.0f, 20.0f);
	ImGui::Text("---------------------------------------------\n");
	ImGui::DragInt("Ally		delayFrames", &allyDelayFrames, 1, 0, 120);
	ImGui::DragFloat("Player	attackGaugeRecoverSpeed", &playerAttackGaugeRecoverSpeed, 0.01f, 0.0f, 1.0f);
	ImGui::DragFloat("Player	attackGaugeRecoverInterval", &playerAttackGaugeRecoverInterval, 0.01f, 0.0f, 5.0f);

}