#include "InGameConfig.h"
#include "../../utilities/Json/Json.h"
#include "imgui.h"

InGameConfig::InGameConfig()
{}

InGameConfig::~InGameConfig()
{}

void InGameConfig::Load()
{
	std::string controller = "/Controller/";
	Json::LoadParam(path, controller + "deadZone", deadZone);

	std::string collisonSize = "/CollisonSize/";
	Json::LoadParam(path, collisonSize + "player", playerCollisonSize);
	Json::LoadParam(path, collisonSize + "playerTower", playerTowerCollisonSize);
	Json::LoadParam(path, collisonSize + "bullet", playerBulletCollisonSize);
	Json::LoadParam(path, collisonSize + "ally", playerAllyCollisonSize);
	Json::LoadParam(path, collisonSize + "enemy", enemyCollisonSize);
	Json::LoadParam(path, collisonSize + "enemyTower", enemyTowerCollisonSize);
	Json::LoadParam(path, collisonSize + "enemyFactory", enemyFactoryCollisonSize);

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
	Json::LoadParam(path, power + "player/defaultAttackPower", playerPower);
	Json::LoadParam(path, power + "player/allyPowerBonus", playerAllyPowerBonus);
	Json::LoadParam(path, power + "player/allySizeBonus", playerAllySizeBonus);
	Json::LoadParam(path, power + "enemy/defaultAttackPower", enemyAttackPower);

	std::string knockBack = "/KnockBackPower/";
	Json::LoadParam(path, knockBack + "enemy/DamapingRate", enemyKnockBackDampingRate);
	Json::LoadParam(path, knockBack + "enemy/ToAlly", enemyKnockBackPowerToAlly);
	Json::LoadParam(path, knockBack + "enemy/ToPlayer", enemyKnockBackPowerToPlayer);
	Json::LoadParam(path, knockBack + "enemy/ToBullet", enemyKnockBackPowerToBullet);
	Json::LoadParam(path, knockBack + "enemy/ToPTower", enemyKnockBackPowerToPlayerTower);
	Json::LoadParam(path, knockBack + "enemy/OfSpawn", enemyKnockBackPowerOfSpawn);
	Json::LoadParam(path, knockBack + "enemy/RandomAngleOfSpawn", enemyKnockBackRandomAngleOfSpawn);

	std::string interval = "/SpawnInterval/";
	Json::LoadParam(path, interval + "enemyMin", enemySpawnIntervalMin);
	Json::LoadParam(path, interval + "enemyMax", enemySpawnIntervalMax);
	Json::LoadParam(path, interval + "playerAlly", playerAllySpawnInterval);
	Json::LoadParam(path, interval + "maxAllyCount", maxAllyCount);
	Json::LoadParam(path, interval + "enemyFactoryRespawnInterval", enemyFactoryRespawnInterval);

	std::string distance = "/Distance/";
	Json::LoadParam(path, distance + "allyToAlly", allyToAllyDelayFrames);
	Json::LoadParam(path, distance + "playerToAlly", playerToAllyDelayFrames);

	std::string attackGauge = "/AttackGauge/";
	Json::LoadParam(path, attackGauge + "player/playerAttackInterval", playerAttackInterval);

	std::string Separate = "/Separate/";
	Json::LoadParam(path, Separate + "judgeSinglePressFrame", judgeSinglePressFrame);
	Json::LoadParam(path, Separate + "separateCompleteFrame", separateCompleteFrame);
}

void InGameConfig::Save()
{
	std::string controller = "/Controller/";
	Json::SaveParam(path, controller + "deadZone", deadZone);

	std::string CollisonSize = "/CollisonSize/";
	Json::SaveParam(path, CollisonSize + "player", playerCollisonSize);
	Json::SaveParam(path, CollisonSize + "playerTower", playerTowerCollisonSize);
	Json::SaveParam(path, CollisonSize + "bullet", playerBulletCollisonSize);
	Json::SaveParam(path, CollisonSize + "ally", playerAllyCollisonSize);
	Json::SaveParam(path, CollisonSize + "enemy", enemyCollisonSize);
	Json::SaveParam(path, CollisonSize + "enemyTower", enemyTowerCollisonSize);
	Json::SaveParam(path, CollisonSize + "enemyFactory", enemyFactoryCollisonSize);

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
	Json::SaveParam(path, power + "player/defaultAttackPower", playerPower);
	Json::SaveParam(path, power + "player/allyPowerBonus", playerAllyPowerBonus);
	Json::SaveParam(path, power + "player/allySizeBonus", playerAllySizeBonus);
	Json::SaveParam(path, power + "enemy/defaultAttackPower", enemyAttackPower);

	std::string knockBack = "/KnockBackPower/";
	Json::SaveParam(path, knockBack + "enemy/DamapingRate", enemyKnockBackDampingRate);
	Json::SaveParam(path, knockBack + "enemy/ToAlly", enemyKnockBackPowerToAlly);
	Json::SaveParam(path, knockBack + "enemy/ToPlayer", enemyKnockBackPowerToPlayer);
	Json::SaveParam(path, knockBack + "enemy/ToBullet", enemyKnockBackPowerToBullet);
	Json::SaveParam(path, knockBack + "enemy/ToPTower", enemyKnockBackPowerToPlayerTower);
	Json::SaveParam(path, knockBack + "enemy/OfSpawn", enemyKnockBackPowerOfSpawn);
	Json::SaveParam(path, knockBack + "enemy/RandomAngleOfSpawn", enemyKnockBackRandomAngleOfSpawn);


	std::string interval = "/SpawnInterval/";
	Json::SaveParam(path, interval + "enemyMin", enemySpawnIntervalMin);
	Json::SaveParam(path, interval + "enemyMax", enemySpawnIntervalMax);
	Json::SaveParam(path, interval + "playerAlly", playerAllySpawnInterval);
	Json::SaveParam(path, interval + "maxAllyCount", maxAllyCount);
	Json::SaveParam(path, interval + "enemyFactoryRespawnInterval", enemyFactoryRespawnInterval);

	std::string distance = "/Distance/";
	Json::SaveParam(path, distance + "allyToAlly", allyToAllyDelayFrames);
	Json::SaveParam(path, distance + "playerToAlly", playerToAllyDelayFrames);

	std::string attackGauge = "/AttackGauge/";
	Json::SaveParam(path, attackGauge + "player/playerAttackInterval", playerAttackInterval);

	std::string Separate = "/Separate/";
	Json::SaveParam(path, Separate + "judgeSinglePressFrame", judgeSinglePressFrame);
	Json::SaveParam(path, Separate + "separateCompleteFrame", separateCompleteFrame);

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

	ImGui::Separator();

	if (ImGui::TreeNode("Controller"))
	{
		ImGui::DragFloat("DeadZone", &deadZone, 0.01f, 0.0f, 1.0f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("CollisonSize"))
	{
		ImGui::DragFloat("Player    CollisonSize", &playerCollisonSize, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("PTower    CollisonSize", &playerTowerCollisonSize, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Bullet    CollisonSize", &playerBulletCollisonSize, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Ally      CollisonSize", &playerAllyCollisonSize, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("Enemy     CollisonSize", &enemyCollisonSize, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("ETower    CollisonSize", &enemyTowerCollisonSize, 0.1f, 0.0f, 10.0f);
		ImGui::DragFloat("EFactory  CollisonSize", &enemyFactoryCollisonSize, 0.1f, 0.0f, 10.0f);

		ImGui::TreePop();
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
		ImGui::DragFloat("Player	Power", &playerPower, 0.1f, 0.0f, 50.0f);
		ImGui::DragFloat("Player	allyPowerBonus", &playerAllyPowerBonus, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Player	allySizeBonus", &playerAllySizeBonus, 0.01f, 0.0f, 10.0f);
		ImGui::DragFloat("Enemy		attackPower", &enemyAttackPower, 0.1f, 0.0f, 50.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("KnockBackPower"))
	{
		ImGui::DragFloat("Enemy		DamapingRate", &enemyKnockBackDampingRate, 0.01f, 0.01f, 0.99f);
		ImGui::DragFloat("Enemy		toAlly", &enemyKnockBackPowerToAlly, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy		toPlayer", &enemyKnockBackPowerToPlayer, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	toBullet", &enemyKnockBackPowerToBullet, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	toPTower", &enemyKnockBackPowerToPlayerTower, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	ofSpawn", &enemyKnockBackPowerOfSpawn, 0.1f, 0.0f, 20.0f);
		ImGui::DragFloat("Enemy 	randomAngleOfSpawn", &enemyKnockBackRandomAngleOfSpawn, 1.0f, 0.0f, 360.0f);

		ImGui::TreePop();
	}
	if (ImGui::TreeNode("AutoSpawn"))
	{
		ImGui::DragFloat("Enemy		spawnIntervalMin", &enemySpawnIntervalMin, 0.1f, 0.0f, enemySpawnIntervalMax);
		ImGui::DragFloat("Enemy		spawnIntervalMax", &enemySpawnIntervalMax, 0.1f, enemySpawnIntervalMin, 20.0f);
		ImGui::DragFloat("Ally		spawnInterval", &playerAllySpawnInterval, 0.1f, 0.0f, 2.0f);
		ImGui::DragInt("Ally		maxAllyCount", &maxAllyCount, 1, 1, 100);
		ImGui::DragFloat("EFactory	respawnInterval", &enemyFactoryRespawnInterval, 1.0f, 0.0f, 60.0f);

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
		ImGui::DragFloat("Player	attackGaugeRecoverInterval", &playerAttackInterval, 0.01f, 0.0f, 10.0f);
		ImGui::TreePop();

	}
	if (ImGui::TreeNode("Separate"))
	{
		ImGui::DragInt("JudgeSinglePressFrame", &judgeSinglePressFrame, 1, 1, 60);
		ImGui::DragInt("SeparateCompleteFrame", &separateCompleteFrame, 1, 30, 300);
		ImGui::TreePop();
	}

#endif // _DEBUG
}