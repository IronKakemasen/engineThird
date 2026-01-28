#include "InGameConfig.h"
#include "../../utilities/Json/Json.h"
#include "imgui.h"

InGameConfig::InGameConfig()
{}

InGameConfig::~InGameConfig()
{}

void InGameConfig::Load()
{
	std::string maxHP = "/MaxHP/";
	Json::LoadParam(path, maxHP + "player", playerMaxHP);
	Json::LoadParam(path, maxHP + "playerTower", playerTowerMaxHP);
	Json::LoadParam(path, maxHP + "enemy", enemyMaxHP);
	Json::LoadParam(path, maxHP + "enemyFactory", enemyFactoryMaxHP);
	Json::LoadParam(path, maxHP + "enemyTower", enemyTowerMaxHP);
	Json::LoadParam(path, maxHP + "playerBullet", playerBulletLifeTime);

	std::string speed = "/Speed/";
	Json::LoadParam(path, speed + "player", playerSpeed);
	Json::LoadParam(path, speed + "enemy", enemySpeed);
	Json::LoadParam(path, speed + "playerBullet", playerBulletSpeed);
	Json::LoadParam(path, speed + "playerAlly", playerAllySpeed);

	std::string power = "/Power/";
	Json::LoadParam(path, power + "player/attak1Power", playerAttack1Power);
	Json::LoadParam(path, power + "player/attak2Power", playerAttack2Power);
	Json::LoadParam(path, power + "player/attak3Power", playerAttack3Power);
	Json::LoadParam(path, power + "player/allyPowerBonus", playerAllyPowerBonus);
	Json::LoadParam(path, power + "player/allySizeBonus", playerAllySizeBonus);
	Json::LoadParam(path, power + "enemy/defaultAttackPower", enemyAttackPower);

	std::string knockBack = "/KnockBackPower/";
	Json::LoadParam(path, knockBack + "enemy/ToAlly", enemyKnockBackPowerToAlly);
	Json::LoadParam(path, knockBack + "enemy/ToBullet1", enemyKnockBackPowerToBullet1);
	Json::LoadParam(path, knockBack + "enemy/ToBullet2", enemyKnockBackPowerToBullet2);
	Json::LoadParam(path, knockBack + "enemy/ToBullet3", enemyKnockBackPowerToBullet3);
	Json::LoadParam(path, knockBack + "enemy/ToPTower", enemyKnockBackPowerToPlayerTower);

	std::string interval = "/SpawnInterval/";
	Json::LoadParam(path, interval + "enemy", enemySpawnInterval);
	Json::LoadParam(path, interval + "playerAlly", playerAllySpawnInterval);

	std::string distance = "/Distance/";
	Json::LoadParam(path, distance + "allyToAlly", allyToAllyDelayFrames);
	Json::LoadParam(path, distance + "playerToAlly", playerToAllyDelayFrames);

	std::string attackGauge = "/AttackGauge/";
	Json::LoadParam(path, attackGauge + "player/attackGaugeRecoverSpeed", playerAttackGaugeRecoverSpeed);
	Json::LoadParam(path, attackGauge + "player/attackGaugeRecoverInterval", playerAttackGaugeRecoverInterval);

}

void InGameConfig::Save()
{
	std::string maxHP = "/MaxHP/";
	Json::SaveParam(path, maxHP + "player", playerMaxHP);
	Json::SaveParam(path, maxHP + "playerTower", playerTowerMaxHP);
	Json::SaveParam(path, maxHP + "enemy", enemyMaxHP);
	Json::SaveParam(path, maxHP + "enemyFactory", enemyFactoryMaxHP);
	Json::SaveParam(path, maxHP + "enemyTower", enemyTowerMaxHP);
	Json::SaveParam(path, maxHP + "playerBullet", playerBulletLifeTime);

	std::string speed = "/Speed/";
	Json::SaveParam(path, speed + "player", playerSpeed);
	Json::SaveParam(path, speed + "enemy", enemySpeed);
	Json::SaveParam(path, speed + "playerBullet", playerBulletSpeed);
	Json::SaveParam(path, speed + "playerAlly", playerAllySpeed);

	std::string power = "/Power/";
	Json::SaveParam(path, power + "player/attak1Power", playerAttack1Power);
	Json::SaveParam(path, power + "player/attak2Power", playerAttack2Power);
	Json::SaveParam(path, power + "player/attak3Power", playerAttack3Power);
	Json::SaveParam(path, power + "player/allyPowerBonus", playerAllyPowerBonus);
	Json::SaveParam(path, power + "player/allySizeBonus", playerAllySizeBonus);
	Json::SaveParam(path, power + "enemy/defaultAttackPower", enemyAttackPower);

	std::string knockBack = "/KnockBackPower/";
	Json::SaveParam(path, knockBack + "enemy/ToAlly", enemyKnockBackPowerToAlly);
	Json::SaveParam(path, knockBack + "enemy/ToBullet1", enemyKnockBackPowerToBullet1);
	Json::SaveParam(path, knockBack + "enemy/ToBullet2", enemyKnockBackPowerToBullet2);
	Json::SaveParam(path, knockBack + "enemy/ToBullet3", enemyKnockBackPowerToBullet3);
	Json::SaveParam(path, knockBack + "enemy/ToPTower", enemyKnockBackPowerToPlayerTower);

	std::string interval = "/SpawnInterval/";
	Json::SaveParam(path, interval + "enemy", enemySpawnInterval);
	Json::SaveParam(path, interval + "playerAlly", playerAllySpawnInterval);

	std::string distance = "/Distance/";
	Json::SaveParam(path, distance + "allyToAlly", allyToAllyDelayFrames);
	Json::SaveParam(path, distance + "playerToAlly", playerToAllyDelayFrames);

	std::string attackGauge = "/AttackGauge/";
	Json::SaveParam(path, attackGauge + "player/attackGaugeRecoverSpeed", playerAttackGaugeRecoverSpeed);
	Json::SaveParam(path, attackGauge + "player/attackGaugeRecoverInterval", playerAttackGaugeRecoverInterval);

	Json::Save(path);
}

void InGameConfig::DebugDraw()
{
#ifdef _DEBUG

	ImGui::PushItemWidth(150.0f);

	if (ImGui::Button("Save Config"))
	{
		Save();
	}


	if (ImGui::TreeNode("MaxHP"))
	{
		ImGui::DragFloat("Player    MaxHP", &playerMaxHP, 1.0f, 0.0f, 100.0f);
		ImGui::DragFloat("PTower    MaxHP", &playerTowerMaxHP, 1.0f, 0.0f, 200.0f);
		ImGui::DragFloat("Enemy     MaxHP", &enemyMaxHP, 1.0f, 0.0f, 100.0f);
		ImGui::DragFloat("EFactory  MaxHP", &enemyFactoryMaxHP, 1.0f, 0.0f, 100.0f);
		ImGui::DragFloat("ETower    MaxHP", &enemyTowerMaxHP, 1.0f, 0.0f, 100.0f);
		ImGui::DragFloat("Bullet    LifeTime", &playerBulletLifeTime, 0.1f, 0.0f, 10.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Speed"))
	{
		ImGui::DragFloat("Player	speed", &playerSpeed, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Enemy		speed", &enemySpeed, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Bullet	speed", &playerBulletSpeed, 0.01f, 0.0f, 5.0f);
		ImGui::DragFloat("Ally		speed", &playerAllySpeed, 0.1f, 0.0f, 10.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Power"))
	{
		ImGui::DragFloat("Player	attack1Power", &playerAttack1Power, 0.1f, 0.0f, 50.0f);
		ImGui::DragFloat("Player	attack2Power", &playerAttack2Power, 0.1f, 0.0f, 50.0f);
		ImGui::DragFloat("Player	attack3Power", &playerAttack3Power, 0.1f, 0.0f, 50.0f);
		ImGui::DragFloat("Player	allyPowerBonus", &playerAllyPowerBonus, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Player	allySizeBonus", &playerAllySizeBonus, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat("Enemy		attackPower", &enemyAttackPower, 0.1f, 0.0f, 50.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("KnockBackPower"))
	{
		ImGui::DragFloat("Enemy		toAlly", &enemyKnockBackPowerToAlly, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	toBullet1", &enemyKnockBackPowerToBullet1, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	toBullet2", &enemyKnockBackPowerToBullet2, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	toBullet3", &enemyKnockBackPowerToBullet3, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	toPTower", &enemyKnockBackPowerToPlayerTower, 0.1f, 0.0f, 20.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("SpawnInterval"))
	{
		ImGui::DragFloat("Enemy		spawnInterval", &enemySpawnInterval, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Ally		spawnInterval", &playerAllySpawnInterval, 0.1f, 0.0f, 20.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Distance"))
	{
		ImGui::DragInt("Ally		A-A delayFrames", &allyToAllyDelayFrames, 1, 0, 120);
		ImGui::DragInt("Ally		P-A delayFrames", &playerToAllyDelayFrames, 1, 0, 120);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("AttackGauge"))
	{
		ImGui::DragFloat("Player	attackGaugeRecoverSpeed", &playerAttackGaugeRecoverSpeed, 0.01f, 0.0f, 1.0f);
		ImGui::DragFloat("Player	attackGaugeRecoverInterval", &playerAttackGaugeRecoverInterval, 0.01f, 0.0f, 5.0f);
		ImGui::TreePop();

	}

#endif // _DEBUG
}